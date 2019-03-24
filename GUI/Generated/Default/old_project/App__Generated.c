/*
This file is automatically generated
App
C Source
*/

#include "App.h"

#include "stdlib.h"

extern void Ft_Esd_Noop(void *context);
extern void Ft_Esd_Spinner_Popup();

static int App_NoPage_Message__Property(void *context) { return 1234L; }

static void App_MainMenu_Yes__Signal(void *context);
static void App_MainMenu_No__Signal(void *context);

#define MainMenu__ID 1
#define YesPage__ID 2
#define NoPage__ID 3

void App__Initializer(App *context)
{
	context->Parent = 0;
	context->_ActivePage = 0;
	context->MainMenu = 0;
	context->MainMenu__Active = 0;
	context->YesPage = 0;
	context->YesPage__Active = 0;
	context->NoPage = 0;
	context->NoPage__Active = 0;
}

static void App__MainMenu__Validate(App *context)
{
	void *parent = context->Parent;
	if (!context->MainMenu)
	{
		context->MainMenu = (MainMenu *)malloc(sizeof(MainMenu));
		MainMenu__Initializer(context->MainMenu);
		context->MainMenu->Parent = context;
		context->MainMenu->Yes = App_MainMenu_Yes__Signal;
		context->MainMenu->No = App_MainMenu_No__Signal;
		MainMenu_Start(context->MainMenu);
	}
}

static void App__MainMenu__Create(App *context)
{
	App__MainMenu__Validate(context);
	context->MainMenu__Active = 1;
}

static void App__MainMenu__Destroy(App *context, int final)
{
	if (context->MainMenu__Active)
	{
		context->MainMenu__Active = 0;
	}
	if (context->MainMenu)
	{
		MainMenu_End(context->MainMenu);
		free(context->MainMenu);
		context->MainMenu = 0;
	}
}

static void App__YesPage__Validate(App *context)
{
	void *parent = context->Parent;
	if (!context->YesPage)
	{
		context->YesPage = (YesPage *)malloc(sizeof(YesPage));
		YesPage__Initializer(context->YesPage);
		context->YesPage->Parent = context;
		YesPage_Start(context->YesPage);
	}
}

static void App__YesPage__Create(App *context)
{
	App__YesPage__Validate(context);
	context->YesPage__Active = 1;
}

static void App__YesPage__Destroy(App *context, int final)
{
	if (context->YesPage__Active)
	{
		context->YesPage__Active = 0;
	}
	if (context->YesPage)
	{
		YesPage_End(context->YesPage);
		free(context->YesPage);
		context->YesPage = 0;
	}
}

static void App__NoPage__Validate(App *context)
{
	void *parent = context->Parent;
	if (!context->NoPage)
	{
		context->NoPage = (NoPage *)malloc(sizeof(NoPage));
		NoPage__Initializer(context->NoPage);
		context->NoPage->Parent = context;
		context->NoPage->Message = App_NoPage_Message__Property;
		NoPage_Start(context->NoPage);
	}
}

static void App__NoPage__Create(App *context)
{
	App__NoPage__Validate(context);
	context->NoPage__Active = 1;
}

static void App__NoPage__Destroy(App *context, int final)
{
	if (context->NoPage__Active)
	{
		context->NoPage__Active = 0;
	}
	if (context->NoPage)
	{
		NoPage_End(context->NoPage);
		free(context->NoPage);
		context->NoPage = 0;
	}
}

void App_Start__Builtin(App *context)
{
	void *parent = context->Parent;
	if ((context->_ActivePage == MainMenu__ID))
		App__MainMenu__Create(context);
	if ((context->_ActivePage == YesPage__ID))
		App__YesPage__Create(context);
	if ((context->_ActivePage == NoPage__ID))
		App__NoPage__Create(context);
}

void App_Update(App *context)
{
	void *parent = context->Parent;
	if ((!!context->MainMenu__Active) != ((context->_ActivePage == MainMenu__ID)))
	{
		if (!context->MainMenu__Active)
			App__MainMenu__Create(context);
		else
			App__MainMenu__Destroy(context, 0);
	}
	if ((!!context->YesPage__Active) != ((context->_ActivePage == YesPage__ID)))
	{
		if (!context->YesPage__Active)
			App__YesPage__Create(context);
		else
			App__YesPage__Destroy(context, 0);
	}
	if ((!!context->NoPage__Active) != ((context->_ActivePage == NoPage__ID)))
	{
		if (!context->NoPage__Active)
			App__NoPage__Create(context);
		else
			App__NoPage__Destroy(context, 0);
	}
	if (context->MainMenu__Active)
		MainMenu_Update(context->MainMenu);
	if (context->YesPage__Active)
		YesPage_Update(context->YesPage);
	if (context->NoPage__Active)
		NoPage_Update(context->NoPage);
	if (!context->MainMenu__Active && (((context->_ActivePage == MainMenu__ID))))
	{
		Ft_Esd_Spinner_Popup();
	}
	if (!context->YesPage__Active && (((context->_ActivePage == YesPage__ID))))
	{
		Ft_Esd_Spinner_Popup();
	}
	if (!context->NoPage__Active && (((context->_ActivePage == NoPage__ID))))
	{
		Ft_Esd_Spinner_Popup();
	}
}

void App_Render(App *context)
{
	void *parent = context->Parent;
	if (context->MainMenu__Active)
		MainMenu_Render(context->MainMenu);
	if (context->YesPage__Active)
		YesPage_Render(context->YesPage);
	if (context->NoPage__Active)
		NoPage_Render(context->NoPage);
}

void App_Idle(App *context)
{
	void *parent = context->Parent;
	if (context->MainMenu__Active)
		MainMenu_Idle(context->MainMenu);
	if (context->YesPage__Active)
		YesPage_Idle(context->YesPage);
	if (context->NoPage__Active)
		NoPage_Idle(context->NoPage);
}

void App_End(App *context)
{
	void *parent = context->Parent;
	if (context->MainMenu__Active)
		App__MainMenu__Destroy(context, 1);
	if (context->YesPage__Active)
		App__YesPage__Destroy(context, 1);
	if (context->NoPage__Active)
		App__NoPage__Destroy(context, 1);
}

void App_Start(App *context)
{
	void *parent = context->Parent;
	App_Start__Builtin(context);
	context->_ActivePage = MainMenu__ID;
}

void App_MainMenu_Yes__Signal(void *c)
{
	App *context = (App *)c;
	void *parent = context->Parent;
	context->_ActivePage = YesPage__ID;
}

void App_MainMenu_No__Signal(void *c)
{
	App *context = (App *)c;
	void *parent = context->Parent;
	context->_ActivePage = NoPage__ID;
}

static App application;

void Ft_Main__Start()
{
	App__Initializer(&application);
	App_Start(&application);
}

void Ft_Main__Update()
{
	App_Update(&application);
}

void Ft_Main__Render()
{
	App_Render(&application);
}

void Ft_Main__Idle()
{
	App_Idle(&application);
}

void Ft_Main__End()
{
	App_End(&application);
}

#ifdef ESD_SIMULATION
#include <stdlib.h>

typedef struct
{
	App Instance;
} App__ESD;


void *App__Create__ESD()
{
	App__ESD *context = (App__ESD *)malloc(sizeof(App__ESD));
	App__Initializer(&context->Instance);
	context->Instance.Parent = context;
	return context;
}

void App__Destroy__ESD(void *context)
{
	free(context);
}


#endif /* ESD_SIMULATION */

/* end of file */
