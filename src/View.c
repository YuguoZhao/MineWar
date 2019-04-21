#include "Button.h"
#include "TouchMtx.h"
#include "ViewStack.h"
#include "View.h"

static int mMoveThreshold = 35;
View_t View;

static void onCreate(View_t *_self)
{
	_LOGI("View", "onCreate, id=%d\n", _self->super.mId);
	_self->mWidgetCount = 0;
}

static void onEnter(View_t *_self)
{
	_LOGI("View", "onEnter, id=%d\n", _self->super.mId);
}

static void onExit(View_t *_self)
{
	int i;

	_LOGI("View", "onExit, id=%d\n", _self->super.mId);
	
	for(i = 0; i < _self->mWidgetCount; i++){
		free(_self->mWidgetArray[i]);
	}
	
	_self->mWidgetCount = 0;
}

static void onHide(View_t *_self)
{
	_LOGI("View", "onHide, id=%d\n", _self->super.mId);
	_self->super.hide(_self);
}

static void onShow(View_t *_self)
{
	_LOGI("View", "onShow, id=%d\n", _self->super.mId);
	_self->super.show(_self);
    _self->mRefreshFlag = true;
}

static void onTouchOn(View_t *_self, int x0, int y0)
{
	int i;
	_LOGI("View", "onTouchOn, id=%d, x=%d, y=%d\n", _self->super.mId, x0, y0);
    _self->super.onTouchOn(_self, x0, y0);
	
	if(_self->super.mState == TOUCH_ON){
		_self->mTX0 = x0;
		_self->mTY0 = y0;
	}

	for(i = 0; i < _self->mWidgetCount; i++){
		_self->mWidgetArray[i]->onTouchOn(_self->mWidgetArray[i], x0, y0);
	}
    
    if(_self->super.mMsg->event != NO_EVENT){
        _self->procEvent(_self);
        _self->super.clearEvent(_self);
    }
}

static void onTouchOff(View_t *_self, int x0, int y0)
{
	int i;
	_LOGI("View", "onTouchOff, id=%d, x=%d, y=%d\n", _self->super.mId, x0, y0);
	for(i = 0; i < _self->mWidgetCount; i++){
		_self->mWidgetArray[i]->onTouchOff(_self->mWidgetArray[i], x0, y0);
	}
	
	if(_self->super.mState == TOUCH_ON){
		int dx = x0-_self->mTX0;
		int dy = y0-_self->mTY0;
		int event = -1;
        
        if(_self->mMoveDirection&SLIDE_DET_LR){
            if(dx > mMoveThreshold){
				_LOGI("View", "EV_SLIDE_R, id=%d\n", _self->super.mId);
                event = EV_SLIDE_R;
            }
            else if(dx < -mMoveThreshold){
				_LOGI("View", "EV_SLIDE_L, id=%d\n", _self->super.mId);
                event = EV_SLIDE_L;
            }
        }

		if(event == -1){
            if(_self->mMoveDirection&SLIDE_DET_UD){
                if(dy > mMoveThreshold){
					_LOGI("View", "EV_SLIDE_D, id=%d\n", _self->super.mId);
                    event = EV_SLIDE_D;
                }
                else if(dy < -mMoveThreshold){
					_LOGI("View", "EV_SLIDE_U, id=%d\n", _self->super.mId);
                    event = EV_SLIDE_U;
                }
            }
		}

		if(event != -1){
			for(i = 0; i < _self->mWidgetCount; i++){
				_self->mWidgetArray[i]->onTouchClear(_self->mWidgetArray[i]);
			}
            _self->super.setEvent(_self, -1, event, 0, 0, 0, 0);
		}
	}

    _self->super.onTouchOff(_self, x0, y0);
    
    if(_self->super.mMsg->event != NO_EVENT){
        _self->procEvent(_self);
        _self->super.clearEvent(_self);
    }
}

static void onTouchMove(View_t *_self, int x0, int y0)
{
	int dx;
	int dy;
	int event = -1;
	int i;

    _self->super.onTouchMove(_self, x0, y0);

	dx = x0-_self->mTX0;
	dy = y0-_self->mTY0;
    
    if(_self->mMoveDirection&SLIDE_DET_LR){
        if(dx > mMoveThreshold){
            event = EV_SLIDE_R;
        }
        else if(dx < -mMoveThreshold){
            event = EV_SLIDE_L;
        }
    }

	if(event == -1){
        if(_self->mMoveDirection&SLIDE_DET_UD){
            if(dy > mMoveThreshold){
                event = EV_SLIDE_D;
            }
            else if(dy < -mMoveThreshold){
                event = EV_SLIDE_U;
            }
        }
	}

	if(event != -1){
        for(i = 0; i < _self->mWidgetCount; i++){
            _self->mWidgetArray[i]->onTouchClear(_self->mWidgetArray[i]);
        }
	}
}

static void onDraw(View_t *_self)
{
    _self->mRefreshFlag = true;
}

static void procEvent(View_t *_self)
{
}

static bool sendEvent(View_t *_self, Msg_t *msg)
{
	return false;
}

static void regWidgets(View_t *_self, WidgetInfo_t *array, int size)
{
	int i;
	_LOGI("View", "regWidgets, id=%d, total=%d\n", _self->super.mId, size);
	
	_self->mWidgetCount = size;
	_self->mWidgetArray = (Widget_t**)malloc(sizeof(Widget_t*)*size);
    
	for(i = 0; i < size; i++){
		if(array[i].wtype == WGT_BTN){
			Button_t *btn = (Button_t *)malloc(sizeof(Button_t));
			Button_initWith(btn, array[i].wid,
				array[i].x, array[i].y, array[i].w, array[i].h,
				_self->super.mMsg);
	        _self->mWidgetArray[i] = (Widget_t *)btn;
		}
		else if(array[i].wtype == WGT_MTX){
			TouchMtx_t *mtx = (TouchMtx_t *)malloc(sizeof(TouchMtx_t));
			TouchMtx_initWith(mtx, array[i].wid,
                array[i].x, array[i].y, array[i].w, array[i].h,
                array[i].gw, array[i].gh, _self->super.mMsg);
			 _self->mWidgetArray[i] = (Widget_t *)mtx;
		}
	}
}

static void setInputPara(View_t *_self, Transfer_t* trans)
{
	_self->mInputPara.currentViewId = trans->currentViewId;
	_self->mInputPara.targetViewId = trans->targetViewId;
	_self->mInputPara.type = trans->type;
	_self->mInputPara.p1 = trans->p1;
	_self->mInputPara.p2 = trans->p2;
	_self->mInputPara.p3 = trans->p3;
	_self->mInputPara.p4 = trans->p4;
}

static void setTransfer(View_t *_self, int target, int type, int p1, int p2, int p3, int p4)
{
	_self->mTransfer.currentViewId = _self->super.mId;
	_self->mTransfer.targetViewId = target;
	_self->mTransfer.type = type;
	_self->mTransfer.p1 = p1;
	_self->mTransfer.p2 = p2;
	_self->mTransfer.p3 = p3;
	_self->mTransfer.p4 = p4;
}

static Transfer_t* getTransfer(View_t *_self)
{
	return &_self->mTransfer;
}

static void clearTransfer(View_t *_self)
{
	_self->mTransfer.currentViewId = -1;
	_self->mTransfer.targetViewId = -1;
	_self->mTransfer.type = TRANS_NONE;
	_self->mTransfer.p1 = -1;
	_self->mTransfer.p2 = -1;
	_self->mTransfer.p3 = -1;
	_self->mTransfer.p4 = -1;
}

static void clearRefreshFlag(View_t *_self)
{
    _self->mRefreshFlag = false;
}

static bool getRefreshFlag(View_t *_self)
{
    return _self->mRefreshFlag;
}

static void setMoveDirection(View_t *_self, int direction)
{
    _self->mMoveDirection = direction;
}

static void setMoveThreshold(int threshold)
{
    mMoveThreshold = threshold;
}

void View_init(View_t *_self)
{
    Widget_init(&_self->super);
	Widget_init(&_self->super_f);

	_self->mTX0 = 0;
	_self->mTY0 = 0;
	_self->mMoveDirection = SLIDE_DET_NONE;

	_self->onCreate = onCreate;
	_self->onEnter = onEnter;
	_self->onExit = onExit;
	_self->onHide = onHide;
	_self->onShow = onShow;
	_self->onTouchOn = onTouchOn;
	_self->onTouchOff = onTouchOff;
	_self->onTouchMove = onTouchMove;
	_self->onDraw = onDraw;
	_self->procEvent = procEvent;
	_self->sendEvent = sendEvent;
	_self->regWidgets = regWidgets;
	_self->setInputPara = setInputPara;
	_self->setTransfer = setTransfer;
	_self->getTransfer = getTransfer;
	_self->clearTransfer = clearTransfer;
	_self->clearRefreshFlag = clearRefreshFlag;
	_self->getRefreshFlag = getRefreshFlag;
	_self->setMoveDirection = setMoveDirection;
	_self->setMoveThreshold = setMoveThreshold;
}

void View_initWith(View_t *_self, int vid0, int x0, int y0, int w0, int h0, Msg_t *msg0)
{
	View_init(_self);
    Widget_initWith(&_self->super, vid0, x0, y0, w0, h0, msg0);
	Widget_init(&_self->super_f);
}

