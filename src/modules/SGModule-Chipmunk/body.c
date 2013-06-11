/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "COPYING.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#include "common.h"

#include <stdlib.h>

SGenum SG_CALL sgmPhysicsBodyCreate(void** body, SGenum type)
{
    *body = cpBodyNew(1, 1);
    DataExt* data = malloc(sizeof(DataExt));
    data->type = type;
    data->data = NULL;
    cpBodySetUserData(*body, data);
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsBodyDestroy(void* body)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    free(cpBodyGetUserData(body));
    cpBodyFree(body);
    return SG_OK;
}

SGenum SG_CALL sgmPhysicsBodySetSleeping(void* body, SGbool sleeping)
{
    if(!body)
        return SG_OK; // SG_INVALID_VALUE
    if(sleeping)
        cpBodySleep(body);
    else
        cpBodyActivate(body);
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsBodyGetSleeping(void* body, SGbool* sleeping)
{
    if(!body)
        return SG_OK; // SG_INVALID_VALUE
    *sleeping = cpBodyIsSleeping(body);
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsBodySetMass(void* body, float mass)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpBodySetMass(body, mass);
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsBodyGetMass(void* body, float* mass)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    *mass = cpBodyGetMass(body);
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsBodySetMoment(void* body, float moment)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpBodySetMoment(body, moment);
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsBodyGetMoment(void* body, float* moment)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    *moment = cpBodyGetMoment(body);
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsBodySetPosition(void* body, float x, float y)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpBodySetPos(body, cpv(x, y));
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsBodyGetPosition(void* body, float* x, float* y)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpVect pos = cpBodyGetPos(body);
    *x = pos.x;
    *y = pos.y;
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsBodySetVelocity(void* body, float x, float y)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpBodySetVel(body, cpv(x, y));
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsBodyGetVelocity(void* body, float* x, float* y)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpVect vel = cpBodyGetVel(body);
    *x = vel.x;
    *y = vel.y;
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsBodySetForce(void* body, float x, float y)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpBodySetForce(body, cpv(x, y));
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsBodyGetForce(void* body, float* x, float* y)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpVect force = cpBodyGetForce(body);
    *x = force.x;
    *y = force.y;
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsBodySetAngle(void* body, float angle)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpBodySetAngle(body, angle);
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsBodyGetAngle(void* body, float* angle)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    *angle = cpBodyGetAngle(body);
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsBodySetAngularVelocity(void* body, float angvel)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpBodySetAngVel(body, angvel);
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsBodyGetAngularVelocity(void* body, float* angvel)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    *angvel = cpBodyGetAngVel(body);
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsBodySetTorque(void* body, float torque)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpBodySetTorque(body, torque);
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsBodyGetTorque(void* body, float* torque)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    *torque = cpBodyGetTorque(body);
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsBodySetData(void* body, void* data)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    ((DataExt*)cpBodyGetUserData(body))->data = data;
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsBodyGetData(void* body, void** data)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    *data = ((DataExt*)cpBodyGetUserData(body))->data;
    return SG_OK;
}

SGenum SG_CALL sgmPhysicsBodyApplyImpulse(void* body, float jx, float jy, float rx, float ry)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpBodyApplyImpulse(body, cpv(jx, jy), cpv(rx, ry));
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsBodyApplyForce(void* body, float jx, float jy, float rx, float ry)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpBodyApplyForce(body, cpv(jx, jy), cpv(rx, ry));
    return SG_OK;
}
