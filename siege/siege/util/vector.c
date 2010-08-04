#define SG_BUILD_LIBRARY
#include <siege/util/vector.h>

#include <stdlib.h>
#include <math.h>

SGVec2 sgVec2f(float x, float y)
{
    SGVec2 vec = {x, y};
    return vec;
}
SGVec2 sgVec2fv(float* f)
{
    return sgVec2f(f[0], f[1]);
}
SGVec2 sgVec2PolarRads(float rads, float len)
{
    SGVec2 vec = {cos(rads) * len, sin(rads) * len};
    return vec;
}
SGVec2 sgVec2PolarDegs(float degs, float len)
{
    return sgVec2PolarRads(degs * M_PI / 180.0, len);
}
SGVec2 sgVec2Nan(void)
{
    return sgVec2f(SG_NAN, SG_NAN);
}

SGVec2 sgVec2Normalize(SGVec2 vec)
{
    float len = sgVec2GetLength(vec);
    return sgVec2f(vec.x / len, vec.y / len);
}

SGVec2 sgVec2SetLength(SGVec2 vec, float length)
{
    float rads = atan2(vec.y, vec.x);
    return sgVec2PolarRads(rads, length);
}
float sgVec2GetLength(SGVec2 vec)
{
    return hypot(vec.x, vec.y);
}
float sgVec2GetLength2(SGVec2 vec)
{
    return vec.x * vec.x + vec.y * vec.y;
}

SGVec2 sgVec2SetAngleRads(SGVec2 vec, float rads)
{
    float len = sgVec2GetLength(vec);
    return sgVec2PolarRads(rads, len);
}
float sgVec2GetAngleRads(SGVec2 vec)
{
    return atan2(vec.y, vec.x);
}
SGVec2 sgVec2SetAngleDegs(SGVec2 vec, float degs)
{
    float len = sgVec2GetLength(vec);
    return sgVec2PolarDegs(degs, len);
}
float sgVec2GetAngleDegs(SGVec2 vec)
{
    return atan2(vec.y, vec.x) * 180.0 / M_PI;
}

SGbool sgVec2IsNan(SGVec2 vec)
{
    return (vec.x != vec.x) || (vec.y != vec.y);
}

SGVec2 sgVec2Neg(SGVec2 a)
{
    return sgVec2f(-a.x, -a.y);
}
SGVec2 sgVec2Add(SGVec2 a, SGVec2 b)
{
    return sgVec2f(a.x + b.x, a.y + b.y);
}
SGVec2 sgVec2Sub(SGVec2 a, SGVec2 b)
{
    return sgVec2f(a.x - b.x, a.y - b.y);
}
SGVec2 sgVec2Mul(SGVec2 a, SGVec2 b)
{
    return sgVec2f(a.x * b.x, a.y * b.y);
}
SGVec2 sgVec2Div(SGVec2 a, SGVec2 b)
{
    return sgVec2f(a.x / b.x, a.y / b.y);
}

float sgVec2Dot(SGVec2 a, SGVec2 b)
{
    return a.x * b.x + a.y * b.y;
}
float sgVec2Cross(SGVec2 a, SGVec2 b)
{
    return a.x * b.y - a.y * b.x;
}



SGVec3 sgVec3f(float x, float y, float z)
{
    SGVec3 vec = {x, y, z};
    return vec;
}
SGVec3 sgVec3fv(float* f)
{
    return sgVec3f(f[0], f[1], f[2]);
}
/*SGVec3 sgVec3PolarRads(float rads, float len);
SGVec3 sgVec3PolarDegs(float degs, float len);*/
SGVec3 sgVec3Nan(void)
{
    return sgVec3f(SG_NAN, SG_NAN, SG_NAN);
}

SGVec3 sgVec3Normalize(SGVec3 vec)
{
    float len = sgVec3GetLength(vec);
    return sgVec3f(vec.x / len, vec.y / len, vec.z / len);
}

/*SGVec3 sgVec3SetLength(SGVec3 vec, float length)
{
    float rads = atan3(vec.y, vec.x);
    return sgVec3PolarRads(rads, length);
}*/
float sgVec3GetLength(SGVec3 vec)
{
    return hypot(hypot(vec.x, vec.y), vec.z);
}
float sgVec3GetLength2(SGVec3 vec)
{
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

/*SGVec3 sgVec3SetAngleRads(SGVec3 vec, float rads);
float sgVec3GetAngleRads(SGVec3 vec);
SGVec3 sgVec3SetAngleDegs(SGVec3 vec, float degs);
float sgVec3GetAngleDegs(SGVec3 vec);*/

SGbool sgVec3IsNan(SGVec3 vec)
{
    return (vec.x != vec.x) || (vec.y != vec.y) || (vec.z != vec.z);
}

SGVec3 sgVec3Neg(SGVec3 a)
{
    return sgVec3f(-a.x, -a.y, -a.z);
}
SGVec3 sgVec3Add(SGVec3 a, SGVec3 b)
{
    return sgVec3f(a.x + b.x, a.y + b.y, a.z + b.z);
}
SGVec3 sgVec3Sub(SGVec3 a, SGVec3 b)
{
    return sgVec3f(a.x - b.x, a.y - b.y, a.z - b.z);
}
SGVec3 sgVec3Mul(SGVec3 a, SGVec3 b)
{
    return sgVec3f(a.x * b.x, a.y * b.y, a.z * b.z);
}
SGVec3 sgVec3Div(SGVec3 a, SGVec3 b)
{
    return sgVec3f(a.x / b.x, a.y / b.y, a.z / b.z);
}

float sgVec3Dot(SGVec3 a, SGVec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
SGVec3 sgVec3Cross(SGVec3 a, SGVec3 b)
{
    return sgVec3f(a.y * b.z - a.z * b.y, a.x * b.z - a.z * b.x, a.x * b.y - a.y * b.x);
}



SGVec4 sgVec4f(float x, float y, float z, float w)
{
    SGVec4 vec = {x, y, z, w};
    return vec;
}
SGVec4 sgVec4fv(float* f)
{
    return sgVec4f(f[0], f[1], f[2], f[3]);
}
/*SGVec4 sgVec4PolarRads(float rads, float len);
SGVec4 sgVec4PolarDegs(float degs, float len);*/
SGVec4 sgVec4Nan(void)
{
    return sgVec4f(SG_NAN, SG_NAN, SG_NAN, SG_NAN);
}

SGVec4 sgVec4Normalize(SGVec4 vec)
{
    float len = sgVec4GetLength(vec);
    return sgVec4f(vec.x / len, vec.y / len, vec.z / len, vec.w / len);
}

/*SGVec4 sgVec4SetLength(SGVec4 vec, float length)
{
    float rads = atan4(vec.y, vec.x);
    return sgVec4PolarRads(rads, length);
}*/
float sgVec4GetLength(SGVec4 vec)
{
    return hypot(hypot(vec.x, vec.y), hypot(vec.z, vec.w));
}
float sgVec4GetLength2(SGVec4 vec)
{
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w;
}

/*SGVec4 sgVec4SetAngleRads(SGVec4 vec, float rads);
float sgVec4GetAngleRads(SGVec4 vec);
SGVec4 sgVec4SetAngleDegs(SGVec4 vec, float degs);
float sgVec4GetAngleDegs(SGVec4 vec);*/

SGbool sgVec4IsNan(SGVec4 vec)
{
    return (vec.x != vec.x) || (vec.y != vec.y) || (vec.z != vec.z) || (vec.w != vec.w);
}

SGVec4 sgVec4Neg(SGVec4 a)
{
    return sgVec4f(-a.x, -a.y, -a.z, -a.w);
}
SGVec4 sgVec4Add(SGVec4 a, SGVec4 b)
{
    return sgVec4f(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}
SGVec4 sgVec4Sub(SGVec4 a, SGVec4 b)
{
    return sgVec4f(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}
SGVec4 sgVec4Mul(SGVec4 a, SGVec4 b)
{
    return sgVec4f(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}
SGVec4 sgVec4Div(SGVec4 a, SGVec4 b)
{
    return sgVec4f(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

float sgVec4Dot(SGVec4 a, SGVec4 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
//SGVec4 sgVec4Cross(SGVec4 a, SGVec4 b);
