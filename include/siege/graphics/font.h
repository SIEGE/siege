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

#ifndef __SIEGE_GRAPHICS_FONT_H__
#define __SIEGE_GRAPHICS_FONT_H__

#include "../common.h"
#include "texture.h"

#include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGCharInfo
{
    SGTexture* texture;
    float width;
    float height;
    SGuint dwidth;
    SGuint dheight;
    float xpre;
    float ypre;
    float xpost;
    float ypost;
} SGCharInfo;

typedef struct SGFont
{
    void* handle;
    char* fname;
    float height;

    SGuint numchars;
    SGCharInfo* chars;

    SGuint numcache;
    SGdchar* cachechars;
    SGCharInfo* cache;
} SGFont;

SGCharInfo* SG_EXPORT _sgFontFindCache(SGFont* font, SGdchar c);
SGbool SG_EXPORT _sgFontGetChars(SGFont* font, SGdchar* str, SGuint strlen, SGCharInfo* info);
void SG_EXPORT _sgFontToLoad(SGFont* font, SGdchar* input, SGuint inlen, SGdchar* output, SGuint* outlen);
SGbool SG_EXPORT _sgFontLoad(SGFont* font, SGdchar* chars, SGuint numchars, SGbool force);
SGubyte* SG_EXPORT _sgFontToRGBA(SGFont* font, SGubyte* data, SGuint datalen);
void SG_EXPORT _sgFontCenterOffsetT(SGFont* font, float* x, float* y, char* text);

SGFont* SG_EXPORT sgFontCreate(char* fname, float height, SGuint preload);
void SG_EXPORT sgFontDestroy(SGFont* font);

SGFont* SG_EXPORT sgFontResizeCopy(SGFont* font, float height);
SGFont* SG_EXPORT sgFontResize(SGFont* font, float height);

// has to be done to avoid doxygen bugs
#define _SG_PRINTF SG_HINT_PRINTF(4, 5)
#define _SG_VPRINTF SG_HINT_PRINTF(4, 0)

void SG_EXPORT _SG_PRINTF sgFontPrint(SGFont* font, float x, float y, char* format, ...);
void SG_EXPORT _SG_VPRINTF sgFontPrintV(SGFont* font, float x, float y, char* format, va_list args);
void SG_EXPORT sgFontPrintT(SGFont* font, float x, float y, char* text);

void SG_EXPORT _SG_PRINTF sgFontPrintCentered(SGFont* font, float x, float y, char* format, ...);
void SG_EXPORT _SG_VPRINTF sgFontPrintCenteredV(SGFont* font, float x, float y, char* format, va_list args);
void SG_EXPORT sgFontPrintCenteredT(SGFont* font, float x, float y, char* text);

// prints centered on X, but not on Y
void SG_EXPORT _SG_PRINTF sgFontPrintXCentered(SGFont* font, float x, float y, char* format, ...);
void SG_EXPORT _SG_VPRINTF sgFontPrintXCenteredV(SGFont* font, float x, float y, char* format, va_list args);
void SG_EXPORT sgFontPrintXCenteredT(SGFont* font, float x, float y, char* text);

// prints centered on Y, but not on X
void SG_EXPORT _SG_PRINTF sgFontPrintYCentered(SGFont* font, float x, float y, char* format, ...);
void SG_EXPORT _SG_VPRINTF sgFontPrintYCenteredV(SGFont* font, float x, float y, char* format, va_list args);
void SG_EXPORT sgFontPrintYCenteredT(SGFont* font, float x, float y, char* text);

void SG_EXPORT _SG_PRINTF sgFontStrSize(SGFont* font, float* x, float* y, char* format, ...);
void SG_EXPORT _SG_VPRINTF sgFontStrSizeV(SGFont* font, float* x, float* y, char* format, va_list args);
void SG_EXPORT sgFontStrSizeT(SGFont* font, float* x, float* y, char* text);

#undef _SG_PRINTF
#undef _SG_VPRINTF

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_FONT_H__
