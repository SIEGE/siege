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

#define SG_BUILD_LIBRARY
#include <siege/graphics/texture.h>
#include <siege/graphics/font.h>
#include <siege/modules/fonts.h>
#include <siege/util/string.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

SGCharInfo* SG_EXPORT _sgFontFindCache(SGFont* font, SGdchar c)
{
	SGuint i;
	for(i = 0; i < font->numcache; i++)
		if(font->cachechars[i] == c)
			return &font->cache[i];
	return NULL;
}
SGbool SG_EXPORT _sgFontGetChars(SGFont* font, SGdchar* str, SGuint strlen, SGCharInfo* info)
{
	if(!_sgFontLoad(font, str, strlen, SG_FALSE))
		return SG_FALSE;

	SGuint i;
	SGCharInfo* ci;
	for(i = 0; i < strlen; i++)
	{
		if(str[i] < font->numchars)
		{
			info[i] = font->chars[str[i]];
		}
		else
		{
			ci = _sgFontFindCache(font, str[i]);
			//if(ci != NULL)
			info[i] = *ci;
		}
	}
	return SG_TRUE;
}
void SG_EXPORT _sgFontToLoad(SGFont* font, SGdchar* input, SGuint inlen, SGdchar* output, SGuint* outlen)
{
	SGuint i;
	*outlen = 0;
	for(i = 0; i < inlen; i++)
	{
		if(input[i] < font->numchars)
			continue;
		if(_sgFontFindCache(font, input[i]) != NULL)
			continue;
		output[(*outlen)++] = input[i];
	}
}
SGbool SG_EXPORT _sgFontLoad(SGFont* font, SGdchar* chars, SGuint numchars, SGbool force)
{
	SGdchar* achars = malloc(numchars * sizeof(SGdchar));
	SGuint alen = numchars;
	if(!force)
		_sgFontToLoad(font, chars, numchars, achars, &alen);
	else
		memcpy(achars, chars, numchars * sizeof(SGdchar));
	if(alen == 0)
	{
		free(achars);
		return SG_TRUE;
	}

	if(_sg_modFonts.sgmFontsCharsCreate == NULL)
	{
		free(achars);
		return SG_FALSE;
	}

	SGuint ret = 0;
	SGuint i;
	SGCharInfo ci;
	void* data;
	SGubyte* rgba;
	SGCharInfo* cache;
	for(i = 0; i < alen; i++)
	{
		ret |= _sg_modFonts.sgmFontsCharsCreate(font->handle, &achars[i], 1, &ci.width, &ci.height, &ci.xpre, &ci.ypre, &ci.xpost, &ci.ypost, &ci.dwidth, &ci.dheight, &data);
		if(ret != SG_OK)
		{
			free(achars);
			return SG_FALSE;
		}

		rgba = _sgFontToRGBA(font, data, ci.dwidth * ci.dheight);
		if(_sg_modFonts.sgmFontsCharsFreeData != NULL)
			_sg_modFonts.sgmFontsCharsFreeData(data);

		SGTexture* texture = sgTextureCreateData(ci.dwidth, ci.dheight, 32, rgba);
		free(rgba);
		ci.texture = texture;
		if(achars[i] < font->numchars)
		{
			memcpy(&font->chars[achars[i]], &ci, sizeof(SGCharInfo));
		}
		else
		{
			cache = _sgFontFindCache(font, achars[i]);
			if(cache != NULL)
			{
				sgTextureDestroy(cache->texture);
			}
			else
			{
				font->numcache++;
				font->cachechars = realloc(font->cachechars, font->numcache * sizeof(SGdchar));
				font->cache = realloc(font->cache, font->numcache * sizeof(SGCharInfo));
				font->cachechars[font->numcache - 1] = achars[i];
				cache = &font->cache[font->numcache - 1];
			}
			memcpy(cache, &ci, sizeof(SGCharInfo));
		}
	}

	free(achars);
	return SG_TRUE;
}
SGubyte* SG_EXPORT _sgFontToRGBA(SGFont* font, SGubyte* data, SGuint datalen)
{
	SGuint i;
	SGubyte* newData = malloc(datalen * 4);
	for(i = 0; i < datalen; i++)
	{
		newData[4*i  ] =
		newData[4*i+1] =
		newData[4*i+2] = 0xFF;
		newData[4*i+3] = data[i];
	}
	return newData;
}
void SG_EXPORT _sgFontCenterOffsetT(SGFont* font, float* x, float* y, const char* text)
{
	//SGuint numlines = sgNumLines(text);
	float cx;
	float cy;
	sgFontStrSizeT(font, &cx, &cy, text);
	*x = -cx / 2.0f;
	*y = -1 / 0.63 + cy / 2.0f;
}

SGFont* SG_EXPORT sgFontCreate(const char* fname, float height, SGuint preload)
{
	SGFont* font = malloc(sizeof(SGFont));
	if(font == NULL)
		return NULL;

	SGuint ret = SG_OK;
	if(_sg_modFonts.sgmFontsFaceCreate != NULL)
		ret = _sg_modFonts.sgmFontsFaceCreate(&font->handle, fname);
	if(ret != SG_OK)
	{
		fprintf(stderr, "Warning: Cannot create font %s\n", fname);
		free(font);
		return NULL;
	}

	if(_sg_modFonts.sgmFontsFaceSetHeight != NULL)
		_sg_modFonts.sgmFontsFaceSetHeight(font->handle, height);

	SGuint len = strlen(fname) + 1;
	font->fname = malloc(len);
	memcpy(font->fname, fname, len);
	font->height = height;

	font->numchars = preload;
	font->chars = malloc(preload * sizeof(SGCharInfo));

	font->numcache = 0;
	font->cachechars = NULL;
	font->cache = NULL;

	SGuint i;
	SGdchar* prestr = malloc(preload * sizeof(SGdchar));
	for(i = 0; i < preload; i++)
		prestr[i] = i;

	_sgFontLoad(font, prestr, preload, SG_TRUE);
	free(prestr);
	return font;
}
void SG_EXPORT sgFontDestroy(SGFont* font)
{
	if(font == NULL)
		return;

	size_t i;
	for(i = 0; i < font->numchars; i++)
		sgTextureDestroy(font->chars[i].texture);
	for(i = 0; i < font->numcache; i++)
		sgTextureDestroy(font->cache[i].texture);

	if(_sg_modFonts.sgmFontsFaceDestroy != NULL)
		_sg_modFonts.sgmFontsFaceDestroy(font->handle);
	free(font->fname);
	free(font->chars);
	free(font->cachechars);
	free(font->cache);
	free(font);
}

SGFont* SG_EXPORT sgFontResizeCopy(SGFont* font, float height)
{
	if(font == NULL)
		return NULL;

	return sgFontCreate(font->fname, height, font->numchars);
}
SGFont* SG_EXPORT sgFontResize(SGFont* font, float height)
{
	if(font == NULL)
		return NULL;

	if(font->height == height)
		return font;

	SGFont* newFont = sgFontResizeCopy(font, height);
	sgFontDestroy(font);
	return newFont;
}

void SG_EXPORT sgFontPrint(SGFont* font, float x, float y, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	sgFontPrintV(font, x, y, format, args);
	va_end(args);
}
void SG_EXPORT sgFontPrintV(SGFont* font, float x, float y, const char* format, va_list args)
{
	sgFontPrintT(font, x, y, sgPrintfv(format, args));
}
void SG_EXPORT sgFontPrintT(SGFont* font, float x, float y, const char* text)
{
	if(font == NULL)
		return;

	float xoffset;
	float yoffset;
	float h = font->height / 0.63;

	const char* start = text;
	const char* end;
	const char* chr;
	SGuint line = 0;
	//SGuint numlines = sgNumLines(text);

	SGCharInfo* info = NULL;
	SGdchar* dline = NULL;
	while(start != NULL)
	{
		end = sgLineEnd(start);
		info = realloc(info, (end - start) * sizeof(SGCharInfo));
		dline = realloc(dline, (end - start) * sizeof(SGdchar));
		sgCharToUTF32(start, end - start, dline);
		if(!_sgFontGetChars(font, dline, end - start, info) && ((end - start) != 0))
		{
			start = sgNextLine(start);
			continue;
		}
		xoffset = x;
		yoffset = y + h * line;
		for(chr = start; chr < end; chr++)
		{
			sgTextureDrawRads3f2f2f1f(info[chr - start].texture, xoffset + info[chr - start].xpre, yoffset + info[chr - start].ypre, 0.0, 1.0, -1.0, 0.0, 0.0, 0.0);
			xoffset += info[chr - start].xpost;
			yoffset += info[chr - start].ypost;
		}
		line++;
		start = sgNextLine(start);
	}
	free(info);
	free(dline);
}

void SG_EXPORT sgFontPrintCentered(SGFont* font, float x, float y, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	sgFontPrintCenteredV(font, x, y, format, args);
	va_end(args);
}
void SG_EXPORT sgFontPrintCenteredV(SGFont* font, float x, float y, const char* format, va_list args)
{
	sgFontPrintCenteredT(font, x, y, sgPrintfv(format, args));
}
void SG_EXPORT sgFontPrintCenteredT(SGFont* font, float x, float y, const char* text)
{
	float ox;
	float oy;
	_sgFontCenterOffsetT(font, &ox, &oy, text);
	sgFontPrintT(font, x + ox, y + oy, text);
}

// prints centered on X, but not on Y
void SG_EXPORT sgFontPrintXCentered(SGFont* font, float x, float y, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	sgFontPrintXCenteredV(font, x, y, format, args);
	va_end(args);
}
void SG_EXPORT sgFontPrintXCenteredV(SGFont* font, float x, float y, const char* format, va_list args)
{
	sgFontPrintXCenteredT(font, x, y, sgPrintfv(format, args));
}
void SG_EXPORT sgFontPrintXCenteredT(SGFont* font, float x, float y, const char* text)
{
	float ox;
	float oy;
	_sgFontCenterOffsetT(font, &ox, &oy, text);
	sgFontPrintT(font, x + ox, y, text);
}

// prints centered on Y, but not on X
void SG_EXPORT sgFontPrintYCentered(SGFont* font, float x, float y, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	sgFontPrintYCenteredV(font, x, y, format, args);
	va_end(args);
}
void SG_EXPORT sgFontPrintYCenteredV(SGFont* font, float x, float y, const char* format, va_list args)
{
	sgFontPrintYCenteredT(font, x, y, sgPrintfv(format, args));
}
void SG_EXPORT sgFontPrintYCenteredT(SGFont* font, float x, float y, const char* text)
{
	float ox;
	float oy;
	_sgFontCenterOffsetT(font, &ox, &oy, text);
	sgFontPrintT(font, x, y + oy, text);
}

void SG_EXPORT sgFontStrSize(SGFont* font, float* x, float* y, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	sgFontStrSizeV(font, x, y, format, args);
	va_end(args);
}
void SG_EXPORT sgFontStrSizeV(SGFont* font, float* x, float* y, const char* format, va_list args)
{
	sgFontStrSizeT(font, x, y, sgPrintfv(format, args));
}
void SG_EXPORT sgFontStrSizeT(SGFont* font, float* x, float* y, const char* text)
{
	if(font == NULL)
		return;

	const char* start = text;
	const char* end;
	SGuint line = 0;
	SGuint numlines = sgNumLines(text);

	*x = 0.0f;
	*y = 0.0f;
	const char* chr;
	float w;
	float h;
	SGCharInfo* info = NULL;
	SGdchar* dline = NULL;
	while(start != NULL)
	{
		end = sgLineEnd(start);
		info = realloc(info, (end - start) * sizeof(SGCharInfo));
		dline = realloc(dline, (end - start) * sizeof(SGdchar));
		sgCharToUTF32(start, end - start, dline);
		_sgFontGetChars(font, dline, end - start, info);
		w = 0.0f;
		h = 0.0f;
		for(chr = start; chr < end; chr++)
			w += info[chr - start].width;
		*x = (*x > w) ? *x : w;
		if(line < numlines - 1)
			*y += font->height / 0.63 - font->height;
		*y += font->height / 0.63;
		line++;
		start = sgNextLine(start);
	}
	free(info);
	free(dline);
}
