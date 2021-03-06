/*
This file is automatically generated
LayoutMargin
Header
*/

#ifndef LayoutMargin__H
#define LayoutMargin__H

#include "Ft_Esd.h"

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

ESD_LOGIC(LayoutMargin, Include = "LayoutMargin.h", Callback, Category = _GroupHidden)
typedef struct
{
	void *Parent;
	ESD_INPUT(X, Type = int)
	int(* X)(void *context);
	ESD_INPUT(Y, Type = int)
	int(* Y)(void *context);
	ESD_INPUT(Width, Type = int)
	int(* Width)(void *context);
	ESD_INPUT(Height, Type = int)
	int(* Height)(void *context);
	ESD_INPUT(Margin, Type = int)
	int(* Margin)(void *context);
} LayoutMargin;

void LayoutMargin__Initializer(LayoutMargin *context);

ESD_OUTPUT(OutX, Type = int)
int LayoutMargin_OutX(LayoutMargin *context);

ESD_OUTPUT(OutY, Type = int)
int LayoutMargin_OutY(LayoutMargin *context);

ESD_OUTPUT(OutWidth, Type = int)
int LayoutMargin_OutWidth(LayoutMargin *context);

ESD_OUTPUT(OutHeight, Type = int)
int LayoutMargin_OutHeight(LayoutMargin *context);

#endif /* LayoutMargin__H */

/* end of file */
