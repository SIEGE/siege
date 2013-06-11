/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "COPYING.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#ifndef __SIEGE_UTIL_GRADIENT_H__
#define __SIEGE_UTIL_GRADIENT_H__

#include "../common.h"
#include "vector.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#define SG_GRADIENT_INTERP_NEAREST 0
#define SG_GRADIENT_INTERP_LINEAR  1
#define SG_GRADIENT_INTERP_COSINE  2
#define SG_GRADIENT_INTERP_CUBIC   3

struct SGGradient;

typedef float SG_CALL (SGGradientInterp)(struct SGGradient* grad, float x);

typedef struct SGGradient
{
    size_t numvals;
    SGVec2* vals;
    SGGradientInterp* interp;
} SGGradient;

/*#ifdef SG_BUILD_LIBRARY
#endif // SG_BUILD_LIBRARY*/

SGVec2* SG_CALL _sgGradientFindMin(SGGradient* grad, float val);

float SG_CALL _sgGradientInterpNearest(SGGradient* grad, float x);
float SG_CALL _sgGradientInterpLinear(SGGradient* grad, float x);
float SG_CALL _sgGradientInterpCosine(SGGradient* grad, float x);
float SG_CALL _sgGradientInterpCubic(SGGradient* grad, float x);

SGGradient* SG_CALL sgGradientCreate(void);
void SG_CALL sgGradientDestroy(SGGradient* grad);

void SG_CALL sgGradientSetInterp(SGGradient* grad, SGenum interp);
void SG_CALL sgGradientSetInterpFunc(SGGradient* grad, SGGradientInterp* interp);

void SG_CALL sgGradientSetStopIndex(SGGradient* grad, size_t i, float y);
void SG_CALL sgGradientSetStopKey(SGGradient* grad, float x, float y);

void SG_CALL sgGradientRemoveStopIndex(SGGradient* grad, size_t i);
void SG_CALL sgGradientRemoveStopKey(SGGradient* grad, float x);

float SG_CALL sgGradientGetValue(SGGradient* grad, float x);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_GRADIENT_H__
