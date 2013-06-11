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
#include <siege/physics/body.h>
#include <siege/modules/physics.h>

#include <stdlib.h>
#include <math.h>

SGPhysicsBody* SG_CALL sgPhysicsBodyCreate(SGPhysicsSpace* space, SGenum type)
{
    SGPhysicsBody* body = malloc(sizeof(SGPhysicsBody));
    if(body == NULL)
        return NULL;

    if(space == NULL)
        space = _sg_physSpaceMain;

    body->space = space;
    body->data = NULL;

    body->type = type;

    body->entity = NULL;

    if(psgmPhysicsBodyCreate != NULL)
        psgmPhysicsBodyCreate(&body->handle, body->type);
    if(psgmPhysicsBodySetData != NULL)
        psgmPhysicsBodySetData(body->handle, body);

    if(psgmPhysicsSpaceAddBody != NULL)
        psgmPhysicsSpaceAddBody(space->handle, body->handle);

    return body;
}
void SG_CALL sgPhysicsBodyDestroy(SGPhysicsBody* body)
{
    if(body == NULL)
        return;

    /*if(body->space != NULL)
    {
        if(psgmPhysicsSpaceRemoveBody != NULL)
            psgmPhysicsSpaceRemoveBody(body->space->handle, body->handle);
    }*/

    if(psgmPhysicsSpaceRemoveBody)
        psgmPhysicsSpaceRemoveBody(body->space->handle, body->handle);
    if(psgmPhysicsBodyDestroy != NULL)
        psgmPhysicsBodyDestroy(body->handle);
}

void SG_CALL sgPhysicsBodySetData(SGPhysicsBody* body, void* data)
{
    if(body == NULL)
        return;

    body->data = data;
}
void* SG_CALL sgPhysicsBodyGetData(SGPhysicsBody* body)
{
    if(body == NULL)
        return NULL;

    return body->data;
}

void SG_CALL sgPhysicsBodySetSleeping(SGPhysicsBody* body, SGbool sleeping)
{
    if(!body)
        return;

    if(psgmPhysicsBodySetSleeping)
        psgmPhysicsBodySetMass(body->handle, sleeping);
}
SGbool SG_CALL sgPhysicsBodyGetSleeping(SGPhysicsBody* body)
{
    if(!body)
        return SG_FALSE;

    SGbool sleeping = SG_FALSE;
    if(psgmPhysicsBodyGetSleeping)
        psgmPhysicsBodyGetSleeping(body->handle, &sleeping);
    return sleeping;
}

void SG_CALL sgPhysicsBodySetPos(SGPhysicsBody* body, float x, float y)
{
    if(body == NULL)
        return;

    if(psgmPhysicsBodySetPosition != NULL)
        psgmPhysicsBodySetPosition(body->handle, x, y);
}
void SG_CALL sgPhysicsBodyGetPos(SGPhysicsBody* body, float* x, float* y)
{
    if(body == NULL)
        return;
    if(x == NULL && y == NULL)
        return;

    float t;
    if(x == NULL)
        x = &t;
    else if(y == NULL)
        y = &t;

    if(psgmPhysicsBodyGetPosition != NULL)
        psgmPhysicsBodyGetPosition(body->handle, x, y);
}

void SG_CALL sgPhysicsBodySetPosX(SGPhysicsBody* body, float x)
{
    if(body == NULL)
        return;

    float y = sgPhysicsBodyGetPosY(body);
    sgPhysicsBodySetPos(body, x, y);
}
float SG_CALL sgPhysicsBodyGetPosX(SGPhysicsBody* body)
{
    if(body == NULL)
        return SG_NAN;

    float x;
    sgPhysicsBodyGetPos(body, &x, NULL);
    return x;
}
void SG_CALL sgPhysicsBodySetPosY(SGPhysicsBody* body, float y)
{
    if(body == NULL)
        return;

    float x = sgPhysicsBodyGetPosX(body);
    sgPhysicsBodySetPos(body, x, y);
}
float SG_CALL sgPhysicsBodyGetPosY(SGPhysicsBody* body)
{
    if(body == NULL)
        return SG_NAN;

    float y;
    sgPhysicsBodyGetPos(body, NULL, &y);
    return y;
}

void SG_CALL sgPhysicsBodySetAngleRads(SGPhysicsBody* body, float rads)
{
    if(body == NULL)
        return;

    if(psgmPhysicsBodySetAngle != NULL)
        psgmPhysicsBodySetAngle(body->handle, rads);
}
float SG_CALL sgPhysicsBodyGetAngleRads(SGPhysicsBody* body)
{
    if(body == NULL)
        return SG_NAN;

    float rads;
    if(psgmPhysicsBodyGetAngle != NULL)
        psgmPhysicsBodyGetAngle(body->handle, &rads);
    return rads;
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
    if(body == NULL)
        return;

    if(psgmPhysicsBodySetVelocity != NULL)
        psgmPhysicsBodySetVelocity(body->handle, x, y);
}
void SG_CALL sgPhysicsBodyGetVel(SGPhysicsBody* body, float* x, float* y)
{
    if(body == NULL)
        return;
    if(x == NULL && y == NULL)
        return;

    float t;
    if(x == NULL)
        x = &t;
    else if(y == NULL)
        y = &t;

    if(psgmPhysicsBodyGetVelocity != NULL)
        psgmPhysicsBodyGetVelocity(body->handle, x, y);
}

void SG_CALL sgPhysicsBodySetVelX(SGPhysicsBody* body, float x)
{
    if(body == NULL)
        return;

    float y = sgPhysicsBodyGetVelY(body);
    sgPhysicsBodySetVel(body, x, y);
}
float SG_CALL sgPhysicsBodyGetVelX(SGPhysicsBody* body)
{
    if(body == NULL)
        return SG_NAN;

    float x;
    sgPhysicsBodyGetVel(body, &x, NULL);
    return x;
}
void SG_CALL sgPhysicsBodySetVelY(SGPhysicsBody* body, float y)
{
    if(body == NULL)
        return;

    float x = sgPhysicsBodyGetVelX(body);
    sgPhysicsBodySetVel(body, x, y);
}
float SG_CALL sgPhysicsBodyGetVelY(SGPhysicsBody* body)
{
    if(body == NULL)
        return SG_NAN;

    float y;
    sgPhysicsBodyGetVel(body, NULL, &y);
    return y;
}

void SG_CALL sgPhysicsBodySetAngVelRads(SGPhysicsBody* body, float rads)
{
    if(body == NULL)
        return;

    if(psgmPhysicsBodySetAngularVelocity != NULL)
        psgmPhysicsBodySetAngularVelocity(body->handle, rads);
}
float SG_CALL sgPhysicsBodyGetAngVelRads(SGPhysicsBody* body)
{
    if(body == NULL)
        return SG_NAN;

    float rads;
    if(psgmPhysicsBodyGetAngularVelocity != NULL)
        psgmPhysicsBodyGetAngularVelocity(body->handle, &rads);
    return rads;
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
    if(body == NULL)
        return;

    if(psgmPhysicsBodySetMass != NULL)
        psgmPhysicsBodySetMass(body->handle, mass);
}
float SG_CALL sgPhysicsBodyGetMass(SGPhysicsBody* body)
{
    if(body == NULL)
        return SG_NAN;

    float mass;
    if(psgmPhysicsBodyGetMass != NULL)
        psgmPhysicsBodyGetMass(body->handle, &mass);
    return mass;
}

void SG_CALL sgPhysicsBodySetMoment(SGPhysicsBody* body, float moment)
{
    if(body == NULL)
        return;

    if(psgmPhysicsBodySetMoment != NULL)
        psgmPhysicsBodySetMoment(body->handle, moment);
}
float SG_CALL sgPhysicsBodyGetMoment(SGPhysicsBody* body)
{
    if(body == NULL)
        return SG_NAN;

    float moment;
    if(psgmPhysicsBodyGetMoment != NULL)
        psgmPhysicsBodyGetMoment(body->handle, &moment);
    return moment;
}

void SG_CALL sgPhysicsBodyApplyImpulse(SGPhysicsBody* body, float jx, float jy, float rx, float ry)
{
	if(!body)
		return;

	if(psgmPhysicsBodyApplyImpulse)
		psgmPhysicsBodyApplyImpulse(body->handle, jx, jy, rx, ry);
}
void SG_CALL sgPhysicsBodyApplyForce(SGPhysicsBody* body, float jx, float jy, float rx, float ry)
{
	if(!body)
		return;

	if(psgmPhysicsBodyApplyForce)
		psgmPhysicsBodyApplyForce(body->handle, jx, jy, rx, ry);
}
