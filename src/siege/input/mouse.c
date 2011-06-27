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
    _sg_mouseButtonPrev[button - 1] = _sg_mouseButtonCurr[button - 1];
    _sg_mouseButtonCurr[button - 1] = down;

    SGbool pressed = sgMouseGetButtonPress(button);

    SGenum events[4];
    memset(events, 0, sizeof(events));

    events[0] = SG_EVF_MOUSEBUTH;
    if(pressed)
        events[1] = SG_EVF_MOUSEBUTP;
    else if(!down)
        events[1] = SG_EVF_MOUSEBUTR;
    switch(button)
    {
        case SG_MOUSE_BUTTON_LEFT:
            events[2] = SG_EVF_MOUSEBUTLH;
            if(pressed)
                events[3] = SG_EVF_MOUSEBUTLP;
            else if(!down)
                events[3] = SG_EVF_MOUSEBUTLR;
            break;
        case SG_MOUSE_BUTTON_RIGHT:
            events[2] = SG_EVF_MOUSEBUTRH;
            if(pressed)
                events[3] = SG_EVF_MOUSEBUTRP;
            else if(!down)
                events[3] = SG_EVF_MOUSEBUTRR;
            break;
        case SG_MOUSE_BUTTON_MIDDLE:
            events[2] = SG_EVF_MOUSEBUTMH;
            if(pressed)
                events[3] = SG_EVF_MOUSEBUTMP;
            else if(!down)
                events[3] = SG_EVF_MOUSEBUTMR;
            break;
        default:
            break;
    }

    sgEventCall(SG_EV_INTERNAL, (SGuint)4, events[0], button, events[1], button, events[2], events[3]);
}
void SG_EXPORT _sg_cbMouseMove(void* mouse, SGint x, SGint y)
{
    _sg_mouseXPrev = _sg_mouseX;
    _sg_mouseYPrev = _sg_mouseY;
    _sg_mouseX = x;
    _sg_mouseY = y;

    sgEventCall(SG_EV_INTERNAL, (SGuint)1, (SGenum)SG_EVF_MOUSEMOVE, x, y);
}
void SG_EXPORT _sg_cbMouseWheel(void* mouse, SGint w)
{
    _sg_mouseWheelPrev = _sg_mouseWheel;
    _sg_mouseWheel = w;

    sgEventCall(SG_EV_INTERNAL, (SGuint)1, (SGenum)SG_EVF_MOUSEWHEEL, w);
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
