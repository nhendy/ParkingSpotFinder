#include "Ft_Esd.h"
#include "Ft_Esd_Image_Rotate.h"
#include "FT_Esd_Primitives.h"

ESD_METHOD(Ft_Esd_Image_Rotate_Render_Signal, Context = Ft_Esd_Image_Rotate)
void Ft_Esd_Image_Rotate_Render_Signal(Ft_Esd_Image_Rotate *context)
{
	Ft_Esd_BitmapCell bitmapCell = context->BitmapCell(context->Owner);
	if (!bitmapCell.Info)
		return;

    Ft_Esd_Render_BitmapRotate(bitmapCell, context->Color, context->Widget.GlobalRect, context->RotateAngle);
}

