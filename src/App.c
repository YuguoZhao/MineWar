#include "Utils.h"
#include "App.h"

static void createViewStack(void);
static void freeViewStack(void);
static void createViews(void);
static void freeViews(void);

static bool calibrationEnable;
static int deviceType;

static VOpening_t *viewOpen;
static VMap_t *viewMap;
static VGame_t *viewGame;
static VCal_t *viewCal;
static VMEdit_t *viewMEdit;
static VQEdit_t *viewQEdit;
static VHelp_t *viewHelp;
static VHonor_t *viewHonor;
static VStat_t *viewStat;

static ViewStack_t *viewStack;
static Msg_t *widgetMsg;
static Msg_t *commMsg;
static View_t *topView;

void App_startup(void)
{
	char filePath[1024];
	
    calibrationEnable = true;

	Utils_getDocPath("Options.dat", filePath);
    opt_load(filePath);
	map_load_maps();
	enemy_load_queues();
	record_load();
	C_init(&C);
	GL_init(&GL);
	View_init(&View);
	
    deviceType = DEV_2X_IPHONE5;
    L_setDensity(LAYOUT_IPHONE5, 1);
    game_set_grid_size(71);
    bullet_set_move_step(7.0);
    GL.setFontSize(20);
    View.setMoveThreshold(35);

	R_load(deviceType);
	createViewStack();
	createViews();
}

void App_exit(void)
{
	R_free();
	freeViews();
	freeViewStack();
}

void App_pause(void)
{
    commMsg->event = EV_PAUSE;
    topView->sendEvent(topView, commMsg);
    topView = viewStack->transfer(viewStack);
}

void App_resume(void)
{
    commMsg->event = EV_RESUME;
    topView->sendEvent(topView, commMsg);
    topView = viewStack->transfer(viewStack);
}

bool App_getRefreshFlag(void)
{
    return topView->getRefreshFlag(topView);
}

void App_enableCal(void)
{
    calibrationEnable = true;
}

void App_disableCal(void)
{
    calibrationEnable = false;
}

bool App_isCalEnable(void)
{
    return calibrationEnable;
}

static void createViews(void)
{
    int SCR_W0 = 1136;
    int SCR_H0 = 640;

	widgetMsg = (Msg_t *)malloc(sizeof(Msg_t));
    
    viewOpen = (VOpening_t *)malloc(sizeof(VOpening_t));
	VOpening_initWith(viewOpen, VID_OPENING, 0, 0, SCR_W0, SCR_H0, widgetMsg);
    viewMap = (VMap_t *)malloc(sizeof(VMap_t));
	VMap_initWith(viewMap, VID_MAP, 0, 0, SCR_W0, SCR_H0, widgetMsg);
    viewGame = (VGame_t *)malloc(sizeof(VGame_t));
	VGame_initWith(viewGame, VID_GAME, 0, 0, SCR_W0, SCR_H0, widgetMsg);
    viewMEdit = (VMEdit_t *)malloc(sizeof(VMEdit_t));
	VMEdit_initWith(viewMEdit, VID_MEDIT, 0, 0, SCR_W0, SCR_H0, widgetMsg);
    viewCal = (VCal_t *)malloc(sizeof(VCal_t));
	VCal_initWith(viewCal, VID_CAL, 0, 0, SCR_W0, SCR_H0, widgetMsg);
    viewQEdit = (VQEdit_t *)malloc(sizeof(VQEdit_t));
	vQEdit_initWith(viewQEdit, VID_QEDIT, 0, 0, SCR_W0, SCR_H0, widgetMsg);
    viewHelp = (VHelp_t *)malloc(sizeof(VHelp_t));
	VHelp_initWith(viewHelp, VID_HELP, 0, 0, SCR_W0, SCR_H0, widgetMsg);
    viewHonor = (VHonor_t *)malloc(sizeof(VHonor_t));
	VHonor_initWith(viewHonor, VID_HONOR, 0, 0, SCR_W0, SCR_H0, widgetMsg);
    viewStat = (VStat_t *)malloc(sizeof(VStat_t));
	VStat_initWith(viewStat, VID_STAT, 0, 0, SCR_W0, SCR_H0, widgetMsg);

	viewStack->regView(viewStack, VID_OPENING, (View_t *)viewOpen);
	viewStack->regView(viewStack, VID_MAP, (View_t *)viewMap);
	viewStack->regView(viewStack, VID_GAME, (View_t *)viewGame);
	viewStack->regView(viewStack, VID_MEDIT, (View_t *)viewMEdit);
	viewStack->regView(viewStack, VID_CAL, (View_t *)viewCal);
	viewStack->regView(viewStack, VID_QEDIT, (View_t *)viewQEdit);
	viewStack->regView(viewStack, VID_HELP, (View_t *)viewHelp);
	viewStack->regView(viewStack, VID_HONOR, (View_t *)viewHonor);
	viewStack->regView(viewStack, VID_STAT, (View_t *)viewStat);
	
    viewStack->push1stView(viewStack, VID_OPENING);
    topView = viewStack->getTopView(viewStack);
}

static void freeViews(void)
{
	free(widgetMsg);
    
    free(viewOpen);
    free(viewMap);
	free(viewGame);
	free(viewMEdit);
	free(viewCal);
	free(viewQEdit);
	free(viewHelp);
	free(viewHonor);
	free(viewStat);
}

static void createViewStack(void)
{
    commMsg = (Msg_t *)malloc(sizeof(Msg_t));
    viewStack = (ViewStack_t *)malloc(sizeof(ViewStack_t));
	ViewStack_init(viewStack);
}

static void freeViewStack(void)
{
	free(commMsg);
    free(viewStack);
}

void App_touchesBegan(int x, int y)
{
    topView->onTouchOn(topView, x, y);
    topView = viewStack->transfer(viewStack);
}

void App_touchesMoved(int x, int y)
{
    topView->onTouchMove(topView, x, y);
}

void App_touchesEnded(int x, int y)
{
	topView->onTouchOff(topView, x, y);
    topView = viewStack->transfer(viewStack);
}

void App_draw(void)
{
    topView->clearRefreshFlag(topView);
    topView->onDraw(topView);
}

void App_sendEvent(int event)
{
    commMsg->event = event;
    topView->sendEvent(topView, commMsg);
    topView = viewStack->transfer(viewStack);
}

void App_freeRes(void)
{
    R_free();
}

int App_getDevType(void)
{
    return deviceType;
}
