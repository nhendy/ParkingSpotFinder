
#include "FT_Platform.h"
#include "FT_Gpu_Hal.h"
#include "FT_Gpu.h"
#include "FT_CoPro_Cmds.h"
#include "Ft_Esd.h"
#include "FT_Esd_Dl.h"
#include "Ft_Esd_GpuAlloc.h"

extern Ft_Gpu_Hal_Context_t *Ft_Esd_Host;
extern Ft_Esd_GpuAlloc *Ft_Esd_GAlloc;
extern ft_uint32_t Ft_Esd_Millis;
extern ft_uint32_t Ft_Esd_DeltaMs;
extern ft_uint32_t Ft_Esd_Frame;
extern ft_rgb32_t Ft_Esd_ClearColor;

extern ft_int16_t FT_DispWidth;
extern ft_int16_t FT_DispHeight;

// When not in the simulation, use the Ft_Main__Start etc symbols
// as exported by the single Application logic document included
#ifndef ESD_SIMULATION
#define Ft_Main__Running__ESD() 1
#define Ft_Main__Start__ESD Ft_Main__Start
#define Ft_Main__Update__ESD Ft_Main__Update
#define Ft_Main__Render__ESD Ft_Main__Render
#define Ft_Main__Idle__ESD Ft_Main__Idle
#define Ft_Main__End__ESD Ft_Main__End
#else
int Ft_Main__Running__ESD();
int Ft_Sleep__ESD(int ms);
#endif

ft_void_t Ft_Main__Start__ESD();
ft_void_t Ft_Main__Update__ESD();
ft_void_t Ft_Main__Render__ESD();
ft_void_t Ft_Main__Idle__ESD();
ft_void_t Ft_Main__End__ESD();

static int s_SpinnerPopup = 0;
static int s_SpinnerPopped = 0;
ESD_FUNCTION(Ft_Esd_Spinner_Popup, DisplayName = "Pop-up Spinner", Category = EsdUtilities)
void Ft_Esd_Spinner_Popup()
{
	s_SpinnerPopup = 1;
}

void Ft_Esd_ResetCoState();

void Ft_Esd_Timer_CancelGlobal();
void Ft_Esd_Timer_UpdateGlobal();

ft_void_t Ft_Esd_MainLoop()
{
	Ft_Gpu_Hal_Context_t *phost = Ft_Esd_Host;

	// Initialize application
	Ft_Esd_ResetGpuState();
	Ft_Esd_ResetCoState();
	Ft_Esd_Frame = 0;
	Ft_Esd_Millis = ft_millis();
	Ft_Esd_Timer_CancelGlobal();
	Ft_Main__Start__ESD();

	int idled = 0;
	while (Ft_Main__Running__ESD())
	{
		// Idle at least once every frame
		if (!idled) Ft_Main__Idle__ESD();
		else idled = 0;

		// Update GUI state before render
		ft_uint32_t ms = ft_millis(); // Calculate frame time delta
		Ft_Esd_DeltaMs = ms - Ft_Esd_Millis;
		Ft_Esd_Millis = ms;
		Ft_Esd_GpuAlloc_Update(Ft_Esd_GAlloc); // Run GC
		Ft_Main__Update__ESD();
		Ft_Esd_Timer_UpdateGlobal();

		// Process all coprocessor commands
		Ft_Gpu_Hal_WrCmd32(phost, CMD_DLSTART);
		Ft_Gpu_Hal_WrCmd32(phost, (2UL << 24) | Ft_Esd_ClearColor); // CLEAR_COLOR_RGB(33, 33, 33)); // Set CLEAR_COLOR_RGB from user var
		Ft_Gpu_Hal_WrCmd32(phost, CLEAR_TAG(255)); // Always default to 255, so no touch = 0, touch non-tag = 255
		Ft_Gpu_Hal_WrCmd32(phost, CLEAR(1, 1, 1));
		Ft_Main__Render__ESD();

		if (s_SpinnerPopup)
		{
			// Spinner used for switching longer loading pages with bitmaps etc
			Ft_Esd_Dl_COLOR_RGB(~Ft_Esd_ClearColor);
			Ft_Gpu_CoCmd_Spinner(phost, FT_DispWidth / 2, FT_DispHeight / 2, 0, 0);
			s_SpinnerPopup = 0;
			s_SpinnerPopped = 1;
		}
		else if (s_SpinnerPopped)
		{
			Ft_Gpu_CoCmd_Stop(phost);
			s_SpinnerPopped = 0;
		}

		Ft_Gpu_Hal_WrCmd32(phost, DISPLAY());
		Ft_Gpu_CoCmd_Swap(phost);

		// Replacement for Ft_Gpu_Hal_WaitCmdfifo_empty(phost); with idle function
		while (Ft_Gpu_Hal_Rd16(phost, REG_CMD_READ) != Ft_Gpu_Hal_Rd16(phost, REG_CMD_WRITE))
		{
			// Loop an idle task instead of doing nothing
			Ft_Main__Idle__ESD();
			idled = 1;
		}
		phost->ft_cmd_fifo_wp = Ft_Gpu_Hal_Rd16(phost, REG_CMD_WRITE);

		// Restore initial frame values
		// Ft_Gpu_CoCmd_LoadIdentity(phost); // ?
		Ft_Esd_ResetGpuState();
		++Ft_Esd_Frame;
	}

	// Cleanup application (generally unreachable)
	Ft_Esd_Timer_CancelGlobal();
	Ft_Main__End__ESD();
}

/* end of file */
