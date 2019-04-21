#include "App.h"
#include "VQEdit.h"

#define CTRL_ENEMY_ID   0
#define CTRL_TIME_UP    1
#define CTRL_TIME_DOWN  2
#define CTRL_RETURN     5
#define CTRL_ENEMY_Q    6
#define CTRL_SAVE       7
#define CTRL_L_DN       8
#define CTRL_L_UP       9

#define INTERVAL_STEP   10
#define LINE_PER_PAGE   7

static void onCreate(VQEdit_t *_self)
{
    WidgetInfo_t controls[]=
    {
        WGT_DATA(CTRL_ENEMY_ID	, WGT_MTX, L_CAL_EID_X, L_LIST_Y, L_GRID_W, L_CAL_ADJ_H, L_GRID_W, L_GRID_H),
        WGT_DATA(CTRL_TIME_UP	, WGT_MTX, L_CAL_ADJ_UP_X, L_LIST_Y, L_GRID_W, L_CAL_ADJ_H, L_GRID_W, L_GRID_H),
        WGT_DATA(CTRL_TIME_DOWN	, WGT_MTX, L_CAL_ADJ_DN_X, L_LIST_Y, L_GRID_W, L_CAL_ADJ_H, L_GRID_W, L_GRID_H),
        WGT_DATA(CTRL_RETURN	, WGT_BTN, L_BACK_X, L_BACK_Y, L_GRID_W ,L_GRID_H, 0, 0),
        WGT_DATA(CTRL_ENEMY_Q	, WGT_MTX, L_CAL_Q_X, L_LIST_Y, L_GRID_W ,L_CAL_ADJ_H, L_GRID_W, L_GRID_H),
        WGT_DATA(CTRL_SAVE		, WGT_BTN, L_BTN_SAVE2_X, L_BTN_SAVE2_Y, L_GRID_W ,L_GRID_H, 0, 0),
        WGT_DATA(CTRL_L_DN		, WGT_BTN, L_CAL_L_DN_X, L_CAL_ITEM_Y, L_GRID_W ,L_GRID_H, 0, 0),
        WGT_DATA(CTRL_L_UP		, WGT_BTN, L_CAL_L_UP_X, L_CAL_ITEM_Y, L_GRID_W ,L_GRID_H, 0, 0),
    };
	int i;
    
    _self->super_f.onCreate(&_self->super);
	L_setWidgetData(controls, ARRAY_SIZE(controls));
	_self->super_f.regWidgets(&_self->super, controls, ARRAY_SIZE(controls));

    _self->mapIndex = _self->super.mInputPara.p1;
    _self->qeditIndex = 0;
    _self->qeditTop = 0;
    
    for(i = 0; i < QUEUE_MAX_LEN; i++){
        _self->queue[i][0] = 0;
        _self->queue[i][1] = 10;
    }
    
	enemy_queue_get(_self->mapIndex, _self->queue);
}

static void onTouchOff(VQEdit_t *_self, int x0, int y0)
{
    _self->super_f.onTouchOff(&_self->super, x0, y0);
    
    _self->upLong = false;
    _self->downLong = false;
    _self->longCount = 0;
}

static void onDraw(VQEdit_t *_self)
{
    int index = _self->qeditIndex;
    int top = _self->qeditTop;
    
    int bmpEnemyTable[]={
        R_ENEMY_SB_0,
        R_ENEMY_GB_0,
        R_ENEMY_QC_0,
        R_ENEMY_ZJ_0,
        R_ENEMY_TK_0,
    };
    
    int id;
	int Y0 = (int)L_y(L_LIST_Y);
    int textOffsetY = (int)L_n(L_TEXT_Y);
    int listX = (int)L_x(L_LIST_X);
	int i;
	char value[64];
	int length;
    
    GL.drawRectFill(0, 0, L_n(L_SCR_W), L_n(L_SCR_H), C.BGR());
    GL.drawImage(L_x(L_BACK_X), L_y(L_BACK_Y), R_BTN_BACK);
    GL.drawImage(L_x(L_BTN_SAVE2_X), L_y(L_BTN_SAVE2_Y), R_BTN_SAVE);
    
    for(i = 0; i < LINE_PER_PAGE; i++){
        id = _self->queue[top+i][0];
        
        if(i == index){
            GL.drawRectFill(listX, Y0+L_n(L_GRID_H)*i,
            	listX+L_n(L_GRID_W)*12, Y0+L_n(L_GRID_H)*i+L_n(L_GRID_H), C.RGB(128, 128, 0));
        }
        else{
            GL.drawRectFill(listX, Y0+L_n(L_GRID_H)*i,
            	listX+L_n(L_GRID_W)*12, Y0+L_n(L_GRID_H)*i+L_n(L_GRID_H), C.RGB(0, 192, 0));
        }
        
        GL.drawImage(L_n(L_CAL_EID_X), Y0+L_n(L_GRID_H)*i, bmpEnemyTable[id]);
        GL.drawImage(L_n(L_CAL_Q_X), Y0+L_n(L_GRID_H)*i, R_ENTRANCE_R);
        GL.drawImage(L_n(L_CAL_ADJ_DN_X), Y0+L_n(L_GRID_H)*i, R_BTN_DOWN);
        GL.drawImage(L_n(L_CAL_ADJ_UP_X), Y0+L_n(L_GRID_H)*i, R_BTN_UP);
        
        GL.drawRectFill(listX, Y0+L_n(L_GRID_H)*i+L_n(L_GRID_H)-2,
        	listX+L_n(L_GRID_W)*12, Y0+L_n(L_GRID_H)*i+L_n(L_GRID_H)+2, C.RGB(0, 128, 0));
        //interval
        sprintf(value, "%d", _self->queue[top+i][1]/10*10);
		GL.drawTextC(listX+L_n(L_GRID_W)*19/2, Y0+L_n(L_GRID_H)*i+textOffsetY, value);
        //queue
		sprintf(value, "%d", _self->queue[top+i][1]%10);
        GL.drawTextC(L_n(L_CAL_Q_X)-L_n(L_GRID_W)/2, Y0+L_n(L_GRID_H)*i+textOffsetY, value);
        //line
		sprintf(value, "%d", (top+i+1));
        GL.drawText(listX+L_n(L_GRID_W)/2, Y0+L_n(L_GRID_H)*i+textOffsetY, value);
    }
    
    GL.drawRectFill(listX+L_n(L_GRID_W)*25/2-4, Y0,
    	listX+L_n(L_GRID_W)*25/2, Y0+L_n(L_GRID_H)*LINE_PER_PAGE-1,
    	C.RGB(0, 255, 0));
    
    GL.drawRectFill(listX+L_n(L_GRID_W)*25/2-4, 
		Y0+(top*L_n(L_GRID_H)*LINE_PER_PAGE/QUEUE_MAX_LEN),
		listX+L_n(L_GRID_W)*25/2, 
		Y0+(top*L_n(L_GRID_H)*LINE_PER_PAGE/QUEUE_MAX_LEN)+L_n(L_GRID_H)*LINE_PER_PAGE*LINE_PER_PAGE/QUEUE_MAX_LEN,
		C.RGB(255, 0, 0));
	
    GL.drawText(L_n(L_GRID_W), L_n(L_TEXT_Y), "Calibration");
    
    GL.drawImage(L_x(L_CAL_L_DN_X), L_y(L_CAL_ITEM_Y), R_BTN_DOWN);
    GL.drawImage(L_x(L_CAL_L_UP_X), L_y(L_CAL_ITEM_Y), R_BTN_UP);
   
    length = opt_get_value(OPT_ID_EMEMY_Q1_LEN+_self->mapIndex);
    sprintf(value, "%d", length);
    GL.drawTextC(L_x(L_CAL_L_DN_X)+L_n(L_GRID_W)*2, 
		L_y(L_CAL_ITEM_Y)+textOffsetY, value);
}

static void procEvent(VQEdit_t *_self)
{
    if((_self->super.super.mMsg->event == EV_SLIDE_U)
       &&(_self->super.super.mMsg->mid == -1)){
        if(_self->qeditTop+LINE_PER_PAGE < (50-LINE_PER_PAGE)){
            _self->qeditTop += LINE_PER_PAGE;
        }
        else{
            _self->qeditTop = 50-LINE_PER_PAGE;
        }
    }
    
    if((_self->super.super.mMsg->event == EV_SLIDE_D)
       &&(_self->super.super.mMsg->mid == -1)){
        if(_self->qeditTop > LINE_PER_PAGE){
            _self->qeditTop -= LINE_PER_PAGE;
        }
        else{
            _self->qeditTop = 0;
        }
    }
    
    if((_self->super.super.mMsg->event == EV_KEY_UP)
       &&(_self->super.super.mMsg->mid == CTRL_RETURN)){
        _self->super.setTransfer(&_self->super, 
			-1, TRANS_RETURN, 0, 0, 0, 0);
    }
    
    if((_self->super.super.mMsg->event == EV_KEY_UP)
       &&(_self->super.super.mMsg->mid == CTRL_SAVE)){
        //[EnemyQueue saveQueues:mapIndex :queue];
        //NSString *fileName = [Utils getDocPath:@"Options.dat"];
        //[Options save:fileName];
        _self->super.setTransfer(&_self->super, 
			-1, TRANS_RETURN, 0, 0, 0, 0);
    }
    
    if((_self->super.super.mMsg->event == EV_MTX_UP)
       &&(_self->super.super.mMsg->mid == CTRL_ENEMY_ID)){
        _self->lineNo = _self->super.super.mMsg->p2;
        
        _self->qeditIndex = _self->lineNo;
        
        _self->queue[_self->qeditTop+_self->lineNo][0]++;
        
        if(_self->queue[_self->qeditTop+_self->lineNo][0] > ENEMY_TK){
            _self->queue[_self->qeditTop+_self->lineNo][0] = ENEMY_SB;
        }
    }
    
    if((_self->super.super.mMsg->event == EV_MTX_UP)
       &&(_self->super.super.mMsg->mid == CTRL_ENEMY_Q)){
		int tmp;
        _self->lineNo = _self->super.super.mMsg->p2;
        
        _self->qeditIndex = _self->lineNo;
        
        tmp = _self->queue[_self->qeditTop+_self->lineNo][1]%10;
        
        _self->queue[_self->qeditTop+_self->lineNo][1] /= 10;
        _self->queue[_self->qeditTop+_self->lineNo][1] *= 10;
        _self->queue[_self->qeditTop+_self->lineNo][1] += ((tmp+1)%4);
    }
    
    if((_self->super.super.mMsg->event == EV_MTX_DOWN)
       &&(_self->super.super.mMsg->mid == CTRL_TIME_DOWN)){
        _self->lineNo = _self->super.super.mMsg->p2;
        _self->qeditIndex = _self->lineNo;
        
        if(_self->queue[_self->qeditTop+_self->lineNo][1]/10 > 1){
            _self->queue[_self->qeditTop+_self->lineNo][1] -= INTERVAL_STEP;
        }
        
        _self->downLong = true;
        _self->longCount = 0;
    }
    
    if((_self->super.super.mMsg->event == EV_MTX_DOWN)
       &&(_self->super.super.mMsg->mid == CTRL_TIME_UP)){
        _self->lineNo = _self->super.super.mMsg->p2;
        _self->qeditIndex = _self->lineNo;
        
        if(_self->queue[_self->qeditTop+_self->lineNo][1] < INTERVAL_STEP*1000){
            _self->queue[_self->qeditTop+_self->lineNo][1] += INTERVAL_STEP;
        }
        
        _self->upLong = true;
        _self->longCount = 0;
    }
    
    if((_self->super.super.mMsg->event == EV_KEY_UP)
       &&(_self->super.super.mMsg->mid == CTRL_L_DN)){
        opt_adjust_down(OPT_ID_EMEMY_Q1_LEN+_self->mapIndex);
    }
    
    if((_self->super.super.mMsg->event == EV_KEY_UP)
       &&(_self->super.super.mMsg->mid == CTRL_L_UP)){
        opt_adjust_up(OPT_ID_EMEMY_Q1_LEN+_self->mapIndex);
    }
    
    _self->super.mRefreshFlag = true;
}

static bool sendEvent(VQEdit_t *_self, Msg_t *msg0)
{
    if(msg0->event == EV_TIME_TICK){
        if(_self->upLong){
            _self->longCount++;
            
            if(_self->longCount < 10)
                return true;
            if(_self->longCount%8 != 0)
                return true;
            
            if(_self->queue[_self->qeditTop+_self->lineNo][1] < INTERVAL_STEP*1000){
                _self->queue[_self->qeditTop+_self->lineNo][1] += INTERVAL_STEP;
            }
            
            _self->super.mRefreshFlag = true;
        }
        else if(_self->downLong){
            _self->longCount++;
            
            if(_self->longCount < 10)
                return true;
            if(_self->longCount%8 != 0)
                return true;
            
            if(_self->queue[_self->qeditTop+_self->lineNo][1]/10 > 1){
                _self->queue[_self->qeditTop+_self->lineNo][1] -= INTERVAL_STEP;
            }
            
            _self->super.mRefreshFlag = true;
        }
    }
    else if(msg0->event == EV_RESUME){
        _self->super.mRefreshFlag = true;
    }
    
    return true;
}

void vQEdit_initWith(VQEdit_t *_self, int vid0, 
	int x0, int y0, int w0, int h0, Msg_t *msg0)
{
    View_initWith(&_self->super, vid0, x0, y0, w0, h0, msg0);
	View_init(&_self->super_f);
	
	_self->mapIndex = 0;
    _self->qeditIndex = 0;
    _self->qeditTop = 0;
    _self->upLong = 0;
    _self->downLong = 0;
    _self->lineNo = 0;
    _self->longCount = 0;
    memset(_self->queue, 0, sizeof(int)*QUEUE_MAX_LEN*2);

	_self->super.setMoveDirection(&_self->super, SLIDE_DET_UD);

	_self->super.onCreate = onCreate;
	_self->super.onDraw = onDraw;
	_self->super.procEvent = procEvent;
	_self->super.sendEvent = sendEvent;
	_self->super.onTouchOff = onTouchOff;

	_self->onCreate = onCreate;
	_self->onDraw = onDraw;
	_self->procEvent = procEvent;
	_self->sendEvent = sendEvent;
	_self->onTouchOff = onTouchOff;
}
