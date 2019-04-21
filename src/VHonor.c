#include "VHonor.h"
#include "App.h"

#define CTRL_BTN_EXIT   0
#define CTRL_MTX_STAR   1

#define STARS_PER_LINE  8

typedef struct {
	const char *name;
	const char **text;
	int lines;
}star_descript_t;

static void onCreate(VHonor_t *_self)
{
    WidgetInfo_t controls[]={
        WGT_DATA(CTRL_BTN_EXIT, WGT_BTN, L_BACK_X, L_BACK_Y, L_GRID_W, L_GRID_H, 0, 0),
        WGT_DATA(CTRL_MTX_STAR, WGT_MTX, L_HONOR_X, L_HONOR_Y, L_HONOR_W ,L_HONOR_H, L_GRID_W, L_GRID_H)
    };
    
    _self->super_f.onCreate(&_self->super);
	L_setWidgetData(controls, ARRAY_SIZE(controls));
	_self->super_f.regWidgets(&_self->super, controls, ARRAY_SIZE(controls));
    _self->starIndex = 0;
}

static const char * const star0[] = {
	"Win first game."
};

static const char * const star1[] = {
	"Get first three stars."
};

static const char * const star2[] = {
	"Win game 1~18."
};

static const char * const star3[] = {
	"Win all games."
};

static const char * const star4[] = {
	"Get three starts using less than",
	"7 anti-engineer mines in a game."
};

static const char * const star5[] = {
	"Get three starts remaining 20 mature",
	"plants in a Classic game."
};

static const char * const star6[] = {
	"Kill 5 enemies at least by one operation."
};

static const char * const star7[] = {
	"Kill 10 enemies at least by one operation."
};

static const char * const star8[] = {
	"Kill 15 enemies at least by one operation."
};

static const char * const star9[] = {
	"Get three stars using less than 800",
	"money in game 6."
};

static const char * const star10[] = {
	"Get all stars of all games."
};

static const char * const star11[] = {
	"Get 1,000,000 money by planting."
};

static const char * const star12[] = {
	"Use 800 mine guns."
};

static const char * const star13[] = {
	"Use 2000 roadside mines."
};

static const char * const star14[] = {
	"Get 1,000,000 total score."
};

static const char * const star15[] = {
	"Win 1000 games."
};

#define STAR_ITEM(name, detail)	\
	{name, (const char **)detail, ARRAY_SIZE(detail)}

static const star_descript_t star_detail[]=
{
	STAR_ITEM("First Star"				,star0),
	STAR_ITEM("First Three Stars"		,star1),
	STAR_ITEM("Half Pass Star"			,star2),
	STAR_ITEM("Full Pass Star"			,star3),
	STAR_ITEM("Sliver Planting Star"	,star4),
	STAR_ITEM("Gold Planting Star"		,star5),
	STAR_ITEM("Copper Power Star"		,star6),
	STAR_ITEM("Sliver Power Star"		,star7),
	STAR_ITEM("Gold Power Star"			,star8),
	STAR_ITEM("Efficient Star"			,star9),
	STAR_ITEM("Gold Star"				,star10),
	STAR_ITEM("Planting Star"			,star11),
	STAR_ITEM("Mine Gun Star"			,star12),
	STAR_ITEM("Roadside Mine Star"		,star13),
	STAR_ITEM("Total Score Star"		,star14),	
	STAR_ITEM("Thousand Battles Star"	,star15)
};

static void onDraw(VHonor_t *_self)
{
    int i;
    int j;
    int bmpId;
    char value[128];
	char starName[128];
    star_data_t stars[16];
    double textW;
	int lineTotal;

	game_get_stars(stars);
	
    GL.drawRectFill(0, 0, L_n(L_SCR_W), L_n(L_SCR_H), C.BGR());
    GL.drawTextC(L_n(L_SCR_W)/2, L_y(L_TEXT_Y), "Starts of Honor");
    GL.drawImage(L_x(L_BACK_X), L_y(L_BACK_Y), R_BTN_BACK);
    
    for(i = 0; i < 2; i++){
        for(j = 0; j < STARS_PER_LINE; j++){
            if(STARS_PER_LINE*i+j == _self->starIndex){
                if(stars[STARS_PER_LINE*i+j].gotten == 1){
                    bmpId = R_HONOR_STAR_B_S;
                }
                else{
                    bmpId = R_HONOR_STAR_E_S;
                }
            }
            else{
                if(stars[STARS_PER_LINE*i+j].gotten == 1){
                    bmpId = R_HONOR_STAR_B;
                }
                else{
                    bmpId = R_HONOR_STAR_E;
                }
            }
            
            GL.drawImage(L_n(L_HONOR_X)+L_n(L_GRID_H)*j,
				L_n(L_HONOR_Y)+L_n(L_GRID_H)*i, bmpId);
        }
    }
    
    if(stars[_self->starIndex].progress == -1){
		sprintf(value, "(-/%d)", stars[_self->starIndex].target);
    }
    else{
		sprintf(value, "(%d/%d)", 
			stars[_self->starIndex].progress, stars[_self->starIndex].target);
    }
    
    sprintf(starName, "%s%s", star_detail[_self->starIndex].name, value);
    textW = L_n(L_GRID_W)*11;
    GL.drawTextC(L_n(L_SCR_W)/2, L_n(L_HONOR_Y)-L_n(L_GRID_H), starName);
    
    lineTotal = star_detail[_self->starIndex].lines;
    
    for(i = 0; i < lineTotal; i++){
        GL.drawTextC(L_n(L_SCR_W)/2, L_n(L_GRID_H)/2+L_n(L_HONOR_Y)+3*L_n(L_GRID_H) +i*(L_n(L_GRID_H)*7/8), 
			star_detail[_self->starIndex].text[i]);
    }
}

static void procEvent(VHonor_t *_self)
{
    if((_self->super.super.mMsg->event == EV_KEY_UP)
       &&(_self->super.super.mMsg->mid == CTRL_BTN_EXIT)){
        _self->super.setTransfer(&_self->super, 
			-1, TRANS_RETURN, 0, 0, 0, 0);
    }
	else if((_self->super.super.mMsg->event == EV_MTX_UP)
       &&(_self->super.super.mMsg->mid == CTRL_MTX_STAR)){
        _self->starIndex = _self->super.super.mMsg->p1
			+_self->super.super.mMsg->p2*STARS_PER_LINE;
        _self->super.mRefreshFlag = true;
    }
}

static bool sendEvent(VHonor_t *_self, Msg_t *msg0)
{
    if(msg0->event == EV_RESUME){
        _self->super.mRefreshFlag = true;
    }
    
    return true;
}

void VHonor_initWith(VHonor_t *_self, int vid0, 
	int x0, int y0, int w0, int h0, Msg_t *msg0)
{
    View_initWith(&_self->super, vid0, x0, y0, w0, h0, msg0);
	View_init(&_self->super_f);
	
    _self->starIndex = 0;

	_self->super.onCreate = onCreate;
	_self->super.onDraw = onDraw;
	_self->super.procEvent = procEvent;
	_self->super.sendEvent = sendEvent;

	_self->onCreate = onCreate;
	_self->onDraw = onDraw;
	_self->procEvent = procEvent;
	_self->sendEvent = sendEvent;
}
