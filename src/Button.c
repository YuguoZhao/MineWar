#include "Button.h"

static void onTouchOn(Button_t *_self, int x0, int y0)
{
	int last_state = _self->super.mState;
    _self->super_f.onTouchOn(&_self->super, x0, y0);

	if((last_state == TOUCH_OFF)
		&&(_self->super.mState == TOUCH_ON))
	{
        if((! _self->super.isDisabled(&_self->super))
           &&(! _self->super.isHiden(&_self->super))){
           _LOGI("Button", "EV_KEY_DOWN, id=%d\n", _self->super.mId);
            _self->super.setEvent(&_self->super, _self->super.mId, EV_KEY_DOWN, 0, 0, 0, 0);
		}
	}
}

static void onTouchOff(Button_t *_self, int x0, int y0)
{
	int last_state = _self->super.mState;
    _self->super_f.onTouchOff(&_self->super, x0, y0);
	
	if((last_state == TOUCH_ON)
		&&(_self->super.mState == TOUCH_OFF))
	{
		if((! _self->super.isDisabled(&_self->super))
           &&(! _self->super.isHiden(&_self->super))){
           _LOGI("Button", "EV_KEY_UP, id=%d\n", _self->super.mId);
			_self->super.setEvent(&_self->super, _self->super.mId, EV_KEY_UP, 0, 0, 0, 0);
		}
	}
}

void Button_initWith(Button_t *_self, int wid0, int x0, int y0, int w0, int h0, Msg_t *msg0)
{
	Widget_initWith(&_self->super, wid0, x0, y0, w0, h0, msg0);
	Widget_init(&_self->super_f);
    _self->super.onTouchOn = onTouchOn;
	_self->super.onTouchOff = onTouchOff;
	_self->onTouchOn = onTouchOn;
	_self->onTouchOff = onTouchOff;
}