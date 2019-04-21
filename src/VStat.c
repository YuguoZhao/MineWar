#include "App.h"
#include "VStat.h"

#define  CTRL_RETURN    0

#define  LINE_PER_PAGE	7
#define  LINE_TOTAL		DATA_MAX

typedef enum{
	DATA_GAME = 0,
	DATA_WIN,
	DATA_SCORE,
	DATA_MONEY,
	DATA_COST,
	DATA_PLANT,
	DATA_MINE_NM,
	DATA_MINE_AE,
	DATA_MINE_AA,
	DATA_MINE_AT,
	DATA_MINE_RS,
	DATA_MINE_MG,

	DATA_MAX
} data_id_t;

static void getStatisticData(void);

static const char * const data_name_table[]={
    "total game",
    "win game",
    "total score",
    "total money",
    "total cost",
    "total plant",
    "normal mine",
    "anti-eng mine",
    "anti-armor mine",
    "anti-tank mine",
    "roadside mine",
    "mine gun"
};

static int statData[DATA_MAX];

static void onCreate(VStat_t *_self)
{
    WidgetInfo_t controls[] = {
        WGT_DATA(CTRL_RETURN, WGT_BTN, L_BACK_X, L_BACK_Y, L_GRID_W, L_GRID_H, 0, 0),
    };
    
    _self->super_f.onCreate(&_self->super);
	L_setWidgetData(controls, ARRAY_SIZE(controls));
    _self->super_f.regWidgets(&_self->super, controls, ARRAY_SIZE(controls));
    _self->top = 0;
    _self->line = 0;
	getStatisticData();
}

static void onDraw(VStat_t *_self)
{
	int i;
    int Y0 = (int)L_y(L_LIST_Y);
    int textOffsetY = (int)L_n(L_TEXT_Y);
    int listX = (int)L_x(L_LIST_X);
	char value[32];
	int page_total = LINE_TOTAL/LINE_PER_PAGE;

	if(LINE_TOTAL%LINE_PER_PAGE != 0){
		page_total++;
	}

	GL.drawRectFill(0, 0, L_n(L_SCR_W), L_n(L_SCR_H), C.BGR());
    GL.drawImage(L_x(L_BACK_X), L_y(L_BACK_Y), R_BTN_BACK);
  
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
        
        GL.drawText(listX+L_n(L_GRID_W)*2, Y0+i*L_n(L_GRID_H)+textOffsetY, data_name_table[i+_self->top]);      
        
        GL.drawRectFill(listX, Y0+L_n(L_GRID_H)*i+L_n(L_GRID_H)-2,
        	listX+L_n(L_GRID_W)*12, Y0+L_n(L_GRID_H)*i+L_n(L_GRID_H)+2,
        	C.RGB(0, 128, 0));
        
       	sprintf(value, "%d", statData[i+_self->top]);
        
        GL.drawTextR(listX+L_n(L_GRID_W)*19/2, Y0+i*L_n(L_GRID_H)+textOffsetY, value);
    }
    
    GL.drawRectFill(listX+L_n(L_GRID_W)*25/2-4, Y0,
    	listX+L_n(L_GRID_W)*25/2, Y0+L_n(L_GRID_H)*LINE_PER_PAGE-1,
    	C.RGB(0, 255, 0));
    
    GL.drawRectFill(listX+L_n(L_GRID_W)*25/2-4, 
		Y0+(_self->top*L_n(L_GRID_H)*LINE_PER_PAGE/LINE_TOTAL),
		listX+L_n(L_GRID_W)*25/2, 
		Y0+(_self->top*L_n(L_GRID_H)*LINE_PER_PAGE/LINE_TOTAL)+L_n(L_GRID_H)*LINE_PER_PAGE*LINE_PER_PAGE/LINE_TOTAL,
		C.RGB(255, 0, 0));
    
    GL.drawTextC(L_n(L_SCR_W)/2, L_n(L_TEXT_Y), "Statistics");
}

static void procEvent(VStat_t *_self)
{
    if((_self->super.super.mMsg->event == EV_SLIDE_U)
       &&(_self->super.super.mMsg->mid == -1)){
        if(_self->top+LINE_PER_PAGE < (LINE_TOTAL-LINE_PER_PAGE)){
            _self->top += LINE_PER_PAGE;
        }
        else{
            _self->top = LINE_TOTAL-LINE_PER_PAGE;
        }
        
        _self->super.mRefreshFlag = true;
    }
    else if((_self->super.super.mMsg->event == EV_SLIDE_D)
       &&(_self->super.super.mMsg->mid == -1)){
        if(_self->top > LINE_PER_PAGE){
            _self->top -= LINE_PER_PAGE;
        }
        else{
            _self->top = 0;
        }
        
        _self->super.mRefreshFlag = true;
    }
    else if((_self->super.super.mMsg->event == EV_KEY_UP)
       &&(_self->super.super.mMsg->mid == CTRL_RETURN)){
        _self->super.setTransfer(&_self->super, 
			-1, TRANS_RETURN, 0, 0, 0, 0);
    }
}

static bool sendEvent(VStat_t *_self, Msg_t *msg0)
{
    if(msg0->event == EV_RESUME){
        _self->super.mRefreshFlag = true;
    }
    
    return true;
}

static void getStatisticData(void)
{
	total_record_t record;
	
	record_get_total_record(&record);
	statData[DATA_GAME] = record.game;
	statData[DATA_WIN] = record.win;
	statData[DATA_SCORE] = record.score;
	statData[DATA_MONEY] = record.money;
	statData[DATA_COST] = record.cost;
	statData[DATA_PLANT] = record.plant;
	statData[DATA_MINE_NM] = record.mine_nm;
	statData[DATA_MINE_AE] = record.mine_ae;
	statData[DATA_MINE_AA] = record.mine_aa;
	statData[DATA_MINE_AT] = record.mine_at;
	statData[DATA_MINE_RS] = record.mine_rs;
	statData[DATA_MINE_MG] = record.mine_mg;
}

void VStat_initWith(VStat_t *_self, int vid0, 
	int x0, int y0, int w0, int h0, Msg_t *msg0)
{
    View_initWith(&_self->super, vid0, x0, y0, w0, h0, msg0);
	View_init(&_self->super_f);
	
    _self->top = 0;
    _self->line = 0;

	_self->super.setMoveDirection(&_self->super, SLIDE_DET_UD);

	_self->super.onCreate = onCreate;
	_self->super.onDraw = onDraw;
	_self->super.procEvent = procEvent;
	_self->super.sendEvent = sendEvent;

	_self->onCreate = onCreate;
	_self->onDraw = onDraw;
	_self->procEvent = procEvent;
	_self->sendEvent = sendEvent;
}
