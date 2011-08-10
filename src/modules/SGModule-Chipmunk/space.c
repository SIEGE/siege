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

#include "main.h"
#include "space.h"
#include "collision.h"

#include <stdio.h>
#include <stdlib.h>

SGuint SG_EXPORT sgmPhysicsSpaceCreate(void** space)
{
    *space = cpSpaceNew();

    DataExt* data = malloc(sizeof(DataExt));
    data->type = SG_PHYSICS_BODY_STATIC;
    data->data = NULL;
    cpBodySetUserData(cpSpaceGetStaticBody(*space), data);

    cpSpaceAddCollisionHandler(*space, 0, 0, cbCollisionBegin, cbCollisionPreSolve, cbCollisionPostSolve, cbCollisionSeparate, NULL);

    return SG_OK;
}

SGuint SG_EXPORT sgmPhysicsSpaceDestroy(void* space)
{
    if(space == NULL)
        return SG_OK; // SG_INVALID_VALUE

	free(cpBodyGetUserData(cpSpaceGetStaticBody(space)));

    //cpSpaceFreeChildren(space);
    cpSpaceFree(space);
    return SG_OK;
}

SGuint SG_EXPORT sgmPhysicsSpaceStep(void* space, float time)
{
    if(space == NULL)
        return SG_OK; // SG_INVALID_VALUE

    cpSpaceStep(space, time);
    return SG_OK;
}

SGenum SG_EXPORT sgmPhysicsSpaceSetIterations(void* space, SGuint iterations)
{
	if(!space)
		return SG_OK; // SG_INVALID_VALUE
	cpSpaceSetIterations(space, iterations);
	return SG_OK;
}
//SGenum SG_EXPORT sgmPhysicsSpaceGetIterations(void* space, SGuint* iterations, SGuint* eiterations);

SGuint SG_EXPORT sgmPhysicsSpaceSetGravity(void* space, float x, float y)
{
    if(!space)
        return SG_OK; // SG_INVALID_VALUE
    cpSpaceSetGravity(space, cpv(x, y));
    return SG_OK;
}
//SGuint SG_EXPORT sgmPhysicsSpaceGetGravity(void* space, float* x, float* y);

SGenum SG_EXPORT sgmPhysicsSpaceSetDamping(void* space, float damping)
{
	if(!space)
		return SG_OK; // SG_INVALID_VALUE
	cpSpace* cspace = space;
	cspace->damping = damping;
	return SG_OK;
}
//SGenum SG_EXPORT sgmPhysicsSpaceGetDamping(void* space, float* damping);

SGuint SG_EXPORT sgmPhysicsSpaceAddShape(void* space, void* shape)
{
    if(space == NULL || shape == NULL)
        return SG_OK; // SG_INVALID_VALUE
    if(((DataExt*)cpBodyGetUserData(cpShapeGetBody(shape)))->type != SG_PHYSICS_BODY_STATIC)
        cpSpaceAddShape(space, shape);
    else
        cpSpaceAddStaticShape(space, shape);
    return SG_OK;
}
SGuint SG_EXPORT sgmPhysicsSpaceRemoveShape(void* space, void* shape)
{
    if(space == NULL || shape == NULL)
        return SG_OK; // SG_INVALID_VALUE
    if(((DataExt*)cpBodyGetUserData(cpShapeGetBody(shape)))->type != SG_PHYSICS_BODY_STATIC)
        cpSpaceRemoveShape(space, shape);
    else
        cpSpaceRemoveStaticShape(space, shape);
    return SG_OK;
}
//SGuint SG_EXPORT sgmPhysicsSpaceAddStaticShape(void* space, void* shape);
//SGuint SG_EXPORT sgmPhysicsSpaceRemoveStaticShape(void* space, void* shape);
SGuint SG_EXPORT sgmPhysicsSpaceAddBody(void* space, void* body)
{
    if(space == NULL || body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    if((((DataExt*)cpBodyGetUserData(body))->type != SG_PHYSICS_BODY_STATIC) && (((DataExt*)cpBodyGetUserData(body))->type != SG_PHYSICS_BODY_SEMISTATIC)) // we shouldn't put the body in, if it's static
        cpSpaceAddBody(space, body);
    return SG_OK;
}
SGuint SG_EXPORT sgmPhysicsSpaceRemoveBody(void* space, void* body)
{
    if(space == NULL || body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    if((((DataExt*)cpBodyGetUserData(body))->type != SG_PHYSICS_BODY_STATIC) && (((DataExt*)cpBodyGetUserData(body))->type != SG_PHYSICS_BODY_SEMISTATIC)) // we shouldn't put the body in, if it's static
        cpSpaceRemoveBody(space, body);
    return SG_OK;
}
SGuint SG_EXPORT sgmPhysicsSpaceAddConstraint(void* space, void* constraint)
{
    if(space == NULL || constraint == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpSpaceAddConstraint(space, constraint);
    return SG_OK;
}
SGuint SG_EXPORT sgmPhysicsSpaceRemoveConstraint(void* space, void* constraint)
{
    if(space == NULL || constraint == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpSpaceRemoveConstraint(space, constraint);
    return SG_OK;
}

SGenum SG_EXPORT sgmPhysicsSpaceGetStaticBody(void* space, void** body)
{
	if(!space || !body)
		return SG_OK; // SG_INVALID_VALUE
	*body = cpSpaceGetStaticBody(space);
	return SG_OK;
}
