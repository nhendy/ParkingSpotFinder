
#include "FT_Platform.h"
#include "FT_Gpu_Hal.h"
#include "FT_Esd_Primitives.h"
#include "FT_Esd_Dl.h"

extern Ft_Gpu_Hal_Context_t *Ft_Esd_Host;

#define FT_ESD_DL_END 0

// Rectangle drawing with some logic to convert from radius to line width and width height to positions to simplify usage
ft_void_t Ft_Esd_Render_RectangleF(ft_int32_f4_t x, ft_int32_f4_t y, ft_int32_f4_t w, ft_int32_f4_t h, ft_int32_f4_t radius, ft_argb32_t color)
{
	Ft_Gpu_Hal_Context_t *phost = Ft_Esd_Host;
	ft_int32_t width = radius + 8;
	ft_int32_t x0 = x + radius;
	ft_int32_t y0 = y + radius;
	ft_int32_t x1 = x + w - 16 - radius;
	ft_int32_t y1 = y + h - 16 - radius;
	Ft_Esd_Dl_COLOR_ARGB(color);
	Ft_Esd_Dl_LINE_WIDTH(width);
	Ft_Gpu_Hal_WrCmd32(phost, BEGIN(RECTS));
#ifdef FT_81X_ENABLE
	Ft_Esd_Dl_VERTEX_FORMAT(4);
#endif
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(x0, y0));
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(x1, y1));
#if FT_ESD_DL_END
	Ft_Gpu_Hal_WrCmd32(phost, END());
#endif
}

ft_void_t Ft_Esd_Render_LineF(ft_int32_f4_t x0, ft_int32_f4_t y0, ft_int32_f4_t x1, ft_int32_f4_t y1, ft_int32_f3_t width, ft_argb32_t color)
{
	Ft_Gpu_Hal_Context_t *phost = Ft_Esd_Host;
	Ft_Esd_Dl_COLOR_ARGB(color);
	Ft_Esd_Dl_LINE_WIDTH(width);
	Ft_Gpu_Hal_WrCmd32(phost, BEGIN(LINES));
#ifdef FT_81X_ENABLE
	Ft_Esd_Dl_VERTEX_FORMAT(4);
#endif
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(x0, y0));
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(x1, y1));
#if FT_ESD_DL_END
	Ft_Gpu_Hal_WrCmd32(phost, END());
#endif
}

void Ft_Esd_Render_Bitmap(ft_int16_t x, ft_int16_t y, Ft_Esd_BitmapCell *bitmapCell, ft_argb32_t c)
{
	if (!bitmapCell || !bitmapCell->Info)
		return;

	Ft_Esd_BitmapInfo *bitmapInfo = bitmapCell->Info;
	ft_uint8_t cell = bitmapCell->Cell;
	Ft_Gpu_Hal_Context_t *phost = Ft_Esd_Host;
	ft_uint8_t handle = Ft_Esd_Dl_Bitmap_Setup(bitmapInfo);
	if (handle != FT_ESD_BITMAPHANDLE_INVALID)
	{
		Ft_Esd_Dl_Bitmap_WidthHeightReset(handle);
		Ft_Esd_Dl_COLOR_ARGB(c);
		Ft_Gpu_Hal_WrCmd32(phost, BEGIN(BITMAPS));
#ifdef FT_81X_ENABLE
		if (x < 0 || y < 0 || x >= 512 || y >= 512)
		{
			Ft_Esd_Dl_VERTEX_FORMAT(0);
			Ft_Esd_Dl_BITMAP_HANDLE(handle);
			Ft_Esd_Dl_CELL(cell);
			Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(x, y));
		}
		else
#endif
		{
			Ft_Gpu_Hal_WrCmd32(phost, VERTEX2II(x, y, handle, cell));
		}
	}
}

ft_void_t Ft_Esd_Render_BitmapScaled(ft_int16_t x, ft_int16_t y, Ft_Esd_BitmapCell *bitmapCell, ft_argb32_t c, ft_int32_f16_t xscale, ft_int32_f16_t yscale, ft_int32_f16_t xoffset, ft_int32_f16_t yoffset, ft_int16_t width, ft_int16_t height)
{
	if (!bitmapCell || !bitmapCell->Info)
		return;

	Ft_Esd_BitmapInfo *bitmapInfo = bitmapCell->Info;
	ft_uint8_t cell = bitmapCell->Cell;
	Ft_Gpu_Hal_Context_t *phost = Ft_Esd_Host;
	ft_uint8_t handle = Ft_Esd_Dl_Bitmap_Setup(bitmapInfo);

	if (handle != FT_ESD_BITMAPHANDLE_INVALID)
	{
		Ft_Esd_Dl_Bitmap_WidthHeight(handle, width, height);
		Ft_Esd_Dl_COLOR_ARGB(c);
		Ft_Esd_Dl_SAVE_CONTEXT();
		Ft_Gpu_CoCmd_Translate(Ft_Esd_Host, xoffset, yoffset);
		Ft_Gpu_CoCmd_Scale(Ft_Esd_Host, xscale, yscale);
		Ft_Gpu_CoCmd_SetMatrix(Ft_Esd_Host);
		Ft_Gpu_Hal_WrCmd32(phost, BEGIN(BITMAPS));
#ifdef FT_81X_ENABLE
		if (x < 0 || y < 0 || x >= 512 || y >= 512)
		{
			Ft_Esd_Dl_VERTEX_FORMAT(0);
			Ft_Esd_Dl_BITMAP_HANDLE(handle);
			Ft_Esd_Dl_CELL(cell);
			Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(x, y));
		}
		else
#endif
		{
			Ft_Gpu_Hal_WrCmd32(phost, VERTEX2II(x, y, handle, cell));
		}
		Ft_Gpu_CoCmd_LoadIdentity(Ft_Esd_Host);
		Ft_Esd_Dl_RESTORE_CONTEXT();
	}
}



ft_void_t Ft_Esd_Render_BitmapRotate(ft_int16_t x, ft_int16_t y, Ft_Esd_BitmapCell *bitmapCell, ft_argb32_t c, ft_int32_t rotateEffi, ft_int32_f16_t x_center, ft_int32_f16_t y_center, ft_int16_t width, ft_int16_t height,ft_int16_t radius)
{
	if (!bitmapCell || !bitmapCell->Info)
		return;

	Ft_Esd_BitmapInfo *bitmapInfo = bitmapCell->Info;
	ft_uint8_t cell = bitmapCell->Cell;
	Ft_Gpu_Hal_Context_t *phost = Ft_Esd_Host;
	ft_uint8_t handle = Ft_Esd_Dl_Bitmap_Setup(bitmapInfo);
    
    
    ft_int32_t translate_pixels = 2*bitmapInfo->Width*65536;

	if (handle != FT_ESD_BITMAPHANDLE_INVALID)	
    {
        
#if 1        
        int tilenumber = 0;
        const int TITLE_SIZE = 64;//Magic number, DONOT CHANGE
        Ft_Esd_Dl_SAVE_CONTEXT();
        Ft_Esd_Dl_COLOR_ARGB(c);
        
        Ft_Esd_Dl_Bitmap_WidthHeight_BILINEAR(handle, TITLE_SIZE, TITLE_SIZE);//Bitmap_Size command
        
        Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BEGIN(BITMAPS));
        
#ifdef FT_81X_ENABLE      
        Ft_Esd_Dl_VERTEX_FORMAT(4);
#endif        
        Ft_Esd_Dl_BITMAP_HANDLE(handle);
        for (int dx = (x - radius); dx < (x + radius); dx += TITLE_SIZE){
            for (int dy = (y - radius); dy < (y + radius); dy += TITLE_SIZE){
                //printf("draw tile %d\n",tilenumber ++);
                tilenumber ++;
                Ft_Gpu_CoCmd_LoadIdentity(Ft_Esd_Host);
                Ft_Gpu_CoCmd_Translate(Ft_Esd_Host, (x - dx) << 16, (y - dy) << 16);

                Ft_Gpu_CoCmd_Rotate(Ft_Esd_Host,rotateEffi);
                //Ft_Gpu_CoCmd_Translate(Ft_Esd_Host, -x_center << 16, -y_center << 16);
                Ft_Gpu_CoCmd_Translate(Ft_Esd_Host, -x_center, -y_center);
                
                Ft_Gpu_CoCmd_SetMatrix(Ft_Esd_Host);
                Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, VERTEX2F(dx*16, dy*16));
            }
        }
        //printf("draw tile %d\n",tilenumber);
        Ft_Gpu_CoCmd_LoadIdentity(Ft_Esd_Host);
        Ft_Esd_Dl_RESTORE_CONTEXT();    

#endif        
#if 0        
		Ft_Esd_Dl_Bitmap_WidthHeight_BILINEAR(handle, width, height);//Bitmap_Size command
		Ft_Esd_Dl_COLOR_ARGB(c);
		Ft_Esd_Dl_SAVE_CONTEXT();
        
        if (bitmapInfo->Width < bitmapInfo->Height)
            translate_pixels = 2*bitmapInfo->Height*65536;
        
                  
            
        Ft_Gpu_CoCmd_LoadIdentity(Ft_Esd_Host);
		Ft_Gpu_CoCmd_Translate(Ft_Esd_Host, radius << 16, radius << 16);
        //printf("xoffset = 0x%x",xoffset);
        //printf(" yoffset = 0x%x\n",yoffset);
        
		//Ft_Gpu_CoCmd_Scale(Ft_Esd_Host, xscale, yscale);
        Ft_Gpu_CoCmd_Rotate(Ft_Esd_Host,rotateEffi);
        
        //printf("rotateEffi=%d\n", rotateEffi);
        
        //printf("-xoffset = 0x%x",-xoffset);
        //printf(" -yoffset = 0x%x\n",-yoffset);
        
		Ft_Gpu_CoCmd_Translate(Ft_Esd_Host, -x_center, -y_center);
        
        Ft_Gpu_CoCmd_SetMatrix(Ft_Esd_Host);
        
		Ft_Gpu_Hal_WrCmd32(phost, BEGIN(BITMAPS));
#ifdef FT_81X_ENABLE
		if (x < 0 || y < 0 || x >= 512 || y >= 512)
		{
			Ft_Esd_Dl_VERTEX_FORMAT(0);
			Ft_Esd_Dl_BITMAP_HANDLE(handle);
			Ft_Esd_Dl_CELL(cell);
			Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(x, y));
		}
		else
#endif
		{
			Ft_Gpu_Hal_WrCmd32(phost, VERTEX2II(x, y, handle, cell));
		}
		Ft_Gpu_CoCmd_LoadIdentity(Ft_Esd_Host);
		Ft_Esd_Dl_RESTORE_CONTEXT();
        
#endif          
	}  
}

/* end of file */
