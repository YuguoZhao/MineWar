#ifndef _VOPENING_H
#define _VOPENING_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "View.h"
#include "ViewStack.h"
#include "Button.h"

typedef struct _VOpening_t
{
	View_t super;
	View_t super_f;

	int mCounter;
    int mTick;
	
	fp_onCreate onCreate;
	fp_onDraw onDraw;
	fp_procEvent procEvent;
	fp_sendEvent sendEvent;
} VOpening_t;

void VOpening_initWith(VOpening_t *_self, int vid0, 
	int x0, int y0, int w0, int h0, Msg_t *msg0);

#ifdef __cplusplus
}
#endif
#endif	//_VOPENING_H