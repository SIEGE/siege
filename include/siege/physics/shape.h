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

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGPhysicsShape
{
    void* handle;
    SGPhysicsBody* body;
    void* data;

    SGenum type;

    float x;
    float y;
    size_t numverts;
    float* verts;
} SGPhysicsShape;

SGPhysicsShape* SG_CALL sgPhysicsShapeCreate(SGPhysicsBody* body, SGenum type);
SGPhysicsShape* SG_CALL sgPhysicsShapeCreateSegment(SGPhysicsBody* body, float x1, float y1, float x2, float y2, float width);
SGPhysicsShape* SG_CALL sgPhysicsShapeCreatePoly(SGPhysicsBody* body, float x, float y, float* verts, size_t numverts);
SGPhysicsShape* SG_CALL sgPhysicsShapeCreateCircle(SGPhysicsBody* body, float x, float y, float r1, float r2);
void SG_CALL sgPhysicsShapeDestroy(SGPhysicsShape* shape);

void SG_CALL sgPhysicsShapeSetGroup(SGPhysicsShape* shape, SGuint group);
SGuint SG_CALL sgPhysicsShapeGetGroup(SGPhysicsShape* shape);
void SG_CALL sgPhysicsShapeSetFriction(SGPhysicsShape* shape, float friction);
float SG_CALL sgPhysicsShapeGetFriction(SGPhysicsShape* shape);
void SG_CALL sgPhysicsShapeSetRestitution(SGPhysicsShape* shape, float restitution);
float SG_CALL sgPhysicsShapeGetRestitution(SGPhysicsShape* shape);
void SG_CALL sgPhysicsShapeSetData(SGPhysicsShape* shape, void* data);
void* SG_CALL sgPhysicsShapeGetData(SGPhysicsShape* shape);

float SG_CALL sgPhysicsShapeGetAreaS(SGPhysicsShape* shape);
float SG_CALL sgPhysicsShapeGetAreaU(SGPhysicsShape* shape);
float SG_CALL sgPhysicsShapeGetMass(SGPhysicsShape* shape, float density);
float SG_CALL sgPhysicsShapeGetMomentMass(SGPhysicsShape* shape, float mass);
float SG_CALL sgPhysicsShapeGetMomentDensity(SGPhysicsShape* shape, float density);

void SG_CALL sgPhysicsShapeGetBBox(SGPhysicsShape* shape, float* t, float* l, float* b, float* r);
void SG_CALL sgPhysicsShapeDrawDBG(SGPhysicsShape* shape);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_PHYSICS_SHAPE_H__
