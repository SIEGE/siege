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

#ifndef __SIEGE_PHYSICS_BODY_H__
#define __SIEGE_PHYSICS_BODY_H__

#include "../common.h"
#include "../config.h"
#include "space.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#ifdef SG_USE_PHYSICS
struct SGEntity;

typedef struct SGPhysicsBody
{
    void* handle;
    SGPhysicsSpace* space;
    void* data;

    SGenum type;

    struct SGEntity* entity;
} SGPhysicsBody;

SGPhysicsBody* SG_CALL sgPhysicsBodyCreate(SGPhysicsSpace* space, SGenum type);
void SG_CALL sgPhysicsBodyDestroy(SGPhysicsBody* body);

void SG_CALL sgPhysicsBodySetData(SGPhysicsBody* body, void* data);
void* SG_CALL sgPhysicsBodyGetData(SGPhysicsBody* body);

void SG_CALL sgPhysicsBodySetSleeping(SGPhysicsBody* body, SGbool sleeping);
SGbool SG_CALL sgPhysicsBodyGetSleeping(SGPhysicsBody* body);

void SG_CALL sgPhysicsBodySetPos(SGPhysicsBody* body, float x, float y);
void SG_CALL sgPhysicsBodyGetPos(SGPhysicsBody* body, float* x, float* y);

void SG_CALL sgPhysicsBodySetPosX(SGPhysicsBody* body, float x);
float SG_CALL sgPhysicsBodyGetPosX(SGPhysicsBody* body);
void SG_CALL sgPhysicsBodySetPosY(SGPhysicsBody* body, float y);
float SG_CALL sgPhysicsBodyGetPosY(SGPhysicsBody* body);

void SG_CALL sgPhysicsBodySetAngleRads(SGPhysicsBody* body, float rads);
float SG_CALL sgPhysicsBodyGetAngleRads(SGPhysicsBody* body);
void SG_CALL sgPhysicsBodySetAngleDegs(SGPhysicsBody* body, float degs);
float SG_CALL sgPhysicsBodyGetAngleDegs(SGPhysicsBody* body);

void SG_CALL sgPhysicsBodySetVel(SGPhysicsBody* body, float x, float y);
void SG_CALL sgPhysicsBodyGetVel(SGPhysicsBody* body, float* x, float* y);

void SG_CALL sgPhysicsBodySetVelX(SGPhysicsBody* body, float x);
float SG_CALL sgPhysicsBodyGetVelX(SGPhysicsBody* body);
void SG_CALL sgPhysicsBodySetVelY(SGPhysicsBody* body, float y);
float SG_CALL sgPhysicsBodyGetVelY(SGPhysicsBody* body);

void SG_CALL sgPhysicsBodySetAngVelRads(SGPhysicsBody* body, float rads);
float SG_CALL sgPhysicsBodyGetAngVelRads(SGPhysicsBody* body);
void SG_CALL sgPhysicsBodySetAngVelDegs(SGPhysicsBody* body, float degs);
float SG_CALL sgPhysicsBodyGetAngVelDegs(SGPhysicsBody* body);

void SG_CALL sgPhysicsBodySetMass(SGPhysicsBody* body, float mass);
float SG_CALL sgPhysicsBodyGetMass(SGPhysicsBody* body);

void SG_CALL sgPhysicsBodySetMoment(SGPhysicsBody* body, float moment);
float SG_CALL sgPhysicsBodyGetMoment(SGPhysicsBody* body);

void SG_CALL sgPhysicsBodySetForce(SGPhysicsBody* body, float x, float y);
void SG_CALL sgPhysicsBodyGetForce(SGPhysicsBody* body, float* x, float* y);

void SG_CALL sgPhysicsBodySetForceX(SGPhysicsBody* body, float x);
float SG_CALL sgPhysicsBodyGetForceX(SGPhysicsBody* body);
void SG_CALL sgPhysicsBodySetForceY(SGPhysicsBody* body, float y);
float SG_CALL sgPhysicsBodyGetForceY(SGPhysicsBody* body);

/* TODO: rads/degs? */
void SG_CALL sgPhysicsBodySetTorque(SGPhysicsBody* body, float torque);
float SG_CALL sgPhysicsBodyGetTorque(SGPhysicsBody* body);

void SG_CALL sgPhysicsBodyApplyImpulse(SGPhysicsBody* body, float jx, float jy, float rx, float ry);
void SG_CALL sgPhysicsBodyApplyForce(SGPhysicsBody* body, float jx, float jy, float rx, float ry);

void SG_CALL sgPhysicsBodyWorldToLocal(SGPhysicsBody* body, float* xo, float* yo, float x, float y);
void SG_CALL sgPhysicsBodyLocalToWorld(SGPhysicsBody* body, float* xo, float* yo, float x, float y);
#endif /* SG_USE_PHYSICS */

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_PHYSICS_BODY_H__
