#include "Ft_Esd.h"
#include "MainPage.h"

ESD_METHOD(MainPage_ESD_Push_Button_Pushed, Context = MainPage)

ESD_METHOD(MainPage_ESD_Push_Button_Pushed, Context = MainPage)
void MainPage_ESD_Push_Button_Pushed(MainPage *context)
{
	// ...
}

ESD_METHOD(MainPage_ESD_Push_Button_2_Pushed, Context = MainPage)

ESD_METHOD(MainPage_ESD_Push_Button_2_Pushed, Context = MainPage)
void MainPage_ESD_Push_Button_2_Pushed(MainPage *context)
{
	// ...
}

ESD_METHOD(MainPage_No_Push_Button_Pushed, Context = MainPage)
void MainPage_No_Push_Button_Pushed(MainPage *context)
{
	// ...
	printf("No is pushed\n");
}
