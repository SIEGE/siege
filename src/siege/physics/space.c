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
#include <siege/physics/space.h>
#include <siege/physics/shape.h>
#include <siege/physics/body.h>
#include <siege/physics/constraint.h>
#include <siege/physics/collision.h>

#include <stdlib.h>

#include "../internal/chipmunk.h"

#ifdef SG_USE_PHYSICS
static cpBool cbCollisionBegin(cpArbiter* arb, cpSpace* space, void* data)
{
    cpShape* one;
    cpShape* two;
    cpArbiterGetShapes(arb, &one, &two);
    _sg_cbPhysicsCollisionBegin(cpShapeGetUserData(one), cpShapeGetUserData(two), arb);
    return cpTrue;
}
static cpBool cbCollisionPreSolve(cpArbiter* arb, cpSpace* space, void* data)
{
    cpShape* one;
    cpShape* two;
    cpArbiterGetShapes(arb, &one, &two);
    _sg_cbPhysicsCollisionPreSolve(cpShapeGetUserData(one), cpShapeGetUserData(two), arb);
    return cpTrue;
}
static void cbCollisionPostSolve(cpArbiter* arb, cpSpace* space, void* data)
{
    cpShape* one;
    cpShape* two;
    cpArbiterGetShapes(arb, &one, &two);
    _sg_cbPhysicsCollisionPostSolve(cpShapeGetUserData(one), cpShapeGetUserData(two), arb);
}
static void cbCollisionSeparate(cpArbiter* arb, cpSpace* space, void* data)
{
    cpShape* one;
    cpShape* two;
    cpArbiterGetShapes(arb, &one, &two);
    _sg_cbPhysicsCollisionSeparate(cpShapeGetUserData(one), cpShapeGetUserData(two), arb);
}

SGbool SG_CALL _sgPhysicsSpaceInit(void)
{
    _sg_physSpaceMain = sgPhysicsSpaceCreate();
    sgPhysicsSpaceSetGravity(_sg_physSpaceMain, 0, 10);
    return SG_TRUE;
}
SGbool SG_CALL _sgPhysicsSpaceDeinit(void)
{
    sgPhysicsSpaceDestroy(_sg_physSpaceMain);
    return SG_TRUE;
}

SGPhysicsSpace* SG_CALL sgPhysicsSpaceCreate(void)
{
    SGPhysicsSpace* space = malloc(sizeof(SGPhysicsSpace));
    if(!space)
        return NULL;
    space->handle = cpSpaceNew();

    space->sbody = malloc(sizeof(SGPhysicsBody));
    space->sbody->handle = cpSpaceGetStaticBody(space->handle);
    space->sbody->space = space;
    space->sbody->data = NULL;
    space->sbody->type = SG_BODY_STATIC;
    space->sbody->entity = NULL;
    cpBodySetUserData(space->sbody->handle, space->sbody);

    // TODO: Add this later, perhaps? (once a body is attached)
    cpSpaceAddCollisionHandler(space->handle, 0, 0, cbCollisionBegin, cbCollisionPreSolve, cbCollisionPostSolve, cbCollisionSeparate, NULL);

    sgPhysicsSpaceSetGravity(space, 0.0, 0.0);

    return space;
}
void SG_CALL sgPhysicsSpaceDestroy(SGPhysicsSpace* space)
{
    if(!space) return;

    cpSpaceFree(space->handle);
    free(space->sbody);
    free(space);
}

void SG_CALL sgPhysicsSpaceStep(SGPhysicsSpace* space, float time)
{
    cpSpaceStep(space->handle, time);
}

void SG_CALL sgPhysicsSpaceSetIterations(SGPhysicsSpace* space, SGuint iterations)
{
    cpSpaceSetIterations(space->handle, iterations);
}
// SGuint SG_CALL sgPhysicsSpaceGetIterations(SGPhysicsSpace* space);
void SG_CALL sgPhysicsSpaceSetGravity(SGPhysicsSpace* space, float x, float y)
{
    cpSpaceSetGravity(space->handle, cpv(x, y));
}
//void SG_CALL sgPhysicsSpaceGetGravity(SGPhysicsSpace* space, float* x, float* y);
void SG_CALL sgPhysicsSpaceSetDamping(SGPhysicsSpace* space, float damping)
{
    cpSpaceSetDamping(space->handle, damping);
}
//float SG_CALL sgPhysicsSpaceGetDamping(SGPhysicsSpace* space);

void SG_CALL sgPhysicsSpaceSetData(SGPhysicsSpace* space, void* data)
{
    space->data = data;
}
void* SG_CALL sgPhysicsSpaceGetData(SGPhysicsSpace* space)
{
    return space->data;
}

SGPhysicsBody* SG_CALL sgPhysicsSpaceGetStaticBody(SGPhysicsSpace* space)
{
    return space->sbody;
}
SGPhysicsSpace* SG_CALL sgPhysicsSpaceGetDefault(void)
{
    return _sg_physSpaceMain;
}

void SG_CALL _sgPhysicsSpaceAddShape(SGPhysicsSpace* space, SGPhysicsShape* shape)
{
    if(shape->body->type != SG_BODY_STATIC)
        cpSpaceAddShape(space->handle, shape->handle);
    else
        cpSpaceAddStaticShape(space->handle, shape->handle);
}
void SG_CALL _sgPhysicsSpaceRemoveShape(SGPhysicsSpace* space, SGPhysicsShape* shape)
{
    if(shape->body->type != SG_BODY_STATIC)
        cpSpaceRemoveShape(space->handle, shape->handle);
    else
        cpSpaceRemoveStaticShape(space->handle, shape->handle);
}

void SG_CALL _sgPhysicsSpaceAddBody(SGPhysicsSpace* space, SGPhysicsBody* body)
{
    if(body->type != SG_BODY_STATIC
    && body->type != SG_BODY_SEMISTATIC)
        cpSpaceAddBody(space->handle, body->handle);
}
void SG_CALL _sgPhysicsSpaceRemoveBody(SGPhysicsSpace* space, SGPhysicsBody* body)
{
    if(body->type != SG_BODY_STATIC
    && body->type != SG_BODY_SEMISTATIC)
        cpSpaceRemoveBody(space->handle, body->handle);
}

void SG_CALL _sgPhysicsSpaceAddConstraint(SGPhysicsSpace* space, SGPhysicsConstraint* constraint)
{
    cpSpaceAddConstraint(space->handle, constraint->handle);
}
void SG_CALL _sgPhysicsSpaceRemoveConstraint(SGPhysicsSpace* space, SGPhysicsConstraint* constraint)
{
    cpSpaceRemoveConstraint(space->handle, constraint->handle);
}
#endif /* SG_USE_PHYSICS */
