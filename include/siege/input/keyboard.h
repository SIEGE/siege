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

#ifndef __SIEGE_INPUT_KEYBOARD_H__
#define __SIEGE_INPUT_KEYBOARD_H__
#include "../common.h"
#include "../modules/input.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/// \todo Create and use AList (Associative List) for this
#ifdef SG_BUILD_LIBRARY
SGenum* _sg_keyStatusType;
SGbool* _sg_keyStatusDownPrev;
SGbool* _sg_keyStatusDownCurr;
SGuint _sg_keyStatusLength;
SGenum* _sg_charStatusType;
SGbool* _sg_charStatusDownPrev;
SGbool* _sg_charStatusDownCurr;
SGuint _sg_charStatusLength;

void* _sg_keyHandle;
SGCoreKeyboardCallbacks _sg_keyCallbacks;
#endif // SG_BUILD_LIBRARY

void SG_EXPORT _sg_cbKeyboardKey(void* keyboard, SGuint key, SGbool down);
void SG_EXPORT _sg_cbKeyboardChar(void* keyboard, SGdchar chr, SGbool down);

SGint SG_EXPORT _sgKeyboardInside(SGuint* array, SGuint what, SGuint len);

SGbool SG_EXPORT _sgKeyboardInit(void);
SGbool SG_EXPORT _sgKeyboardDeinit(void);

void SG_EXPORT _sgKeyboardKeyUpdate(SGenum key, SGbool down);
void SG_EXPORT _sgKeyboardCharUpdate(SGdchar chr, SGbool down);

SGbool SG_EXPORT sgKeyboardKey(SGenum key);
SGbool SG_EXPORT sgKeyboardKeyPress(SGenum key);
SGbool SG_EXPORT sgKeyboardKeyRelease(SGenum key);

SGbool SG_EXPORT sgKeyboardChar(SGdchar chr);
SGbool SG_EXPORT sgKeyboardCharPress(SGdchar chr);
SGbool SG_EXPORT sgKeyboardCharRelease(SGdchar chr);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_INPUT_KEYBOARD_H__
