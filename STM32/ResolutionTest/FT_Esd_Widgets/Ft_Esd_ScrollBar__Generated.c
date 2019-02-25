/*
This file is automatically generated
DO NOT MODIFY BY HAND
Ft_Esd_ScrollBar
C Source
*/

#include "Ft_Esd_ScrollBar.h"

#include "FT_Esd_Dl.h"
#include "FT_Gpu.h"
#include "Ft_Esd_CoCmd.h"

extern void Ft_Esd_Noop(void *context);
Ft_Esd_Theme * Ft_Esd_ScrollBar_Theme__Default(void *context) { return 0; }
ft_int16_t Ft_Esd_ScrollBar_Size__Default(void *context) { return 256; }
ft_int16_t Ft_Esd_ScrollBar_Max__Default(void *context) { return 32767; }
ft_int16_t Ft_Esd_ScrollBar_Min__Default(void *context) { return 0; }
void Ft_Esd_ScrollBar_Changed__Noop(void *context, int value) { }


static Ft_Esd_WidgetSlots s_Ft_Esd_ScrollBar__Slots = {
	(void(*)(void *))Ft_Esd_Widget_Initialize,
	(void(*)(void *))Ft_Esd_ScrollBar_Start,
	(void(*)(void *))Ft_Esd_Widget_Enable,
	(void(*)(void *))Ft_Esd_ScrollBar_Update,
	(void(*)(void *))Ft_Esd_ScrollBar_Render,
	(void(*)(void *))Ft_Esd_Widget_Idle,
	(void(*)(void *))Ft_Esd_Widget_Disable,
	(void(*)(void *))Ft_Esd_ScrollBar_End,
};

static void Ft_Esd_ScrollBar_TouchTag_Down__Signal(void *context);

void Ft_Esd_ScrollBar__TouchTag__Initializer(Ft_Esd_ScrollBar *context)
{
	Ft_Esd_TouchTag *object = &context->TouchTag;
	Ft_Esd_TouchTag__Initializer(object);
	object->Owner = context;
	object->Down = Ft_Esd_ScrollBar_TouchTag_Down__Signal;
}

void Ft_Esd_ScrollBar__Initializer(Ft_Esd_ScrollBar *context)
{
	Ft_Esd_Widget__Initializer((Ft_Esd_Widget *)context);
	context->Widget.ClassId = Ft_Esd_ScrollBar_CLASSID;
	context->Widget.Slots = &s_Ft_Esd_ScrollBar__Slots;
	context->Widget.LocalX = 50;
	context->Widget.LocalY = 50;
	context->Widget.LocalWidth = 180;
	context->Widget.LocalHeight = 24;
	context->Theme = Ft_Esd_ScrollBar_Theme__Default;
	context->Size = Ft_Esd_ScrollBar_Size__Default;
	context->Value = 0;
	context->Max = Ft_Esd_ScrollBar_Max__Default;
	context->Min = Ft_Esd_ScrollBar_Min__Default;
	context->Changed = Ft_Esd_ScrollBar_Changed__Noop;
	context->PreviousValue = 0;
	context->PreviousX = 0;
	context->PreviousY = 0;
	Ft_Esd_ScrollBar__TouchTag__Initializer(context);
}

static ft_rgb32_t Ft_Esd_ScrollBar_Ft_Esd_Theme_GetBackColor__return(Ft_Esd_ScrollBar *context);
static ft_int16_t Ft_Esd_ScrollBar_Clamp_Int16__return(Ft_Esd_ScrollBar *context);

ft_void_t Ft_Gpu_CoCmd_BgColor(Ft_Gpu_Hal_Context_t *, ft_rgb32_t);
ft_void_t Ft_Gpu_CoCmd_FgColor(Ft_Gpu_Hal_Context_t *, ft_rgb32_t);
void Ft_Esd_ScrollBar_Update_Signal(Ft_Esd_ScrollBar *context);
void Ft_Esd_ScrollBar_CoCmd(Ft_Esd_ScrollBar *context, ft_uint16_t, ft_uint16_t, ft_uint16_t, ft_uint16_t);

void Ft_Esd_ScrollBar_Start(Ft_Esd_ScrollBar *context)
{
	void *owner = context->Owner;
	Ft_Esd_Widget_Start((Ft_Esd_Widget *)context);
	Ft_Esd_TouchTag_Start(&context->TouchTag);
}

void Ft_Esd_ScrollBar_End(Ft_Esd_ScrollBar *context)
{
	void *owner = context->Owner;
	Ft_Esd_TouchTag_End(&context->TouchTag);
	Ft_Esd_Widget_End((Ft_Esd_Widget *)context);
}

void Ft_Esd_ScrollBar_Render(Ft_Esd_ScrollBar *context)
{
	void *owner = context->Owner;
	ft_uint8_t alpha = 255;
	Ft_Esd_Dl_COLOR_A(alpha);
	Ft_Gpu_Hal_Context_t * phost = Ft_Esd_GetHost();
	ft_bool_t left = Ft_Esd_TouchTag_Touching(&context->TouchTag);
	ft_int16_t left_1 = context->Max(owner);
	ft_int16_t right_1 = context->Min(owner);
	ft_uint16_t right = left_1 - right_1;
	int if_1 = left && right;
	ft_rgb32_t c_1;
	if (if_1)
	{
		Ft_Esd_Theme * theme = context->Theme(owner);
		c_1 = Ft_Esd_Theme_GetCurrentColor(theme);
	}
	else
	{
		c_1 = Ft_Esd_ScrollBar_Ft_Esd_Theme_GetBackColor__return(context);
	}
	Ft_Gpu_CoCmd_BgColor(phost, c_1);
	Ft_Gpu_Hal_Context_t * phost_1 = Ft_Esd_GetHost();
	ft_int16_t left_2 = context->Max(owner);
	ft_int16_t right_2 = context->Min(owner);
	ft_uint16_t if_2 = left_2 - right_2;
	ft_rgb32_t c_2;
	if (if_2)
	{
		Ft_Esd_Theme * theme_1 = context->Theme(owner);
		c_2 = Ft_Esd_Theme_GetPrimaryColor(theme_1);
	}
	else
	{
		c_2 = Ft_Esd_ScrollBar_Ft_Esd_Theme_GetBackColor__return(context);
	}
	Ft_Gpu_CoCmd_FgColor(phost_1, c_2);
	ft_uint8_t s = Ft_Esd_TouchTag_Tag(&context->TouchTag);
	Ft_Esd_Dl_TAG(s);
	ft_uint16_t options = 0;
	ft_int16_t left_3 = Ft_Esd_ScrollBar_Clamp_Int16__return(context);
	ft_int16_t right_3 = context->Min(owner);
	int val = left_3 - right_3;
	ft_int16_t size = context->Size(owner);
	ft_int16_t left_5 = context->Max(owner);
	ft_int16_t right_4 = context->Min(owner);
	ft_uint16_t left_4 = left_5 - right_4;
	ft_int16_t right_5 = context->Size(owner);
	ft_uint16_t range = left_4 + right_5;
	Ft_Esd_ScrollBar_CoCmd(context, options, val, size, range);
	ft_uint8_t s_1 = 255;
	Ft_Esd_Dl_TAG(s_1);
	Ft_Esd_Widget_Render((Ft_Esd_Widget *)context); 
}

ft_rgb32_t Ft_Esd_ScrollBar_Ft_Esd_Theme_GetBackColor__return(Ft_Esd_ScrollBar *context)
{
	void *owner = context->Owner;
	Ft_Esd_Theme * theme_2 = context->Theme(owner);
	return Ft_Esd_Theme_GetBackColor(theme_2);
}

void Ft_Esd_ScrollBar_Update(Ft_Esd_ScrollBar *context)
{
	void *owner = context->Owner;
	Ft_Esd_TouchTag_Update(&context->TouchTag);
	Ft_Esd_ScrollBar_Update_Signal(context);
	Ft_Esd_Widget_Update((Ft_Esd_Widget *)context); 
}

ft_int16_t Ft_Esd_ScrollBar_Clamp_Int16__return(Ft_Esd_ScrollBar *context)
{
	void *owner = context->Owner;
	ft_int16_t value = context->Value;
	ft_int16_t min = context->Min(owner);
	ft_int16_t max = context->Max(owner);
	return Ft_Esd_Int16_ClampedValue(value, min, max);
}

void Ft_Esd_ScrollBar_TouchTag_Down__Signal(void *c)
{
	Ft_Esd_ScrollBar *context = (Ft_Esd_ScrollBar *)c;
	void *owner = context->Owner;
	ft_int16_t set_variable = Ft_Esd_ScrollBar_Clamp_Int16__return(context);
	context->PreviousValue = set_variable;
	ft_int16_t left_6 = Ft_Esd_TouchTag_TouchX(&context->TouchTag);
	ft_int16_t right_6 = context->Widget.GlobalX;
	ft_int16_t set_variable_2 = left_6 - right_6;
	context->PreviousX = set_variable_2;
	ft_int16_t left_7 = Ft_Esd_TouchTag_TouchY(&context->TouchTag);
	ft_int16_t right_7 = context->Widget.GlobalY;
	ft_int16_t set_variable_3 = left_7 - right_7;
	context->PreviousY = set_variable_3;
}

#ifdef ESD_SIMULATION
#include <stdlib.h>

typedef struct
{
	Ft_Esd_ScrollBar Instance;
	Ft_Esd_Theme * Theme;
	ft_int16_t Size;
	ft_int16_t Max;
	ft_int16_t Min;
} Ft_Esd_ScrollBar__ESD;

Ft_Esd_Theme * Ft_Esd_ScrollBar__Get_Theme__ESD(void *context) { return ((Ft_Esd_ScrollBar__ESD *)context)->Theme; }
void Ft_Esd_ScrollBar__Set_Theme__ESD(void *context, Ft_Esd_Theme * value) { ((Ft_Esd_ScrollBar__ESD *)context)->Theme = value; }
ft_int16_t Ft_Esd_ScrollBar__Get_Size__ESD(void *context) { return ((Ft_Esd_ScrollBar__ESD *)context)->Size; }
void Ft_Esd_ScrollBar__Set_Size__ESD(void *context, ft_int16_t value) { ((Ft_Esd_ScrollBar__ESD *)context)->Size = value; }
ft_int16_t Ft_Esd_ScrollBar__Get_Max__ESD(void *context) { return ((Ft_Esd_ScrollBar__ESD *)context)->Max; }
void Ft_Esd_ScrollBar__Set_Max__ESD(void *context, ft_int16_t value) { ((Ft_Esd_ScrollBar__ESD *)context)->Max = value; }
ft_int16_t Ft_Esd_ScrollBar__Get_Min__ESD(void *context) { return ((Ft_Esd_ScrollBar__ESD *)context)->Min; }
void Ft_Esd_ScrollBar__Set_Min__ESD(void *context, ft_int16_t value) { ((Ft_Esd_ScrollBar__ESD *)context)->Min = value; }

void *Ft_Esd_ScrollBar__Create__ESD()
{
	Ft_Esd_ScrollBar__ESD *context = (Ft_Esd_ScrollBar__ESD *)malloc(sizeof(Ft_Esd_ScrollBar__ESD));
	Ft_Esd_ScrollBar__Initializer(&context->Instance);
	context->Instance.Owner = context;
	context->Theme = 0;
	context->Instance.Theme = Ft_Esd_ScrollBar__Get_Theme__ESD;
	context->Size = 256;
	context->Instance.Size = Ft_Esd_ScrollBar__Get_Size__ESD;
	context->Max = 32767;
	context->Instance.Max = Ft_Esd_ScrollBar__Get_Max__ESD;
	context->Min = 0;
	context->Instance.Min = Ft_Esd_ScrollBar__Get_Min__ESD;
	return context;
}

void Ft_Esd_ScrollBar__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Esd_ScrollBar__Set_Value__ESD(void *context, ft_int16_t value) { ((Ft_Esd_ScrollBar__ESD *)context)->Instance.Value = value; }
void Ft_Esd_ScrollBar__Set_PreviousValue__ESD(void *context, ft_int16_t value) { ((Ft_Esd_ScrollBar__ESD *)context)->Instance.PreviousValue = value; }
void Ft_Esd_ScrollBar__Set_PreviousX__ESD(void *context, ft_int16_t value) { ((Ft_Esd_ScrollBar__ESD *)context)->Instance.PreviousX = value; }
void Ft_Esd_ScrollBar__Set_PreviousY__ESD(void *context, ft_int16_t value) { ((Ft_Esd_ScrollBar__ESD *)context)->Instance.PreviousY = value; }

#endif /* ESD_SIMULATION */

/* end of file */
