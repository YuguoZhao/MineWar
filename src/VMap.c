#include "App.h"
#include "VMap.h"

#define	TAG					"vMap"

#define CTRL_BTN_CAL        0
#define CTRL_BTN_DOWN       1
#define CTRL_BTN_UP         2
#define CTRL_BTN_ENTER      3
#define CTRL_BTN_Q_EDIT     4
#define CTRL_BTN_M_EDIT     5
#define CTRL_BTN_ABOUT      6
#define CTRL_BTN_HONOR      7
#define CTRL_BTN_STAT       8

#define IS_EVENT(event0, mid0)	\
	(_self->super.super.mMsg->event == event0)	\
	&&(_self->super.super.mMsg->mid == mid0)

static void onCreate(VMap_t *_self)
{
    WidgetInfo_t controls[]={
        WGT_DATA(CTRL_BTN_CAL	, WGT_BTN, L_BACK_X, L_BACK_Y, L_GRID_W, L_GRID_H, 0, 0),
        WGT_DATA(CTRL_BTN_DOWN	, WGT_BTN, L_SCR_X0, L_MAP_PAGE_Y, L_MAP_PAGE_W, L_MAP_PAGE_H, 0, 0),
        WGT_DATA(CTRL_BTN_UP	, WGT_BTN, L_MAP_PAGE_X2, L_MAP_PAGE_Y, L_MAP_PAGE_W , L_MAP_PAGE_H, 0, 0),
        WGT_DATA(CTRL_BTN_ENTER	, WGT_BTN, L_ENTER_X, L_ENTER_Y, L_ENTER_W, L_ENTER_H, 0, 0),
        WGT_DATA(CTRL_BTN_Q_EDIT, WGT_BTN, L_MQ_EDIT_X, L_SCR_Y0, L_MQ_EDIT_W, L_GRID_H, 0, 0),
        WGT_DATA(CTRL_BTN_M_EDIT, WGT_BTN, L_MQ_EDIT_X, L_MQ_EDIT_Y2, L_MQ_EDIT_W, L_GRID_H, 0, 0),
        WGT_DATA(CTRL_BTN_ABOUT	, WGT_BTN, L_BTN_SAVE2_X, L_BTN_SAVE2_Y, L_GRID_W, L_GRID_H, 0, 0),
        WGT_DATA(CTRL_BTN_HONOR	, WGT_BTN, L_SCR_X0, L_CAL_ITEM_Y, L_GRID_W, L_GRID_H, 0, 0),
        WGT_DATA(CTRL_BTN_STAT	, WGT_BTN, L_BTN_SAVE2_X, L_CAL_ITEM_Y, L_GRID_W, L_GRID_H, 0, 0),
    };
	
    _self->super_f.onCreate(&_self->super);
	L_setWidgetData(controls, ARRAY_SIZE(controls));
	_self->super_f.regWidgets(&_self->super, controls, ARRAY_SIZE(controls));
    _self->mapIndex = 0;
    _self->updateMapIndexFlag = false;
}

static void onShow(VMap_t *_self)
{
    _self->super_f.onShow(&_self->super);
    
    if(_self->updateMapIndexFlag){
        _self->mapIndex = game_get_map_index();
    }
	
    _self->updateMapIndexFlag = false;
}

static void onDraw(VMap_t *_self)
{
	int arrowLeft[][3]={
        {0,0,0},
        {0,1,0},
        {1,0,0},
        {0,1,0},
        {0,0,0},
    };
    
    int arrowRight[][3]={
        {0,0,0},
        {0,1,0},
        {0,0,1},
        {0,1,0},
        {0,0,0},
    };
    
    int index = _self->mapIndex;
    int i;
    int j;
    int map[MAP_H][MAP_W];
    int bmp;
    
    int offset_x = (int)((L_n(L_SCR_W)-L_n(L_GRID_W)*14/2)/2);
    int offset_y = (int)((L_n(L_SCR_H)-L_n(L_GRID_H)*9/2)/2);
    
    GL.drawRectFill(0, 0, L_n(L_SCR_W), L_n(L_SCR_H), C.BGR());

	GL.drawImage(L_n(L_ICON_A_X), L_n(L_ICON_A_Y), R_LOGO);

	GL.drawImage(L_x(L_X0), L_y(L_Y0), R_BTN_OPTIONS);
	GL.drawImage(L_n(L_SCR_W)-L_n(L_GRID_W), L_y(L_Y0), R_BTN_HELP);
	GL.drawImage(L_x(L_X0), L_n(L_SCR_H)-L_n(L_GRID_H), R_BTN_HONOR);
	GL.drawImage(L_n(L_SCR_W)-L_n(L_GRID_W), L_n(L_SCR_H)-L_n(L_GRID_H), R_BTN_MENU);

	{
		char name[64];
		game_get_name(index, name);
    	GL.drawTextC(L_n(L_SCR_W)/2, L_n(L_SCR_H)-1.7*L_n(L_GRID_H), name);
	}
	
    {
		int star_x = (int)(L_n(L_SCR_W)*3/4-L_n(L_GRID_W)/2);
    	int star_y = (int)(L_n(L_SCR_H)/4-L_n(L_GRID_H)*9/10);
        int victory_y = star_y;
        int plant_y = star_y+(int)(L_n(L_GRID_H)*3/4);
        int house_y = star_y+2*(int)(L_n(L_GRID_H)*3/4);
		record_t record;

		record_get(index, &record);
        
        if(record.star_victory != 0){
            GL.drawImage(star_x, victory_y, R_HONOR_STAR);
        }
        else{
            GL.drawImage(star_x, victory_y, R_BTN_HONOR);
        }
        
        if(record.star_plant != 0){
            GL.drawImage(star_x, plant_y, R_HONOR_STAR);
        }
        else{
            GL.drawImage(star_x, plant_y, R_BTN_HONOR);
        }
        
        if(record.star_house != 0){
            GL.drawImage(star_x, house_y, R_HONOR_STAR);
        }
        else{
            GL.drawImage(star_x, house_y, R_BTN_HONOR);
        }
    }
    
    map_get(index, map);
    
    GL.drawRectFill(offset_x-4, offset_y-4, 
		offset_x+L_n(L_GRID_W)*14/2+4, offset_y+L_n(L_GRID_H)*9/2+4,
		C.RGB(255, 255, 255));
    
    for(i = 0; i < MAP_H; i++){
        for(j = 0; j < MAP_W; j++){
            if((map[i][j] == FIELD_ROAD)
				||(map[i][j] == FIELD_ENTRANCE)
				||(map[i][j] == FIELD_END)){
                bmp = R_MAP_ROAD_S;
            }
            else if(map[i][j] == FIELD_FOREST){
                bmp = R_MAP_FOREST_S;
            }
            else if(map[i][j] == FIELD_WATER){
                bmp = R_MAP_WATER_S;
            }
            else if(map[i][j] == FIELD_HOUSE){
                bmp = R_MAP_HOUSE_S;
            }
            else{
                bmp = R_MAP_LAND_S;
            }
            
            GL.drawImage(offset_x+j*L_n(L_GRID_W)/2, offset_y+i*(L_n(L_GRID_H)/2), bmp);
        }
    }
    
    for(i = 0; i < 5; i++){
        for(j = 0; j < 3; j++){
            if(arrowLeft[i][j] == 1){
                GL.drawImage(L_n(L_GRID_W)/2+j*L_n(L_GRID_W)/2, L_n(L_SCR_H)/2-L_n(L_GRID_H)/2*2.5+i*(L_n(L_GRID_H)/2), R_MAP_LAND_S);
            }

			if(arrowRight[i][j] == 1){
                GL.drawImage(L_n(L_SCR_W)-L_n(L_GRID_W)/2*4+j*L_n(L_GRID_W)/2, L_n(L_SCR_H)/2-L_n(L_GRID_H)/2*2.5+i*(L_n(L_GRID_H)/2), R_MAP_LAND_S);
            }
        }
    }

	GL.drawImage(L_n(L_SCR_W)/2-L_n(L_ICON_W_L)/2, L_n(L_SCR_H)/2-L_n(L_ICON_W_L)/2, R_ICON_LARGE_SHADOW);
}

static void procEvent(VMap_t *_self)
{
    if(IS_EVENT(EV_SLIDE_L, -1)){
        _self->mapIndex++;
        _self->mapIndex %= MAP_TOTAL;
        _self->updateMapIndexFlag = false;
        _self->super.mRefreshFlag = true;
    }
    else if(IS_EVENT(EV_SLIDE_R, -1)){
        _self->mapIndex--;
        _self->mapIndex = (_self->mapIndex+MAP_TOTAL)%MAP_TOTAL;
        _self->updateMapIndexFlag = false;
        _self->super.mRefreshFlag = true;
    }
    else if(IS_EVENT(EV_KEY_UP, CTRL_BTN_CAL)){
        _self->super.setTransfer(&_self->super, VID_CAL,
			TRANS_CALL, 0, 0, 0, 0);
    }
	else if(IS_EVENT(EV_KEY_UP, CTRL_BTN_ABOUT)){
        _self->super.setTransfer(&_self->super, VID_HELP,
			TRANS_CALL, 0, 0, 0, 0);
    }
    else if(IS_EVENT(EV_KEY_UP, CTRL_BTN_UP)){
        _self->mapIndex++;
        _self->mapIndex %= MAP_TOTAL;
        _self->updateMapIndexFlag = false;
        _self->super.mRefreshFlag = true;
    }
    else if(IS_EVENT(EV_KEY_UP, CTRL_BTN_DOWN)){
        _self->mapIndex--;
        _self->mapIndex = (_self->mapIndex+MAP_TOTAL)%MAP_TOTAL;
        _self->updateMapIndexFlag = false;
        _self->super.mRefreshFlag = true;
    }
    else if(IS_EVENT(EV_KEY_UP, CTRL_BTN_ENTER)){
        _self->super.setTransfer(&_self->super, VID_GAME,
			TRANS_CALL, _self->mapIndex, 0, 0, 0);
        _self->updateMapIndexFlag = true;
    }
    else if(IS_EVENT(EV_KEY_UP, CTRL_BTN_M_EDIT)){
        if(App_isCalEnable()){
            _self->super.setTransfer(&_self->super, VID_MEDIT, 
            	TRANS_CALL, _self->mapIndex, 0, 0, 0);
        }
    }
    else if(IS_EVENT(EV_KEY_UP, CTRL_BTN_Q_EDIT)){
        if(App_isCalEnable()){
        	_self->super.setTransfer(&_self->super, VID_QEDIT, 
        		TRANS_CALL, _self->mapIndex, 0, 0, 0);
        }
    }
	else if(IS_EVENT(EV_KEY_UP, CTRL_BTN_HONOR)){
        _self->super.setTransfer(&_self->super, VID_HONOR, 
        	TRANS_CALL, 0, 0, 0, 0);
    }
	else if(IS_EVENT(EV_KEY_UP, CTRL_BTN_STAT)){
        _self->super.setTransfer(&_self->super, VID_STAT, 
        	TRANS_CALL, 0, 0, 0, 0);
    }
}

static bool sendEvent(VMap_t *_self, Msg_t *msg0)
{
    if(msg0->event == EV_RESUME){
        _self->super.mRefreshFlag = true;
    }
    
    return true;
}

void VMap_initWith(VMap_t *_self, int vid0, 
	int x0, int y0, int w0, int h0, Msg_t *msg0)
{
    View_initWith(&_self->super, vid0, x0, y0, w0, h0, msg0);
	View_init(&_self->super_f);
	
    _self->mapIndex = 0;
    _self->updateMapIndexFlag = false;

	_self->super.setMoveDirection(&_self->super, SLIDE_DET_LR);

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

