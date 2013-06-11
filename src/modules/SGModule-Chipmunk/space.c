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

SGenum SG_CALL sgmPhysicsSpaceCreate(void** space)
{
    *space = cpSpaceNew();

    DataExt* data = malloc(sizeof(DataExt));
    data->type = SG_BODY_STATIC;
    data->data = NULL;
    cpBodySetUserData(cpSpaceGetStaticBody(*space), data);

    cpSpaceAddCollisionHandler(*space, 0, 0, cbCollisionBegin, cbCollisionPreSolve, cbCollisionPostSolve, cbCollisionSeparate, NULL);

    return SG_OK;
}

SGenum SG_CALL sgmPhysicsSpaceDestroy(void* space)
{
    if(space == NULL)
        return SG_OK; // SG_INVALID_VALUE

    free(cpBodyGetUserData(cpSpaceGetStaticBody(space)));

    //cpSpaceFreeChildren(space);
    cpSpaceFree(space);
    return SG_OK;
}

SGenum SG_CALL sgmPhysicsSpaceStep(void* space, float time)
{
    if(space == NULL)
        return SG_OK; // SG_INVALID_VALUE

    cpSpaceStep(space, time);
    return SG_OK;
}

SGenum SG_CALL sgmPhysicsSpaceSetIterations(void* space, SGuint iterations)
{
    if(!space)
        return SG_OK; // SG_INVALID_VALUE
    cpSpaceSetIterations(space, iterations);
    return SG_OK;
}
//SGenum SG_CALL sgmPhysicsSpaceGetIterations(void* space, SGuint* iterations, SGuint* eiterations);

SGenum SG_CALL sgmPhysicsSpaceSetGravity(void* space, float x, float y)
{
    if(!space)
        return SG_OK; // SG_INVALID_VALUE
    cpSpaceSetGravity(space, cpv(x, y));
    return SG_OK;
}
//SGenum SG_CALL sgmPhysicsSpaceGetGravity(void* space, float* x, float* y);

SGenum SG_CALL sgmPhysicsSpaceSetDamping(void* space, float damping)
{
    if(!space)
        return SG_OK; // SG_INVALID_VALUE
    cpSpace* cspace = space;
    cspace->damping = damping;
    return SG_OK;
}
//SGenum SG_CALL sgmPhysicsSpaceGetDamping(void* space, float* damping);

SGenum SG_CALL sgmPhysicsSpaceAddShape(void* space, void* shape)
{
    if(space == NULL || shape == NULL)
        return SG_OK; // SG_INVALID_VALUE
    if(((DataExt*)cpBodyGetUserData(cpShapeGetBody(shape)))->type != SG_BODY_STATIC)
        cpSpaceAddShape(space, shape);
    else
        cpSpaceAddStaticShape(space, shape);
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsSpaceRemoveShape(void* space, void* shape)
{
    if(space == NULL || shape == NULL)
        return SG_OK; // SG_INVALID_VALUE
    if(((DataExt*)cpBodyGetUserData(cpShapeGetBody(shape)))->type != SG_BODY_STATIC)
        cpSpaceRemoveShape(space, shape);
    else
        cpSpaceRemoveStaticShape(space, shape);
    return SG_OK;
}
//SGenum SG_CALL sgmPhysicsSpaceAddStaticShape(void* space, void* shape);
//SGenum SG_CALL sgmPhysicsSpaceRemoveStaticShape(void* space, void* shape);
SGenum SG_CALL sgmPhysicsSpaceAddBody(void* space, void* body)
{
    if(space == NULL || body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    if((((DataExt*)cpBodyGetUserData(body))->type != SG_BODY_STATIC) && (((DataExt*)cpBodyGetUserData(body))->type != SG_BODY_SEMISTATIC)) // we shouldn't put the body in, if it's static
        cpSpaceAddBody(space, body);
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsSpaceRemoveBody(void* space, void* body)
{
    if(space == NULL || body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    if((((DataExt*)cpBodyGetUserData(body))->type != SG_BODY_STATIC) && (((DataExt*)cpBodyGetUserData(body))->type != SG_BODY_SEMISTATIC)) // we shouldn't put the body in, if it's static
        cpSpaceRemoveBody(space, body);
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsSpaceAddConstraint(void* space, void* constraint)
{
    if(space == NULL || constraint == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpSpaceAddConstraint(space, constraint);
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsSpaceRemoveConstraint(void* space, void* constraint)
{
    if(space == NULL || constraint == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpSpaceRemoveConstraint(space, constraint);
    return SG_OK;
}

SGenum SG_CALL sgmPhysicsSpaceGetStaticBody(void* space, void** body)
{
    if(!space || !body)
        return SG_OK; // SG_INVALID_VALUE
    *body = cpSpaceGetStaticBody(space);
    return SG_OK;
}
