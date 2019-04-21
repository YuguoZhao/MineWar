#ifndef _VMEDIT_H
#define _VMEDIT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "map.h"
#include "View.h"
#include "ViewStack.h"
#include "Button.h"
#include "TouchMtx.h"

typedef struct _VMEdit_t
{
	View_t super;
	View_t super_f;

	int itemId;
    int map[MAP_H][MAP_W];
    int mapIndex;
	
	fp_onCreate onCreate;
	fp_onShow onShow;
	fp_onDraw onDraw;
	fp_procEvent procEvent;
	fp_sendEvent sendEvent;
} VMEdit_t;

void VMEdit_initWith(VMEdit_t *_self, int vid0, 
	int x0, int y0, int w0, int h0, Msg_t *msg0);

#ifdef __cplusplus
}
#endif
#endif	//_VMEDIT_H