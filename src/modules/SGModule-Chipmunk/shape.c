#include "main.h"
#include "shape.h"

#include <stdio.h>
#include <stdlib.h>

SGuint SG_EXPORT sgmPhysicsShapeCreate(void** shape, void* body, float xoffset, float yoffset, SGenum type, SGuint numverts, float* vertices)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpShape** cshape = (cpShape**)shape;

    cpVect offset = (cpVect) {xoffset, yoffset};
    cpVect a;
    cpVect b;

    int i;
    cpVect* nvect;
    switch(type)
    {
        case SG_PHYSICS_SHAPE_SEGMENT: // vertices: [x1, y1, x2, y2, width]
            a = (cpVect) {vertices[0] + xoffset, vertices[1] + yoffset};
            b = (cpVect) {vertices[2] + xoffset, vertices[3] + yoffset};
            *shape = cpSegmentShapeNew(body, a, b, vertices[4]);
            break;

        case SG_PHYSICS_SHAPE_POLYGON: // vertices: [x1, y1, x2, y2, ..., xn, yn]
            // assert(sizeof(cpVect) == sizeof(float)*2);
            nvect = malloc(numverts * sizeof(cpFloat) * 2);
            for(i = 0; i < numverts; i++)
                nvect[i] = (cpVect) { vertices[2*i], vertices[2*i+1] };
            *shape = cpPolyShapeNew(body, numverts, nvect, offset);
            free(nvect);
            break;

        case SG_PHYSICS_SHAPE_CIRCLE: // vertices: [radius]
            *shape = cpCircleShapeNew(body, vertices[0], offset);
            break;

        default:
            return SG_OK; // SG_INVALID_ENUM
    }

    (*cshape)->e = 0.25; // TEST
    (*cshape)->u = 0.75;
    return SG_OK;
}
SGuint SG_EXPORT sgmPhysicsShapeDestroy(void* shape)
{
    if(shape == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpShapeFree(shape);
    return SG_OK;
}
