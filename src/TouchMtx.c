#include "TouchMtx.h"

static void onTouchOn(TouchMtx_t *_self, int x0, int y0)
{
	int last_state = _self->super.mState;
	_self->super_f.onTouchOn(&_self->super, x0, y0);

	if((last_state == TOUCH_OFF)
		&&(_self->super.mState == TOUCH_ON)){

        if((! _self->super.isDisabled(&_self->super))
           &&(! _self->super.isHiden(&_self->super))){
			_self->gx = (int)((x0-_self->super.mX)/_self->gw);
			_self->gy = (int)((y0-_self->super.mY)/_self->gh);

			_LOGI("TMtx", "EV_MTX_DOWN, id=%d, x=%d, y=%d\n", _self->super.mId, _self->gx, _self->gy);
            _self->super.setEvent(&_self->super, _self->super.mId, EV_MTX_DOWN, _self->gx, _self->gy, 0, 0);
		}
	}
}

static void onTouchOff(TouchMtx_t *_self, int x0, int y0)
{
	int last_state = _self->super.mState;
	_self->super_f.onTouchOff(&_self->super, x0, y0);
	
	if((last_state == TOUCH_ON)
		&&(_self->super.mState == TOUCH_OFF)){
        if((! _self->super.isDisabled(&_self->super))
           &&(! _self->super.isHiden(&_self->super))){
           _LOGI("TMtx", "EV_MTX_UP, id=%d, x=%d, y=%d\n", _self->super.mId, _self->gx, _self->gy);
			_self->super.setEvent(&_self->super, _self->super.mId, EV_MTX_UP, _self->gx, _self->gy, 0, 0);
		}
	}
}

void TouchMtx_initWith(TouchMtx_t *_self, int wid0, 
	int x0, int y0, int w0, int h0, double gw0, double gh0, Msg_t *msg0)
{
	Widget_initWith(&_self->super, wid0, x0, y0, w0, h0, msg0);
	Widget_init(&_self->super_f);
    _self->super.onTouchOn = onTouchOn;
	_self->super.onTouchOff = onTouchOff;
	_self->onTouchOn = onTouchOn;
	_self->onTouchOff = onTouchOff;
	_self->gw = gw0;
	_self->gh = gh0;
	_self->gx = 0;
	_self->gy = 0;
}

