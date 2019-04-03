/*
This file is automatically generated
MainPage
Header
*/

#ifndef MainPage__H
#define MainPage__H

#include "Ft_Esd.h"
#include "Ft_Esd_Label.h"
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

ESD_PAGE(MainPage, Include = "MainPage.h", Callback)
typedef struct
{
	void *Parent;
	ESD_SIGNAL(keyPad)
	void(* keyPad)(void *context);
	Ft_Esd_Label ESD_Label;
	Ft_Esd_PushButton MainPage_Yes;
	Ft_Esd_PushButton MainPage_No;
} MainPage;

void MainPage__Initializer(MainPage *context);

ESD_SLOT(Start)
void MainPage_Start(MainPage *context);

ESD_SLOT(Update)
void MainPage_Update(MainPage *context);

ESD_SLOT(Render)
void MainPage_Render(MainPage *context);

ESD_SLOT(Idle)
void MainPage_Idle(MainPage *context);

ESD_SLOT(End)
void MainPage_End(MainPage *context);

#endif /* MainPage__H */

/* end of file */
