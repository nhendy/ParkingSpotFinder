#include "Ft_Esd.h"
#include "YesPage.h"
#include "global.h"

ESD_METHOD(YesPage_Cancel_Pushed, Context = YesPage)
void YesPage_Cancel_Pushed(YesPage *context)
{
	// ...
}

ESD_METHOD(YesPage_OK_Pushed, Context = YesPage)
void YesPage_OK_Pushed(YesPage *context)
{
	confirmationCode = context->Total;
}
