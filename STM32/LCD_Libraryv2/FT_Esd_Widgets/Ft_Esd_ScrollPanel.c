#include "Ft_Esd.h"
#include "Ft_Esd_ScrollPanel.h"
#include "Ft_Esd_Layout.h"
#include "Ft_Esd_Dl.h"
#include "Ft_Esd_TouchArea.h"

#include <stdlib.h>

extern Ft_Gpu_Hal_Context_t *Ft_Esd_Host;

#define FT_ESD_SCROLLPANEL_SCISSOR 2

ESD_METHOD(Ft_Esd_ScrollPanel_Update_Scroll, Context = Ft_Esd_ScrollPanel)
void Ft_Esd_ScrollPanel_Update_Scroll(Ft_Esd_ScrollPanel *context)
{
	ft_bool_t touching = context->TouchArea.Touching;
	if (touching)
	{
		ft_int16_t touchY = Ft_Esd_TouchArea_TouchY(&context->TouchArea);
		ft_int16_t diffY = touchY - context->PreviousTouchY;
		context->OffsetY = context->PreviousOffsetY - diffY;
		context->OffsetYChanged(context->Parent, context->OffsetY);
		if (diffY > 5 || diffY < -5)
		{
			// Cancel any ongoing button presses
			Ft_Esd_TouchTag_SuppressCurrentTags();
		}
	}
	int offsetYRange = context->CurrentY - context->Height(context->Parent) + context->Margin(context->Parent);
	context->OffsetYRange = offsetYRange > 0 ? offsetYRange : 0;
}

ESD_METHOD(Ft_Esd_ScrollPanel_Update_Contents, Context = Ft_Esd_ScrollPanel)
void Ft_Esd_ScrollPanel_Update_Contents(Ft_Esd_ScrollPanel *context)
{
	Ft_Esd_LayoutChild *last = context->First;
	while (last)
	{
		context->Current = last;
		if (last->Update)
		{
			last->Update(last->Child);
		}
		last = last->Next;
	}
}

ESD_METHOD(Ft_Esd_ScrollPanel_Render_Contents, Context = Ft_Esd_ScrollPanel)
void Ft_Esd_ScrollPanel_Render_Contents(Ft_Esd_ScrollPanel *context)
{
	Ft_Gpu_Hal_Context_t *phost = Ft_Esd_Host;
	Ft_Esd_LayoutChild *last = context->First;
	context->CurrentY = 0;
	context->CurrentX = 0;
	ft_int16_t boundWidth = context->Width(context->Parent);
	ft_int16_t boundHeight = context->Height(context->Parent);
	ft_int16_t columns = context->Columns(context->Parent);
	ft_int16_t scissorX = context->X(context->Parent) + FT_ESD_SCROLLPANEL_SCISSOR;
	ft_int16_t scissorY = context->Y(context->Parent) + FT_ESD_SCROLLPANEL_SCISSOR;
	ft_int16_t scissorWidth = boundWidth - FT_ESD_SCROLLPANEL_SCISSOR * 2;
	ft_int16_t scissorHeight = boundHeight - FT_ESD_SCROLLPANEL_SCISSOR * 2;
	Ft_Esd_Dl_SAVE_CONTEXT();
	Ft_Gpu_Hal_WrCmd32(phost, SCISSOR_XY(scissorX, scissorY));
	Ft_Gpu_Hal_WrCmd32(phost, SCISSOR_SIZE(scissorWidth, scissorHeight));
	int count = 0;
	while (last)
	{
		context->Current = last;
		if (last->Render)
		{
		    if ( ((count+1)%(columns))==0 ){
				ft_int16_t height = last->Height(context->Parent);
				ft_int16_t bottom = context->CurrentY + height;
				if (bottom >= context->OffsetY && context->CurrentY < (context->OffsetY + boundHeight - context->Margin(context->Parent) * 2) )
				{
					last->Render(last->Child);
				}
				context->CurrentY = bottom + context->Margin(context->Parent);
				context->CurrentX = 0;
		    }
			else
		    {
				ft_int16_t width = last->Width(context->Parent);
				ft_int16_t right = context->CurrentX + width;
				ft_int16_t height = last->Height(context->Parent);
				ft_int16_t bottom = context->CurrentY + height;
				last->Render(last->Child);
				context->CurrentX = right + context->Margin(context->Parent);
		    }
		}
		last = last->Next;
		count++;
	}
	Ft_Esd_Dl_RESTORE_CONTEXT();
}

void Ft_Esd_ScrollPanel_Add(Ft_Esd_ScrollPanel *context, Ft_Esd_LayoutChild *child)
{
	Ft_Esd_LayoutChild *last = context->First;
	if (last)
	{
		while (last->Next)
		{
			last = last->Next;
		}
		last->Next = child;
		child->Previous = last;
	}
	else
	{
		context->First = child;
	}
}

void Ft_Esd_ScrollPanel_Remove(Ft_Esd_ScrollPanel *context, Ft_Esd_LayoutChild *child)
{
	Ft_Esd_LayoutChild *previous = child->Previous;
	Ft_Esd_LayoutChild *next = child->Next;
	if (previous)
	{
		previous->Next = next;
	}
	if (next)
	{
		next->Previous = previous;
	}
	if (context->Current == child)
	{
		context->Current = child->Previous;
	}
	if (context->First == child)
	{
		context->First = child->Next;
	}
}

ft_int16_t Ft_Esd_ScrollPanel_ChildX(Ft_Esd_ScrollPanel *context)
{
	return context->X(context->Parent) + context->CurrentX + context->Margin(context->Parent);
}

ft_int16_t Ft_Esd_ScrollPanel_ChildY(Ft_Esd_ScrollPanel *context)
{
	return context->Y(context->Parent) + context->CurrentY - context->OffsetY + context->Margin(context->Parent);
}

ft_int16_t Ft_Esd_ScrollPanel_ChildWidth(Ft_Esd_ScrollPanel *context)
{
	return context->Width(context->Parent) - (context->Margin(context->Parent) * 2);
}

ft_int16_t Ft_Esd_ScrollPanel_ChildHeight(Ft_Esd_ScrollPanel *context)
{
	return context->Current->Height(context->Parent);
}
