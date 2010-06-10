#ifndef __SIEGE_COMMON_H__
#define __SIEGE_COMMON_H__

#include <stdint.h>

typedef uint8_t  SGchar;
typedef uint16_t SGwchar;
typedef uint32_t SGdchar;

typedef uint8_t  SGbool;
typedef uint32_t SGenum;

typedef int8_t   SGbyte;
typedef uint8_t  SGubyte;
typedef int16_t  SGshort;
typedef uint16_t SGushort;
typedef int32_t  SGint;
typedef uint32_t SGuint;
typedef int64_t  SGlong;
typedef uint64_t SGulong;

typedef float  SGfloat;
typedef double SGdouble;

#ifdef __GCC__
#define SG_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define SG_DEPRECATED __declspec(deprecated)
#else
#define SG_DEPRECATED
#endif // __GCC__

// use test
#define SIEGE_TEST

#ifndef SG_EXPORT
//#define SG_EXPORT _cdecl
#define SG_EXPORT
#endif

#define SG_INTERFACE_VMAJOR 0
#define SG_INTERFACE_VMINOR 1
#define SG_INTERFACE_VPATCH 2

#define SG_TRUE  1
#define SG_FALSE 0

#define SG_OK            0
#define SG_NO_ERROR      0
#define SG_UNKNOWN_ERROR 1
#define SG_INVALID_VALUE 2

#define SG_MODULE_WINDOW       0x01
#define SG_MODULE_INPUT        0x02
#define SG_MODULE_CORE         (SG_MODULE_WINDOW | SG_MODULE_INPUT)
#define SG_MODULE_GRAPHICS     0x04
#define SG_MODULE_GRAPHICSLOAD 0x08
#define SG_MODULE_AUDIO        0x10
#define SG_MODULE_AUDIOLOAD    0x20
#define SG_MODULE_FONTLOAD     0x40
#define SG_MODULE_PHYSICS      0x80

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

#define SG_GRAPHICS_PRIMITIVE_POINTS            0x01
#define SG_GRAPHICS_PRIMITIVE_LINES             0x02
#define SG_GRAPHICS_PRIMITIVE_LINE_STRIP        0x03
#define SG_GRAPHICS_PRIMITIVE_LINE_FAN          0x04
#define SG_GRAPHICS_PRIMITIVE_LINE_LOOP         0x05
#define SG_GRAPHICS_PRIMITIVE_TRIANGLES         0x06
#define SG_GRAPHICS_PRIMITIVE_TRIANGLE_STRIP    0x07
#define SG_GRAPHICS_PRIMITIVE_TRIANGLE_FAN      0x08
//#define SG_GRAPHICS_PRIMITIVE_TRIANGLE_LOOP     0x09
#define SG_GRAPHICS_PRIMITIVE_QUADS             0x0A
#define SG_GRAPHICS_PRIMITIVE_QUAD_STRIP        0x0B
//#define SG_GRAPHICS_PRIMITIVE_QUAD_FAN          0x0C
//#define SG_GRAPHICS_PRIMITIVE_QUAD_LOOP         0x0D

#define SG_GRAPHICS_PRIMITIVE_CONVEX_POLYGON        0x10
#define SG_GRAPHICS_PRIMITIVE_CONCAVE_POLYGON       0x20
#define SG_GRAPHICS_PRIMITIVE_INTERSECTING_POLYGON  0x30

#define SG_GRAPHICS_TEXTURE_NPOT    0x01

#define SG_PHYSICS_SHAPE_SEGMENT 0x01
#define SG_PHYSICS_SHAPE_POLYGON 0x02
#define SG_PHYSICS_SHAPE_CIRCLE  0x03

#define SG_PHYSICS_BODY_PASSIVE    0x01
#define SG_PHYSICS_BODY_NORMAL     0x02
#define SG_PHYSICS_BODY_SEMISTATIC 0x03
#define SG_PHYSICS_BODY_STATIC     0x04

#define SG_WINDOW_FULLSCREEN 0x01
#define SG_WINDOW_RESIZABLE  0x02

#define SG_JOYSTICK_BUTTON_NOCB 0x01
#define SG_JOYSTICK_AXIS_NOCB   0x11

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

/*typedef struct SGModuleFlags
{
    // 0-terminated
    SGenum* sAudioFormat;
    SGenum* sGraphicsPrimitive;
    SGenum* sGraphicsTextures;
} SGModuleFlags;*/

typedef struct SGModuleInfo
{
    SGushort imajor;
    SGushort iminor;
    SGushort ipatch;

    SGushort vmajor;
    SGushort vminor;
    SGushort vpatch;

    SGuint type;
    char* name;
    //char* longname;
    //char* description;

    void* data;
} SGModuleInfo;

#endif // __SIEGE_COMMON_H__
