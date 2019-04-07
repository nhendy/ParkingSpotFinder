
//#include "FT_LoadFile.h"
#include "Ft_Esd_BitmapInfo.h"
#include "Ft_Esd_GpuAlloc.h"

#ifndef NDEBUG
#define ESD_BITMAPINFO_DEBUG
#endif

extern Ft_Gpu_Hal_Context_t *Ft_Esd_Host;
extern Ft_Esd_GpuAlloc *Ft_Esd_GAlloc;

ft_uint32_t Ft_Esd_LoadBitmap(Ft_Esd_BitmapInfo *bitmapInfo)
{
	if (!bitmapInfo)
	{
#ifdef ESD_BITMAPINFO_DEBUG
		ESD_print("Bitmap info is NULL\n");
#endif
		return ~0;
	}

	// Get address of specified handle
	// ESD_print("%i: %i\n", bitmapInfo->GpuHandle.Id, bitmapInfo->GpuHandle.Seq);
	ft_uint32_t addr = Ft_Esd_GpuAlloc_Get(Ft_Esd_GAlloc, bitmapInfo->GpuHandle);
	if (addr == ~0)
	{
		if (!bitmapInfo->File)
		{
#ifdef ESD_BITMAPINFO_DEBUG
			// ESD_print("Bitmap info file name is NULL, cannot auto-load\n");
#endif
			return ~0;
		}

		// Not loaded, load this bitmap
		bitmapInfo->GpuHandle = Ft_Esd_GpuAlloc_Alloc(Ft_Esd_GAlloc, bitmapInfo->Size, bitmapInfo->Persistent ? 0 : GA_GC_FLAG);
		addr = Ft_Esd_GpuAlloc_Get(Ft_Esd_GAlloc, bitmapInfo->GpuHandle);
		if (addr != ~0)
		{
#ifdef ESD_BITMAPINFO_DEBUG
			ESD_print("Allocated space for bitmap\n");
#endif
			int loadimage = bitmapInfo->Format == JPEG || bitmapInfo->Format == PNG;

			// Allocation space OK
			if (loadimage
				? !Ft_Hal_LoadImageFile(Ft_Esd_Host, addr, bitmapInfo->File)
				: (bitmapInfo->Compressed
					? !Ft_Hal_LoadInflateFile(Ft_Esd_Host, addr, bitmapInfo->File)
					: !Ft_Hal_LoadRawFile(Ft_Esd_Host, addr, bitmapInfo->File)))
			{
#ifdef ESD_BITMAPINFO_DEBUG
				ESD_print("Failed to load bitmap from file\n");
#endif
				// Failed to load from file
				Ft_Esd_GpuAlloc_Free(Ft_Esd_GAlloc, bitmapInfo->GpuHandle);
				addr = ~0;
			}
			
			// Special load for DXT1, additional file loaded halfway the address space
			if (bitmapInfo->AdditionalFile)
			{
				if (loadimage
					? !Ft_Hal_LoadImageFile(Ft_Esd_Host, addr + (bitmapInfo->Size >> 1), bitmapInfo->AdditionalFile)
					: (bitmapInfo->Compressed
						? !Ft_Hal_LoadInflateFile(Ft_Esd_Host, addr + (bitmapInfo->Size >> 1), bitmapInfo->AdditionalFile)
						: !Ft_Hal_LoadRawFile(Ft_Esd_Host, addr + (bitmapInfo->Size >> 1), bitmapInfo->AdditionalFile)))
				{
					// Failed to load from additional file
					// Ft_Esd_GpuAlloc_Free(Ft_Esd_GAlloc, bitmapInfo->GpuHandle);
					addr = ~0;
				}
			}
		}
		else
		{
#ifdef ESD_BITMAPINFO_DEBUG
			ESD_print("Unable to allocate space for bitmap\n");
#endif
		}
	}
	
	return addr;
}

ft_uint32_t Ft_Esd_LoadPalette(Ft_Esd_BitmapInfo *bitmapInfo)
{
	if (!bitmapInfo)
	{
#ifdef ESD_BITMAPINFO_DEBUG
		ESD_print("Bitmap info is NULL\n");
#endif
		return ~0;
	}

#if (BT_EVE_MODEL >= 0x0810)

	// Get palette address of specified handle
	ft_uint32_t addr = Ft_Esd_GpuAlloc_Get(Ft_Esd_GAlloc, bitmapInfo->PaletteGpuHandle);
	if (addr == ~0)
	{
		if (!bitmapInfo->PaletteFile)
		{
#ifdef ESD_BITMAPINFO_DEBUG
			// ESD_print("Bitmap info palette file name is NULL, cannot auto-load\n");
#endif
			return ~0;
		}

		ft_uint32_t size;
		switch (bitmapInfo->Format)
		{
		case PALETTED8: size = 256 * 4; break;
		case PALETTED4444: size = 256 * 2; break;
		case PALETTED565: size = 256 * 2; break;
		default:
			ESD_print("Unknown palette format, cannot load\n");
			return ~0;
		}

		// Not loaded, load this bitmap palette
		bitmapInfo->PaletteGpuHandle = Ft_Esd_GpuAlloc_Alloc(Ft_Esd_GAlloc, size,bitmapInfo->Persistent ? 0 : GA_GC_FLAG);
		addr = Ft_Esd_GpuAlloc_Get(Ft_Esd_GAlloc, bitmapInfo->PaletteGpuHandle);
		if (addr != ~0)
		{
#ifdef ESD_BITMAPINFO_DEBUG
			ESD_print("Allocated space for bitmap palette\n");
#endif
			// Allocation space OK
			if (!Ft_Hal_LoadRawFile(Ft_Esd_Host, addr, bitmapInfo->PaletteFile))
			{
				// Failed to load from file
				Ft_Esd_GpuAlloc_Free(Ft_Esd_GAlloc, bitmapInfo->PaletteGpuHandle);
				addr = ~0;
			}
		}
		else
		{
#ifdef ESD_BITMAPINFO_DEBUG
			ESD_print("Unable to allocate space for bitmap palette\n");
#endif
		}
	}

#else // FT_80X_ENABLE

	ESD_print("Palette not yet implemented for FT80x\n");
	ft_uint32_t addr = ~0;

#endif

	return addr;
}

Ft_Esd_BitmapCell Ft_Esd_SwitchBitmapCell(Ft_Esd_BitmapCell bitmapCell, ft_uint16_t cell)
{
	bitmapCell.Cell = cell;
	return bitmapCell;
}

void Ft_Esd_BitmapPersist(Ft_Esd_BitmapCell bitmapCell)
{
	if (bitmapCell.Info)
	{
		Ft_Esd_LoadBitmap(bitmapCell.Info);
		Ft_Esd_LoadPalette(bitmapCell.Info);
	}
}

/* end of file */
