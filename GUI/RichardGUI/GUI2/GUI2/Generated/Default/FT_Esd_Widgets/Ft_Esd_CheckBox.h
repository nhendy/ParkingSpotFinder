/*
This file is automatically generated
Ft_Esd_CheckBox
Header
*/

#ifndef Ft_Esd_CheckBox__H
#define Ft_Esd_CheckBox__H

#include "FT_DataTypes.h"
#include "Ft_Esd.h"
#include "Ft_Esd_DefaultTheme.h"
#include "Ft_Esd_Label.h"
#include "Ft_Esd_Theme.h"
#include "Ft_Esd_TouchTag.h"

#ifndef ESD_LOGIC
#define ESD_LOGIC(name, ...)
#define ESD_ACTOR(name, ...)
#define ESD_WIDGET(name, ...)
#define ESD_PAGE(name, ...)
#define ESD_APPLICATION(name, ...)
#define ESD_INPUT(name, ...)
#define ESD_OUTPUT(name, ...)
#define ESD_SLOT(name, ...)
#define ESD_SIGNAL(name, ...)
#define ESD_VARIABLE(name, ...)
#define ESD_WRITER(name, ...)
#endif

/* Classic check box with label option */
ESD_WIDGET(Ft_Esd_CheckBox, Include = "Ft_Esd_CheckBox.h", Callback, DisplayName = "ESD Check Box", Category = EsdWidgets, DefaultSignal = Toggled)
typedef struct
{
	void *Parent;
	Ft_Esd_TouchTag Touch_Tag;
	ESD_INPUT(Theme, Type = Ft_Esd_Theme *, Default = Ft_Esd_Theme_GetCurrent)
	Ft_Esd_Theme *(* Theme)(void *context);
	ESD_INPUT(Font, Type = ft_uint8_t, Default = 27)
	ft_uint8_t(* Font)(void *context);
	ESD_INPUT(X, Type = int, Min = 0)
	int(* X)(void *context);
	ESD_INPUT(Y, Type = int, Min = 0)
	int(* Y)(void *context);
	ESD_INPUT(Width, Type = int, Min = 10, Default = 20)
	int(* Width)(void *context);
	ESD_INPUT(Height, Type = int, Min = 10, Default = 20)
	int(* Height)(void *context);
	ESD_INPUT(Alpha, Type = ft_uint8_t, Min = 0, Max = 255, SingleStep = 1, Default = 255)
	ft_uint8_t(* Alpha)(void *context);
	ESD_INPUT(Text, Type = char *, Default = "Option")
	char *(* Text)(void *context);
	ESD_VARIABLE(Value, Type = ft_bool_t, Default = false, Public)
	ft_bool_t Value;
	ESD_SIGNAL(Toggled)
	void(* Toggled)(void *context);
	ESD_WRITER(Changed, Type = ft_bool_t)
	void(* Changed)(void *context, ft_bool_t value);
	Ft_Esd_Label ESD_Label;
} Ft_Esd_CheckBox;

void Ft_Esd_CheckBox__Initializer(Ft_Esd_CheckBox *context);

ESD_SLOT(Render)
void Ft_Esd_CheckBox_Render(Ft_Esd_CheckBox *context);

ESD_SLOT(Start)
void Ft_Esd_CheckBox_Start(Ft_Esd_CheckBox *context);

ESD_SLOT(Update)
void Ft_Esd_CheckBox_Update(Ft_Esd_CheckBox *context);

ESD_SLOT(End)
void Ft_Esd_CheckBox_End(Ft_Esd_CheckBox *context);

ESD_SLOT(Toggle)
void Ft_Esd_CheckBox_Toggle(Ft_Esd_CheckBox *context);

#endif /* Ft_Esd_CheckBox__H */

/* end of file */
