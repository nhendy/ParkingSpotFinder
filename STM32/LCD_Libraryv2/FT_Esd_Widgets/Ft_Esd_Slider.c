#include "Ft_Esd.h"
#include "Ft_Esd_Slider.h"

#include "Ft_Esd_TouchTag.h"

#include <stdio.h>

ESD_METHOD(Ft_Esd_Slider_Update_Signal, Context = Ft_Esd_Slider)
void Ft_Esd_Slider_Update_Signal(Ft_Esd_Slider *context)
{
	if (Ft_Esd_TouchTag_Touching(&context->TouchTag))
	{
		ft_int32_t width = context->Width(context->Parent) - context->Height(context->Parent);
		ft_int16_t touchX = Ft_Esd_TouchTag_TouchX(&context->TouchTag);
		ft_int16_t touchY = Ft_Esd_TouchTag_TouchY(&context->TouchTag);
		ft_int32_t range = context->Range(context->Parent);
		ft_int32_t touchDelta = touchX - context->PreviousX;
		ft_int32_t valueDelta = (touchDelta * range) / width;
		ft_int32_t newValue = context->PreviousValue + valueDelta;
		if (newValue < 0) newValue = 0;
		else if (newValue > range) newValue = range;
		context->Value = newValue;
		context->Changed(context->Parent, context->Value);
	}
}

ESD_METHOD(Ft_Esd_Slider_ClampedValue, Context = Ft_Esd_Slider, Type = ft_int16_t)
ft_int16_t Ft_Esd_Slider_ClampedValue(Ft_Esd_Slider *context)
{
	ft_int16_t value = context->Value;
	ft_int16_t range = context->Range(context->Parent);
	if (value < 0) return 0;
	if (value > range) return range;
	return value;
}
