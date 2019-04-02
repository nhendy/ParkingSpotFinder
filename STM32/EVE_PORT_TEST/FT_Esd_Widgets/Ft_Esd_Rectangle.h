/*
This file is automatically generated
DO NOT MODIFY BY HAND
Ft_Esd_Rectangle
Header
*/

#ifndef Ft_Esd_Rectangle__H
#define Ft_Esd_Rectangle__H

#include "Ft_Esd.h"
#include "Ft_Esd_Math.h"
#include "Ft_Esd_Widget.h"

#ifndef ESD_LOGIC
#define ESD_LOGIC(name, ...)
#define ESD_ACTOR(name, ...)
#define ESD_WIDGET(name, ...)
#define ESD_UI(name, ...)
#define ESD_PAGE(name, ...)
#define ESD_APPLICATION(name, ...)
#define ESD_INPUT(name, ...)
#define ESD_OUTPUT(name, ...)
#define ESD_SLOT(name, ...)
#define ESD_SIGNAL(name, ...)
#define ESD_VARIABLE(name, ...)
#define ESD_WRITER(name, ...)
#endif

#define Ft_Esd_Rectangle_CLASSID 0x126144A2
ESD_SYMBOL(Ft_Esd_Rectangle_CLASSID, Type = esd_classid_t)

ESD_WIDGET(Ft_Esd_Rectangle, Include = "Ft_Esd_Rectangle.h", Callback, DisplayName = "ESD Rectangle Widget", Category = EsdBasicWidegts, X = 33, Y = 42, Width = 400, Height = 300)
typedef struct
{
	union
	{
		void *Owner;
		Ft_Esd_Widget Widget;
	};
	/* corner radius */
	ESD_INPUT(Radius, Type = ft_int32_t, Default = 4)
	ft_int32_t(* Radius)(void *context);
	ESD_INPUT(Color, Type = ft_argb32_t, Default = #ffffff)
	ft_argb32_t(* Color)(void *context);
} Ft_Esd_Rectangle;

void Ft_Esd_Rectangle__Initializer(Ft_Esd_Rectangle *context);

ESD_SLOT(Render)
void Ft_Esd_Rectangle_Render(Ft_Esd_Rectangle *context);

#endif /* Ft_Esd_Rectangle__H */

/* end of file */
