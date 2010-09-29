#ifndef __SIEGE_UTIL_MATRIX_H__
#define __SIEGE_UTIL_MATRIX_H__

#include "../common.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGMat2
{
    float f11, f12,
          f21, f22;
} SGMat2;

typedef struct SGMat3
{
    float f11, f12, f13,
          f21, f22, f23,
          f31, f32, f33;
} SGMat3;

typedef struct SGMat4
{
    float f11, f12, f13, f14,
          f21, f22, f23, f24,
          f31, f32, f33, f34,
          f41, f42, f43, f44;
} SGMat4;

typedef struct SGMat5
{
    float f11, f12, f13, f14, f15,
          f21, f22, f23, f24, f25,
          f31, f32, f33, f34, f35,
          f41, f42, f43, f44, f45,
          f51, f52, f53, f54, f55;
} SGMat5;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_MATRIX_H__
