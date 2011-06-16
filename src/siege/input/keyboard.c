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

void SG_EXPORT _sg_cbKeyboardKey(void* keyboard, SGenum key, SGbool down)
{
    _sgKeyboardKeyUpdate(key, down);
    SGbool pressed = sgKeyboardKeyPress(key);

    SGenum second;
    if(pressed)
        second = SG_EVF_KEYKEYP;
    else if(!down)
        second = SG_EVF_KEYKEYR;
    else
        second = SG_EVF_KEYKEYA;

    sgEventCall(SG_EV_INTERNAL, (SGuint)2, (SGenum)SG_EVF_KEYKEYH, key, second, key);
}
void SG_EXPORT _sg_cbKeyboardChar(void* keyboard, SGdchar chr, SGbool down)
{
    _sgKeyboardCharUpdate(chr, down);
    SGbool pressed = sgKeyboardCharPress(chr);

    SGenum type = 0;
    if(pressed)
        type = SG_EVF_KEYCHARP;
    else if(down)
        type = SG_EVF_KEYCHARA;
    if(type == 0)
        return;

    sgEventCall(SG_EV_INTERNAL, (SGuint)1, type, chr);
}

SGint SG_EXPORT _sgKeyboardInside(SGenum* array, SGenum what, SGuint len)
{
    SGuint i;
    for(i = 0; i < len; i++)
        if(array[i] == what)
            return i;
    return -1;
}

SGbool SG_EXPORT _sgKeyboardInit(void)
{
    _sg_keyStatusType = NULL;
    _sg_keyStatusDownPrev = NULL;
    _sg_keyStatusDownCurr = NULL;
    _sg_keyStatusLength = 0;
    _sg_charStatusType = NULL;
    _sg_charStatusDownPrev = NULL;
    _sg_charStatusDownCurr = NULL;
    _sg_charStatusLength = 0;

    _sg_keyCallbacks.key = _sg_cbKeyboardKey;
    _sg_keyCallbacks.chr = _sg_cbKeyboardChar;

    if(sgmCoreKeyboardCreate != NULL)
        sgmCoreKeyboardCreate(&_sg_keyHandle, _sg_winHandle);
    if(sgmCoreKeyboardSetCallbacks != NULL)
        sgmCoreKeyboardSetCallbacks(_sg_keyHandle, &_sg_keyCallbacks);
    return SG_TRUE;
}
SGbool SG_EXPORT _sgKeyboardDeinit(void)
{
    free(_sg_keyStatusType);
    free(_sg_keyStatusDownPrev);
    free(_sg_keyStatusDownCurr);
    _sg_keyStatusLength = 0;
    free(_sg_charStatusType);
    free(_sg_charStatusDownPrev);
    free(_sg_charStatusDownCurr);
    _sg_charStatusLength = 0;

    if(sgmCoreKeyboardDestroy != NULL)
        sgmCoreKeyboardDestroy(_sg_keyHandle);
    return SG_TRUE;
}

void SG_EXPORT _sgKeyboardKeyUpdate(SGenum key, SGbool down)
{
    SGint i = _sgKeyboardInside(_sg_keyStatusType, key, _sg_keyStatusLength);
    if(i == -1)
    {
        i = _sg_keyStatusLength;
        _sg_keyStatusLength++;
        _sg_keyStatusType = realloc(_sg_keyStatusType, _sg_keyStatusLength * sizeof(SGenum));
        _sg_keyStatusDownPrev = realloc(_sg_keyStatusDownPrev, _sg_keyStatusLength * sizeof(SGbool));
        _sg_keyStatusDownCurr = realloc(_sg_keyStatusDownCurr, _sg_keyStatusLength * sizeof(SGbool));
        _sg_keyStatusType[i] = key;
        _sg_keyStatusDownCurr[i] = !down;
    }
    _sg_keyStatusDownPrev[i] = _sg_keyStatusDownCurr[i];
    _sg_keyStatusDownCurr[i] = down;
}
void SG_EXPORT _sgKeyboardCharUpdate(SGdchar chr, SGbool down)
{
    SGint i = _sgKeyboardInside(_sg_charStatusType, chr, _sg_charStatusLength);
    if(i == -1)
    {
        i = _sg_charStatusLength;
        _sg_charStatusLength++;
        _sg_charStatusType = realloc(_sg_charStatusType, _sg_charStatusLength * sizeof(SGenum));
        _sg_charStatusDownPrev = realloc(_sg_charStatusDownPrev, _sg_charStatusLength * sizeof(SGbool));
        _sg_charStatusDownCurr = realloc(_sg_charStatusDownCurr, _sg_charStatusLength * sizeof(SGbool));
        _sg_charStatusType[i] = chr;
        _sg_charStatusDownCurr[i] = !down;
    }
    _sg_charStatusDownPrev[i] = _sg_charStatusDownCurr[i];
    _sg_charStatusDownCurr[i] = down;
}

SGbool SG_EXPORT sgKeyboardKey(SGenum key)
{
    SGint i = _sgKeyboardInside(_sg_keyStatusType, key, _sg_keyStatusLength);
    if(i == -1)
        return SG_FALSE;
    return _sg_keyStatusDownCurr[i];
}
SGbool SG_EXPORT sgKeyboardKeyPress(SGenum key)
{
    SGint i = _sgKeyboardInside(_sg_keyStatusType, key, _sg_keyStatusLength);
    if(i == -1)
        return SG_FALSE;
    return !_sg_keyStatusDownPrev[i] && _sg_keyStatusDownCurr[i];
}
SGbool SG_EXPORT sgKeyboardKeyRelease(SGenum key)
{
    SGint i = _sgKeyboardInside(_sg_keyStatusType, key, _sg_keyStatusLength);
    if(i == -1)
        return SG_FALSE;
    return _sg_keyStatusDownPrev[i] && !_sg_keyStatusDownCurr[i];
}

SGbool SG_EXPORT sgKeyboardChar(SGdchar chr)
{
    SGint i = _sgKeyboardInside(_sg_charStatusType, chr, _sg_charStatusLength);
    if(i == -1)
        return SG_FALSE;
    return _sg_charStatusDownCurr[i];
}
SGbool SG_EXPORT sgKeyboardCharPress(SGdchar chr)
{
    SGint i = _sgKeyboardInside(_sg_charStatusType, chr, _sg_charStatusLength);
    if(i == -1)
        return SG_FALSE;
    return !_sg_charStatusDownPrev[i] && _sg_charStatusDownCurr[i];
}
SGbool SG_EXPORT sgKeyboardCharRelease(SGdchar chr)
{
    SGint i = _sgKeyboardInside(_sg_charStatusType, chr, _sg_charStatusLength);
    if(i == -1)
        return SG_FALSE;
    return _sg_charStatusDownPrev[i] && !_sg_charStatusDownCurr[i];
}
