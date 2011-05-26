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
#include <wchar.h>

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

void SG_EXPORT _sgFontCenterOffsetU32(SGFont* font, float* x, float* y, const SGdchar* text)
{
    //SGuint numlines = sgNumLines(text);
    float cx, cy;
    sgFontStrSizeU32(font, &cx, &cy, text);
    *x = -cx / 2.0f;
    *y = -1 / 0.63 + cy / 2.0f;
}
void SG_EXPORT _sgFontCenterOffsetU16(SGFont* font, float* x, float* y, const SGwchar* text)
{
    //SGuint numlines = sgNumLines(text);
    float cx, cy;
    sgFontStrSizeU16(font, &cx, &cy, text);
    *x = -cx / 2.0f;
    *y = -1 / 0.63 + cy / 2.0f;
}
void SG_EXPORT _sgFontCenterOffsetU8(SGFont* font, float* x, float* y, const SGchar* text)
{
    //SGuint numlines = sgNumLines(text);
    float cx, cy;
    sgFontStrSizeU8(font, &cx, &cy, text);
    *x = -cx / 2.0f;
    *y = -1 / 0.63 + cy / 2.0f;
}
void SG_EXPORT _sgFontCenterOffsetW(SGFont* font, float* x, float* y, const wchar_t* text)
{
    //SGuint numlines = sgNumLines(text);
    float cx, cy;
    sgFontStrSizeW(font, &cx, &cy, text);
    *x = -cx / 2.0f;
    *y = -1 / 0.63 + cy / 2.0f;
}
void SG_EXPORT _sgFontCenterOffset(SGFont* font, float* x, float* y, const char* text)
{
	//SGuint numlines = sgNumLines(text);
	float cx, cy;
	sgFontStrSize(font, &cx, &cy, text);
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

	font->conv[0] = sgConvCreate("char", "UTF-32");
	font->conv[1] = sgConvCreate("wchar_t", "UTF-32");
	font->conv[2] = sgConvCreate("UTF-8", "UTF-32");
	font->conv[3] = sgConvCreate("UTF-16", "UTF-32");

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

	for(i = 0; i < 4; i++)
		sgConvDestroy(font->conv[i]);

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

void SG_EXPORT sgFontPrintfW(SGFont* font, float x, float y, const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    sgFontPrintfvW(font, x, y, format, args);
    va_end(args);
}
void SG_EXPORT sgFontPrintfvW(SGFont* font, float x, float y, const wchar_t* format, va_list args)
{
    sgFontPrintW(font, x, y, sgPrintfvW(format, args));
}

void SG_EXPORT sgFontPrintf(SGFont* font, float x, float y, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	sgFontPrintfv(font, x, y, format, args);
	va_end(args);
}
void SG_EXPORT sgFontPrintfv(SGFont* font, float x, float y, const char* format, va_list args)
{
	sgFontPrint(font, x, y, sgPrintfv(format, args));
}

void SG_EXPORT sgFontPrintU32(SGFont* font, float x, float y, const SGdchar* text)
{
	if(font == NULL)
		return;

	float xoffset;
	float yoffset;
	float h = font->height / 0.63;

	const SGdchar* start = text;
	const SGdchar* end;
	const SGdchar* chr;
	SGuint line = 0;
	//SGuint numlines = sgNumLines(text);

	SGCharInfo* info = NULL;
	while(start != NULL)
	{
		end = sgLineEndU32(start);
		info = realloc(info, (end - start) * sizeof(SGCharInfo));
		if(!_sgFontGetChars(font, (SGdchar*)start, end - start, info) && ((end - start) != 0))
		{
			start = sgNextLineU32(start);
			continue;
		}
		xoffset = x;
		yoffset = y + h * line;
		for(chr = start; chr < end; chr++)
		{
			sgTextureDrawRads3f2f2f1f(info[chr - start].texture, xoffset + info[chr - start].xpre, ((int)yoffset) + info[chr - start].ypre, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0);
			xoffset += info[chr - start].xpost;
			yoffset += info[chr - start].ypost;
		}
		line++;
		start = sgNextLineU32(start);
	}
	free(info);
}
void SG_EXPORT sgFontPrintU16(SGFont* font, float x, float y, const SGwchar* text)
{
	size_t len;
	for(len = 0; text[len]; len++)
	{
	}

	SGdchar* dtext = sgConv(font->conv[3], NULL, text, len * sizeof(SGwchar));
	sgFontPrintU32(font, x, y, dtext);
	free(dtext);
}
void SG_EXPORT sgFontPrintU8(SGFont* font, float x, float y, const SGchar* text)
{
	size_t len = strlen((const char*)text);

	SGdchar* dtext = sgConv(font->conv[2], NULL, text, len * sizeof(SGchar));
	sgFontPrintU32(font, x, y, dtext);
	free(dtext);
}
void SG_EXPORT sgFontPrintW(SGFont* font, float x, float y, const wchar_t* text)
{
	size_t len = wcslen(text);

	SGdchar* dtext = sgConv(font->conv[1], NULL, text, len * sizeof(wchar_t));
	sgFontPrintU32(font, x, y, dtext);
	free(dtext);
}
void SG_EXPORT sgFontPrint(SGFont* font, float x, float y, const char* text)
{
	size_t len = strlen(text);

	SGdchar* dtext = sgConv(font->conv[0], NULL, text, len);
	sgFontPrintU32(font, x, y, dtext);
	free(dtext);
}

void SG_EXPORT sgFontPrintCenteredfW(SGFont* font, float x, float y, const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    sgFontPrintCenteredfvW(font, x, y, format, args);
    va_end(args);
}
void SG_EXPORT sgFontPrintCenteredfvW(SGFont* font, float x, float y, const wchar_t* format, va_list args)
{
    sgFontPrintCenteredW(font, x, y, sgPrintfvW(format, args));
}

void SG_EXPORT sgFontPrintCenteredf(SGFont* font, float x, float y, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	sgFontPrintCenteredfv(font, x, y, format, args);
	va_end(args);
}
void SG_EXPORT sgFontPrintCenteredfv(SGFont* font, float x, float y, const char* format, va_list args)
{
	sgFontPrintCentered(font, x, y, sgPrintfv(format, args));
}

void SG_EXPORT sgFontPrintCenteredU32(SGFont* font, float x, float y, const SGdchar* text)
{
    float ox, oy;
    _sgFontCenterOffsetU32(font, &ox, &oy, text);
    sgFontPrintU32(font, x + ox, y + oy, text);
}
void SG_EXPORT sgFontPrintCenteredU16(SGFont* font, float x, float y, const SGwchar* text)
{
    float ox, oy;
    _sgFontCenterOffsetU16(font, &ox, &oy, text);
    sgFontPrintU16(font, x + ox, y + oy, text);
}
void SG_EXPORT sgFontPrintCenteredU8(SGFont* font, float x, float y, const SGchar* text)
{
    float ox, oy;
    _sgFontCenterOffsetU8(font, &ox, &oy, text);
    sgFontPrintU8(font, x + ox, y + oy, text);
}
void SG_EXPORT sgFontPrintCenteredW(SGFont* font, float x, float y, const wchar_t* text)
{
    float ox, oy;
    _sgFontCenterOffsetW(font, &ox, &oy, text);
    sgFontPrintW(font, x + ox, y + oy, text);
}
void SG_EXPORT sgFontPrintCentered(SGFont* font, float x, float y, const char* text)
{
	float ox, oy;
	_sgFontCenterOffset(font, &ox, &oy, text);
	sgFontPrint(font, x + ox, y + oy, text);
}

// prints centered on X, but not on Y
void SG_EXPORT sgFontPrintXCenteredfW(SGFont* font, float x, float y, const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    sgFontPrintXCenteredfvW(font, x, y, format, args);
    va_end(args);
}
void SG_EXPORT sgFontPrintXCenteredfvW(SGFont* font, float x, float y, const wchar_t* format, va_list args)
{
    sgFontPrintXCenteredW(font, x, y, sgPrintfvW(format, args));
}

void SG_EXPORT sgFontPrintXCenteredf(SGFont* font, float x, float y, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	sgFontPrintXCenteredfv(font, x, y, format, args);
	va_end(args);
}
void SG_EXPORT sgFontPrintXCenteredfv(SGFont* font, float x, float y, const char* format, va_list args)
{
	sgFontPrintXCentered(font, x, y, sgPrintfv(format, args));
}

void SG_EXPORT sgFontPrintXCenteredU32(SGFont* font, float x, float y, const SGdchar* text)
{
    float ox, oy;
    _sgFontCenterOffsetU32(font, &ox, &oy, text);
    sgFontPrintU32(font, x + ox, y, text);
}
void SG_EXPORT sgFontPrintXCenteredU16(SGFont* font, float x, float y, const SGwchar* text)
{
    float ox, oy;
    _sgFontCenterOffsetU16(font, &ox, &oy, text);
    sgFontPrintU16(font, x + ox, y, text);
}
void SG_EXPORT sgFontPrintXCenteredU8(SGFont* font, float x, float y, const SGchar* text)
{
    float ox, oy;
    _sgFontCenterOffsetU8(font, &ox, &oy, text);
    sgFontPrintU8(font, x + ox, y, text);
}
void SG_EXPORT sgFontPrintXCenteredW(SGFont* font, float x, float y, const wchar_t* text)
{
    float ox, oy;
    _sgFontCenterOffsetW(font, &ox, &oy, text);
    sgFontPrintW(font, x + ox, y, text);
}
void SG_EXPORT sgFontPrintXCentered(SGFont* font, float x, float y, const char* text)
{
	float ox, oy;
	_sgFontCenterOffset(font, &ox, &oy, text);
	sgFontPrint(font, x + ox, y, text);
}

// prints centered on Y, but not on X
void SG_EXPORT sgFontPrintYCenteredfW(SGFont* font, float x, float y, const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    sgFontPrintYCenteredfvW(font, x, y, format, args);
    va_end(args);
}
void SG_EXPORT sgFontPrintYCenteredfvW(SGFont* font, float x, float y, const wchar_t* format, va_list args)
{
    sgFontPrintYCenteredW(font, x, y, sgPrintfvW(format, args));
}

void SG_EXPORT sgFontPrintYCenteredf(SGFont* font, float x, float y, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	sgFontPrintYCenteredfv(font, x, y, format, args);
	va_end(args);
}
void SG_EXPORT sgFontPrintYCenteredfv(SGFont* font, float x, float y, const char* format, va_list args)
{
	sgFontPrintYCentered(font, x, y, sgPrintfv(format, args));
}

void SG_EXPORT sgFontPrintYCenteredU32(SGFont* font, float x, float y, const SGdchar* text)
{
    float ox, oy;
    _sgFontCenterOffsetU32(font, &ox, &oy, text);
    sgFontPrintU32(font, x, y + oy, text);
}
void SG_EXPORT sgFontPrintYCenteredU16(SGFont* font, float x, float y, const SGwchar* text)
{
    float ox, oy;
    _sgFontCenterOffsetU16(font, &ox, &oy, text);
    sgFontPrintU16(font, x, y + oy, text);
}
void SG_EXPORT sgFontPrintYCenteredU8(SGFont* font, float x, float y, const SGchar* text)
{
    float ox, oy;
    _sgFontCenterOffsetU8(font, &ox, &oy, text);
    sgFontPrintU8(font, x, y + oy, text);
}
void SG_EXPORT sgFontPrintYCenteredW(SGFont* font, float x, float y, const wchar_t* text)
{
    float ox, oy;
    _sgFontCenterOffsetW(font, &ox, &oy, text);
    sgFontPrintW(font, x, y + oy, text);
}
void SG_EXPORT sgFontPrintYCentered(SGFont* font, float x, float y, const char* text)
{
	float ox, oy;
	_sgFontCenterOffset(font, &ox, &oy, text);
	sgFontPrint(font, x, y + oy, text);
}

void SG_EXPORT sgFontStrSizefW(SGFont* font, float* x, float* y, const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    sgFontStrSizefvW(font, x, y, format, args);
    va_end(args);
}
void SG_EXPORT sgFontStrSizefvW(SGFont* font, float* x, float* y, const wchar_t* format, va_list args)
{
    sgFontStrSizeW(font, x, y, sgPrintfvW(format, args));
}

void SG_EXPORT sgFontStrSizef(SGFont* font, float* x, float* y, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	sgFontStrSizefv(font, x, y, format, args);
	va_end(args);
}
void SG_EXPORT sgFontStrSizefv(SGFont* font, float* x, float* y, const char* format, va_list args)
{
	sgFontStrSize(font, x, y, sgPrintfv(format, args));
}

void SG_EXPORT sgFontStrSizeU32(SGFont* font, float* x, float* y, const SGdchar* text)
{
	if(font == NULL)
		return;

	if(text[0] == 0xFEFF)
		text++;

	const SGdchar* start = text;
	const SGdchar* end;
	SGuint line = 0;
	SGuint numlines = sgNumLinesU32(text);

	*x = 0.0f;
	*y = 0.0f;
	const SGdchar* chr;
	float w;
	float h;
	SGCharInfo* info = NULL;
	while(start != NULL)
	{
		end = sgLineEndU32(start);
		info = realloc(info, (end - start) * sizeof(SGCharInfo));
		_sgFontGetChars(font, (SGdchar*)start, end - start, info);
		w = 0.0f;
		h = 0.0f;
		for(chr = start; chr < end; chr++)
			w += info[chr - start].width;
		*x = (*x > w) ? *x : w;
		if(line < numlines - 1)
			*y += font->height / 0.63 - font->height;
		*y += font->height / 0.63;
		line++;
		start = sgNextLineU32(start);
	}
	free(info);
}
void SG_EXPORT sgFontStrSizeU16(SGFont* font, float* x, float* y, const SGwchar* text)
{
	size_t len;
	for(len = 0; text[len]; len++)
	{
	}

	SGdchar* dtext = sgConv(font->conv[3], NULL, text, len * sizeof(SGwchar));
	sgFontStrSizeU32(font, x, y, dtext);
	free(dtext);
}
void SG_EXPORT sgFontStrSizeU8(SGFont* font, float* x, float* y, const SGchar* text)
{
	size_t len = strlen((char*)text);

	SGdchar* dtext = sgConv(font->conv[2], NULL, text, len * sizeof(SGchar));
	sgFontStrSizeU32(font, x, y, dtext);
	free(dtext);
}
void SG_EXPORT sgFontStrSizeW(SGFont* font, float* x, float* y, const wchar_t* text)
{
	size_t len = wcslen(text);

	SGdchar* dtext = sgConv(font->conv[1], NULL, text, len * sizeof(wchar_t));
	sgFontStrSizeU32(font, x, y, dtext);
	free(dtext);
}
void SG_EXPORT sgFontStrSize(SGFont* font, float* x, float* y, const char* text)
{
	size_t len = strlen(text);

	SGdchar* dtext = sgConv(font->conv[0], NULL, text, len);
	sgFontStrSizeU32(font, x, y, dtext);
	free(dtext);
}
