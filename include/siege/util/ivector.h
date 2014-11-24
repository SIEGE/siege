#ifndef __SIEGE_UTIL_IVECTOR_H__
#define __SIEGE_UTIL_IVECTOR_H__

#include "../common.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

struct SGVec2;
struct SGVec3;
struct SGVec4;

typedef struct SGIVec2
{
    SGint x, y;
} SGIVec2;

typedef struct SGIVec3
{
    SGint x, y, z;
} SGIVec3;

typedef struct SGIVec4
{
    SGint x, y, z, w;
} SGIVec4;

/**
    \memberof SGIVec2
    \brief Create a 2D vector from coordinates
    \param x X coordinate
    \param y Y coordinate
    \return A new 2D vector.
*/
SGIVec2 SG_CALL sgIVec2i(SGint x, SGint y);
SGIVec2 SG_CALL sgIVec2ip(const SGint* xy);
SGIVec2 SG_CALL sgIVec2fv(struct SGVec2 vec);

float SG_CALL sgIVec2Length(SGIVec2 vec);
SGint SG_CALL sgIVec2Length2(SGIVec2 vec);

SGIVec2 SG_CALL sgIVec2Neg(SGIVec2 a);
SGIVec2 SG_CALL sgIVec2Add(SGIVec2 a, SGIVec2 b);
SGIVec2 SG_CALL sgIVec2Sub(SGIVec2 a, SGIVec2 b);
SGIVec2 SG_CALL sgIVec2Mul(SGIVec2 a, SGIVec2 b);
SGIVec2 SG_CALL sgIVec2Div(SGIVec2 a, SGIVec2 b);

SGIVec2 SG_CALL sgIVec2Addi(SGIVec2 a, SGint i);
SGIVec2 SG_CALL sgIVec2Subi(SGIVec2 a, SGint i);
SGIVec2 SG_CALL sgIVec2Muli(SGIVec2 a, SGint i);
SGIVec2 SG_CALL sgIVec2Divi(SGIVec2 a, SGint i);

SGIVec2 SG_CALL sgIVec2QMul2(SGIVec2 a, SGIVec2 b);

float SG_CALL sgIVec2Distance(SGIVec2 a, SGIVec2 b);
SGint SG_CALL sgIVec2Distance2(SGIVec2 a, SGIVec2 b);

SGIVec2 SG_CALL sgIVec2Min(SGIVec2 a, SGIVec2 b);
SGIVec2 SG_CALL sgIVec2Max(SGIVec2 a, SGIVec2 b);
SGIVec2 SG_CALL sgIVec2Abs(SGIVec2 a);
SGIVec2 SG_CALL sgIVec2Wrap(SGIVec2 a, SGIVec2 min, SGIVec2 max);
SGIVec2 SG_CALL sgIVec2Clamp(SGIVec2 a, SGIVec2 min, SGIVec2 max);
SGIVec2 SG_CALL sgIVec2XWrap(SGIVec2 a, SGIVec2 min, SGIVec2 max);
SGIVec2 SG_CALL sgIVec2XClamp(SGIVec2 a, SGIVec2 min, SGIVec2 max);

SGint SG_CALL sgIVec2Dot(SGIVec2 a, SGIVec2 b);
/*
 * Calculates the perpendicular dot product.
 *
 * This is what some call the 2D cross product, though I have opted to call the
 * (IMO more mathematically correct) the generalization below "cross product".
 */
SGint SG_CALL sgIVec2PDot(SGIVec2 a, SGIVec2 b);
SGIVec2 SG_CALL sgIVec2Cross(SGIVec2 a);


SGIVec3 SG_CALL sgIVec3i(SGint x, SGint y, SGint z);
SGIVec3 SG_CALL sgIVec3ip(const SGint* xyz);
SGIVec3 SG_CALL sgIVec3fv(struct SGVec3 vec);

float SG_CALL sgIVec3Length(SGIVec3 vec);
SGint SG_CALL sgIVec3Length2(SGIVec3 vec);

SGIVec3 SG_CALL sgIVec3Neg(SGIVec3 a);
SGIVec3 SG_CALL sgIVec3Add(SGIVec3 a, SGIVec3 b);
SGIVec3 SG_CALL sgIVec3Sub(SGIVec3 a, SGIVec3 b);
SGIVec3 SG_CALL sgIVec3Mul(SGIVec3 a, SGIVec3 b);
SGIVec3 SG_CALL sgIVec3Div(SGIVec3 a, SGIVec3 b);

SGIVec3 SG_CALL sgIVec3Addi(SGIVec3 a, SGint i);
SGIVec3 SG_CALL sgIVec3Subi(SGIVec3 a, SGint i);
SGIVec3 SG_CALL sgIVec3Muli(SGIVec3 a, SGint i);
SGIVec3 SG_CALL sgIVec3Divi(SGIVec3 a, SGint i);

float SG_CALL sgIVec3Distance(SGIVec3 a, SGIVec3 b);
SGint SG_CALL sgIVec3Distance2(SGIVec3 a, SGIVec3 b);

SGIVec3 SG_CALL sgIVec3Min(SGIVec3 a, SGIVec3 b);
SGIVec3 SG_CALL sgIVec3Max(SGIVec3 a, SGIVec3 b);
SGIVec3 SG_CALL sgIVec3Abs(SGIVec3 a);
SGIVec3 SG_CALL sgIVec3Wrap(SGIVec3 a, SGIVec3 min, SGIVec3 max);
SGIVec3 SG_CALL sgIVec3Clamp(SGIVec3 a, SGIVec3 min, SGIVec3 max);
SGIVec3 SG_CALL sgIVec3XWrap(SGIVec3 a, SGIVec3 min, SGIVec3 max);
SGIVec3 SG_CALL sgIVec3XClamp(SGIVec3 a, SGIVec3 min, SGIVec3 max);

SGint SG_CALL sgIVec3Dot(SGIVec3 a, SGIVec3 b);
SGIVec3 SG_CALL sgIVec3Cross(SGIVec3 a, SGIVec3 b);
// A dot (B cross C)
SGint SG_CALL sgIVec3Triple(SGIVec3 a, SGIVec3 b, SGIVec3 c);


SGIVec4 SG_CALL sgIVec4i(SGint x, SGint y, SGint z, SGint w);
SGIVec4 SG_CALL sgIVec4ip(const SGint* xyzw);
SGIVec4 SG_CALL sgIVec4fv(struct SGVec4 vec);

float SG_CALL sgIVec4Length(SGIVec4 vec);
SGint SG_CALL sgIVec4Length2(SGIVec4 vec);

SGIVec4 SG_CALL sgIVec4Neg(SGIVec4 a);
SGIVec4 SG_CALL sgIVec4Add(SGIVec4 a, SGIVec4 b);
SGIVec4 SG_CALL sgIVec4Sub(SGIVec4 a, SGIVec4 b);
SGIVec4 SG_CALL sgIVec4Mul(SGIVec4 a, SGIVec4 b);
SGIVec4 SG_CALL sgIVec4Div(SGIVec4 a, SGIVec4 b);

SGIVec4 SG_CALL sgIVec4Addi(SGIVec4 a, SGint i);
SGIVec4 SG_CALL sgIVec4Subi(SGIVec4 a, SGint i);
SGIVec4 SG_CALL sgIVec4Muli(SGIVec4 a, SGint i);
SGIVec4 SG_CALL sgIVec4Divi(SGIVec4 a, SGint i);

SGIVec4 SG_CALL sgIVec4QMul4(SGIVec4 a, SGIVec4 b);

float SG_CALL sgIVec4Distance(SGIVec4 a, SGIVec4 b);
SGint SG_CALL sgIVec4Distance2(SGIVec4 a, SGIVec4 b);

SGIVec4 SG_CALL sgIVec4Min(SGIVec4 a, SGIVec4 b);
SGIVec4 SG_CALL sgIVec4Max(SGIVec4 a, SGIVec4 b);
SGIVec4 SG_CALL sgIVec4Abs(SGIVec4 a);
SGIVec4 SG_CALL sgIVec4Wrap(SGIVec4 a, SGIVec4 min, SGIVec4 max);
SGIVec4 SG_CALL sgIVec4Clamp(SGIVec4 a, SGIVec4 min, SGIVec4 max);
SGIVec4 SG_CALL sgIVec4XWrap(SGIVec4 a, SGIVec4 min, SGIVec4 max);
SGIVec4 SG_CALL sgIVec4XClamp(SGIVec4 a, SGIVec4 min, SGIVec4 max);

SGint SG_CALL sgIVec4Dot(SGIVec4 a, SGIVec4 b);
//SGIVec4 sgIVec4Cross(SGIVec4 a, SGIVec4 b, SGIVec4 c);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_IVECTOR_H__
