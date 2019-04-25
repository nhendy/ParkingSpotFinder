#include "Ft_Esd.h"
#include "YesPage.h"
#include "global.h"
void append(char* s, char c) {
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

ESD_METHOD(YesPage_OK_Pushed, Context = YesPage)
void YesPage_OK_Pushed(YesPage *context)
{
}

ESD_METHOD(YesPage_Num1_Pushed, Context = YesPage)
void YesPage_Num1_Pushed(YesPage *context)
{
	append(cCode, '1');
}




ESD_METHOD(YesPage_Num2_Pushed, Context = YesPage)
void YesPage_Num2_Pushed(YesPage *context)
{
	append(cCode, '2');
}


ESD_METHOD(YesPage_Num3_Pushed, Context = YesPage)
void YesPage_Num3_Pushed(YesPage *context)
{
	append(cCode, '3');
}

ESD_METHOD(YesPage_Num4_Pushed, Context = YesPage)
void YesPage_Num4_Pushed(YesPage *context)
{
	append(cCode, '4');
}

ESD_METHOD(YesPage_Num5_Pushed, Context = YesPage)
void YesPage_Num5_Pushed(YesPage *context)
{
	append(cCode, '5');
}

ESD_METHOD(YesPage_Num6_Pushed, Context = YesPage)
void YesPage_Num6_Pushed(YesPage *context)
{
	append(cCode, '6');
}

ESD_METHOD(YesPage_Num7_Pushed, Context = YesPage)
void YesPage_Num7_Pushed(YesPage *context)
{
	append(cCode, '7');
}

ESD_METHOD(YesPage_Num8_Pushed, Context = YesPage)
void YesPage_Num8_Pushed(YesPage *context)
{
	append(cCode, '8');
}

ESD_METHOD(YesPage_Num9_Pushed, Context = YesPage)
void YesPage_Num9_Pushed(YesPage *context)
{
	append(cCode, '9');
}

ESD_METHOD(YesPage_Num0_Pushed, Context = YesPage)
void YesPage_Num0_Pushed(YesPage *context)
{
	append(cCode, '0');
}

ESD_METHOD(YesPage_Cancel_Pushed, Context = YesPage)
void YesPage_Cancel_Pushed(YesPage *context)
{
	cCode[0] = '\0';
}



