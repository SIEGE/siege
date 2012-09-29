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
#include <siege/util/vector.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <wchar.h>

static SGint SG_EXPORT _sgFontMapCmp(const SGdchar* a, const SGdchar* b, void* data)
{
    return *a - *b;
}

SGCharInfo* SG_EXPORT _sgFontFindCache(SGFont* font, SGdchar c)
{
    size_t* ind = sgMapFind(font->cmap, &c);
    if(!ind) return NULL;

    return &font->cache[*ind];
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
    SGdchar* key;
    size_t* val;
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
        sgTextureSetWrap(texture, SG_WRAP_CLAMP_TO_EDGE, SG_WRAP_CLAMP_TO_EDGE);
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

                key = malloc(sizeof(SGdchar));
                *key = achars[i];
                val = malloc(sizeof(size_t));
                *val = font->numcache - 1;
                sgMapAssign(font->cmap, key, val);
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
    float sx, sy;
    sgFontStrSizeU32(font, &sx, &sy, text);
    *x = -sx / 2.0;
    *y = sy / 2.0;
}

SGdchar* SG_EXPORT _sgFontU16ToU32(SGFont* font, const SGwchar* text)
{
	size_t len;
    for(len = 0; text[len]; len++) { }
    size_t buflen = len + 1;

    SGdchar* buf = malloc(buflen * sizeof(SGdchar));
    sgConv(font->conv[3], buf, buflen, text, len, SG_FALSE);
    return buf;
}
SGdchar* SG_EXPORT _sgFontU8ToU32(SGFont* font, const SGchar* text)
{
	size_t len = strlen(text);
    size_t buflen = len + 1;

    SGdchar* buf = malloc(buflen * sizeof(SGdchar));
    sgConv(font->conv[2], buf, buflen, text, len, SG_FALSE);
    return buf;
}
SGdchar* SG_EXPORT _sgFontWToU32(SGFont* font, const wchar_t* text)
{
	size_t len = wcslen(text);
    size_t buflen = len + 1;

    SGdchar* buf = malloc(buflen * sizeof(SGdchar));
    sgConv(font->conv[1], buf, buflen, text, len, SG_FALSE);
    return buf;
}
SGdchar* SG_EXPORT _sgFontToU32(SGFont* font, const char* text)
{
	size_t len = strlen(text);
    size_t buflen = len + 1;

    SGdchar* buf = malloc(buflen * sizeof(SGdchar));
    sgConv(font->conv[0], buf, buflen, text, len, SG_FALSE);
    return buf;
}

static void SG_EXPORT _sgFontCreateCache(SGFont* font)
{
    font->numchars = font->npreload;
    font->chars = malloc(font->npreload * sizeof(SGCharInfo));

    font->numcache = 0;
    font->cachechars = NULL;
    font->cache = NULL;

    font->cmap = sgMapCreate((SGMapCmp*)_sgFontMapCmp, NULL);

    size_t i;
    SGdchar* prestr = malloc(font->npreload * sizeof(SGdchar));
    for(i = 0; i < font->npreload; i++)
        prestr[i] = i;

    _sgFontLoad(font, prestr, font->npreload, SG_TRUE);
    free(prestr);
}
static void SG_EXPORT _sgFontDestroyCache(SGFont* font)
{
    size_t i;
    for(i = 0; i < font->numchars; i++)
        sgTextureDestroy(font->chars[i].texture);
    for(i = 0; i < font->numcache; i++)
        sgTextureDestroy(font->cache[i].texture);

    free(font->chars);
    free(font->cachechars);
    free(font->cache);

    SGMapNode* node;
    SGdchar* key;
    if(font->cmap)
    {
        for(;;)
        {
            node = sgMapGetRoot(font->cmap);
            if(!node) break;

            key = node->key;
            free(sgMapPopRoot(font->cmap));
            free(key);
        }
        sgMapDestroy(font->cmap);
    }
}
static void SG_EXPORT _sgFontSetHeight(SGFont* font, float height, SGuint dpi)
{
    font->height = height;
    font->dpi = dpi;
    if(psgmFontsFaceSetHeight)
        psgmFontsFaceSetHeight(font->handle, height, dpi);
    if(psgmFontsFaceGetMetrics)
        psgmFontsFaceGetMetrics(font->handle, &font->ascent, &font->descent, &font->linegap);
    else
    {
        font->ascent = SG_NAN;
        font->descent = SG_NAN;
        font->linegap = SG_NAN;
    }
}

typedef SGbool SG_EXPORT ExecLineStartFunction(SGFont* font, const SGdchar* text, const SGdchar* start, const SGdchar* end, void* data);
typedef SGbool SG_EXPORT ExecLineEndFunction(SGFont* font, const SGdchar* text, const SGdchar* start, const SGdchar* end, float xoffset, float yoffset, void* data);
typedef SGbool SG_EXPORT ExecCharFunction(SGFont* font, const SGdchar* text, const SGdchar* chr, SGCharInfo* cinfo, float xoffset, float yoffset, void* data);
typedef SGbool SG_EXPORT ExecDoneFunction(SGFont* font, float xoffset, float yoffset, void* data);
static SGbool SG_EXPORT _sgFontExecuteU32(SGFont* font, const SGdchar* text, ExecLineStartFunction* execLineStart, ExecCharFunction* execChar, ExecLineEndFunction* execLineEnd, ExecDoneFunction* execDone, void* data)
{
    if(!font)
        return SG_FALSE;

    float xoffset = 0.0;
    float yoffset = 0.0;

    const SGdchar* start = text;
    const SGdchar* end;
    const SGdchar* chr;
    size_t line = 0;

    float linesep = font->ascent - font->descent + font->linegap;

    SGCharInfo* info = NULL;
    float* kerning = NULL;
    while(start != NULL)
    {
        end = sgLineEndU32(start);
        if(execLineStart && execLineStart(font, text, start, end, data))
            goto end;
        info = realloc(info, (end - start) * sizeof(SGCharInfo));
        /*
         * we actually alloc 1 more, but it's better
         * than getting into trouble because of unsigned wrap
         * due to end being the same as start
         */
        kerning = realloc(kerning, (end - start) * sizeof(float));
        if(psgmFontsCharsGetKerning)
            psgmFontsCharsGetKerning(font->handle, start, end - start, kerning);
        if(!_sgFontGetChars(font, (SGdchar*)start, end - start, info) && ((end - start) != 0))
        {
            start = sgNextLineU32(start);
            continue;
        }
        xoffset = 0.0;
        yoffset = linesep * line;
        for(chr = start; chr < end; chr++)
        {
            if(execChar && execChar(font, text, chr, &info[chr-start], xoffset, yoffset, data))
                goto end;
            if(psgmFontsCharsGetKerning && chr != end - 1)
                xoffset += kerning[chr - start];
            xoffset += info[chr - start].xpost;
            yoffset += info[chr - start].ypost;
        }
        if(execLineEnd && execLineEnd(font, text, start, end, xoffset, yoffset, data))
            goto end;
        line++;
        start = sgNextLineU32(start);
    }
end:
    free(info);
    free(kerning);
    if(execDone)
        return execDone(font, xoffset, yoffset, data);
    return SG_TRUE;
}

SGFont* SG_EXPORT sgFontCreateStream(SGStream* stream, SGbool delstream, float height, SGuint dpi, SGuint preload)
{
    SGFont* font = malloc(sizeof(SGFont));
    if(font == NULL)
        return NULL;

    font->stream = stream;
    font->del = delstream;

    SGuint ret = SG_OK;
    if(psgmFontsFaceCreate != NULL)
        ret = psgmFontsFaceCreate(&font->handle, stream);
    if(ret != SG_OK)
    {
        fprintf(stderr, "Warning: Cannot create font\n");
        free(font);
        return NULL;
    }

    font->conv[0] = sgConvCreate(SG_CONV_TYPE_UTF32, SG_CONV_TYPE_CHAR);
    font->conv[1] = sgConvCreate(SG_CONV_TYPE_UTF32, SG_CONV_TYPE_WCHAR_T);
    font->conv[2] = sgConvCreate(SG_CONV_TYPE_UTF32, SG_CONV_TYPE_UTF8);
    font->conv[3] = sgConvCreate(SG_CONV_TYPE_UTF32, SG_CONV_TYPE_UTF16);

    font->npreload = preload;

    _sgFontSetHeight(font, height, dpi);
    _sgFontCreateCache(font);

    return font;
}
SGFont* SG_EXPORT sgFontCreate(const char* fname, float height, SGuint preload)
{
    SGStream* stream = sgStreamCreateFile(fname, "r");
    if(!stream)
    {
        fprintf(stderr, "Warning: Cannot create font %s\n", fname);
        return NULL;
    }
    return sgFontCreateStream(stream, SG_TRUE, height, 96, preload);
}
void SG_EXPORT sgFontDestroy(SGFont* font)
{
    if(font == NULL)
        return;

    size_t i;
    for(i = 0; i < 4; i++)
        sgConvDestroy(font->conv[i]);

    if(psgmFontsFaceDestroy != NULL)
        psgmFontsFaceDestroy(font->handle);

    _sgFontDestroyCache(font);

    if(font->del)
        sgStreamDestroy(font->stream);
    free(font);
}

void SG_EXPORT sgFontClearCache(SGFont* font)
{
    _sgFontDestroyCache(font);
    _sgFontCreateCache(font);
}
void SG_EXPORT sgFontSetHeight(SGFont* font, float height, SGuint dpi)
{
    _sgFontSetHeight(font, height, dpi);
    sgFontClearCache(font);
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
    wchar_t* buf = sgAPrintfvW(format, args);
    sgFontPrintW(font, x, y, buf);
    sgAPrintFree(buf);
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
    char* buf = sgAPrintfv(format, args);
	sgFontPrint(font, x, y, buf);
    sgAPrintFree(buf);
}

static SGbool SG_EXPORT _printChar(SGFont* font, const SGdchar* text, const SGdchar* chr, SGCharInfo* cinfo, float xoffset, float yoffset, void* data)
{
    SGVec2* pos = data;
    sgTextureDrawRads3f2f2f1f(cinfo->texture, pos->x + xoffset + cinfo->xpre, ((int)(pos->y + yoffset)) + cinfo->ypre, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0);
    return SG_FALSE;
}
void SG_EXPORT sgFontPrintU32(SGFont* font, float x, float y, const SGdchar* text)
{
    SGVec2 pos = sgVec2f(x, y);
    _sgFontExecuteU32(font, text, NULL, _printChar, NULL, NULL, &pos);
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
    wchar_t* buf = sgAPrintfvW(format, args);
    sgFontPrintAlignedW(font, x, y, align, buf);
    sgAPrintFree(buf);
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
    char* buf = sgAPrintfv(format, args);
    sgFontPrintAligned(font, x, y, align, buf);
    sgAPrintFree(buf);
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
        case SG_ALIGN_RIGHT: x += ox - sx / 2.0; break;
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

void SG_EXPORT sgFontStrSizefW(SGFont* font, float* x, float* y, const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    sgFontStrSizefvW(font, x, y, format, args);
    va_end(args);
}
void SG_EXPORT sgFontStrSizefvW(SGFont* font, float* x, float* y, const wchar_t* format, va_list args)
{
    wchar_t* buf = sgAPrintfvW(format, args);
    sgFontStrSizeW(font, x, y, buf);
    sgAPrintFree(buf);
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
    char* buf = sgAPrintfv(format, args);
	sgFontStrSize(font, x, y, buf);
    sgAPrintFree(buf);
}

static SGbool SG_EXPORT _strSizeLineEnd(SGFont* font, const SGdchar* text, const SGdchar* start, const SGdchar* end, float xoffset, float yoffset, void* data)
{
    SGVec2* size = data;
    if(size->x < xoffset)
        size->x = xoffset;
    return SG_FALSE;
}
static SGbool SG_EXPORT _strSizeDone(SGFont* font, float xoffset, float yoffset, void* data)
{
    SGVec2* size = data;
    size->y = yoffset + font->ascent - font->descent;
    return SG_TRUE;
}
void SG_EXPORT sgFontStrSizeU32(SGFont* font, float* x, float* y, const SGdchar* text)
{
    SGVec2 size = sgVec2f(0.0, 0.0);
    _sgFontExecuteU32(font, text, NULL, NULL, _strSizeLineEnd, _strSizeDone, &size);
    *x = size.x;
    *y = size.y;
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
    wchar_t* buf = sgAPrintfvW(format, args);
    size_t ind = sgFontFindIndexW(font, x, y, buf);
    sgAPrintFree(buf);
    return ind;
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
    char* buf = sgAPrintfv(format, args);
	size_t ind = sgFontFindIndex(font, x, y, buf);
    sgAPrintFree(buf);
    return ind;
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
    wchar_t* buf = sgAPrintfvW(format, args);
	sgFontGetPosW(font, x, y, index, buf);
    sgAPrintFree(buf);
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
    char* buf = sgAPrintfv(format, args);
	sgFontGetPos(font, x, y, index, buf);
    sgAPrintFree(buf);
}

typedef struct PosInfo
{
    SGVec2 pos;
    size_t index;
} PosInfo;

static SGbool SG_EXPORT _getPosLineStart(SGFont* font, const SGdchar* text, const SGdchar* start, const SGdchar* end, void* data)
{
    PosInfo* pi = data;
    if(start - text > pi->index)
        return SG_TRUE;
    return SG_FALSE;
}
static SGbool SG_EXPORT _getPosChar(SGFont* font, const SGdchar* text, const SGdchar* chr, SGCharInfo* cinfo, float xoffset, float yoffset, void* data)
{
    PosInfo* pi = data;
    if(chr - text == pi->index)
    {
        pi->pos.x += cinfo->xpre;
        return SG_TRUE;
    }
    return SG_FALSE;
}
static SGbool SG_EXPORT _getPosDone(SGFont* font, float xoffset, float yoffset, void* data)
{
    PosInfo* pi = data;
    pi->pos.x += xoffset;
    pi->pos.y += yoffset;
    return SG_TRUE;
}
void SG_EXPORT sgFontGetPosU32(SGFont* font, float* x, float* y, size_t index, const SGdchar* text)
{
    PosInfo pi;
    pi.pos = sgVec2f(0.0, 0.0);
    pi.index = index;
    _sgFontExecuteU32(font, text, _getPosLineStart, _getPosChar, NULL, _getPosDone, &pi);
    *x = pi.pos.x;
    *y = pi.pos.y;
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
