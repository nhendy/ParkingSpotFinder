#include "Ft_Esd.h"
#include "YesPage.h"
#include "global.h"
#include <string.h>
#include <stdlib.h>
void append(char* s, char c) {
        int len = strlen(s);
	if(len < 4) {
		if ((len == 0) & (c == '0')) {
		}
		else {
			s[len] = c;
			s[len+1] = '\0';
		}
	}
}
ESD_METHOD(YesPage_confirmationCode, Context = YesPage)
extern void YesPage_confirmationCode(YesPage *context){
	int num = atoi(cCode);
	context->confCodeInt = num;
}
ESD_METHOD(YesPage_Cancel_Pushed, Context = YesPage)
void YesPage_Cancel_Pushed(YesPage *context)
{
	cCode[0] = '\0';
}

ESD_METHOD(YesPage_OK_Pushed, Context = YesPage)
void YesPage_OK_Pushed(YesPage *context)
{

}

ESD_METHOD(YesPage_Num0_Pushed, Context = YesPage)
void YesPage_Num0_Pushed(YesPage *context)
{
	append(cCode, '0');
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


ESD_METHOD(YesPage_Back_Pushed, Context = YesPage)
void YesPage_Back_Pushed(YesPage *context)
{
	cCode[0] = '\0';
}

ESD_METHOD(YesPage_resetCCode_Signal, Context = YesPage)
void YesPage_resetCCode_Signal(YesPage *context)
{
	cCode[0] = '\0';
	context->confCodeInt = 0;
}


