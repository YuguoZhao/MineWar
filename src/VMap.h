#ifndef _VMAP_H
#define _VMAP_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "View.h"
#include "ViewStack.h"
#include "Button.h"

typedef struct _VMap_t
{
	View_t super;
	View_t super_f;

	int mapIndex;
    bool updateMapIndexFlag;
	
	fp_onCreate onCreate;
	fp_onShow onShow;
	fp_onDraw onDraw;
	fp_procEvent procEvent;
	fp_sendEvent sendEvent;
} VMap_t;

void VMap_initWith(VMap_t *_self, int vid0, 
	int x0, int y0, int w0, int h0, Msg_t *msg0);

#ifdef __cplusplus
}
#endif
#endif	//_VMAP_H