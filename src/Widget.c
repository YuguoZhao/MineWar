#include "Widget.h"

static bool isInRect(Widget_t *_self, int x0, int y0)
{
	if((x0 >= _self->mX)
		&&(y0 >= _self->mY)
		&&(x0 < _self->mX+_self->mW)
		&&(y0 < _self->mY+_self->mH))
	{
		return true;
	}
	else
	{
		return false;
	}
}

static void show(Widget_t *_self)
{
	_self->mProperty &= (~PROPERTY_HIDE);
}

static void hide(Widget_t *_self)
{
	_self->mProperty |= PROPERTY_HIDE;
}

static void enable(Widget_t *_self)
{
	_self->mProperty &= (~PROPERTY_DISABLE);
}

static void disable(Widget_t *_self)
{
	_self->mProperty |= PROPERTY_DISABLE;
}

static bool isDisabled(Widget_t *_self)
{
	if((_self->mProperty&PROPERTY_DISABLE) != 0){
		return true;
	}
	else{
		return false;
	}
}

static bool isHiden(Widget_t *_self)
{
	if((_self->mProperty&PROPERTY_HIDE) != 0){
		return true;
	}
	else{
		return false;
	}
}

static void onTouchOn(Widget_t *_self, int x0, int y0)
{
    if(_self->isInRect(_self, x0, y0)){
		_self->mTX = x0;
		_self->mTY = y0;
		_self->mState = TOUCH_ON;
	}
}

static void onTouchOff(Widget_t *_self, int x0, int y0)
{
	_self->mState = TOUCH_OFF;
}

static void onTouchMove(Widget_t *_self, int x0, int y0)
{
	_self->mTX = x0;
	_self->mTY = y0;
}

static void onTouchClear(Widget_t *_self)
{
	_self->mState = TOUCH_OFF;
}

static void setEvent(Widget_t *_self, int mid, int event, int p1, int p2, int p3, int p4)
{
	_self->mMsg->mid = mid;
	_self->mMsg->event = event;
	_self->mMsg->p1 = p1;
	_self->mMsg->p2 = p2;
	_self->mMsg->p3 = p3;
	_self->mMsg->p4 = p4;
}

static Msg_t* getEvent(Widget_t *_self)
{
	return _self->mMsg;
}

static void clearEvent(Widget_t *_self)
{
	_self->mMsg->mid = -1;
	_self->mMsg->event = NO_EVENT;
	_self->mMsg->p1 = -1;
	_self->mMsg->p2 = -1;
	_self->mMsg->p3 = -1;
	_self->mMsg->p4 = -1;
}

static int getId(Widget_t *_self)
{
    return _self->mId;
}

void Widget_init(Widget_t *_self)
{
	_self->isInRect = isInRect;
	_self->show = show;
	_self->hide = hide;
	_self->isHiden = isHiden;
	_self->enable = enable;
	_self->disable = disable;
	_self->isDisabled = isDisabled;
	_self->onTouchOn = onTouchOn;
	_self->onTouchOff = onTouchOff;
	_self->onTouchMove = onTouchMove;
	_self->onTouchClear = onTouchClear;
	_self->setEvent = setEvent;
	_self->getEvent = getEvent;
	_self->clearEvent = clearEvent;
	_self->getId = getId;

	_self->mId = 0;
    _self->mX = 0;
    _self->mY = 0;
    _self->mW = 0;
    _self->mH = 0;
    _self->mTX = 0;
    _self->mTY = 0;
    _self->mState = TOUCH_OFF;
    _self->mProperty = 0;
	_self->mMsg = NULL;
}

void Widget_initWith(Widget_t *_self, int wid0, 
	int x0, int y0, int w0, int h0, Msg_t *msg0)
{
	Widget_init(_self);
	_self->mId = wid0;
	_self->mX = x0;
	_self->mY = y0;
	_self->mW = w0;
	_self->mH = h0;
	_self->mMsg = msg0;
	_self->mMsg->event = NO_EVENT;
	_self->mTX = 0;
	_self->mTY = 0;
	_self->mState = TOUCH_OFF;
	_self->mProperty = 0;
	_self->clearEvent(_self);
}