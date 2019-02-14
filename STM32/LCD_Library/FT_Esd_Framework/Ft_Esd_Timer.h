/*
This file is automatically generated
Ft_Esd_Timer
Header
*/

#ifndef Ft_Esd_Timer__H
#define Ft_Esd_Timer__H

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

ESD_ACTOR(Ft_Esd_Timer, Include = "Ft_Esd_Timer.h", Callback, DisplayName = "ESD Timer", Category = EsdUtilities, Icon = ":/icons/clock.png")
typedef struct
{
	void *Parent;
	ESD_SIGNAL(Fired)
	void(* Fired)(void *context);
	/* Time in milliseconds for the timer to fire */
	ESD_VARIABLE(TimeoutMs, Type = int, Default = 1000, Public)
	int TimeoutMs;
	/* Whether the timer repeats after it is fired */
	ESD_VARIABLE(Repeat, Type = ft_bool_t, Public)
	ft_bool_t Repeat;
} Ft_Esd_Timer;

void Ft_Esd_Timer__Initializer(Ft_Esd_Timer *context);

ESD_SLOT(Run)
void Ft_Esd_Timer_Run(Ft_Esd_Timer *context);

ESD_SLOT(Halt)
void Ft_Esd_Timer_Halt(Ft_Esd_Timer *context);

ESD_SLOT(End)
void Ft_Esd_Timer_End(Ft_Esd_Timer *context);

#endif /* Ft_Esd_Timer__H */

/* end of file */
