/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "COPYING.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#include "common.h"

#include <stdio.h>
#include <stdlib.h>

SGenum SG_EXPORT sgmPhysicsShapeCreate(void** shape, void* body, float xoffset, float yoffset, SGenum type, size_t numverts, float* verts)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE

    cpVect offset = {xoffset, yoffset};
    cpVect a;
    cpVect b;

    int i;
    cpVect* nvect;
    switch(type)
    {
        case SG_SHAPE_SEGMENT: // vertices: [x1, y1, x2, y2, width]
            a = (cpVect) {verts[0] + xoffset, verts[1] + yoffset};
            b = (cpVect) {verts[2] + xoffset, verts[3] + yoffset};
            *shape = cpSegmentShapeNew(body, a, b, verts[4]);
            break;

        case SG_SHAPE_POLYGON: // vertices: [x1, y1, x2, y2, ..., xn, yn]
            // assert(sizeof(cpVect) == sizeof(float)*2);
            nvect = malloc(numverts * sizeof(cpFloat) * 2);
            for(i = 0; i < numverts; i++)
                nvect[i] = (cpVect) { verts[2*i], verts[2*i+1] };
            *shape = cpPolyShapeNew(body, numverts, nvect, offset);
            free(nvect);
            break;

        case SG_SHAPE_CIRCLE: // vertices: [radius]
            *shape = cpCircleShapeNew(body, verts[0], offset);
            break;

        default:
            return SG_OK; // SG_INVALID_ENUM
    }

    return SG_OK;
}
SGenum SG_EXPORT sgmPhysicsShapeDestroy(void* shape)
{
    if(shape == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpShapeFree(shape);
    return SG_OK;
}

SGenum SG_EXPORT SG_FPTR(sgmPhysicsShapeSetGroup)(void* shape, SGuint group)
{
    if(!shape)
        return SG_OK; // SG_INVALID_VALUE
    cpShapeSetGroup(shape, group);
    return SG_OK;
}
SGenum SG_EXPORT SG_FPTR(sgmPhysicsShapeGetGroup)(void* shape, SGuint* group)
{
    if(!shape)
        return SG_OK; // SG_INVALID_VALUE
    *group = cpShapeGetGroup(shape);
    return SG_OK;
}
SGenum SG_EXPORT sgmPhysicsShapeSetFriction(void* shape, float friction)
{
    if(shape == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpShapeSetFriction(shape, friction);
    return SG_OK;
}
SGenum SG_EXPORT sgmPhysicsShapeGetFriction(void* shape, float* friction)
{
    if(shape == NULL)
        return SG_OK; // SG_INVALID_VALUE
    *friction = cpShapeGetFriction(shape);
    return SG_OK;
}
SGenum SG_EXPORT sgmPhysicsShapeSetRestitution(void* shape, float restitution)
{
    if(shape == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpShapeSetElasticity(shape, restitution);
    return SG_OK;
}
SGenum SG_EXPORT sgmPhysicsShapeGetRestitution(void* shape, float* restitution)
{
    if(shape == NULL)
        return SG_OK; // SG_INVALID_VALUE
    *restitution = cpShapeGetElasticity(shape);
    return SG_OK;
}
SGenum SG_EXPORT sgmPhysicsShapeSetData(void* shape, void* data)
{
    if(shape == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpShapeSetUserData(shape, data);
    return SG_OK;
}
SGenum SG_EXPORT sgmPhysicsShapeGetData(void* shape, void** data)
{
    if(shape == NULL)
        return SG_OK; // SG_INVALID_VALUE
    *data = cpShapeGetUserData(shape);
    return SG_OK;
}
SGenum SG_EXPORT sgmPhysicsShapeGetBBox(void* shape, float* t, float* l, float* b, float* r)
{
    if(shape == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpBB bb = cpShapeGetBB(shape);
    *t = bb.t;
    *l = bb.l;
    *b = bb.b;
    *r = bb.r;
    return SG_OK;
}
