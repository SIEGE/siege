#ifndef __SIEGE_MODULE_PHYSICS_COMPAT_H__

#include <chipmunk/chipmunk.h>

#if CP_VERSION_MAJOR < 7
#define cpBodySetPosition   cpBodySetPos
#define cpBodyGetPosition   cpBodyGetPos
#define cpBodySetVelocity   cpBodySetVel
#define cpBodyGetVelocity   cpBodyGetVel

#define cpBodyWorldToLocal  cpBodyWorld2Local
#define cpBodyLocalToWorld  cpBodyLocal2World

#define cpPolyShapeNewRaw(body, count, verts, radius)   cpPolyShapeNew(body, count, verts, cpvzero)

#define cpArbiterTotalImpulse   cpArbiterTotalImpulseWithFriction

#define cpArbiterGetNormal(arb)  cpArbiterGetNormal(arb, 0)
#define cpArbiterGetPointA  cpArbiterGetPoint
#define cpArbiterGetPointB  cpArbiterGetPoint

#define cpSpaceAddShape(space, shape)       do {    \
                                                cpShape* _tmp_shape = (shape);                  \
                                                if(cpBodyGetType(cpShapeGetBody(_tmp_shape)) == CP_BODY_TYPE_STATIC)    \
                                                    cpSpaceAddStaticShape(space, _tmp_shape);   \
                                                else cpSpaceAddShape(space, _tmp_shape);        \
                                            } while(0)
#define cpSpaceRemoveShape(space, shape)    do {    \
                                                cpShape* _tmp_shape = (shape);                  \
                                                if(cpBodyGetType(cpShapeGetBody(_tmp_shape)) == CP_BODY_TYPE_STATIC)    \
                                                    cpSpaceRemoveStaticShape(space, _tmp_shape);   \
                                                else cpSpaceRemoveShape(space, _tmp_shape);        \
                                            } while(0)
#endif /* CP_VERSION_MAJOR < 7 */

#endif /* __SIEGE_MODULE_PHYSICS_COMPAT_H__ */
