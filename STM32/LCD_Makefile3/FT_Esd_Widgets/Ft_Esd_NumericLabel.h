/*
This file is automatically generated
DO NOT MODIFY BY HAND
Ft_Esd_NumericLabel
Header
*/

#ifndef Ft_Esd_NumericLabel__H
#define Ft_Esd_NumericLabel__H

#include "FT_DataTypes.h"
#include "FT_Gpu.h"
#include "Ft_Esd.h"
#include "Ft_Esd_DefaultTheme.h"
#include "Ft_Esd_Math.h"
#include "Ft_Esd_Theme.h"
#include "Ft_Esd_Widget.h"

#ifndef ESD_LOGIC
#define ESD_LOGIC(name, ...)
#define ESD_ACTOR(name, ...)
#define ESD_WIDGET(name, ...)
#define ESD_UI(name, ...)
#define ESD_PAGE(name, ...)
#define ESD_APPLICATION(name, ...)
#define ESD_INPUT(name, ...)
#define ESD_OUTPUT(name, ...)
#define ESD_SLOT(name, ...)
#define ESD_SIGNAL(name, ...)
#define ESD_VARIABLE(name, ...)
#define ESD_WRITER(name, ...)
#endif

#define Ft_Esd_NumericLabel_CLASSID 0x0560FBA3
ESD_SYMBOL(Ft_Esd_NumericLabel_CLASSID, Type = esd_classid_t)

/* Number based label widget */
ESD_WIDGET(Ft_Esd_NumericLabel, Include = "Ft_Esd_NumericLabel.h", Callback, DisplayName = "ESD Numeric Label", Category = EsdWidgets, Icon = ":/icons/ui-label.png", X = 0, Y = 0, Width = 120, Height = 36)
typedef struct
{
	union
	{
		void *Owner;
		Ft_Esd_Widget Widget;
	};
	ESD_INPUT(Theme, Type = Ft_Esd_Theme *, Default = Ft_Esd_Theme_GetCurrent)
	Ft_Esd_Theme *(* Theme)(void *context);
	ESD_VARIABLE(X, Type = ft_int16_t, Private)
	ft_int16_t X;
	ESD_VARIABLE(Y, Type = ft_int16_t, Private)
	ft_int16_t Y;
	ESD_VARIABLE(Option, Type = Ft_CoPro_Opt, Default = OPT_SIGNED, Private)
	ft_uint16_t Option;
	ESD_VARIABLE(Number, Type = char *, Private)
	char * Number;
	ESD_INPUT(Font, Type = ft_int16_t, Min = 16, Max = 34, Default = 27)
	ft_int16_t(* Font)(void *context);
	ESD_VARIABLE(FontHeight, Type = ft_int16_t, Private)
	ft_int16_t FontHeight;
	ESD_INPUT(AlignX, Type = Ft_AlignX_Opt, Default = OPT_ALIGN_LEFT)
	ft_uint16_t(* AlignX)(void *context);
	ESD_INPUT(AlignY, Type = Ft_AlignY_Opt, Default = OPT_ALIGN_CENTER)
	ft_uint16_t(* AlignY)(void *context);
	/* Automatically resize the height of the label to the text height (only for single-line labels) */
	ESD_INPUT(AutoResize, Type = Esd_AutoResize, Default = ESD_AUTORESIZE_HEIGHT)
	ft_uint8_t(* AutoResize)(void *context);
	ESD_VARIABLE(NDigit, Type = int, Min = 0, Max = 10, Private)
	int NDigit;
	ESD_INPUT(Value, DisplayName = "Integer value", Type = ft_int32_t, Default = 0)
	ft_int32_t(* Value)(void *context);
	/* Allow padding to specify no of digit set NoOfDigits */
	ESD_INPUT(EnablePadding, DisplayName = "EnablePadding", Type = ft_bool_t, Default = false)
	ft_bool_t(* EnablePadding)(void *context);
	/* Mini-Digits display */
	ESD_INPUT(NoOfDigits, DisplayName = "No Of Digits", Type = ft_int32_t, Min = 0, Max = 11, SingleStep = 1, Default = 5)
	ft_int32_t(* NoOfDigits)(void *context);
	/* Zero leading mode used in padding */
	ESD_INPUT(IsZeroLeading, DisplayName = "IsZeroLeading", Type = ft_bool_t, Default = false)
	ft_bool_t(* IsZeroLeading)(void *context);
	/* Hex display instead of decimal display */
	ESD_INPUT(IsHexDisplay, DisplayName = "IsHexDisplay", Type = ft_bool_t)
	ft_bool_t(* IsHexDisplay)(void *context);
} Ft_Esd_NumericLabel;

void Ft_Esd_NumericLabel__Initializer(Ft_Esd_NumericLabel *context);

ESD_SLOT(Start)
void Ft_Esd_NumericLabel_Start(Ft_Esd_NumericLabel *context);

ESD_SLOT(End)
void Ft_Esd_NumericLabel_End(Ft_Esd_NumericLabel *context);

ESD_SLOT(Render)
void Ft_Esd_NumericLabel_Render(Ft_Esd_NumericLabel *context);

ESD_SLOT(Update)
void Ft_Esd_NumericLabel_Update(Ft_Esd_NumericLabel *context);

#endif /* Ft_Esd_NumericLabel__H */

/* end of file */
