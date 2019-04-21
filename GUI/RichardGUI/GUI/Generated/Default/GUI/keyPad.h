/*
This file is automatically generated
keyPad
Header
*/

#ifndef keyPad__H
#define keyPad__H

#ifndef ESD_LOGIC
#define ESD_LOGIC(name, ...)
#define ESD_ACTOR(name, ...)
#define ESD_WIDGET(name, ...)
#define ESD_PAGE(name, ...)
#define ESD_APPLICATION(name, ...)
#define ESD_INPUT(name, ...)
#define ESD_OUTPUT(name, ...)
#define ESD_SLOT(name, ...)
#define ESD_SIGNAL(name, ...)
#define ESD_VARIABLE(name, ...)
#define ESD_WRITER(name, ...)
#endif

ESD_PAGE(keyPad, Include = "keyPad.h", Callback)
typedef struct
{
	void *Parent;
} keyPad;

void keyPad__Initializer(keyPad *context);

ESD_SLOT(Start)
void keyPad_Start(keyPad *context);

ESD_SLOT(Update)
void keyPad_Update(keyPad *context);

ESD_SLOT(Render)
void keyPad_Render(keyPad *context);

ESD_SLOT(Idle)
void keyPad_Idle(keyPad *context);

ESD_SLOT(End)
void keyPad_End(keyPad *context);

#endif /* keyPad__H */

/* end of file */