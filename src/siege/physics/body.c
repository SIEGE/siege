#define SG_BUILD_LIBRARY
#include <siege/physics/body.h>
#include <siege/modules/physics.h>

#include <stdlib.h>
#include <math.h>

SGPhysicsBody* SG_EXPORT sgPhysicsBodyCreate(SGPhysicsSpace* space, SGenum type)
{
    SGPhysicsBody* body = malloc(sizeof(SGPhysicsBody));
    if(body == NULL)
        return NULL;

    if(space == NULL)
        space = _sg_physSpaceMain;

    body->space = space;
    body->type = type;
    body->data = NULL;

    if(_sg_modPhysics.sgmPhysicsBodyCreate != NULL)
        _sg_modPhysics.sgmPhysicsBodyCreate(&body->handle, body->type);
    if(_sg_modPhysics.sgmPhysicsBodySetData != NULL)
        _sg_modPhysics.sgmPhysicsBodySetData(body->handle, body);

    if(_sg_modPhysics.sgmPhysicsSpaceAddBody != NULL)
        _sg_modPhysics.sgmPhysicsSpaceAddBody(space->handle, body->handle);

    return body;
}
void SG_EXPORT sgPhysicsBodyDestroy(SGPhysicsBody* body)
{
    if(body == NULL)
        return;

    /*if(body->space != NULL)
    {
        if(_sg_modPhysics.sgmPhysicsSpaceRemoveBody != NULL)
            _sg_modPhysics.sgmPhysicsSpaceRemoveBody(body->space->handle, body->handle);
    }*/

    if(_sg_modPhysics.sgmPhysicsBodyDestroy != NULL)
        _sg_modPhysics.sgmPhysicsBodyDestroy(body->handle);
}

void SG_EXPORT sgPhysicsBodySetData(SGPhysicsBody* body, void* data)
{
    if(body == NULL)
        return;

    body->data = data;
}
void* SG_EXPORT sgPhysicsBodyGetData(SGPhysicsBody* body)
{
    if(body == NULL)
        return NULL;

    return body->data;
}

void SG_EXPORT sgPhysicsBodySetPos(SGPhysicsBody* body, float x, float y)
{
    if(body == NULL)
        return;

    if(_sg_modPhysics.sgmPhysicsBodySetPosition != NULL)
        _sg_modPhysics.sgmPhysicsBodySetPosition(body->handle, x, y);
}
void SG_EXPORT sgPhysicsBodyGetPos(SGPhysicsBody* body, float* x, float* y)
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

    if(_sg_modPhysics.sgmPhysicsBodyGetPosition != NULL)
        _sg_modPhysics.sgmPhysicsBodyGetPosition(body->handle, x, y);
}

void SG_EXPORT sgPhysicsBodySetPosX(SGPhysicsBody* body, float x)
{
    if(body == NULL)
        return;

    float y = sgPhysicsBodyGetPosY(body);
    sgPhysicsBodySetPos(body, x, y);
}
float SG_EXPORT sgPhysicsBodyGetPosX(SGPhysicsBody* body)
{
    if(body == NULL)
        return SG_NAN;

    float x;
    sgPhysicsBodyGetPos(body, &x, NULL);
    return x;
}
void SG_EXPORT sgPhysicsBodySetPosY(SGPhysicsBody* body, float y)
{
    if(body == NULL)
        return;

    float x = sgPhysicsBodyGetPosX(body);
    sgPhysicsBodySetPos(body, x, y);
}
float SG_EXPORT sgPhysicsBodyGetPosY(SGPhysicsBody* body)
{
    if(body == NULL)
        return SG_NAN;

    float y;
    sgPhysicsBodyGetPos(body, NULL, &y);
    return y;
}

void SG_EXPORT sgPhysicsBodySetAngleRads(SGPhysicsBody* body, float rads)
{
    if(body == NULL)
        return;

    if(_sg_modPhysics.sgmPhysicsBodySetAngle != NULL)
        _sg_modPhysics.sgmPhysicsBodySetAngle(body->handle, rads);
}
float SG_EXPORT sgPhysicsBodyGetAngleRads(SGPhysicsBody* body)
{
    if(body == NULL)
        return SG_NAN;

    float rads;
    if(_sg_modPhysics.sgmPhysicsBodyGetAngle != NULL)
        _sg_modPhysics.sgmPhysicsBodyGetAngle(body->handle, &rads);
    return rads;
}
void SG_EXPORT sgPhysicsBodySetAngleDegs(SGPhysicsBody* body, float degs)
{
    sgPhysicsBodySetAngleRads(body, degs * M_PI / 180.0);
}
float SG_EXPORT sgPhysicsBodyGetAngleDegs(SGPhysicsBody* body)
{
    return sgPhysicsBodyGetAngleRads(body) * 180.0 / M_PI;
}

void SG_EXPORT sgPhysicsBodySetVel(SGPhysicsBody* body, float x, float y)
{
    if(body == NULL)
        return;

    if(_sg_modPhysics.sgmPhysicsBodySetVelocity != NULL)
        _sg_modPhysics.sgmPhysicsBodySetVelocity(body->handle, x, y);
}
void SG_EXPORT sgPhysicsBodyGetVel(SGPhysicsBody* body, float* x, float* y)
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

    if(_sg_modPhysics.sgmPhysicsBodyGetVelocity != NULL)
        _sg_modPhysics.sgmPhysicsBodyGetVelocity(body->handle, x, y);
}

void SG_EXPORT sgPhysicsBodySetVelX(SGPhysicsBody* body, float x)
{
    if(body == NULL)
        return;

    float y = sgPhysicsBodyGetVelY(body);
    sgPhysicsBodySetVel(body, x, y);
}
float SG_EXPORT sgPhysicsBodyGetVelX(SGPhysicsBody* body)
{
    if(body == NULL)
        return SG_NAN;

    float x;
    sgPhysicsBodyGetVel(body, &x, NULL);
    return x;
}
void SG_EXPORT sgPhysicsBodySetVelY(SGPhysicsBody* body, float y)
{
    if(body == NULL)
        return;

    float x = sgPhysicsBodyGetVelX(body);
    sgPhysicsBodySetVel(body, x, y);
}
float SG_EXPORT sgPhysicsBodyGetVelY(SGPhysicsBody* body)
{
    if(body == NULL)
        return SG_NAN;

    float y;
    sgPhysicsBodyGetVel(body, NULL, &y);
    return y;
}

void SG_EXPORT sgPhysicsBodySetAngVelRads(SGPhysicsBody* body, float rads)
{
    if(body == NULL)
        return;

    if(_sg_modPhysics.sgmPhysicsBodySetAngularVelocity != NULL)
        _sg_modPhysics.sgmPhysicsBodySetAngularVelocity(body->handle, rads);
}
float SG_EXPORT sgPhysicsBodyGetAngVelRads(SGPhysicsBody* body)
{
    if(body == NULL)
        return SG_NAN;

    float rads;
    if(_sg_modPhysics.sgmPhysicsBodyGetAngularVelocity != NULL)
        _sg_modPhysics.sgmPhysicsBodyGetAngularVelocity(body->handle, &rads);
    return rads;
}
void SG_EXPORT sgPhysicsBodySetAngVelDegs(SGPhysicsBody* body, float degs)
{
    sgPhysicsBodySetAngVelRads(body, degs * M_PI / 180.0);
}
float SG_EXPORT sgPhysicsBodyGetAngVelDegs(SGPhysicsBody* body)
{
    return sgPhysicsBodyGetAngVelRads(body) * 180.0 / M_PI;
}

void SG_EXPORT sgPhysicsBodySetMass(SGPhysicsBody* body, float mass)
{
    if(body == NULL)
        return;

    if(_sg_modPhysics.sgmPhysicsBodySetMass != NULL)
        _sg_modPhysics.sgmPhysicsBodySetMass(body->handle, mass);
}
float SG_EXPORT sgPhysicsBodyGetMass(SGPhysicsBody* body)
{
    if(body == NULL)
        return SG_NAN;

    float mass;
    if(_sg_modPhysics.sgmPhysicsBodyGetMass != NULL)
        _sg_modPhysics.sgmPhysicsBodyGetMass(body->handle, &mass);
    return mass;
}

void SG_EXPORT sgPhysicsBodySetMoment(SGPhysicsBody* body, float moment)
{
    if(body == NULL)
        return;

    if(_sg_modPhysics.sgmPhysicsBodySetMoment != NULL)
        _sg_modPhysics.sgmPhysicsBodySetMoment(body->handle, moment);
}
float SG_EXPORT sgPhysicsBodyGetMoment(SGPhysicsBody* body)
{
    if(body == NULL)
        return SG_NAN;

    float moment;
    if(_sg_modPhysics.sgmPhysicsBodyGetMoment != NULL)
        _sg_modPhysics.sgmPhysicsBodyGetMoment(body->handle, &moment);
    return moment;
}

