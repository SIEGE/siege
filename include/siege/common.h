/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "license.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
*/

#ifndef __SIEGE_COMMON_H__
#define __SIEGE_COMMON_H__

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

// @{
typedef void     SGvoid;
typedef uint8_t  SGbool;
/// \brief Equivalent to SGuint
typedef uint32_t SGenum;
// @}

/// \name Characters
// @{
typedef uint8_t  SGchar;
typedef uint16_t SGwchar;
typedef uint32_t SGdchar;
// }@

/**
    \name Integers

    Sizes:
    - SG[u]byte: 8 bits
    - SG[u]short: 16 bits
    - SG[u]int: 32 bits
    - SG[u]long: 64 bits
*/
// @{
typedef int8_t   SGbyte;
typedef uint8_t  SGubyte;
typedef int16_t  SGshort;
typedef uint16_t SGushort;
typedef int32_t  SGint;
typedef uint32_t SGuint;
typedef int64_t  SGlong;
typedef uint64_t SGulong;
// @}

/// \name Floating point
// @{
typedef float  SGfloat;
typedef double SGdouble;
// @}

/**
    \brief Used for things like pasting together SG_INTERFACE_VSTRING
*/
// @{
#define _SG_STRING(P) #P
#define _SG_STRING_MACRO(P) _SG_STRING(P)
// @}

/**
    \name Hints

    Different hints which give the compiler more info, in order to produce warning messages and similar where applicable.
*/
// @{
#ifdef __GNUC__
#   define SG_HINT_DEPRECATED __attribute__((deprecated))
#   define SG_HINT_PRINTF(str, chk) __attribute__((format(printf, str, chk)))
#elif defined(_MSC_VER)
#   define SG_HINT_DEPRECATED __declspec(deprecated)
#   define SG_HINT_PRINTF(str, chk)
#else
/**
    \brief Deprecated function hint

    Indicates that the function is deprecated and thus scheduled for removal. Usage of deprecated functions is not recommended.
*/
#   define SG_HINT_DEPRECATED
/**
    \brief Printf-like syntax hint
    \param str Index of the format string (starting with 1)
    \param chk Index of the first varargs (starting with 1) or 0 if the function accepts va_args directly

    Indicates that the syntax of the function resembles that of printf.
*/
#   define SG_HINT_PRINTF(str, chk)
#endif // __GCC__
// @}

/**
    \brief Use test functionality
    \deprecated
        This is included for testing purposes and therefore may be removed in the future.

    Defined to indicate that some "test" functionality should be used in the modules.
*/
#define SIEGE_TEST

#ifndef SG_EXPORT
#   if defined(__WIN32)
#       define SG_EXPORT _cdecl
#   else
/**
    \brief Exported in siege calling convention

    This is used in all SIEGE functions. SIEGE currently uses the cdecl calling convention.
*/
#       define SG_EXPORT
#   endif  // defined(__WIN32)
#endif // defined(SG_EXPORT)

/**
    \name Version information
*/
// @{
#define SG_VERSION_MAJOR 0
#define SG_VERSION_MINOR 1
#define SG_VERSION_PATCH 7
/**
    \brief Version string

    In VMAJOR.VMINOR.VPATCH form, for example "0.1.5".
*/
#define SG_VERSION_STRING ( _SG_STRING_MACRO(SG_VERSION_MAJOR) "." _SG_STRING_MACRO(SG_VERSION_MINOR) "." _SG_STRING_MACRO(SG_VERSION_PATCH) )
// @}

/**
    \name Booleans

    These are used in conjunction with \ref SGbool "SGbool".
*/
// @{
#define SG_TRUE  1
#define SG_FALSE 0
// @}

/**
    \name Floating point constants
*/
// @{
#ifndef NAN
#	ifdef __GNUC__
#		define SG_NAN __builtin_nanf("0")
#	elif defined(_MSC_VER)
		union _SG_MSVC_NAN_HACK
		{
			unsigned uint8_t bytes[4];
			float value;
		} ;
		/// \todo Get this to the proper value and test
		static union _SG_MSVC_NAN_HACK _sg_msvc_nanHack = {{0x01 , 0x00, 0xC0, 0x7F}};
#		define SG_NAN (_sg_msvc_nanHack.value)
#	else
#		define SG_NAN 0.0f/0.0f
#	endif // __GNUC__ / _MSC_VER / other
#else
/**
 * Used by some functions to indicate "invalid value" when returning.
 */
#	define SG_NAN NAN
#endif // NAN

#ifndef INFINITY
#	ifdef __GNUC__
#		define SG_INF __builtin_inff()
#	elif defined(_MSC_VER)
		union _SG_MSVC_INF_HACK
		{
			unsigned uint8_t bytes[4];
			float value;
		} ;
		static union _SG_MSVC_INF_HACK _sg_msvc_infHack = {{0x00, 0x00, 0x80, 0x7F}};
#		define SG_INF (_sg_msvc_infHack.value)
#	else
#		define SG_INF 1e1000f
#	endif // __GNUC__ / _MSC_VER / other
#else
/**
 * Currently used with physics, to indicate infinite mass (or moment of inertia).
 */
#	define SG_INF INFINITY
#endif // INFINITY
// @}

/**
    \name Module error values

    These values are to be returned from backend modules, to indicate roughly if (and which) error has occured.

    They are currently not used in the frontend -> client space, but they may be in the future.
*/
// @{
#define SG_OK            0
#define SG_NO_ERROR      0
#define SG_UNKNOWN_ERROR 1
#define SG_INVALID_VALUE 2
// }@

/**
    \name Module types

    Used in modules, to indicate which interface groups they implement. These are \b not used in SIEGE frontend - they are merely used in other modules, for checking module compatibility.
*/
// @{
#define SG_MODULE_WINDOW       0x01
#define SG_MODULE_INPUT        0x02
#define SG_MODULE_CORE         (SG_MODULE_WINDOW | SG_MODULE_INPUT)
#define SG_MODULE_GRAPHICS     0x04
#define SG_MODULE_GRAPHICSLOAD 0x08
#define SG_MODULE_AUDIO        0x10
#define SG_MODULE_AUDIOLOAD    0x20
#define SG_MODULE_FONTLOAD     0x40
#define SG_MODULE_PHYSICS      0x80
// }@

/**
    \name Audio formats

    These are used to indicate the format of the data passed to audio buffers.
*/
// @{
#define SG_AUDIO_FORMAT_S8  0x01
#define SG_AUDIO_FORMAT_S16 0x02
#define SG_AUDIO_FORMAT_S24 0x03
#define SG_AUDIO_FORMAT_S32 0x04

#define SG_AUDIO_FORMAT_U8  0x05
#define SG_AUDIO_FORMAT_U16 0x06
#define SG_AUDIO_FORMAT_U24 0x07
#define SG_AUDIO_FORMAT_U32 0x08

#define SG_AUDIO_FORMAT_F   0x0A
#define SG_AUDIO_FORMAT_D   0x0B
// }@

/**
    \name Graphics primitives types
*/
// @{
/**
    Each vertex makes a point.
*/
#define SG_GRAPHICS_PRIMITIVE_POINTS            0x01
/**
    Each 2 vertices make a line. The number of passed vertices must be even.
*/
#define SG_GRAPHICS_PRIMITIVE_LINES             0x02
/**
    Last vertex of previous line becomes the first vertex of the next one, drawing a connected line defined by the set of vertices.
    \sa
        SG_GRAPHICS_PRIMITIVE_TRIANGLE_STRIP
        SG_GRAPHICS_PRIMITIVE_QUAD_STRIP
*/
#define SG_GRAPHICS_PRIMITIVE_LINE_STRIP        0x03
/**
    The first vertex is the "origin" for all the lines.
    \sa
        SG_GRAPHICS_PRIMITIVE_TRIANGLE_FAN
*/
#define SG_GRAPHICS_PRIMITIVE_LINE_FAN          0x04
/**
    Lines are created in a loop. This is similar to \ref SG_GRAPHICS_PRIMITIVE_LINE_STRIP "SG_GRAPHICS_PRIMITIVE_LINE_STRIP", except that the last and first vertex become connected by a line.
    \sa
        SG_GRAPHICS_PRIMITIVE_LINE_STRIP
*/
#define SG_GRAPHICS_PRIMITIVE_LINE_LOOP         0x05
/**
    Each 3 vertices make a triangle. The number of passed vertices must be a multiple of 3.
*/
#define SG_GRAPHICS_PRIMITIVE_TRIANGLES         0x06
/**
    Last 2 vertices of the previous triangle become the first two vertices of the next one, making a connected hull. This is analogous to \ref SG_GRAPHICS_PRIMITIVE_LINE_STRIP "SG_GRAPHICS_PRIMITIVE_LINE_STRIP".
    \sa
        SG_GRAPHICS_PRIMITIVE_LINE_STRIP
*/
#define SG_GRAPHICS_PRIMITIVE_TRIANGLE_STRIP    0x07
/**
    The first vertex becomes a "common point" between all the triangles. This is analogous to \ref SG_GRAPHICS_PRIMITIVE_LINE_FAN "SG_GRAPHICS_PRIMITIVE_LINE_FAN".
    \sa
        SG_GRAPHICS_PRIMITIVE_LINE_FAN
*/
#define SG_GRAPHICS_PRIMITIVE_TRIANGLE_FAN      0x08
//#define SG_GRAPHICS_PRIMITIVE_TRIANGLE_LOOP     0x09
/**
    Each 4 vertices make a quad. The number of passed vertices must be a multiple of 4.
*/
#define SG_GRAPHICS_PRIMITIVE_QUADS             0x0A
/**
    Last 2 vertices of the previous quad become the first two vertices of the next one. This is analogous to \ref SG_GRAPHICS_PRIMITIVE_LINE_STRIP "SG_GRAPHICS_PRIMITIVE_LINE_STRIP" and \ref SG_GRAPHICS_PRIMITIVE_TRIANGLE_STRIP "SG_GRAPHICS_PRIMITIVE_TRIANGLE_STRIP".
    \sa
        SG_GRAPHICS_PRIMITIVE_LINE_STRIP
        SG_GRAPHICS_PRIMITIVE_TRIANGLE_STRIP
*/
#define SG_GRAPHICS_PRIMITIVE_QUAD_STRIP        0x0B
//#define SG_GRAPHICS_PRIMITIVE_QUAD_FAN          0x0C
//#define SG_GRAPHICS_PRIMITIVE_QUAD_LOOP         0x0D

/**
    Create a convex polygon - the vertices passed are assumed to form one.
*/
#define SG_GRAPHICS_PRIMITIVE_CONVEX_POLYGON        0x10
/**
    Create polygon that is possibly concave (but not self-intersecting).
    \note
        The vertices passed may be implicitly converted to a series of convex polygons.
    \note
        It is perfectly fine (if not best for performance) to pass a convex polygon as a concave one.
*/
#define SG_GRAPHICS_PRIMITIVE_CONCAVE_POLYGON       0x20
/**
    Create a polygon that is possibly self-intersecting.
    \note
        The vertices passed may be implicitly converted to a series of convex polygons.
    \note
        It is perfectly fine (if not best for performance) to pass non-intersecting polygon as an intersecting one.
*/
#define SG_GRAPHICS_PRIMITIVE_INTERSECTING_POLYGON  0x30
// }@

/**
    \name Graphics info flags
    \deprecated
        These may be removed in the future.
*/
// @{
/**
    \brief Cannot use NPOT textures

    This flag indicates that the backend does not support power-of-two textures, and that conversion to such sizes may be necessarry by the frontend.
*/
#define SG_GRAPHICS_TEXTURE_NPOT    0x01
// }@

/**
    \name Physics shapes
*/
// @{
/**
    Segment shape, defined by two points and possibly a width.
*/
#define SG_PHYSICS_SHAPE_SEGMENT 0x01
/**
    Polygon shape, defined by a set of points.
*/
#define SG_PHYSICS_SHAPE_POLYGON 0x02
/**
    A circle shape, defined by an inner and outer radius.
*/
#define SG_PHYSICS_SHAPE_CIRCLE  0x03
// @}

/**
    \name Physics body types
*/
// @{
/**
    Completely non-interactive body type.
*/
#define SG_PHYSICS_BODY_PASSIVE    0x01
/**
    "Normal" body type, with normal physics interaction.
*/
#define SG_PHYSICS_BODY_NORMAL     0x02
/**
    A body type with seemingly infinite mass, but still movable (usually through user interaction).
    \note
        May be deprecated in the future.
*/
#define SG_PHYSICS_BODY_SEMISTATIC 0x03
/**
    A completely static, non-movable body type with seemingly infinite mass.
*/
#define SG_PHYSICS_BODY_STATIC     0x04
// @}

/**
    \name Window flags
*/
// @{
#define SG_WINDOW_FULLSCREEN 0x01
#define SG_WINDOW_RESIZABLE  0x02
// @}

/**
    \name Keyboard keys
*/
// @{
#define SG_KEYBOARD_KEY_UNKNOWN     0x000
#define SG_KEYBOARD_KEY_SPACE       0x020
#define SG_KEYBOARD_KEY_ESC         0x100
#define SG_KEYBOARD_KEY_F1          0x101
#define SG_KEYBOARD_KEY_F2          0x102
#define SG_KEYBOARD_KEY_F3          0x103
#define SG_KEYBOARD_KEY_F4          0x104
#define SG_KEYBOARD_KEY_F5          0x105
#define SG_KEYBOARD_KEY_F6          0x106
#define SG_KEYBOARD_KEY_F7          0x107
#define SG_KEYBOARD_KEY_F8          0x108
#define SG_KEYBOARD_KEY_F9          0x109
#define SG_KEYBOARD_KEY_F10         0x10A
#define SG_KEYBOARD_KEY_F11         0x10B
#define SG_KEYBOARD_KEY_F12         0x10C
#define SG_KEYBOARD_KEY_F13         0x10D
#define SG_KEYBOARD_KEY_F14         0x10E
#define SG_KEYBOARD_KEY_F15         0x10F
#define SG_KEYBOARD_KEY_F16         0x110
#define SG_KEYBOARD_KEY_F17         0x111
#define SG_KEYBOARD_KEY_F18         0x112
#define SG_KEYBOARD_KEY_F19         0x113
#define SG_KEYBOARD_KEY_F20         0x114
#define SG_KEYBOARD_KEY_F21         0x115
#define SG_KEYBOARD_KEY_F22         0x116
#define SG_KEYBOARD_KEY_F23         0x117
#define SG_KEYBOARD_KEY_F24         0x118
#define SG_KEYBOARD_KEY_F25         0x119
#define SG_KEYBOARD_KEY_UP          0x200
#define SG_KEYBOARD_KEY_DOWN        0x201
#define SG_KEYBOARD_KEY_LEFT        0x202
#define SG_KEYBOARD_KEY_RIGHT       0x203
#define SG_KEYBOARD_KEY_LSHIFT      0x210
#define SG_KEYBOARD_KEY_RSHIFT      0x211
#define SG_KEYBOARD_KEY_LCTRL       0x220
#define SG_KEYBOARD_KEY_RCTRL       0x221
#define SG_KEYBOARD_KEY_LALT        0x230
#define SG_KEYBOARD_KEY_RALT        0x231
#define SG_KEYBOARD_KEY_TAB         0x240
#define SG_KEYBOARD_KEY_ENTER       0x241
#define SG_KEYBOARD_KEY_BACKSPACE   0x242
#define SG_KEYBOARD_KEY_INSERT      0x250
#define SG_KEYBOARD_KEY_DELETE      0x251
#define SG_KEYBOARD_KEY_HOME        0x252
#define SG_KEYBOARD_KEY_END         0x253
#define SG_KEYBOARD_KEY_PAGEUP      0x254
#define SG_KEYBOARD_KEY_PAGEDOWN    0x255
#define SG_KEYBOARD_KEY_KP0         0x300
#define SG_KEYBOARD_KEY_KP1         0x301
#define SG_KEYBOARD_KEY_KP2         0x302
#define SG_KEYBOARD_KEY_KP3         0x303
#define SG_KEYBOARD_KEY_KP4         0x304
#define SG_KEYBOARD_KEY_KP5         0x305
#define SG_KEYBOARD_KEY_KP6         0x306
#define SG_KEYBOARD_KEY_KP7         0x307
#define SG_KEYBOARD_KEY_KP8         0x308
#define SG_KEYBOARD_KEY_KP9         0x309
#define SG_KEYBOARD_KEY_KP_ADD      0x310
#define SG_KEYBOARD_KEY_KP_SUBTRACT 0x311
#define SG_KEYBOARD_KEY_KP_MULTIPLY 0x312
#define SG_KEYBOARD_KEY_KP_DIVIDE   0x313
#define SG_KEYBOARD_KEY_KP_DECIMAL  0x314
#define SG_KEYBOARD_KEY_KP_EQUAL    0x315
#define SG_KEYBOARD_KEY_KP_ENTER    0x316
// @}

/**
    \name Mouse buttons
*/
// @{
#define SG_MOUSE_BUTTON_LEFT   1
#define SG_MOUSE_BUTTON_RIGHT  2
#define SG_MOUSE_BUTTON_MIDDLE 3
// @}

/**
    \brief Module info

    Used in modules, to send information about the module to SIEGE and other modules.
*/
typedef struct SGModuleInfo
{
    /**
        \name SIEGE version
    */
    // @{
    SGushort vmajor;
    SGushort vminor;
    SGushort vpatch;
    // @}

    /**
        \name Module version
    */
    // @{
    SGushort mmajor;
    SGushort mminor;
    SGushort mpatch;
    // @}

    SGuint type;
    char* name;
    //char* longname;
    //char* description;

    void* data;
} SGModuleInfo;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_COMMON_H__
