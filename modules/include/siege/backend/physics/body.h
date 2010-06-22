#ifndef __SIEGE_PHYSICS_BODY_H__
#define __SIEGE_PHYSICS_BODY_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgPhysicsBodyCreate(void** body, SGenum type);
    SGuint SG_EXPORT sgPhysicsBodyDestroy(void* body);

    SGuint SG_EXPORT sgPhysicsBodySetMass(void* body, float mass);
    SGuint SG_EXPORT sgPhysicsBodyGetMass(void* body, float* mass);
    SGuint SG_EXPORT sgPhysicsBodySetMoment(void* body, float moment);
    SGuint SG_EXPORT sgPhysicsBodyGetMoment(void* body, float* moment);
    SGuint SG_EXPORT sgPhysicsBodySetPosition(void* body, float x, float y);
    SGuint SG_EXPORT sgPhysicsBodyGetPosition(void* body, float* x, float* y);
    SGuint SG_EXPORT sgPhysicsBodySetVelocity(void* body, float x, float y);
    SGuint SG_EXPORT sgPhysicsBodyGetVelocity(void* body, float* x, float* y);
    SGuint SG_EXPORT sgPhysicsBodySetForce(void* body, float x, float y);
    SGuint SG_EXPORT sgPhysicsBodyGetForce(void* body, float* x, float* y);
    SGuint SG_EXPORT sgPhysicsBodySetAngle(void* body, float angle);
    SGuint SG_EXPORT sgPhysicsBodyGetAngle(void* body, float* angle);
    SGuint SG_EXPORT sgPhysicsBodySetAngularVelocity(void* body, float angvel);
    SGuint SG_EXPORT sgPhysicsBodyGetAngularVelocity(void* body, float* angvel);
    SGuint SG_EXPORT sgPhysicsBodySetTorque(void* body, float torque);
    SGuint SG_EXPORT sgPhysicsBodyGetTorque(void* body, float* torque);
    SGuint SG_EXPORT sgPhysicsBodySetData(void* body, void* data);
    SGuint SG_EXPORT sgPhysicsBodyGetData(void* body, void** data);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_PHYSICS_BODY_H__
