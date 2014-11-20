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
#include <siege/input/keyboard.h>
#include <siege/core/window.h>
#include <siege/core/entity.h>

#include <stdlib.h>
#include <string.h>

#include <SDL/SDL.h>

void SG_CALL _sg_cbKeyboardKey(SGenum key, SGbool down)
{
    _sgKeyboardKeyUpdate(key, down);
    SGbool pressed = sgKeyboardKeyPress(key);

    SGenum evt;
    if(pressed)
        evt = SG_EVF_KEYKEYP;
    else if(!down)
        evt = SG_EVF_KEYKEYR;
    else
        evt = SG_EVF_KEYKEYA;

    sgEntityEventSignal(1, evt, key);
}
void SG_CALL _sg_cbKeyboardChar(SGdchar chr)
{
    sgEntityEventSignal(1, (SGenum)SG_EVF_KEYCHARP, chr);
}

void SG_CALL _sgKeyboardUpdatePre(void)
{
    memcpy(_sg_keyPrev, _sg_keyCurr, SG_KEY_NUM * sizeof(*_sg_keyCurr));
    memset(_sg_keyAgn, 0, SG_KEY_NUM * sizeof(*_sg_keyAgn));
}
void SG_CALL _sgKeyboardUpdatePost(void)
{
    SGenum i;
    for(i = 0; i < SG_KEY_NUM; i++)
        if(_sg_keyCurr[i])
            sgEntityEventSignal(1, (SGenum)SG_EVF_KEYKEYH, i);
}

SGbool SG_CALL _sgKeyboardInit(void)
{
    memset(_sg_keyPrev, 0, SG_KEY_NUM * sizeof(SGbool));
    memset(_sg_keyCurr, 0, SG_KEY_NUM * sizeof(SGbool));
    return SG_TRUE;
}
SGbool SG_CALL _sgKeyboardDeinit(void)
{
    return SG_TRUE;
}

void SG_CALL _sgKeyboardKeyUpdate(SGenum key, SGbool down)
{
    if(key >= SG_KEY_NUM) return;
    _sg_keyAgn[key] = (_sg_keyCurr[key] == down);
    _sg_keyCurr[key] = down;
}

SGbool SG_CALL sgKeyboardKey(SGenum key)
{
    if(key >= SG_KEY_NUM) return SG_FALSE;
    return _sg_keyCurr[key];
}
SGbool SG_CALL sgKeyboardKeyPress(SGenum key)
{
    if(key >= SG_KEY_NUM) return SG_FALSE;
    return !_sg_keyPrev[key] && _sg_keyCurr[key];
}
SGbool SG_CALL sgKeyboardKeyRelease(SGenum key)
{
    if(key >= SG_KEY_NUM) return SG_FALSE;
    return _sg_keyPrev[key] && !_sg_keyCurr[key];
}
SGbool SG_CALL sgKeyboardKeyRepeat(SGenum key)
{
    if(key >= SG_KEY_NUM) return SG_FALSE;
    return _sg_keyAgn[key];
}
