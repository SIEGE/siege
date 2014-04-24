#ifndef __SIEGE_TYPES_H__
#define __SIEGE_TYPES_H__

#include <stdint.h>

/// @{
typedef uint8_t  SGbool;
/// \brief Equivalent to SGuint
typedef uint32_t SGenum;
/// @}

/// \name Characters
/// @{
typedef char     SGchar;
#if 0 // TODO: replace with __STDC_VERSION__ for C1x
typedef char16_t SGwchar;
typedef char32_t SGdchar;
#else // C1x
typedef uint16_t SGwchar;
typedef uint32_t SGdchar;
#endif // C1x
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
