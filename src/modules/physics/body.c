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
#include <siege/physics/body.h>

#include <stdlib.h>
#include <math.h>

#include <chipmunk/chipmunk.h>

SGPhysicsBody* SG_CALL sgPhysicsBodyCreate(SGPhysicsSpace* space, SGenum type)
{
    SGPhysicsBody* body = malloc(sizeof(SGPhysicsBody));
    if(!body) return NULL;

    if(!space)
        space = _sg_physSpaceMain;

    body->space = space;
    body->data = NULL;

    body->type = type;

    body->entity = NULL;

    body->handle = cpBodyNew(1, 1);
    cpBodySetUserData(body->handle, body);

    _sgPhysicsSpaceAddBody(space, body);

    return body;
}
void SG_CALL sgPhysicsBodyDestroy(SGPhysicsBody* body)
{
    if(!body) return;

    _sgPhysicsSpaceRemoveBody(body->space, body);
    cpBodyFree(body->handle);
    free(body);
}

void SG_CALL sgPhysicsBodySetData(SGPhysicsBody* body, void* data)
{
    body->data = data;
}
void* SG_CALL sgPhysicsBodyGetData(SGPhysicsBody* body)
{
    return body->data;
}

void SG_CALL sgPhysicsBodySetSleeping(SGPhysicsBody* body, SGbool sleeping)
{
    if(sleeping)
        cpBodySleep(body->handle);
    else
        cpBodyActivate(body->handle);
}
SGbool SG_CALL sgPhysicsBodyGetSleeping(SGPhysicsBody* body)
{
    return cpBodyIsSleeping(body->handle);
}

void SG_CALL sgPhysicsBodySetPos(SGPhysicsBody* body, float x, float y)
{
    cpBodySetPos(body->handle, cpv(x, y));
}
void SG_CALL sgPhysicsBodyGetPos(SGPhysicsBody* body, float* x, float* y)
{
    float t;
    if(!x) x = &t;
    if(!y) y = &t;

    cpVect pos = cpBodyGetPos(body->handle);
    *x = pos.x;
    *y = pos.y;
}

void SG_CALL sgPhysicsBodySetPosX(SGPhysicsBody* body, float x)
{
    float y = sgPhysicsBodyGetPosY(body);
    sgPhysicsBodySetPos(body, x, y);
}
float SG_CALL sgPhysicsBodyGetPosX(SGPhysicsBody* body)
{
    float x;
    sgPhysicsBodyGetPos(body, &x, NULL);
    return x;
}
void SG_CALL sgPhysicsBodySetPosY(SGPhysicsBody* body, float y)
{
    float x = sgPhysicsBodyGetPosX(body);
    sgPhysicsBodySetPos(body, x, y);
}
float SG_CALL sgPhysicsBodyGetPosY(SGPhysicsBody* body)
{
    float y;
    sgPhysicsBodyGetPos(body, NULL, &y);
    return y;
}

void SG_CALL sgPhysicsBodySetAngleRads(SGPhysicsBody* body, float rads)
{
    cpBodySetAngle(body->handle, rads);
}
float SG_CALL sgPhysicsBodyGetAngleRads(SGPhysicsBody* body)
{
    return cpBodyGetAngle(body->handle);
}
void SG_CALL sgPhysicsBodySetAngleDegs(SGPhysicsBody* body, float degs)
{
    sgPhysicsBodySetAngleRads(body, degs * SG_PI / 180.0);
}
float SG_CALL sgPhysicsBodyGetAngleDegs(SGPhysicsBody* body)
{
    return sgPhysicsBodyGetAngleRads(body) * 180.0 / SG_PI;
}

void SG_CALL sgPhysicsBodySetVel(SGPhysicsBody* body, float x, float y)
{
    cpBodySetVel(body->handle, cpv(x, y));
}
void SG_CALL sgPhysicsBodyGetVel(SGPhysicsBody* body, float* x, float* y)
{
    float t;
    if(!x) x = &t;
    if(!y) y = &t;

    cpVect vel = cpBodyGetVel(body->handle);
    *x = vel.x;
    *y = vel.y;
}

void SG_CALL sgPhysicsBodySetVelX(SGPhysicsBody* body, float x)
{
    float y = sgPhysicsBodyGetVelY(body);
    sgPhysicsBodySetVel(body, x, y);
}
float SG_CALL sgPhysicsBodyGetVelX(SGPhysicsBody* body)
{
    float x;
    sgPhysicsBodyGetVel(body, &x, NULL);
    return x;
}
void SG_CALL sgPhysicsBodySetVelY(SGPhysicsBody* body, float y)
{
    float x = sgPhysicsBodyGetVelX(body);
    sgPhysicsBodySetVel(body, x, y);
}
float SG_CALL sgPhysicsBodyGetVelY(SGPhysicsBody* body)
{
    float y;
    sgPhysicsBodyGetVel(body, NULL, &y);
    return y;
}

void SG_CALL sgPhysicsBodySetAngVelRads(SGPhysicsBody* body, float rads)
{
    cpBodySetAngVel(body->handle, rads);
}
float SG_CALL sgPhysicsBodyGetAngVelRads(SGPhysicsBody* body)
{
    return cpBodyGetAngVel(body->handle);
}
void SG_CALL sgPhysicsBodySetAngVelDegs(SGPhysicsBody* body, float degs)
{
    sgPhysicsBodySetAngVelRads(body, degs * SG_PI / 180.0);
}
float SG_CALL sgPhysicsBodyGetAngVelDegs(SGPhysicsBody* body)
{
    return sgPhysicsBodyGetAngVelRads(body) * 180.0 / SG_PI;
}

void SG_CALL sgPhysicsBodySetMass(SGPhysicsBody* body, float mass)
{
    cpBodySetMass(body->handle, mass);
}
float SG_CALL sgPhysicsBodyGetMass(SGPhysicsBody* body)
{
    return cpBodyGetMass(body->handle);
}

void SG_CALL sgPhysicsBodySetMoment(SGPhysicsBody* body, float moment)
{
    cpBodySetMoment(body->handle, moment);
}
float SG_CALL sgPhysicsBodyGetMoment(SGPhysicsBody* body)
{
    return cpBodyGetMoment(body->handle);
}

void SG_CALL sgPhysicsBodySetForce(SGPhysicsBody* body, float x, float y)
{
    cpBodySetForce(body->handle, cpv(x, y));
}
void SG_CALL sgPhysicsBodyGetForce(SGPhysicsBody* body, float* x, float* y)
{
    float t;
    if(!x) x = &t;
    if(!y) y = &t;

    cpVect vel = cpBodyGetForce(body->handle);
    *x = vel.x;
    *y = vel.y;
}

void SG_CALL sgPhysicsBodySetForceX(SGPhysicsBody* body, float x)
{
    float y = sgPhysicsBodyGetForceY(body);
    sgPhysicsBodySetForce(body, x, y);
}
float SG_CALL sgPhysicsBodyGetForceX(SGPhysicsBody* body)
{
    float x;
    sgPhysicsBodyGetForce(body, &x, NULL);
    return x;
}
void SG_CALL sgPhysicsBodySetForceY(SGPhysicsBody* body, float y)
{
    float x = sgPhysicsBodyGetForceX(body);
    sgPhysicsBodySetForce(body, x, y);
}
float SG_CALL sgPhysicsBodyGetForceY(SGPhysicsBody* body)
{
    float y;
    sgPhysicsBodyGetForce(body, NULL, &y);
    return y;
}

void SG_CALL sgPhysicsBodySetTorque(SGPhysicsBody* body, float torque)
{
    cpBodySetTorque(body->handle, torque);
}
float SG_CALL sgPhysicsBodyGetTorque(SGPhysicsBody* body)
{
    return cpBodyGetTorque(body->handle);
}

void SG_CALL sgPhysicsBodyApplyImpulse(SGPhysicsBody* body, float jx, float jy, float rx, float ry)
{
    cpBodyApplyImpulse(body->handle, cpv(jx, jy), cpv(rx, ry));
}
void SG_CALL sgPhysicsBodyApplyForce(SGPhysicsBody* body, float jx, float jy, float rx, float ry)
{
    cpBodyApplyForce(body->handle, cpv(jx, jy), cpv(rx, ry));
}

void SG_CALL sgPhysicsBodyWorldToLocal(SGPhysicsBody* body, float* xo, float* yo, float x, float y)
{
    float t;
    if(!xo) xo = &t;
    if(!yo) yo = &t;

    cpVect v = cpBodyWorld2Local(body->handle, cpv(x, y));
    *xo = v.x;
    *yo = v.y;
}
void SG_CALL sgPhysicsBodyLocalToWorld(SGPhysicsBody* body, float* xo, float* yo, float x, float y)
{
    float t;
    if(!xo) xo = &t;
    if(!yo) yo = &t;

    cpVect v = cpBodyLocal2World(body->handle, cpv(x, y));
    *xo = v.x;
    *yo = v.y;
}
