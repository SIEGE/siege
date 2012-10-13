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

#define SG_BUILD_LIBRARY
#include <siege/util/vector.h>

#include <stdlib.h>
#include <math.h>

SGVec2 SG_EXPORT sgVec2f(float x, float y)
{
    SGVec2 vec;
    vec.x = x; vec.y = y;
    return vec;
}
SGVec2 SG_EXPORT sgVec2fv(const float* xy)
{
    return sgVec2f(xy[0], xy[1]);
}
SGVec2 SG_EXPORT sgVec2PolarRads(float rads, float len)
{
    return sgVec2f(cos(rads) * len, sin(rads) * len);
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
    float len = sgVec2Length(vec);
    return sgVec2f(vec.x / len, vec.y / len);
}

SGVec2 SG_EXPORT sgVec2Resize(SGVec2 vec, float length)
{
    float scale = length / sgVec2Length(vec);
    if(scale != scale)
        scale = 0;
    return sgVec2f(vec.x * scale, vec.y * scale);
}
float SG_EXPORT sgVec2Length(SGVec2 vec)
{
    return sqrt(sgVec2Length2(vec));
}
float SG_EXPORT sgVec2Length2(SGVec2 vec)
{
    return sgVec2Dot(vec, vec);
}

SGVec2 SG_EXPORT sgVec2RotateRads(SGVec2 vec, float rads)
{
    float len = sgVec2Length(vec);
    return sgVec2PolarRads(rads, len);
}
float SG_EXPORT sgVec2AngleRads(SGVec2 vec)
{
    return atan2(vec.y, vec.x);
}
SGVec2 SG_EXPORT sgVec2RotateDegs(SGVec2 vec, float degs)
{
    float len = sgVec2Length(vec);
    return sgVec2PolarDegs(degs, len);
}
float SG_EXPORT sgVec2AngleDegs(SGVec2 vec)
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

float SG_EXPORT sgVec2Distance(SGVec2 a, SGVec2 b)
{
    return sgVec2Length(sgVec2Sub(a, b));
}
float SG_EXPORT sgVec2Distance2(SGVec2 a, SGVec2 b)
{
    return sgVec2Length2(sgVec2Sub(a, b));
}

float SG_EXPORT sgVec2Dot(SGVec2 a, SGVec2 b)
{
    return a.x * b.x + a.y * b.y;
}
float SG_EXPORT sgVec2PDot(SGVec2 a, SGVec2 b)
{
    return a.x * b.y - a.y * b.x;
}
SGVec2 SG_EXPORT sgVec2Cross(SGVec2 a)
{
    return sgVec2f(a.y, -a.x);
}

SGVec2 SG_EXPORT sgVec2Reflect(SGVec2 ray, SGVec2 normal)
{
    ray = sgVec2Normalize(ray);
    normal = sgVec2Normalize(normal);

    return sgVec2Sub(ray, sgVec2Resize(normal, 2.0 * sgVec2Dot(ray, normal)));
}
float SG_EXPORT sgVec2ProjectScalar(SGVec2 v, SGVec2 target)
{
    return sgVec2Dot(v, target) / sgVec2Length(target);
}
SGVec2 SG_EXPORT sgVec2Project(SGVec2 v, SGVec2 target)
{
    return sgVec2Resize(target, sgVec2ProjectScalar(v, target));
}


SGVec3 SG_EXPORT sgVec3f(float x, float y, float z)
{
    SGVec3 vec;
    vec.x = x; vec.y = y; vec.z = z;
    return vec;
}
SGVec3 SG_EXPORT sgVec3fv(const float* xyz)
{
    return sgVec3f(xyz[0], xyz[1], xyz[2]);
}
SGVec3 SG_EXPORT sgVec3CylindricalRads(float rads, float radius, float z)
{
    return sgVec3f(cos(rads) * radius, sin(rads) * radius, z);
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
	return sgVec3f(radius * ca * sz, radius * sa * sz, radius * cz);
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
    float len = sgVec3Length(vec);
    return sgVec3f(vec.x / len, vec.y / len, vec.z / len);
}

SGVec3 SG_EXPORT sgVec3Resize(SGVec3 vec, float length)
{
    float scale = length / sgVec3Length(vec);
    if(scale != scale)
        scale = 0;
    return sgVec3f(vec.x * scale, vec.y * scale, vec.z * scale);
}
float SG_EXPORT sgVec3Length(SGVec3 vec)
{
    return sqrt(sgVec3Length2(vec));
}
float SG_EXPORT sgVec3Length2(SGVec3 vec)
{
    return sgVec3Dot(vec, vec);
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

float SG_EXPORT sgVec3Distance(SGVec3 a, SGVec3 b)
{
    return sgVec3Length(sgVec3Sub(a, b));
}
float SG_EXPORT sgVec3Distance2(SGVec3 a, SGVec3 b)
{
    return sgVec3Length2(sgVec3Sub(a, b));
}

float SG_EXPORT sgVec3Dot(SGVec3 a, SGVec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
SGVec3 SG_EXPORT sgVec3Cross(SGVec3 a, SGVec3 b)
{
    return sgVec3f(a.y * b.z - a.z * b.y, a.x * b.z - a.z * b.x, a.x * b.y - a.y * b.x);
}
float SG_EXPORT sgVec3Triple(SGVec3 a, SGVec3 b, SGVec3 c)
{
    return sgVec3Dot(a, sgVec3Cross(b, c));
}

SGVec3 SG_EXPORT sgVec3Reflect(SGVec3 ray, SGVec3 normal)
{
    ray = sgVec3Normalize(ray);
    normal = sgVec3Normalize(normal);

    return sgVec3Sub(ray, sgVec3Resize(normal, 2.0 * sgVec3Dot(ray, normal)));
}
float SG_EXPORT sgVec3ProjectScalar(SGVec3 v, SGVec3 target)
{
    return sgVec3Dot(v, target) / sgVec3Length(target);
}
SGVec3 SG_EXPORT sgVec3Project(SGVec3 v, SGVec3 target)
{
    return sgVec3Resize(target, sgVec3ProjectScalar(v, target));
}


SGVec4 SG_EXPORT sgVec4f(float x, float y, float z, float w)
{
    SGVec4 vec;
    vec.x = x; vec.y = y; vec.z = z; vec.w = w;
    return vec;
}
SGVec4 SG_EXPORT sgVec4fv(const float* xyzw)
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
    float len = sgVec4Length(vec);
    return sgVec4f(vec.x / len, vec.y / len, vec.z / len, vec.w / len);
}

SGVec4 SG_EXPORT sgVec4Resize(SGVec4 vec, float length)
{
    float scale = length / sgVec4Length(vec);
    if(scale != scale)
        scale = 0;
    return sgVec4f(vec.x * scale, vec.y * scale, vec.z * scale, vec.w * scale);
}
float SG_EXPORT sgVec4Length(SGVec4 vec)
{
    return sqrt(sgVec4Length2(vec));
}
float SG_EXPORT sgVec4Length2(SGVec4 vec)
{
    return sgVec4Dot(vec, vec);
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

float SG_EXPORT sgVec4Distance(SGVec4 a, SGVec4 b)
{
    return sgVec4Length(sgVec4Sub(a, b));
}
float SG_EXPORT sgVec4Distance2(SGVec4 a, SGVec4 b)
{
    return sgVec4Length2(sgVec4Sub(a, b));
}

float SG_EXPORT sgVec4Dot(SGVec4 a, SGVec4 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
//SGVec4 SG_EXPORT sgVec4Cross(SGVec4 a, SGVec4 b, SGVec4 c);

SGVec4 SG_EXPORT sgVec4Reflect(SGVec4 ray, SGVec4 normal)
{
    ray = sgVec4Normalize(ray);
    normal = sgVec4Normalize(normal);

    return sgVec4Sub(ray, sgVec4Resize(normal, 2.0 * sgVec4Dot(ray, normal)));
}
float SG_EXPORT sgVec4ProjectScalar(SGVec4 v, SGVec4 target)
{
    return sgVec4Dot(v, target) / sgVec4Length(target);
}
SGVec4 SG_EXPORT sgVec4Project(SGVec4 v, SGVec4 target)
{
    return sgVec4Resize(target, sgVec4ProjectScalar(v, target));
}
