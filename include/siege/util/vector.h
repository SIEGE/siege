/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "COPYING.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
*/

#ifndef __SIEGE_UTIL_VECTOR_H__
#define __SIEGE_UTIL_VECTOR_H__

#include "../common.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

struct SGIVec2;
struct SGIVec3;
struct SGIVec4;

typedef struct SGVec2
{
    float x, y;
} SGVec2;

typedef struct SGVec3
{
    float x, y, z;
} SGVec3;

typedef struct SGVec4
{
    float x, y, z, w;
} SGVec4;

/**
    \memberof SGVec2
    \brief Create a 2D vector from coordinates
    \param x X coordinate
    \param y Y coordinate
    \return A new 2D vector.
*/
SGVec2 SG_CALL sgVec2f(float x, float y);
SGVec2 SG_CALL sgVec2fp(const float* xy);
SGVec2 SG_CALL sgVec2iv(struct SGIVec2 vec);
/**
    \memberof SGVec2
    \brief Create a 2D vector from polar coordinates in radians
    \param rads Vector's angle in radians
    \param len Vector's length
    \return A new 2D vector.
*/
SGVec2 SG_CALL sgVec2PolarRads(float rads, float len);
SGVec2 SG_CALL sgVec2PolarDegs(float degs, float len);
/**
    \memberof SGVec2
    \brief Create a 2D NaN vector
    \return A new 2D vector with SG_NAN,SG_NAN coordinates.
*/
SGVec2 SG_CALL sgVec2Nan(void);

/**
    \memberof SGVec2
    \brief Normalize the vector
    \param vec The vector to normalize
    \return The normalized vector.

    This function changes the vector so that its length is 1.
*/
SGVec2 SG_CALL sgVec2Normalize(SGVec2 vec);

SGVec2 SG_CALL sgVec2Resize(SGVec2 vec, float length);
float SG_CALL sgVec2Length(SGVec2 vec);
float SG_CALL sgVec2Length2(SGVec2 vec);

SGVec2 SG_CALL sgVec2RotateRads(SGVec2 vec, float rads);
float SG_CALL sgVec2AngleRads(SGVec2 vec);
SGVec2 SG_CALL sgVec2RotateDegs(SGVec2 vec, float degs);
float SG_CALL sgVec2AngleDegs(SGVec2 vec);

SGbool SG_CALL sgVec2IsNan(SGVec2 vec);

SGVec2 SG_CALL sgVec2Neg(SGVec2 a);
SGVec2 SG_CALL sgVec2Add(SGVec2 a, SGVec2 b);
SGVec2 SG_CALL sgVec2Sub(SGVec2 a, SGVec2 b);
SGVec2 SG_CALL sgVec2Mul(SGVec2 a, SGVec2 b);
SGVec2 SG_CALL sgVec2Div(SGVec2 a, SGVec2 b);

SGVec2 SG_CALL sgVec2Addf(SGVec2 a, float f);
SGVec2 SG_CALL sgVec2Subf(SGVec2 a, float f);
SGVec2 SG_CALL sgVec2Mulf(SGVec2 a, float f);
SGVec2 SG_CALL sgVec2Divf(SGVec2 a, float f);

SGVec2 SG_CALL sgVec2QMul2(SGVec2 a, SGVec2 b);

float SG_CALL sgVec2Distance(SGVec2 a, SGVec2 b);
float SG_CALL sgVec2Distance2(SGVec2 a, SGVec2 b);

float SG_CALL sgVec2Dot(SGVec2 a, SGVec2 b);
/*
 * Calculates the perpendicular dot product.
 *
 * This is what some call the 2D cross product, though I have opted to call the
 * (IMO more mathematically correct) the generalization below "cross product".
 */
float SG_CALL sgVec2PDot(SGVec2 a, SGVec2 b);
SGVec2 SG_CALL sgVec2Cross(SGVec2 a);

SGVec2 SG_CALL sgVec2Refract(SGVec2 ray, SGVec2 normal, float eta);
SGVec2 SG_CALL sgVec2Reflect(SGVec2 ray, SGVec2 normal);
float SG_CALL sgVec2ProjectScalar(SGVec2 v, SGVec2 target);
SGVec2 SG_CALL sgVec2Project(SGVec2 v, SGVec2 target);
SGVec2 SG_CALL sgVec2Reject(SGVec2 v, SGVec2 target);


SGVec3 SG_CALL sgVec3f(float x, float y, float z);
SGVec3 SG_CALL sgVec3fp(const float* xyz);
SGVec3 SG_CALL sgVec3iv(struct SGIVec3 vec);
SGVec3 SG_CALL sgVec3CylindricalRads(float rads, float radius, float z);
SGVec3 SG_CALL sgVec3CylindricalDegs(float degs, float radius, float z);
SGVec3 SG_CALL sgVec3SphericalRads(float azimuth, float zenith, float radius);
SGVec3 SG_CALL sgVec3SphericalDegs(float azimuth, float zenith, float radius);
SGVec3 SG_CALL sgVec3Nan(void);

SGVec3 SG_CALL sgVec3Normalize(SGVec3 vec);

SGVec3 SG_CALL sgVec3Resize(SGVec3 vec, float length);
float SG_CALL sgVec3Length(SGVec3 vec);
float SG_CALL sgVec3Length2(SGVec3 vec);

//SGVec3 sgVec3SetAngleRads(SGVec3 vec, float rads);
//float sgVec3GetAngleRads(SGVec3 vec);
//SGVec3 sgVec3SetAngleDegs(SGVec3 vec, float degs);
//float sgVec3GetAngleDegs(SGVec3 vec);

SGbool SG_CALL sgVec3IsNan(SGVec3 vec);

SGVec3 SG_CALL sgVec3Neg(SGVec3 a);
SGVec3 SG_CALL sgVec3Add(SGVec3 a, SGVec3 b);
SGVec3 SG_CALL sgVec3Sub(SGVec3 a, SGVec3 b);
SGVec3 SG_CALL sgVec3Mul(SGVec3 a, SGVec3 b);
SGVec3 SG_CALL sgVec3Div(SGVec3 a, SGVec3 b);

SGVec3 SG_CALL sgVec3Addf(SGVec3 a, float f);
SGVec3 SG_CALL sgVec3Subf(SGVec3 a, float f);
SGVec3 SG_CALL sgVec3Mulf(SGVec3 a, float f);
SGVec3 SG_CALL sgVec3Divf(SGVec3 a, float f);

float SG_CALL sgVec3Distance(SGVec3 a, SGVec3 b);
float SG_CALL sgVec3Distance2(SGVec3 a, SGVec3 b);

float SG_CALL sgVec3Dot(SGVec3 a, SGVec3 b);
SGVec3 SG_CALL sgVec3Cross(SGVec3 a, SGVec3 b);
// A dot (B cross C)
float SG_CALL sgVec3Triple(SGVec3 a, SGVec3 b, SGVec3 c);

SGVec3 SG_CALL sgVec3Refract(SGVec3 ray, SGVec3 normal, float eta);
SGVec3 SG_CALL sgVec3Reflect(SGVec3 ray, SGVec3 normal);
float SG_CALL sgVec3ProjectScalar(SGVec3 v, SGVec3 target);
SGVec3 SG_CALL sgVec3Project(SGVec3 v, SGVec3 target);
SGVec3 SG_CALL sgVec3Reject(SGVec3 v, SGVec3 target);


SGVec4 SG_CALL sgVec4f(float x, float y, float z, float w);
SGVec4 SG_CALL sgVec4fp(const float* xyzw);
SGVec4 SG_CALL sgVec4iv(struct SGIVec4 vec);
//SGVec4 sgVec4PolarRads(float rads, float len);
//SGVec4 sgVec4PolarDegs(float degs, float len);
SGVec4 SG_CALL sgVec4Nan(void);

SGVec4 SG_CALL sgVec4Normalize(SGVec4 vec);

SGVec4 SG_CALL sgVec4Resize(SGVec4 vec, float length);
float SG_CALL sgVec4Length(SGVec4 vec);
float SG_CALL sgVec4Length2(SGVec4 vec);

//SGVec4 sgVec4SetAngleRads(SGVec4 vec, float rads);
//float sgVec4GetAngleRads(SGVec4 vec);
//SGVec4 sgVec4SetAngleDegs(SGVec4 vec, float degs);
//float sgVec4GetAngleDegs(SGVec4 vec);

SGbool SG_CALL sgVec4IsNan(SGVec4 vec);

SGVec4 SG_CALL sgVec4Neg(SGVec4 a);
SGVec4 SG_CALL sgVec4Add(SGVec4 a, SGVec4 b);
SGVec4 SG_CALL sgVec4Sub(SGVec4 a, SGVec4 b);
SGVec4 SG_CALL sgVec4Mul(SGVec4 a, SGVec4 b);
SGVec4 SG_CALL sgVec4Div(SGVec4 a, SGVec4 b);

SGVec4 SG_CALL sgVec4Addf(SGVec4 a, float f);
SGVec4 SG_CALL sgVec4Subf(SGVec4 a, float f);
SGVec4 SG_CALL sgVec4Mulf(SGVec4 a, float f);
SGVec4 SG_CALL sgVec4Divf(SGVec4 a, float f);

SGVec4 SG_CALL sgVec4QMul4(SGVec4 a, SGVec4 b);

float SG_CALL sgVec4Distance(SGVec4 a, SGVec4 b);
float SG_CALL sgVec4Distance2(SGVec4 a, SGVec4 b);

float SG_CALL sgVec4Dot(SGVec4 a, SGVec4 b);
//SGVec4 sgVec4Cross(SGVec4 a, SGVec4 b, SGVec4 c);

SGVec4 SG_CALL sgVec4Refract(SGVec4 ray, SGVec4 normal, float eta);
SGVec4 SG_CALL sgVec4Reflect(SGVec4 ray, SGVec4 normal);
float SG_CALL sgVec4ProjectScalar(SGVec4 v, SGVec4 target);
SGVec4 SG_CALL sgVec4Project(SGVec4 v, SGVec4 target);
SGVec4 SG_CALL sgVec4Reject(SGVec4 v, SGVec4 target);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_VECTOR_H__
