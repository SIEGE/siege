#ifndef __SIEGE_MODULES_PHYSICS_H__
#define __SIEGE_MODULES_PHYSICS_H__
#include "../common.h"
#include "../util/link.h"
#include <stddef.h>


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGModulePhysics
{
    /// Physics
    SGuint SG_EXPORT (*sgmPhysicsBodyCreate)(void** cbody, SGuint type);
    SGuint SG_EXPORT (*sgmPhysicsBodyDestroy)(void* cbody);

    SGuint SG_EXPORT (*sgmPhysicsBodySetMass)(void* cbody, float mass);
    SGuint SG_EXPORT (*sgmPhysicsBodyGetMass)(void* cbody, float* mass);
    SGuint SG_EXPORT (*sgmPhysicsBodySetMoment)(void* cbody, float moment);
    SGuint SG_EXPORT (*sgmPhysicsBodyGetMoment)(void* cbody, float* moment);
    SGuint SG_EXPORT (*sgmPhysicsBodySetPosition)(void* cbody, float x, float y);
    SGuint SG_EXPORT (*sgmPhysicsBodyGetPosition)(void* cbody, float* x, float* y);
    SGuint SG_EXPORT (*sgmPhysicsBodySetVelocity)(void* cbody, float x, float y);
    SGuint SG_EXPORT (*sgmPhysicsBodyGetVelocity)(void* cbody, float* x, float* y);
    SGuint SG_EXPORT (*sgmPhysicsBodySetForce)(void* cbody, float x, float y);
    SGuint SG_EXPORT (*sgmPhysicsBodyGetForce)(void* cbody, float* x, float* y);
    SGuint SG_EXPORT (*sgmPhysicsBodySetAngle)(void* cbody, float angle);
    SGuint SG_EXPORT (*sgmPhysicsBodyGetAngle)(void* cbody, float* angle);
    SGuint SG_EXPORT (*sgmPhysicsBodySetAngularVelocity)(void* cbody, float angvel);
    SGuint SG_EXPORT (*sgmPhysicsBodyGetAngularVelocity)(void* cbody, float* angvel);
    SGuint SG_EXPORT (*sgmPhysicsBodySetTorque)(void* cbody, float torque);
    SGuint SG_EXPORT (*sgmPhysicsBodyGetTorque)(void* cbody, float* torque);
    SGuint SG_EXPORT (*sgmPhysicsBodySetData)(void* cbody, void* data);
    SGuint SG_EXPORT (*sgmPhysicsBodyGetData)(void* cbody, void** data);

    // constraint

    SGuint SG_EXPORT (*sgmPhysicsShapeCreate)(void** shape, void* cbody, float xoffset, float yoffset, SGuint type, SGuint numverts, float* vertices);
    SGuint SG_EXPORT (*sgmPhysicsShapeDestroy)(void* shape);

    SGuint SG_EXPORT (*sgmPhysicsSpaceCreate)(void** space);
    SGuint SG_EXPORT (*sgmPhysicsSpaceDestroy)(void* space);
    SGuint SG_EXPORT (*sgmPhysicsSpaceStep)(void* space, float time);
    SGuint SG_EXPORT (*sgmPhysicsSpaceSetGravity)(void* space, float x, float y);

    SGuint SG_EXPORT (*sgmPhysicsSpaceAddShape)(void* space, void* shape);
    SGuint SG_EXPORT (*sgmPhysicsSpaceRemoveShape)(void* space, void* shape);
    //SGuint SG_EXPORT (*sgmPhysicsSpaceAddStaticShape)(void* space, void* shape);
    //SGuint SG_EXPORT (*sgmPhysicsSpaceRemoveStaticShape)(void* space, void* shape);
    SGuint SG_EXPORT (*sgmPhysicsSpaceAddBody)(void* space, void* cbody);
    SGuint SG_EXPORT (*sgmPhysicsSpaceRemoveBody)(void* space, void* cbody);
    SGuint SG_EXPORT (*sgmPhysicsSpaceAddConstraint)(void* space, void* constraint);
    SGuint SG_EXPORT (*sgmPhysicsSpaceRemoveConstraint)(void* space, void* constraint);


    SGuint SG_EXPORT (*sgmPhysicsBodyWorldToLocal_TEST)(void* cbody, float* x, float* y);
    SGuint SG_EXPORT (*sgmPhysicsBodyLocalToWorld_TEST)(void* cbody, float* x, float* y);
    SGuint SG_EXPORT (*sgmPhysicsShapeGetBB_TEST)(void* shape, float* t, float* l, float* b, float* r);
    SGuint SG_EXPORT (*sgmPhysicsShapeGetPoints_TEST)(void* shape, SGuint* pnum, float** points);
    SGuint SG_EXPORT (*sgmPhysicsShapeFreePoints_TEST)(float* points);
} SGModulePhysics;

#ifdef SG_BUILD_LIBRARY
SGModulePhysics _sg_modPhysics;
#endif // SG_BUILD_LIBRARY

void SG_EXPORT _sgModuleLoadPhysics(SGLibrary* lib);

SGModulePhysics* SG_EXPORT sgModuleGetPhysics(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_MODULES_PHYSICS_H__
