#ifndef __SIEGE_PHYSICS_SPACE_H__
#define __SIEGE_PHYSICS_SPACE_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGPhysicsSpace
{
    void* handle;
} SGPhysicsSpace;

#ifdef SG_BUILD_LIBRARY
SGPhysicsSpace* _sg_physSpaceMain;
#endif // SG_BUILD_LIBRARY

SGbool SG_EXPORT _sgPhysicsSpaceInit(void);
SGbool SG_EXPORT _sgPhysicsSpaceDeinit(void);

SGPhysicsSpace* SG_EXPORT sgPhysicsSpaceCreate(void);
void SG_EXPORT sgPhysicsSpaceDestroy(SGPhysicsSpace* space);

void SG_EXPORT sgPhysicsSpaceStep(SGPhysicsSpace* space, float time);
void SG_EXPORT sgPhysicsSpaceSetGravity(SGPhysicsSpace* space, float x, float y);
//void SG_EXPORT sgPhysicsSpaceGetGravity(SGPhysicsSpace* space, float* x, float* y);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_PHYSICS_SPACE_H__