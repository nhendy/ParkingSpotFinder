/*
This file is automatically generated
DO NOT MODIFY BY HAND
Ft_Esd_ColorPicker
C Source
*/

#include "Ft_Esd_ColorPicker.h"

#include "FT_Esd_Dl.h"
#include "FT_Esd_Primitives.h"

extern void Ft_Esd_Noop(void *context);


static Ft_Esd_WidgetSlots s_Ft_Esd_ColorPicker__Slots = {
	(void(*)(void *))Ft_Esd_Widget_Initialize,
	(void(*)(void *))Ft_Esd_ColorPicker_Start,
	(void(*)(void *))Ft_Esd_Widget_Enable,
	(void(*)(void *))Ft_Esd_ColorPicker_Update,
	(void(*)(void *))Ft_Esd_ColorPicker_Render,
	(void(*)(void *))Ft_Esd_Widget_Idle,
	(void(*)(void *))Ft_Esd_Widget_Disable,
	(void(*)(void *))Ft_Esd_ColorPicker_End,
};


void Ft_Esd_ColorPicker__Touch_Tag__Initializer(Ft_Esd_ColorPicker *context)
{
	Ft_Esd_TouchTag *object = &context->Touch_Tag;
	Ft_Esd_TouchTag__Initializer(object);
	object->Owner = context;
}

void Ft_Esd_ColorPicker__Initializer(Ft_Esd_ColorPicker *context)
{
	Ft_Esd_Widget__Initializer((Ft_Esd_Widget *)context);
	context->Widget.ClassId = Ft_Esd_ColorPicker_CLASSID;
	context->Widget.Slots = &s_Ft_Esd_ColorPicker__Slots;
	context->Widget.LocalX = 0;
	context->Widget.LocalY = 0;
	context->Widget.LocalWidth = 400;
	context->Widget.LocalHeight = 300;
	context->Bitmap = (Ft_Esd_BitmapCell){ 0 };
	context->Radius = 125L;
	context->Color = 0xffffffffUL;
	Ft_Esd_ColorPicker__Touch_Tag__Initializer(context);
}

static double Ft_Esd_ColorPicker_getSat__return(Ft_Esd_ColorPicker *context);

ft_void_t Ft_Esd_Render_Bitmap(ft_int16_t, ft_int16_t, Ft_Esd_BitmapCell, ft_argb32_t);
double getHue(int, int, int, int);
double getSat(int, int, int, int, double);
ft_argb32_t hsvToRgb(double, double, double);

void Ft_Esd_ColorPicker_Start__Builtin(Ft_Esd_ColorPicker *context)
{
	void *owner = context->Owner;
	Ft_Esd_Widget_Start((Ft_Esd_Widget *)context);
	Ft_Esd_TouchTag_Start(&context->Touch_Tag);
}

void Ft_Esd_ColorPicker_End__Builtin(Ft_Esd_ColorPicker *context)
{
	void *owner = context->Owner;
	Ft_Esd_TouchTag_End(&context->Touch_Tag);
	Ft_Esd_Widget_End((Ft_Esd_Widget *)context);
}

void Ft_Esd_ColorPicker_Render(Ft_Esd_ColorPicker *context)
{
	void *owner = context->Owner;
	ft_uint8_t s = Ft_Esd_TouchTag_Tag(&context->Touch_Tag);
	Ft_Esd_Dl_TAG(s);
	ft_int16_t x = context->Widget.GlobalX;
	ft_int16_t y = context->Widget.GlobalY;
	Ft_Esd_BitmapCell bitmapCell = context->Bitmap;
	ft_argb32_t c_1 = 0xffffffffUL;
	Ft_Esd_Render_Bitmap(x, y, bitmapCell, c_1);
	ft_uint8_t s_1 = 255;
	Ft_Esd_Dl_TAG(s_1);
	Ft_Esd_Widget_Render((Ft_Esd_Widget *)context); 
}

double Ft_Esd_ColorPicker_getSat__return(Ft_Esd_ColorPicker *context)
{
	void *owner = context->Owner;
	ft_int16_t left = context->Widget.GlobalX;
	int right = context->Radius;
	int x0 = left + right;
	ft_int16_t left_1 = context->Widget.GlobalY;
	int right_1 = context->Radius;
	int y0 = left_1 + right_1;
	ft_int16_t x1 = Ft_Esd_TouchTag_TouchX(&context->Touch_Tag);
	ft_int16_t y1 = Ft_Esd_TouchTag_TouchY(&context->Touch_Tag);
	int r = context->Radius;
	return getSat(x0, y0, x1, y1, r);
}

void Ft_Esd_ColorPicker_Start(Ft_Esd_ColorPicker *context)
{
	void *owner = context->Owner;
	Ft_Esd_ColorPicker_Start__Builtin(context);
}

void Ft_Esd_ColorPicker_Update(Ft_Esd_ColorPicker *context)
{
	void *owner = context->Owner;
	Ft_Esd_TouchTag_Update(&context->Touch_Tag);
	double left_3 = Ft_Esd_ColorPicker_getSat__return(context);
	double right_2 = 1.0;
	int left_2 = left_3 <= right_2;
	ft_bool_t right_3 = Ft_Esd_TouchTag_Touching(&context->Touch_Tag);
	ft_bool_t if_1 = left_2 & right_3;
	ft_argb32_t set_variable;
	if (if_1)
	{
		ft_int16_t left_4 = context->Widget.GlobalX;
		int right_4 = context->Radius;
		int x0_1 = left_4 + right_4;
		ft_int16_t left_5 = context->Widget.GlobalY;
		int right_5 = context->Radius;
		int y0_1 = left_5 + right_5;
		ft_int16_t x1_1 = Ft_Esd_TouchTag_TouchX(&context->Touch_Tag);
		ft_int16_t y1_1 = Ft_Esd_TouchTag_TouchY(&context->Touch_Tag);
		double h = getHue(x0_1, y0_1, x1_1, y1_1);
		double s_2 = Ft_Esd_ColorPicker_getSat__return(context);
		double v = 255.0;
		set_variable = hsvToRgb(h, s_2, v);
	}
	else
	{
		set_variable = context->Color;
	}
	context->Color = set_variable;
	Ft_Esd_Widget_Update((Ft_Esd_Widget *)context); 
}

void Ft_Esd_ColorPicker_End(Ft_Esd_ColorPicker *context)
{
	void *owner = context->Owner;
	Ft_Esd_ColorPicker_End__Builtin(context);
}

#ifdef ESD_SIMULATION
#include <stdlib.h>

typedef struct
{
	Ft_Esd_ColorPicker Instance;
} Ft_Esd_ColorPicker__ESD;


void *Ft_Esd_ColorPicker__Create__ESD()
{
	Ft_Esd_ColorPicker__ESD *context = (Ft_Esd_ColorPicker__ESD *)malloc(sizeof(Ft_Esd_ColorPicker__ESD));
	Ft_Esd_ColorPicker__Initializer(&context->Instance);
	context->Instance.Owner = context;
	return context;
}

void Ft_Esd_ColorPicker__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Esd_ColorPicker__Set_Bitmap__ESD(void *context, Ft_Esd_BitmapCell value) { ((Ft_Esd_ColorPicker__ESD *)context)->Instance.Bitmap = value; }
void Ft_Esd_ColorPicker__Set_Radius__ESD(void *context, int value) { ((Ft_Esd_ColorPicker__ESD *)context)->Instance.Radius = value; }
void Ft_Esd_ColorPicker__Set_Color__ESD(void *context, ft_argb32_t value) { ((Ft_Esd_ColorPicker__ESD *)context)->Instance.Color = value; }

#endif /* ESD_SIMULATION */

/* end of file */