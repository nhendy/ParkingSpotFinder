/*
This file is automatically generated
DO NOT MODIFY BY HAND
Ft_Esd_Layout_Stretch
Header
*/

#ifndef Ft_Esd_Layout_Stretch__H
#define Ft_Esd_Layout_Stretch__H

#include "Ft_Esd.h"
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

#define Ft_Esd_Layout_Stretch_CLASSID 0x922270D9
ESD_SYMBOL(Ft_Esd_Layout_Stretch_CLASSID, Type = esd_classid_t)

ESD_WIDGET(Ft_Esd_Layout_Stretch, Include = "Ft_Esd_Layout_Stretch.h", Callback, DisplayName = "Stretch", Category = EsdLayouts, Icon = ":/icons/fill-270.png", X = 0, Y = 0, Width = 50, Height = 50, Layout, BackToFront)
typedef struct
{
	union
	{
		void *Owner;
		Ft_Esd_Widget Widget;
	};
	ESD_VARIABLE(Weight, Type = ft_int16_t, Default = 1, Public)
	ft_int16_t Weight;
} Ft_Esd_Layout_Stretch;

void Ft_Esd_Layout_Stretch__Initializer(Ft_Esd_Layout_Stretch *context);

#endif /* Ft_Esd_Layout_Stretch__H */

/* end of file */
