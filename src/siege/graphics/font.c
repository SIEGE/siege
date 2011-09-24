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

	if(psgmFontsCharsCreate == NULL)
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
		ret |= psgmFontsCharsCreate(font->handle, &achars[i], 1, &ci.width, &ci.height, &ci.xpre, &ci.ypre, &ci.xpost, &ci.ypost, &ci.dwidth, &ci.dheight, &data);
		if(ret != SG_OK)
		{
			free(achars);
			return SG_FALSE;
		}

		rgba = _sgFontToRGBA(font, data, ci.dwidth * ci.dheight);
		if(psgmFontsCharsFreeData != NULL)
			psgmFontsCharsFreeData(data);

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

SGdchar* SG_EXPORT _sgFontU16ToU32(SGFont* font, const SGwchar* text)
{
	size_t len;
	for(len = 0; text[len]; len++)
	{
	}

	return sgConv(font->conv[3], NULL, text, len * sizeof(SGwchar));
}
SGdchar* SG_EXPORT _sgFontU8ToU32(SGFont* font, const SGchar* text)
{
	size_t len = strlen(text);

	return sgConv(font->conv[2], NULL, text, len * sizeof(SGchar));
}
SGdchar* SG_EXPORT _sgFontWToU32(SGFont* font, const wchar_t* text)
{
	size_t len = wcslen(text);

	return sgConv(font->conv[1], NULL, text, len * sizeof(wchar_t));
}
SGdchar* SG_EXPORT _sgFontToU32(SGFont* font, const char* text)
{
	size_t len = strlen(text);

	return sgConv(font->conv[0], NULL, text, len);
}

SGFont* SG_EXPORT sgFontCreate(const char* fname, float height, SGuint preload)
{
	SGFont* font = malloc(sizeof(SGFont));
	if(font == NULL)
		return NULL;

	SGuint ret = SG_OK;
	if(psgmFontsFaceCreate != NULL)
		ret = psgmFontsFaceCreate(&font->handle, fname);
	if(ret != SG_OK)
	{
		fprintf(stderr, "Warning: Cannot create font %s\n", fname);
		free(font);
		return NULL;
	}

	if(psgmFontsFaceSetHeight != NULL)
		psgmFontsFaceSetHeight(font->handle, height);

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

	if(psgmFontsFaceDestroy != NULL)
		psgmFontsFaceDestroy(font->handle);

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
	size_t line = 0;
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
	SGdchar* dtext = _sgFontU16ToU32(font, text);
	sgFontPrintU32(font, x, y, dtext);
	free(dtext);
}
void SG_EXPORT sgFontPrintU8(SGFont* font, float x, float y, const SGchar* text)
{
	SGdchar* dtext = _sgFontU8ToU32(font, text);
	sgFontPrintU32(font, x, y, dtext);
	free(dtext);
}
void SG_EXPORT sgFontPrintW(SGFont* font, float x, float y, const wchar_t* text)
{
	SGdchar* dtext = _sgFontWToU32(font, text);
	sgFontPrintU32(font, x, y, dtext);
	free(dtext);
}
void SG_EXPORT sgFontPrint(SGFont* font, float x, float y, const char* text)
{
	SGdchar* dtext = _sgFontToU32(font, text);
	sgFontPrintU32(font, x, y, dtext);
	free(dtext);
}

void SG_EXPORT sgFontPrintAlignedfW(SGFont* font, float x, float y, SGenum align, const wchar_t* format, ...)
{
	va_list args;
	va_start(args, format);
	sgFontPrintAlignedfvW(font, x, y, align, format, args);
	va_end(args);
}
void SG_EXPORT sgFontPrintAlignedfvW(SGFont* font, float x, float y, SGenum align, const wchar_t* format, va_list args)
{
    sgFontPrintAlignedW(font, x, y, align, sgPrintfvW(format, args));
}

void SG_EXPORT SG_HINT_PRINTF(5, 6) sgFontPrintAlignedf(SGFont* font, float x, float y, SGenum align, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	sgFontPrintAlignedfv(font, x, y, align, format, args);
	va_end(args);
}
void SG_EXPORT SG_HINT_PRINTF(5, 0) sgFontPrintAlignedfv(SGFont* font, float x, float y, SGenum align, const char* format, va_list args)
{
    sgFontPrintAligned(font, x, y, align, sgPrintfv(format, args));
}

void SG_EXPORT sgFontPrintAlignedU32(SGFont* font, float x, float y, SGenum align, const SGdchar* text)
{
    float ox, oy;
    float sx, sy;
    // todo: only calc these when needed
    _sgFontCenterOffsetU32(font, &ox, &oy, text);
    sgFontStrSizeU32(font, &sx, &sy, text);
    switch(align & SG_ALIGN_HMASK)
    {
        case SG_ALIGN_CENTER: x += ox; break;
        case SG_ALIGN_LEFT: break;
        case SG_ALIGN_RIGHT: x += sx; break;
    }
    switch(align & SG_ALIGN_VMASK)
    {
        case SG_ALIGN_CENTER: y += oy; break;
        case SG_ALIGN_TOP: y += oy + sy / 2.0; break;
        case SG_ALIGN_BASELINE: break;
        case SG_ALIGN_BOTTOM: y += oy - sy / 2.0; break;
    }
    sgFontPrintU32(font, x, y, text);
}
void SG_EXPORT sgFontPrintAlignedU16(SGFont* font, float x, float y, SGenum align, const SGwchar* text)
{
	SGdchar* dtext = _sgFontU16ToU32(font, text);
    sgFontPrintAlignedU32(font, x, y, align, dtext);
	free(dtext);
}
void SG_EXPORT sgFontPrintAlignedU8(SGFont* font, float x, float y, SGenum align, const SGchar* text)
{
	SGdchar* dtext = _sgFontU8ToU32(font, text);
    sgFontPrintAlignedU32(font, x, y, align, dtext);
	free(dtext);
}
void SG_EXPORT sgFontPrintAlignedW(SGFont* font, float x, float y, SGenum align, const wchar_t* text)
{
	SGdchar* dtext = _sgFontWToU32(font, text);
    sgFontPrintAlignedU32(font, x, y, align, dtext);
	free(dtext);
}
void SG_EXPORT sgFontPrintAligned(SGFont* font, float x, float y, SGenum align, const char* text)
{
	SGdchar* dtext = _sgFontToU32(font, text);
    sgFontPrintAlignedU32(font, x, y, align, dtext);
	free(dtext);
}

void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintCenteredfW(SGFont* font, float x, float y, const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    sgFontPrintAlignedfvW(font, x, y, SG_ALIGN_CENTER, format, args);
    va_end(args);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintCenteredfvW(SGFont* font, float x, float y, const wchar_t* format, va_list args)
{
    sgFontPrintAlignedfvW(font, x, y, SG_ALIGN_CENTER, format, args);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintCenteredf(SGFont* font, float x, float y, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	sgFontPrintAlignedfv(font, x, y, SG_ALIGN_CENTER, format, args);
	va_end(args);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintCenteredfv(SGFont* font, float x, float y, const char* format, va_list args)
{
	sgFontPrintAlignedfv(font, x, y, SG_ALIGN_CENTER, format, args);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintCenteredU32(SGFont* font, float x, float y, const SGdchar* text)
{
    sgFontPrintAlignedU32(font, x, y, SG_ALIGN_CENTER, text);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintCenteredU16(SGFont* font, float x, float y, const SGwchar* text)
{
    sgFontPrintAlignedU16(font, x, y, SG_ALIGN_CENTER, text);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintCenteredU8(SGFont* font, float x, float y, const SGchar* text)
{
    sgFontPrintAlignedU8(font, x, y, SG_ALIGN_CENTER, text);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintCenteredW(SGFont* font, float x, float y, const wchar_t* text)
{
    sgFontPrintAlignedW(font, x, y, SG_ALIGN_CENTER, text);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintCentered(SGFont* font, float x, float y, const char* text)
{
    sgFontPrintAligned(font, x, y, SG_ALIGN_CENTER, text);
}

void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintXCenteredfW(SGFont* font, float x, float y, const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    sgFontPrintAlignedfvW(font, x, y, SG_ALIGN_CENTER | SG_ALIGN_BASELINE, format, args);
    va_end(args);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintXCenteredfvW(SGFont* font, float x, float y, const wchar_t* format, va_list args)
{
    sgFontPrintAlignedfvW(font, x, y, SG_ALIGN_CENTER | SG_ALIGN_BASELINE, format, args);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintXCenteredf(SGFont* font, float x, float y, const char* format, ...)
{
	va_list args;
	va_start(args, format);
    sgFontPrintAlignedfv(font, x, y, SG_ALIGN_CENTER | SG_ALIGN_BASELINE, format, args);
	va_end(args);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintXCenteredfv(SGFont* font, float x, float y, const char* format, va_list args)
{
    sgFontPrintAlignedfv(font, x, y, SG_ALIGN_CENTER | SG_ALIGN_BASELINE, format, args);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintXCenteredU32(SGFont* font, float x, float y, const SGdchar* text)
{
    sgFontPrintAlignedU32(font, x, y, SG_ALIGN_CENTER | SG_ALIGN_BASELINE, text);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintXCenteredU16(SGFont* font, float x, float y, const SGwchar* text)
{
    sgFontPrintAlignedU16(font, x, y, SG_ALIGN_CENTER | SG_ALIGN_BASELINE, text);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintXCenteredU8(SGFont* font, float x, float y, const SGchar* text)
{
    sgFontPrintAlignedU8(font, x, y, SG_ALIGN_CENTER | SG_ALIGN_BASELINE, text);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintXCenteredW(SGFont* font, float x, float y, const wchar_t* text)
{
    sgFontPrintAlignedW(font, x, y, SG_ALIGN_CENTER | SG_ALIGN_BASELINE, text);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintXCentered(SGFont* font, float x, float y, const char* text)
{
    sgFontPrintAligned(font, x, y, SG_ALIGN_CENTER | SG_ALIGN_BASELINE, text);
}

void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintYCenteredfW(SGFont* font, float x, float y, const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    sgFontPrintAlignedfvW(font, x, y, SG_ALIGN_LEFT | SG_ALIGN_CENTER, format, args);
    va_end(args);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintYCenteredfvW(SGFont* font, float x, float y, const wchar_t* format, va_list args)
{
    sgFontPrintAlignedfvW(font, x, y, SG_ALIGN_LEFT | SG_ALIGN_CENTER, format, args);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintYCenteredf(SGFont* font, float x, float y, const char* format, ...)
{
	va_list args;
	va_start(args, format);
    sgFontPrintAlignedfv(font, x, y, SG_ALIGN_LEFT | SG_ALIGN_CENTER, format, args);
	va_end(args);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintYCenteredfv(SGFont* font, float x, float y, const char* format, va_list args)
{
    sgFontPrintAlignedfv(font, x, y, SG_ALIGN_LEFT | SG_ALIGN_CENTER, format, args);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintYCenteredU32(SGFont* font, float x, float y, const SGdchar* text)
{
    sgFontPrintAlignedU32(font, x, y, SG_ALIGN_LEFT | SG_ALIGN_CENTER, text);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintYCenteredU16(SGFont* font, float x, float y, const SGwchar* text)
{
    sgFontPrintAlignedU16(font, x, y, SG_ALIGN_LEFT | SG_ALIGN_CENTER, text);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintYCenteredU8(SGFont* font, float x, float y, const SGchar* text)
{
    sgFontPrintAlignedU8(font, x, y, SG_ALIGN_LEFT | SG_ALIGN_CENTER, text);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintYCenteredW(SGFont* font, float x, float y, const wchar_t* text)
{
    sgFontPrintAlignedW(font, x, y, SG_ALIGN_LEFT | SG_ALIGN_CENTER, text);
}
void SG_EXPORT SG_HINT_DEPRECATED sgFontPrintYCentered(SGFont* font, float x, float y, const char* text)
{
    sgFontPrintAligned(font, x, y, SG_ALIGN_LEFT | SG_ALIGN_CENTER, text);
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
	SGdchar* dtext = _sgFontU16ToU32(font, text);
	sgFontStrSizeU32(font, x, y, dtext);
	free(dtext);
}
void SG_EXPORT sgFontStrSizeU8(SGFont* font, float* x, float* y, const SGchar* text)
{
	SGdchar* dtext = _sgFontU8ToU32(font, text);
	sgFontStrSizeU32(font, x, y, dtext);
	free(dtext);
}
void SG_EXPORT sgFontStrSizeW(SGFont* font, float* x, float* y, const wchar_t* text)
{
	SGdchar* dtext = _sgFontWToU32(font, text);
	sgFontStrSizeU32(font, x, y, dtext);
	free(dtext);
}
void SG_EXPORT sgFontStrSize(SGFont* font, float* x, float* y, const char* text)
{
	SGdchar* dtext = _sgFontToU32(font, text);
	sgFontStrSizeU32(font, x, y, dtext);
	free(dtext);
}

size_t SG_EXPORT sgFontFindIndexfW(SGFont* font, float x, float y, const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    size_t pos = sgFontFindIndexfvW(font, x, y, format, args);
    va_end(args);
    return pos;
}
size_t SG_EXPORT sgFontFindIndexfvW(SGFont* font, float x, float y, const wchar_t* format, va_list args)
{
    return sgFontFindIndexW(font, x, y, sgPrintfvW(format, args));
}

size_t SG_EXPORT sgFontFindIndexf(SGFont* font, float x, float y, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	size_t pos = sgFontFindIndexfv(font, x, y, format, args);
	va_end(args);
	return pos;
}
size_t SG_EXPORT sgFontFindIndexfv(SGFont* font, float x, float y, const char* format, va_list args)
{
	return sgFontFindIndex(font, x, y, sgPrintfv(format, args));
}

// todo: make this bisect instead of performing a linear search
size_t SG_EXPORT sgFontFindIndexU32(SGFont* font, float x, float y, const SGdchar* text)
{
	y += font->height;

	size_t len;
	for(len = 0; text[len]; len++)
	{
	}
	if(len == 0)
		return 0;

	SGdchar* cpy = malloc((len + 1) * sizeof(SGdchar));
	memset(cpy, 0, (len + 1) * sizeof(SGdchar));

	float sx, sy, px;

	const SGdchar* prev = text;
	const SGdchar* line = text;
	const SGdchar* end;

	do
	{
		end = sgLineEndU32(line);

		memcpy(&cpy[line-text], &text[line-text], (end - line) * sizeof(SGdchar));

		sgFontStrSizeU32(font, &sx, &sy, cpy);

		prev = line;
		line = sgNextLineU32(end);

		if(line)
			memcpy(&cpy[end-text], &text[end-text], (line - end) * sizeof(SGdchar)); // append CR/LF/CRLF
	}
	while(line && sy < y);

	end = sgLineEndU32(prev);
	memcpy(cpy, &text[prev-text], (end-prev) * sizeof(SGdchar));

	sx = 0.0;

	line = prev;
	do
	{
		cpy[line - prev] = *line;
		cpy[line - prev + 1] = 0;

		px = sx;
		sgFontStrSizeU32(font, &sx, &sy, cpy);

		line++;
	}
	while(line < end && sx < x);

	free(cpy);

	if(sx < x)
		return line - text;

	//float avg = (int)((px + sx) * 0.5 + 0.5); // rounded of average
	if(SG_ABS(px - x) < SG_ABS(sx - x))
		return line - text - 1;
	return line - text;
	//return line - text - 1;
}

size_t SG_EXPORT sgFontFindIndexU16(SGFont* font, float x, float y, const SGwchar* text)
{
	SGdchar* dtext = _sgFontU16ToU32(font, text);
	size_t pos = sgFontFindIndexU32(font, x, y, dtext);
	free(dtext);
	return pos;
}
size_t SG_EXPORT sgFontFindIndexU8(SGFont* font, float x, float y, const SGchar* text)
{
	SGdchar* dtext = _sgFontU8ToU32(font, text);
	size_t pos = sgFontFindIndexU32(font, x, y, dtext);
	free(dtext);
	return pos;
}
size_t SG_EXPORT sgFontFindIndexW(SGFont* font, float x, float y, const wchar_t* text)
{
	SGdchar* dtext = _sgFontWToU32(font, text);
	size_t pos = sgFontFindIndexU32(font, x, y, dtext);
	free(dtext);
	return pos;
}
size_t SG_EXPORT sgFontFindIndex(SGFont* font, float x, float y, const char* text)
{
	SGdchar* dtext = _sgFontToU32(font, text);
	size_t pos = sgFontFindIndexU32(font, x, y, dtext);
	free(dtext);
	return pos;
}

void SG_EXPORT sgFontGetPosfW(SGFont* font, float* x, float* y, size_t index, const wchar_t* format, ...)
{
	va_list args;
	va_start(args, format);
	sgFontGetPosfvW(font, x, y, index, format, args);
	va_end(args);
}
void SG_EXPORT sgFontGetPosfvW(SGFont* font, float* x, float* y, size_t index, const wchar_t* format, va_list args)
{
	sgFontGetPosW(font, x, y, index, sgPrintfvW(format, args));
}

void SG_EXPORT SG_HINT_PRINTF(5, 6) sgFontGetPosf(SGFont* font, float* x, float* y, size_t index, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	sgFontGetPosfv(font, x, y, index, format, args);
	va_end(args);
}
void SG_EXPORT SG_HINT_PRINTF(5, 0) sgFontGetPosfv(SGFont* font, float* x, float* y, size_t index, const char* format, va_list args)
{
	sgFontGetPos(font, x, y, index, sgPrintfv(format, args));
}

void SG_EXPORT sgFontGetPosU32(SGFont* font, float* x, float* y, size_t index, const SGdchar* text)
{
	if(font == NULL)
		return;

	float xoffset;
	float yoffset;
	float h = font->height / 0.63;

	const SGdchar* start = text;
	const SGdchar* end;
	const SGdchar* chr;
	size_t line = 0;
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
		xoffset = 0.0;
		yoffset = h * line;
		for(chr = start; chr < end; chr++)
		{
			if(chr - text == index)
			{
				*x = xoffset;
				*y = yoffset;
				goto end;
			}
			//sgTextureDrawRads3f2f2f1f(info[chr - start].texture, xoffset + info[chr - start].xpre, ((int)yoffset) + info[chr - start].ypre, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0);
			xoffset += info[chr - start].xpost;
			yoffset += info[chr - start].ypost;
		}
		line++;
		start = sgNextLineU32(start);
		if(start == NULL || start - text > index) // if sgNextLineU32 skipped a line...
		{
			*x = xoffset;
			*y = yoffset;
			goto end;
		}
	}

end:
	free(info);
}
void SG_EXPORT sgFontGetPosU16(SGFont* font, float* x, float* y, size_t index, const SGwchar* text)
{
	SGdchar* dtext = _sgFontU16ToU32(font, text);
	sgFontGetPosU32(font, x, y, index, dtext);
	free(dtext);
}
void SG_EXPORT sgFontGetPosU8(SGFont* font, float* x, float* y, size_t index, const SGchar* text)
{
	SGdchar* dtext = _sgFontU8ToU32(font, text);
	sgFontGetPosU32(font, x, y, index, dtext);
	free(dtext);
}
void SG_EXPORT sgFontGetPosW(SGFont* font, float* x, float* y, size_t index, const wchar_t* text)
{
	SGdchar* dtext = _sgFontWToU32(font, text);
	sgFontGetPosU32(font, x, y, index, dtext);
	free(dtext);
}
void SG_EXPORT sgFontGetPos(SGFont* font, float* x, float* y, size_t index, const char* text)
{
	SGdchar* dtext = _sgFontToU32(font, text);
	sgFontGetPosU32(font, x, y, index, dtext);
	free(dtext);
}
