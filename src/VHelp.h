#ifndef _VHELP_H
#define _VHELP_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "View.h"
#include "ViewStack.h"
#include "Button.h"

typedef struct _VHelp_t
{
	View_t super;
	View_t super_f;
	
	fp_onCreate onCreate;
	fp_onShow onShow;
	fp_onDraw onDraw;
	fp_procEvent procEvent;
	fp_sendEvent sendEvent;
} VHelp_t;

void VHelp_initWith(VHelp_t *_self, int vid0, 
	int x0, int y0, int w0, int h0, Msg_t *msg0);

#ifdef __cplusplus
}
#endif
#endif	//_VHELP_H