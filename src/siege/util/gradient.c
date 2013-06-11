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

#define SG_BUILD_LIBRARY
#include <siege/util/gradient.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>

SGVec2* SG_CALL _sgGradientFindMin(SGGradient* grad, float val)
{
    size_t i;
    for(i = 0; i < grad->numvals; i++)
    {
        if(grad->vals[i].x == val)
            return &grad->vals[i];
        else if(grad->vals[i].x > val)
            return (i != 0) ? &grad->vals[i - 1] : NULL;
    }
    return NULL;
}

float SG_CALL _sgGradientInterpNearest(SGGradient* grad, float x)
{
    SGVec2* min = _sgGradientFindMin(grad, x);
    if(!min) // not found - first element...
        return grad->vals[0].y;
    if(min == &grad->vals[grad->numvals - 1]) // last element...
        return grad->vals[grad->numvals - 1].y;

    SGVec2* max = min + 1;

    float t = (x - min->x) / (max->x - min->x);

    return (t < 0.5) ? min->y : max->y;
}
float SG_CALL _sgGradientInterpLinear(SGGradient* grad, float x)
{
    SGVec2* min = _sgGradientFindMin(grad, x);
    if(!min) // not found - first element...
        return grad->vals[0].y;
    if(min == &grad->vals[grad->numvals - 1]) // last element...
        return grad->vals[grad->numvals - 1].y;

    SGVec2* max = min + 1;

    float t = (x - min->x) / (max->x - min->x);

    return min->y + t * (max->y - min->y);
}
float SG_CALL _sgGradientInterpCosine(SGGradient* grad, float x)
{
    SGVec2* min = _sgGradientFindMin(grad, x);
    if(!min) // not found - first element...
        return grad->vals[0].y;
    if(min == &grad->vals[grad->numvals - 1]) // last element...
        return grad->vals[grad->numvals - 1].y;

    SGVec2* max = min + 1;

    float t = (x - min->x) / (max->x - min->x);

    float f = (1.0 - cos(t * SG_PI)) * 0.5;

    return min->y + f * (max->y - min->y);
}
float SG_CALL _sgGradientInterpCubic(SGGradient* grad, float x)
{
    SGVec2* min = _sgGradientFindMin(grad, x);
    if(!min) // not found - first element...
        return grad->vals[0].y;
    if(min == &grad->vals[grad->numvals - 1]) // last element...
        return grad->vals[grad->numvals - 1].y;

    SGVec2* max = min + 1;

    SGVec2* premin = (min != &grad->vals[0]) ? min - 1 : min;
    SGVec2* postmax = (max != &grad->vals[grad->numvals - 1]) ? max + 1 : max;

    float t = (x - min->x) / (max->x - min->x);

    float p = (postmax->y - max->y) - (premin->y - min->y);
    float q = (premin->y - min->y) - p;
    float r = max->y - premin->y;
    float s = min->y;

    return p*t*t*t + q*t*t + r*t + s;
}

SGGradient* SG_CALL sgGradientCreate(void)
{
    SGGradient* grad = malloc(sizeof(SGGradient));
    if(!grad)
        return NULL;
    grad->numvals = 2;
    grad->vals = malloc(grad->numvals * sizeof(SGVec2));
    grad->vals[0] = sgVec2f(0.0, 0.0);
    grad->vals[1] = sgVec2f(1.0, 1.0);
    grad->interp = _sgGradientInterpLinear;
    return grad;
}
void SG_CALL sgGradientDestroy(SGGradient* grad)
{
    if(!grad)
        return;
    free(grad->vals);
    free(grad);
}

void SG_CALL sgGradientSetInterp(SGGradient* grad, SGenum interp)
{
    switch(interp)
    {
        case SG_GRADIENT_INTERP_NEAREST:
            grad->interp = _sgGradientInterpNearest;
            break;
        case SG_GRADIENT_INTERP_LINEAR:
            grad->interp = _sgGradientInterpLinear;
            break;
        case SG_GRADIENT_INTERP_COSINE:
            grad->interp = _sgGradientInterpCosine;
            break;
        case SG_GRADIENT_INTERP_CUBIC:
            grad->interp = _sgGradientInterpCubic;
            break;
        default:
            break;
    }
}
void SG_CALL sgGradientSetInterpFunc(SGGradient* grad, SGGradientInterp* interp)
{
    if(!interp)
        interp = _sgGradientInterpLinear;
    grad->interp = interp;
}

void SG_CALL sgGradientSetStopIndex(SGGradient* grad, size_t i, float y)
{
    if(i >= grad->numvals)
        return;
    grad->vals[i].y = y;
}
void SG_CALL sgGradientSetStopKey(SGGradient* grad, float x, float y)
{
    size_t i;
    SGVec2* v = _sgGradientFindMin(grad, x);
    if(v)
    {
        if(v->x == x) // we replace the stop
            v->y = y;
        else
        {
            i = v - grad->vals + 1;

            grad->numvals++;
            grad->vals = realloc(grad->vals, grad->numvals * sizeof(SGVec2));
            memmove(&grad->vals[i + 1], &grad->vals[i], (grad->numvals - i - 1) * sizeof(SGVec2));
            grad->vals[i] = sgVec2f(x, y);
        }
    }
    else // v not found, we insert at the start
    {
        grad->numvals++;
        grad->vals = realloc(grad->vals, grad->numvals * sizeof(SGVec2));
        memmove(&grad->vals[1], &grad->vals[0], (grad->numvals - 1) * sizeof(SGVec2));
        grad->vals[0] = sgVec2f(x, y);
    }
}

void SG_CALL sgGradientRemoveStopIndex(SGGradient* grad, size_t i)
{
    if(i >= grad->numvals)
        return;
    memmove(&grad->vals[i], &grad->vals[i + 1], (grad->numvals - i - 1) * sizeof(SGVec2));
    grad->numvals--;
    grad->vals = realloc(grad->vals, grad->numvals * sizeof(SGVec2));
}
void SG_CALL sgGradientRemoveStopKey(SGGradient* grad, float x)
{
    SGVec2* v = _sgGradientFindMin(grad, x);
    if(v && v->x == x)
        sgGradientRemoveStopIndex(grad, v - grad->vals);
}

float SG_CALL sgGradientGetValue(SGGradient* grad, float x)
{
    return grad->interp(grad, x);
}
