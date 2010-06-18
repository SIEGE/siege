#include "main.h"
#include "body.h"

#include <stdio.h>
#include <stdlib.h>

SGuint SG_EXPORT sgPhysicsBodyCreate(void** body, SGenum type)
{
    cpBody** cbody = (cpBody**)body;
    *cbody = cpBodyNew(1, 1);
    (*cbody)->data = malloc(sizeof(DataExt));
    ((DataExt*)(*cbody)->data)->type = type;
    ((DataExt*)(*cbody)->data)->data = NULL;
    return SG_OK;
}
SGuint SG_EXPORT sgPhysicsBodyDestroy(void* body)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpBody* cbody = (cpBody*)body;
    free(cbody->data);
    cpBodyFree(body);
    return SG_OK;
}

SGuint SG_EXPORT sgPhysicsBodySetMass(void* body, float mass)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpBodySetMass(body, mass);
    return SG_OK;
}
SGuint SG_EXPORT sgPhysicsBodyGetMass(void* body, float* mass)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    *mass = cpBodyGetMass(body);
    return SG_OK;
}
SGuint SG_EXPORT sgPhysicsBodySetMoment(void* body, float moment)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpBodySetMoment(body, moment);
    return SG_OK;
}
SGuint SG_EXPORT sgPhysicsBodyGetMoment(void* body, float* moment)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    *moment = cpBodyGetMoment(body);
    return SG_OK;
}
SGuint SG_EXPORT sgPhysicsBodySetPosition(void* body, float x, float y)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpVect pos = (cpVect) {x, y};
    cpBodySetPos(body, pos);
    return SG_OK;
}
SGuint SG_EXPORT sgPhysicsBodyGetPosition(void* body, float* x, float* y)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpVect pos = cpBodyGetPos(body);
    *x = pos.x;
    *y = pos.y;
    return SG_OK;
}
SGuint SG_EXPORT sgPhysicsBodySetVelocity(void* body, float x, float y)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpVect vel = (cpVect) {x, y};
    cpBodySetVel(body, vel);
    return SG_OK;
}
SGuint SG_EXPORT sgPhysicsBodyGetVelocity(void* body, float* x, float* y)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpVect vel = cpBodyGetVel(body);
    *x = vel.x;
    *y = vel.y;
    return SG_OK;
}
SGuint SG_EXPORT sgPhysicsBodySetForce(void* body, float x, float y)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpVect force = (cpVect) {x, y};
    cpBodySetForce(body, force);
    return SG_OK;
}
SGuint SG_EXPORT sgPhysicsBodyGetForce(void* body, float* x, float* y)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpVect force = cpBodyGetForce(body);
    *x = force.x;
    *y = force.y;
    return SG_OK;
}
SGuint SG_EXPORT sgPhysicsBodySetAngle(void* body, float angle)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpBodySetAngle(body, -angle);
    return SG_OK;
}
SGuint SG_EXPORT sgPhysicsBodyGetAngle(void* body, float* angle)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    *angle = -cpBodyGetAngle(body);
    return SG_OK;
}
SGuint SG_EXPORT sgPhysicsBodySetAngularVelocity(void* body, float angvel)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpBodySetAngVel(body, angvel);
    return SG_OK;
}
SGuint SG_EXPORT sgPhysicsBodyGetAngularVelocity(void* body, float* angvel)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    *angvel = cpBodyGetAngVel(body);
    return SG_OK;
}
SGuint SG_EXPORT sgPhysicsBodySetTorque(void* body, float torque)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpBodySetTorque(body, torque);
    return SG_OK;
}
SGuint SG_EXPORT sgPhysicsBodyGetTorque(void* body, float* torque)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    *torque = cpBodyGetTorque(body);
    return SG_OK;
}
SGuint SG_EXPORT sgPhysicsBodySetData(void* body, void* data)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpBody* cbody = (cpBody*)body;
    ((DataExt*)cbody->data)->data = data;
    return SG_OK;
}
SGuint SG_EXPORT sgPhysicsBodyGetData(void* body, void** data)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpBody* cbody = (cpBody*)body;
    *data = ((DataExt*)cbody->data)->data;
    return SG_OK;
}
