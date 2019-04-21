#ifndef _VQEDIT_H
#define _VQEDIT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "map.h"
#include "View.h"
#include "ViewStack.h"
#include "Button.h"
#include "TouchMtx.h"

typedef struct _VQEdit_t
{
	View_t super;
	View_t super_f;

	int mapIndex;
    int qeditIndex;
    int qeditTop;
    bool upLong;
    bool downLong;
    int lineNo;
    int longCount;
    int queue[QUEUE_MAX_LEN][2];
	
	fp_onCreate onCreate;
	fp_onShow onShow;
	fp_onDraw onDraw;
	fp_onTouch onTouchOff;
	fp_procEvent procEvent;
	fp_sendEvent sendEvent;
} VQEdit_t;

void vQEdit_initWith(VQEdit_t *_self, int vid0, 
	int x0, int y0, int w0, int h0, Msg_t *msg0);

#ifdef __cplusplus
}
#endif
#endif	//_VQEDIT_H