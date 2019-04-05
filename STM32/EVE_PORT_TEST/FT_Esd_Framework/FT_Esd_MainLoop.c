
#include "FT_Platform.h"
#include "FT_Gpu_Hal.h"
#include "FT_Gpu.h"
#include "Ft_Esd.h"
#include "FT_Esd_Dl.h"
#include "Ft_Esd_GpuAlloc.h"
#include "Ft_Esd_TouchTag.h"
#include "Ft_Esd_CoCmd.h"

extern Ft_Gpu_Hal_Context_t *Ft_Esd_Host;
extern Ft_Esd_GpuAlloc *Ft_Esd_GAlloc;
extern ft_uint32_t Ft_Esd_Millis;
extern ft_uint32_t Ft_Esd_DeltaMs;
extern ft_uint32_t Ft_Esd_Frame;
extern ft_rgb32_t Ft_Esd_ClearColor;
extern ft_uint8_t Ft_Esd_LoopState;

extern ft_int16_t FT_DispWidth;
extern ft_int16_t FT_DispHeight;

extern void Ft_Hal_LoadSDCard();
extern void Ft_Esd_Widget_ProcessFree();

// When not in the simulation, use the Ft_Main__Start etc symbols
// as exported by the single Application logic document included
#ifndef ESD_SIMULATION
#ifdef BT8XXEMU_PLATFORM
#define Ft_Main__Running__ESD() BT8XXEMU_isRunning(Ft_Esd_Host->emu)
#else
#define Ft_Main__Running__ESD() (1)
#endif
#define Ft_Main__Start__ESD  Ft_Main__Start
#define Ft_Main__Update__ESD Ft_Main__Update
#define Ft_Main__Render__ESD Ft_Main__Render
#define Ft_Main__Idle__ESD   Ft_Main__Idle
#define Ft_Main__End__ESD    Ft_Main__End
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



//A function to enable spinner when frame is rendered.  
ESD_FUNCTION(Ft_Esd_Spinner_Popup, DisplayName = "Pop-up Spinner", Category = EsdUtilities)
void Ft_Esd_Spinner_Popup()
{
	s_SpinnerPopup = 1;
}

void Ft_Esd_InitDlState();
void Ft_Esd_ResetCoState();

void Ft_Esd_Timer_CancelGlobal();
void Ft_Esd_Timer_UpdateGlobal();


ft_void_t Ft_Esd_MainLoop()
{
	Ft_Gpu_Hal_Context_t *phost = Ft_Esd_Host;
	if (!Ft_Main__Running__ESD())
		return;

	// Initialize application
	Ft_Esd_InitDlState();
	Ft_Esd_ResetGpuState();
	Ft_Esd_ResetCoState();
	Ft_Esd_Frame = 0;

	Ft_Esd_Millis = ft_millis();
	Ft_Esd_Timer_CancelGlobal();
	Ft_Main__Start__ESD();

	int idled = 0;
	while (Ft_Main__Running__ESD())
	{
		// Verify initialization
        Ft_Hal_LoadSDCard();

		// Idle at least once every frame
		Ft_Esd_LoopState = ESD_LOOPSTATE_IDLE;
		if (!idled) Ft_Main__Idle__ESD();
		else idled = 0;
		
		// Update GUI state before render
		Ft_Esd_LoopState = ESD_LOOPSTATE_UPDATE;
		ft_uint32_t ms = ft_millis(); // Calculate frame time delta
		Ft_Esd_DeltaMs = ms - Ft_Esd_Millis;
		Ft_Esd_Millis = ms;
		Ft_Esd_GpuAlloc_Update(Ft_Esd_GAlloc); // Run GC
		Ft_Esd_TouchTag_Update(0); // Update touch
		Ft_Main__Update__ESD();
		Ft_Esd_Timer_UpdateGlobal();
		
		
		// Process all coprocessor commands
		Ft_Esd_LoopState = ESD_LOOPSTATE_RENDER;

		Ft_Gpu_CoCmd_StartFrame();


		Ft_Gpu_Hal_WrCmd32(phost, CMD_DLSTART);
		Ft_Gpu_Hal_WrCmd32(phost, (2UL << 24) | Ft_Esd_ClearColor); // Set CLEAR_COLOR_RGB from user var
		Ft_Gpu_Hal_WrCmd32(phost, CLEAR_TAG(255)); // Always default to 255, so no touch = 0, touch non-tag = 255
		Ft_Gpu_Hal_WrCmd32(phost, CLEAR(1, 1, 1));
		Ft_Main__Render__ESD();

		
		if (s_SpinnerPopup)
		{
			// Spinner used for switching longer loading pages with bitmaps etc
			Ft_Esd_Dl_COLOR_RGB(~Ft_Esd_ClearColor);
			Ft_Esd_CoCmd_Spinner(Ft_Esd_MainLoop, FT_DispWidth / 2, FT_DispHeight / 2, 0, 0);
			s_SpinnerPopup = 0;
			s_SpinnerPopped = 1;
		}
		else if (s_SpinnerPopped)
		{
			Ft_Esd_CoCmd_Stop(Ft_Esd_MainLoop);
			s_SpinnerPopped = 0;
		}

		Ft_Gpu_Hal_WrCmd32(phost, DISPLAY());
		Ft_Gpu_CoCmd_Swap(phost);


		Ft_Gpu_CoCmd_EndFrame(phost);


		// Replacement for Ft_Gpu_Hal_WaitCmdfifo_empty(phost); with idle function
		Ft_Esd_LoopState = ESD_LOOPSTATE_IDLE;
		
		while (Ft_Gpu_Hal_Rd16(phost, REG_CMD_READ) != Ft_Gpu_Hal_Rd16(phost, REG_CMD_WRITE))
		{
			// Loop an idle task instead of doing nothing
			Ft_Main__Idle__ESD();
            Ft_Gpu_Hal_ESD_Idle(phost);
			idled = 1;
		}
		// Restore initial frame values
		// Ft_Gpu_CoCmd_LoadIdentity(phost); // ?
		Ft_Esd_ResetGpuState();
		Ft_Esd_Widget_ProcessFree();
		++Ft_Esd_Frame;		
	}

	// Cleanup application (generally unreachable)
	Ft_Esd_LoopState = ESD_LOOPSTATE_NONE;
	Ft_Esd_Timer_CancelGlobal();
	Ft_Main__End__ESD();
}

/* end of file */
