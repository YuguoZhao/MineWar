#include "App.h"
#include "VHelp.h"

#define CTRL_BTN_EXIT	0
#define LINE_PER_PAGE	6

const char *mw_version = "Ver 1.0.1";
const char *mw_author = "Mine War Project";
const char *mw_release_time = "2016-9-29";

const char *mw_help_description[] = {
	"#MineWar:",
    "MineWar is a mini defence game.",
    
    "#Rule:",
    "Kill all enemies and don't let enemy destory",
    "your houses.",
    "You can not operate in enemy's gunshot",
    "except remote explosing a roadside mine.",
    "The enemy will become slowly if it is",
    "demaged.",
    "You can dig weapons to get 60% money ",
    "for reusing.",

	"#Plant:",
    "You can planting in land to get money.",
    "When land becomes yellow, you must touch",
    "the plant to watering it.",
    "You can harvest a meture plant by touch",
    "or harvest other plant by knife.",

	"#Enemy:",
	"The enemy will go along the road.",
	"The enemies have diffrent gunshot and",
	"power.",
	"Only engineering can clear landmines.",
    
    "#Landmine:",
    "You can dispose landmine in the road.",
    "Anti-Engineer mine can demage all enemies",
    "include engineer.",
    "Anti-Armor mine can ONLY be detonated ",
    "by armor or tank.",
    "Anti-Tank mine can ONLY be detonated ",
    "by tank.",
    
    "#Roadside mine:",
	"Roadside mine can ONLY disposed in ",
	"roadside land.",
	"Roadside mine can ONLY be exploded by ",
	"remote control.",
	"Roadside mines which are adjacent will ",
	"explose in same time, so you need not plug",
	"a remote control for every mine.",

	"#Minegun:",
    "Minegun can throw bomb to enemy.",

	"#Stars:",
	"Victory Star: win the game.",
	"Plant Star: win the game and leave 3 ",
	"metured plant.",
	"Home Star: don not let enemy dameage ",
	"the house.",
    
    "#The war is cruel, even as a winner",
    "you do NOT want to experience it again.",
    "#For more information, please visit",
    "minewar2016.tumblr.com."
};

static int top = 0;
static int line_total = 0;

static void onCreate(VHelp_t *_self)
{
    WidgetInfo_t controls[]={
        WGT_DATA(CTRL_BTN_EXIT, WGT_BTN, L_X0, L_Y0, L_GRID_W, L_GRID_H, 0, 0)
    };
	
	_self->super_f.onCreate(&_self->super);
	L_setWidgetData(controls, ARRAY_SIZE(controls));
	_self->super_f.regWidgets(&_self->super, controls, ARRAY_SIZE(controls));
	top = 0;
	line_total = ARRAY_SIZE(mw_help_description);
	_LOGD("vAbout", "onCreate, top=%d, total=%d\n", top, line_total);
}

static void onDraw(VHelp_t *_self)
{
	char tmpStr[256];
	int i;
	double listX = L_n(L_SCR_W)-L_n(L_GRID_W);
	double listY = L_n(L_GRID_H)*1.5;
	const char *p;
	
    GL.drawRectFill(0, 0, L_n(L_SCR_W), L_n(L_SCR_H), C.BGR());
    GL.drawImage(L_x(L_BACK_X), L_y(L_BACK_Y), R_BTN_BACK);
	GL.drawImage(L_n(L_ICON_A_X), L_n(L_ICON_A_Y), R_LOGO);

    GL.drawRectFill(L_n(L_GRID_W), L_n(L_GRID_H)*1.5, L_n(L_SCR_W)-L_n(L_GRID_W), L_n(L_SCR_H)-L_n(L_GRID_H)*1.5, C.RGB(0, 96, 0));

	for(i = 0; i < 6; i++){
		p = mw_help_description[top+i];
		
		if(*p == '#'){
			GL.drawImage(L_n(L_GRID_W)*1, L_n(L_GRID_H)*(1.5+i), R_BTN_HONOR);
			p++;
		}
		
		GL.drawText(L_n(L_GRID_W)*2, L_n(L_GRID_H)*(1.6+i), p);
	}

	GL.drawRectFill(listX-4, listY,
    	listX, listY+L_n(L_GRID_H)*LINE_PER_PAGE,
    	C.RGB(0, 255, 0));
    
    GL.drawRectFill(listX-4, 
		listY+(top*L_n(L_GRID_H)*LINE_PER_PAGE/line_total),
		listX, 
		listY+(top*L_n(L_GRID_H)*LINE_PER_PAGE/line_total)+L_n(L_GRID_H)*LINE_PER_PAGE*LINE_PER_PAGE/line_total,
		C.RGB(255, 0, 0));

	sprintf(tmpStr, "%s %s %s", mw_version, mw_release_time, mw_author);
	GL.drawTextC(L_n(L_SCR_W)/2, L_n(L_SCR_H)-L_n(L_GRID_H)*1.2, tmpStr);
}

static void procEvent(VHelp_t *_self)
{
    if((_self->super.super.mMsg->event == EV_KEY_UP)
       &&(_self->super.super.mMsg->mid == CTRL_BTN_EXIT)){
        _self->super.setTransfer(&_self->super, 
			-1, TRANS_RETURN, 0, 0, 0, 0);
    }
	else if((_self->super.super.mMsg->event == EV_SLIDE_U)
       &&(_self->super.super.mMsg->mid == -1)){
        if(top+LINE_PER_PAGE < (line_total-LINE_PER_PAGE)){
            top += LINE_PER_PAGE;
        }
        else{
            top = line_total-LINE_PER_PAGE;
        }
        _LOGD("vAbout", "page up, top=%d, total=%d\n", top, line_total);
        _self->super.mRefreshFlag = true;
    }
    else if((_self->super.super.mMsg->event == EV_SLIDE_D)
       &&(_self->super.super.mMsg->mid == -1)){
        if(top > LINE_PER_PAGE){
            top -= LINE_PER_PAGE;
        }
        else{
            top = 0;
        }
        _LOGD("vAbout", "page down, top=%d, total=%d\n", top, line_total);
        _self->super.mRefreshFlag = true;
    }
}

static bool sendEvent(VHelp_t *_self, Msg_t *msg0)
{
    if(msg0->event == EV_RESUME){
        _self->super.mRefreshFlag = true;
    }
    
    return true;
}

void VHelp_initWith(VHelp_t *_self, int vid0, 
	int x0, int y0, int w0, int h0, Msg_t *msg0)
{
    View_initWith(&_self->super, vid0, x0, y0, w0, h0, msg0);
	View_init(&_self->super_f);
	
	_self->super.onCreate = onCreate;
	_self->super.onDraw = onDraw;
	_self->super.procEvent = procEvent;
	_self->super.sendEvent = sendEvent;

	_self->super.setMoveDirection(&_self->super, SLIDE_DET_UD);

	_self->onCreate = onCreate;
	_self->onDraw = onDraw;
	_self->procEvent = procEvent;
	_self->sendEvent = sendEvent;
}

