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

#ifndef __SIEGE_BACKEND_PHYSICS_BODY_H__
#define __SIEGE_BACKEND_PHYSICS_BODY_H__

#include "../../common.h"

#ifndef SG_FPTR
#define SG_FPTR(name)	name
#endif // SG_FPTR

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsBodyCreate)(void** body, SGenum type);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsBodyDestroy)(void* body);

    SGuint SG_EXPORT SG_FPTR(sgmPhysicsBodySetMass)(void* body, float mass);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsBodyGetMass)(void* body, float* mass);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsBodySetMoment)(void* body, float moment);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsBodyGetMoment)(void* body, float* moment);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsBodySetPosition)(void* body, float x, float y);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsBodyGetPosition)(void* body, float* x, float* y);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsBodySetVelocity)(void* body, float x, float y);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsBodyGetVelocity)(void* body, float* x, float* y);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsBodySetForce)(void* body, float x, float y);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsBodyGetForce)(void* body, float* x, float* y);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsBodySetAngle)(void* body, float angle);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsBodyGetAngle)(void* body, float* angle);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsBodySetAngularVelocity)(void* body, float angvel);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsBodyGetAngularVelocity)(void* body, float* angvel);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsBodySetTorque)(void* body, float torque);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsBodyGetTorque)(void* body, float* torque);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsBodySetData)(void* body, void* data);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsBodyGetData)(void* body, void** data);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_PHYSICS_BODY_H__
