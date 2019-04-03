/*
This file is automatically generated
MainPage
C Source
*/

#include "MainPage.h"

#include "FT_Esd_Primitives.h"

extern void Ft_Esd_Noop(void *context);

Ft_Esd_Theme * Ft_Esd_Theme_GetCurrent();
static ft_int16_t MainPage_MainPage_Yes_X__Property(void *context) { return 250; }
static ft_int16_t MainPage_MainPage_Yes_Y__Property(void *context) { return 280; }
static ft_int16_t MainPage_MainPage_Yes_Width__Property(void *context) { return 100; }
static ft_int16_t MainPage_MainPage_Yes_Height__Property(void *context) { return 50; }
static const char * MainPage_MainPage_Yes_Text__Property(void *context) { return "Yes"; }
static ft_int16_t MainPage_ESD_Label_Font__Property(void *context) { return 31; }
static const char * MainPage_ESD_Label_Text__Property(void *context) { return "Have you reserved a spot?"; }
static ft_int16_t MainPage_ESD_Label_X__Property(void *context) { return 250; }
static ft_int16_t MainPage_ESD_Label_Y__Property(void *context) { return 150; }
static ft_int16_t MainPage_ESD_Label_Width__Property(void *context) { return 300; }
static ft_int16_t MainPage_ESD_Label_Height__Property(void *context) { return 50; }
static ft_uint16_t MainPage_ESD_Label_AlignX__Property(void *context) { return OPT_ALIGN_CENTER; }
static ft_int16_t MainPage_MainPage_No_X__Property(void *context) { return 450; }
static ft_int16_t MainPage_MainPage_No_Y__Property(void *context) { return 280; }
static ft_int16_t MainPage_MainPage_No_Width__Property(void *context) { return 100; }
static ft_int16_t MainPage_MainPage_No_Height__Property(void *context) { return 50; }
static const char * MainPage_MainPage_No_Text__Property(void *context) { return "No"; }

static void MainPage_MainPage_Yes_Pushed__Signal(void *context);
static void MainPage_MainPage_No_Pushed__Signal(void *context);

void MainPage__Initializer(MainPage *context)
{
	context->Parent = 0;
	context->keyPad = Ft_Esd_Noop;
	context->Confirmation = Ft_Esd_Noop;
	Ft_Esd_PushButton__Initializer(&context->MainPage_Yes);
	context->MainPage_Yes.Parent = context;
	context->MainPage_Yes.X = MainPage_MainPage_Yes_X__Property;
	context->MainPage_Yes.Y = MainPage_MainPage_Yes_Y__Property;
	context->MainPage_Yes.Width = MainPage_MainPage_Yes_Width__Property;
	context->MainPage_Yes.Height = MainPage_MainPage_Yes_Height__Property;
	context->MainPage_Yes.Text = MainPage_MainPage_Yes_Text__Property;
	context->MainPage_Yes.Pushed = MainPage_MainPage_Yes_Pushed__Signal;
	Ft_Esd_Label__Initializer(&context->ESD_Label);
	context->ESD_Label.Parent = context;
	context->ESD_Label.Font = MainPage_ESD_Label_Font__Property;
	context->ESD_Label.Text = MainPage_ESD_Label_Text__Property;
	context->ESD_Label.X = MainPage_ESD_Label_X__Property;
	context->ESD_Label.Y = MainPage_ESD_Label_Y__Property;
	context->ESD_Label.Width = MainPage_ESD_Label_Width__Property;
	context->ESD_Label.Height = MainPage_ESD_Label_Height__Property;
	context->ESD_Label.AlignX = MainPage_ESD_Label_AlignX__Property;
	Ft_Esd_PushButton__Initializer(&context->MainPage_No);
	context->MainPage_No.Parent = context;
	context->MainPage_No.X = MainPage_MainPage_No_X__Property;
	context->MainPage_No.Y = MainPage_MainPage_No_Y__Property;
	context->MainPage_No.Width = MainPage_MainPage_No_Width__Property;
	context->MainPage_No.Height = MainPage_MainPage_No_Height__Property;
	context->MainPage_No.Text = MainPage_MainPage_No_Text__Property;
	context->MainPage_No.Pushed = MainPage_MainPage_No_Pushed__Signal;
}

void MainPage_MainPage_Yes_Pushed(MainPage *context);
void MainPage_MainPage_No_Pushed(MainPage *context);
ft_void_t Ft_Esd_Render_RectangleF(ft_int32_f4_t, ft_int32_f4_t, ft_int32_f4_t, ft_int32_f4_t, ft_int32_f4_t, ft_argb32_t);

void MainPage_Start(MainPage *context)
{
	void *parent = context->Parent;
	Ft_Esd_PushButton_Start(&context->MainPage_Yes);
	Ft_Esd_PushButton_Start(&context->MainPage_No);
}

void MainPage_Update(MainPage *context)
{
	void *parent = context->Parent;
	Ft_Esd_PushButton_Update(&context->MainPage_Yes);
	Ft_Esd_PushButton_Update(&context->MainPage_No);
}

void MainPage_Render(MainPage *context)
{
	void *parent = context->Parent;
	ft_int32_f4_t x = (1 * (1 << 4) + 0x6);
	ft_int32_f4_t y = 0;
	ft_int32_f4_t width = (800 * (1 << 4) + 0x0);
	ft_int32_f4_t height = (480 * (1 << 4) + 0x0);
	ft_int32_f4_t radius = (4 * (1 << 4) + 0x0);
	ft_argb32_t color = 0xffc28e0eUL;
	Ft_Esd_Render_RectangleF(x, y, width, height, radius, color);
	Ft_Esd_PushButton_Render(&context->MainPage_Yes);
	Ft_Esd_Label_Render(&context->ESD_Label);
	Ft_Esd_PushButton_Render(&context->MainPage_No);
}

void MainPage_Idle(MainPage *context)
{
	void *parent = context->Parent;
}

void MainPage_End(MainPage *context)
{
	void *parent = context->Parent;
	Ft_Esd_PushButton_End(&context->MainPage_Yes);
	Ft_Esd_PushButton_End(&context->MainPage_No);
}

void MainPage_MainPage_Yes_Pushed__Signal(void *c)
{
	MainPage *context = (MainPage *)c;
	void *parent = context->Parent;
	context->keyPad(parent);
	MainPage_MainPage_Yes_Pushed(context);
}

void MainPage_MainPage_No_Pushed__Signal(void *c)
{
	MainPage *context = (MainPage *)c;
	void *parent = context->Parent;
	MainPage_MainPage_No_Pushed(context);
	context->Confirmation(parent);
}

#ifdef ESD_SIMULATION
#include <stdlib.h>

typedef struct
{
	MainPage Instance;
} MainPage__ESD;


void *MainPage__Create__ESD()
{
	MainPage__ESD *context = (MainPage__ESD *)malloc(sizeof(MainPage__ESD));
	MainPage__Initializer(&context->Instance);
	context->Instance.Parent = context;
	return context;
}

void MainPage__Destroy__ESD(void *context)
{
	free(context);
}


#endif /* ESD_SIMULATION */

/* end of file */
