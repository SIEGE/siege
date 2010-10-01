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

#ifndef __SIEGE_INPUT_MOUSE_H__
#define __SIEGE_INPUT_MOUSE_H__

#include "../modules/input.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#ifdef SG_BUILD_LIBRARY
SGbool* _sg_mouseButtonPrev;
SGbool* _sg_mouseButtonCurr;
SGuint _sg_mouseButtonNum;
SGint _sg_mouseXPrev;
SGint _sg_mouseYPrev;
SGint _sg_mouseX;
SGint _sg_mouseY;
SGint _sg_mouseWheelPrev;
SGint _sg_mouseWheel;

void* _sg_mouseHandle;
SGCoreMouseCallbacks _sg_mouseCallbacks;
#endif // SG_BUILD_LIBRARY

void SG_EXPORT _sg_cbMouseButton(void* mouse, SGuint button, SGbool action);
void SG_EXPORT _sg_cbMouseMove(void* mouse, SGint x, SGint y);
void SG_EXPORT _sg_cbMouseWheel(void* mouse, SGint w);

SGbool SG_EXPORT _sgMouseInit(void);
SGbool SG_EXPORT _sgMouseDeinit(void);

void SG_EXPORT sgMouseGetPosPrev(SGint* x, SGint* y);
SGint SG_EXPORT sgMouseGetPosPrevX(void);
SGint SG_EXPORT sgMouseGetPosPrevY(void);

void SG_EXPORT sgMouseGetPos(SGint* x, SGint* y);
SGint SG_EXPORT sgMouseGetPosX(void);
SGint SG_EXPORT sgMouseGetPosY(void);

SGint SG_EXPORT sgMouseGetWheelPrev(void);
SGint SG_EXPORT sgMouseGetWheel(void);

SGbool SG_EXPORT sgMouseGetButtonPrev(SGuint button);
SGbool SG_EXPORT sgMouseGetButton(SGuint button);
SGbool SG_EXPORT sgMouseGetButtonPress(SGuint button);
SGbool SG_EXPORT sgMouseGetButtonRelease(SGuint button);

SGbool SG_EXPORT sgMouseGetButtonLeftPrev(void);
SGbool SG_EXPORT sgMouseGetButtonLeft(void);
SGbool SG_EXPORT sgMouseGetButtonLeftPress(void);
SGbool SG_EXPORT sgMouseGetButtonLeftRelease(void);

SGbool SG_EXPORT sgMouseGetButtonRightPrev(void);
SGbool SG_EXPORT sgMouseGetButtonRight(void);
SGbool SG_EXPORT sgMouseGetButtonRightPress(void);
SGbool SG_EXPORT sgMouseGetButtonRightRelease(void);

SGbool SG_EXPORT sgMouseGetButtonMiddlePrev(void);
SGbool SG_EXPORT sgMouseGetButtonMiddle(void);
SGbool SG_EXPORT sgMouseGetButtonMiddlePress(void);
SGbool SG_EXPORT sgMouseGetButtonMiddleRelease(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_INPUT_MOUSE_H__
