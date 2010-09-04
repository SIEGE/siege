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

void SG_EXPORT SG_HINT_PRINTF(4, 5) sgFontPrint(SGFont* font, float x, float y, char* format, ...);
void SG_EXPORT SG_HINT_PRINTF(4, 0) sgFontPrintV(SGFont* font, float x, float y, char* format, va_list args);
void SG_EXPORT sgFontPrintT(SGFont* font, float x, float y, char* text);

void SG_EXPORT SG_HINT_PRINTF(4, 5) sgFontPrintCentered(SGFont* font, float x, float y, char* format, ...);
void SG_EXPORT SG_HINT_PRINTF(4, 0) sgFontPrintCenteredV(SGFont* font, float x, float y, char* format, va_list args);
void SG_EXPORT sgFontPrintCenteredT(SGFont* font, float x, float y, char* text);

// prints centered on X, but not on Y
void SG_EXPORT SG_HINT_PRINTF(4, 5) sgFontPrintXCentered(SGFont* font, float x, float y, char* format, ...);
void SG_EXPORT SG_HINT_PRINTF(4, 0) sgFontPrintXCenteredV(SGFont* font, float x, float y, char* format, va_list args);
void SG_EXPORT sgFontPrintXCenteredT(SGFont* font, float x, float y, char* text);

// prints centered on Y, but not on X
void SG_EXPORT SG_HINT_PRINTF(4, 5) sgFontPrintYCentered(SGFont* font, float x, float y, char* format, ...);
void SG_EXPORT SG_HINT_PRINTF(4, 0) sgFontPrintYCenteredV(SGFont* font, float x, float y, char* format, va_list args);
void SG_EXPORT sgFontPrintYCenteredT(SGFont* font, float x, float y, char* text);

void SG_EXPORT SG_HINT_PRINTF(4, 5) sgFontStrSize(SGFont* font, float* x, float* y, char* format, ...);
void SG_EXPORT SG_HINT_PRINTF(4, 0) sgFontStrSizeV(SGFont* font, float* x, float* y, char* format, va_list args);
void SG_EXPORT sgFontStrSizeT(SGFont* font, float* x, float* y, char* text);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_FONT_H__
