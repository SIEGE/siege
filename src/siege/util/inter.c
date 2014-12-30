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

#define SG_BUILD_LIBRARY
#include <siege/util/inter.h>

static SGbool testInter(SGenum type, float den, float u)
{
    switch(type)
    {
    case SG_ITYPE_LINE:     return SG_TRUE; /* denominator is tested outside */
    case SG_ITYPE_SEGMENT:  return SG_IN_RANGE(u, 0.0, 1.0);
    case SG_ITYPE_RAY:      return u >= 0.0;
    }
    return SG_FALSE;
}

float SG_CALL sgIntersectU(SGVec2* inter, SGVec2* u, SGVec2 p1, SGVec2 p2, SGVec2 p3, SGVec2 p4)
{
    SGVec2 p43 = sgVec2Sub(p4, p3);
    SGVec2 p13 = sgVec2Sub(p1, p3);
    SGVec2 p21 = sgVec2Sub(p2, p1);

    //    return a.x * b.y - a.y * b.x;
    float den = sgVec2PDot(p21, p43);
    //float den = p21.x * p43.y - p21.y * p43.x;

    if(!u && !inter)
        return den;

    SGVec2 tu;
    if(!u)
        u = &tu;

    u->x = sgVec2PDot(p43, p13) / den;
    u->y = sgVec2PDot(p21, p13) / den;
    //u->x = (p43.x * p13.y - p43.y * p13.x) / den;
    //u->y = (p21.x * p13.y - p21.y * p13.x) / den;

    if(!inter)
        return den;
    inter->x = p1.x + u->x * p21.x;
    inter->y = p1.y + u->x * p21.y;

    return den;
}
SGbool SG_CALL sgIntersect(SGVec2* inter, SGenum type12, SGVec2 p1, SGVec2 p2, SGenum type34, SGVec2 p3, SGVec2 p4)
{
    SGVec2 u;
    float den = sgIntersectU(inter, &u, p1, p2, p3, p4);
    if(den == 0)
        return SG_FALSE;
    if(!testInter(type12, den, u.x))
        return SG_FALSE;
    if(!testInter(type34, den, u.y))
        return SG_FALSE;
    return SG_TRUE;
}

SGbool SG_CALL sgIntersectLL(SGVec2* inter, SGVec2 p1, SGVec2 p2, SGVec2 p3, SGVec2 p4)
{
    return sgIntersect(inter, SG_ITYPE_LINE, p1, p2, SG_ITYPE_LINE, p3, p4);
}
SGbool SG_CALL sgIntersectLS(SGVec2* inter, SGVec2 p1, SGVec2 p2, SGVec2 p3, SGVec2 p4)
{
    return sgIntersect(inter, SG_ITYPE_LINE, p1, p2, SG_ITYPE_SEGMENT, p3, p4);
}
SGbool SG_CALL sgIntersectLR(SGVec2* inter, SGVec2 p1, SGVec2 p2, SGVec2 p3, SGVec2 p4)
{
    return sgIntersect(inter, SG_ITYPE_LINE, p1, p2, SG_ITYPE_RAY, p3, p4);
}
SGbool SG_CALL sgIntersectSL(SGVec2* inter, SGVec2 p1, SGVec2 p2, SGVec2 p3, SGVec2 p4)
{
    return sgIntersect(inter, SG_ITYPE_SEGMENT, p1, p2, SG_ITYPE_LINE, p3, p4);
}
SGbool SG_CALL sgIntersectSS(SGVec2* inter, SGVec2 p1, SGVec2 p2, SGVec2 p3, SGVec2 p4)
{
    return sgIntersect(inter, SG_ITYPE_SEGMENT, p1, p2, SG_ITYPE_SEGMENT, p3, p4);
}
SGbool SG_CALL sgIntersectSR(SGVec2* inter, SGVec2 p1, SGVec2 p2, SGVec2 p3, SGVec2 p4)
{
    return sgIntersect(inter, SG_ITYPE_SEGMENT, p1, p2, SG_ITYPE_RAY, p3, p4);
}
SGbool SG_CALL sgIntersectRL(SGVec2* inter, SGVec2 p1, SGVec2 p2, SGVec2 p3, SGVec2 p4)
{
    return sgIntersect(inter, SG_ITYPE_RAY, p1, p2, SG_ITYPE_LINE, p3, p4);
}
SGbool SG_CALL sgIntersectRS(SGVec2* inter, SGVec2 p1, SGVec2 p2, SGVec2 p3, SGVec2 p4)
{
    return sgIntersect(inter, SG_ITYPE_RAY, p1, p2, SG_ITYPE_SEGMENT, p3, p4);
}
SGbool SG_CALL sgIntersectRR(SGVec2* inter, SGVec2 p1, SGVec2 p2, SGVec2 p3, SGVec2 p4)
{
    return sgIntersect(inter, SG_ITYPE_RAY, p1, p2, SG_ITYPE_RAY, p3, p4);
}
