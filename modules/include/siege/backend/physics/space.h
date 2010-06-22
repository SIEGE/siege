#ifndef __SIEGE_PHYSICS_SPACE_H__
#define __SIEGE_PHYSICS_SPACE_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgPhysicsSpaceCreate(void** space);
    SGuint SG_EXPORT sgPhysicsSpaceDestroy(void* space);
    SGuint SG_EXPORT sgPhysicsSpaceStep(void* space, float time);
    SGuint SG_EXPORT sgPhysicsSpaceSetGravity(void* space, float x, float y);
    //SGuint SG_EXPORT sgPhysicsSpaceGetGravity(void* space, float* x, float* y);

    SGuint SG_EXPORT sgPhysicsSpaceAddShape(void* space, void* shape);
    SGuint SG_EXPORT sgPhysicsSpaceRemoveShape(void* space, void* shape);
    //SGuint SG_EXPORT sgPhysicsSpaceAddStaticShape(void* space, void* shape);
    //SGuint SG_EXPORT sgPhysicsSpaceRemoveStaticShape(void* space, void* shape);
    SGuint SG_EXPORT sgPhysicsSpaceAddBody(void* space, void* body);
    SGuint SG_EXPORT sgPhysicsSpaceRemoveBody(void* space, void* body);
    SGuint SG_EXPORT sgPhysicsSpaceAddConstraint(void* space, void* constraint);
    SGuint SG_EXPORT sgPhysicsSpaceRemoveConstraint(void* space, void* constraint);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_PHYSICS_SPACE_H__
