#include "Ft_Esd.h"
#include "MainPage.h"
#include "global.h"
int confirmationCode = 0;
int parkingSpotID = 0;
char cCode[4] = "";
ESD_METHOD(MainPage_MainPage_Yes_Pushed, Context = MainPage)
void MainPage_MainPage_Yes_Pushed(MainPage *context)
{
	cCode[0] = '\0';
}

ESD_METHOD(MainPage_MainPage_No_Pushed, Context = MainPage)
void MainPage_MainPage_No_Pushed(MainPage *context)
{
	cCode[0] = 'n';
	cCode[1] = '\0';
}
