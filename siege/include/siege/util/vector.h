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

SGVec2 sgVec2f(float x, float y);
SGVec2 sgVec2fv(float* f);
SGVec2 sgVec2PolarRads(float rads, float len);
SGVec2 sgVec2PolarDegs(float degs, float len);
SGVec2 sgVec2Nan(void);

SGVec2 sgVec2Normalize(SGVec2 vec);

SGVec2 sgVec2SetLength(SGVec2 vec, float length);
float sgVec2GetLength(SGVec2 vec);
float sgVec2GetLength2(SGVec2 vec);

SGVec2 sgVec2SetAngleRads(SGVec2 vec, float rads);
float sgVec2GetAngleRads(SGVec2 vec);
SGVec2 sgVec2SetAngleDegs(SGVec2 vec, float degs);
float sgVec2GetAngleDegs(SGVec2 vec);

SGbool sgVec2IsNan(SGVec2 vec);

SGVec2 sgVec2Neg(SGVec2 a);
SGVec2 sgVec2Add(SGVec2 a, SGVec2 b);
SGVec2 sgVec2Sub(SGVec2 a, SGVec2 b);
SGVec2 sgVec2Mul(SGVec2 a, SGVec2 b);
SGVec2 sgVec2Div(SGVec2 a, SGVec2 b);

float sgVec2Dot(SGVec2 a, SGVec2 b);
float sgVec2Cross(SGVec2 a, SGVec2 b);



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
