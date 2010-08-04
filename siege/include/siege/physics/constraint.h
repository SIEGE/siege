#ifndef __SIEGE_PHYSICS_CONSTRAINT_H__
#define __SIEGE_PHYSICS_CONSTRAINT_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGPhysicsConstraint
{
    void* handle;
} SGPhysicsConstraint;

void SG_EXPORT sgPhysicsConstraintDestroy(SGPhysicsConstraint* constraint);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_PHYSICS_CONSTRAINT_H__
