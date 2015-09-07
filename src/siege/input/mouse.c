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
#include <siege/input/vinput.h>
#include <siege/core/window.h>
#include <siege/core/entity.h>

#include <stdlib.h>
#include <string.h>

#include <SDL/SDL.h>
#include "../internal/bitop.h"

void SG_CALL _sg_cbMouseButton(SGuint button, SGbool down)
{
    SET_BIT_CURR(mouseButton, button - 1, down);

    SGbool pressed = sgMouseGetButtonPress(button);

    size_t numevents = 2;
    SGenum events[2];

    if(pressed)
        events[0] = SG_EVF_MOUSEBUTP;
    else if(!down)
        events[0] = SG_EVF_MOUSEBUTR;
    else
    {
        events[0] = 0;
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
            events[--numevents] = 0;
            break;
    }

    SG_ASSERT(numevents >= 2 || !events[1], "incorrectly initialized events[1]");
    SG_ASSERT(numevents >= 1 || !events[0], "incorrectly initialized events[0]");
    sgEntityEventSignal(numevents, events[0], button, events[1]);
}
void SG_CALL _sg_cbMouseMove(SGint x, SGint y)
{
    _sg_mousePosPrev = _sg_mousePos;
    _sg_mousePos = sgIVec2i(x, y);

    sgEntityEventSignal(1, (SGenum)SG_EVF_MOUSEMOVE, x, y);
}
void SG_CALL _sg_cbMouseWheel(SGint dw)
{
    _sg_mouseWheelPrev = _sg_mouseWheel;
    _sg_mouseWheel = _sg_mouseWheelPrev + dw;

    sgEntityEventSignal(1, (SGenum)SG_EVF_MOUSEWHEEL, _sg_mouseWheel);
}

void SG_CALL _sgMouseUpdate(void)
{
    size_t numevents;
    SGenum events[2];

    SGuint i = 1;
    SGulong buttons;
    for(buttons = _sg_mouseButtonCurr; buttons; buttons >>= 1)
    {
        if(buttons & 1)
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
            sgEntityEventSignal(numevents, events[0], i, events[1]);
        }
        i++;
    }
    _sg_mouseButtonPrev = _sg_mouseButtonBuff;
    _sg_mouseButtonBuff = _sg_mouseButtonCurr;

    _sgVInputUpdateMouse();
}

SGbool SG_CALL _sgMouseInit(void)
{
    _sg_mouseButtonPrev = 0;
    _sg_mouseButtonCurr = 0;
    _sg_mouseButtonBuff = 0;

    _sg_mousePosPrev = sgIVec2i(0, 0);
    _sg_mousePos = sgIVec2i(0, 0);
    _sg_mouseWheelPrev = 0;
    _sg_mouseWheel = 0;

    return SG_TRUE;
}
SGbool SG_CALL _sgMouseDeinit(void)
{
    return SG_TRUE;
}

void SG_CALL sgMouseMove(SGint x, SGint y)
{
    SDL_WarpMouse(x, y);
    _sg_mousePosPrev = _sg_mousePos;
    _sg_mousePos = sgIVec2i(x, y);
}

void SG_CALL sgMouseSetVisible(SGbool vis)
{
    SDL_ShowCursor(vis);
}
void SG_CALL sgMouseShow(void)
{
    sgMouseSetVisible(SG_TRUE);
}
void SG_CALL sgMouseHide(void)
{
    sgMouseSetVisible(SG_FALSE);
}

SGIVec2 SG_CALL sgMouseGetPosPrev2iv(void)
{
    return _sg_mousePosPrev;
}
SGVec2 SG_CALL sgMouseGetPosPrev2fv(void)
{
    return sgVec2iv(sgMouseGetPosPrev2iv());
}
SGint SG_CALL sgMouseGetPosPrevX(void)
{
    return _sg_mousePosPrev.x;
}
SGint SG_CALL sgMouseGetPosPrevY(void)
{
    return _sg_mousePosPrev.y;
}

SGIVec2 SG_CALL sgMouseGetPos2iv(void)
{
    return _sg_mousePos;
}
SGVec2 SG_CALL sgMouseGetPos2fv(void)
{
    return sgVec2iv(sgMouseGetPos2iv());
}
SGint SG_CALL sgMouseGetPosX(void)
{
    return _sg_mousePos.x;
}
SGint SG_CALL sgMouseGetPosY(void)
{
    return _sg_mousePos.y;
}

SGIVec2 SG_CALL sgMouseGetDelta2iv(void)
{
    return sgIVec2Sub(sgMouseGetPos2iv(), sgMouseGetPosPrev2iv());
}
SGVec2 SG_CALL sgMouseGetDelta2fv(void)
{
    return sgVec2iv(sgMouseGetDelta2iv());
}

SGint SG_CALL sgMouseGetWheelPrev(void)
{
    return _sg_mouseWheelPrev;
}
SGint SG_CALL sgMouseGetWheel(void)
{
    return _sg_mouseWheel;
}

SGulong SG_CALL sgMouseGetButtonMaskPrev(void)
{
    return _sg_mouseButtonPrev;
}
SGulong SG_CALL sgMouseGetButtonMask(void)
{
    return _sg_mouseButtonCurr;
}

SGbool SG_CALL sgMouseGetButtonPrev(SGuint button)
{
    return GET_BIT_PREV(mouseButton, button - 1);
}
SGbool SG_CALL sgMouseGetButton(SGuint button)
{
    return GET_BIT_CURR(mouseButton, button - 1);
}
SGbool SG_CALL sgMouseGetButtonPress(SGuint button)
{
    return !GET_BIT_PREV(mouseButton, button - 1) && GET_BIT_CURR(mouseButton, button - 1);
}
SGbool SG_CALL sgMouseGetButtonRelease(SGuint button)
{
    return GET_BIT_PREV(mouseButton, button - 1) && !GET_BIT_CURR(mouseButton, button - 1);
}

SGbool SG_CALL sgMouseGetButtonLeftPrev(void)
{
    return sgMouseGetButtonPrev(SG_MOUSE_BUTTON_LEFT);
}
SGbool SG_CALL sgMouseGetButtonLeft(void)
{
    return sgMouseGetButton(SG_MOUSE_BUTTON_LEFT);
}
SGbool SG_CALL sgMouseGetButtonLeftPress(void)
{
    return sgMouseGetButtonPress(SG_MOUSE_BUTTON_LEFT);
}
SGbool SG_CALL sgMouseGetButtonLeftRelease(void)
{
    return sgMouseGetButtonRelease(SG_MOUSE_BUTTON_LEFT);
}

SGbool SG_CALL sgMouseGetButtonRightPrev(void)
{
    return sgMouseGetButtonPrev(SG_MOUSE_BUTTON_RIGHT);
}
SGbool SG_CALL sgMouseGetButtonRight(void)
{
    return sgMouseGetButton(SG_MOUSE_BUTTON_RIGHT);
}
SGbool SG_CALL sgMouseGetButtonRightPress(void)
{
    return sgMouseGetButtonPress(SG_MOUSE_BUTTON_RIGHT);
}
SGbool SG_CALL sgMouseGetButtonRightRelease(void)
{
    return sgMouseGetButtonRelease(SG_MOUSE_BUTTON_RIGHT);
}

SGbool SG_CALL sgMouseGetButtonMiddlePrev(void)
{
    return sgMouseGetButtonPrev(SG_MOUSE_BUTTON_MIDDLE);
}
SGbool SG_CALL sgMouseGetButtonMiddle(void)
{
    return sgMouseGetButton(SG_MOUSE_BUTTON_MIDDLE);
}
SGbool SG_CALL sgMouseGetButtonMiddlePress(void)
{
    return sgMouseGetButtonPress(SG_MOUSE_BUTTON_MIDDLE);
}
SGbool SG_CALL sgMouseGetButtonMiddleRelease(void)
{
    return sgMouseGetButtonRelease(SG_MOUSE_BUTTON_MIDDLE);
}
