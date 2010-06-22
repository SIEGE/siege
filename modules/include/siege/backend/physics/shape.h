#ifndef __SIEGE_PHYSICS_SHAPE_H__
#define __SIEGE_PHYSICS_SHAPE_H__

#include "../../common.h"

#ifdef SG_LEGACY_API
#    define sgPhysicsShapeCreate sgmPhysicsShapeCreate
#    define sgPhysicsShapeDestroy sgmPhysicsShapeDestroy
#endif // SG_LEGACY_API

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgmPhysicsShapeCreate(void** shape, void* body, float xoffset, float yoffset, SGenum type, SGuint numverts, float* vertices);
    SGuint SG_EXPORT sgmPhysicsShapeDestroy(void* shape);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_PHYSICS_SHAPE_H__
