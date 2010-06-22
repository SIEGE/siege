#ifndef __SIEGE_PHYSICS_BODY_H__
#define __SIEGE_PHYSICS_BODY_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgmPhysicsBodyCreate(void** body, SGenum type);
    SGuint SG_EXPORT sgmPhysicsBodyDestroy(void* body);

    SGuint SG_EXPORT sgmPhysicsBodySetMass(void* body, float mass);
    SGuint SG_EXPORT sgmPhysicsBodyGetMass(void* body, float* mass);
    SGuint SG_EXPORT sgmPhysicsBodySetMoment(void* body, float moment);
    SGuint SG_EXPORT sgmPhysicsBodyGetMoment(void* body, float* moment);
    SGuint SG_EXPORT sgmPhysicsBodySetPosition(void* body, float x, float y);
    SGuint SG_EXPORT sgmPhysicsBodyGetPosition(void* body, float* x, float* y);
    SGuint SG_EXPORT sgmPhysicsBodySetVelocity(void* body, float x, float y);
    SGuint SG_EXPORT sgmPhysicsBodyGetVelocity(void* body, float* x, float* y);
    SGuint SG_EXPORT sgmPhysicsBodySetForce(void* body, float x, float y);
    SGuint SG_EXPORT sgmPhysicsBodyGetForce(void* body, float* x, float* y);
    SGuint SG_EXPORT sgmPhysicsBodySetAngle(void* body, float angle);
    SGuint SG_EXPORT sgmPhysicsBodyGetAngle(void* body, float* angle);
    SGuint SG_EXPORT sgmPhysicsBodySetAngularVelocity(void* body, float angvel);
    SGuint SG_EXPORT sgmPhysicsBodyGetAngularVelocity(void* body, float* angvel);
    SGuint SG_EXPORT sgmPhysicsBodySetTorque(void* body, float torque);
    SGuint SG_EXPORT sgmPhysicsBodyGetTorque(void* body, float* torque);
    SGuint SG_EXPORT sgmPhysicsBodySetData(void* body, void* data);
    SGuint SG_EXPORT sgmPhysicsBodyGetData(void* body, void** data);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_PHYSICS_BODY_H__
