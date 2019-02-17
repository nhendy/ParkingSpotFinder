/*

Copyright (C) 2016  BridgeTek Pte Ltd

THIS SOFTWARE IS PROVIDED BY BridgeTek Pte Ltd "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
BridgeTek Pte Ltd BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
OF SUBSTITUTE GOODS OR SERVICES LOSS OF USE, DATA, OR PROFITS OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Author: Jan Boon <jan.boon@kaetemi.be>

*/

#include "Ft_Esd_Elements.h"
#include "Ft_Esd_Dl.h"

#define FT_ESD_DL_END 0

#ifdef FT_81X_ENABLE
#	define VERTEX2F2(x, y) VERTEX2F((x), (y))
#else
#	define VERTEX2F2(x, y) VERTEX2F((x) << 2, (y) << 2)
#endif

extern Ft_Gpu_Hal_Context_t *Ft_Esd_Host;

void Ft_Esd_Elements_PanelSunken(ft_rgb32_t color, ft_int16_t x, ft_int16_t y, ft_int16_t width, ft_int16_t height, ft_int16_t radius)
{
	Ft_Gpu_Hal_Context_t *phost = Ft_Esd_Host;
	ft_int32_t lw = ((ft_int32_t)radius << 4) + 8;
	ft_int32_t x0 = ((ft_int32_t)x << 2) + ((ft_int32_t)radius << 2) + 4;
	ft_int32_t y0 = ((ft_int32_t)y << 2) + ((ft_int32_t)radius << 2) + 4;
	ft_int32_t x1 = ((ft_int32_t)x << 2) + ((ft_int32_t)width << 2) - 4 - ((ft_int32_t)radius << 2);
	ft_int32_t y1 = ((ft_int32_t)y << 2) + ((ft_int32_t)height << 2) - 4 - ((ft_int32_t)radius << 2);
	Ft_Gpu_Hal_WrCmd32(phost, BEGIN(RECTS));
#ifdef FT_81X_ENABLE
	Ft_Esd_Dl_VERTEX_FORMAT(2);
#endif
	Ft_Esd_Dl_COLOR_RGB(0xFFFFFF);
	Ft_Gpu_Hal_WrCmd32(phost, LINE_WIDTH(lw));
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F2(x0 + 2, y0 + 2));
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F2(x1 + 4, y1 + 4));
	Ft_Esd_Dl_COLOR_RGB(0x000000);
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F2(x0 - 5, y0 - 5));
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F2(x1 - 1, y1 - 1));
	Ft_Esd_Dl_COLOR_RGB(color);
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F2(x0 - 2, y0 - 2));
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F2(x1 + 2, y1 + 2));
#if FT_ESD_DL_END
	Ft_Gpu_Hal_WrCmd32(phost, END());
#endif
}

void Ft_Esd_Elements_PanelRaised(ft_rgb32_t color, ft_int16_t x, ft_int16_t y, ft_int16_t width, ft_int16_t height, ft_int16_t radius)
{
	Ft_Gpu_Hal_Context_t *phost = Ft_Esd_Host;
	ft_int32_t lw = ((ft_int32_t)radius << 4) + 12;
	ft_int32_t x0 = ((ft_int32_t)x << 2) + ((ft_int32_t)radius << 2) + 6;
	ft_int32_t y0 = ((ft_int32_t)y << 2) + ((ft_int32_t)radius << 2) + 6;
	ft_int32_t x1 = ((ft_int32_t)x << 2) + ((ft_int32_t)width << 2) - 6 - ((ft_int32_t)radius << 2);
	ft_int32_t y1 = ((ft_int32_t)y << 2) + ((ft_int32_t)height << 2) - 6 - ((ft_int32_t)radius << 2);
	Ft_Gpu_Hal_WrCmd32(phost, BEGIN(RECTS));
#ifdef FT_81X_ENABLE
	Ft_Esd_Dl_VERTEX_FORMAT(2);
#endif
	Ft_Esd_Dl_COLOR_RGB(0x000000);
	Ft_Gpu_Hal_WrCmd32(phost, LINE_WIDTH(lw));
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F2(x0 + 1, y0 + 1));
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F2(x1 + 7, y1 + 7));
	Ft_Esd_Dl_COLOR_RGB(0xFFFFFF);
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F2(x0 - 5, y0 - 5));
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F2(x1 + 1, y1 + 1));
	Ft_Esd_Dl_COLOR_RGB(color);
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F2(x0 - 3, y0 - 3));
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F2(x1 + 3, y1 + 3));
#if FT_ESD_DL_END
	Ft_Gpu_Hal_WrCmd32(phost, END());
#endif
}

void Ft_Esd_Elements_CircleSunken(ft_rgb32_t color, ft_int16_t x, ft_int16_t y, ft_int16_t radius)
{
	Ft_Gpu_Hal_Context_t *phost = Ft_Esd_Host;
#if 0
	// Abuse CMD_CLOCK
	Ft_Gpu_CoCmd_BgColor(phost, color);
	Ft_Gpu_CoCmd_Clock(phost, x, y, radius, OPT_NOTICKS | OPT_NOHANDS, 0, 0, 0, 0);
#else
	ft_int32_t ps = ((ft_int32_t)radius << 4);
	ft_int32_t x2 = ((ft_int32_t)x << 2);
	ft_int32_t y2 = ((ft_int32_t)y << 2);
	Ft_Gpu_Hal_WrCmd32(phost, BEGIN(FTPOINTS));
#	ifdef FT_81X_ENABLE
	Ft_Esd_Dl_VERTEX_FORMAT(2);
#	endif
	Ft_Gpu_Hal_WrCmd32(phost, POINT_SIZE(ps));
	Ft_Esd_Dl_COLOR_RGB(0xFFFFFF);
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F2(x2 + 2, y2 + 2));
	Ft_Esd_Dl_COLOR_RGB(0x000000);
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F2(x2 - 3, y2 - 3));
	Ft_Esd_Dl_COLOR_RGB(color);
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F2(x2, y2));
#	if FT_ESD_DL_END
	Ft_Gpu_Hal_WrCmd32(phost, END());
#	endif
#endif
}

void Ft_Esd_Elements_CircleRaised(ft_rgb32_t color, ft_int16_t x, ft_int16_t y, ft_int16_t radius)
{
	Ft_Gpu_Hal_Context_t *phost = Ft_Esd_Host;
	ft_int32_t ps = ((ft_int32_t)radius << 4);
	ft_int32_t x2 = ((ft_int32_t)x << 2);
	ft_int32_t y2 = ((ft_int32_t)y << 2);
	Ft_Gpu_Hal_WrCmd32(phost, BEGIN(FTPOINTS));
#ifdef FT_81X_ENABLE
	Ft_Esd_Dl_VERTEX_FORMAT(2);
#endif
	Ft_Gpu_Hal_WrCmd32(phost, POINT_SIZE(ps));
	Ft_Esd_Dl_COLOR_RGB(0x000000);
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F2(x2 + 4, y2 + 4));
	Ft_Esd_Dl_COLOR_RGB(0xFFFFFF);
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F2(x2 - 2, y2 - 2));
	Ft_Esd_Dl_COLOR_RGB(color);
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F2(x2, y2));
#if FT_ESD_DL_END
	Ft_Gpu_Hal_WrCmd32(phost, END());
#endif
}

void Ft_Esd_Elements_CircleFlat(ft_rgb32_t color, ft_int16_t x, ft_int16_t y, ft_int16_t radius)
{
	Ft_Gpu_Hal_Context_t *phost = Ft_Esd_Host;
	ft_int32_t ps = ((ft_int32_t)radius << 4);
	ft_int32_t x2 = ((ft_int32_t)x << 2);
	ft_int32_t y2 = ((ft_int32_t)y << 2);
	Ft_Gpu_Hal_WrCmd32(phost, BEGIN(FTPOINTS));
#ifdef FT_81X_ENABLE
	Ft_Esd_Dl_VERTEX_FORMAT(2);
#endif
	Ft_Gpu_Hal_WrCmd32(phost, POINT_SIZE(ps));
	Ft_Esd_Dl_COLOR_RGB(color);
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F2(x2, y2));
#if FT_ESD_DL_END
	Ft_Gpu_Hal_WrCmd32(phost, END());
#endif
}

void Ft_Esd_Elements_Panel(Ft_Esd_Theme *theme, ft_int16_t x, ft_int16_t y, ft_int16_t width, ft_int16_t height, ft_int16_t radius, ft_bool_t raised)
{
	if (!theme) theme = Ft_Esd_Theme_GetCurrent();
	if (raised) Ft_Esd_Elements_PanelRaised(theme->DefaultColor, x, y, width, height, radius);
	else Ft_Esd_Elements_PanelSunken(theme->BackColor, x, y, width, height, radius);
}

/* end of file */
