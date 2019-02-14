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

#ifndef FT_ESD_ELEMENTS_H
#define FT_ESD_ELEMENTS_H

#include "Ft_Esd.h"
#include "Ft_Esd_Theme.h"

// Panel element, sunken, follows the same alignment and 3D shading effect as CMD_PROGRESS and CMD_SLIDER
ESD_RENDER(Ft_Esd_Elements_PanelSunken, DisplayName = "ESD Panel Sunken", Icon = ":/icons/ui-panel.png", Category = EsdElements)
ESD_PARAMETER(color, Type = ft_rgb32_t, Default = "#151515")
ESD_PARAMETER(x, Type = ft_int16_t, Default = 0, Min = -2048, Max = 2047)
ESD_PARAMETER(y, Type = ft_int16_t, Default = 0, Min = -2048, Max = 2047)
ESD_PARAMETER(width, Type = ft_int16_t, Default = 80, Min = 0, Max = 4095)
ESD_PARAMETER(height, Type = ft_int16_t, Default = 60, Min = 0, Max = 4095)
ESD_PARAMETER(radius, Type = ft_int16_t, Default = 4, Min = 0, Max = 255)
void Ft_Esd_Elements_PanelSunken(ft_rgb32_t color, ft_int16_t x, ft_int16_t y, ft_int16_t width, ft_int16_t height, ft_int16_t radius);

// Panel element, raised, follows the same alignment and 3D shading effect as CMD_BUTTON
ESD_RENDER(Ft_Esd_Elements_PanelRaised, DisplayName = "ESD Panel Raised", Icon = ":/icons/ui-panel.png", Category = EsdElements)
ESD_PARAMETER(color, Type = ft_rgb32_t, Default = "#6b6b6b")
ESD_PARAMETER(x, Type = ft_int16_t, Default = 0, Min = -2048, Max = 2047)
ESD_PARAMETER(y, Type = ft_int16_t, Default = 0, Min = -2048, Max = 2047)
ESD_PARAMETER(width, Type = ft_int16_t, Default = 80, Min = 0, Max = 4095)
ESD_PARAMETER(height, Type = ft_int16_t, Default = 60, Min = 0, Max = 4095)
ESD_PARAMETER(radius, Type = ft_int16_t, Default = 4, Min = 0, Max = 255)
void Ft_Esd_Elements_PanelRaised(ft_rgb32_t color, ft_int16_t x, ft_int16_t y, ft_int16_t width, ft_int16_t height, ft_int16_t radius);

// Circle element, sunken, follows the same alignment and 3D shading effect as CMD_CLOCK
ESD_RENDER(Ft_Esd_Elements_CircleSunken, DisplayName = "ESD Circle Sunken", Icon = ":/icons/ui-panel.png", Category = EsdElements)
ESD_PARAMETER(color, Type = ft_rgb32_t, Default = "#151515")
ESD_PARAMETER(x, Type = ft_int16_t, Default = 0, Min = -2048, Max = 2047)
ESD_PARAMETER(y, Type = ft_int16_t, Default = 0, Min = -2048, Max = 2047)
ESD_PARAMETER(radius, Type = ft_int16_t, Default = 20, Min = 0, Max = 255)
void Ft_Esd_Elements_CircleSunken(ft_rgb32_t color, ft_int16_t x, ft_int16_t y, ft_int16_t radius);

// Circle element, raised
ESD_RENDER(Ft_Esd_Elements_CircleRaised, DisplayName = "ESD Circle Raised", Icon = ":/icons/ui-panel.png", Category = EsdElements)
ESD_PARAMETER(color, Type = ft_rgb32_t, Default = "#6b6b6b")
ESD_PARAMETER(x, Type = ft_int16_t, Default = 0, Min = -2048, Max = 2047)
ESD_PARAMETER(y, Type = ft_int16_t, Default = 0, Min = -2048, Max = 2047)
ESD_PARAMETER(radius, Type = ft_int16_t, Default = 20, Min = 0, Max = 255)
void Ft_Esd_Elements_CircleRaised(ft_rgb32_t color, ft_int16_t x, ft_int16_t y, ft_int16_t radius);

// Circle element, flat
ESD_RENDER(Ft_Esd_Elements_CircleFlat, DisplayName = "ESD Circle Flat", Icon = ":/icons/ui-panel.png", Category = EsdElements)
ESD_PARAMETER(color, Type = ft_rgb32_t, Default = "#151515")
ESD_PARAMETER(x, Type = ft_int16_t, Default = 0, Min = -2048, Max = 2047)
ESD_PARAMETER(y, Type = ft_int16_t, Default = 0, Min = -2048, Max = 2047)
ESD_PARAMETER(radius, Type = ft_int16_t, Default = 20, Min = 0, Max = 255)
void Ft_Esd_Elements_CircleFlat(ft_rgb32_t color, ft_int16_t x, ft_int16_t y, ft_int16_t radius);

ESD_FUNCTION(Ft_Esd_Char_RightTriangle, Type = char *, Category = _GroupHidden, Inline)
inline static char *Ft_Esd_Char_RightTriangle() { return "\x10"; }

ESD_FUNCTION(Ft_Esd_Char_LeftTriangle, Type = char *, Category = _GroupHidden, Inline)
inline static char *Ft_Esd_Char_LeftTriangle() { return "\x11"; }

ESD_FUNCTION(Ft_Esd_Char_UpTriangle, Type = char *, Category = _GroupHidden, Inline)
inline static char *Ft_Esd_Char_UpTriangle() { return "\x1E"; }

ESD_FUNCTION(Ft_Esd_Char_DownTriangle, Type = char *, Category = _GroupHidden, Inline)
inline static char *Ft_Esd_Char_DownTriangle() { return "\x1F"; }

// Panel element, with "raised" option
ESD_RENDER(Ft_Esd_Elements_Panel, DisplayName = "ESD Panel", Icon = ":/icons/ui-panel.png", Category = EsdElements)
ESD_PARAMETER(theme, Type = Ft_Esd_Theme *, Default = Ft_Esd_Theme_GetCurrent)
ESD_PARAMETER(x, Type = ft_int16_t, Default = 0, Min = -2048, Max = 2047)
ESD_PARAMETER(y, Type = ft_int16_t, Default = 0, Min = -2048, Max = 2047)
ESD_PARAMETER(width, Type = ft_int16_t, Default = 80, Min = 0, Max = 4095)
ESD_PARAMETER(height, Type = ft_int16_t, Default = 60, Min = 0, Max = 4095)
ESD_PARAMETER(radius, Type = ft_int16_t, Default = 4, Min = 0, Max = 255)
ESD_PARAMETER(raised, Type = ft_bool_t, Default = 0)
void Ft_Esd_Elements_Panel(Ft_Esd_Theme *theme, ft_int16_t x, ft_int16_t y, ft_int16_t width, ft_int16_t height, ft_int16_t radius, ft_bool_t raised);

// TODO: Backward compatibility feature
// Example: ESD_RENAME(Ft_Esd_Elements_PanelOld, To = Ft_Esd_Elements_PanelNew)

#endif /* FT_ESD_ELEMENTS_H */

/* end of file */ 
