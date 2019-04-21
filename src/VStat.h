#ifndef _VSTAT_H
#define _VSTAT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "view.h"
#include "ViewStack.h"
#include "Button.h"

typedef struct _VStat_t
{
	View_t super;
	View_t super_f;

	int top;
	int line;
	
	fp_onCreate onCreate;
	fp_onShow onShow;
	fp_onDraw onDraw;
	fp_procEvent procEvent;
	fp_sendEvent sendEvent;
} VStat_t;

void VStat_initWith(VStat_t *_self, int vid0, 
	int x0, int y0, int w0, int h0, Msg_t *msg0);

#ifdef __cplusplus
}
#endif
#endif	//_VSTAT_H