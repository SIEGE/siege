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
    _sgVInputUpdateMouse();
    SGbool pressed = sgMouseGetButtonPress(button);

    size_t numevents = 1;
    SGenum event;
    if(pressed)
        event = SG_EVF_INPUTBUTP;
    else if(!down)
        event = SG_EVF_INPUTBUTR;
    else
    {
        event = 0;
        numevents--;
    }

    sgEntityEventSignal(numevents, event, SG_INPUT_ID_MOUSE, button);
}
void SG_CALL _sg_cbMouseMove(SGint x, SGint y)
{
    _sg_mousePosPrev = _sg_mousePos;
    _sg_mousePos = sgIVec2i(x, y);
    _sgVInputUpdateMouse();

    sgEntityEventSignal(1, (SGenum)SG_EVF_INPUTPMOVE, SG_INPUT_ID_MOUSE, _sg_inputs[SG_INPUT_ID_MOUSE].pos, (size_t)2);
}
void SG_CALL _sg_cbMouseWheel(SGint dw)
{
    _sg_mouseWheelPrev = _sg_mouseWheel;
    _sg_mouseWheel = dw;
    _sgVInputUpdateMouse();

    sgEntityEventSignal(1, (SGenum)SG_EVF_INPUTAMOVE, SG_INPUT_ID_MOUSE, _sg_inputs[SG_INPUT_ID_MOUSE].axis, (size_t)1);
}

void SG_CALL _sgMouseUpdate(void)
{
    SGuint i = 1;
    SGulong buttons;
    for(buttons = _sg_mouseButtonCurr; buttons; buttons >>= 1)
    {
        if(buttons & 1)
            sgEntityEventSignal(1, (SGenum)SG_EVF_INPUTBUTH, SG_INPUT_ID_MOUSE, i);
        i++;
    }
    _sg_mouseButtonPrev = _sg_mouseButtonBuff;
    _sg_mouseButtonBuff = _sg_mouseButtonCurr;
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
