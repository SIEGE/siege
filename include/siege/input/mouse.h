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
#include "../common.h"
#include "../util/vector.h"
#include "../util/ivector.h"

/**
 * \name Mouse buttons
 */
/// @{
#define SG_MOUSE_BUTTON_LEFT   1
#define SG_MOUSE_BUTTON_RIGHT  2
#define SG_MOUSE_BUTTON_MIDDLE 3
/// @}

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

void SG_CALL _sg_cbMouseButton(SGuint button, SGbool action);
void SG_CALL _sg_cbMouseMove(SGint x, SGint y);
void SG_CALL _sg_cbMouseWheel(SGint dw);

void SG_CALL _sgMouseUpdate(void);

SGbool SG_CALL _sgMouseInit(void);
SGbool SG_CALL _sgMouseDeinit(void);

void SG_CALL sgMouseMove(SGint x, SGint y);

void SG_CALL sgMouseSetVisible(SGbool vis);
void SG_CALL sgMouseShow(void);
void SG_CALL sgMouseHide(void);

SGIVec2 SG_CALL sgMouseGetPosPrev2iv(void);
SGVec2 SG_CALL sgMouseGetPosPrev2fv(void);
SGint SG_CALL sgMouseGetPosPrevX(void);
SGint SG_CALL sgMouseGetPosPrevY(void);

SGIVec2 SG_CALL sgMouseGetPos2iv(void);
SGVec2 SG_CALL sgMouseGetPos2fv(void);
SGint SG_CALL sgMouseGetPosX(void);
SGint SG_CALL sgMouseGetPosY(void);

SGint SG_CALL sgMouseGetWheelPrev(void);
SGint SG_CALL sgMouseGetWheel(void);

SGbool SG_CALL sgMouseGetButtonPrev(SGuint button);
SGbool SG_CALL sgMouseGetButton(SGuint button);
SGbool SG_CALL sgMouseGetButtonPress(SGuint button);
SGbool SG_CALL sgMouseGetButtonRelease(SGuint button);

SGbool SG_CALL sgMouseGetButtonLeftPrev(void);
SGbool SG_CALL sgMouseGetButtonLeft(void);
SGbool SG_CALL sgMouseGetButtonLeftPress(void);
SGbool SG_CALL sgMouseGetButtonLeftRelease(void);

SGbool SG_CALL sgMouseGetButtonRightPrev(void);
SGbool SG_CALL sgMouseGetButtonRight(void);
SGbool SG_CALL sgMouseGetButtonRightPress(void);
SGbool SG_CALL sgMouseGetButtonRightRelease(void);

SGbool SG_CALL sgMouseGetButtonMiddlePrev(void);
SGbool SG_CALL sgMouseGetButtonMiddle(void);
SGbool SG_CALL sgMouseGetButtonMiddlePress(void);
SGbool SG_CALL sgMouseGetButtonMiddleRelease(void);

void SG_CALL SG_HINT_DEPRECATED sgMouseGetPosPrev(SGint* x, SGint* y);
void SG_CALL SG_HINT_DEPRECATED sgMouseGetPos(SGint* x, SGint* y);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_INPUT_MOUSE_H__
