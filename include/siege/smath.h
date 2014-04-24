#ifndef __SIEGE_SMATH_H__
#define __SIEGE_SMATH_H__

#include <math.h>
#include <float.h>

/********** SG_NAN **********/
#ifdef NAN
#define SG_NAN NAN
#elif defined(__GNUC__)
#define SG_NAN __builtin_nanf("0")
#elif defined(_MSC_VER)
union _SG_MSVC_NAN_HACK
{
    unsigned char bytes[4];
    float value;
} ;
/// \todo Get this to the proper value and test
static union _SG_MSVC_NAN_HACK _sg_msvc_nanHack = {{0x01 , 0x00, 0xC0, 0x7F}};
#define SG_NAN (_sg_msvc_nanHack.value)
#else
#define SG_NAN 0.0f/0.0f
#endif /* SG_NAN */

/********** SG_INF **********/
#ifdef INFINITY
#define SG_INF INFINITY
#elif defined(__GNUC__)
#define SG_INF __builtin_inff()
#elif defined(_MSC_VER)
union _SG_MSVC_INF_HACK
{
    unsigned char bytes[4];
    float value;
} ;
static union _SG_MSVC_INF_HACK _sg_msvc_infHack = {{0x00, 0x00, 0x80, 0x7F}};
#define SG_INF (_sg_msvc_infHack.value)
#else
#define SG_INF 1e1000f
#endif /* SG_INF */

/********** SG_PI **********/
#ifdef M_PI
#define SG_PI M_PI
#elif defined(PI)
#define SG_PI PI
#else
#define SG_PI 3.14159265358979323846
#endif /* SG_PI */

/*
 * Using this will allow me to set the epsilon, just in case some system doesn't
 * define FLT_EPSILON
 *
 * TODO: Name this just `SG_EPSILON` instead?
 */
#define SG_FLT_EPSILON  FLT_EPSILON

/**
 * \name Some commonly used macros
 * \warning
 *    These are macros - this means that their arguments may be evaluated more than once!
 */
/// @{
#define SG_MAX(x, y)                (((x) > (y)) ? (x) : (y))
#define SG_MIN(x, y)                (((x) < (y)) ? (x) : (y))
#define SG_ABS(x)                   (((x) < 0) ? -(x) : (x))
#define SG_SIGN(x)                  (((x) > 0) - ((x) < 0))
#define SG_PSIGN(x)                 (((x) >= 0) - ((x) < 0))
#define SG_IN_RANGE(x, min, max)    ((min) <= (x) && (x) <= (max))
#define SG_IN_XRANGE(x, a, b)       SG_IN_RANGE(x, SG_MIN(a, b), SG_MAX(a, b))

#endif /* __SIEGE_SMATH_H__ */
