#include "VMEdit.h"
#include "App.h"

#define CTRL_MTX        0
#define CTRL_RETURN     1
#define CTRL_SAVE       2
#define CTRL_EDIT       3

static void onCreate(VMEdit_t *_self)
{
    WidgetInfo_t controls[]={
        WGT_DATA(CTRL_MTX	, WGT_MTX, L_PLAY_MTX_X, L_PLAY_MTX_Y, L_PLAY_MTX_W,L_PLAY_MTX_H, L_GRID_W, L_GRID_H),
        WGT_DATA(CTRL_SAVE	, WGT_BTN, L_ME_SAVE_X, L_ME_SAVE_Y, L_GRID_W, L_GRID_H, 0, 0),
        WGT_DATA(CTRL_EDIT	, WGT_MTX, L_ME_TB_X, L_ME_TB_Y, L_ME_TB_W, L_ME_TB_H, L_GRID_W, L_GRID_H),
    };
    
    _self->super_f.onCreate(&_self->super);
	L_setWidgetData(controls, ARRAY_SIZE(controls));
	_self->super_f.regWidgets(&_self->super, controls, ARRAY_SIZE(controls));
}

static void onShow(VMEdit_t *_self)
{
    _self->super_f.onShow(&_self->super);
    
    _self->itemId = FIELD_LAND;
    _self->mapIndex = _self->super.mInputPara.p1;
	map_get(_self->mapIndex, _self->map);
}

static void onDraw(VMEdit_t *_self)
{
    int btnTable[]={
        R_MAP_ROAD,
        R_MAP_LAND,
        R_MAP_FOREST,
        R_HOUSE,
        R_MAP_WATER,
        R_ENTRANCE_R,
        R_HONOR_STAR
    };
    int bmp;
    int x0 = (int)(L_x(L_PLAY_MTX_X));
    double y0 = L_y(L_PLAY_MTX_Y);
	int i, j;

	GL.drawRectFill(0, 0, L_n(L_SCR_W), L_n(L_SCR_H), C.RGB(0, 0, 0));
	
    GL.drawRectFill(L_n(L_X0), L_y(L_PLAY_MTX_Y)+0.5, 
		L_n(L_GRID_W)*2-L_n(L_GRID_W)/8, L_n(L_GRID_H)*9, C.BGR());
    
    for(i = 0; i < 7; i++){
        GL.drawImage(L_x(L_TB_ICON_X), L_y(L_SCR_Y0)+i*L_n(L_GRID_H), btnTable[i]);
    }
    
    GL.drawImage(L_n(L_ME_SAVE_X), L_n(L_ME_SAVE_Y), R_BTN_SAVE);
    
    for(i = 0; i < MAP_H; i++){
        for(j = 0; j < MAP_W; j++){
            if(_self->map[i][j] == FIELD_ROAD){
                bmp = R_MAP_ROAD;
            }
            else if(_self->map[i][j] == FIELD_FOREST){
                bmp = R_MAP_FOREST;
            }
            else if(_self->map[i][j] == FIELD_WATER){
                bmp = R_MAP_WATER;
            }
            else if(_self->map[i][j] == FIELD_LAND){
                bmp = R_MAP_LAND;
            }
            else if(_self->map[i][j] == FIELD_HOUSE){
                bmp = R_HOUSE;
            }
            else if(_self->map[i][j] == FIELD_END){
                GL.drawImage(x0+j*L_n(L_GRID_W), y0+i*L_n(L_GRID_H), R_MAP_ROAD);
                bmp = R_HONOR_STAR;
            }
            else if(_self->map[i][j] == FIELD_TREE){
                bmp = R_PLANT_PLANTING_MATURE;
            }
            else{
                GL.drawImage(x0+j*L_n(L_GRID_W), y0+i*L_n(L_GRID_H), R_MAP_ROAD);
                bmp = R_ENTRANCE_R;
            }
            
            GL.drawImage(x0+j*L_n(L_GRID_W), y0+i*L_n(L_GRID_H), bmp);
        }
    }
    
    GL.drawText(x0+L_n(L_GRID_W)/2, y0+L_n(L_TEXT_Y), "Map Edit");
}

static void procEvent(VMEdit_t *_self)
{
    if((_self->super.super.mMsg->event == EV_MTX_UP)
       &&(_self->super.super.mMsg->mid == CTRL_MTX)){
        int x0 = _self->super.super.mMsg->p1;
        int y0 = _self->super.super.mMsg->p2;
        _self->map[y0][x0] = _self->itemId;
    }
    else if((_self->super.super.mMsg->event == EV_MTX_UP)
       &&(_self->super.super.mMsg->mid == CTRL_EDIT)){
        _self->itemId = _self->super.super.mMsg->p2;
    }
    else if((_self->super.super.mMsg->event == EV_KEY_UP)
       &&(_self->super.super.mMsg->mid == CTRL_RETURN)){
        _self->super.setTransfer(&_self->super, 
			-1, TRANS_RETURN, 0, 0, 0, 0);
    }
    else if((_self->super.super.mMsg->event == EV_KEY_UP)
       &&(_self->super.super.mMsg->mid == CTRL_SAVE)){
        //[Map saveMap:mapIndex :map];
         _self->super.setTransfer(&_self->super, 
			-1, TRANS_RETURN, 0, 0, 0, 0);
    }
    
    _self->super.mRefreshFlag = true;
}

static bool sendEvent(VMEdit_t *_self, Msg_t *msg0)
{
    if(msg0->event == EV_RESUME){
        _self->super.mRefreshFlag = true;
    }
    
    return true;
}

void VMEdit_initWith(VMEdit_t *_self, int vid0, 
	int x0, int y0, int w0, int h0, Msg_t *msg0)
{
    View_initWith(&_self->super, vid0, x0, y0, w0, h0, msg0);
	View_init(&_self->super_f);

	_self->itemId = 0;
    _self->mapIndex = 0;

	_self->super.onCreate = onCreate;
	_self->super.onDraw = onDraw;
	_self->super.onShow = onShow;
	_self->super.procEvent = procEvent;
	_self->super.sendEvent = sendEvent;

	_self->onCreate = onCreate;
	_self->onDraw = onDraw;
	_self->onShow = onShow;
	_self->procEvent = procEvent;
	_self->sendEvent = sendEvent;
}
