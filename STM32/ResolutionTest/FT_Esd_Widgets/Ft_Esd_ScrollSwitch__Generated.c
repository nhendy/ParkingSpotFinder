/*
This file is automatically generated
DO NOT MODIFY BY HAND
Ft_Esd_ScrollSwitch
C Source
*/

#include "Ft_Esd_ScrollSwitch.h"


extern void Ft_Esd_Noop(void *context);
Ft_Esd_Widget * Ft_Esd_ScrollSwitch_InitialPrevious__Default(void *context) { return 0x0; }
Ft_Esd_Widget * Ft_Esd_ScrollSwitch_InitialCurrent__Default(void *context) { return 0x0; }
Ft_Esd_Widget * Ft_Esd_ScrollSwitch_InitialNext__Default(void *context) { return 0x0; }
int Ft_Esd_ScrollSwitch_InitialIndex__Default(void *context) { return 1L; }
ft_bool_t Ft_Esd_ScrollSwitch_Active_Scroll__Default(void *context) { return 0; }
ft_bool_t Ft_Esd_ScrollSwitch_Spinner__Default(void *context) { return 0; }
Ft_Esd_Widget * Ft_Esd_ScrollSwitch_New__Default(void *context) { return 0x0; }

static ft_bool_t Ft_Esd_ScrollSwitch_ScrollPanel_Active_Scroll__Property(void *context);
static Ft_Esd_Theme * Ft_Esd_ScrollSwitch_ScrollPanel_Theme__Property(void *context) { return Ft_Esd_Theme_LightBlue(); }

static Ft_Esd_WidgetSlots s_Ft_Esd_ScrollSwitch__Slots = {
	(void(*)(void *))Ft_Esd_Widget_Initialize,
	(void(*)(void *))Ft_Esd_Widget_Start,
	(void(*)(void *))Ft_Esd_Widget_Enable,
	(void(*)(void *))Ft_Esd_ScrollSwitch_Update,
	(void(*)(void *))Ft_Esd_ScrollSwitch_Render,
	(void(*)(void *))Ft_Esd_Widget_Idle,
	(void(*)(void *))Ft_Esd_Widget_Disable,
	(void(*)(void *))Ft_Esd_ScrollSwitch_End,
};

static void Ft_Esd_ScrollSwitch_ScrollPanel_Up__Signal(void *context);
static void Ft_Esd_ScrollSwitch_ScrollPanel_Down__Signal(void *context);

Ft_Esd_Widget *Ft_Esd_ScrollSwitch_Widget_Interface__Container(void *context);

void Ft_Esd_ScrollSwitch__ScrollPanel__Initializer(Ft_Esd_ScrollSwitch *context)
{
	Ft_Esd_ScrollPanel *object = &context->ScrollPanel;
	Ft_Esd_ScrollPanel__Initializer(object);
	object->Owner = context;
	object->Widget.Active = 1;
	object->Widget.LocalX = -2;
	object->Widget.LocalY = 41;
	object->Widget.LocalWidth = 322;
	object->Widget.LocalHeight = 431;
	object->Active_Scroll = Ft_Esd_ScrollSwitch_ScrollPanel_Active_Scroll__Property;
	object->Theme = Ft_Esd_ScrollSwitch_ScrollPanel_Theme__Property;
	object->ScrollX = 0;
	object->Align = ESD_ALIGN_TOPLEFT;
	object->Up = Ft_Esd_ScrollSwitch_ScrollPanel_Up__Signal;
	object->Down = Ft_Esd_ScrollSwitch_ScrollPanel_Down__Signal;
	Ft_Esd_Widget_InsertBottom((Ft_Esd_Widget *)object, (Ft_Esd_Widget *)context);
}

void Ft_Esd_ScrollSwitch__FixedPositioning__Initializer(Ft_Esd_ScrollSwitch *context)
{
	Ft_Esd_Layout_Fixed *object = &context->FixedPositioning;
	Ft_Esd_Layout_Fixed__Initializer(object);
	object->Owner = context;
	object->Widget.Active = 1;
	object->Widget.LocalX = 0;
	object->Widget.LocalY = 0;
	object->Widget.LocalWidth = 1016;
	object->Widget.LocalHeight = 390;
	Ft_Esd_Widget_InsertBottom((Ft_Esd_Widget *)object, (Ft_Esd_Widget *)&context->ScrollPanel);
}

void Ft_Esd_ScrollSwitch__Initializer(Ft_Esd_ScrollSwitch *context)
{
	Ft_Esd_Widget__Initializer((Ft_Esd_Widget *)context);
	context->Widget.ClassId = Ft_Esd_ScrollSwitch_CLASSID;
	context->Widget.Slots = &s_Ft_Esd_ScrollSwitch__Slots;
	context->Widget.LocalX = 0;
	context->Widget.LocalY = 0;
	context->Widget.LocalWidth = 318;
	context->Widget.LocalHeight = 478;
	context->InitialPrevious = Ft_Esd_ScrollSwitch_InitialPrevious__Default;
	context->InitialCurrent = Ft_Esd_ScrollSwitch_InitialCurrent__Default;
	context->InitialNext = Ft_Esd_ScrollSwitch_InitialNext__Default;
	context->InitialIndex = Ft_Esd_ScrollSwitch_InitialIndex__Default;
	context->Active_Scroll = Ft_Esd_ScrollSwitch_Active_Scroll__Default;
	context->Looping = 1;
	context->Count = 4L;
	context->Spacing = 5L;
	context->Touching = 0;
	context->Sensitivity = 1.5f;
	context->SwitchSpeed = 4L;
	context->ScrollXStart = 0L;
	context->ScrollX = 0L;
	context->NewPage = Ft_Esd_Noop;
	context->ScrollXTarget = 0L;
	context->NewScrollX = 0L;
	context->Overflow = 0;
	context->Spinner = Ft_Esd_ScrollSwitch_Spinner__Default;
	context->State = 0L;
	context->RemovingWidget = 0x0;
	context->Previous = 0x0;
	context->Current = 0x0;
	context->Next = 0x0;
	context->New = Ft_Esd_ScrollSwitch_New__Default;
	context->Index = 1L;
	context->NewIndex = 1L;
	Ft_Esd_ScrollSwitch__ScrollPanel__Initializer(context);
	Ft_Esd_ScrollSwitch__FixedPositioning__Initializer(context);
	context->Widget.Container = Ft_Esd_ScrollSwitch_Widget_Interface__Container(context);
}

void Ft_Esd_ScrollSwitch_SS_Initialise(Ft_Esd_ScrollSwitch *context);
void Ft_Esd_ScrollSwitch_Touch_Down(Ft_Esd_ScrollSwitch *context);
void Ft_Esd_ScrollSwitch_PreUpdate_Widget(Ft_Esd_ScrollSwitch *context);
void Ft_Esd_ScrollSwitch_Touch_Up(Ft_Esd_ScrollSwitch *context);
void Ft_Esd_ScrollSwitch_Update_Handle(Ft_Esd_ScrollSwitch *context);
void Ft_Esd_ScrollSwitch_Render_Signal(Ft_Esd_ScrollSwitch *context);

void Ft_Esd_ScrollSwitch_Update__Builtin(Ft_Esd_ScrollSwitch *context)
{
	void *owner = context->Owner;
	ft_bool_t update_variable = context->ScrollPanel.Touching;
	context->Touching = update_variable;
	ft_int16_t update_variable_1 = context->Widget.GlobalWidth;
	Ft_Esd_Widget_SetWidth((Ft_Esd_Widget *)&context->ScrollPanel, update_variable_1);
	ft_int16_t left = context->Widget.GlobalHeight;
	int right = 40L;
	int update_variable_2 = left - right;
	Ft_Esd_Widget_SetHeight((Ft_Esd_Widget *)&context->ScrollPanel, update_variable_2);
	Ft_Esd_Widget_Update((Ft_Esd_Widget *)context);
}

void Ft_Esd_ScrollSwitch_End(Ft_Esd_ScrollSwitch *context)
{
	void *owner = context->Owner;
	Ft_Esd_Widget_End((Ft_Esd_Widget *)context);
	Ft_Esd_Widget_Detach((Ft_Esd_Widget *)&context->ScrollPanel); 
	Ft_Esd_Widget_Detach((Ft_Esd_Widget *)&context->FixedPositioning); 
}

void Ft_Esd_ScrollSwitch_Initialise(Ft_Esd_ScrollSwitch *context)
{
	void *owner = context->Owner;
	Ft_Esd_ScrollSwitch_SS_Initialise(context);
}

void Ft_Esd_ScrollSwitch_Update(Ft_Esd_ScrollSwitch *context)
{
	void *owner = context->Owner;
	ft_int16_t update_scrollx = context->ScrollPanel.ScrollX;
	context->ScrollX = update_scrollx;
	Ft_Esd_ScrollSwitch_Update_Handle(context);
	ft_bool_t if_1 = context->Touching;
	if (if_1)
	{
	}
	else
	{
		int left_1 = context->State;
		int right_1 = 0L;
		int if_2 = left_1 == right_1;
		if (if_2)
		{
		}
		else
		{
			int set_variable = context->NewScrollX;
			context->ScrollPanel.ScrollX = (int)set_variable;
		}
	}
	Ft_Esd_ScrollSwitch_Update__Builtin(context);
}

Ft_Esd_Widget * Ft_Esd_ScrollSwitch_Widget_Interface__Container(void *c)
{
	Ft_Esd_ScrollSwitch *context = (Ft_Esd_ScrollSwitch *)c;
	void *owner = context->Owner;
	return &context->FixedPositioning;
}

void Ft_Esd_ScrollSwitch_Render(Ft_Esd_ScrollSwitch *context)
{
	void *owner = context->Owner;
	Ft_Esd_ScrollSwitch_Render_Signal(context);
	Ft_Esd_Widget_Render((Ft_Esd_Widget *)context); 
}

ft_bool_t Ft_Esd_ScrollSwitch_ScrollPanel_Active_Scroll__Property(void *c)
{
	Ft_Esd_ScrollSwitch *context = (Ft_Esd_ScrollSwitch *)c;
	void *owner = context->Owner;
	return context->Active_Scroll(owner);
}

void Ft_Esd_ScrollSwitch_ScrollPanel_Up__Signal(void *c)
{
	Ft_Esd_ScrollSwitch *context = (Ft_Esd_ScrollSwitch *)c;
	void *owner = context->Owner;
	Ft_Esd_ScrollSwitch_Touch_Up(context);
	Ft_Esd_ScrollSwitch_PreUpdate_Widget(context);
}

void Ft_Esd_ScrollSwitch_ScrollPanel_Down__Signal(void *c)
{
	Ft_Esd_ScrollSwitch *context = (Ft_Esd_ScrollSwitch *)c;
	void *owner = context->Owner;
	Ft_Esd_ScrollSwitch_Touch_Down(context);
}

#ifdef ESD_SIMULATION
#include <stdlib.h>

typedef struct
{
	Ft_Esd_ScrollSwitch Instance;
	Ft_Esd_Widget * InitialPrevious;
	Ft_Esd_Widget * InitialCurrent;
	Ft_Esd_Widget * InitialNext;
	int InitialIndex;
	ft_bool_t Active_Scroll;
	ft_bool_t Spinner;
	Ft_Esd_Widget * New;
} Ft_Esd_ScrollSwitch__ESD;

Ft_Esd_Widget * Ft_Esd_ScrollSwitch__Get_InitialPrevious__ESD(void *context) { return ((Ft_Esd_ScrollSwitch__ESD *)context)->InitialPrevious; }
void Ft_Esd_ScrollSwitch__Set_InitialPrevious__ESD(void *context, Ft_Esd_Widget * value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->InitialPrevious = value; }
Ft_Esd_Widget * Ft_Esd_ScrollSwitch__Get_InitialCurrent__ESD(void *context) { return ((Ft_Esd_ScrollSwitch__ESD *)context)->InitialCurrent; }
void Ft_Esd_ScrollSwitch__Set_InitialCurrent__ESD(void *context, Ft_Esd_Widget * value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->InitialCurrent = value; }
Ft_Esd_Widget * Ft_Esd_ScrollSwitch__Get_InitialNext__ESD(void *context) { return ((Ft_Esd_ScrollSwitch__ESD *)context)->InitialNext; }
void Ft_Esd_ScrollSwitch__Set_InitialNext__ESD(void *context, Ft_Esd_Widget * value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->InitialNext = value; }
int Ft_Esd_ScrollSwitch__Get_InitialIndex__ESD(void *context) { return ((Ft_Esd_ScrollSwitch__ESD *)context)->InitialIndex; }
void Ft_Esd_ScrollSwitch__Set_InitialIndex__ESD(void *context, int value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->InitialIndex = value; }
ft_bool_t Ft_Esd_ScrollSwitch__Get_Active_Scroll__ESD(void *context) { return ((Ft_Esd_ScrollSwitch__ESD *)context)->Active_Scroll; }
void Ft_Esd_ScrollSwitch__Set_Active_Scroll__ESD(void *context, ft_bool_t value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->Active_Scroll = value; }
ft_bool_t Ft_Esd_ScrollSwitch__Get_Spinner__ESD(void *context) { return ((Ft_Esd_ScrollSwitch__ESD *)context)->Spinner; }
void Ft_Esd_ScrollSwitch__Set_Spinner__ESD(void *context, ft_bool_t value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->Spinner = value; }
Ft_Esd_Widget * Ft_Esd_ScrollSwitch__Get_New__ESD(void *context) { return ((Ft_Esd_ScrollSwitch__ESD *)context)->New; }
void Ft_Esd_ScrollSwitch__Set_New__ESD(void *context, Ft_Esd_Widget * value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->New = value; }

void *Ft_Esd_ScrollSwitch__Create__ESD()
{
	Ft_Esd_ScrollSwitch__ESD *context = (Ft_Esd_ScrollSwitch__ESD *)malloc(sizeof(Ft_Esd_ScrollSwitch__ESD));
	Ft_Esd_ScrollSwitch__Initializer(&context->Instance);
	context->Instance.Owner = context;
	context->InitialPrevious = 0x0;
	context->Instance.InitialPrevious = Ft_Esd_ScrollSwitch__Get_InitialPrevious__ESD;
	context->InitialCurrent = 0x0;
	context->Instance.InitialCurrent = Ft_Esd_ScrollSwitch__Get_InitialCurrent__ESD;
	context->InitialNext = 0x0;
	context->Instance.InitialNext = Ft_Esd_ScrollSwitch__Get_InitialNext__ESD;
	context->InitialIndex = 1L;
	context->Instance.InitialIndex = Ft_Esd_ScrollSwitch__Get_InitialIndex__ESD;
	context->Active_Scroll = 0;
	context->Instance.Active_Scroll = Ft_Esd_ScrollSwitch__Get_Active_Scroll__ESD;
	context->Spinner = 0;
	context->Instance.Spinner = Ft_Esd_ScrollSwitch__Get_Spinner__ESD;
	context->New = 0x0;
	context->Instance.New = Ft_Esd_ScrollSwitch__Get_New__ESD;
	return context;
}

void Ft_Esd_ScrollSwitch__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Esd_ScrollSwitch__Set_Looping__ESD(void *context, ft_bool_t value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->Instance.Looping = value; }
void Ft_Esd_ScrollSwitch__Set_Count__ESD(void *context, int value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->Instance.Count = value; }
void Ft_Esd_ScrollSwitch__Set_Spacing__ESD(void *context, int value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->Instance.Spacing = value; }
void Ft_Esd_ScrollSwitch__Set_Touching__ESD(void *context, ft_bool_t value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->Instance.Touching = value; }
void Ft_Esd_ScrollSwitch__Set_Sensitivity__ESD(void *context, float value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->Instance.Sensitivity = value; }
void Ft_Esd_ScrollSwitch__Set_SwitchSpeed__ESD(void *context, int value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->Instance.SwitchSpeed = value; }
void Ft_Esd_ScrollSwitch__Set_ScrollXStart__ESD(void *context, int value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->Instance.ScrollXStart = value; }
void Ft_Esd_ScrollSwitch__Set_ScrollX__ESD(void *context, int value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->Instance.ScrollX = value; }
void Ft_Esd_ScrollSwitch__Set_ScrollXTarget__ESD(void *context, int value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->Instance.ScrollXTarget = value; }
void Ft_Esd_ScrollSwitch__Set_NewScrollX__ESD(void *context, int value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->Instance.NewScrollX = value; }
void Ft_Esd_ScrollSwitch__Set_Overflow__ESD(void *context, ft_int16_t value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->Instance.Overflow = value; }
void Ft_Esd_ScrollSwitch__Set_State__ESD(void *context, int value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->Instance.State = value; }
void Ft_Esd_ScrollSwitch__Set_RemovingWidget__ESD(void *context, Ft_Esd_Widget * value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->Instance.RemovingWidget = value; }
void Ft_Esd_ScrollSwitch__Set_Previous__ESD(void *context, Ft_Esd_Widget * value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->Instance.Previous = value; }
void Ft_Esd_ScrollSwitch__Set_Current__ESD(void *context, Ft_Esd_Widget * value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->Instance.Current = value; }
void Ft_Esd_ScrollSwitch__Set_Next__ESD(void *context, Ft_Esd_Widget * value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->Instance.Next = value; }
void Ft_Esd_ScrollSwitch__Set_Index__ESD(void *context, int value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->Instance.Index = value; }
void Ft_Esd_ScrollSwitch__Set_NewIndex__ESD(void *context, int value) { ((Ft_Esd_ScrollSwitch__ESD *)context)->Instance.NewIndex = value; }

#endif /* ESD_SIMULATION */

/* end of file */
