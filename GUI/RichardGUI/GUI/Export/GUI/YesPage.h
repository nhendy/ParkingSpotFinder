/*
This file is automatically generated
YesPage
Header
*/

#ifndef YesPage__H
#define YesPage__H

#include "Ft_Esd.h"
#include "Ft_Esd_Label.h"
#include "Ft_Esd_NumericLabel.h"
#include "Ft_Esd_PushButton.h"
#include "Ft_Esd_Theme.h"

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

ESD_PAGE(YesPage, Include = "YesPage.h", Callback)
typedef struct
{
	void *Parent;
	ESD_VARIABLE(Variable, Type = int, Private)
	int Variable;
	ESD_VARIABLE(Total, Type = int, Public)
	int Total;
	ESD_VARIABLE(OneIncrementer, Type = int, Default = 1, Private)
	int OneIncrementer;
	ESD_VARIABLE(Digits, Type = int, Default = -1, Private)
	int Digits;
	ESD_SIGNAL(KeyPadBack)
	void(* KeyPadBack)(void *context);
	ESD_SIGNAL(Confirmation)
	void(* Confirmation)(void *context);
	Ft_Esd_PushButton Num2;
	Ft_Esd_PushButton Num1;
	Ft_Esd_PushButton __1;
	Ft_Esd_PushButton __2;
	Ft_Esd_PushButton __3;
	Ft_Esd_PushButton __4;
	Ft_Esd_PushButton __5;
	Ft_Esd_PushButton __6;
	Ft_Esd_PushButton Back;
	Ft_Esd_PushButton __7;
	Ft_Esd_NumericLabel ESD_Numeric_Label;
	Ft_Esd_Label ESD_Label;
	Ft_Esd_PushButton __8;
	Ft_Esd_PushButton Cancel;
	Ft_Esd_PushButton OK;
} YesPage;

void YesPage__Initializer(YesPage *context);

ESD_SLOT(Start)
void YesPage_Start(YesPage *context);

ESD_SLOT(Update)
void YesPage_Update(YesPage *context);

ESD_SLOT(Render)
void YesPage_Render(YesPage *context);

ESD_SLOT(Idle)
void YesPage_Idle(YesPage *context);

ESD_SLOT(End)
void YesPage_End(YesPage *context);

#endif /* YesPage__H */

/* end of file */
