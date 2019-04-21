#define _UNIT_TEST
#define _CASE_TOTAL	32

#include "type.h"
#include "View.h"
#include "ViewStack.h"

#define VID_1			0
#define VID_2			1

#define EV_TEST_CALL	0
#define EV_TEST_RETURN	1
#define EV_TEST_CHANGE	2

typedef struct _V1_t
{
	View_t super;
	View_t super_f;
	
	fp_onCreate onCreate;
	fp_onEnter onEnter;
	fp_onShow onShow;
	fp_onHide onHide;
	fp_onExit onExit;
	fp_onDraw onDraw;
	fp_procEvent procEvent;
	fp_sendEvent sendEvent;
} V1_t;

static int onCreateFlag1 = 0;
static int onEnterFlag1 = 0;
static int onShowFlag1 = 0;
static int onHideFlag1 = 0;
static int onExitFlag1 = 0;
static int para1_p1 = 0;
static int para1_p2 = 0;
static int para1_p3 = 0;
static int para1_p4 = 0;

static void onCreate1(V1_t * _self)
{
	_self->super_f.onCreate(&_self->super);
	onCreateFlag1 = 1;
	para1_p1 = _self->super.mInputPara.p1;
	para1_p2 = _self->super.mInputPara.p2;
	para1_p3 = _self->super.mInputPara.p3;
	para1_p4 = _self->super.mInputPara.p4;
}

static void onEnter1(V1_t * _self)
{
	_self->super_f.onEnter(&_self->super);
	onEnterFlag1 = 1;
	para1_p1 = _self->super.mInputPara.p1;
	para1_p2 = _self->super.mInputPara.p2;
	para1_p3 = _self->super.mInputPara.p3;
	para1_p4 = _self->super.mInputPara.p4;
}

static void onShow1(V1_t * _self)
{
	_self->super_f.onShow(&_self->super);
	onShowFlag1 = 1;
	para1_p1 = _self->super.mInputPara.p1;
	para1_p2 = _self->super.mInputPara.p2;
	para1_p3 = _self->super.mInputPara.p3;
	para1_p4 = _self->super.mInputPara.p4;
}

static void onHide1(V1_t * _self)
{
	_self->super_f.onHide(&_self->super);
	onHideFlag1 = 1;
	para1_p1 = _self->super.mInputPara.p1;
	para1_p2 = _self->super.mInputPara.p2;
	para1_p3 = _self->super.mInputPara.p3;
	para1_p4 = _self->super.mInputPara.p4;
}

static void onExit1(V1_t * _self)
{
	_self->super_f.onExit(&_self->super);
	onExitFlag1 = 1;
	para1_p1 = _self->super.mInputPara.p1;
	para1_p2 = _self->super.mInputPara.p2;
	para1_p3 = _self->super.mInputPara.p3;
	para1_p4 = _self->super.mInputPara.p4;
}

static void onDraw1(V1_t * _self)
{
}

static void procEvent1(V1_t *_self)
{
}

static bool sendEvent1(V1_t *_self, Msg_t *msg0)
{
    if(msg0->event == EV_TEST_CALL){
		_T_OPER("_self->super.setTransfer(&_self->super, VID_2, TRANS_CALL, 1, 2, 3, 4)");
		_self->super.setTransfer(&_self->super, VID_2, 
            	TRANS_CALL, 1, 2, 3, 4);
        _self->super.mRefreshFlag = true;
    }
	else if(msg0->event == EV_TEST_CHANGE){
		_T_OPER("_self->super.setTransfer(&_self->super, VID_2, TRANS_CHANGE, 1, 2, 3, 4)");
		_self->super.setTransfer(&_self->super, VID_2, 
            	TRANS_CHANGE, 1, 2, 3, 4);
        _self->super.mRefreshFlag = true;
    }
    
    return true;
}

void V1_initWith(V1_t *_self, int vid0, 
	int x0, int y0, int w0, int h0, Msg_t *msg0)
{
	View_initWith(&_self->super, vid0, x0, y0, w0, h0, msg0);
	View_init(&_self->super_f);
	
	_self->super.onCreate = onCreate1;
	_self->super.onEnter = onEnter1;
	_self->super.onHide = onHide1;
	_self->super.onShow = onShow1;
	_self->super.onExit = onExit1;
	_self->super.onDraw = onDraw1;
	_self->super.procEvent = procEvent1;
	_self->super.sendEvent = sendEvent1;
	
	_self->onCreate = onCreate1;
	_self->onEnter = onEnter1;
	_self->onHide = onHide1;
	_self->onShow = onShow1;
	_self->onExit = onExit1;
	_self->onDraw = onDraw1;
	_self->procEvent = procEvent1;
	_self->sendEvent = sendEvent1;
}

typedef struct _V2_t
{
	View_t super;
	View_t super_f;
	
	fp_onCreate onCreate;
	fp_onEnter onEnter;
	fp_onShow onShow;
	fp_onHide onHide;
	fp_onExit onExit;
	fp_onDraw onDraw;
	fp_procEvent procEvent;
	fp_sendEvent sendEvent;
} V2_t;

static int onCreateFlag2 = 0;
static int onEnterFlag2 = 0;
static int onShowFlag2 = 0;
static int onHideFlag2 = 0;
static int onExitFlag2 = 0;
static int para2_p1 = 0;
static int para2_p2 = 0;
static int para2_p3 = 0;
static int para2_p4 = 0;

static void onCreate2(V1_t * _self)
{
	_self->super_f.onCreate(&_self->super);
	onCreateFlag2 = 1;
	para2_p1 = _self->super.mInputPara.p1;
	para2_p2 = _self->super.mInputPara.p2;
	para2_p3 = _self->super.mInputPara.p3;
	para2_p4 = _self->super.mInputPara.p4;
}

static void onEnter2(V1_t * _self)
{
	_self->super_f.onEnter(&_self->super);
	onEnterFlag2 = 1;
	para2_p1 = _self->super.mInputPara.p1;
	para2_p2 = _self->super.mInputPara.p2;
	para2_p3 = _self->super.mInputPara.p3;
	para2_p4 = _self->super.mInputPara.p4;
}

static void onShow2(V1_t * _self)
{
	_self->super_f.onShow(&_self->super);
	onShowFlag2 = 1;
	para2_p1 = _self->super.mInputPara.p1;
	para2_p2 = _self->super.mInputPara.p2;
	para2_p3 = _self->super.mInputPara.p3;
	para2_p4 = _self->super.mInputPara.p4;
}

static void onHide2(V1_t * _self)
{
	_self->super_f.onHide(&_self->super);
	onHideFlag2 = 1;
	para2_p1 = _self->super.mInputPara.p1;
	para2_p2 = _self->super.mInputPara.p2;
	para2_p3 = _self->super.mInputPara.p3;
	para2_p4 = _self->super.mInputPara.p4;
}

static void onExit2(V1_t * _self)
{
	_self->super_f.onExit(&_self->super);
	onExitFlag2 = 1;
	para2_p1 = _self->super.mInputPara.p1;
	para2_p2 = _self->super.mInputPara.p2;
	para2_p3 = _self->super.mInputPara.p3;
	para2_p4 = _self->super.mInputPara.p4;
}

static void onDraw2(V1_t * _self)
{
}

static void procEvent2(V1_t *_self)
{
}

static bool sendEvent2(V1_t *_self, Msg_t *msg0)
{
    if(msg0->event == EV_TEST_RETURN){
		_T_OPER("_self->super.setTransfer(&_self->super, -1, TRANS_RETURN, 1, 2, 3, 4)");
		_self->super.setTransfer(&_self->super, -1, 
            	TRANS_RETURN, 5, 6, 7, 8);
        _self->super.mRefreshFlag = true;
    }
    
    return true;
}

void V2_initWith(V2_t *_self, int vid0, 
	int x0, int y0, int w0, int h0, Msg_t *msg0)
{
	View_initWith(&_self->super, vid0, x0, y0, w0, h0, msg0);
	View_init(&_self->super_f);
	
	_self->super.onCreate = onCreate2;
	_self->super.onEnter = onEnter2;
	_self->super.onHide = onHide2;
	_self->super.onShow = onShow2;
	_self->super.onExit = onExit2;
	_self->super.onDraw = onDraw2;
	_self->super.procEvent = procEvent2;
	_self->super.sendEvent = sendEvent2;
	
	_self->onCreate = onCreate2;
	_self->onEnter = onEnter2;
	_self->onHide = onHide2;
	_self->onShow = onShow2;
	_self->onExit = onExit2;
	_self->onDraw = onDraw2;
	_self->procEvent = procEvent2;
	_self->sendEvent = sendEvent2;
}

static V1_t *view1;
static V2_t *view2;

static ViewStack_t *vStack;
static Msg_t *wdgMsg;
static Msg_t *msg;
static View_t *topV;

static void v1_flag_clear(void)
{
	onCreateFlag1 = 0;
	onEnterFlag1 = 0;
	onShowFlag1 = 0;
	onHideFlag1 = 0;
	onExitFlag1 = 0;

	para1_p1 = 0;
	para1_p2 = 0;
	para1_p3 = 0;
	para1_p4 = 0;
}

static void v2_flag_clear(void)
{
	onCreateFlag2 = 0;
	onEnterFlag2 = 0;
	onShowFlag2 = 0;
	onHideFlag2 = 0;
	onExitFlag2 = 0;

	para2_p1 = 0;
	para2_p2 = 0;
	para2_p3 = 0;
	para2_p4 = 0;
}

static void test_vstack_init(void)
{
	msg = (Msg_t *)malloc(sizeof(Msg_t));
    vStack = (ViewStack_t *)malloc(sizeof(ViewStack_t));
	ViewStack_init(vStack);

	wdgMsg = (Msg_t *)malloc(sizeof(Msg_t));
    
    view1 = (V1_t *)malloc(sizeof(V1_t));
	V1_initWith(view1, VID_1, 0, 0, 1136, 640, wdgMsg);

	view2 = (V2_t *)malloc(sizeof(V2_t));
	V2_initWith(view2, VID_2, 0, 0, 1136, 640, wdgMsg);
}

static void case_01_001(void)
{
	_T_CASE("VSTACK-01-001");
	_T_PURPOSE("validate API regView.");
	_T_PRECOND("view stack and views have be created.");

	_T_STEP(1);
	_T_PARAM("view1=%p", view1);
	_T_OPER("vStack->regView(vStack, VID_1, (View_t *)view1)");
	vStack->regView(vStack, VID_1, (View_t *)view1);
	_T_ASSERT(vStack->mIndex[VID_1] == (View_t *)view1);

	_T_STEP(2);
	_T_PARAM("view2=%p", view2);
	_T_OPER("vStack->regView(vStack, VID_2, (View_t *)view2)");
	vStack->regView(vStack, VID_2, (View_t *)view2);
	
	_T_ASSERT(vStack->mIndex[VID_2] == (View_t *)view2);
	
	_T_END_OK();
}

static void case_01_002(void)
{
	_T_CASE("VSTACK-01-002");
	_T_PURPOSE("validate API push1stView and getTopView.");
	_T_PRECOND("views have be registered.");

	_T_STEP(1);
	v1_flag_clear();
	_T_PARAM("view id=%d", VID_1);
	_T_OPER("vStack->push1stView(vStack, VID_1)");
	vStack->push1stView(vStack, VID_1);
    topV = vStack->getTopView(vStack);
	
	_T_ASSERT(topV == (View_t *)view1);
	_T_ASSERT(vStack->mSp == 0);
	_T_ASSERT(onCreateFlag1 == 1);
	_T_ASSERT(onEnterFlag1 == 1);
	_T_ASSERT(onShowFlag1 == 1);
	_T_ASSERT(onHideFlag1 == 0);
	_T_ASSERT(onExitFlag1 == 0);
	
	_T_END_OK();
}

static void case_01_003(void)
{
	_T_CASE("VSTACK-01-003");
	_T_PURPOSE("validate API callView.");
	_T_PRECOND("views have be registered.");

	_T_STEP(1);
	v1_flag_clear();
	v2_flag_clear();
	
	_T_OPER("topV = vStack->getTopView(vStack)");
    topV = vStack->getTopView(vStack);
	_T_OPER("msg->event = EV_TEST_CALL");
	msg->event = EV_TEST_CALL;
	_T_OPER("topV->sendEvent(topV, msg)");
    topV->sendEvent(topV, msg);
	_T_OPER("topV = vStack->transfer(vStack)");
    topV = vStack->transfer(vStack);
	
	_T_ASSERT(topV == (View_t *)view2);
	_T_ASSERT(vStack->mSp == 1);
	_T_ASSERT(onCreateFlag1 == 0);
	_T_ASSERT(onEnterFlag1 == 0);
	_T_ASSERT(onShowFlag1 == 0);
	_T_ASSERT(onHideFlag1 == 1);
	_T_ASSERT(onExitFlag1 == 0);

	_T_ASSERT(onCreateFlag2 == 1);
	_T_ASSERT(onEnterFlag2 == 1);
	_T_ASSERT(onShowFlag2 == 1);
	_T_ASSERT(onHideFlag2 == 0);
	_T_ASSERT(onExitFlag2 == 0);

	_T_ASSERT(para2_p1 == 1);
	_T_ASSERT(para2_p2 == 2);
	_T_ASSERT(para2_p3 == 3);
	_T_ASSERT(para2_p4 == 4);
	
	_T_END_OK();
}

static void case_01_004(void)
{
	_T_CASE("VSTACK-01-004");
	_T_PURPOSE("validate API returnView.");
	_T_PRECOND("views have be registered.");

	_T_STEP(1);
	v1_flag_clear();
	v2_flag_clear();
    _T_OPER("topV = vStack->getTopView(vStack)");
    topV = vStack->getTopView(vStack);
	_T_OPER("msg->event = EV_TEST_RETURN");
	msg->event = EV_TEST_RETURN;
	_T_OPER("topV->sendEvent(topV, msg)");
    topV->sendEvent(topV, msg);
	_T_OPER("topV = vStack->transfer(vStack)");
    topV = vStack->transfer(vStack);
	
	_T_ASSERT(topV == (View_t *)view1);
	_T_ASSERT(vStack->mSp == 0);
	_T_ASSERT(onCreateFlag1 == 0);
	_T_ASSERT(onEnterFlag1 == 0);
	_T_ASSERT(onShowFlag1 == 1);
	_T_ASSERT(onHideFlag1 == 0);
	_T_ASSERT(onExitFlag1 == 0);

	_T_ASSERT(onCreateFlag2 == 0);
	_T_ASSERT(onEnterFlag2 == 0);
	_T_ASSERT(onShowFlag2 == 0);
	_T_ASSERT(onHideFlag2 == 1);
	_T_ASSERT(onExitFlag2 == 1);

	_T_ASSERT(para1_p1 == 5);
	_T_ASSERT(para1_p2 == 6);
	_T_ASSERT(para1_p3 == 7);
	_T_ASSERT(para1_p4 == 8);
	
	_T_END_OK();
}

static void case_01_005(void)
{
	_T_CASE("VSTACK-01-005");
	_T_PURPOSE("validate API changeView.");
	_T_PRECOND("views have be registered.");

	_T_STEP(1);
	v1_flag_clear();
	v2_flag_clear();
    _T_OPER("topV = vStack->getTopView(vStack)");
    topV = vStack->getTopView(vStack);
	_T_OPER("msg->event = EV_TEST_CHANGE");
	msg->event = EV_TEST_CHANGE;
	_T_OPER("topV->sendEvent(topV, msg)");
    topV->sendEvent(topV, msg);
	_T_OPER("topV = vStack->transfer(vStack)");
    topV = vStack->transfer(vStack);
	
	_T_ASSERT(topV == (View_t *)view2);
	_T_ASSERT(vStack->mSp == 0);
	_T_ASSERT(onCreateFlag1 == 0);
	_T_ASSERT(onEnterFlag1 == 0);
	_T_ASSERT(onShowFlag1 == 0);
	_T_ASSERT(onHideFlag1 == 1);
	_T_ASSERT(onExitFlag1 == 1);

	_T_ASSERT(onCreateFlag2 == 1);
	_T_ASSERT(onEnterFlag2 == 1);
	_T_ASSERT(onShowFlag2 == 1);
	_T_ASSERT(onHideFlag2 == 0);
	_T_ASSERT(onExitFlag2 == 0);

	_T_ASSERT(para2_p1 == 1);
	_T_ASSERT(para2_p2 == 2);
	_T_ASSERT(para2_p3 == 3);
	_T_ASSERT(para2_p4 == 4);
	
	_T_END_OK();
}

void test_vstack(void)
{
	int i;
	
	test_vstack_init();
	_T_INIT();

	case_01_001();
	case_01_002();
	case_01_003();
	case_01_004();
	case_01_005();
	
	for(i = 0; i < _T_CASE_TOTAL; i++){
		if(_T_CASE_RESULT(i).result == 1){
			printf("%s OK\n", _T_CASE_RESULT(i).case_id);
		}
		else{
			printf("%s NG\n", _T_CASE_RESULT(i).case_id);
		}
	}
}

