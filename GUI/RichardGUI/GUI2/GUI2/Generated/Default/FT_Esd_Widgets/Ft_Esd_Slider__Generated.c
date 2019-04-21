/*
This file is automatically generated
Ft_Esd_Slider
C Source
*/

#include "Ft_Esd_Slider.h"

#include "FT_Esd_CoPro_Cmds.h"
#include "FT_Esd_Dl.h"
#include "FT_Gpu.h"

extern void Ft_Esd_Noop(void *context);
Ft_Esd_Theme * Ft_Esd_Slider_Theme__Default(void *context) { return Ft_Esd_Theme_GetCurrent(); }
ft_int16_t Ft_Esd_Slider_X__Default(void *context) { return 10; }
ft_int16_t Ft_Esd_Slider_Y__Default(void *context) { return 10; }
ft_int16_t Ft_Esd_Slider_Width__Default(void *context) { return 160; }
ft_int16_t Ft_Esd_Slider_Height__Default(void *context) { return 20; }
ft_uint8_t Ft_Esd_Slider_Alpha__Default(void *context) { return 255; }
void Ft_Esd_Slider_Changed__Noop(void *context, int value) { }
ft_int16_t Ft_Esd_Slider_Range__Default(void *context) { return 100; }

Ft_Esd_Theme * Ft_Esd_Theme_GetCurrent();
Ft_Gpu_Hal_Context_t * Ft_Esd_GetHost();

static void Ft_Esd_Slider_TouchTag_Down__Signal(void *context);

void Ft_Esd_Slider__Initializer(Ft_Esd_Slider *context)
{
	context->Parent = 0;
	context->Theme = Ft_Esd_Slider_Theme__Default;
	Ft_Esd_TouchTag__Initializer(&context->TouchTag);
	context->TouchTag.Parent = context;
	context->TouchTag.Down = Ft_Esd_Slider_TouchTag_Down__Signal;
	context->X = Ft_Esd_Slider_X__Default;
	context->Y = Ft_Esd_Slider_Y__Default;
	context->Width = Ft_Esd_Slider_Width__Default;
	context->Height = Ft_Esd_Slider_Height__Default;
	context->Alpha = Ft_Esd_Slider_Alpha__Default;
	context->Value = 0;
	context->Changed = Ft_Esd_Slider_Changed__Noop;
	context->PreviousValue = 0;
	context->PreviousX = 0;
	context->Range = Ft_Esd_Slider_Range__Default;
	context->PreviousY = 0;
}

static ft_rgb32_t Ft_Esd_Slider_Get_Primary_Color__return(Ft_Esd_Slider *context);
static ft_int16_t Ft_Esd_Slider_Ft_Esd_Slider_ClampedValue__return(Ft_Esd_Slider *context);

ft_void_t Ft_Gpu_CoCmd_BgColor(Ft_Gpu_Hal_Context_t *, ft_rgb32_t);
ft_void_t Ft_Gpu_CoCmd_FgColor(Ft_Gpu_Hal_Context_t *, ft_rgb32_t);
void Ft_Esd_Slider_Update_Signal(Ft_Esd_Slider *context);
ft_int16_t Ft_Esd_Slider_ClampedValue(Ft_Esd_Slider *context);
ft_void_t Ft_Gpu_CoCmd_Slider(Ft_Gpu_Hal_Context_t *, ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_uint16_t, ft_uint16_t, ft_uint16_t);

void Ft_Esd_Slider_Render(Ft_Esd_Slider *context)
{
	void *parent = context->Parent;
	ft_uint8_t alpha = context->Alpha(parent);
	Ft_Esd_Dl_COLOR_A(alpha);
	ft_bool_t if_1 = Ft_Esd_TouchTag_Touching(&context->TouchTag);
	ft_rgb32_t c;
	if (if_1)
	{
		c = Ft_Esd_Slider_Get_Primary_Color__return(context);
	}
	else
	{
		Ft_Esd_Theme * theme = context->Theme(parent);
		c = Ft_Esd_Theme_GetCurrentColor(theme);
	}
	Ft_Esd_Dl_COLOR_RGB(c);
	Ft_Gpu_Hal_Context_t * phost = Ft_Esd_GetHost();
	Ft_Esd_Theme * theme_1 = context->Theme(parent);
	ft_rgb32_t c_1 = Ft_Esd_Theme_GetBackColor(theme_1);
	Ft_Gpu_CoCmd_BgColor(phost, c_1);
	Ft_Gpu_Hal_Context_t * phost_1 = Ft_Esd_GetHost();
	ft_rgb32_t c_2 = Ft_Esd_Slider_Get_Primary_Color__return(context);
	Ft_Gpu_CoCmd_FgColor(phost_1, c_2);
	ft_uint8_t s = Ft_Esd_TouchTag_Tag(&context->TouchTag);
	Ft_Esd_Dl_TAG(s);
	Ft_Gpu_Hal_Context_t * phost_2 = Ft_Esd_GetHost();
	ft_int16_t left = context->X(parent);
	ft_int16_t left_1 = context->Height(parent);
	ft_int16_t right_1 = 2;
	ft_int16_t right = left_1 / right_1;
	ft_int16_t x = left + right;
	ft_int16_t y = context->Y(parent);
	ft_int16_t left_2 = context->Width(parent);
	ft_int16_t right_2 = context->Height(parent);
	ft_int16_t width = left_2 - right_2;
	ft_int16_t height = context->Height(parent);
	ft_uint16_t options = 0;
	ft_int16_t val = Ft_Esd_Slider_Ft_Esd_Slider_ClampedValue__return(context);
	ft_int16_t range = context->Range(parent);
	Ft_Gpu_CoCmd_Slider(phost_2, x, y, width, height, options, val, range);
	ft_uint8_t s_1 = 255;
	Ft_Esd_Dl_TAG(s_1);
}

void Ft_Esd_Slider_Start(Ft_Esd_Slider *context)
{
	void *parent = context->Parent;
	Ft_Esd_TouchTag_Start(&context->TouchTag);
}

void Ft_Esd_Slider_Update(Ft_Esd_Slider *context)
{
	void *parent = context->Parent;
	Ft_Esd_TouchTag_Update(&context->TouchTag);
	Ft_Esd_Slider_Update_Signal(context);
}

void Ft_Esd_Slider_End(Ft_Esd_Slider *context)
{
	void *parent = context->Parent;
	Ft_Esd_TouchTag_End(&context->TouchTag);
}

ft_rgb32_t Ft_Esd_Slider_Get_Primary_Color__return(Ft_Esd_Slider *context)
{
	void *parent = context->Parent;
	Ft_Esd_Theme * theme_2 = context->Theme(parent);
	return Ft_Esd_Theme_GetPrimaryColor(theme_2);
}

void Ft_Esd_Slider_TouchTag_Down__Signal(void *c)
{
	Ft_Esd_Slider *context = (Ft_Esd_Slider *)c;
	void *parent = context->Parent;
	ft_int16_t set_variable = Ft_Esd_Slider_Ft_Esd_Slider_ClampedValue__return(context);
	context->PreviousValue = set_variable;
	ft_int16_t set_variable_1 = Ft_Esd_TouchTag_TouchX(&context->TouchTag);
	context->PreviousX = set_variable_1;
	ft_int16_t set_variable_2 = Ft_Esd_TouchTag_TouchY(&context->TouchTag);
	context->PreviousY = set_variable_2;
}

ft_int16_t Ft_Esd_Slider_Ft_Esd_Slider_ClampedValue__return(Ft_Esd_Slider *context)
{
	void *parent = context->Parent;
	return Ft_Esd_Slider_ClampedValue(context);
}

#ifdef ESD_SIMULATION
#include <stdlib.h>

typedef struct
{
	Ft_Esd_Slider Instance;
	Ft_Esd_Theme * Theme;
	ft_int16_t X;
	ft_int16_t Y;
	ft_int16_t Width;
	ft_int16_t Height;
	ft_uint8_t Alpha;
	ft_int16_t Range;
} Ft_Esd_Slider__ESD;

Ft_Esd_Theme * Ft_Esd_Slider__Get_Theme__ESD(void *context) { return ((Ft_Esd_Slider__ESD *)context)->Theme; }
void Ft_Esd_Slider__Set_Theme__ESD(void *context, Ft_Esd_Theme * value) { ((Ft_Esd_Slider__ESD *)context)->Theme = value; }
ft_int16_t Ft_Esd_Slider__Get_X__ESD(void *context) { return ((Ft_Esd_Slider__ESD *)context)->X; }
void Ft_Esd_Slider__Set_X__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Slider__ESD *)context)->X = value; }
ft_int16_t Ft_Esd_Slider__Get_Y__ESD(void *context) { return ((Ft_Esd_Slider__ESD *)context)->Y; }
void Ft_Esd_Slider__Set_Y__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Slider__ESD *)context)->Y = value; }
ft_int16_t Ft_Esd_Slider__Get_Width__ESD(void *context) { return ((Ft_Esd_Slider__ESD *)context)->Width; }
void Ft_Esd_Slider__Set_Width__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Slider__ESD *)context)->Width = value; }
ft_int16_t Ft_Esd_Slider__Get_Height__ESD(void *context) { return ((Ft_Esd_Slider__ESD *)context)->Height; }
void Ft_Esd_Slider__Set_Height__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Slider__ESD *)context)->Height = value; }
ft_uint8_t Ft_Esd_Slider__Get_Alpha__ESD(void *context) { return ((Ft_Esd_Slider__ESD *)context)->Alpha; }
void Ft_Esd_Slider__Set_Alpha__ESD(void *context, ft_uint8_t value) { ((Ft_Esd_Slider__ESD *)context)->Alpha = value; }
ft_int16_t Ft_Esd_Slider__Get_Range__ESD(void *context) { return ((Ft_Esd_Slider__ESD *)context)->Range; }
void Ft_Esd_Slider__Set_Range__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Slider__ESD *)context)->Range = value; }

void *Ft_Esd_Slider__Create__ESD()
{
	Ft_Esd_Slider__ESD *context = (Ft_Esd_Slider__ESD *)malloc(sizeof(Ft_Esd_Slider__ESD));
	Ft_Esd_Slider__Initializer(&context->Instance);
	context->Instance.Parent = context;
	context->Theme = Ft_Esd_Theme_GetCurrent();
	context->Instance.Theme = Ft_Esd_Slider__Get_Theme__ESD;
	context->X = 10;
	context->Instance.X = Ft_Esd_Slider__Get_X__ESD;
	context->Y = 10;
	context->Instance.Y = Ft_Esd_Slider__Get_Y__ESD;
	context->Width = 160;
	context->Instance.Width = Ft_Esd_Slider__Get_Width__ESD;
	context->Height = 20;
	context->Instance.Height = Ft_Esd_Slider__Get_Height__ESD;
	context->Alpha = 255;
	context->Instance.Alpha = Ft_Esd_Slider__Get_Alpha__ESD;
	context->Range = 100;
	context->Instance.Range = Ft_Esd_Slider__Get_Range__ESD;
	return context;
}

void Ft_Esd_Slider__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Esd_Slider__Set_Value__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Slider__ESD *)context)->Instance.Value = value; }
void Ft_Esd_Slider__Set_PreviousValue__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Slider__ESD *)context)->Instance.PreviousValue = value; }
void Ft_Esd_Slider__Set_PreviousX__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Slider__ESD *)context)->Instance.PreviousX = value; }
void Ft_Esd_Slider__Set_PreviousY__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Slider__ESD *)context)->Instance.PreviousY = value; }

#endif /* ESD_SIMULATION */

/* end of file */