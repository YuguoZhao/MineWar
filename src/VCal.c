#include "App.h"
#include "VCal.h"

#define  CTRL_ADJ_UP    0
#define  CTRL_ADJ_DOWN  1
#define  CTRL_RETURN    2
#define  CTRL_SAVE      3

#define  LINE_PER_PAGE	7
#define  CAL_TOTAL		OPT_ID_EMEMY_Q1_LEN

#define IS_EVENT(event0, mid0)	\
	(_self->super.super.mMsg->event == event0)	\
	&&(_self->super.super.mMsg->mid == mid0)

static void onCreate(VCal_t *_self)
{
    WidgetInfo_t controls[]=
    {
        WGT_DATA(CTRL_ADJ_UP	, WGT_MTX, L_CAL_ADJ_UP_X, L_LIST_Y, L_GRID_W ,L_CAL_ADJ_H, L_GRID_W, L_GRID_H),
        WGT_DATA(CTRL_ADJ_DOWN	, WGT_MTX, L_CAL_ADJ_DN_X, L_LIST_Y, L_GRID_W ,L_CAL_ADJ_H, L_GRID_W, L_GRID_H),
        WGT_DATA(CTRL_RETURN	, WGT_BTN, L_BACK_X, L_BACK_Y, L_GRID_W, L_GRID_H, 0, 0),
        WGT_DATA(CTRL_SAVE		, WGT_BTN, L_BTN_SAVE2_X, L_BTN_SAVE2_Y, L_GRID_W, L_GRID_H, 0, 0),
    };

	_self->super_f.onCreate(&_self->super);
	L_setWidgetData(controls, ARRAY_SIZE(controls));
    _self->super_f.regWidgets(&_self->super, controls, ARRAY_SIZE(controls));
    _self->top = 0;
    _self->line = 0;
}

static void onShow(VCal_t *_self)
{
    _self->super_f.onShow(&_self->super);
    _self->clear_count = 0;
}

static void onDraw(VCal_t *_self)
{
	int i;
    int Y0 = (int)L_y(L_LIST_Y);
    int textOffsetY = (int)L_n(L_TEXT_Y);
    int listX = (int)L_x(L_LIST_X);
	char value[32];
	int page_total = CAL_TOTAL/LINE_PER_PAGE;

	if(CAL_TOTAL%LINE_PER_PAGE != 0){
		page_total++;
	}

	GL.drawRectFill(0, 0, L_n(L_SCR_W), L_n(L_SCR_H), C.BGR());
    GL.drawImage(L_x(L_BACK_X), L_y(L_BACK_Y), R_BTN_BACK);
    GL.drawImage(L_x(L_BTN_SAVE2_X), L_y(L_BTN_SAVE2_Y), R_BTN_SAVE);
  
    for(i = 0; i < LINE_PER_PAGE; i++){
        if(i == _self->line){
            GL.drawRectFill(listX, Y0+L_n(L_GRID_H)*i,
            	listX+L_n(L_GRID_W)*12, Y0+L_n(L_GRID_H)*i+L_n(L_GRID_H),
            	C.RGB(128, 128, 0));
        }
        else{
            GL.drawRectFill(listX, Y0+L_n(L_GRID_H)*i,
            	listX+L_n(L_GRID_W)*12, Y0+L_n(L_GRID_H)*i+L_n(L_GRID_H),
            	C.RGB(0, 192, 0));
        }
        
        GL.drawText(listX+L_n(L_GRID_W)/3, Y0+i*L_n(L_GRID_H)+textOffsetY, opt_get_name(i+_self->top));      
        GL.drawImage(L_n(L_CAL_ADJ_DN_X), Y0+i*L_n(L_GRID_H), R_BTN_DOWN);
        GL.drawImage(L_n(L_CAL_ADJ_UP_X), Y0+i*L_n(L_GRID_H), R_BTN_UP);
        
        GL.drawRectFill(listX, Y0+L_n(L_GRID_H)*i+L_n(L_GRID_H)-2,
        	listX+L_n(L_GRID_W)*12, Y0+L_n(L_GRID_H)*i+L_n(L_GRID_H)+2,
        	C.RGB(0, 128, 0));
        
        if(i+_self->top <= OPT_ID_PLUG_TIMER_CYCLE){
            sprintf(value, "%d ms" , opt_get_value(i+_self->top));
        }
        else if(i+_self->top == OPT_ID_DISPOSE_OFFSET){
            sprintf(value, "%d ms" , opt_get_value(i+_self->top)*TIME_UNIT);
        }
		else if(i+_self->top == OPT_ID_GAME_SPEED){
            if(opt_get_value(OPT_ID_GAME_SPEED) == 1){
				sprintf(value, "%s", "X2");
            }
            else{
				sprintf(value, "%s", "X1");
            }
        }
        else if(i+_self->top == OPT_ID_QUEUE_RANDOM){
            if(opt_get_value(OPT_ID_QUEUE_RANDOM) == 1){
				sprintf(value, "%s", "On");
            }
            else{
				sprintf(value, "%s", "Off");
            }
        }
        else{
        	sprintf(value, "%d", opt_get_value(i+_self->top));
        }
        
        GL.drawTextC(listX+L_n(L_GRID_W)*19/2, Y0+i*L_n(L_GRID_H)+textOffsetY, value);
    }
    
    GL.drawRectFill(listX+L_n(L_GRID_W)*25/2-4, Y0,
    	listX+L_n(L_GRID_W)*25/2, Y0+L_n(L_GRID_H)*LINE_PER_PAGE-1,
    	C.RGB(0, 255, 0));
    
    GL.drawRectFill(listX+L_n(L_GRID_W)*25/2-4, 
		Y0+(_self->top*L_n(L_GRID_H)*LINE_PER_PAGE/CAL_TOTAL),
		listX+L_n(L_GRID_W)*25/2, 
		Y0+(_self->top*L_n(L_GRID_H)*LINE_PER_PAGE/CAL_TOTAL)+L_n(L_GRID_H)*LINE_PER_PAGE*LINE_PER_PAGE/CAL_TOTAL,
		C.RGB(255, 0, 0));
    
    GL.drawTextC(L_n(L_SCR_W)/2, L_n(L_TEXT_Y), "Calibration");
}

static void procEvent(VCal_t *_self)
{
    if(IS_EVENT(EV_SLIDE_U, -1)){
        if(_self->top+LINE_PER_PAGE < (CAL_TOTAL-LINE_PER_PAGE)){
            _self->top += LINE_PER_PAGE;
        }
        else{
            _self->top = CAL_TOTAL-LINE_PER_PAGE;
        }
        
        _self->super.mRefreshFlag = true;
    }
    else if(IS_EVENT(EV_SLIDE_D, -1)){
        if(_self->top > LINE_PER_PAGE){
            _self->top -= LINE_PER_PAGE;
        }
        else{
            _self->top = 0;
        }
        
        _self->super.mRefreshFlag = true;
    }
    else if(IS_EVENT(EV_KEY_UP, CTRL_RETURN)){
        _self->super.setTransfer(&_self->super, 
			-1, TRANS_RETURN, 0, 0, 0, 0);
    }
    else if(IS_EVENT(EV_KEY_UP, CTRL_SAVE)){
        char filePath[1024];
        Utils_getDocPath("Options.dat", filePath);
		opt_save(filePath);
        _self->super.setTransfer(&_self->super, 
			-1, TRANS_RETURN, 0, 0, 0, 0);
    }
 	else if(IS_EVENT(EV_MTX_DOWN, CTRL_ADJ_DOWN)){
        _self->line = _self->super.super.mMsg->p2;
        opt_adjust_down(_self->top+_self->line);
        _self->super.mRefreshFlag = true;
    }
	else if(IS_EVENT(EV_MTX_DOWN, CTRL_ADJ_UP)){
        _self->line = _self->super.super.mMsg->p2;
        opt_adjust_up(_self->top+_self->line);
        _self->super.mRefreshFlag = true;
    }
}

static bool sendEvent(VCal_t *_self, Msg_t *msg0)
{
    if(msg0->event == EV_RESUME){
        _self->super.mRefreshFlag = true;
    }
    
    return true;
}

void VCal_initWith(VCal_t *_self, int vid0, 
	int x0, int y0, int w0, int h0, Msg_t *msg0)
{
    View_initWith(&_self->super, vid0, x0, y0, w0, h0, msg0);
	View_init(&_self->super_f);
	
    _self->top = 0;
    _self->line = 0;
    _self->clear_count = false;

	_self->super.setMoveDirection(&_self->super, SLIDE_DET_UD);

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
