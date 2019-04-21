#include "App.h"
#include "VOpening.h"

#define CTRL_ID_CANCEL  0

static void onCreate(VOpening_t *_self)
{
    WidgetInfo_t controls[]={
        WGT_DATA(CTRL_ID_CANCEL, WGT_BTN, L_X0, L_Y0, L_SCR_W, L_SCR_H, 0, 0)
    };

	_self->super_f.onCreate(&_self->super);
	L_setWidgetData(controls, ARRAY_SIZE(controls));
	_self->super_f.regWidgets(&_self->super, controls, ARRAY_SIZE(controls));
	_self->mCounter = 0;
    _self->mTick = 0;
}

static void onDraw(VOpening_t *_self)
{
    int logo[4][16]={
        {0,0,2,0,1,0,0,0,2,0,1,0,0,0,2,0},
        {0,0,0,1,0,1,0,2,0,1,0,1,0,2,0,0},
        {0,0,1,0,2,0,2,0,1,0,2,0,2,0,0,0},
        {0,1,0,0,0,2,0,1,0,0,0,2,0,1,0,0}
    };
    int logo_m[4][16]={
        {0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0},
        {0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0},
        {0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0},
        {0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0}
    };
    int logo_w[4][16]={
        {0,0,2,0,0,0,0,0,2,0,0,0,0,0,2,0},
        {0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,0},
        {0,0,0,0,2,0,2,0,0,0,2,0,2,0,0,0},
        {0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0}
    };
    
    int i;
    int j;
    int x0 = (int)(L_n(L_SCR_W)/2-L_n(L_GRID_W)*4);
    int y0 = (int)((L_n(L_SCR_H)-L_n(L_GRID_H)*3.65)/2);
    int logoY0 = (int)(y0+L_n(L_GRID_H)*2.65);
    int gw = (int)(L_n(L_GRID_W)/2);
    int gh = (int)(L_n(L_GRID_H)/2);

	GL.drawRectFill(0, 0, L_n(L_SCR_W), L_n(L_SCR_H), C.BGR());
    
    if(_self->mCounter < 256){
        for(i = 0; i < 4; i++){
            for(j = 0; j < _self->mCounter/16; j++){
                if(logo_m[i][j] == 1){
                    GL.drawRectFill(x0+j*gw, y0+i*gh,
						x0+(j+1)*gw, y0+(i+1)*gh, 
                     	C.RGBA(0, 255, 0, _self->mCounter));
                }
            }
        }
        
        GL.drawImage2(L_n(L_SCR_W)/2-(L_n(L_LOGO_MINE_W)+L_n(L_LOGO_WAR_W))/2, 
			logoY0, R_LOGO_MINE, _self->mCounter);
    }
    
    if((_self->mCounter >= 256)
       &&(_self->mCounter < 512)){
        for(i = 0; i < 4; i++){
            for(j = 0; j < 16; j++){
                if(logo_m[i][j] == 1){
                    GL.drawRectFill(x0+j*gw, y0+i*gh, 
						x0+(j+1)*gw, y0+(i+1)*gh, 
                     	C.RGBA(0, 255, 0, 255));
                }
            }
        }
        
        for(i = 0; i < 4; i++){
            for(j = 0; j < _self->mCounter/16-16; j++){
                if(logo_w[i][j] == 2){
                    GL.drawRectFill(x0+j*gw, y0+i*gh, 
						x0+(j+1)*gw, y0+(i+1)*gh, 
                     	C.RGBA(255, 255, 0, (_self->mCounter-256)));
                }
            }
        }
        
        GL.drawImage2(L_n(L_SCR_W)/2-(L_n(L_LOGO_MINE_W)+L_n(L_LOGO_WAR_W))/2, logoY0, R_LOGO_MINE, 255);
        GL.drawImage2(L_n(L_SCR_W)/2-(L_n(L_LOGO_MINE_W)+L_n(L_LOGO_WAR_W))/2+L_n(L_LOGO_MINE_W), logoY0, R_LOGO_WAR, _self->mCounter-256);
    }
    
    if(_self->mCounter >= 512){
        for(i = 0; i < 4; i++){
            for(j = 0; j < 16; j++){
                if(logo[i][j] == 1){
                    GL.drawRectFill(x0+j*gw, y0+i*gh, x0+(j+1)*gw, y0+(i+1)*gh, C.RGBA(0, 255, 0, 255));
                }
                else if(logo[i][j] == 2){
                    GL.drawRectFill(x0+j*gw, y0+i*gh, x0+(j+1)*gw, y0+(i+1)*gh, C.RGBA(255, 255, 0, 255));
                }
            }
        }
        
        GL.drawImage2(L_n(L_SCR_W)/2-(L_n(L_LOGO_MINE_W)+L_n(L_LOGO_WAR_W))/2, logoY0, R_LOGO_MINE, 255);
        GL.drawImage2(L_n(L_SCR_W)/2-(L_n(L_LOGO_MINE_W)+L_n(L_LOGO_WAR_W))/2+L_n(L_LOGO_MINE_W), logoY0, R_LOGO_WAR, 255);
    }
    
    if(_self->mCounter < (256*3-1-16*8)){
        _self->mCounter += 16;
    }
    else{
        //_self->mCounter = 0;
    }
}

static void procEvent(VOpening_t *_self)
{
	if((_self->super.super.mMsg->event == EV_KEY_UP)
		&&(_self->super.super.mMsg->mid == CTRL_ID_CANCEL)){
		_self->super.setTransfer(&_self->super, VID_MAP,
			TRANS_CHANGE, 0, 0, 0, 0);
    }
}

static bool sendEvent(VOpening_t *_self, Msg_t *msg0)
{
   if(msg0->event == EV_TIME_TICK){
        _self->mTick++;;
        
        if(_self->mTick%5 == 0){
            _self->super.mRefreshFlag = true;
        }
        
        if(_self->mCounter >= (256*3-1-16*8)){
			_self->super.setTransfer(&_self->super, VID_MAP,
				TRANS_CHANGE, 0, 0, 0, 0);
        }
        
        return true;
    }
    else if(msg0->event == EV_RESUME){
        _self->super.mRefreshFlag = true;
    }
    
    return true;
}

void VOpening_initWith(VOpening_t *_self, int vid0, 
	int x0, int y0, int w0, int h0, Msg_t *msg0)
{
    View_initWith(&_self->super, vid0, x0, y0, w0, h0, msg0);
	View_init(&_self->super_f);
	
    _self->mCounter = 0;
    _self->mTick = 0;

	_self->super.onCreate = onCreate;
	_self->super.onDraw = onDraw;
	_self->super.procEvent = procEvent;
	_self->super.sendEvent = sendEvent;

	_self->onCreate = onCreate;
	_self->onDraw = onDraw;
	_self->procEvent = procEvent;
	_self->sendEvent = sendEvent;
}
