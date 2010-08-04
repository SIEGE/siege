#ifndef __SIEGE_PHYSICS_BODY_H__
#define __SIEGE_PHYSICS_BODY_H__

#include "../common.h"
#include "space.h"
#include "../core/entity.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGPhysicsBody
{
    void* handle;

    SGPhysicsSpace* space;

    SGenum type;
    void* data;
} SGPhysicsBody;

SGPhysicsBody* SG_EXPORT sgPhysicsBodyCreate(SGPhysicsSpace* space, SGenum type);
void SG_EXPORT sgPhysicsBodyDestroy(SGPhysicsBody* body);

void SG_EXPORT sgPhysicsBodySetData(SGPhysicsBody* body, void* data);
void* SG_EXPORT sgPhysicsBodyGetData(SGPhysicsBody* body);

void SG_EXPORT sgPhysicsBodySetPos(SGPhysicsBody* body, float x, float y);
void SG_EXPORT sgPhysicsBodyGetPos(SGPhysicsBody* body, float* x, float* y);

void SG_EXPORT sgPhysicsBodySetPosX(SGPhysicsBody* body, float x);
float SG_EXPORT sgPhysicsBodyGetPosX(SGPhysicsBody* body);
void SG_EXPORT sgPhysicsBodySetPosY(SGPhysicsBody* body, float y);
float SG_EXPORT sgPhysicsBodyGetPosY(SGPhysicsBody* body);

void SG_EXPORT sgPhysicsBodySetAngleRads(SGPhysicsBody* body, float rads);
float SG_EXPORT sgPhysicsBodyGetAngleRads(SGPhysicsBody* body);
void SG_EXPORT sgPhysicsBodySetAngleDegs(SGPhysicsBody* body, float degs);
float SG_EXPORT sgPhysicsBodyGetAngleDegs(SGPhysicsBody* body);

void SG_EXPORT sgPhysicsBodySetVel(SGPhysicsBody* body, float x, float y);
void SG_EXPORT sgPhysicsBodyGetVel(SGPhysicsBody* body, float* x, float* y);

void SG_EXPORT sgPhysicsBodySetVelX(SGPhysicsBody* body, float x);
float SG_EXPORT sgPhysicsBodyGetVelX(SGPhysicsBody* body);
void SG_EXPORT sgPhysicsBodySetVelY(SGPhysicsBody* body, float y);
float SG_EXPORT sgPhysicsBodyGetVelY(SGPhysicsBody* body);

void SG_EXPORT sgPhysicsBodySetAngVelRads(SGPhysicsBody* body, float rads);
float SG_EXPORT sgPhysicsBodyGetAngVelRads(SGPhysicsBody* body);
void SG_EXPORT sgPhysicsBodySetAngVelDegs(SGPhysicsBody* body, float degs);
float SG_EXPORT sgPhysicsBodyGetAngVelDegs(SGPhysicsBody* body);

void SG_EXPORT sgPhysicsBodySetMass(SGPhysicsBody* body, float mass);
float SG_EXPORT sgPhysicsBodyGetMass(SGPhysicsBody* body);

void SG_EXPORT sgPhysicsBodySetMoment(SGPhysicsBody* body, float moment);
float SG_EXPORT sgPhysicsBodyGetMoment(SGPhysicsBody* body);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_PHYSICS_BODY_H__
