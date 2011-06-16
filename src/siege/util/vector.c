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

#define SG_BUILD_LIBRARY
#include <siege/util/vector.h>

#include <stdlib.h>
#include <math.h>

SGVec2 SG_EXPORT sgVec2f(float x, float y)
{
    SGVec2 vec = {x, y};
    return vec;
}
SGVec2 SG_EXPORT sgVec2fv(float* xy)
{
    return sgVec2f(xy[0], xy[1]);
}
SGVec2 SG_EXPORT sgVec2PolarRads(float rads, float len)
{
    SGVec2 vec = {cos(rads) * len, sin(rads) * len};
    return vec;
}
SGVec2 SG_EXPORT sgVec2PolarDegs(float degs, float len)
{
    return sgVec2PolarRads(degs * SG_PI / 180.0, len);
}
SGVec2 SG_EXPORT sgVec2Nan(void)
{
    return sgVec2f(SG_NAN, SG_NAN);
}

SGVec2 SG_EXPORT sgVec2Normalize(SGVec2 vec)
{
    float len = sgVec2GetLength(vec);
    return sgVec2f(vec.x / len, vec.y / len);
}

SGVec2 SG_EXPORT sgVec2SetLength(SGVec2 vec, float length)
{
    float rads = atan2(vec.y, vec.x);
    return sgVec2PolarRads(rads, length);
}
float SG_EXPORT sgVec2GetLength(SGVec2 vec)
{
    return hypot(vec.x, vec.y);
}
float SG_EXPORT sgVec2GetLength2(SGVec2 vec)
{
    return vec.x * vec.x + vec.y * vec.y;
}

SGVec2 SG_EXPORT sgVec2SetAngleRads(SGVec2 vec, float rads)
{
    float len = sgVec2GetLength(vec);
    return sgVec2PolarRads(rads, len);
}
float SG_EXPORT sgVec2GetAngleRads(SGVec2 vec)
{
    return atan2(vec.y, vec.x);
}
SGVec2 SG_EXPORT sgVec2SetAngleDegs(SGVec2 vec, float degs)
{
    float len = sgVec2GetLength(vec);
    return sgVec2PolarDegs(degs, len);
}
float SG_EXPORT sgVec2GetAngleDegs(SGVec2 vec)
{
    return atan2(vec.y, vec.x) * 180.0 / SG_PI;
}

SGbool SG_EXPORT sgVec2IsNan(SGVec2 vec)
{
    return (vec.x != vec.x) || (vec.y != vec.y);
}

SGVec2 SG_EXPORT sgVec2Neg(SGVec2 a)
{
    return sgVec2f(-a.x, -a.y);
}
SGVec2 SG_EXPORT sgVec2Add(SGVec2 a, SGVec2 b)
{
    return sgVec2f(a.x + b.x, a.y + b.y);
}
SGVec2 SG_EXPORT sgVec2Sub(SGVec2 a, SGVec2 b)
{
    return sgVec2f(a.x - b.x, a.y - b.y);
}
SGVec2 SG_EXPORT sgVec2Mul(SGVec2 a, SGVec2 b)
{
    return sgVec2f(a.x * b.x, a.y * b.y);
}
SGVec2 SG_EXPORT sgVec2Div(SGVec2 a, SGVec2 b)
{
    return sgVec2f(a.x / b.x, a.y / b.y);
}

float SG_EXPORT sgVec2Dot(SGVec2 a, SGVec2 b)
{
    return a.x * b.x + a.y * b.y;
}
float SG_EXPORT sgVec2Cross(SGVec2 a, SGVec2 b)
{
    return a.x * b.y - a.y * b.x;
}



SGVec3 SG_EXPORT sgVec3f(float x, float y, float z)
{
    SGVec3 vec = {x, y, z};
    return vec;
}
SGVec3 SG_EXPORT sgVec3fv(float* xyz)
{
    return sgVec3f(xyz[0], xyz[1], xyz[2]);
}
SGVec3 SG_EXPORT sgVec3CylindricalRads(float rads, float radius, float z)
{
	SGVec3 vec = {cos(rads) * radius, sin(rads) * radius, z};
	return vec;
}
SGVec3 SG_EXPORT sgVec3CylindricalDegs(float degs, float radius, float z)
{
	return sgVec3CylindricalRads(degs * SG_PI / 180.0, radius, z);
}
SGVec3 SG_EXPORT sgVec3SphericalRads(float azimuth, float zenith, float radius)
{
	float ca = cos(azimuth);
	float sa = sin(azimuth);
	float cz = cos(zenith);
	float sz = sin(zenith);
	SGVec3 vec = {radius * ca * sz, radius * sa * sz, radius * cz};
	return vec;
}
SGVec3 SG_EXPORT sgVec3SphericalDegs(float azimuth, float zenith, float radius)
{
	return sgVec3SphericalRads(azimuth * SG_PI / 180.0, zenith * SG_PI / 180.0, radius);
}
SGVec3 SG_EXPORT sgVec3Nan(void)
{
    return sgVec3f(SG_NAN, SG_NAN, SG_NAN);
}

SGVec3 SG_EXPORT sgVec3Normalize(SGVec3 vec)
{
    float len = sgVec3GetLength(vec);
    return sgVec3f(vec.x / len, vec.y / len, vec.z / len);
}

/*SGVec3 SG_EXPORT sgVec3SetLength(SGVec3 vec, float length)
{
    float rads = atan3(vec.y, vec.x);
    return sgVec3PolarRads(rads, length);
}*/
float SG_EXPORT sgVec3GetLength(SGVec3 vec)
{
    return hypot(hypot(vec.x, vec.y), vec.z);
}
float SG_EXPORT sgVec3GetLength2(SGVec3 vec)
{
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

/*SGVec3 SG_EXPORT sgVec3SetAngleRads(SGVec3 vec, float rads);
float SG_EXPORT sgVec3GetAngleRads(SGVec3 vec);
SGVec3 SG_EXPORT sgVec3SetAngleDegs(SGVec3 vec, float degs);
float SG_EXPORT sgVec3GetAngleDegs(SGVec3 vec);*/

SGbool SG_EXPORT sgVec3IsNan(SGVec3 vec)
{
    return (vec.x != vec.x) || (vec.y != vec.y) || (vec.z != vec.z);
}

SGVec3 SG_EXPORT sgVec3Neg(SGVec3 a)
{
    return sgVec3f(-a.x, -a.y, -a.z);
}
SGVec3 SG_EXPORT sgVec3Add(SGVec3 a, SGVec3 b)
{
    return sgVec3f(a.x + b.x, a.y + b.y, a.z + b.z);
}
SGVec3 SG_EXPORT sgVec3Sub(SGVec3 a, SGVec3 b)
{
    return sgVec3f(a.x - b.x, a.y - b.y, a.z - b.z);
}
SGVec3 SG_EXPORT sgVec3Mul(SGVec3 a, SGVec3 b)
{
    return sgVec3f(a.x * b.x, a.y * b.y, a.z * b.z);
}
SGVec3 SG_EXPORT sgVec3Div(SGVec3 a, SGVec3 b)
{
    return sgVec3f(a.x / b.x, a.y / b.y, a.z / b.z);
}

float SG_EXPORT sgVec3Dot(SGVec3 a, SGVec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
SGVec3 SG_EXPORT sgVec3Cross(SGVec3 a, SGVec3 b)
{
    return sgVec3f(a.y * b.z - a.z * b.y, a.x * b.z - a.z * b.x, a.x * b.y - a.y * b.x);
}



SGVec4 SG_EXPORT sgVec4f(float x, float y, float z, float w)
{
    SGVec4 vec = {x, y, z, w};
    return vec;
}
SGVec4 SG_EXPORT sgVec4fv(float* xyzw)
{
    return sgVec4f(xyzw[0], xyzw[1], xyzw[2], xyzw[3]);
}
/*SGVec4 SG_EXPORT sgVec4PolarRads(float rads, float len);
SGVec4 SG_EXPORT sgVec4PolarDegs(float degs, float len);*/
SGVec4 SG_EXPORT sgVec4Nan(void)
{
    return sgVec4f(SG_NAN, SG_NAN, SG_NAN, SG_NAN);
}

SGVec4 SG_EXPORT sgVec4Normalize(SGVec4 vec)
{
    float len = sgVec4GetLength(vec);
    return sgVec4f(vec.x / len, vec.y / len, vec.z / len, vec.w / len);
}

/*SGVec4 SG_EXPORT sgVec4SetLength(SGVec4 vec, float length)
{
    float rads = atan4(vec.y, vec.x);
    return sgVec4PolarRads(rads, length);
}*/
float SG_EXPORT sgVec4GetLength(SGVec4 vec)
{
    return hypot(hypot(vec.x, vec.y), hypot(vec.z, vec.w));
}
float SG_EXPORT sgVec4GetLength2(SGVec4 vec)
{
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w;
}

/*SGVec4 SG_EXPORT sgVec4SetAngleRads(SGVec4 vec, float rads);
float SG_EXPORT sgVec4GetAngleRads(SGVec4 vec);
SGVec4 SG_EXPORT sgVec4SetAngleDegs(SGVec4 vec, float degs);
float SG_EXPORT sgVec4GetAngleDegs(SGVec4 vec);*/

SGbool SG_EXPORT sgVec4IsNan(SGVec4 vec)
{
    return (vec.x != vec.x) || (vec.y != vec.y) || (vec.z != vec.z) || (vec.w != vec.w);
}

SGVec4 SG_EXPORT sgVec4Neg(SGVec4 a)
{
    return sgVec4f(-a.x, -a.y, -a.z, -a.w);
}
SGVec4 SG_EXPORT sgVec4Add(SGVec4 a, SGVec4 b)
{
    return sgVec4f(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}
SGVec4 SG_EXPORT sgVec4Sub(SGVec4 a, SGVec4 b)
{
    return sgVec4f(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}
SGVec4 SG_EXPORT sgVec4Mul(SGVec4 a, SGVec4 b)
{
    return sgVec4f(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}
SGVec4 SG_EXPORT sgVec4Div(SGVec4 a, SGVec4 b)
{
    return sgVec4f(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

float SG_EXPORT sgVec4Dot(SGVec4 a, SGVec4 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
//SGVec4 SG_EXPORT sgVec4Cross(SGVec4 a, SGVec4 b);
