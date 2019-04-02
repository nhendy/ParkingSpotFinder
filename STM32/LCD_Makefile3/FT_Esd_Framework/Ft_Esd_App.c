/**
* This source code ("the Software") is provided by Bridgetek Pte Ltd
* ("Bridgetek") subject to the licence terms set out
*   http://brtchip.com/BRTSourceCodeLicenseAgreement/ ("the Licence Terms").
* You must read the Licence Terms before downloading or using the Software.
* By installing or using the Software you agree to the Licence Terms. If you
* do not agree to the Licence Terms then do not download or use the Software.
*
* Without prejudice to the Licence Terms, here is a summary of some of the key
* terms of the Licence Terms (and in the event of any conflict between this
* summary and the Licence Terms then the text of the Licence Terms will
* prevail).
*
* The Software is provided "as is".
* There are no warranties (or similar) in relation to the quality of the
* Software. You use it at your own risk.
* The Software should not be used in, or for, any medical device, system or
* appliance. There are exclusions of Bridgetek liability for certain types of loss
* such as: special loss or damage; incidental loss or damage; indirect or
* consequential loss or damage; loss of income; loss of business; loss of
* profits; loss of revenue; loss of contracts; business interruption; loss of
* the use of money or anticipated savings; loss of information; loss of
* opportunity; loss of goodwill or reputation; and/or loss of, damage to or
* corruption of data.
* There is a monetary cap on Bridgetek's liability.
* The Software may have subsequently been amended by another user and then
* distributed by that other user ("Adapted Software").  If so that user may
* have additional licence terms that apply to those amendments. However, Bridgetek
* has no liability in relation to those amendments.
*/

#include <FT_Platform.h>
#include "Ft_Esd.h"
#include "Ft_Esd_GpuAlloc.h"


//
// Static
//
static Ft_Gpu_Hal_Context_t s_Host;
static Ft_Gpu_HalInit_t     s_HalInit;
static Ft_Esd_GpuAlloc      s_GAlloc;


//
// Globals
//
Ft_Gpu_Hal_Context_t *Ft_Esd_Host   = 0; // Pointer to s_Host
Ft_Esd_GpuAlloc      *Ft_Esd_GAlloc = 0; // Pointer to s_GAlloc
ft_uint32_t Ft_Esd_Millis  = 0;  // Time in milliseconds for current frame
ft_uint32_t Ft_Esd_DeltaMs = 0;  // Delta time in milliseconds between frames
ft_uint32_t Ft_Esd_Frame   = 0;  // Number of times Render has been called
ft_rgb32_t Ft_Esd_ClearColor = 0x212121; // Screen clear color
ft_uint8_t Ft_Esd_LoopState  = ESD_LOOPSTATE_NONE;

/*A function to get milliseconds for current frame*/
ESD_FUNCTION(Ft_Esd_GetMillis, Type = ft_uint32_t, DisplayName = "Get Milliseconds", Category = EsdUtilities)
ft_uint32_t Ft_Esd_GetMillis() { return Ft_Esd_Millis; }

/* A function to get the difference in milliseconds since last frame Update call */
ESD_FUNCTION(Ft_Esd_GetDeltaMs, Type = ft_uint32_t, DisplayName = "Get Delta Ms", Category = EsdUtilities)
ft_uint32_t Ft_Esd_GetDeltaMs() { return Ft_Esd_DeltaMs; }

/* A function to get the global HAL context data structure*/
ESD_FUNCTION(Ft_Esd_GetHost, Type = Ft_Gpu_Hal_Context_t *, DisplayName = "Get EVE Host", Category = EsdUtilities)
Ft_Gpu_Hal_Context_t *Ft_Esd_GetHost() { return Ft_Esd_Host; }

ft_uint16_t Ft_Esd_FontHeight[35] = { 0 }; // Font heights of currently set bitmaps


#ifdef ESD_SIMULATION
int Ft_Esd_DesignerMode = 0;
#endif

#define FT_WELCOME_MESSAGE "Copyright (C) Bridgetek Pte Ltd.\r\n"

/* API to demonstrate calibrate widget/functionality */
ft_void_t App_CoPro_Widget_Calibrate()
{
	ft_uint32_t NumBytesGen = 0, TransMatrix[6];
	ft_uint16_t CurrWriteOffset = 0;


	Ft_Gpu_CoCmd_StartFrame();


	Ft_Gpu_CoCmd_Dlstart(&s_Host);
	Ft_Gpu_Hal_WrCmd32(&s_Host, CLEAR_COLOR_RGB(64, 64, 64));
	Ft_Gpu_Hal_WrCmd32(&s_Host, CLEAR(1, 1, 1));
	Ft_Gpu_Hal_WrCmd32(&s_Host, COLOR_RGB(0xff, 0xff, 0xff));
	
	//Ft_Gpu_CoCmd_Text(&s_Host, (FT_DispWidth / 2), (FT_DispHeight / 2), 27, OPT_CENTER, "Please Tap on the dot");

	#if defined(FT_801_ENABLE) || defined(FT_811_ENABLE) || defined(FT_813_ENABLE)
		Ft_Gpu_Hal_Wr8(&s_Host, REG_CTOUCH_EXTENDED, CTOUCH_MODE_COMPATIBILITY);
	#endif
	Ft_Gpu_CoCmd_Calibrate(&s_Host, 0);


	Ft_Gpu_CoCmd_EndFrame(&s_Host);


	/* Wait till coprocessor completes the operation */
	Ft_Gpu_Hal_WaitCmdfifo_empty(&s_Host);
	/* Print the configured values */
	Ft_Gpu_Hal_RdMem(&s_Host, REG_TOUCH_TRANSFORM_A, (ft_uint8_t *)TransMatrix, 4 * 6); //read all the 6 coefficients
#ifdef MSVC_PLATFORM
	ESD_print("Touch screen transform values are A 0x%x,B 0x%x,C 0x%x,D 0x%x,E 0x%x, F 0x%x",
		TransMatrix[0], TransMatrix[1], TransMatrix[2], TransMatrix[3], TransMatrix[4], TransMatrix[5]);
#endif
}

// TODO: Update Ft_Esd_FontHeight on CMD_SETFONT
ft_void_t Ft_Esd_InitFontHeight()
{
	ft_uint32_t ft = Ft_Gpu_Hal_Rd32(&s_Host, ROMFONT_TABLEADDRESS);
	for (int i = 0; i < 19; ++i)
	{
		ft_uint32_t addr = ft + (FT_GPU_FONT_TABLE_SIZE * i) + (ft_uint32_t)(uintptr_t)(&(((FT_Gpu_Fonts_t *)(void *)0)->FontHeightInPixels));
		Ft_Esd_FontHeight[16 + i] = Ft_Gpu_Hal_Rd16(&s_Host, addr);
	}
}

ft_void_t setup()
{

}

// Ft_Esd_MainLoop
ft_void_t Ft_Esd_MainLoop();

// FT_Mcu_Hal.c
ft_void_t Eve_BootupConfig(Ft_Gpu_Hal_Context_t *s_Host);
ft_void_t Ft_Mcu_Init();

/* Main entry point */
ft_int32_t main(ft_int32_t argc, ft_char8_t *argv[])
{
	ESD_print("\f"); // Shows horizontal line in ESD output window
	ESD_print(FT_WELCOME_MESSAGE);

    Ft_Mcu_Init();

	Ft_Gpu_Hal_Init(&s_HalInit);
	Ft_Gpu_Hal_Open(&s_Host);
	Ft_Esd_Host = &s_Host;

    Eve_BootupConfig(&s_Host);

#ifndef ESD_SIMULATION
	App_CoPro_Widget_Calibrate(); 
#endif

	Ft_Esd_GAlloc = &s_GAlloc;
	Ft_Esd_GpuAlloc_Reset(&s_GAlloc);

	Ft_Esd_InitFontHeight();

	Ft_Esd_MainLoop();

	Ft_Gpu_Hal_Close(&s_Host);
	Ft_Gpu_Hal_DeInit();
	Ft_Esd_Host = 0;
    
	return 0;
}

ft_uint32_t Ft_Esd_GAlloc_GetTotalUsed(Ft_Esd_GpuAlloc *ga)
{
	if (!Ft_Esd_GAlloc) return 0;
	return Ft_Esd_GpuAlloc_GetTotalUsed(Ft_Esd_GAlloc);
}

ft_uint32_t Ft_Esd_GAlloc_GetTotal(Ft_Esd_GpuAlloc *ga)
{
	if (!Ft_Esd_GAlloc) return 0;
	return Ft_Esd_GpuAlloc_GetTotal(Ft_Esd_GAlloc);
}

/* Nothing beyond this */
