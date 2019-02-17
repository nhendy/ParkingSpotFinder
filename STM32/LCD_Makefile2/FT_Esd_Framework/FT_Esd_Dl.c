
#include "FT_Platform.h"
#include "FT_Esd_Dl.h"

Ft_Esd_GpuState_T Ft_Esd_GpuState[FT_ESD_STATE_STACK_SIZE];
ft_uint8_t Ft_Esd_GpuState_I;
ft_uint32_t Ft_Esd_CoFgColor;
ft_uint32_t Ft_Esd_CoBgColor;

// Number of bitmap handles to use (and also the scratch handle)
#define FT_ESD_BITMAPHANDLE_NB 15UL
// List which bitmap info is using a handle
Ft_Esd_BitmapInfo *Ft_Esd_BitmapHandleInfo[FT_ESD_BITMAPHANDLE_NB] = { 0 };
Ft_Esd_GpuHandle Ft_Esd_BitmapHandleGpuHandle[FT_ESD_BITMAPHANDLE_NB] = { 0 };
ft_bool_t Ft_Esd_BitmapHandleUse[FT_ESD_BITMAPHANDLE_NB] = { 0 };

ft_bool_t Ft_Esd_BitmapHandleResized[FT_ESD_BITMAPHANDLE_NB] = { 0 };

void Ft_Esd_ResetGpuState() // Begin of frame
{
	Ft_Esd_GpuState_I = 0;
	Ft_Esd_GpuState[0] = (Ft_Esd_GpuState_T) {
		.ColorA = 0xFF,
		.ColorRGB = 0xFFFFFF,
		.VertexFormat = 4
	};
	for (int i = 0; i < FT_ESD_BITMAPHANDLE_NB; ++i)
	{
		// 2: In use last frame
		// 1: Not in use anymore
		// 0: Not in use
		if (Ft_Esd_BitmapHandleUse[i] < 2)
			Ft_Esd_BitmapHandleUse[i] = 0;
		else
			--Ft_Esd_BitmapHandleUse[i];
		// 2: In use this frame
		// 1: In use last frame
		// 0: Not in use
	}
}

void Ft_Esd_ResetCoState()
{
	Ft_Esd_CoFgColor = 0x003870;
	Ft_Esd_CoBgColor = 0x002040;
}

ft_uint32_t Ft_Esd_BitmapHandle_GetTotalUsed()
{
	ft_uint32_t total = 0;
	for (int i = 0; i < FT_ESD_BITMAPHANDLE_NB; ++i)
	{
		if (Ft_Esd_BitmapHandleUse[i] > 0)
		{
			++total;
		}
	}
	return total;
}

ft_uint32_t Ft_Esd_BitmapHandle_GetTotal()
{
	return FT_ESD_BITMAPHANDLE_NB;
}

void FT_Esd_Render_Rect(ft_int16_t x, ft_int16_t y, ft_int16_t w, ft_int16_t h)
{
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BEGIN(RECTS));
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, VERTEX2II(x, y, 0, 0));
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, VERTEX2II(x + w, y + h, 0, 0));
}

ft_void_t Ft_Esd_Cmd_Button(ft_int16_t x, ft_int16_t y, ft_int16_t w, ft_int16_t h, ft_int16_t font, ft_uint16_t options, const ft_char8_t* s)
{
	Ft_Gpu_CoCmd_Button(Ft_Esd_Host, x, y, w, h, font, options, s);
}

ft_void_t Ft_Esd_Cmd_Number(ft_int16_t x, ft_int16_t y, ft_int16_t font, ft_uint16_t options, ft_int32_t n)
{
	Ft_Gpu_CoCmd_Number(Ft_Esd_Host, x, y, font, options, n);
}

ft_uint8_t Ft_Esd_Dl_Bitmap_Setup(Ft_Esd_BitmapInfo *bitmapInfo)
{
	// Get bitmap address
	uint32_t addr = Ft_Esd_LoadBitmap(bitmapInfo);
	if (addr == ~0)
		return FT_ESD_BITMAPHANDLE_INVALID; // Bitmap not loaded (out of memory or file not found)

	uint32_t handle = bitmapInfo->BitmapHandle;
	if (!((handle < FT_ESD_BITMAPHANDLE_NB)
		&& (Ft_Esd_BitmapHandleInfo[handle] == bitmapInfo)
		&& (Ft_Esd_BitmapHandleGpuHandle[handle].Id == bitmapInfo->GpuHandle.Id)
		&& (Ft_Esd_BitmapHandleGpuHandle[handle].Seq == bitmapInfo->GpuHandle.Seq)))
	{
		// Bitmap is loaded but no handle is setup, create a new handle for this bitmap
		// printf("Find free bitmap handle for addr %i\n", (int)addr);

		// Find a free handle
		handle = FT_ESD_BITMAPHANDLE_NB; // Fallback to scratch handle
		for (int i = 0; i < FT_ESD_BITMAPHANDLE_NB; ++i)
		{
			if (!Ft_Esd_BitmapHandleUse[i])
			{
				// Attach this handle to the bitmap info
				handle = i;
				Ft_Esd_BitmapHandleInfo[i] = bitmapInfo;
				Ft_Esd_BitmapHandleGpuHandle[i] = bitmapInfo->GpuHandle;
				break;
			}
		}
		
		// printf("Use handle %i, addr %i, gpu alloc %i, %i, file %s\n",
		// 	(int)handle, (int)addr, (int)bitmapInfo->GpuHandle.Id, (int)bitmapInfo->GpuHandle.Seq,
		// 	bitmapInfo->File ? bitmapInfo->File : "");

		bitmapInfo->BitmapHandle = handle;
		
		// Setup the handle
		// Ft_Esd_Dl_BITMAP_HANDLE(handle);
		// Ft_Gpu_CoCmd_SetBitmap(Ft_Esd_Host, addr, bitmapInfo->Format, bitmapInfo->Width, bitmapInfo->Height); // TODO: What with stride?
	}

	// TEMPORARY WORKAROUND: SetBitmap not correctly being applied some frames... Need to check!
	Ft_Esd_Dl_BITMAP_HANDLE(handle);
	Ft_Gpu_CoCmd_SetBitmap(Ft_Esd_Host, addr, bitmapInfo->Format, bitmapInfo->Width, bitmapInfo->Height); // TODO: What with stride?
	Ft_Esd_BitmapHandleResized[handle] = 0;

	if (handle < FT_ESD_BITMAPHANDLE_NB) // When valid and not using scratch handle
	{
		Ft_Esd_BitmapHandleUse[handle] = 2; // In use
	}

	// Use palette if available
	ft_uint32_t paletteAddr = Ft_Esd_LoadPalette(bitmapInfo);
	if (paletteAddr != ~0)
	{
		Ft_Esd_Dl_PALETTE_SOURCE(paletteAddr);
	}

	return handle;
}

void Ft_Esd_Dl_Bitmap_WidthHeight(ft_uint8_t handle, ft_uint16_t width, ft_uint16_t height)
{
	Ft_Esd_Dl_BITMAP_HANDLE(handle);
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BITMAP_SIZE(NEAREST, BORDER, BORDER, width & 0x1ff, height & 0x1ff));
#ifdef FT_81X_ENABLE
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BITMAP_SIZE_H(width >> 9, height >> 9));
#endif
	Ft_Esd_BitmapHandleResized[handle] = 1;
}

void Ft_Esd_Dl_Bitmap_WidthHeight_BILINEAR(ft_uint8_t handle, ft_uint16_t width, ft_uint16_t height)
{
	Ft_Esd_Dl_BITMAP_HANDLE(handle);
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BITMAP_SIZE(BILINEAR, BORDER, BORDER, width & 0x1ff, height & 0x1ff));
#ifdef FT_81X_ENABLE
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BITMAP_SIZE_H(width >> 9, height >> 9));
#endif
	Ft_Esd_BitmapHandleResized[handle] = 1;
}

void Ft_Esd_Dl_Bitmap_WidthHeightReset(ft_uint8_t handle)
{
	if (Ft_Esd_BitmapHandleResized[handle])
	{
		Ft_Esd_BitmapInfo *bitmapInfo = Ft_Esd_BitmapHandleInfo[handle];
		Ft_Esd_Dl_Bitmap_WidthHeight(handle, bitmapInfo->Width, bitmapInfo->Height);
		Ft_Esd_BitmapHandleResized[handle] = 0;
	}
}

/* end of file */
