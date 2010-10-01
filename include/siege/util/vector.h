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

#ifndef __SIEGE_UTIL_VECTOR_H__
#define __SIEGE_UTIL_VECTOR_H__

#include "../common.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

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
SGVec2 SG_EXPORT sgVec2f(float x, float y);
/**
    \memberof SGVec2
    \brief Create a 2D vector from a coordinate pointer
    \param f A pointer to 2 float coordinates
    \return A new 2D vector.
*/
SGVec2 SG_EXPORT sgVec2fv(float* f);
/**
    \memberof SGVec2
    \brief Create a 2D vector from polar coordinates in radians
    \param rads Vector's angle in radians
    \param len Vector's length
    \return A new 2D vector.
*/
SGVec2 SG_EXPORT sgVec2PolarRads(float rads, float len);
/**
    \memberof SGVec2
    \brief Create a 2D vector from polar coordinates in degrees
    \param degs Vector's angle in degrees
    \param len Vector's length
    \return A new 2D vector.
*/
SGVec2 SG_EXPORT sgVec2PolarDegs(float degs, float len);
/**
    \memberof SGVec2
    \brief Create a 2D NaN vector
    \return A new 2D vector with SG_NAN,SG_NAN coordinates.
*/
SGVec2 SG_EXPORT sgVec2Nan(void);

/**
    \memberof SGVec2
    \brief Normalize the vector
    \param vec The vector to normalize
    \return The normalized vector.

    This function changes the vector so that its length is 1.
*/
SGVec2 SG_EXPORT sgVec2Normalize(SGVec2 vec);

/**
    \memberof SGVec2
    \brief Set the vector's length
    \param vec The vector of which the length we want to set
    \param length The new length
    \return A vector with the same angle but new length.
*/
SGVec2 SG_EXPORT sgVec2SetLength(SGVec2 vec, float length);
/**
    \memberof SGVec2
    \brief Get the vector's length
    \param vec The vector of which the length we want to get
    \return The length of the vector.
    \note
        If the squared length is required, it is more efficient to use \ref sgVec2GetLength2 "sgVec2GetLength2".
*/
float SG_EXPORT sgVec2GetLength(SGVec2 vec);
/**
    \memberof SGVec2
    \brief Get the vector's squared length
    \param vec The vector of which the squared length we want to get
    \return The length of the vector, squared.
*/
float SG_EXPORT sgVec2GetLength2(SGVec2 vec);

SGVec2 SG_EXPORT sgVec2SetAngleRads(SGVec2 vec, float rads);
float SG_EXPORT sgVec2GetAngleRads(SGVec2 vec);
SGVec2 SG_EXPORT sgVec2SetAngleDegs(SGVec2 vec, float degs);
float SG_EXPORT sgVec2GetAngleDegs(SGVec2 vec);

SGbool SG_EXPORT sgVec2IsNan(SGVec2 vec);

SGVec2 SG_EXPORT sgVec2Neg(SGVec2 a);
SGVec2 SG_EXPORT sgVec2Add(SGVec2 a, SGVec2 b);
SGVec2 SG_EXPORT sgVec2Sub(SGVec2 a, SGVec2 b);
SGVec2 SG_EXPORT sgVec2Mul(SGVec2 a, SGVec2 b);
SGVec2 SG_EXPORT sgVec2Div(SGVec2 a, SGVec2 b);

float SG_EXPORT sgVec2Dot(SGVec2 a, SGVec2 b);
float SG_EXPORT sgVec2Cross(SGVec2 a, SGVec2 b);



SGVec3 sgVec3f(float x, float y, float z);
SGVec3 sgVec3fv(float* f);
//SGVec3 sgVec3PolarRads(float rads, float len);
//SGVec3 sgVec3PolarDegs(float degs, float len);
SGVec3 sgVec3Nan(void);

SGVec3 sgVec3Normalize(SGVec3 vec);

SGVec3 sgVec3SetLength(SGVec3 vec, float length);
float sgVec3GetLength(SGVec3 vec);
float sgVec3GetLength2(SGVec3 vec);

//SGVec3 sgVec3SetAngleRads(SGVec3 vec, float rads);
//float sgVec3GetAngleRads(SGVec3 vec);
//SGVec3 sgVec3SetAngleDegs(SGVec3 vec, float degs);
//float sgVec3GetAngleDegs(SGVec3 vec);

SGbool sgVec3IsNan(SGVec3 vec);

SGVec3 sgVec3Neg(SGVec3 a);
SGVec3 sgVec3Add(SGVec3 a, SGVec3 b);
SGVec3 sgVec3Sub(SGVec3 a, SGVec3 b);
SGVec3 sgVec3Mul(SGVec3 a, SGVec3 b);
SGVec3 sgVec3Div(SGVec3 a, SGVec3 b);

float sgVec3Dot(SGVec3 a, SGVec3 b);
SGVec3 sgVec3Cross(SGVec3 a, SGVec3 b);



SGVec4 sgVec4f(float x, float y, float z, float w);
SGVec4 sgVec4fv(float* f);
//SGVec4 sgVec4PolarRads(float rads, float len);
//SGVec4 sgVec4PolarDegs(float degs, float len);
SGVec4 sgVec4Nan(void);

SGVec4 sgVec4Normalize(SGVec4 vec);

SGVec4 sgVec4SetLength(SGVec4 vec, float length);
float sgVec4GetLength(SGVec4 vec);
float sgVec4GetLength2(SGVec4 vec);

//SGVec4 sgVec4SetAngleRads(SGVec4 vec, float rads);
//float sgVec4GetAngleRads(SGVec4 vec);
//SGVec4 sgVec4SetAngleDegs(SGVec4 vec, float degs);
//float sgVec4GetAngleDegs(SGVec4 vec);

SGbool sgVec4IsNan(SGVec4 vec);

SGVec4 sgVec4Neg(SGVec4 a);
SGVec4 sgVec4Add(SGVec4 a, SGVec4 b);
SGVec4 sgVec4Sub(SGVec4 a, SGVec4 b);
SGVec4 sgVec4Mul(SGVec4 a, SGVec4 b);
SGVec4 sgVec4Div(SGVec4 a, SGVec4 b);

float sgVec4Dot(SGVec4 a, SGVec4 b);
//SGVec4 sgVec4Cross(SGVec4 a, SGVec4 b);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_VECTOR_H__
