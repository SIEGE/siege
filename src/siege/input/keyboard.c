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
#include "../internal/bitop.h"

#define SG_NUM_KEYS     0x400

#define KEYARR_LENGTH   ARR_BITLENGTH(SG_NUM_KEYS)

#if SG_NUM_KEYS % 64
#error "SG_NUM_KEYS must be divisible by 64!"
#endif

static SGulong _sg_keyPrev[KEYARR_LENGTH];
static SGulong _sg_keyCurr[KEYARR_LENGTH];
static SGulong _sg_keyAgn[KEYARR_LENGTH];

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
    memcpy(_sg_keyPrev, _sg_keyCurr, sizeof(_sg_keyCurr));
    memset(_sg_keyAgn, 0, sizeof(_sg_keyAgn));
}
void SG_CALL _sgKeyboardUpdatePost(void)
{
    SGenum i, j;
    SGulong buffer;
    for(i = 0; i < KEYARR_LENGTH; i++)
    {
        j = i * ARR_BITS;
        for(buffer = ARR_BITITEM(_sg_keyCurr, i); buffer; buffer >>= 1)
        {
            if(buffer & 1)
                sgEntityEventSignal(1, (SGenum)SG_EVF_KEYKEYH, j);
            j++;
        }
    }
}

SGbool SG_CALL _sgKeyboardInit(void)
{
    memset(_sg_keyPrev, 0, sizeof(_sg_keyPrev));
    memset(_sg_keyCurr, 0, sizeof(_sg_keyCurr));
    memset(_sg_keyAgn, 0, sizeof(_sg_keyAgn));
    return SG_TRUE;
}
SGbool SG_CALL _sgKeyboardDeinit(void)
{
    return SG_TRUE;
}

void SG_CALL _sgKeyboardKeyUpdate(SGenum key, SGbool down)
{
    if(key >= SG_NUM_KEYS) return;
    SET_BITARR(_sg_keyAgn, key, GET_BITARR(_sg_keyAgn, key) == down);
    SET_BITARR_CURR(key, key, down);
}

SGbool SG_CALL sgKeyboardKey(SGenum key)
{
    if(key >= SG_NUM_KEYS) return SG_FALSE;
    return _sg_keyCurr[key];
}
SGbool SG_CALL sgKeyboardKeyPress(SGenum key)
{
    if(key >= SG_NUM_KEYS) return SG_FALSE;
    return !_sg_keyPrev[key] && _sg_keyCurr[key];
}
SGbool SG_CALL sgKeyboardKeyRelease(SGenum key)
{
    if(key >= SG_NUM_KEYS) return SG_FALSE;
    return _sg_keyPrev[key] && !_sg_keyCurr[key];
}
SGbool SG_CALL sgKeyboardKeyRepeat(SGenum key)
{
    if(key >= SG_NUM_KEYS) return SG_FALSE;
    return _sg_keyAgn[key];
}
