#include "Ft_Esd.h"
#include "MainPage.h"
#include "global.h"
int confirmationCode = 0;
int parkingSpotID = 0;
char cCode[10] = "";
ESD_METHOD(MainPage_MainPage_Yes_Pushed, Context = MainPage)
void MainPage_MainPage_Yes_Pushed(MainPage *context)
{
	// ...
	cCode = 
}

ESD_METHOD(MainPage_MainPage_No_Pushed, Context = MainPage)
void MainPage_MainPage_No_Pushed(MainPage *context)
{
	confirmationCode = -1;
}
