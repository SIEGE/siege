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

#include "common.h"
#include "collision.h"

#include <stdio.h>
#include <stdlib.h>

int cbCollisionBegin(cpArbiter* arb, cpSpace* space, void* data)
{
    cpShape* one;
    cpShape* two;
    if(colCallbacks && colCallbacks->begin)
    {
        cpArbiterGetShapes(arb, &one, &two);
        colCallbacks->begin(one, two, arb);
    }
    return 1;
}
int cbCollisionPreSolve(cpArbiter* arb, cpSpace* space, void* data)
{
    cpShape* one;
    cpShape* two;
    if(colCallbacks && colCallbacks->step)
    {
        cpArbiterGetShapes(arb, &one, &two);
        colCallbacks->step(one, two, arb);
    }
    return 1;
}
void cbCollisionPostSolve(cpArbiter* arb, cpSpace* space, void* data)
{
    cpShape* one;
    cpShape* two;
    if(colCallbacks && colCallbacks->post)
    {
        cpArbiterGetShapes(arb, &one, &two);
        colCallbacks->post(one, two, arb);
    }
}
void cbCollisionSeparate(cpArbiter* arb, cpSpace* space, void* data)
{
    cpShape* one;
    cpShape* two;
    if(colCallbacks && colCallbacks->end)
    {
        cpArbiterGetShapes(arb, &one, &two);
        colCallbacks->end(one, two, arb);
    }
}

SGenum SG_CALL sgmPhysicsCollisionIgnore(void* handle)
{
    cpArbiterIgnore(handle);
    return SG_OK;
}

SGenum SG_CALL sgmPhysicsCollisionGetNumContacts(void* handle, size_t* numcontacts)
{
    *numcontacts = cpArbiterGetCount(handle);
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsCollisionGetPoint(void* handle, size_t index, float* x, float* y)
{
    cpVect v = cpArbiterGetPoint(handle, index);
    *x = v.x;
    *y = v.y;
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsCollisionGetNormal(void* handle, size_t index, float* x, float* y)
{
    cpVect v = cpArbiterGetNormal(handle, index);
    *x = v.x;
    *y = v.y;
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsCollisionGetDistance(void* handle, size_t index, float* distance)
{
    *distance = cpArbiterGetDepth(handle, index);
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsCollisionGetImpulse(void* handle, float* x, float* y, SGbool friction)
{
    cpVect v;
    if(friction)
        v = cpArbiterTotalImpulseWithFriction(handle);
    else
        v = cpArbiterTotalImpulse(handle);
    *x = v.x;
    *y = v.y;
    return SG_OK;
}

SGenum SG_CALL sgmPhysicsCollisionSetCallbacks(SGPhysicsCollisionCallbacks* callbacks)
{
    colCallbacks = callbacks;
    return SG_OK;
}
