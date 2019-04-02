/*
Bitmap info structure
*/

#ifndef FT_ESD_BITMAPINFO_H
#define FT_ESD_BITMAPINFO_H

#include "Ft_Esd.h"
#include "Ft_Esd_GpuAlloc.h"

ESD_TYPE(Ft_Esd_BitmapInfo, Native = Struct) // TODO: Struct support, expose values
typedef struct Ft_Esd_BitmapInfo
{
	ft_int32_t Width;
	ft_int32_t Height;
	ft_int32_t Stride;
	ft_int32_t Format;
	ft_int32_t Size;
	const char *File;

	// Handle pointing to the address in RAM_G if it is allocated
	Ft_Esd_GpuHandle GpuHandle;

	// Bitmap handle that is being used
	ft_uint32_t BitmapHandle;

	// Used for paletted format
	const char *PaletteFile;
	Ft_Esd_GpuHandle PaletteGpuHandle;
	
	// Used for DXT1 format
	const char *AdditionalFile;
	struct Ft_Esd_BitmapInfo *AdditionalInfo;

	// Load file from compressed format
	ft_bool_t Compressed;

	// When this is set, the allocated ram is not free'd automatically
	// Use Ft_Esd_GpuAlloc_Free(GpuAlloc, GpuHandle) to free the GPU ram manually
	ft_bool_t Persistent;

	// Number of cells usable by the user. There may be additional internally used cells after this
	ft_uint16_t Cells;

} Ft_Esd_BitmapInfo;

ESD_TYPE(Ft_Esd_BitmapInfo *, Native = Pointer, Edit = Library)

ESD_TYPE(Ft_Esd_BitmapCell, Native = Struct, Edit = Library) // TODO: Struct support, expose values
typedef struct
{
	Ft_Esd_BitmapInfo *Info;
	ft_int32_t Cell;
} Ft_Esd_BitmapCell;

ESD_TYPE(Ft_Esd_BitmapCell *, Native = Pointer, Edit = Library)

//A function to load bitmap data(not including palette data) into RAM_G
ESD_FUNCTION(Ft_Esd_LoadBitmap, Type = ft_uint32_t, Include = "Ft_Esd_BitmapInfo.h", DisplayName = "Load Bitmap to RAM_G", Category = EsdUtilities)
ESD_PARAMETER(bitmapInfo, Type = Ft_Esd_BitmapInfo *)
ft_uint32_t Ft_Esd_LoadBitmap(Ft_Esd_BitmapInfo *bitmapInfo);

//A function to load palette data of bitmap into RAM_G 
ESD_FUNCTION(Ft_Esd_LoadPalette, Type = ft_uint32_t, Include = "Ft_Esd_BitmapInfo.h", DisplayName = "Load Palette to RAM_G", Category = EsdUtilities)
ESD_PARAMETER(bitmapInfo, Type = Ft_Esd_BitmapInfo *)
ft_uint32_t Ft_Esd_LoadPalette(Ft_Esd_BitmapInfo *bitmapInfo);

ESD_ENUM(_BitmapResourceFormat, DisplayName = "Bitmap Format")
// Hardware bitmap formats
ESD_IDENTIFIER(ARGB1555)
ESD_IDENTIFIER(L1)
ESD_IDENTIFIER(L2)
ESD_IDENTIFIER(L4)
ESD_IDENTIFIER(L8)
ESD_IDENTIFIER(RGB332)
ESD_IDENTIFIER(ARGB2)
ESD_IDENTIFIER(ARGB4)
ESD_IDENTIFIER(RGB565)
ESD_IDENTIFIER(PALETTED565)
ESD_IDENTIFIER(PALETTED4444)
ESD_IDENTIFIER(PALETTED8)
// Specially loaded bitmap formats
#define DXT1 0x81
#define JPEG 0x91
#define PNG 0x92
ESD_END()

// Switch bitmap cell number
ESD_FUNCTION(Ft_Esd_SwitchBitmapCell, Type = Ft_Esd_BitmapCell, DisplayName = "Switch Bitmap Cell", Category = EsdUtilities)
ESD_PARAMETER(BitmapInfo, Type = Ft_Esd_BitmapCell, DisplayName = "Bitmap Cell")
ESD_PARAMETER(Cell, Type = ft_uint16_t, DisplayName = "Cell")
Ft_Esd_BitmapCell Ft_Esd_SwitchBitmapCell(Ft_Esd_BitmapCell bitmapCell, ft_uint16_t cell);

//A function to make bitmap persistant in memory by reloading the data, called during the Update cycle of each frame
ESD_UPDATE(Ft_Esd_BitmapPersist, DisplayName = "Bitmap Persist", Category = EsdUtilities)
ESD_PARAMETER(bitmapCell, Type = Ft_Esd_BitmapCell)
void Ft_Esd_BitmapPersist(Ft_Esd_BitmapCell bitmapCell);

//A function to get bitmap information structure from bitmap cell 
ESD_FUNCTION(Ft_Esd_BitmapCell_GetInfo, Type = Ft_Esd_BitmapInfo *, DisplayName = "ESD BitmapCell GetInfo", Category = EsdUtilities, Inline)
ESD_PARAMETER(bitmapCell, Type = Ft_Esd_BitmapCell)
static Ft_Esd_BitmapInfo *Ft_Esd_BitmapCell_GetInfo(Ft_Esd_BitmapCell bitmapCell)
{
	return bitmapCell.Info;
}
//A function to get the bitmap width from bitmap information
ESD_FUNCTION(Ft_Esd_BitmapInfo_GetWidth, Type = ft_int32_t, DisplayName = "ESD BitmapInfo GetWidth", Category = EsdUtilities, Inline)
ESD_PARAMETER(bitmapInfo, Type = Ft_Esd_BitmapInfo *)
static inline ft_int32_t Ft_Esd_BitmapInfo_GetWidth(Ft_Esd_BitmapInfo *bitmapInfo)
{
	if (!bitmapInfo) return 1;
	return bitmapInfo->Width;
}

//A function to get the bitmap height from bitmap information
ESD_FUNCTION(Ft_Esd_BitmapInfo_GetHeight, Type = ft_int32_t, DisplayName = "ESD BitmapInfo GetHeight", Category = EsdUtilities, Inline)
ESD_PARAMETER(bitmapInfo, Type = Ft_Esd_BitmapInfo *)
static inline ft_int32_t Ft_Esd_BitmapInfo_GetHeight(Ft_Esd_BitmapInfo *bitmapInfo)
{
	if (!bitmapInfo) return 1;
	return bitmapInfo->Height;
}

#endif /* #ifndef FT_ESD_BITMAPINFO_H */

/* end of file */
