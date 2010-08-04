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

SGCharInfo* _sgFontFindCache(SGFont* font, SGdchar c);
SGbool _sgFontGetChars(SGFont* font, SGdchar* str, SGuint strlen, SGCharInfo* info);
void _sgFontToLoad(SGFont* font, SGdchar* input, SGuint inlen, SGdchar* output, SGuint* outlen);
SGbool _sgFontLoad(SGFont* font, SGdchar* chars, SGuint numchars, SGbool force);
SGubyte* _sgFontToRGBA(SGFont* font, SGubyte* data, SGuint datalen);
void _sgFontCenterOffsetT(SGFont* font, float* x, float* y, char* text);

SGFont* sgFontCreate(char* fname, float height, SGuint preload);
void sgFontDestroy(SGFont* font);

SGFont* sgFontResizeCopy(SGFont* font, float height);
SGFont* sgFontResize(SGFont* font, float height);

void sgFontPrint(SGFont* font, float x, float y, char* format, ...);
void sgFontPrintV(SGFont* font, float x, float y, char* format, va_list args);
void sgFontPrintT(SGFont* font, float x, float y, char* text);

void sgFontPrintCentered(SGFont* font, float x, float y, char* format, ...);
void sgFontPrintCenteredV(SGFont* font, float x, float y, char* format, va_list args);
void sgFontPrintCenteredT(SGFont* font, float x, float y, char* text);

// prints centered on X, but not on Y
void sgFontPrintXCentered(SGFont* font, float x, float y, char* format, ...);
void sgFontPrintXCenteredV(SGFont* font, float x, float y, char* format, va_list args);
void sgFontPrintXCenteredT(SGFont* font, float x, float y, char* text);

// prints centered on Y, but not on X
void sgFontPrintYCentered(SGFont* font, float x, float y, char* format, ...);
void sgFontPrintYCenteredV(SGFont* font, float x, float y, char* format, va_list args);
void sgFontPrintYCenteredT(SGFont* font, float x, float y, char* text);

void sgFontStrSize(SGFont* font, float* x, float* y, char* format, ...);
void sgFontStrSizeV(SGFont* font, float* x, float* y, char* format, va_list args);
void sgFontStrSizeT(SGFont* font, float* x, float* y, char* text);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_FONT_H__
