#ifndef _VGAME_H
#define _VGAME_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "war.h"
#include "View.h"

typedef struct _VGame_t
{
	View_t super;
	View_t super_f;

	int gameMode;
    int mapIndex;
    int mode;
    int tbarType;
    int tbarItem;
    bool backConfirm;
    bool backupFlag;
    int tick;
	
	fp_onCreate onCreate;
	fp_onEnter onEnter;
	fp_onExit onExit;
	fp_onDraw onDraw;
	fp_procEvent procEvent;
	fp_sendEvent sendEvent;
} VGame_t;

void VGame_initWith(VGame_t *_self, int vid0, 
	int x0, int y0, int w0, int h0, Msg_t *msg0);

#ifdef __cplusplus
}
#endif
#endif	//_VGAME_H

