#include "Ft_Esd_CoCmd.h"
#include "FT_Esd_Dl.h"

static void *s_ActiveOwner = 0;

ft_void_t Ft_Esd_CoCmd_Spinner(void *owner, ft_int16_t x, ft_int16_t y, ft_uint16_t style, ft_uint16_t scale)
{
	s_ActiveOwner = owner;
	Ft_Esd_Dl_VERTEX_FORMAT(4);
	Ft_Gpu_CoCmd_Spinner(Ft_Esd_Host, x, y, style, scale);
}

ft_void_t Ft_Esd_CoCmd_ScreenSaver(void *owner)
{
	s_ActiveOwner = owner;
	Ft_Gpu_CoCmd_ScreenSaver(Ft_Esd_Host);
}

ft_void_t Ft_Esd_CoCmd_Sketch(void *owner, Ft_Esd_Rect16 globalRect, ft_uint32_t addr, ft_uint16_t format)
{
	s_ActiveOwner = owner;
	Ft_Gpu_CoCmd_Sketch(Ft_Esd_Host, globalRect.X, globalRect.Y, globalRect.Width, globalRect.Height, addr, format);
}

ft_void_t Ft_Esd_CoCmd_Stop(void *owner)
{
	if ((owner == s_ActiveOwner) || !owner)
	{
		Ft_Gpu_CoCmd_Stop(Ft_Esd_Host);
		s_ActiveOwner = 0;
	}
}

/* end of file */
