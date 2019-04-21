#include "View.h"
#include "ViewStack.h"

#define	TAG				"vStack"

static void regView(ViewStack_t *_self, int vid, View_t* view)
{
	_LOGI(TAG, "regView, vid=%d\n", vid);

	if(vid < STACK_SIZE)
	{
    	_self->mIndex[vid] = view;
	}
	else
	{
		_LOGE(TAG, "regView, invalid view id! vid=%d\n", vid);
	}
}

static void setInputPara(ViewStack_t *_self, int vid, Transfer_t* trans)
{
    _self->mIndex[vid]->setInputPara(_self->mIndex[vid], trans);
}

static void push1stView(ViewStack_t *_self, int vid)
{
	_LOGI(TAG, "push1stView, vid=%d\n", vid);
	_self->mSp = 0;
    _self->mStack[_self->mSp] = _self->mIndex[vid];
    _self->mStack[_self->mSp]->onCreate(_self->mStack[_self->mSp]);
    _self->mStack[_self->mSp]->onEnter(_self->mStack[_self->mSp]);
    _self->mStack[_self->mSp]->onShow(_self->mStack[_self->mSp]);
}

static void callView(ViewStack_t *_self, int vid)
{
	_LOGI(TAG, "callView, vid=%d\n", vid);
	
	_self->mStack[_self->mSp]->onHide(_self->mStack[_self->mSp]);
	_self->mSp++;
	_self->mStack[_self->mSp] = _self->mIndex[vid];
	_self->mStack[_self->mSp]->onCreate(_self->mStack[_self->mSp]);
    _self->mStack[_self->mSp]->onEnter(_self->mStack[_self->mSp]);
    _self->mStack[_self->mSp]->onShow(_self->mStack[_self->mSp]);
}

static void returnView(ViewStack_t *_self)
{
	_LOGI(TAG, "returnView, vid=%d\n", _self->mStack[_self->mSp]->super.mId);
	_self->mStack[_self->mSp]->onHide(_self->mStack[_self->mSp]);
	_self->mStack[_self->mSp]->onExit(_self->mStack[_self->mSp]);
	_self->mSp--;
	_self->mStack[_self->mSp]->onShow(_self->mStack[_self->mSp]);
}

static void changeView(ViewStack_t *_self, int vid)
{
	_LOGI(TAG, "changeView, vid=%d\n", vid);
	
	_self->mStack[_self->mSp]->onHide(_self->mStack[_self->mSp]);
	_self->mStack[_self->mSp]->onExit(_self->mStack[_self->mSp]);

	_self->mStack[_self->mSp] = _self->mIndex[vid];
	_self->mStack[_self->mSp]->onCreate(_self->mStack[_self->mSp]);
	_self->mStack[_self->mSp]->onEnter(_self->mStack[_self->mSp]);
	_self->mStack[_self->mSp]->onShow(_self->mStack[_self->mSp]);
}

static View_t* getTopView(ViewStack_t *_self)
{
	return _self->mStack[_self->mSp];
}

static View_t* transfer(ViewStack_t *_self)
{
    View_t *topView = _self->getTopView(_self);
    Transfer_t *trans = topView->getTransfer(topView);
	int target = trans->targetViewId;
    
    if(trans->type == TRANS_CHANGE)
    {
        _self->setInputPara(_self, target, trans);
        topView->clearTransfer(topView);
        _self->changeView(_self, target);
        topView = _self->getTopView(_self);
    }
    else if(trans->type == TRANS_CALL)
    {
        _self->setInputPara(_self, target, trans);
        topView->clearTransfer(topView);
        _self->callView(_self, target);
        topView = _self->getTopView(_self);
    }
    else if(trans->type == TRANS_RETURN)
    {
    	Widget_t *wdg = (Widget_t*)_self->mStack[_self->mSp-1];
    	target = wdg->mId;
    	_self->setInputPara(_self, target, trans);
        topView->clearTransfer(topView);
        _self->returnView(_self);
        topView = _self->getTopView(_self);
    }

	return topView;
}

void ViewStack_init(ViewStack_t *_self)
{
	int i;
	_self->mSp = 0;
    
    for(i = 0; i < STACK_SIZE; i++){
        _self->mStack[i] = NULL;
		_self->mIndex[i] = NULL;
    }

	_self->regView = regView;
	_self->setInputPara = setInputPara;
	_self->push1stView = push1stView;
	_self->callView = callView;
	_self->returnView = returnView;
	_self->changeView = changeView;
	_self->getTopView = getTopView;
	_self->transfer = transfer;
}
