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
#include "../config.h"
#include "../util/list.h"
#include "shape.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#ifdef SG_USE_PHYSICS
typedef struct SGPhysicsCollision
{
    void* handle;
    SGPhysicsShape* shape1;
    SGPhysicsShape* shape2;
} SGPhysicsCollision;

void SG_CALL _sg_cbPhysicsCollisionBegin(SGPhysicsShape* shape1, SGPhysicsShape* shape2, void* handle);
void SG_CALL _sg_cbPhysicsCollisionPreSolve(SGPhysicsShape* shape1, SGPhysicsShape* shape2, void* handle);
void SG_CALL _sg_cbPhysicsCollisionPostSolve(SGPhysicsShape* shape1, SGPhysicsShape* shape2, void* handle);
void SG_CALL _sg_cbPhysicsCollisionSeparate(SGPhysicsShape* shape1, SGPhysicsShape* shape2, void* handle);

void SG_CALL sgPhysicsCollisionIgnore(SGPhysicsCollision* coll);
size_t SG_CALL sgPhysicsCollisionGetNumContacts(SGPhysicsCollision* coll);
void SG_CALL sgPhysicsCollisionGetPoint(SGPhysicsCollision* coll, size_t index, float* x, float* y);
void SG_CALL sgPhysicsCollisionGetNormal(SGPhysicsCollision* coll, size_t index, float* x, float* y);
float SG_CALL sgPhysicsCollisionGetDepth(SGPhysicsCollision* coll, size_t index);
void SG_CALL sgPhysicsCollisionGetImpulse(SGPhysicsCollision* coll, float* x, float* y, SGbool friction);
SGPhysicsShape* SG_CALL sgPhysicsCollisionGetShapeOne(SGPhysicsCollision* coll);
SGPhysicsShape* SG_CALL sgPhysicsCollisionGetShapeTwo(SGPhysicsCollision* coll);
#endif /* SG_USE_PHYSICS */

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_PHYSICS_COLLISION_H__
