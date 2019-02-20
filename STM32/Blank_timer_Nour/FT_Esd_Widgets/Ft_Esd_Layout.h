
// Early layouting code
// Subject to changes

#ifndef FT_ESD_LAYOUT_H
#define FT_ESD_LAYOUT_H

#include "Ft_Esd.h"

typedef struct Ft_Esd_LayoutChild
{
	// The widget
	void *Child;

	// Pointers to input functions
	ft_int16_t(* Width)(void *context);
	ft_int16_t(* Height)(void *context);

	// Pointers to slot functions
	void(* Update)(void *context);
	void(* Render)(void *context);

	// Linked list
	void *Previous;
	void *Next;

	// User state
	void *State;
	
} Ft_Esd_LayoutChild;
ESD_TYPE(Ft_Esd_LayoutChild *, Native = Pointer, Edit = None)

#endif /* FT_ESD_LAYOUT_H */

/* Nothing beyond this */
