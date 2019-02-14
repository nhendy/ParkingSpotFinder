/*
Bitmap info structure
*/

#ifndef FT_ESD_BITMAPINFO_H
#define FT_ESD_BITMAPINFO_H

#include "Ft_Esd.h"
#include "FT_DataTypes.h"
#include "Ft_Esd_GpuAlloc.h"

ESD_TYPE(Ft_Esd_BitmapInfo, Native = Struct) // TODO: Struct support, expose values
typedef struct
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

	const char *PaletteFile;
	Ft_Esd_GpuHandle PaletteGpuHandle;

	// When this is set, the allocated ram is not free'd automatically
	// Use Ft_Esd_GpuAlloc_Free(GpuAlloc, GpuHandle) to free the GPU ram manually
	ft_bool_t Persistent;

} Ft_Esd_BitmapInfo;

ESD_TYPE(Ft_Esd_BitmapInfo *, Native = Pointer, Edit = Library)

ESD_TYPE(Ft_Esd_BitmapCell, Native = Struct) // TODO: Struct support, expose values
typedef struct
{
	Ft_Esd_BitmapInfo *Info;
	ft_int32_t Cell;
} Ft_Esd_BitmapCell;

ESD_TYPE(Ft_Esd_BitmapCell *, Native = Pointer, Edit = Library)

// Attempts to load the specified bitmap if it has not been loaded into RAM_G yet.
// Call during the Update cycle of each frame to keep the bitmap flagged as in use, otherwise the memory allocator may wipe the allocation from RAM.
ESD_FUNCTION(Ft_Esd_LoadBitmap, Type = ft_uint32_t, Include = "Ft_Esd_BitmapInfo.h", DisplayName = "Load Bitmap to RAM_G", Category = EsdUtilities)
ESD_PARAMETER(bitmapInfo, Type = Ft_Esd_BitmapInfo *)
ft_uint32_t Ft_Esd_LoadBitmap(Ft_Esd_BitmapInfo *bitmapInfo);

ESD_FUNCTION(Ft_Esd_LoadPalette, Type = ft_uint32_t, Include = "Ft_Esd_BitmapInfo.h", DisplayName = "Load Palette to RAM_G", Category = EsdUtilities)
ESD_PARAMETER(bitmapInfo, Type = Ft_Esd_BitmapInfo *)
ft_uint32_t Ft_Esd_LoadPalette(Ft_Esd_BitmapInfo *bitmapInfo);

ESD_ENUM(_BitmapResourceFormat, DisplayName = "Bitmap Format")
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
// ESD_IDENTIFIER(PALETTED8)
// ESD_IDENTIFIER(JPEG)
// ESD_IDENTIFIER(PNG)
ESD_END()

ESD_LOGIC(Ft_Esd_SwitchBitmapCell, Callback, Include = "Ft_Esd_BitmapInfo.h", DisplayName = "Switch Bitmap Cell", Category = EsdUtilities, Compact)
typedef struct
{
	// Callback
	void *Parent;

	//
	// Input
	//

	ESD_INPUT(BitmapInfo, Type = Ft_Esd_BitmapInfo *, DisplayName = "Bitmap Info")
	Ft_Esd_BitmapInfo *(* BitmapInfo)(void *context);

	ESD_INPUT(Cell, Type = ft_uint8_t, DisplayName = "Cell")
	ft_uint8_t(* Cell)(void *context);

	//
	// Variables
	//

	// BitmapCell object
	Ft_Esd_BitmapCell BitmapCell;

} Ft_Esd_SwitchBitmapCell;

void Ft_Esd_SwitchBitmapCell__Initializer(Ft_Esd_SwitchBitmapCell *context);

ESD_OUTPUT(BitmapCell, Type = Ft_Esd_BitmapCell *, DisplayName = "Bitmap Cell")
Ft_Esd_BitmapCell *Ft_Esd_SwitchBitmapCell_BitmapCell(Ft_Esd_SwitchBitmapCell *context);

ESD_UPDATE(Ft_Esd_BitmapPersist, DisplayName = "Bitmap Persist", Category = EsdUtilities)
ESD_PARAMETER(bitmapCell, Type = Ft_Esd_BitmapCell *)
void Ft_Esd_BitmapPersist(Ft_Esd_BitmapCell *bitmapCell);

ESD_FUNCTION(Ft_Esd_BitmapCell_GetInfo, Type = Ft_Esd_BitmapInfo *, DisplayName = "ESD BitmapCell GetInfo", Category = EsdUtilities, Inline)
ESD_PARAMETER(bitmapCell, Type = Ft_Esd_BitmapCell *)
static Ft_Esd_BitmapInfo *Ft_Esd_BitmapCell_GetInfo(Ft_Esd_BitmapCell *bitmapCell)
{
	if (!bitmapCell) return 0;
	return bitmapCell->Info;
}

ESD_FUNCTION(Ft_Esd_BitmapInfo_GetWidth, Type = ft_int32_t, DisplayName = "ESD BitmapInfo GetWidth", Category = EsdUtilities, Inline)
ESD_PARAMETER(bitmapInfo, Type = Ft_Esd_BitmapInfo *)
static inline ft_int32_t Ft_Esd_BitmapInfo_GetWidth(Ft_Esd_BitmapInfo *bitmapInfo)
{
	if (!bitmapInfo) return 1;
	return bitmapInfo->Width;
}

ESD_FUNCTION(Ft_Esd_BitmapInfo_GetHeight, Type = ft_int32_t, DisplayName = "ESD BitmapInfo GetHeight", Category = EsdUtilities, Inline)
ESD_PARAMETER(bitmapInfo, Type = Ft_Esd_BitmapInfo *)
static inline ft_int32_t Ft_Esd_BitmapInfo_GetHeight(Ft_Esd_BitmapInfo *bitmapInfo)
{
	if (!bitmapInfo) return 1;
	return bitmapInfo->Height;
}

#endif /* #ifndef FT_ESD_BITMAPINFO_H */

/* end of file */
