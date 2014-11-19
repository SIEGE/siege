/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "COPYING.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */
/**
 * \file common.h
 * \brief Defines and macros used throughout SIEGE.
 */

#ifndef __SIEGE_COMMON_H__
#define __SIEGE_COMMON_H__

#include <stddef.h>
#include <assert.h>

#include "types.h" /* TEMPORARY (?) */
#include "smath.h" /* TEMPORARY */

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#if defined(SG_DEBUG) && defined(SG_NDEBUG)
#error "Both SG_DEBUG and SG_NDEBUG are defined!"
#elif !defined(SG_DEBUG) && !defined(SG_NDEBUG)
/*
 * Neither SG_DEBUG nor SG_NDEBUG are defined, so attempt to figure out whether
 * we are in a debug build or not.
 */
#ifdef NDEBUG
#define SG_NDEBUG 1
#else
#define SG_DEBUG 1
#endif /* NDEBUG */
#endif /* SG_DEBUG, SG_NDEBUG */
/* ^ Now we should have SG_NDEBUG xor SG_DEBUG defined. */

/**
 * \brief Used for things like pasting together SG_VERSION_STRING
 */
/// @{
#define _SG_STRING(P) #P
#define _SG_STRING_MACRO(P) _SG_STRING(P)
/// @}

/**
 * \name Hints
 *
 * Different hints which give the compiler more info, in order to produce warning messages and similar where applicable.
 */
/// @{
#ifdef __GNUC__
#    define SG_HINT_DEPRECATED __attribute__((deprecated))
#    define SG_HINT_PRINTF(str, chk) __attribute__((format(printf, str, chk)))
#elif defined(_MSC_VER)
#    define SG_HINT_DEPRECATED __declspec(deprecated)
#    define SG_HINT_PRINTF(str, chk)
#else
/**
 * \brief Deprecated function hint
 *
 * Indicates that the function is deprecated and thus scheduled for removal. Usage of deprecated functions is not recommended.
 */
#    define SG_HINT_DEPRECATED
/**
 * \brief Printf-like syntax hint
 * \param str Index of the format string (starting with 1)
 * \param chk Index of the first varargs (starting with 1) or 0 if the function accepts va_args directly
 *
 * Indicates that the syntax of the function resembles that of printf.
 */
#    define SG_HINT_PRINTF(str, chk)
#endif // __GCC__
/// @}

#ifndef SG_CALL
#    if defined(__WIN32)
#       define SG_CALL __cdecl
#    else
/**
 * \brief Exported in siege calling convention
 *
 * This is used in all SIEGE functions. SIEGE currently uses the cdecl calling convention.
 */
#       define SG_CALL
#    endif  // defined(__WIN32)
#endif // defined(SG_CALL)

//TODO WIN32
#ifndef SG_EXPORT
#define SG_EXPORT
#endif /* SG_EXPORT */

/**
 * \name Version information
 */
/// @{
#define SG_VERSION_MAJOR 0
#define SG_VERSION_MINOR 8
#define SG_VERSION_PATCH 4
/**
 * \brief Version string
 *
 * In VMAJOR.VMINOR.VPATCH form, for example "0.1.5".
 */
#define SG_VERSION_STRING ( _SG_STRING_MACRO(SG_VERSION_MAJOR) "." _SG_STRING_MACRO(SG_VERSION_MINOR) "." _SG_STRING_MACRO(SG_VERSION_PATCH) )
/// @}

/* TODO: Use msg */
#define SG_ASSERT(x,msg)            assert(x)
/// @}

#define SG_CMP_NEVER    0
#define SG_CMP_EQUAL    1
#define SG_CMP_NOTEQUAL 2
#define SG_CMP_LESS     3
#define SG_CMP_LEQUAL   4 /* default for DepthFunc */
#define SG_CMP_GREATER  5
#define SG_CMP_GEQUAL   6
#define SG_CMP_ALWAYS   7 /* default for AlphaFunc */

/* TODO: Put this into shape.h for SGShape, once those are added */
/**
 * Segment shape, defined by two points and possibly a width.
 */
#define SG_SHAPE_SEGMENT    0x01
/**
 * Polygon shape, defined by a set of points.
 */
#define SG_SHAPE_POLYGON    0x02
/**
 * A circle shape, defined by an inner and outer radius.
 */
#define SG_SHAPE_CIRCLE     0x03

typedef void SG_CALL SGFree(void* ptr);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_COMMON_H__
