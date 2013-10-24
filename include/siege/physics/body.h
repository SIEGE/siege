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
#include "../module.h"
#include "space.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

struct SGEntity;

typedef struct SGPhysicsBody
{
    void* handle;
    SGPhysicsSpace* space;
    void* data;

    SGenum type;

    struct SGEntity* entity;
} SGPhysicsBody;

SGPhysicsBody* SG_CALL SG_FPTR(sgPhysicsBodyCreate)(SGPhysicsSpace* space, SGenum type);
void SG_CALL SG_FPTR(sgPhysicsBodyDestroy)(SGPhysicsBody* body);

void SG_CALL SG_FPTR(sgPhysicsBodySetData)(SGPhysicsBody* body, void* data);
void* SG_CALL SG_FPTR(sgPhysicsBodyGetData)(SGPhysicsBody* body);

void SG_CALL SG_FPTR(sgPhysicsBodySetSleeping)(SGPhysicsBody* body, SGbool sleeping);
SGbool SG_CALL SG_FPTR(sgPhysicsBodyGetSleeping)(SGPhysicsBody* body);

void SG_CALL SG_FPTR(sgPhysicsBodySetPos)(SGPhysicsBody* body, float x, float y);
void SG_CALL SG_FPTR(sgPhysicsBodyGetPos)(SGPhysicsBody* body, float* x, float* y);

void SG_CALL SG_FPTR(sgPhysicsBodySetPosX)(SGPhysicsBody* body, float x);
float SG_CALL SG_FPTR(sgPhysicsBodyGetPosX)(SGPhysicsBody* body);
void SG_CALL SG_FPTR(sgPhysicsBodySetPosY)(SGPhysicsBody* body, float y);
float SG_CALL SG_FPTR(sgPhysicsBodyGetPosY)(SGPhysicsBody* body);

void SG_CALL SG_FPTR(sgPhysicsBodySetAngleRads)(SGPhysicsBody* body, float rads);
float SG_CALL SG_FPTR(sgPhysicsBodyGetAngleRads)(SGPhysicsBody* body);
void SG_CALL SG_FPTR(sgPhysicsBodySetAngleDegs)(SGPhysicsBody* body, float degs);
float SG_CALL SG_FPTR(sgPhysicsBodyGetAngleDegs)(SGPhysicsBody* body);

void SG_CALL SG_FPTR(sgPhysicsBodySetVel)(SGPhysicsBody* body, float x, float y);
void SG_CALL SG_FPTR(sgPhysicsBodyGetVel)(SGPhysicsBody* body, float* x, float* y);

void SG_CALL SG_FPTR(sgPhysicsBodySetVelX)(SGPhysicsBody* body, float x);
float SG_CALL SG_FPTR(sgPhysicsBodyGetVelX)(SGPhysicsBody* body);
void SG_CALL SG_FPTR(sgPhysicsBodySetVelY)(SGPhysicsBody* body, float y);
float SG_CALL SG_FPTR(sgPhysicsBodyGetVelY)(SGPhysicsBody* body);

void SG_CALL SG_FPTR(sgPhysicsBodySetAngVelRads)(SGPhysicsBody* body, float rads);
float SG_CALL SG_FPTR(sgPhysicsBodyGetAngVelRads)(SGPhysicsBody* body);
void SG_CALL SG_FPTR(sgPhysicsBodySetAngVelDegs)(SGPhysicsBody* body, float degs);
float SG_CALL SG_FPTR(sgPhysicsBodyGetAngVelDegs)(SGPhysicsBody* body);

void SG_CALL SG_FPTR(sgPhysicsBodySetMass)(SGPhysicsBody* body, float mass);
float SG_CALL SG_FPTR(sgPhysicsBodyGetMass)(SGPhysicsBody* body);

void SG_CALL SG_FPTR(sgPhysicsBodySetMoment)(SGPhysicsBody* body, float moment);
float SG_CALL SG_FPTR(sgPhysicsBodyGetMoment)(SGPhysicsBody* body);

void SG_CALL SG_FPTR(sgPhysicsBodySetForce)(SGPhysicsBody* body, float x, float y);
void SG_CALL SG_FPTR(sgPhysicsBodyGetForce)(SGPhysicsBody* body, float* x, float* y);

void SG_CALL SG_FPTR(sgPhysicsBodySetForceX)(SGPhysicsBody* body, float x);
float SG_CALL SG_FPTR(sgPhysicsBodyGetForceX)(SGPhysicsBody* body);
void SG_CALL SG_FPTR(sgPhysicsBodySetForceY)(SGPhysicsBody* body, float y);
float SG_CALL SG_FPTR(sgPhysicsBodyGetForceY)(SGPhysicsBody* body);

/* TODO: rads/degs? */
void SG_CALL SG_FPTR(sgPhysicsBodySetTorque)(SGPhysicsBody* body, float torque);
float SG_CALL SG_FPTR(sgPhysicsBodyGetTorque)(SGPhysicsBody* body);

void SG_CALL SG_FPTR(sgPhysicsBodyApplyImpulse)(SGPhysicsBody* body, float jx, float jy, float rx, float ry);
void SG_CALL SG_FPTR(sgPhysicsBodyApplyForce)(SGPhysicsBody* body, float jx, float jy, float rx, float ry);

void SG_CALL SG_FPTR(sgPhysicsBodyWorldToLocal)(SGPhysicsBody* body, float* xo, float* yo, float x, float y);
void SG_CALL SG_FPTR(sgPhysicsBodyLocalToWorld)(SGPhysicsBody* body, float* xo, float* yo, float x, float y);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_PHYSICS_BODY_H__
