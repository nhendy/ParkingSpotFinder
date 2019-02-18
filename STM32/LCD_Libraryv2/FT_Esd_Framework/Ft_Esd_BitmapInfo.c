
#include "Ft_Esd_BitmapInfo.h"
#include "Ft_Esd_GpuAlloc.h"

#if defined (FT900_PLATFORM)
#	include "ff.h"
#endif

#ifndef NDEBUG
#define ESD_BITMAPINFO_DEBUG
#endif

extern Ft_Gpu_Hal_Context_t *Ft_Esd_Host;
extern Ft_Esd_GpuAlloc *Ft_Esd_GAlloc;



int load_inflate_image(ft_uint32_t address, const char *filename)
{
	Ft_Gpu_Hal_Context_t *phost = Ft_Esd_Host;

#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU) || defined(ESD_SIMULATION)

	FILE *afile;
	ft_uint32_t ftsize = 0;
	ft_uint8_t pbuff[8192];
	ft_uint16_t blocklen;

	afile = fopen(filename, "rb");		// read Binary (rb)
	if (afile == NULL)
	{
		printf("Unable to open: %s\n", filename);
		return 0;
	}
	Ft_Gpu_Hal_WrCmd32(phost, CMD_INFLATE);
	Ft_Gpu_Hal_WrCmd32(phost, address);
	fseek(afile, 0, SEEK_END);
	ftsize = ftell(afile);
	fseek(afile, 0, SEEK_SET);
	while (ftsize>0)
	{
		blocklen = ftsize>8192 ? 8192 : ftsize;
		fread(pbuff, 1, blocklen, afile);							/* copy the data into pbuff and then transfter it to command buffer */
		ftsize -= blocklen;
		Ft_Gpu_Hal_WrCmdBuf(phost, pbuff, blocklen);				/* copy data continuously into command memory */
	}
	fclose(afile);												/* close the opened jpg file */
	return 1;

#elif defined (FT900_PLATFORM)

	FRESULT fResult;
	FIL InfSrc;

	ft_int32_t blocklen, filesize;
	ft_uint32_t g_random_buffer[512L];

	fResult = f_open(&InfSrc, filename, FA_READ | FA_OPEN_EXISTING);
	if (fResult == FR_OK)
	{
		Ft_Gpu_Hal_WrCmd32(phost, CMD_INFLATE);
		Ft_Gpu_Hal_WrCmd32(phost, address);
		filesize = f_size(&InfSrc);
		while (filesize>0)
		{
			fResult = f_read(&InfSrc, g_random_buffer, 512, &blocklen);	// read a chunk of src file
			filesize -= blocklen;
			Ft_Gpu_Hal_WrCmdBuf(phost, (char *)g_random_buffer, blocklen);

		}
		f_close(&InfSrc);
		return 1;
	}
	else
	{
		printf("Unable to open file: \"%s\"\n", filename);
		return 0;
	}

#else

	return 0;

#endif
}

ft_uint32_t Ft_Esd_LoadBitmap(Ft_Esd_BitmapInfo *bitmapInfo)
{
	if (!bitmapInfo)
	{
#ifdef ESD_BITMAPINFO_DEBUG
		printf("Bitmap info is NULL\n");
#endif
		return ~0;
	}

	// Get address of specified handle
	// printf("%i: %i\n", bitmapInfo->GpuHandle.Id, bitmapInfo->GpuHandle.Seq);
	ft_uint32_t addr = Ft_Esd_GpuAlloc_Get(Ft_Esd_GAlloc, bitmapInfo->GpuHandle);
	if (addr == ~0)
	{
		if (!bitmapInfo->File)
		{
#ifdef ESD_BITMAPINFO_DEBUG
			// printf("Bitmap info file name is NULL, cannot auto-load\n");
#endif
			return ~0;
		}

		// Not loaded, load this bitmap
		bitmapInfo->GpuHandle = Ft_Esd_GpuAlloc_Alloc(Ft_Esd_GAlloc, bitmapInfo->Size, bitmapInfo->Persistent ? 0 : GA_GC_FLAG);
		addr = Ft_Esd_GpuAlloc_Get(Ft_Esd_GAlloc, bitmapInfo->GpuHandle);
		if (addr != ~0)
		{
#ifdef ESD_BITMAPINFO_DEBUG
			printf("Allocated space for bitmap\n");
#endif
			// Allocation space OK
			if (!load_inflate_image(addr, bitmapInfo->File))
			{
				// Failed to load from file
				Ft_Esd_GpuAlloc_Free(Ft_Esd_GAlloc, bitmapInfo->GpuHandle);
				addr = ~0;
			}
		}
		else
		{
#ifdef ESD_BITMAPINFO_DEBUG
			printf("Unable to allocate space for bitmap\n");
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
		printf("Bitmap info is NULL\n");
#endif
		return ~0;
	}

#ifdef FT_81X_ENABLE

	// Get palette address of specified handle
	ft_uint32_t addr = Ft_Esd_GpuAlloc_Get(Ft_Esd_GAlloc, bitmapInfo->PaletteGpuHandle);
	if (addr == ~0)
	{
		if (!bitmapInfo->PaletteFile)
		{
#ifdef ESD_BITMAPINFO_DEBUG
			// printf("Bitmap info palette file name is NULL, cannot auto-load\n");
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
			printf("Unknown palette format, cannot load\n");
			return ~0;
		}

		// Not loaded, load this bitmap palette
		bitmapInfo->PaletteGpuHandle = Ft_Esd_GpuAlloc_Alloc(Ft_Esd_GAlloc, size,bitmapInfo->Persistent ? 0 : GA_GC_FLAG);
		addr = Ft_Esd_GpuAlloc_Get(Ft_Esd_GAlloc, bitmapInfo->PaletteGpuHandle);
		if (addr != ~0)
		{
#ifdef ESD_BITMAPINFO_DEBUG
			printf("Allocated space for bitmap palette\n");
#endif
			// Allocation space OK
			if (!load_inflate_image(addr, bitmapInfo->PaletteFile))
			{
				// Failed to load from file
				Ft_Esd_GpuAlloc_Free(Ft_Esd_GAlloc, bitmapInfo->PaletteGpuHandle);
				addr = ~0;
			}
		}
		else
		{
#ifdef ESD_BITMAPINFO_DEBUG
			printf("Unable to allocate space for bitmap palette\n");
#endif
		}
	}

#else // FT_80X_ENABLE

	printf("Palette not yet implemented for FT80x\n");
	ft_uint32_taddr = ~0;

#endif

	return addr;
}

void Ft_Esd_BitmapPersist(Ft_Esd_BitmapCell *bitmapCell)
{
	if (bitmapCell)
	{
		Ft_Esd_LoadBitmap(bitmapCell->Info);
		Ft_Esd_LoadPalette(bitmapCell->Info);
	}
}

extern void Ft_Esd_Noop(void *context);

static Ft_Esd_BitmapInfo *nullInfo(void *context) { return 0; }
static ft_uint8_t nullCell(void *context) { return 0; }

void Ft_Esd_SwitchBitmapCell__Initializer(Ft_Esd_SwitchBitmapCell *context)
{
	context->Parent = 0;
	context->BitmapInfo = nullInfo;
	context->Cell = nullCell;
	context->BitmapCell.Info = 0;
	context->BitmapCell.Cell = 0;
}

Ft_Esd_BitmapCell *Ft_Esd_SwitchBitmapCell_BitmapCell(Ft_Esd_SwitchBitmapCell *context)
{
	context->BitmapCell.Info = context->BitmapInfo(context->Parent);
	context->BitmapCell.Cell = context->Cell(context->Parent);
	return &context->BitmapCell;
}

/* end of file */
