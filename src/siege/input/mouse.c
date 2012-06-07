/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "license.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
*/

#define SG_BUILD_LIBRARY
#include <siege/input/mouse.h>
#include <siege/core/window.h>
#include <siege/core/entity.h>

#include <stdlib.h>
#include <string.h>

void SG_EXPORT _sg_cbMouseButton(void* mouse, SGuint button, SGbool down)
{
    if(button - 1 >= _sg_mouseButtonNum)
        return;
    //_sg_mouseButtonPrev[button - 1] = !down; //_sg_mouseButtonCurr[button - 1];
    _sg_mouseButtonCurr[button - 1] = down;

    SGbool pressed = sgMouseGetButtonPress(button);

    size_t numevents = 2;
    SGenum events[2];

    if(pressed)
        events[0] = SG_EVF_MOUSEBUTP;
    else if(!down)
        events[0] = SG_EVF_MOUSEBUTR;
    else
    {
        events[1] = 0;
        numevents--;
    }
    switch(button)
    {
        case SG_MOUSE_BUTTON_LEFT:
            if(pressed)
                events[numevents-1] = SG_EVF_MOUSEBUTLP;
            else if(!down)
                events[numevents-1] = SG_EVF_MOUSEBUTLR;
            break;
        case SG_MOUSE_BUTTON_RIGHT:
            if(pressed)
                events[numevents-1] = SG_EVF_MOUSEBUTRP;
            else if(!down)
                events[numevents-1] = SG_EVF_MOUSEBUTRR;
            break;
        case SG_MOUSE_BUTTON_MIDDLE:
            if(pressed)
                events[numevents-1] = SG_EVF_MOUSEBUTMP;
            else if(!down)
                events[numevents-1] = SG_EVF_MOUSEBUTMR;
            break;
        default:
            numevents--;
            break;
    }

    sgEntityEventSignal(numevents, events[0], button, events[1]);
}
void SG_EXPORT _sg_cbMouseMove(void* mouse, SGint x, SGint y)
{
    _sg_mouseXPrev = _sg_mouseX;
    _sg_mouseYPrev = _sg_mouseY;
    _sg_mouseX = x;
    _sg_mouseY = y;

    sgEntityEventSignal(1, (SGenum)SG_EVF_MOUSEMOVE, x, y);
}
void SG_EXPORT _sg_cbMouseWheel(void* mouse, SGint w)
{
    _sg_mouseWheelPrev = _sg_mouseWheel;
    _sg_mouseWheel = w;

    sgEntityEventSignal(1, (SGenum)SG_EVF_MOUSEWHEEL, w);
}

void SG_EXPORT _sgMouseUpdate(void)
{
    size_t numevents;
	SGenum events[2];
	SGuint i;
	for(i = 0; i < _sg_mouseButtonNum; i++)
	{
		if(_sg_mouseButtonCurr[i])
		{
			numevents = 2;
			events[0] = SG_EVF_MOUSEBUTH;
			switch(i + 1)
			{
				case SG_MOUSE_BUTTON_LEFT:
					events[1] = SG_EVF_MOUSEBUTLH;
					break;
				case SG_MOUSE_BUTTON_RIGHT:
					events[1] = SG_EVF_MOUSEBUTRH;
					break;
				case SG_MOUSE_BUTTON_MIDDLE:
					events[1] = SG_EVF_MOUSEBUTMH;
					break;
				default:
                    events[1] = 0;
					numevents--;
					break;
			}
            sgEntityEventSignal(numevents, events[0], i + 1, events[1]);
		}
	}
    memcpy(_sg_mouseButtonPrev, _sg_mouseButtonBuff, _sg_mouseButtonNum * sizeof(SGbool));
    memcpy(_sg_mouseButtonBuff, _sg_mouseButtonCurr, _sg_mouseButtonNum * sizeof(SGbool));
}

SGbool SG_EXPORT _sgMouseInit(void)
{
    _sg_mouseCallbacks.button = _sg_cbMouseButton;
    _sg_mouseCallbacks.move = _sg_cbMouseMove;
    _sg_mouseCallbacks.wheel = _sg_cbMouseWheel;

    if(psgmCoreMouseCreate != NULL)
        psgmCoreMouseCreate(&_sg_mouseHandle, _sg_winHandle);

    if(psgmCoreMouseSetCallbacks != NULL)
        psgmCoreMouseSetCallbacks(_sg_mouseHandle, &_sg_mouseCallbacks);

    _sg_mouseButtonNum = 3;
    if(psgmCoreMouseGetNumButtons != NULL)
        psgmCoreMouseGetNumButtons(_sg_mouseHandle, &_sg_mouseButtonNum);
    _sg_mouseButtonPrev = malloc(_sg_mouseButtonNum * sizeof(SGbool));
    memset(_sg_mouseButtonPrev, 0, _sg_mouseButtonNum * sizeof(SGbool));
    _sg_mouseButtonBuff = malloc(_sg_mouseButtonNum * sizeof(SGbool));
    memset(_sg_mouseButtonBuff, 0, _sg_mouseButtonNum * sizeof(SGbool));
    _sg_mouseButtonCurr = malloc(_sg_mouseButtonNum * sizeof(SGbool));
    memset(_sg_mouseButtonCurr, 0, _sg_mouseButtonNum * sizeof(SGbool));

    _sg_mouseXPrev = 0;
    _sg_mouseYPrev = 0;
    _sg_mouseX = 0;
    _sg_mouseY = 0;
    _sg_mouseWheelPrev = 0;
    _sg_mouseWheel = 0;

    return SG_TRUE;
}
SGbool SG_EXPORT _sgMouseDeinit(void)
{
    free(_sg_mouseButtonPrev);
    free(_sg_mouseButtonBuff);
    free(_sg_mouseButtonCurr);
    _sg_mouseButtonNum = 0;

    if(psgmCoreMouseDestroy != NULL)
        psgmCoreMouseDestroy(_sg_mouseHandle);

    return SG_TRUE;
}

void SG_EXPORT sgMouseGetPosPrev(SGint* x, SGint* y)
{
    if(x != NULL)
        *x = _sg_mouseXPrev;
    if(y != NULL)
        *y = _sg_mouseYPrev;
}
SGint SG_EXPORT sgMouseGetPosPrevX(void)
{
    return _sg_mouseXPrev;
}
SGint SG_EXPORT sgMouseGetPosPrevY(void)
{
    return _sg_mouseYPrev;
}

void SG_EXPORT sgMouseGetPos(SGint* x, SGint* y)
{
    if(x != NULL)
        *x = _sg_mouseX;
    if(y != NULL)
        *y = _sg_mouseY;
}
SGint SG_EXPORT sgMouseGetPosX(void)
{
    return _sg_mouseX;
}
SGint SG_EXPORT sgMouseGetPosY(void)
{
    return _sg_mouseY;
}

SGint SG_EXPORT sgMouseGetWheelPrev(void)
{
    return _sg_mouseWheelPrev;
}
SGint SG_EXPORT sgMouseGetWheel(void)
{
    return _sg_mouseWheel;
}

SGbool SG_EXPORT sgMouseGetButtonPrev(SGuint button)
{
    if(button - 1 < _sg_mouseButtonNum)
        return _sg_mouseButtonPrev[button - 1];
    return SG_FALSE;
}
SGbool SG_EXPORT sgMouseGetButton(SGuint button)
{
    if(button - 1 < _sg_mouseButtonNum)
        return _sg_mouseButtonCurr[button - 1];
    return SG_FALSE;
}
SGbool SG_EXPORT sgMouseGetButtonPress(SGuint button)
{
    if(button - 1 < _sg_mouseButtonNum)
        return !_sg_mouseButtonPrev[button - 1] && _sg_mouseButtonCurr[button - 1];
    return SG_FALSE;
}
SGbool SG_EXPORT sgMouseGetButtonRelease(SGuint button)
{
    if(button - 1 < _sg_mouseButtonNum)
        return _sg_mouseButtonPrev[button - 1] && !_sg_mouseButtonCurr[button - 1];
    return SG_FALSE;
}

SGbool SG_EXPORT sgMouseGetButtonLeftPrev(void)
{
    return sgMouseGetButtonPrev(SG_MOUSE_BUTTON_LEFT);
}
SGbool SG_EXPORT sgMouseGetButtonLeft(void)
{
    return sgMouseGetButton(SG_MOUSE_BUTTON_LEFT);
}
SGbool SG_EXPORT sgMouseGetButtonLeftPress(void)
{
    return sgMouseGetButtonPress(SG_MOUSE_BUTTON_LEFT);
}
SGbool SG_EXPORT sgMouseGetButtonLeftRelease(void)
{
    return sgMouseGetButtonRelease(SG_MOUSE_BUTTON_LEFT);
}

SGbool SG_EXPORT sgMouseGetButtonRightPrev(void)
{
    return sgMouseGetButtonPrev(SG_MOUSE_BUTTON_RIGHT);
}
SGbool SG_EXPORT sgMouseGetButtonRight(void)
{
    return sgMouseGetButton(SG_MOUSE_BUTTON_RIGHT);
}
SGbool SG_EXPORT sgMouseGetButtonRightPress(void)
{
    return sgMouseGetButtonPress(SG_MOUSE_BUTTON_RIGHT);
}
SGbool SG_EXPORT sgMouseGetButtonRightRelease(void)
{
    return sgMouseGetButtonRelease(SG_MOUSE_BUTTON_RIGHT);
}

SGbool SG_EXPORT sgMouseGetButtonMiddlePrev(void)
{
    return sgMouseGetButtonPrev(SG_MOUSE_BUTTON_MIDDLE);
}
SGbool SG_EXPORT sgMouseGetButtonMiddle(void)
{
    return sgMouseGetButton(SG_MOUSE_BUTTON_MIDDLE);
}
SGbool SG_EXPORT sgMouseGetButtonMiddlePress(void)
{
    return sgMouseGetButtonPress(SG_MOUSE_BUTTON_MIDDLE);
}
SGbool SG_EXPORT sgMouseGetButtonMiddleRelease(void)
{
    return sgMouseGetButtonRelease(SG_MOUSE_BUTTON_MIDDLE);
}
