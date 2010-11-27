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
 * \file graphics/font.h
 * \brief Font handling.
 * \ingroup Graphics
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
	 *	Should multiple characters be put into a single texture?
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
	SGuint dwidth;
	SGuint dheight;
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
	char* fname;	/// < Filename used to load the font
	float height;	/// < Height of the font
	/// @}

	/**
	 * \name Preloaded characters
	 */
	/// @{
	SGuint numchars;	/// < The number of characters
	SGCharInfo* chars;	/// < The characters themselves
	/// @}

	/**
	 * \name On-demand loaded characters
	 */
	/// @{
	SGuint numcache;		/// < Length of the arrays
	SGdchar* cachechars;	/// < The character UTF-32 values (keys)
	SGCharInfo* cache;		/// < Character infos (values)
	/// @}
} SGFont;

SGCharInfo* SG_EXPORT _sgFontFindCache(SGFont* font, SGdchar c);
SGbool SG_EXPORT _sgFontGetChars(SGFont* font, SGdchar* str, SGuint strlen, SGCharInfo* info);
void SG_EXPORT _sgFontToLoad(SGFont* font, SGdchar* input, SGuint inlen, SGdchar* output, SGuint* outlen);
SGbool SG_EXPORT _sgFontLoad(SGFont* font, SGdchar* chars, SGuint numchars, SGbool force);
SGubyte* SG_EXPORT _sgFontToRGBA(SGFont* font, SGubyte* data, SGuint datalen);
void SG_EXPORT _sgFontCenterOffsetT(SGFont* font, float* x, float* y, const char* text);

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
SGFont* SG_EXPORT sgFontCreate(const char* fname, float height, SGuint preload);
/**
 * \brief Destroy a font info
 *
 * \param font The font info to destroy.
 * It should not be used anymore after this call.
 */
void SG_EXPORT sgFontDestroy(SGFont* font);
/// @}

/**
 * \name Resizing
 */
/// @{
/**
 * \brief Resize the font, force duplication.
 *
 * \param font The font to resize
 * \param height New font height
 *
 * \return A copy of the font, with the height \a height.
 *
 * This resizes the font and forces for it to be duplicated even
 * if the character data for the new size has already been created.
 *
 * It is roughly equivalent to:
 * \code
 *	sgFontCreate(font->fname, font->height, font->preload);
 * \endcode
 *
 * \see sgFontResize
 */

SGFont* SG_EXPORT sgFontResizeCopy(SGFont* font, float height);
/**
 * \brief Resize the font, duplicating only if necessarry.
 *
 * \param font The font to resize
 * \param height New font height
 *
 * \return A new font if one had to be created;
 * otherwise a previously-created font.
 *
 * This function is similar to sgFontResizeCopy(), only it
 * does not allocate a new font if it doesn't have to.
 *
 * \see	sgFontResizeCopy
 */
SGFont* SG_EXPORT sgFontResize(SGFont* font, float height);
/// @}

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
/**
 * \brief printf-style print
 */
void SG_EXPORT SG_HINT_PRINTF(4, 5) sgFontPrint(SGFont* font, float x, float y, const char* format, ...);
/**
 * \brief vprintf-style print
 */
void SG_EXPORT SG_HINT_PRINTF(4, 0) sgFontPrintV(SGFont* font, float x, float y, const char* format, va_list args);
/**
 * \brief Text-based print
 */
void SG_EXPORT sgFontPrintT(SGFont* font, float x, float y, const char* text);
/// @}

/**
 * \name Print centered
 *
 * \param font The font face to use for printing.
 * \param x X position (center)
 * \param y Y position (center)
 *
 * These functions print text in a position <em>x</em>,<em>y</em>,
 * where both \a x and \a y specify the center of the text.
 */
/// @{
/**
 * \brief printf-style print
 */
void SG_EXPORT SG_HINT_PRINTF(4, 5) sgFontPrintCentered(SGFont* font, float x, float y, const char* format, ...);
/**
 * \brief vprintf-style print
 */
void SG_EXPORT SG_HINT_PRINTF(4, 0) sgFontPrintCenteredV(SGFont* font, float x, float y, const char* format, va_list args);
/**
 * \brief Text-based print
 */
void SG_EXPORT sgFontPrintCenteredT(SGFont* font, float x, float y, const char* text);
/// @}

/**
 * \name Print x-centered
 *
 * \param font The font face to use for printing.
 * \param x X position (center)
 * \param y Y position (baseline)
 *
 * These functions print text in a position <em>x</em>,<em>y</em>,
 * where \a x specifies the center of the text in that direction
 * and \a y specifies the baseline.
 */
/// @{
/**
 * \brief printf-style print
 */
void SG_EXPORT SG_HINT_PRINTF(4, 5) sgFontPrintXCentered(SGFont* font, float x, float y, const char* format, ...);
/**
 * \brief vprintf-style print
 */
void SG_EXPORT SG_HINT_PRINTF(4, 0) sgFontPrintXCenteredV(SGFont* font, float x, float y, const char* format, va_list args);
/**
 * \brief text-based print
 */
void SG_EXPORT sgFontPrintXCenteredT(SGFont* font, float x, float y, const char* text);
/// @}

/**
 * \name Print y-centered
 *
 * \param font The font face to use for printing.
 * \param x X position (left)
 * \param y Y position (center)
 *
 * These functions print text in a position <em>x</em>,<em>y</em>,
 * where \a x specifies the start of the text in that direction
 * and \a y specifies the center.
 */
/// @{
/**
 * \brief printf-style print
 */
void SG_EXPORT SG_HINT_PRINTF(4, 5) sgFontPrintYCentered(SGFont* font, float x, float y, const char* format, ...);
/**
 * \brief vprintf-style print
 */
void SG_EXPORT SG_HINT_PRINTF(4, 0) sgFontPrintYCenteredV(SGFont* font, float x, float y, const char* format, va_list args);
/**
 * \brief text-based print
 */
void SG_EXPORT sgFontPrintYCenteredT(SGFont* font, float x, float y, const char* text);
/// @}

/**
 * \name Get size of printed text
 *
 * \param font The font face to use for printing.
 * \param[out] x Width
 * \param[out] y Height
 *
 * These functions return the size of the text, had it been printed,
 * in <em>x</em>,<em>y</em>, with the former being the width and the
 * latter height.
 */
/// @{
/**
 * \brief printf-style text
 */
void SG_EXPORT SG_HINT_PRINTF(4, 5) sgFontStrSize(SGFont* font, float* x, float* y, const char* format, ...);
/**
 * \brief vprintf-style text
 */
void SG_EXPORT SG_HINT_PRINTF(4, 0) sgFontStrSizeV(SGFont* font, float* x, float* y, const char* format, va_list args);
/**
 * \brief plain text
 */
void SG_EXPORT sgFontStrSizeT(SGFont* font, float* x, float* y, const char* text);
/// @}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_FONT_H__
