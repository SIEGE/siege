#ifndef __SIEGE_PHYSICS_COLLISION_H__
#define __SIEGE_PHYSICS_COLLISION_H__

#include "../common.h"

typedef struct SGCollisionPoint
{
    float xpos;
    float ypos;
    float xvel;
    float yvel;
    float xnorm;
    float ynorm;
    float separation;
    float friction;
    float restitution;
} SGCollisionPoint;

typedef struct SGCollisionResult
{
    float xpos;
    float ypos;
    float xvel;
    float yvel;
    float xnorm;
    float ynorm;
} SGCollisionResult;

#endif // __SIEGE_PHYSICS_COLLISION_H__
