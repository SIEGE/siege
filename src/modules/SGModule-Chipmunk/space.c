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
    cpSpace** cspace = (cpSpace**)space;
    (*cspace)->iterations = 10; // TEST
    (*cspace)->elasticIterations = 10;
    (*cspace)->damping = 0.75;

    (*cspace)->staticBody.data = malloc(sizeof(DataExt));
    ((DataExt*)(*cspace)->staticBody.data)->type = SG_PHYSICS_BODY_STATIC;
    ((DataExt*)(*cspace)->staticBody.data)->data = NULL;

    cpSpaceAddCollisionHandler(*cspace, 0, 0, cbCollisionBegin, cbCollisionPreSolve, cbCollisionPostSolve, cbCollisionSeparate, NULL);

    return SG_OK;
}

SGuint SG_EXPORT sgmPhysicsSpaceDestroy(void* space)
{
    if(space == NULL)
        return SG_OK; // SG_INVALID_VALUE
	cpSpace* cspace = space;

	free(cspace->staticBody.data);

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

SGenum SG_EXPORT sgmPhysicsSpaceSetIterations(void* space, SGuint iterations, SGuint eiterations)
{
	if(!space)
		return SG_OK; // SG_INVALID_VALUE
	cpSpace* cspace = space;
	cspace->iterations = iterations;
	cspace->elasticIterations = eiterations;
	return SG_OK;
}
//SGenum SG_EXPORT sgmPhysicsSpaceGetIterations(void* space, SGuint* iterations, SGuint* eiterations);

SGuint SG_EXPORT sgmPhysicsSpaceSetGravity(void* space, float x, float y)
{
    if(!space)
        return SG_OK; // SG_INVALID_VALUE
    cpSpace* cspace = space;
    cspace->gravity.x = x;
    cspace->gravity.y = y;
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
    cpShape* cshape = shape;
    cpBody* cbody = cshape->body;
    if(((DataExt*)cbody->data)->type != SG_PHYSICS_BODY_STATIC)
        cpSpaceAddShape(space, shape);
    else
        cpSpaceAddStaticShape(space, shape);
    return SG_OK;
}
SGuint SG_EXPORT sgmPhysicsSpaceRemoveShape(void* space, void* shape)
{
    if(space == NULL || shape == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpShape* cshape = shape;
    cpBody* cbody = cshape->body;
    if(((DataExt*)cbody->data)->type != SG_PHYSICS_BODY_STATIC)
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
    cpBody* cbody = body;
    if((((DataExt*)cbody->data)->type != SG_PHYSICS_BODY_STATIC) && (((DataExt*)cbody->data)->type != SG_PHYSICS_BODY_SEMISTATIC)) // we shouldn't put the body in, if it's static
        cpSpaceAddBody(space, body);
    return SG_OK;
}
SGuint SG_EXPORT sgmPhysicsSpaceRemoveBody(void* space, void* body)
{
    if(space == NULL || body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpBody* cbody = body;
    if((((DataExt*)cbody->data)->type != SG_PHYSICS_BODY_STATIC) && (((DataExt*)cbody->data)->type != SG_PHYSICS_BODY_SEMISTATIC)) // we shouldn't put the body in, if it's static
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

SGenum SG_EXPORT sgmPhysicsSpaceRehash(void* space)
{
	if(!space)
		return SG_OK; // SG_INVALID_VALUE
	cpSpaceRehashStatic(space);
	return SG_OK;
}

SGenum SG_EXPORT sgmPhysicsSpaceGetStaticBody(void* space, void** body)
{
	if(!space || !body)
		return SG_OK; // SG_INVALID_VALUE
	cpSpace* cspace = space;
	*body = &cspace->staticBody;
	return SG_OK;
}
