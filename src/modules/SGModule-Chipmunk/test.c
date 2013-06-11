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

SGenum SG_CALL sgmPhysicsBodyWorldToLocal_TEST(void* body, float* x, float* y)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpVect vect = cpBodyWorld2Local(body, (cpVect) {*x, *y});
    *x = vect.x;
    *y = vect.y;
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsBodyLocalToWorld_TEST(void* body, float* x, float* y)
{
    if(body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpVect vect = cpBodyLocal2World(body, (cpVect) {*x, *y});
    *x = vect.x;
    *y = vect.y;
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsShapeGetPoints_TEST(void* shape, SGuint* pnum, float** points)
{
    if(shape == NULL)
        return SG_OK; // SG_INVALID_VALUE
    *pnum = 0;
    *points = NULL;
    /*cpShape* cshape = (cpShape*)shape;

    SGuint i;
    cpVect vect;
    switch(cshape->klass->type)
    {
        case CP_CIRCLE_SHAPE:
            *pnum = 1;
            *points = malloc(*pnum * sizeof(float) * 2 + sizeof(float));

            vect = cpCircleShapeGetOffset(shape);
            (*points)[0] = vect.x;
            (*points)[1] = vect.y;
            (*points)[2] = cpCircleShapeGetRadius(shape);
            break;
        case CP_SEGMENT_SHAPE:
            *pnum = 2;
            *points = malloc(*pnum * sizeof(float) * 2 + sizeof(float));

            vect = cpSegmentShapeGetA(shape);
            (*points)[0] = vect.x;
            (*points)[1] = vect.y;
            vect = cpSegmentShapeGetB(shape);
            (*points)[2] = vect.x;
            (*points)[3] = vect.y;
            (*points)[4] = cpSegmentShapeGetRadius(shape);
            break;
        case CP_POLY_SHAPE:
            *pnum = cpPolyShapeGetNumVerts(shape);
            *points = malloc(*pnum * sizeof(float) * 2);

            for(i = 0; i < *pnum; i++)
            {
                vect = cpPolyShapeGetVert(shape, i);
                (*points)[2*i] = vect.x;
                (*points)[2*i+1] = vect.y;
            }
            break;

        default:
            break;
    }*/
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsShapeFreePoints_TEST(float* points)
{
    free(points);
    return SG_OK;
}
