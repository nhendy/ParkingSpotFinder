
#ifndef FT_ESD_THEME_H
#define FT_ESD_THEME_H
#include "FT_DataTypes.h"
#include "Ft_Esd.h"

ESD_CATEGORY(EsdTheme, DisplayName = "ESD Theme")
ESD_CATEGORY(EsdTheme_Themes, DisplayName = "Themes", Category = EsdTheme)

typedef unsigned int ft_uint32_t;

typedef struct
{
	ft_rgb32_t ClearColor;
	ft_rgb32_t BackColor;
	ft_rgb32_t TextColor;
	ft_rgb32_t ButtonTextColor;
	ft_rgb32_t DefaultColor;
	ft_rgb32_t PrimaryColor;
} Ft_Esd_Theme;

ESD_TYPE(Ft_Esd_Theme *, Native = Pointer, Edit = Library)

ESD_RENDER(Ft_Esd_Theme_SetCurrent, DisplayName = "Set Current Theme", Category = EsdTheme, Include = "Ft_Esd_Theme.h", Icon = ":/icons/palette--arrow.png")
ESD_PARAMETER(theme, Type = Ft_Esd_Theme *)
void Ft_Esd_Theme_SetCurrent(Ft_Esd_Theme *theme);

ESD_FUNCTION(Ft_Esd_Theme_GetCurrent, DisplayName = "Current Theme", Category = EsdTheme, Type = Ft_Esd_Theme *, Include = "Ft_Esd_Theme.h", Icon = ":/icons/palette.png")
Ft_Esd_Theme *Ft_Esd_Theme_GetCurrent();

ESD_FUNCTION(Ft_Esd_Theme_GetClearColor, DisplayName = "Get Clear Color", Category = EsdTheme, Type = ft_rgb32_t, Include = "Ft_Esd_Theme.h", Icon = ":/icons/palette-paint-brush.png", Inline)
ESD_PARAMETER(theme, Type = Ft_Esd_Theme *, Default = Ft_Esd_Theme_GetCurrent)
inline static ft_rgb32_t Ft_Esd_Theme_GetClearColor(Ft_Esd_Theme *theme) { if (!theme) return Ft_Esd_Theme_GetCurrent()->ClearColor; return theme->ClearColor; }

ESD_FUNCTION(Ft_Esd_Theme_GetBackColor, DisplayName = "Get Back Color", Category = EsdTheme, Type = ft_rgb32_t, Include = "Ft_Esd_Theme.h", Icon = ":/icons/palette-paint-brush.png", Inline)
ESD_PARAMETER(theme, Type = Ft_Esd_Theme *, Default = Ft_Esd_Theme_GetCurrent)
inline static ft_rgb32_t Ft_Esd_Theme_GetBackColor(Ft_Esd_Theme *theme) { if (!theme) return Ft_Esd_Theme_GetCurrent()->BackColor;  return theme->BackColor; }

ESD_FUNCTION(Ft_Esd_Theme_GetTextColor, DisplayName = "Get Text Color", Category = EsdTheme, Type = ft_rgb32_t, Include = "Ft_Esd_Theme.h", Icon = ":/icons/palette-paint-brush.png", Inline)
ESD_PARAMETER(theme, Type = Ft_Esd_Theme *, Default = Ft_Esd_Theme_GetCurrent)
inline static ft_rgb32_t Ft_Esd_Theme_GetTextColor(Ft_Esd_Theme *theme) { if (!theme) return Ft_Esd_Theme_GetCurrent()->TextColor; return theme->TextColor; }

ESD_FUNCTION(Ft_Esd_Theme_GetButtonTextColor, DisplayName = "Get Button Text Color", Category = EsdTheme, Type = ft_rgb32_t, Include = "Ft_Esd_Theme.h", Icon = ":/icons/palette-paint-brush.png", Inline)
ESD_PARAMETER(theme, Type = Ft_Esd_Theme *, Default = Ft_Esd_Theme_GetCurrent)
inline static ft_rgb32_t Ft_Esd_Theme_GetButtonTextColor(Ft_Esd_Theme *theme) { if (!theme) return Ft_Esd_Theme_GetCurrent()->ButtonTextColor; return theme->ButtonTextColor; }

ESD_FUNCTION(Ft_Esd_Theme_GetCurrentColor, DisplayName = "Get Default Color", Category = EsdTheme, Type = ft_rgb32_t, Include = "Ft_Esd_Theme.h", Icon = ":/icons/palette-paint-brush.png", Inline)
ESD_PARAMETER(theme, Type = Ft_Esd_Theme *, Default = Ft_Esd_Theme_GetCurrent)
inline static ft_rgb32_t Ft_Esd_Theme_GetCurrentColor(Ft_Esd_Theme *theme) { if (!theme) return Ft_Esd_Theme_GetCurrent()->DefaultColor; return theme->DefaultColor; }

ESD_FUNCTION(Ft_Esd_Theme_GetPrimaryColor, DisplayName = "Get Primary Color", Category = EsdTheme, Type = ft_rgb32_t, Include = "Ft_Esd_Theme.h", Icon = ":/icons/palette-paint-brush.png", Inline)
ESD_PARAMETER(theme, Type = Ft_Esd_Theme *, Default = Ft_Esd_Theme_GetCurrent)
inline static ft_rgb32_t Ft_Esd_Theme_GetPrimaryColor(Ft_Esd_Theme *theme) { if (!theme) return Ft_Esd_Theme_GetCurrent()->PrimaryColor; return theme->PrimaryColor; }

#endif

/* Nothing beyond this */
