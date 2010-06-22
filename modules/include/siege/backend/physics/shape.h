#ifndef __SIEGE_PHYSICS_SHAPE_H__
#define __SIEGE_PHYSICS_SHAPE_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgPhysicsShapeCreate(void** shape, void* body, float xoffset, float yoffset, SGenum type, SGuint numverts, float* vertices);
    SGuint SG_EXPORT sgPhysicsShapeDestroy(void* shape);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_PHYSICS_SHAPE_H__
