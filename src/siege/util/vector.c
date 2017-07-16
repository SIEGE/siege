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
#include <siege/util/ivector.h>

#include <stdlib.h>
#include <math.h>

static float wrapFloat(float a, float min, float max)
{
    a -= min;
    max -= min;

    return min + (a < 0 ? fmod(max - fmod(-a, max), max) : fmod(a, max));
}
static void swapFloat(float* x, float* y)
{
    float tmp = *x;
    *x = *y;
    *y = tmp;
}
static void sortFloat(float* x, float* y)
{
    if(*y < *x) swapFloat(x, y);
}

SGVec2 SG_CALL sgVec2f(float x, float y)
{
    SGVec2 vec;
    vec.x = x; vec.y = y;
    return vec;
}
SGVec2 SG_CALL sgVec2fp(const float* xy)
{
    return sgVec2f(xy[0], xy[1]);
}
SGVec2 SG_CALL sgVec2iv(SGIVec2 vec)
{
    return sgVec2f(vec.x, vec.y);
}
SGVec2 SG_CALL sgVec2PolarRads(float rads, float len)
{
    return sgVec2f(cos(rads) * len, sin(rads) * len);
}
SGVec2 SG_CALL sgVec2PolarDegs(float degs, float len)
{
    return sgVec2PolarRads(degs * SG_PI / 180.0, len);
}
SGVec2 SG_CALL sgVec2Nan(void)
{
    return sgVec2f(SG_NAN, SG_NAN);
}

SGVec2 SG_CALL sgVec2Normalize(SGVec2 vec)
{
    float len = sgVec2Length(vec);
    return sgVec2f(vec.x / len, vec.y / len);
}

SGVec2 SG_CALL sgVec2Resize(SGVec2 vec, float length)
{
    float scale = length / sgVec2Length(vec);
    if(scale != scale)
        scale = 0;
    return sgVec2f(vec.x * scale, vec.y * scale);
}
float SG_CALL sgVec2Length(SGVec2 vec)
{
    return sqrt(sgVec2Length2(vec));
}
float SG_CALL sgVec2Length2(SGVec2 vec)
{
    return sgVec2Dot(vec, vec);
}

SGVec2 SG_CALL sgVec2RotateRads(SGVec2 vec, float rads)
{
    float len = sgVec2Length(vec);
    return sgVec2PolarRads(rads, len);
}
float SG_CALL sgVec2AngleRads(SGVec2 vec)
{
    return atan2(vec.y, vec.x);
}
SGVec2 SG_CALL sgVec2RotateDegs(SGVec2 vec, float degs)
{
    float len = sgVec2Length(vec);
    return sgVec2PolarDegs(degs, len);
}
float SG_CALL sgVec2AngleDegs(SGVec2 vec)
{
    return atan2(vec.y, vec.x) * 180.0 / SG_PI;
}

SGbool SG_CALL sgVec2IsNan(SGVec2 vec)
{
    return SG_IS_NAN(vec.x) || SG_IS_NAN(vec.y);
}

SGVec2 SG_CALL sgVec2Neg(SGVec2 a)
{
    return sgVec2f(-a.x, -a.y);
}
SGVec2 SG_CALL sgVec2Add(SGVec2 a, SGVec2 b)
{
    return sgVec2f(a.x + b.x, a.y + b.y);
}
SGVec2 SG_CALL sgVec2Sub(SGVec2 a, SGVec2 b)
{
    return sgVec2f(a.x - b.x, a.y - b.y);
}
SGVec2 SG_CALL sgVec2Mul(SGVec2 a, SGVec2 b)
{
    return sgVec2f(a.x * b.x, a.y * b.y);
}
SGVec2 SG_CALL sgVec2Div(SGVec2 a, SGVec2 b)
{
    return sgVec2f(a.x / b.x, a.y / b.y);
}

SGVec2 SG_CALL sgVec2Addf(SGVec2 a, float f)
{
    return sgVec2Add(a, sgVec2f(f, f));
}
SGVec2 SG_CALL sgVec2Subf(SGVec2 a, float f)
{
    return sgVec2Sub(a, sgVec2f(f, f));
}
SGVec2 SG_CALL sgVec2Mulf(SGVec2 a, float f)
{
    return sgVec2Mul(a, sgVec2f(f, f));
}
SGVec2 SG_CALL sgVec2Divf(SGVec2 a, float f)
{
    return sgVec2Div(a, sgVec2f(f, f));
}

float SG_CALL sgVec2Distance(SGVec2 a, SGVec2 b)
{
    return sgVec2Length(sgVec2Sub(a, b));
}
float SG_CALL sgVec2Distance2(SGVec2 a, SGVec2 b)
{
    return sgVec2Length2(sgVec2Sub(a, b));
}

SGVec2 SG_CALL sgVec2Min(SGVec2 a, SGVec2 b)
{
    return sgVec2f(SG_MIN(a.x, b.x), SG_MIN(a.y, b.y));
}
SGVec2 SG_CALL sgVec2Max(SGVec2 a, SGVec2 b)
{
    return sgVec2f(SG_MAX(a.x, b.x), SG_MAX(a.y, b.y));
}
SGVec2 SG_CALL sgVec2Abs(SGVec2 a)
{
    return sgVec2f(SG_ABS(a.x), SG_ABS(a.y));
}
SGVec2 SG_CALL sgVec2Wrap(SGVec2 a, SGVec2 min, SGVec2 max)
{
    return sgVec2f(wrapFloat(a.x, min.x, max.x), wrapFloat(a.y, min.y, max.y));
}
SGVec2 SG_CALL sgVec2Clamp(SGVec2 a, SGVec2 min, SGVec2 max)
{
    return sgVec2Min(sgVec2Max(a, min), max);
}
SGVec2 SG_CALL sgVec2XWrap(SGVec2 a, SGVec2 min, SGVec2 max)
{
    sortFloat(&min.x, &max.x);
    sortFloat(&min.y, &max.y);
    return sgVec2Wrap(a, min, max);
}
SGVec2 SG_CALL sgVec2XClamp(SGVec2 a, SGVec2 min, SGVec2 max)
{
    sortFloat(&min.x, &max.x);
    sortFloat(&min.y, &max.y);
    return sgVec2Clamp(a, min, max);
}

float SG_CALL sgVec2HSum(SGVec2 a)
{
    return a.x + a.y;
}
float SG_CALL sgVec2HProd(SGVec2 a)
{
    return a.x * a.y;
}

float SG_CALL sgVec2Dot(SGVec2 a, SGVec2 b)
{
    return sgVec2HSum(sgVec2Mul(a, b));
}
float SG_CALL sgVec2PDot(SGVec2 a, SGVec2 b)
{
    return a.x * b.y - a.y * b.x;
}
SGVec2 SG_CALL sgVec2Cross(SGVec2 a)
{
    return sgVec2f(a.y, -a.x);
}

SGVec2 SG_CALL sgVec2CMul(SGVec2 a, SGVec2 b)
{
    // (ax + ay I) * (bx + by I)
    return sgVec2f(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

/* shamelessly stolen from GLSL docs */
SGVec2 SG_CALL sgVec2Refract(SGVec2 ray, SGVec2 normal, float eta)
{
    float dot = sgVec2Dot(ray, normal);
    float eta2 = eta * eta;

    float k = 1.0 - eta2 * (1.0 - dot * dot);
    if(k < 0.0)
        return sgVec2f(0.0, 0.0);

    return sgVec2Sub(sgVec2Mulf(ray, eta), sgVec2Mulf(normal, eta * dot + sqrt(k)));
}
SGVec2 SG_CALL sgVec2Reflect(SGVec2 ray, SGVec2 normal)
{
    return sgVec2Sub(ray, sgVec2Mulf(normal, 2.0 * sgVec2Dot(ray, normal)));
}
float SG_CALL sgVec2ProjectScalar(SGVec2 v, SGVec2 target)
{
    return sgVec2Dot(v, target);
}
// relative to target
SGVec2 SG_CALL sgVec2Project(SGVec2 v, SGVec2 target)
{
    return sgVec2Mulf(target, sgVec2ProjectScalar(v, target));
}
// relative to v
SGVec2 SG_CALL sgVec2Reject(SGVec2 v, SGVec2 target)
{
    return sgVec2Sub(v, sgVec2Project(v, target));
}


SGVec3 SG_CALL sgVec3f(float x, float y, float z)
{
    SGVec3 vec;
    vec.x = x; vec.y = y; vec.z = z;
    return vec;
}
SGVec3 SG_CALL sgVec3fp(const float* xyz)
{
    return sgVec3f(xyz[0], xyz[1], xyz[2]);
}
SGVec3 SG_CALL sgVec3iv(SGIVec3 vec)
{
    return sgVec3f(vec.x, vec.y, vec.z);
}
SGVec3 SG_CALL sgVec3CylindricalRads(float rads, float radius, float z)
{
    return sgVec3f(cos(rads) * radius, sin(rads) * radius, z);
}
SGVec3 SG_CALL sgVec3CylindricalDegs(float degs, float radius, float z)
{
    return sgVec3CylindricalRads(degs * SG_PI / 180.0, radius, z);
}
SGVec3 SG_CALL sgVec3SphericalRads(float azimuth, float zenith, float radius)
{
    float ca = cos(azimuth);
    float sa = sin(azimuth);
    float cz = cos(zenith);
    float sz = sin(zenith);
    return sgVec3f(radius * ca * sz, radius * sa * sz, radius * cz);
}
SGVec3 SG_CALL sgVec3SphericalDegs(float azimuth, float zenith, float radius)
{
    return sgVec3SphericalRads(azimuth * SG_PI / 180.0, zenith * SG_PI / 180.0, radius);
}
SGVec3 SG_CALL sgVec3Nan(void)
{
    return sgVec3f(SG_NAN, SG_NAN, SG_NAN);
}

SGVec3 SG_CALL sgVec3Normalize(SGVec3 vec)
{
    float len = sgVec3Length(vec);
    return sgVec3f(vec.x / len, vec.y / len, vec.z / len);
}

SGVec3 SG_CALL sgVec3Resize(SGVec3 vec, float length)
{
    float scale = length / sgVec3Length(vec);
    if(scale != scale)
        scale = 0;
    return sgVec3f(vec.x * scale, vec.y * scale, vec.z * scale);
}
float SG_CALL sgVec3Length(SGVec3 vec)
{
    return sqrt(sgVec3Length2(vec));
}
float SG_CALL sgVec3Length2(SGVec3 vec)
{
    return sgVec3Dot(vec, vec);
}

/*SGVec3 SG_CALL sgVec3SetAngleRads(SGVec3 vec, float rads);
float SG_CALL sgVec3GetAngleRads(SGVec3 vec);
SGVec3 SG_CALL sgVec3SetAngleDegs(SGVec3 vec, float degs);
float SG_CALL sgVec3GetAngleDegs(SGVec3 vec);*/

SGbool SG_CALL sgVec3IsNan(SGVec3 vec)
{
    return SG_IS_NAN(vec.x) || SG_IS_NAN(vec.y) || SG_IS_NAN(vec.z);
}

SGVec3 SG_CALL sgVec3Neg(SGVec3 a)
{
    return sgVec3f(-a.x, -a.y, -a.z);
}
SGVec3 SG_CALL sgVec3Add(SGVec3 a, SGVec3 b)
{
    return sgVec3f(a.x + b.x, a.y + b.y, a.z + b.z);
}
SGVec3 SG_CALL sgVec3Sub(SGVec3 a, SGVec3 b)
{
    return sgVec3f(a.x - b.x, a.y - b.y, a.z - b.z);
}
SGVec3 SG_CALL sgVec3Mul(SGVec3 a, SGVec3 b)
{
    return sgVec3f(a.x * b.x, a.y * b.y, a.z * b.z);
}
SGVec3 SG_CALL sgVec3Div(SGVec3 a, SGVec3 b)
{
    return sgVec3f(a.x / b.x, a.y / b.y, a.z / b.z);
}

SGVec3 SG_CALL sgVec3Addf(SGVec3 a, float f)
{
    return sgVec3Add(a, sgVec3f(f, f, f));
}
SGVec3 SG_CALL sgVec3Subf(SGVec3 a, float f)
{
    return sgVec3Sub(a, sgVec3f(f, f, f));
}
SGVec3 SG_CALL sgVec3Mulf(SGVec3 a, float f)
{
    return sgVec3Mul(a, sgVec3f(f, f, f));
}
SGVec3 SG_CALL sgVec3Divf(SGVec3 a, float f)
{
    return sgVec3Div(a, sgVec3f(f, f, f));
}

float SG_CALL sgVec3Distance(SGVec3 a, SGVec3 b)
{
    return sgVec3Length(sgVec3Sub(a, b));
}
float SG_CALL sgVec3Distance2(SGVec3 a, SGVec3 b)
{
    return sgVec3Length2(sgVec3Sub(a, b));
}

SGVec3 SG_CALL sgVec3Min(SGVec3 a, SGVec3 b)
{
    return sgVec3f(SG_MIN(a.x, b.x), SG_MIN(a.y, b.y), SG_MIN(a.z, b.z));
}
SGVec3 SG_CALL sgVec3Max(SGVec3 a, SGVec3 b)
{
    return sgVec3f(SG_MAX(a.x, b.x), SG_MAX(a.y, b.y), SG_MAX(a.z, b.z));
}
SGVec3 SG_CALL sgVec3Abs(SGVec3 a)
{
    return sgVec3f(SG_ABS(a.x), SG_ABS(a.y), SG_ABS(a.z));
}
SGVec3 SG_CALL sgVec3Wrap(SGVec3 a, SGVec3 min, SGVec3 max)
{
    return sgVec3f(wrapFloat(a.x, min.x, max.x), wrapFloat(a.y, min.y, max.y), wrapFloat(a.z, min.z, max.z));
}
SGVec3 SG_CALL sgVec3Clamp(SGVec3 a, SGVec3 min, SGVec3 max)
{
    return sgVec3Min(sgVec3Max(a, min), max);
}
SGVec3 SG_CALL sgVec3XWrap(SGVec3 a, SGVec3 min, SGVec3 max)
{
    sortFloat(&min.x, &max.x);
    sortFloat(&min.y, &max.y);
    sortFloat(&min.z, &max.z);
    return sgVec3Wrap(a, min, max);
}
SGVec3 SG_CALL sgVec3XClamp(SGVec3 a, SGVec3 min, SGVec3 max)
{
    sortFloat(&min.x, &max.x);
    sortFloat(&min.y, &max.y);
    sortFloat(&min.z, &max.z);
    return sgVec3Clamp(a, min, max);
}

float SG_CALL sgVec3HSum(SGVec3 a)
{
    return a.x + a.y + a.z;
}
float SG_CALL sgVec3HProd(SGVec3 a)
{
    return a.x * a.y * a.z;
}

float SG_CALL sgVec3Dot(SGVec3 a, SGVec3 b)
{
    return sgVec3HSum(sgVec3Mul(a, b));
}
SGVec3 SG_CALL sgVec3Cross(SGVec3 a, SGVec3 b)
{
    return sgVec3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
float SG_CALL sgVec3Triple(SGVec3 a, SGVec3 b, SGVec3 c)
{
    return sgVec3Dot(a, sgVec3Cross(b, c));
}

SGVec3 SG_CALL sgVec3Refract(SGVec3 ray, SGVec3 normal, float eta)
{
    float dot = sgVec3Dot(ray, normal);
    float eta2 = eta * eta;

    float k = 1.0 - eta2 * (1.0 - dot * dot);
    if(k < 0.0)
        return sgVec3f(0.0, 0.0, 0.0);

    return sgVec3Sub(sgVec3Mulf(ray, eta), sgVec3Mulf(normal, eta * dot + sqrt(k)));
}
SGVec3 SG_CALL sgVec3Reflect(SGVec3 ray, SGVec3 normal)
{
    return sgVec3Sub(ray, sgVec3Mulf(normal, 2.0 * sgVec3Dot(ray, normal)));
}
float SG_CALL sgVec3ProjectScalar(SGVec3 v, SGVec3 target)
{
    return sgVec3Dot(v, target);
}
SGVec3 SG_CALL sgVec3Project(SGVec3 v, SGVec3 target)
{
    return sgVec3Mulf(target, sgVec3ProjectScalar(v, target));
}
SGVec3 SG_CALL sgVec3Reject(SGVec3 v, SGVec3 target)
{
    return sgVec3Sub(v, sgVec3Project(v, target));
}



SGVec4 SG_CALL sgVec4f(float x, float y, float z, float w)
{
    SGVec4 vec;
    vec.x = x; vec.y = y; vec.z = z; vec.w = w;
    return vec;
}
SGVec4 SG_CALL sgVec4fp(const float* xyzw)
{
    return sgVec4f(xyzw[0], xyzw[1], xyzw[2], xyzw[3]);
}
SGVec4 SG_CALL sgVec4iv(SGIVec4 vec)
{
    return sgVec4f(vec.x, vec.y, vec.z, vec.w);
}
/*SGVec4 SG_CALL sgVec4PolarRads(float rads, float len);
SGVec4 SG_CALL sgVec4PolarDegs(float degs, float len);*/
SGVec4 SG_CALL sgVec4Nan(void)
{
    return sgVec4f(SG_NAN, SG_NAN, SG_NAN, SG_NAN);
}

SGVec4 SG_CALL sgVec4Normalize(SGVec4 vec)
{
    float len = sgVec4Length(vec);
    return sgVec4f(vec.x / len, vec.y / len, vec.z / len, vec.w / len);
}

SGVec4 SG_CALL sgVec4Resize(SGVec4 vec, float length)
{
    float scale = length / sgVec4Length(vec);
    if(scale != scale)
        scale = 0;
    return sgVec4f(vec.x * scale, vec.y * scale, vec.z * scale, vec.w * scale);
}
float SG_CALL sgVec4Length(SGVec4 vec)
{
    return sqrt(sgVec4Length2(vec));
}
float SG_CALL sgVec4Length2(SGVec4 vec)
{
    return sgVec4Dot(vec, vec);
}

/*SGVec4 SG_CALL sgVec4SetAngleRads(SGVec4 vec, float rads);
float SG_CALL sgVec4GetAngleRads(SGVec4 vec);
SGVec4 SG_CALL sgVec4SetAngleDegs(SGVec4 vec, float degs);
float SG_CALL sgVec4GetAngleDegs(SGVec4 vec);*/

SGbool SG_CALL sgVec4IsNan(SGVec4 vec)
{
    return SG_IS_NAN(vec.x) || SG_IS_NAN(vec.y) || SG_IS_NAN(vec.z) || SG_IS_NAN(vec.w);
}

SGVec4 SG_CALL sgVec4Neg(SGVec4 a)
{
    return sgVec4f(-a.x, -a.y, -a.z, -a.w);
}
SGVec4 SG_CALL sgVec4Add(SGVec4 a, SGVec4 b)
{
    return sgVec4f(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}
SGVec4 SG_CALL sgVec4Sub(SGVec4 a, SGVec4 b)
{
    return sgVec4f(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}
SGVec4 SG_CALL sgVec4Mul(SGVec4 a, SGVec4 b)
{
    return sgVec4f(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}
SGVec4 SG_CALL sgVec4Div(SGVec4 a, SGVec4 b)
{
    return sgVec4f(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

SGVec4 SG_CALL sgVec4Addf(SGVec4 a, float f)
{
    return sgVec4Add(a, sgVec4f(f, f, f, f));
}
SGVec4 SG_CALL sgVec4Subf(SGVec4 a, float f)
{
    return sgVec4Sub(a, sgVec4f(f, f, f, f));
}
SGVec4 SG_CALL sgVec4Mulf(SGVec4 a, float f)
{
    return sgVec4Mul(a, sgVec4f(f, f, f, f));
}
SGVec4 SG_CALL sgVec4Divf(SGVec4 a, float f)
{
    return sgVec4Div(a, sgVec4f(f, f, f, f));
}

SGVec4 SG_CALL sgVec4QMul(SGVec4 a, SGVec4 b)
{
    // (ax + ay I + az J + aw K) * (bx + by I + bz J + bw K)
    SGVec4 ret;
    ret.x = a.x * b.x - a.y * b.y - a.z * b.z - a.w * b.w;
    ret.y = a.x * b.y + a.y * b.x + a.z * b.w - a.w * b.z;
    ret.z = a.x * b.z - a.y * b.w + a.z * b.x + a.w * b.y;
    ret.w = a.x * b.w + a.y * b.z - a.z * b.y + a.w * b.x;
    return ret;
}

float SG_CALL sgVec4Distance(SGVec4 a, SGVec4 b)
{
    return sgVec4Length(sgVec4Sub(a, b));
}
float SG_CALL sgVec4Distance2(SGVec4 a, SGVec4 b)
{
    return sgVec4Length2(sgVec4Sub(a, b));
}

SGVec4 SG_CALL sgVec4Min(SGVec4 a, SGVec4 b)
{
    return sgVec4f(SG_MIN(a.x, b.x), SG_MIN(a.y, b.y), SG_MIN(a.z, b.z), SG_MIN(a.w, b.w));
}
SGVec4 SG_CALL sgVec4Max(SGVec4 a, SGVec4 b)
{
    return sgVec4f(SG_MAX(a.x, b.x), SG_MAX(a.y, b.y), SG_MAX(a.z, b.z), SG_MAX(a.w, b.w));
}
SGVec4 SG_CALL sgVec4Abs(SGVec4 a)
{
    return sgVec4f(SG_ABS(a.x), SG_ABS(a.y), SG_ABS(a.z), SG_ABS(a.w));
}
SGVec4 SG_CALL sgVec4Wrap(SGVec4 a, SGVec4 min, SGVec4 max)
{
    return sgVec4f(wrapFloat(a.x, min.x, max.x), wrapFloat(a.y, min.y, max.y), wrapFloat(a.z, min.z, max.z), wrapFloat(a.w, min.w, max.w));
}
SGVec4 SG_CALL sgVec4Clamp(SGVec4 a, SGVec4 min, SGVec4 max)
{
    return sgVec4Min(sgVec4Max(a, min), max);
}
SGVec4 SG_CALL sgVec4XWrap(SGVec4 a, SGVec4 min, SGVec4 max)
{
    sortFloat(&min.x, &max.x);
    sortFloat(&min.y, &max.y);
    sortFloat(&min.z, &max.z);
    sortFloat(&min.w, &max.w);
    return sgVec4Wrap(a, min, max);
}
SGVec4 SG_CALL sgVec4XClamp(SGVec4 a, SGVec4 min, SGVec4 max)
{
    sortFloat(&min.x, &max.x);
    sortFloat(&min.y, &max.y);
    sortFloat(&min.z, &max.z);
    sortFloat(&min.w, &max.w);
    return sgVec4Clamp(a, min, max);
}

float SG_CALL sgVec4HSum(SGVec4 a)
{
    return a.x + a.y + a.z + a.w;
}
float SG_CALL sgVec4HProd(SGVec4 a)
{
    return a.x * a.y * a.z * a.w;
}

float SG_CALL sgVec4Dot(SGVec4 a, SGVec4 b)
{
    return sgVec4HSum(sgVec4Mul(a, b));
}
SGVec4 SG_CALL sgVec4Cross(SGVec4 a, SGVec4 b, SGVec4 c)
{
    return sgVec4f(
        + b.y*c.z*a.w - b.z*c.y*a.w - b.w*c.z*a.y + b.z*c.w*a.y - b.y*c.w*a.z + b.w*c.y*a.z,
        - c.z*b.x*a.w + b.z*c.x*a.w + b.w*c.z*a.x - b.z*c.w*a.x + c.w*b.x*a.z - b.w*c.x*a.z,
        - b.y*c.x*a.w + b.x*c.y*a.w + b.y*c.w*a.x - b.w*c.y*a.x - c.w*b.x*a.y + b.w*c.x*a.y,
        - b.y*c.z*a.x + b.z*c.y*a.x + c.z*b.x*a.y - b.z*c.x*a.y + b.y*c.x*a.z - b.x*c.y*a.z
    );
}

SGVec4 SG_CALL sgVec4Refract(SGVec4 ray, SGVec4 normal, float eta)
{
    float dot = sgVec4Dot(ray, normal);
    float eta2 = eta * eta;

    float k = 1.0 - eta2 * (1.0 - dot * dot);
    if(k < 0.0)
        return sgVec4f(0.0, 0.0, 0.0, 0.0);

    return sgVec4Sub(sgVec4Mulf(ray, eta), sgVec4Mulf(normal, eta * dot + sqrt(k)));
}
SGVec4 SG_CALL sgVec4Reflect(SGVec4 ray, SGVec4 normal)
{
    return sgVec4Sub(ray, sgVec4Mulf(normal, 2.0 * sgVec4Dot(ray, normal)));
}
float SG_CALL sgVec4ProjectScalar(SGVec4 v, SGVec4 target)
{
    return sgVec4Dot(v, target);
}
SGVec4 SG_CALL sgVec4Project(SGVec4 v, SGVec4 target)
{
    return sgVec4Mulf(target, sgVec4ProjectScalar(v, target));
}
SGVec4 SG_CALL sgVec4Reject(SGVec4 v, SGVec4 target)
{
    return sgVec4Sub(v, sgVec4Project(v, target));
}

// DEPRECATED
SG_HINT_DEPRECATED SGVec2 SG_CALL sgVec2QMul2(SGVec2 a, SGVec2 b)
{
    return sgVec2CMul(a, b);
}
SG_HINT_DEPRECATED SGVec4 SG_CALL sgVec4QMul4(SGVec4 a, SGVec4 b)
{
    return sgVec4QMul(a, b);
}
