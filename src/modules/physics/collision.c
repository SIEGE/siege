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

#define SG_BUILD_MODULE
#include <siege/physics/collision.h>
#include <siege/core/entity.h>

#include <stdlib.h>

#include "compat.h"

/* TODO: Return value */
void SG_CALL _sg_cbPhysicsCollisionBegin(SGPhysicsShape* shape1, SGPhysicsShape* shape2, void* handle)
{
    SGPhysicsCollision coll;
    coll.handle = handle;
    coll.shape1 = shape1;
    coll.shape2 = shape2;

    if(shape1 && shape1->body->entity)
    {
        if(shape1->body->entity->lcCollisionBegin)
            shape1->body->entity->lcCollisionBegin(shape1->body->entity, shape2->body->entity, &coll);
        if(shape1->body->entity->lcCollisionOneBegin)
            shape1->body->entity->lcCollisionOneBegin(shape1->body->entity, shape2->body->entity, &coll);
    }
    if(shape2 && shape2->body->entity)
    {
        if(shape2->body->entity->lcCollisionBegin)
            shape2->body->entity->lcCollisionBegin(shape2->body->entity, shape1->body->entity, &coll);
        if(shape2->body->entity->lcCollisionTwoBegin)
            shape2->body->entity->lcCollisionTwoBegin(shape2->body->entity, shape1->body->entity, &coll);
    }
}
void SG_CALL _sg_cbPhysicsCollisionPreSolve(SGPhysicsShape* shape1, SGPhysicsShape* shape2, void* handle)
{
    SGPhysicsCollision coll;
    coll.handle = handle;
    coll.shape1 = shape1;
    coll.shape2 = shape2;

    if(shape1 && shape1->body->entity)
    {
        if(shape1->body->entity->lcCollision)
            shape1->body->entity->lcCollision(shape1->body->entity, shape2->body->entity, &coll);
        if(shape1->body->entity->lcCollisionOne)
            shape1->body->entity->lcCollisionOne(shape1->body->entity, shape2->body->entity, &coll);
    }
    if(shape2 && shape2->body->entity)
    {
        if(shape2->body->entity->lcCollision)
            shape2->body->entity->lcCollision(shape2->body->entity, shape1->body->entity, &coll);
        if(shape2->body->entity->lcCollisionTwo)
            shape2->body->entity->lcCollisionTwo(shape2->body->entity, shape1->body->entity, &coll);
    }
}
void SG_CALL _sg_cbPhysicsCollisionPostSolve(SGPhysicsShape* shape1, SGPhysicsShape* shape2, void* handle) /// \TODO TODO
{
}
void SG_CALL _sg_cbPhysicsCollisionSeparate(SGPhysicsShape* shape1, SGPhysicsShape* shape2, void* handle)
{
    SGPhysicsCollision coll;
    coll.handle = handle;
    coll.shape1 = shape1;
    coll.shape2 = shape2;

    if(shape1 && shape1->body->entity)
    {
        if(shape1->body->entity->lcCollisionEnd)
            shape1->body->entity->lcCollisionEnd(shape1->body->entity, shape2->body->entity, &coll);
        if(shape1->body->entity->lcCollisionOneEnd)
            shape1->body->entity->lcCollisionOneEnd(shape1->body->entity, shape2->body->entity, &coll);
    }
    if(shape2 && shape2->body->entity)
    {
        if(shape2->body->entity->lcCollisionEnd)
            shape2->body->entity->lcCollisionEnd(shape2->body->entity, shape1->body->entity, &coll);
        if(shape2->body->entity->lcCollisionTwoEnd)
            shape2->body->entity->lcCollisionTwoEnd(shape2->body->entity, shape1->body->entity, &coll);
    }
}

void SG_CALL sgPhysicsCollisionIgnore(SGPhysicsCollision* coll)
{
    cpArbiterIgnore(coll->handle);
}

size_t SG_CALL sgPhysicsCollisionGetNumContacts(SGPhysicsCollision* coll)
{
    return cpArbiterGetCount(coll->handle);
}
void SG_CALL sgPhysicsCollisionGetPoint(SGPhysicsCollision* coll, size_t index, float* x, float* y)
{
    float t;
    if(!x) x = &t;
    if(!y) y = &t;

    cpVect a = cpArbiterGetPointA(coll->handle, index);
    cpVect b = cpArbiterGetPointB(coll->handle, index);
    *x = (a.x + b.x) / 2.0f;
    *y = (a.y + b.y) / 2.0f;
}
void SG_CALL sgPhysicsCollisionGetNormal(SGPhysicsCollision* coll, size_t index, float* x, float* y)
{
    float t;
    if(!x) x = &t;
    if(!y) y = &t;

    cpVect v = cpArbiterGetNormal(coll->handle);
    *x = v.x;
    *y = v.y;
}
float SG_CALL sgPhysicsCollisionGetDepth(SGPhysicsCollision* coll, size_t index)
{
    return cpArbiterGetDepth(coll->handle, index);
}
void SG_CALL sgPhysicsCollisionGetImpulse(SGPhysicsCollision* coll, float* x, float* y, SGbool friction)
{
    float t;
    if(!x) x = &t;
    if(!y) y = &t;

    cpVect v = cpArbiterTotalImpulse(coll->handle);
    *x = v.x;
    *y = v.y;
}
SGPhysicsShape* SG_CALL sgPhysicsCollisionGetShapeOne(SGPhysicsCollision* coll)
{
    return coll->shape1;
}
SGPhysicsShape* SG_CALL sgPhysicsCollisionGetShapeTwo(SGPhysicsCollision* coll)
{
    return coll->shape2;
}
