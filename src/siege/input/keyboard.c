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

void SG_EXPORT _sg_cbKeyboardKey(void* keyboard, SGenum key, SGbool down)
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

    //sgEventCall(SG_EV_INTERNAL, (SGuint)2, (SGenum)SG_EVF_KEYKEYH, key, evt, key);
    sgEventCall(SG_EV_INTERNAL, (SGuint)1, evt, key);
}
void SG_EXPORT _sg_cbKeyboardChar(void* keyboard, SGdchar chr, SGbool down)
{
    _sgKeyboardCharUpdate(chr, down);
    SGbool pressed = sgKeyboardCharPress(chr);

    SGenum evt = 0;
    if(pressed)
        evt = SG_EVF_KEYCHARP;
    /*else if(!down)
        evt = SG_EVF_KEYCHARR;*/
    else if(down)
        evt = SG_EVF_KEYCHARA;
    else
        return;

    sgEventCall(SG_EV_INTERNAL, (SGuint)1, evt, chr);
}

void SG_EXPORT _sgKeyboardUpdate(void)
{
    SGenum i;
    for(i = 0; i < SG_KEY_NUM; i++)
        if(_sg_keyCurr[i])
            sgEventCall(SG_EV_INTERNAL, (SGuint)1, (SGenum)SG_EVF_KEYKEYH, i);
}

SGbool SG_EXPORT _sgKeyboardInit(void)
{
    memset(_sg_keyPrev, 0, SG_KEY_NUM * sizeof(SGbool));
    memset(_sg_keyCurr, 0, SG_KEY_NUM * sizeof(SGbool));
    memset(_sg_charPrev, 0, SG_CHAR_NUM * sizeof(SGbool));
    memset(_sg_charCurr, 0, SG_CHAR_NUM * sizeof(SGbool));

    _sg_keyCallbacks.key = _sg_cbKeyboardKey;
    _sg_keyCallbacks.chr = _sg_cbKeyboardChar;

    if(psgmCoreKeyboardCreate != NULL)
        psgmCoreKeyboardCreate(&_sg_keyHandle, _sg_winHandle);
    if(psgmCoreKeyboardSetCallbacks != NULL)
        psgmCoreKeyboardSetCallbacks(_sg_keyHandle, &_sg_keyCallbacks);
    return SG_TRUE;
}
SGbool SG_EXPORT _sgKeyboardDeinit(void)
{
    if(psgmCoreKeyboardDestroy != NULL)
        psgmCoreKeyboardDestroy(_sg_keyHandle);
    return SG_TRUE;
}

void SG_EXPORT _sgKeyboardKeyUpdate(SGenum key, SGbool down)
{
    if(key >= SG_KEY_NUM) return;
    _sg_keyPrev[key] = _sg_keyCurr[key];
    _sg_keyCurr[key] = down;
}
void SG_EXPORT _sgKeyboardCharUpdate(SGdchar chr, SGbool down)
{
    if(chr >= SG_CHAR_NUM) return;
    _sg_charPrev[chr] = _sg_charCurr[chr];
    _sg_charCurr[chr] = down;
}

SGbool SG_EXPORT sgKeyboardKey(SGenum key)
{
    if(key >= SG_KEY_NUM) return SG_FALSE;
    return _sg_keyCurr[key];
}
SGbool SG_EXPORT sgKeyboardKeyPress(SGenum key)
{
    if(key >= SG_KEY_NUM) return SG_FALSE;
    return !_sg_keyPrev[key] && _sg_keyCurr[key];
}
SGbool SG_EXPORT sgKeyboardKeyRelease(SGenum key)
{
    if(key >= SG_KEY_NUM) return SG_FALSE;
    return _sg_keyPrev[key] && !_sg_keyCurr[key];
}

SGbool SG_EXPORT sgKeyboardChar(SGdchar chr)
{
    if(chr >= SG_CHAR_NUM) return SG_FALSE;
    return _sg_charCurr[chr];
}
SGbool SG_EXPORT sgKeyboardCharPress(SGdchar chr)
{
    if(chr >= SG_CHAR_NUM) return SG_FALSE;
    return !_sg_charPrev[chr] && _sg_charCurr[chr];
}
SGbool SG_EXPORT sgKeyboardCharRelease(SGdchar chr)
{
    if(chr >= SG_CHAR_NUM) return SG_FALSE;
    return _sg_charPrev[chr] && !_sg_charCurr[chr];
}
