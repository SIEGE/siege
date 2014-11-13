/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "license.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */
/**
 * \file siege/graphics/font.h
 * \brief Font handling.
 * \ingroup Graphics
 */

#ifndef __SIEGE_GRAPHICS_FONT_H__
#define __SIEGE_GRAPHICS_FONT_H__

#include "../common.h"
#include "../util/stream.h"
#include "../util/conv.h"
#include "../util/map.h"
#include "../util/rect.h"
#include "texture.h"

#include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#define SG_ALIGN_CENTER   0x00

#define SG_ALIGN_LEFT     0x01
#define SG_ALIGN_RIGHT    0x02

#define SG_ALIGN_TOP      0x10
#define SG_ALIGN_BASELINE 0x20
#define SG_ALIGN_BOTTOM   0x40

#define SG_ALIGN_HMASK    0x0F
#define SG_ALIGN_VMASK    0xF0

/**
 * \brief Character info.
 * \private
 *
 * This is the character info which holds data such as datafield
 * width, height, character width, height, etc...
 */
typedef struct SGCharInfo
{
    /**
     * \brief Character's texture.
     *
     * \todo
     *    Should multiple characters be put into a single texture?
     */
    SGTexture* texture;

    /**
     * \name Actual size
     */
    /// @{
    float width;
    float height;
    /// @}

    /**
     * \name Bitmap size
     */
    /// @{
    size_t dwidth;
    size_t dheight;
    /// @}

    /**
     * \name Local offset
     *
     * This is not cumulative with other characters - thus,
     * it does not affect the position of other characters.
     */
    /// @{
    float xpre;
    float ypre;
    /// @}

    /**
     * \name Global offset
     *
     * This \em is (unlike the local offset) cumulative with
     * other characters and does affect their position.
     */
    /// @{
    float xpost;
    float ypost;
    /// @}
} SGCharInfo;

/**
 * \brief Font info
 *
 * This buffer holds the info of a font, along
 * with the characters (both preloaded and not).
 */
typedef struct SGFont
{
    /// @{
    /**
     * \brief Internal handle
     * \private
     */
    void* handle;
    float height;    /// < Height of the font
    SGuint dpi;
    /// @}

    float ascent;
    float descent;
    float linegap;

    // char, wchar_t, utf8, utf16
    SGConv* conv[4];

    /**
     * \name Preloaded characters
     */
    /// @{
    size_t npreload;
    SGuint numchars;    /// < The number of characters
    SGCharInfo* chars;    /// < The characters themselves
    /// @}

    /**
     * \name On-demand loaded characters
     */
    /// @{
    SGuint numcache;        /// < Length of the arrays
    SGdchar* cachechars;    /// < The character UTF-32 values (keys)
    SGCharInfo* cache;        /// < Character infos (values)
    SGMap* cmap;          ///< SGdchar->SGCharInfo mapping
    /// @}

    SGStream* stream;
    SGbool del;
} SGFont;

SGCharInfo* SG_CALL _sgFontFindCache(SGFont* font, SGdchar c);
SGbool SG_CALL _sgFontGetChars(SGFont* font, SGdchar* str, SGuint strlen, SGCharInfo* info);
void SG_CALL _sgFontToLoad(SGFont* font, SGdchar* input, SGuint inlen, SGdchar* output, SGuint* outlen);
SGbool SG_CALL _sgFontLoad(SGFont* font, SGdchar* chars, SGuint numchars, SGbool force);
SGubyte* SG_CALL _sgFontToRGBA(SGFont* font, SGubyte* data, SGuint datalen);

SGdchar* SG_CALL _sgFontU16ToU32(SGFont* font, const SGwchar* text);
SGdchar* SG_CALL _sgFontU8ToU32(SGFont* font, const SGchar* text);
SGdchar* SG_CALL _sgFontWToU32(SGFont* font, const wchar_t* text);
SGdchar* SG_CALL _sgFontToU32(SGFont* font, const char* text);

SGFont* SG_CALL sgFontCreateStream(SGStream* stream, SGbool delstream, float height, SGuint dpi, SGuint preload);
/// @{
/**
 * \brief Load a font
 *
 * \param fname Filename of the font to load
 * \param height Height of the font (in pt)
 * \param preload Number of characters to preload; good values are 127 or 255.
 *
 * \return The newly created font info if successful, NULL otherwise.
 */
SGFont* SG_CALL sgFontCreate(const char* fname, float height, SGuint dpi, SGuint preload);
/**
 * \brief Destroy a font info
 *
 * \param font The font info to destroy.
 * It should not be used anymore after this call.
 */
void SG_CALL sgFontDestroy(SGFont* font);
/// @}

void SG_CALL sgFontClearCache(SGFont* font);
void SG_CALL sgFontSetHeight(SGFont* font, float height, SGuint dpi);

/**
 * \name Printing
 *
 * \param font The font face to use for printing.
 * \param x X position (left)
 * \param y Y position (baseline)
 *
 * These functions print text in a position <em>x</em>,<em>y</em>,
 * where \a x is the start, leftmost, position of the printed text
 * and \a y is the baseline.
 */
/// @{
void SG_CALL sgFontPrintfW(SGFont* font, float x, float y, const wchar_t* format, ...);
void SG_CALL sgFontPrintfvW(SGFont* font, float x, float y, const wchar_t* format, va_list args);
/**
 * \brief printf-style print
 */
void SG_CALL SG_HINT_PRINTF(4, 5) sgFontPrintf(SGFont* font, float x, float y, const char* format, ...);
/**
 * \brief vprintf-style print
 */
void SG_CALL SG_HINT_PRINTF(4, 0) sgFontPrintfv(SGFont* font, float x, float y, const char* format, va_list args);
/**
 * \brief Text-based print
 */
void SG_CALL sgFontPrintU32(SGFont* font, float x, float y, const SGdchar* text);
void SG_CALL sgFontPrintU16(SGFont* font, float x, float y, const SGwchar* text);
void SG_CALL sgFontPrintU8(SGFont* font, float x, float y, const SGchar* text);
void SG_CALL sgFontPrintW(SGFont* font, float x, float y, const wchar_t* text);
void SG_CALL sgFontPrint(SGFont* font, float x, float y, const char* text);
/// @}

void SG_CALL sgFontPrintAlignedfW(SGFont* font, float x, float y, SGenum align, const wchar_t* format, ...);
void SG_CALL sgFontPrintAlignedfvW(SGFont* font, float x, float y, SGenum align, const wchar_t* format, va_list args);

void SG_CALL SG_HINT_PRINTF(5, 6) sgFontPrintAlignedf(SGFont* font, float x, float y, SGenum align, const char* format, ...);
void SG_CALL SG_HINT_PRINTF(5, 0) sgFontPrintAlignedfv(SGFont* font, float x, float y, SGenum align, const char* format, va_list args);

void SG_CALL sgFontPrintAlignedU32(SGFont* font, float x, float y, SGenum align, const SGdchar* text);
void SG_CALL sgFontPrintAlignedU16(SGFont* font, float x, float y, SGenum align, const SGwchar* text);
void SG_CALL sgFontPrintAlignedU8(SGFont* font, float x, float y, SGenum align, const SGchar* text);
void SG_CALL sgFontPrintAlignedW(SGFont* font, float x, float y, SGenum align, const wchar_t* text);
void SG_CALL sgFontPrintAligned(SGFont* font, float x, float y, SGenum align, const char* text);

/* get the bounding rectangle of a string */
SGRect SG_CALL sgFontStrRectfW(SGFont* font, const wchar_t* format, ...);
SGRect SG_CALL sgFontStrRectfvW(SGFont* font, const wchar_t* format, va_list args);

SGRect SG_CALL SG_HINT_PRINTF(2, 3) sgFontStrRectf(SGFont* font, const char* format, ...);
SGRect SG_CALL SG_HINT_PRINTF(2, 0) sgFontStrRectfv(SGFont* font, const char* format, va_list args);

SGRect SG_CALL sgFontStrRectU32(SGFont* font, const SGdchar* text);
SGRect SG_CALL sgFontStrRectU16(SGFont* font, const SGwchar* text);
SGRect SG_CALL sgFontStrRectU8(SGFont* font, const SGchar* text);
SGRect SG_CALL sgFontStrRectW(SGFont* font, const wchar_t* text);
SGRect SG_CALL sgFontStrRect(SGFont* font, const char* text);

// need a better name for FindIndex and GetPos...
size_t SG_CALL sgFontFindIndexfW(SGFont* font, float x, float y, const wchar_t* format, ...);
size_t SG_CALL sgFontFindIndexfvW(SGFont* font, float x, float y, const wchar_t* format, va_list args);

size_t SG_CALL SG_HINT_PRINTF(4, 5) sgFontFindIndexf(SGFont* font, float x, float y, const char* format, ...);
size_t SG_CALL SG_HINT_PRINTF(4, 0) sgFontFindIndexfv(SGFont* font, float x, float y, const char* format, va_list args);

size_t SG_CALL sgFontFindIndexU32(SGFont* font, float x, float y, const SGdchar* text);
size_t SG_CALL sgFontFindIndexU16(SGFont* font, float x, float y, const SGwchar* text);
size_t SG_CALL sgFontFindIndexU8(SGFont* font, float x, float y, const SGchar* text);
size_t SG_CALL sgFontFindIndexW(SGFont* font, float x, float y, const wchar_t* text);
size_t SG_CALL sgFontFindIndex(SGFont* font, float x, float y, const char* text);

void SG_CALL sgFontGetPosfW(SGFont* font, float* x, float* y, size_t index, const wchar_t* format, ...);
void SG_CALL sgFontGetPosfvW(SGFont* font, float* x, float* y, size_t index, const wchar_t* format, va_list args);

void SG_CALL SG_HINT_PRINTF(5, 6) sgFontGetPosf(SGFont* font, float* x, float* y, size_t index, const char* format, ...);
void SG_CALL SG_HINT_PRINTF(5, 0) sgFontGetPosfv(SGFont* font, float* x, float* y, size_t index, const char* format, va_list args);

void SG_CALL sgFontGetPosU32(SGFont* font, float* x, float* y, size_t index, const SGdchar* text);
void SG_CALL sgFontGetPosU16(SGFont* font, float* x, float* y, size_t index, const SGwchar* text);
void SG_CALL sgFontGetPosU8(SGFont* font, float* x, float* y, size_t index, const SGchar* text);
void SG_CALL sgFontGetPosW(SGFont* font, float* x, float* y, size_t index, const wchar_t* text);
void SG_CALL sgFontGetPos(SGFont* font, float* x, float* y, size_t index, const char* text);

/* DEPRECATED: Use sgFontStrRect* instead */
void SG_CALL SG_HINT_DEPRECATED sgFontStrSizefW(SGFont* font, float* x, float* y, const wchar_t* format, ...);
void SG_CALL SG_HINT_DEPRECATED sgFontStrSizefvW(SGFont* font, float* x, float* y, const wchar_t* format, va_list args);

void SG_CALL SG_HINT_PRINTF(4, 5) SG_HINT_DEPRECATED sgFontStrSizef(SGFont* font, float* x, float* y, const char* format, ...);
void SG_CALL SG_HINT_PRINTF(4, 0) SG_HINT_DEPRECATED sgFontStrSizefv(SGFont* font, float* x, float* y, const char* format, va_list args);

void SG_CALL SG_HINT_DEPRECATED sgFontStrSizeU32(SGFont* font, float* x, float* y, const SGdchar* text);
void SG_CALL SG_HINT_DEPRECATED sgFontStrSizeU16(SGFont* font, float* x, float* y, const SGwchar* text);
void SG_CALL SG_HINT_DEPRECATED sgFontStrSizeU8(SGFont* font, float* x, float* y, const SGchar* text);
void SG_CALL SG_HINT_DEPRECATED sgFontStrSizeW(SGFont* font, float* x, float* y, const wchar_t* text);
void SG_CALL SG_HINT_DEPRECATED sgFontStrSize(SGFont* font, float* x, float* y, const char* text);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_FONT_H__
