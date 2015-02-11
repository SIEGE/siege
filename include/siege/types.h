#ifndef __SIEGE_TYPES_H__
#define __SIEGE_TYPES_H__

#include <stdint.h>

/// \name Characters
/// @{
typedef char     SGchar;
/*
 * TODO: <uchar.h> was (supposedly) actually introduced in a technical report
 * *before* C11; find out the version number and use that, instead.
 */
#if __STDC_VERSION__ >= 201112L || __cplusplus >= 201103L
#include <uchar.h>
typedef char16_t SGwchar;
typedef char32_t SGdchar;
#else // C1x
typedef uint16_t SGwchar;
typedef uint32_t SGdchar;
#endif // C1x
/// @}

/// @{
typedef uint8_t  SGbool;
/// \brief Equivalent to SGuint
typedef uint32_t SGenum;
/// @}

/**
 * \name Integers
 *
 * Sizes:
 * - SG[u]byte: 8 bits
 * - SG[u]short: 16 bits
 * - SG[u]int: 32 bits
 * - SG[u]long: 64 bits
 */
/// @{
typedef int8_t     SGbyte;
typedef uint8_t  SGubyte;
typedef int16_t  SGshort;
typedef uint16_t SGushort;
typedef int32_t  SGint;
typedef uint32_t SGuint;
typedef int64_t  SGlong;
typedef uint64_t SGulong;
/// @}

/// \name Floating point
/// @{
typedef float  SGfloat;
typedef double SGdouble;
/// @}

/**
 * \name Booleans
 *
 * These are used in conjunction with \ref SGbool "SGbool".
 */
/// @{
#define SG_TRUE  1
#define SG_FALSE 0
/// @}

#endif /* __SIEGE_TYPES_H__ */
