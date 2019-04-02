/*
This file is automatically generated
Ft_Esd_NumericLabel
C Source
*/

#include "Ft_Esd_NumericLabel.h"

#include "FT_Esd_CoPro_Cmds.h"
#include "FT_Esd_Dl.h"
#include "FT_Gpu.h"

extern void Ft_Esd_Noop(void *context);
Ft_Esd_Theme * Ft_Esd_NumericLabel_Theme__Default(void *context) { return Ft_Esd_Theme_GetCurrent(); }
ft_int16_t Ft_Esd_NumericLabel_X__Default(void *context) { return 0; }
ft_int16_t Ft_Esd_NumericLabel_Y__Default(void *context) { return 0; }
ft_int16_t Ft_Esd_NumericLabel_Width__Default(void *context) { return 120; }
ft_int16_t Ft_Esd_NumericLabel_Height__Default(void *context) { return 36; }
ft_int16_t Ft_Esd_NumericLabel_Font__Default(void *context) { return 27; }
ft_int32_t Ft_Esd_NumericLabel_Value__Default(void *context) { return 0L; }

Ft_Esd_Theme * Ft_Esd_Theme_GetCurrent();
Ft_Gpu_Hal_Context_t * Ft_Esd_GetHost();


void Ft_Esd_NumericLabel__Initializer(Ft_Esd_NumericLabel *context)
{
	context->Parent = 0;
	context->Theme = Ft_Esd_NumericLabel_Theme__Default;
	context->X = Ft_Esd_NumericLabel_X__Default;
	context->Y = Ft_Esd_NumericLabel_Y__Default;
	context->Width = Ft_Esd_NumericLabel_Width__Default;
	context->Height = Ft_Esd_NumericLabel_Height__Default;
	context->Font = Ft_Esd_NumericLabel_Font__Default;
	context->Value = Ft_Esd_NumericLabel_Value__Default;
}

ft_void_t Ft_Gpu_CoCmd_Number(Ft_Gpu_Hal_Context_t *, ft_int16_t, ft_int16_t, ft_int16_t, ft_uint16_t, ft_int32_t);

void Ft_Esd_NumericLabel_Render(Ft_Esd_NumericLabel *context)
{
	void *parent = context->Parent;
	ft_uint8_t alpha = 255;
	Ft_Esd_Dl_COLOR_A(alpha);
	Ft_Esd_Theme * theme = context->Theme(parent);
	ft_rgb32_t c = Ft_Esd_Theme_GetTextColor(theme);
	Ft_Esd_Dl_COLOR_RGB(c);
	Ft_Gpu_Hal_Context_t * phost = Ft_Esd_GetHost();
	ft_int16_t x = context->X(parent);
	ft_int16_t y = context->Y(parent);
	ft_int16_t font = context->Font(parent);
	ft_uint16_t options = 0;
	ft_int32_t n = context->Value(parent);
	Ft_Gpu_CoCmd_Number(phost, x, y, font, options, n);
}

#ifdef ESD_SIMULATION
#include <stdlib.h>

typedef struct
{
	Ft_Esd_NumericLabel Instance;
	Ft_Esd_Theme * Theme;
	ft_int16_t X;
	ft_int16_t Y;
	ft_int16_t Width;
	ft_int16_t Height;
	ft_int16_t Font;
	ft_int32_t Value;
} Ft_Esd_NumericLabel__ESD;

Ft_Esd_Theme * Ft_Esd_NumericLabel__Get_Theme__ESD(void *context) { return ((Ft_Esd_NumericLabel__ESD *)context)->Theme; }
void Ft_Esd_NumericLabel__Set_Theme__ESD(void *context, Ft_Esd_Theme * value) { ((Ft_Esd_NumericLabel__ESD *)context)->Theme = value; }
ft_int16_t Ft_Esd_NumericLabel__Get_X__ESD(void *context) { return ((Ft_Esd_NumericLabel__ESD *)context)->X; }
void Ft_Esd_NumericLabel__Set_X__ESD(void *context, ft_int16_t value) { ((Ft_Esd_NumericLabel__ESD *)context)->X = value; }
ft_int16_t Ft_Esd_NumericLabel__Get_Y__ESD(void *context) { return ((Ft_Esd_NumericLabel__ESD *)context)->Y; }
void Ft_Esd_NumericLabel__Set_Y__ESD(void *context, ft_int16_t value) { ((Ft_Esd_NumericLabel__ESD *)context)->Y = value; }
ft_int16_t Ft_Esd_NumericLabel__Get_Width__ESD(void *context) { return ((Ft_Esd_NumericLabel__ESD *)context)->Width; }
void Ft_Esd_NumericLabel__Set_Width__ESD(void *context, ft_int16_t value) { ((Ft_Esd_NumericLabel__ESD *)context)->Width = value; }
ft_int16_t Ft_Esd_NumericLabel__Get_Height__ESD(void *context) { return ((Ft_Esd_NumericLabel__ESD *)context)->Height; }
void Ft_Esd_NumericLabel__Set_Height__ESD(void *context, ft_int16_t value) { ((Ft_Esd_NumericLabel__ESD *)context)->Height = value; }
ft_int16_t Ft_Esd_NumericLabel__Get_Font__ESD(void *context) { return ((Ft_Esd_NumericLabel__ESD *)context)->Font; }
void Ft_Esd_NumericLabel__Set_Font__ESD(void *context, ft_int16_t value) { ((Ft_Esd_NumericLabel__ESD *)context)->Font = value; }
ft_int32_t Ft_Esd_NumericLabel__Get_Value__ESD(void *context) { return ((Ft_Esd_NumericLabel__ESD *)context)->Value; }
void Ft_Esd_NumericLabel__Set_Value__ESD(void *context, ft_int32_t value) { ((Ft_Esd_NumericLabel__ESD *)context)->Value = value; }

void *Ft_Esd_NumericLabel__Create__ESD()
{
	Ft_Esd_NumericLabel__ESD *context = (Ft_Esd_NumericLabel__ESD *)malloc(sizeof(Ft_Esd_NumericLabel__ESD));
	Ft_Esd_NumericLabel__Initializer(&context->Instance);
	context->Instance.Parent = context;
	context->Theme = Ft_Esd_Theme_GetCurrent();
	context->Instance.Theme = Ft_Esd_NumericLabel__Get_Theme__ESD;
	context->X = 0;
	context->Instance.X = Ft_Esd_NumericLabel__Get_X__ESD;
	context->Y = 0;
	context->Instance.Y = Ft_Esd_NumericLabel__Get_Y__ESD;
	context->Width = 120;
	context->Instance.Width = Ft_Esd_NumericLabel__Get_Width__ESD;
	context->Height = 36;
	context->Instance.Height = Ft_Esd_NumericLabel__Get_Height__ESD;
	context->Font = 27;
	context->Instance.Font = Ft_Esd_NumericLabel__Get_Font__ESD;
	context->Value = 0L;
	context->Instance.Value = Ft_Esd_NumericLabel__Get_Value__ESD;
	return context;
}

void Ft_Esd_NumericLabel__Destroy__ESD(void *context)
{
	free(context);
}


#endif /* ESD_SIMULATION */

/* end of file */
