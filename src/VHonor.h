#ifndef _VHONOR_H
#define _VHONOR_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "View.h"
#include "ViewStack.h"
#include "Button.h"

typedef struct _VHonor_t
{
	View_t super;
	View_t super_f;

	int starIndex;
	
	fp_onCreate onCreate;
	fp_onDraw onDraw;
	fp_procEvent procEvent;
	fp_sendEvent sendEvent;
} VHonor_t;

void VHonor_initWith(VHonor_t *_self, int vid0, 
	int x0, int y0, int w0, int h0, Msg_t *msg0);

#ifdef __cplusplus
}
#endif
#endif	//_VHONOR_H