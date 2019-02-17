#ifndef SwitchPage__H
#define SwitchPage__H

#include "Ft_Esd.h"

ESD_LOGIC(SwitchPage, Include = "SwitchPage.h", Category = _GroupHidden)
typedef struct
{
	void *Parent;
} SwitchPage;

void SwitchPage__Initializer(SwitchPage *context);

ESD_SLOT(Activate)
void SwitchPage_Activate(SwitchPage *context);

ESD_OUTPUT(Active, Type = int)
int SwitchPage_Active(SwitchPage *context);

#endif /* SwitchPage__H */

/* end of file */
