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
#include <siege/input/vinput.h>
#include <siege/core/entity.h>

#include <stdlib.h>
#include <string.h>

#include <SDL/SDL.h>
#include "../internal/bitop.h"

#define SGI_KEYARR_LENGTH   ARR_BITLENGTH(SGI_NUM_KEYS)

SGulong _sg_keyPrev[SGI_KEYARR_LENGTH];
SGulong _sg_keyCurr[SGI_KEYARR_LENGTH];
SGulong _sg_keyAgn[SGI_KEYARR_LENGTH];

#if SGI_NUM_KEYS % 64
#error "SGI_NUM_KEYS must be divisible by 64!"
#endif

void SG_CALL _sg_cbKeyboardKey(SGenum key, SGbool down)
{
    _sgKeyboardKeyUpdate(key, down);
    SGbool pressed = sgKeyboardKeyPress(key);

    size_t numevents = 1;
    SGenum event;
    if(pressed)
        event = SG_EVF_INPUTBUTP;
    else if(!down)
        event = SG_EVF_INPUTBUTR;
    else
    {
        /* repeat (but we ignore it) */
        event = 0;
        numevents--;
    }

    sgEntityEventSignal(numevents, event, SG_INPUT_ID_KEYBOARD, key);
}
void SG_CALL _sg_cbKeyboardChar(SGdchar chr)
{
    sgEntityEventSignal(1, (SGenum)SG_EVF_TEXTCHARP, chr);
}

void SG_CALL _sgKeyboardUpdatePre(void)
{
    memcpy(_sg_keyPrev, _sg_keyCurr, SGI_KEYARR_LENGTH * sizeof(*_sg_keyCurr));
    memset(_sg_keyAgn, 0, SGI_KEYARR_LENGTH * sizeof(*_sg_keyAgn));
}
void SG_CALL _sgKeyboardUpdatePost(void)
{
    SGenum i, j;
    SGulong buffer;
    for(i = 0; i < SGI_KEYARR_LENGTH; i++)
    {
        j = i * ARR_BITS;
        for(buffer = _sg_keyCurr[i]; buffer; buffer >>= 1)
        {
            if(buffer & 1)
                sgEntityEventSignal(1, (SGenum)SG_EVF_INPUTBUTH, SG_INPUT_ID_KEYBOARD, j);
            j++;
        }
    }
    _sgVInputUpdateKeyboard();
}

SGbool SG_CALL _sgKeyboardInit(void)
{
    memset(_sg_keyPrev, 0, SGI_KEYARR_LENGTH * sizeof(*_sg_keyPrev));
    memset(_sg_keyCurr, 0, SGI_KEYARR_LENGTH * sizeof(*_sg_keyCurr));
    memset(_sg_keyAgn, 0, SGI_KEYARR_LENGTH * sizeof(*_sg_keyAgn));
    return SG_TRUE;
}
SGbool SG_CALL _sgKeyboardDeinit(void)
{
    return SG_TRUE;
}

void SG_CALL _sgKeyboardKeyUpdate(SGenum key, SGbool down)
{
    if(key >= SGI_NUM_KEYS) return;
    SET_BITARR(_sg_keyAgn, key, GET_BITARR(_sg_keyAgn, key) == down);
    SET_BITARR_CURR(key, key, down);
}

SGbool SG_CALL sgKeyboardKey(SGenum key)
{
    if(key >= SGI_NUM_KEYS) return SG_FALSE;
    return GET_BITARR_CURR(key, key);
}
SGbool SG_CALL sgKeyboardKeyPress(SGenum key)
{
    if(key >= SGI_NUM_KEYS) return SG_FALSE;
    return !GET_BITARR_PREV(key, key) && GET_BITARR_CURR(key, key);
}
SGbool SG_CALL sgKeyboardKeyRelease(SGenum key)
{
    if(key >= SGI_NUM_KEYS) return SG_FALSE;
    return GET_BITARR_PREV(key, key) && !GET_BITARR_CURR(key, key);
}
SGbool SG_CALL sgKeyboardKeyRepeat(SGenum key)
{
    if(key >= SGI_NUM_KEYS) return SG_FALSE;
    return GET_BITARR(_sg_keyAgn, key);
}
