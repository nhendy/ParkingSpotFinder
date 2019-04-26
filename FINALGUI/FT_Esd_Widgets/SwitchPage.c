#include "SwitchPage.h"

static SwitchPage *s_ActiveSwitchPage = 0;

void SwitchPage__Initializer(SwitchPage *context)
{
	context->Parent = 0;
}

void SwitchPage_Activate(SwitchPage *context)
{
	s_ActiveSwitchPage = context;
}

int SwitchPage_Active(SwitchPage *context)
{
	return context == s_ActiveSwitchPage;
}

/* end of file */
