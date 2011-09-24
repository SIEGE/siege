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
#include <siege/physics/collision.h>
#include <siege/core/entity.h>

#include <stdlib.h>

SGbool SG_EXPORT _sgPhysicsCollisionInit(void)
{
    _sg_colCallbacks.begin = _sg_cbPhysicsCollisionBegin;
    _sg_colCallbacks.step = _sg_cbPhysicsCollision;
    _sg_colCallbacks.post = _sg_cbPhysicsCollisionPost;
    _sg_colCallbacks.end = _sg_cbPhysicsCollisionEnd;

    if(psgmPhysicsCollisionSetCallbacks)
        psgmPhysicsCollisionSetCallbacks(&_sg_colCallbacks);

    return SG_TRUE;
}

SGbool SG_EXPORT _sgPhysicsCollisionDeinit(void)
{
    if(psgmPhysicsCollisionSetCallbacks)
        psgmPhysicsCollisionSetCallbacks(NULL);

    return SG_TRUE;
}

void SG_EXPORT _sg_cbPhysicsCollisionBegin(void* shandle1, void* shandle2, void* handle)
{
    SGPhysicsCollision coll;
    coll.shandle1 = shandle1;
    coll.shandle2 = shandle2;
    coll.handle = handle;
    coll.shape1 = NULL;
    coll.shape2 = NULL;

    if(psgmPhysicsShapeGetData)
    {
        psgmPhysicsShapeGetData(shandle1, (void**)&coll.shape1);
        psgmPhysicsShapeGetData(shandle2, (void**)&coll.shape2);
    }

    if(coll.shape1 && coll.shape1->body->entity)
    {
        if(coll.shape1->body->entity->lcCollisionBegin)
            coll.shape1->body->entity->lcCollisionBegin(coll.shape1->body->entity, coll.shape2->body->entity, &coll);
        if(coll.shape1->body->entity->lcCollisionOneBegin)
            coll.shape1->body->entity->lcCollisionOneBegin(coll.shape1->body->entity, coll.shape2->body->entity, &coll);
    }
    if(coll.shape2 && coll.shape2->body->entity)
    {
        if(coll.shape2->body->entity->lcCollisionBegin)
            coll.shape2->body->entity->lcCollisionBegin(coll.shape2->body->entity, coll.shape1->body->entity, &coll);
        if(coll.shape2->body->entity->lcCollisionTwoBegin)
            coll.shape2->body->entity->lcCollisionTwoBegin(coll.shape2->body->entity, coll.shape1->body->entity, &coll);
    }
}
void SG_EXPORT _sg_cbPhysicsCollision(void* shandle1, void* shandle2, void* handle)
{
    SGPhysicsCollision coll;
    coll.shandle1 = shandle1;
    coll.shandle2 = shandle2;
    coll.handle = handle;
    coll.shape1 = NULL;
    coll.shape2 = NULL;

    if(psgmPhysicsShapeGetData)
    {
        psgmPhysicsShapeGetData(shandle1, (void**)&coll.shape1);
        psgmPhysicsShapeGetData(shandle2, (void**)&coll.shape2);
    }

    if(coll.shape1 && coll.shape1->body->entity)
    {
        if(coll.shape1->body->entity->lcCollision)
            coll.shape1->body->entity->lcCollision(coll.shape1->body->entity, coll.shape2->body->entity, &coll);
        if(coll.shape1->body->entity->lcCollisionOne)
            coll.shape1->body->entity->lcCollisionOne(coll.shape1->body->entity, coll.shape2->body->entity, &coll);
    }
    if(coll.shape2 && coll.shape2->body->entity)
    {
        if(coll.shape2->body->entity->lcCollision)
            coll.shape2->body->entity->lcCollision(coll.shape2->body->entity, coll.shape1->body->entity, &coll);
        if(coll.shape2->body->entity->lcCollisionTwo)
            coll.shape2->body->entity->lcCollisionTwo(coll.shape2->body->entity, coll.shape1->body->entity, &coll);
    }
}
void SG_EXPORT _sg_cbPhysicsCollisionPost(void* shandle1, void* shandle2, void* handle) /// \TODO TODO
{
}
void SG_EXPORT _sg_cbPhysicsCollisionEnd(void* shandle1, void* shandle2, void* handle)
{
    SGPhysicsCollision coll;
    coll.shandle1 = shandle1;
    coll.shandle2 = shandle2;
    coll.handle = handle;
    coll.shape1 = NULL;
    coll.shape2 = NULL;

    if(psgmPhysicsShapeGetData)
    {
        psgmPhysicsShapeGetData(shandle1, (void**)&coll.shape1);
        psgmPhysicsShapeGetData(shandle2, (void**)&coll.shape2);
    }

    if(coll.shape1 && coll.shape1->body->entity)
    {
        if(coll.shape1->body->entity->lcCollisionEnd)
            coll.shape1->body->entity->lcCollisionEnd(coll.shape1->body->entity, coll.shape2->body->entity, &coll);
        if(coll.shape1->body->entity->lcCollisionOneEnd)
            coll.shape1->body->entity->lcCollisionOneEnd(coll.shape1->body->entity, coll.shape2->body->entity, &coll);
    }
    if(coll.shape2 && coll.shape2->body->entity)
    {
        if(coll.shape2->body->entity->lcCollisionEnd)
            coll.shape2->body->entity->lcCollisionEnd(coll.shape2->body->entity, coll.shape1->body->entity, &coll);
        if(coll.shape2->body->entity->lcCollisionTwoEnd)
            coll.shape2->body->entity->lcCollisionTwoEnd(coll.shape2->body->entity, coll.shape1->body->entity, &coll);
    }
}

void SG_EXPORT sgPhysicsCollisionIgnore(SGPhysicsCollision* coll)
{
    if(psgmPhysicsCollisionIgnore)
        psgmPhysicsCollisionIgnore(coll->handle);
}

size_t SG_EXPORT sgPhysicsCollisionGetNumContacts(SGPhysicsCollision* coll)
{
    size_t num = 0;
    if(psgmPhysicsCollisionGetNumContacts)
        psgmPhysicsCollisionGetNumContacts(coll->handle, &num);
    return num;
}
void SG_EXPORT sgPhysicsCollisionGetPoint(SGPhysicsCollision* coll, size_t index, float* x, float* y)
{
    float tmp;
    if(x == NULL)
        x = &tmp;
    if(y == NULL)
        y = &tmp;
    *x = SG_NAN;
    *y = SG_NAN;
    if(psgmPhysicsCollisionGetPoint)
        psgmPhysicsCollisionGetPoint(coll->handle, index, x, y);
}
void SG_EXPORT sgPhysicsCollisionGetNormal(SGPhysicsCollision* coll, size_t index, float* x, float* y)
{
    float tmp;
    if(x == NULL)
        x = &tmp;
    if(y == NULL)
        y = &tmp;
    *x = SG_NAN;
    *y = SG_NAN;
    if(psgmPhysicsCollisionGetNormal)
        psgmPhysicsCollisionGetNormal(coll->handle, index, x, y);
}
float SG_EXPORT sgPhysicsCollisionGetDistance(SGPhysicsCollision* coll, size_t index)
{
    float dist = SG_NAN;
    if(psgmPhysicsCollisionGetDistance)
        psgmPhysicsCollisionGetDistance(coll->handle, index, &dist);
    return dist;
}
void SG_EXPORT sgPhysicsCollisionGetImpulse(SGPhysicsCollision* coll, float* x, float* y, SGbool friction)
{
    float tmp;
    if(x == NULL)
        x = &tmp;
    if(y == NULL)
        y = &tmp;
    *x = SG_NAN;
    *y = SG_NAN;
    if(psgmPhysicsCollisionGetImpulse)
        psgmPhysicsCollisionGetImpulse(coll->handle, x, y, friction);
}
SGPhysicsShape* SG_EXPORT sgPhysicsCollisionGetShapeOne(SGPhysicsCollision* coll)
{
    return coll->shape1;
}
SGPhysicsShape* SG_EXPORT sgPhysicsCollisionGetShapeTwo(SGPhysicsCollision* coll)
{
    return coll->shape2;
}
