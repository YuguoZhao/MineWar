#ifndef _VCAL_H
#define _VCAL_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "map.h"
#include "View.h"
#include "ViewStack.h"
#include "Button.h"
#include "TouchMtx.h"

typedef struct _VCal_t
{
	View_t super;
	View_t super_f;

	int top;
    int line;
    int clear_count;
	
	fp_onCreate onCreate;
	fp_onShow onShow;
	fp_onDraw onDraw;
	fp_procEvent procEvent;
	fp_sendEvent sendEvent;
} VCal_t;

void VCal_initWith(VCal_t *_self, int vid0, 
	int x0, int y0, int w0, int h0, Msg_t *msg0);

#ifdef __cplusplus
}
#endif
#endif	//_VCAL_H