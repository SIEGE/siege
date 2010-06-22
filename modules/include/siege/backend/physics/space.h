#ifndef __SIEGE_PHYSICS_SPACE_H__
#define __SIEGE_PHYSICS_SPACE_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgmPhysicsSpaceCreate(void** space);
    SGuint SG_EXPORT sgmPhysicsSpaceDestroy(void* space);
    SGuint SG_EXPORT sgmPhysicsSpaceStep(void* space, float time);
    SGuint SG_EXPORT sgmPhysicsSpaceSetGravity(void* space, float x, float y);
    //SGuint SG_EXPORT sgmPhysicsSpaceGetGravity(void* space, float* x, float* y);

    SGuint SG_EXPORT sgmPhysicsSpaceAddShape(void* space, void* shape);
    SGuint SG_EXPORT sgmPhysicsSpaceRemoveShape(void* space, void* shape);
    //SGuint SG_EXPORT sgmPhysicsSpaceAddStaticShape(void* space, void* shape);
    //SGuint SG_EXPORT sgmPhysicsSpaceRemoveStaticShape(void* space, void* shape);
    SGuint SG_EXPORT sgmPhysicsSpaceAddBody(void* space, void* body);
    SGuint SG_EXPORT sgmPhysicsSpaceRemoveBody(void* space, void* body);
    SGuint SG_EXPORT sgmPhysicsSpaceAddConstraint(void* space, void* constraint);
    SGuint SG_EXPORT sgmPhysicsSpaceRemoveConstraint(void* space, void* constraint);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_PHYSICS_SPACE_H__
