/*
This file is automatically generated
Ft_Esd_Elements__h
Simulation wrapper
*/

/* Simulation wrapper for 'Ft_Esd_Elements_CircleFlat' */

#ifdef ESD_SIMULATION
#include <stdlib.h>
#include "Ft_Esd_Elements.h"

void Ft_Esd_Elements_CircleFlat(ft_argb32_t, ft_int16_t, ft_int16_t, ft_int16_t);

typedef struct
{
	ft_argb32_t color;
	ft_int16_t x;
	ft_int16_t y;
	ft_int16_t radius;
} Ft_Esd_Elements_CircleFlat__ESD;

void Ft_Esd_Elements_CircleFlat__Set_color__ESD(void *context, ft_argb32_t value) { ((Ft_Esd_Elements_CircleFlat__ESD *)context)->color = value; }
void Ft_Esd_Elements_CircleFlat__Set_x__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_CircleFlat__ESD *)context)->x = value; }
void Ft_Esd_Elements_CircleFlat__Set_y__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_CircleFlat__ESD *)context)->y = value; }
void Ft_Esd_Elements_CircleFlat__Set_radius__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_CircleFlat__ESD *)context)->radius = value; }

void *Ft_Esd_Elements_CircleFlat__Create__ESD()
{
	Ft_Esd_Elements_CircleFlat__ESD *context = (Ft_Esd_Elements_CircleFlat__ESD *)malloc(sizeof(Ft_Esd_Elements_CircleFlat__ESD));
	context->color = 0xff151515UL;
	context->x = 0;
	context->y = 0;
	context->radius = 20;
	return context;
}

void Ft_Esd_Elements_CircleFlat__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Esd_Elements_CircleFlat_Render(Ft_Esd_Elements_CircleFlat__ESD *context)
{
	Ft_Esd_Elements_CircleFlat(context->color, context->x, context->y, context->radius);
}

#endif /* ESD_SIMULATION */

/* Simulation wrapper for 'Ft_Esd_Elements_CircleRaised' */

#ifdef ESD_SIMULATION
#include <stdlib.h>
#include "Ft_Esd_Elements.h"

void Ft_Esd_Elements_CircleRaised(ft_argb32_t, ft_int16_t, ft_int16_t, ft_int16_t);

typedef struct
{
	ft_argb32_t color;
	ft_int16_t x;
	ft_int16_t y;
	ft_int16_t radius;
} Ft_Esd_Elements_CircleRaised__ESD;

void Ft_Esd_Elements_CircleRaised__Set_color__ESD(void *context, ft_argb32_t value) { ((Ft_Esd_Elements_CircleRaised__ESD *)context)->color = value; }
void Ft_Esd_Elements_CircleRaised__Set_x__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_CircleRaised__ESD *)context)->x = value; }
void Ft_Esd_Elements_CircleRaised__Set_y__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_CircleRaised__ESD *)context)->y = value; }
void Ft_Esd_Elements_CircleRaised__Set_radius__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_CircleRaised__ESD *)context)->radius = value; }

void *Ft_Esd_Elements_CircleRaised__Create__ESD()
{
	Ft_Esd_Elements_CircleRaised__ESD *context = (Ft_Esd_Elements_CircleRaised__ESD *)malloc(sizeof(Ft_Esd_Elements_CircleRaised__ESD));
	context->color = 0xff6b6b6bUL;
	context->x = 0;
	context->y = 0;
	context->radius = 20;
	return context;
}

void Ft_Esd_Elements_CircleRaised__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Esd_Elements_CircleRaised_Render(Ft_Esd_Elements_CircleRaised__ESD *context)
{
	Ft_Esd_Elements_CircleRaised(context->color, context->x, context->y, context->radius);
}

#endif /* ESD_SIMULATION */

/* Simulation wrapper for 'Ft_Esd_Elements_CircleSunken' */

#ifdef ESD_SIMULATION
#include <stdlib.h>
#include "Ft_Esd_Elements.h"

void Ft_Esd_Elements_CircleSunken(ft_argb32_t, ft_int16_t, ft_int16_t, ft_int16_t);

typedef struct
{
	ft_argb32_t color;
	ft_int16_t x;
	ft_int16_t y;
	ft_int16_t radius;
} Ft_Esd_Elements_CircleSunken__ESD;

void Ft_Esd_Elements_CircleSunken__Set_color__ESD(void *context, ft_argb32_t value) { ((Ft_Esd_Elements_CircleSunken__ESD *)context)->color = value; }
void Ft_Esd_Elements_CircleSunken__Set_x__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_CircleSunken__ESD *)context)->x = value; }
void Ft_Esd_Elements_CircleSunken__Set_y__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_CircleSunken__ESD *)context)->y = value; }
void Ft_Esd_Elements_CircleSunken__Set_radius__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_CircleSunken__ESD *)context)->radius = value; }

void *Ft_Esd_Elements_CircleSunken__Create__ESD()
{
	Ft_Esd_Elements_CircleSunken__ESD *context = (Ft_Esd_Elements_CircleSunken__ESD *)malloc(sizeof(Ft_Esd_Elements_CircleSunken__ESD));
	context->color = 0xff151515UL;
	context->x = 0;
	context->y = 0;
	context->radius = 20;
	return context;
}

void Ft_Esd_Elements_CircleSunken__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Esd_Elements_CircleSunken_Render(Ft_Esd_Elements_CircleSunken__ESD *context)
{
	Ft_Esd_Elements_CircleSunken(context->color, context->x, context->y, context->radius);
}

#endif /* ESD_SIMULATION */

/* Simulation wrapper for 'Ft_Esd_Elements_Gradient_Panel' */

#ifdef ESD_SIMULATION
#include <stdlib.h>
#include "Ft_Esd_Elements.h"

void Ft_Esd_Elements_Gradient_Panel(ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_rgb32_t, ft_rgb32_t, ft_int16_t, ft_bool_t);

typedef struct
{
	ft_int16_t x;
	ft_int16_t y;
	ft_int16_t width;
	ft_int16_t height;
	ft_int16_t radius;
	ft_rgb32_t color1;
	ft_rgb32_t color2;
	ft_int16_t direction;
	ft_bool_t raised;
} Ft_Esd_Elements_Gradient_Panel__ESD;

void Ft_Esd_Elements_Gradient_Panel__Set_x__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_Gradient_Panel__ESD *)context)->x = value; }
void Ft_Esd_Elements_Gradient_Panel__Set_y__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_Gradient_Panel__ESD *)context)->y = value; }
void Ft_Esd_Elements_Gradient_Panel__Set_width__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_Gradient_Panel__ESD *)context)->width = value; }
void Ft_Esd_Elements_Gradient_Panel__Set_height__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_Gradient_Panel__ESD *)context)->height = value; }
void Ft_Esd_Elements_Gradient_Panel__Set_radius__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_Gradient_Panel__ESD *)context)->radius = value; }
void Ft_Esd_Elements_Gradient_Panel__Set_color1__ESD(void *context, ft_rgb32_t value) { ((Ft_Esd_Elements_Gradient_Panel__ESD *)context)->color1 = value; }
void Ft_Esd_Elements_Gradient_Panel__Set_color2__ESD(void *context, ft_rgb32_t value) { ((Ft_Esd_Elements_Gradient_Panel__ESD *)context)->color2 = value; }
void Ft_Esd_Elements_Gradient_Panel__Set_direction__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_Gradient_Panel__ESD *)context)->direction = value; }
void Ft_Esd_Elements_Gradient_Panel__Set_raised__ESD(void *context, ft_bool_t value) { ((Ft_Esd_Elements_Gradient_Panel__ESD *)context)->raised = value; }

void *Ft_Esd_Elements_Gradient_Panel__Create__ESD()
{
	Ft_Esd_Elements_Gradient_Panel__ESD *context = (Ft_Esd_Elements_Gradient_Panel__ESD *)malloc(sizeof(Ft_Esd_Elements_Gradient_Panel__ESD));
	context->x = 0;
	context->y = 0;
	context->width = 80;
	context->height = 60;
	context->radius = 4;
	context->color1 = 0x2f2f2fUL;
	context->color2 = 0xffffffUL;
	context->direction = 90;
	context->raised = 0;
	return context;
}

void Ft_Esd_Elements_Gradient_Panel__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Esd_Elements_Gradient_Panel_Render(Ft_Esd_Elements_Gradient_Panel__ESD *context)
{
	Ft_Esd_Elements_Gradient_Panel(context->x, context->y, context->width, context->height, context->radius, context->color1, context->color2, context->direction, context->raised);
}

#endif /* ESD_SIMULATION */

/* Simulation wrapper for 'Ft_Esd_Elements_Panel' */

#ifdef ESD_SIMULATION
#include <stdlib.h>
#include "Ft_Esd_Elements.h"

void Ft_Esd_Elements_Panel(Ft_Esd_Theme *, ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_bool_t);

typedef struct
{
	Ft_Esd_Theme * theme;
	ft_int16_t x;
	ft_int16_t y;
	ft_int16_t width;
	ft_int16_t height;
	ft_int16_t radius;
	ft_bool_t raised;
} Ft_Esd_Elements_Panel__ESD;

void Ft_Esd_Elements_Panel__Set_theme__ESD(void *context, Ft_Esd_Theme * value) { ((Ft_Esd_Elements_Panel__ESD *)context)->theme = value; }
void Ft_Esd_Elements_Panel__Set_x__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_Panel__ESD *)context)->x = value; }
void Ft_Esd_Elements_Panel__Set_y__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_Panel__ESD *)context)->y = value; }
void Ft_Esd_Elements_Panel__Set_width__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_Panel__ESD *)context)->width = value; }
void Ft_Esd_Elements_Panel__Set_height__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_Panel__ESD *)context)->height = value; }
void Ft_Esd_Elements_Panel__Set_radius__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_Panel__ESD *)context)->radius = value; }
void Ft_Esd_Elements_Panel__Set_raised__ESD(void *context, ft_bool_t value) { ((Ft_Esd_Elements_Panel__ESD *)context)->raised = value; }

void *Ft_Esd_Elements_Panel__Create__ESD()
{
	Ft_Esd_Elements_Panel__ESD *context = (Ft_Esd_Elements_Panel__ESD *)malloc(sizeof(Ft_Esd_Elements_Panel__ESD));
	context->theme = Ft_Esd_Theme_GetCurrent();
	context->x = 0;
	context->y = 0;
	context->width = 80;
	context->height = 60;
	context->radius = 4;
	context->raised = 0;
	return context;
}

void Ft_Esd_Elements_Panel__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Esd_Elements_Panel_Render(Ft_Esd_Elements_Panel__ESD *context)
{
	Ft_Esd_Elements_Panel(context->theme, context->x, context->y, context->width, context->height, context->radius, context->raised);
}

#endif /* ESD_SIMULATION */

/* Simulation wrapper for 'Ft_Esd_Elements_PanelRaised' */

#ifdef ESD_SIMULATION
#include <stdlib.h>
#include "Ft_Esd_Elements.h"

void Ft_Esd_Elements_PanelRaised(ft_rgb32_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t);

typedef struct
{
	ft_rgb32_t color;
	ft_int16_t x;
	ft_int16_t y;
	ft_int16_t width;
	ft_int16_t height;
	ft_int16_t radius;
} Ft_Esd_Elements_PanelRaised__ESD;

void Ft_Esd_Elements_PanelRaised__Set_color__ESD(void *context, ft_rgb32_t value) { ((Ft_Esd_Elements_PanelRaised__ESD *)context)->color = value; }
void Ft_Esd_Elements_PanelRaised__Set_x__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_PanelRaised__ESD *)context)->x = value; }
void Ft_Esd_Elements_PanelRaised__Set_y__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_PanelRaised__ESD *)context)->y = value; }
void Ft_Esd_Elements_PanelRaised__Set_width__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_PanelRaised__ESD *)context)->width = value; }
void Ft_Esd_Elements_PanelRaised__Set_height__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_PanelRaised__ESD *)context)->height = value; }
void Ft_Esd_Elements_PanelRaised__Set_radius__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_PanelRaised__ESD *)context)->radius = value; }

void *Ft_Esd_Elements_PanelRaised__Create__ESD()
{
	Ft_Esd_Elements_PanelRaised__ESD *context = (Ft_Esd_Elements_PanelRaised__ESD *)malloc(sizeof(Ft_Esd_Elements_PanelRaised__ESD));
	context->color = 0x6b6b6bUL;
	context->x = 0;
	context->y = 0;
	context->width = 80;
	context->height = 60;
	context->radius = 4;
	return context;
}

void Ft_Esd_Elements_PanelRaised__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Esd_Elements_PanelRaised_Render(Ft_Esd_Elements_PanelRaised__ESD *context)
{
	Ft_Esd_Elements_PanelRaised(context->color, context->x, context->y, context->width, context->height, context->radius);
}

#endif /* ESD_SIMULATION */

/* Simulation wrapper for 'Ft_Esd_Elements_PanelSunken' */

#ifdef ESD_SIMULATION
#include <stdlib.h>
#include "Ft_Esd_Elements.h"

void Ft_Esd_Elements_PanelSunken(ft_rgb32_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t);

typedef struct
{
	ft_rgb32_t color;
	ft_int16_t x;
	ft_int16_t y;
	ft_int16_t width;
	ft_int16_t height;
	ft_int16_t radius;
} Ft_Esd_Elements_PanelSunken__ESD;

void Ft_Esd_Elements_PanelSunken__Set_color__ESD(void *context, ft_rgb32_t value) { ((Ft_Esd_Elements_PanelSunken__ESD *)context)->color = value; }
void Ft_Esd_Elements_PanelSunken__Set_x__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_PanelSunken__ESD *)context)->x = value; }
void Ft_Esd_Elements_PanelSunken__Set_y__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_PanelSunken__ESD *)context)->y = value; }
void Ft_Esd_Elements_PanelSunken__Set_width__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_PanelSunken__ESD *)context)->width = value; }
void Ft_Esd_Elements_PanelSunken__Set_height__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_PanelSunken__ESD *)context)->height = value; }
void Ft_Esd_Elements_PanelSunken__Set_radius__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_PanelSunken__ESD *)context)->radius = value; }

void *Ft_Esd_Elements_PanelSunken__Create__ESD()
{
	Ft_Esd_Elements_PanelSunken__ESD *context = (Ft_Esd_Elements_PanelSunken__ESD *)malloc(sizeof(Ft_Esd_Elements_PanelSunken__ESD));
	context->color = 0x151515UL;
	context->x = 0;
	context->y = 0;
	context->width = 80;
	context->height = 60;
	context->radius = 4;
	return context;
}

void Ft_Esd_Elements_PanelSunken__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Esd_Elements_PanelSunken_Render(Ft_Esd_Elements_PanelSunken__ESD *context)
{
	Ft_Esd_Elements_PanelSunken(context->color, context->x, context->y, context->width, context->height, context->radius);
}

#endif /* ESD_SIMULATION */

/* Simulation wrapper for 'Ft_Esd_Elements_Panel_Color' */

#ifdef ESD_SIMULATION
#include <stdlib.h>
#include "Ft_Esd_Elements.h"

void Ft_Esd_Elements_Panel_Color(ft_argb32_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_bool_t);

typedef struct
{
	ft_argb32_t color;
	ft_int16_t x;
	ft_int16_t y;
	ft_int16_t width;
	ft_int16_t height;
	ft_int16_t radius;
	ft_bool_t raised;
} Ft_Esd_Elements_Panel_Color__ESD;

void Ft_Esd_Elements_Panel_Color__Set_color__ESD(void *context, ft_argb32_t value) { ((Ft_Esd_Elements_Panel_Color__ESD *)context)->color = value; }
void Ft_Esd_Elements_Panel_Color__Set_x__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_Panel_Color__ESD *)context)->x = value; }
void Ft_Esd_Elements_Panel_Color__Set_y__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_Panel_Color__ESD *)context)->y = value; }
void Ft_Esd_Elements_Panel_Color__Set_width__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_Panel_Color__ESD *)context)->width = value; }
void Ft_Esd_Elements_Panel_Color__Set_height__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_Panel_Color__ESD *)context)->height = value; }
void Ft_Esd_Elements_Panel_Color__Set_radius__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Elements_Panel_Color__ESD *)context)->radius = value; }
void Ft_Esd_Elements_Panel_Color__Set_raised__ESD(void *context, ft_bool_t value) { ((Ft_Esd_Elements_Panel_Color__ESD *)context)->raised = value; }

void *Ft_Esd_Elements_Panel_Color__Create__ESD()
{
	Ft_Esd_Elements_Panel_Color__ESD *context = (Ft_Esd_Elements_Panel_Color__ESD *)malloc(sizeof(Ft_Esd_Elements_Panel_Color__ESD));
	context->color = 0xff000000UL;
	context->x = 0;
	context->y = 0;
	context->width = 80;
	context->height = 60;
	context->radius = 4;
	context->raised = 0;
	return context;
}

void Ft_Esd_Elements_Panel_Color__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Esd_Elements_Panel_Color_Render(Ft_Esd_Elements_Panel_Color__ESD *context)
{
	Ft_Esd_Elements_Panel_Color(context->color, context->x, context->y, context->width, context->height, context->radius, context->raised);
}

#endif /* ESD_SIMULATION */

/* end of file */
