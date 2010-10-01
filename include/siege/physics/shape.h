/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "license.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
*/

#ifndef __SIEGE_PHYSICS_SHAPE_H__
#define __SIEGE_PHYSICS_SHAPE_H__

#include "../common.h"
#include "body.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGPhysicsShape
{
    void* handle;
    SGPhysicsBody* body;

    SGenum type;

    float x;
    float y;
    size_t numverts;
    float* verts;
} SGPhysicsShape;

SGPhysicsShape* SG_EXPORT sgPhysicsShapeCreate(SGPhysicsBody* body, SGenum type);
SGPhysicsShape* SG_EXPORT sgPhysicsShapeCreateSegment(SGPhysicsBody* body, float x1, float y1, float x2, float y2, float width);
SGPhysicsShape* SG_EXPORT sgPhysicsShapeCreatePoly(SGPhysicsBody* body, float x, float y, float* verts, size_t numverts);
SGPhysicsShape* SG_EXPORT sgPhysicsShapeCreateCircle(SGPhysicsBody* body, float x, float y, float r1, float r2);
void SG_EXPORT sgPhysicsShapeDestroy(SGPhysicsShape* shape);

float SG_EXPORT sgPhysicsShapeGetAreaS(SGPhysicsShape* shape);
float SG_EXPORT sgPhysicsShapeGetAreaU(SGPhysicsShape* shape);
float SG_EXPORT sgPhysicsShapeGetMass(SGPhysicsShape* shape, float density);
float SG_EXPORT sgPhysicsShapeGetMomentMass(SGPhysicsShape* shape, float mass);
float SG_EXPORT sgPhysicsShapeGetMomentDensity(SGPhysicsShape* shape, float density);

void SG_EXPORT sgPhysicsShapeDrawDBG(SGPhysicsShape* shape);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_PHYSICS_SHAPE_H__
