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

#ifndef __SIEGE_PHYSICS_COLLISION_H__
#define __SIEGE_PHYSICS_COLLISION_H__

#include "../common.h"
#include "../util/list.h"
#include "shape.h"
#include "../modules/physics.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGPhysicsCollision
{
    void* shandle1;
    void* shandle2;
    void* handle;
    SGPhysicsShape* shape1;
    SGPhysicsShape* shape2;
} SGPhysicsCollision;

#ifdef SG_BUILD_LIBRARY
SGPhysicsCollisionCallbacks _sg_colCallbacks;
#endif // SG_BUILD_LIBRARY

SGbool SG_EXPORT _sgPhysicsCollisionInit(void);
SGbool SG_EXPORT _sgPhysicsCollisionDeinit(void);

void SG_EXPORT _sg_cbPhysicsCollisionBegin(void* shandle1, void* shandle2, void* handle);
void SG_EXPORT _sg_cbPhysicsCollision(void* shandle1, void* shandle2, void* handle);
void SG_EXPORT _sg_cbPhysicsCollisionPost(void* shandle1, void* shandle2, void* handle);
void SG_EXPORT _sg_cbPhysicsCollisionEnd(void* shandle1, void* shandle2, void* handle);

void SG_EXPORT sgPhysicsCollisionIgnore(SGPhysicsCollision* coll);
size_t SG_EXPORT sgPhysicsCollisionGetNumContacts(SGPhysicsCollision* coll);
void SG_EXPORT sgPhysicsCollisionGetPoint(SGPhysicsCollision* coll, size_t index, float* x, float* y);
void SG_EXPORT sgPhysicsCollisionGetNormal(SGPhysicsCollision* coll, size_t index, float* x, float* y);
float SG_EXPORT sgPhysicsCollisionGetDistance(SGPhysicsCollision* coll, size_t index);
void SG_EXPORT sgPhysicsCollisionGetImpulse(SGPhysicsCollision* coll, float* x, float* y, SGbool friction);
SGPhysicsShape* SG_EXPORT sgPhysicsCollisionGetShapeOne(SGPhysicsCollision* coll);
SGPhysicsShape* SG_EXPORT sgPhysicsCollisionGetShapeTwo(SGPhysicsCollision* coll);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_PHYSICS_COLLISION_H__
