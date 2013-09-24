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
#include <siege/util/string.h>
#include <siege/util/vector.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <wchar.h>

#include "../internal/stb/stb_truetype.h"

typedef struct FontFace
{
    stbtt_fontinfo info;
    void* buf;
    float scale;
} FontFace;

static SGint SG_CALL _sgFontMapCmp(const SGdchar* a, const SGdchar* b, void* data)
{
    return *a - *b;
}

SGCharInfo* SG_CALL _sgFontFindCache(SGFont* font, SGdchar c)
{
    size_t* ind = sgMapFind(font->cmap, &c);
    if(!ind) return NULL;

    return &font->cache[*ind];
}
SGbool SG_CALL _sgFontGetChars(SGFont* font, SGdchar* str, SGuint strlen, SGCharInfo* info)
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
void SG_CALL _sgFontToLoad(SGFont* font, SGdchar* input, SGuint inlen, SGdchar* output, SGuint* outlen)
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
SGbool SG_CALL _sgFontLoad(SGFont* font, SGdchar* chars, SGuint numchars, SGbool force)
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

    FontFace* fface = font->handle;
    int adv, left;
    int dw, dh;
    int xo, yo;
    int glyph;

    SGuint i;
    SGCharInfo ci;
    void* data;
    SGubyte* rgba;
    SGCharInfo* cache;
    SGdchar* key;
    size_t* val;
    for(i = 0; i < alen; i++)
    {
        glyph = stbtt_FindGlyphIndex(&fface->info, achars[i]);

        dw = dh = 0;
        data = stbtt_GetGlyphBitmap(&fface->info, fface->scale, fface->scale, glyph, &dw, &dh, &xo, &yo);
        //if(!data) goto err;
        ci.dwidth = dw;
        ci.dheight = dh;

        stbtt_GetGlyphHMetrics(&fface->info, glyph, &adv, &left);
        ci.xpre = xo;
        ci.ypre = yo;
        ci.xpost = adv * fface->scale;
        ci.ypost = 0;
        ci.width = adv * fface->scale;
        ci.height = 0; // TODO

        rgba = _sgFontToRGBA(font, data, ci.dwidth * ci.dheight);
        stbtt_FreeBitmap(data, NULL);

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
SGubyte* SG_CALL _sgFontToRGBA(SGFont* font, SGubyte* data, SGuint datalen)
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

void SG_CALL _sgFontCenterOffsetU32(SGFont* font, float* x, float* y, const SGdchar* text)
{
    float sx, sy;
    sgFontStrSizeU32(font, &sx, &sy, text);
    *x = -sx / 2.0;
    *y = sy / 2.0;
}

SGdchar* SG_CALL _sgFontU16ToU32(SGFont* font, const SGwchar* text)
{
    size_t len;
    for(len = 0; text[len]; len++) { }
    size_t buflen = len + 1;

    SGdchar* buf = malloc(buflen * sizeof(SGdchar));
    sgConv(font->conv[3], buf, buflen, text, len, SG_FALSE);
    return buf;
}
SGdchar* SG_CALL _sgFontU8ToU32(SGFont* font, const SGchar* text)
{
    size_t len = strlen(text);
    size_t buflen = len + 1;

    SGdchar* buf = malloc(buflen * sizeof(SGdchar));
    sgConv(font->conv[2], buf, buflen, text, len, SG_FALSE);
    return buf;
}
SGdchar* SG_CALL _sgFontWToU32(SGFont* font, const wchar_t* text)
{
    size_t len = wcslen(text);
    size_t buflen = len + 1;

    SGdchar* buf = malloc(buflen * sizeof(SGdchar));
    sgConv(font->conv[1], buf, buflen, text, len, SG_FALSE);
    return buf;
}
SGdchar* SG_CALL _sgFontToU32(SGFont* font, const char* text)
{
    size_t len = strlen(text);
    size_t buflen = len + 1;

    SGdchar* buf = malloc(buflen * sizeof(SGdchar));
    sgConv(font->conv[0], buf, buflen, text, len, SG_FALSE);
    return buf;
}

static void SG_CALL _sgFontCreateCache(SGFont* font)
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
static void SG_CALL _sgFontDestroyCache(SGFont* font)
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
static void SG_CALL _sgFontSetHeight(SGFont* font, float height, SGuint dpi)
{
    font->height = height;
    font->dpi = dpi ? dpi : 96;

    FontFace* fface = font->handle;
    //fface->scale = stbtt_ScaleForPixelHeight(&fface->info, height);
    fface->scale = stbtt_ScaleForMappingEmToPixels(&fface->info, height * font->dpi / 72.0);

    int iasc, idesc, igap;
    stbtt_GetFontVMetrics(&fface->info, &iasc, &idesc, &igap);
    font->ascent = iasc * fface->scale;
    font->descent = idesc * fface->scale;
    font->linegap = igap * fface->scale;
}

typedef SGbool SG_CALL ExecLineStartFunction(SGFont* font, const SGdchar* text, const SGdchar* start, const SGdchar* end, void* data);
typedef SGbool SG_CALL ExecLineEndFunction(SGFont* font, const SGdchar* text, const SGdchar* start, const SGdchar* end, float xoffset, float yoffset, void* data);
typedef SGbool SG_CALL ExecCharFunction(SGFont* font, const SGdchar* text, const SGdchar* chr, SGCharInfo* cinfo, float xoffset, float yoffset, void* data);
typedef SGbool SG_CALL ExecDoneFunction(SGFont* font, float xoffset, float yoffset, void* data);
static SGbool SG_CALL _sgFontExecuteU32(SGFont* font, const SGdchar* text, ExecLineStartFunction* execLineStart, ExecCharFunction* execChar, ExecLineEndFunction* execLineEnd, ExecDoneFunction* execDone, void* data)
{
    if(!font)
        return SG_FALSE;

    FontFace* fface = font->handle;

    float xoffset = 0.0;
    float yoffset = 0.0;

    const SGdchar* start = text;
    const SGdchar* end;
    const SGdchar* chr;
    size_t line = 0;

    float linesep = font->ascent - font->descent + font->linegap;

    SGCharInfo* info = NULL;
    float* kerning = NULL;
    size_t i;
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
        for(i = 1; i < end - start; i++)
            kerning[i-1] = stbtt_GetCodepointKernAdvance(&fface->info, start[i-1], start[i]) * fface->scale;
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
            if(chr != end - 1)
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

SGFont* SG_CALL sgFontCreateStream(SGStream* stream, SGbool delstream, float height, SGuint dpi, SGuint preload)
{
    SGFont* font = malloc(sizeof(SGFont));
    if(font == NULL)
        return NULL;

    font->stream = stream;
    font->del = delstream;
    FontFace* fface = NULL;

    fface = malloc(sizeof(FontFace));
    if(!fface) goto err;
    fface->buf = NULL;

    font->handle = fface;

    SGlong pos = sgStreamTell(stream);
    SGlong size = sgStreamTellSize(stream);
    size -= pos;
    if(pos < 0 || size < 0)
        goto err;

    fface->buf = malloc(size);
    if(sgStreamRead(stream, fface->buf, 1, size) != size)
        goto err;
    if(!stbtt_InitFont(&fface->info, fface->buf, 0))
        goto err;

    fface->scale = 1.0;

    font->conv[0] = sgConvCreate(SG_CONV_TYPE_UTF32, SG_CONV_TYPE_CHAR);
    font->conv[1] = sgConvCreate(SG_CONV_TYPE_UTF32, SG_CONV_TYPE_WCHAR_T);
    font->conv[2] = sgConvCreate(SG_CONV_TYPE_UTF32, SG_CONV_TYPE_UTF8);
    font->conv[3] = sgConvCreate(SG_CONV_TYPE_UTF32, SG_CONV_TYPE_UTF16);

    font->npreload = preload;

    _sgFontSetHeight(font, height, dpi);
    _sgFontCreateCache(font);

    return font;
err:
    if(fface)
    {
        if(fface->buf)
            free(fface->buf);
        free(fface);
    }
    fprintf(stderr, "Warning: Cannot create font\n");
    free(font);
    return NULL;
}
SGFont* SG_CALL sgFontCreate(const char* fname, float height, SGuint dpi, SGuint preload)
{
    SGStream* stream = sgStreamCreateFile(fname, "r");
    if(!stream)
    {
        fprintf(stderr, "Warning: Cannot create font %s\n", fname);
        return NULL;
    }
    return sgFontCreateStream(stream, SG_TRUE, height, dpi, preload);
}
void SG_CALL sgFontDestroy(SGFont* font)
{
    if(font == NULL)
        return;

    size_t i;
    for(i = 0; i < 4; i++)
        sgConvDestroy(font->conv[i]);

    FontFace* fface = font->handle;
    free(fface->buf);
    free(fface);

    _sgFontDestroyCache(font);

    if(font->del)
        sgStreamDestroy(font->stream);
    free(font);
}

void SG_CALL sgFontClearCache(SGFont* font)
{
    _sgFontDestroyCache(font);
    _sgFontCreateCache(font);
}
void SG_CALL sgFontSetHeight(SGFont* font, float height, SGuint dpi)
{
    _sgFontSetHeight(font, height, dpi);
    sgFontClearCache(font);
}

void SG_CALL sgFontPrintfW(SGFont* font, float x, float y, const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    sgFontPrintfvW(font, x, y, format, args);
    va_end(args);
}
void SG_CALL sgFontPrintfvW(SGFont* font, float x, float y, const wchar_t* format, va_list args)
{
    wchar_t* buf = sgAPrintfvW(format, args);
    sgFontPrintW(font, x, y, buf);
    sgAPrintFree(buf);
}

void SG_CALL sgFontPrintf(SGFont* font, float x, float y, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    sgFontPrintfv(font, x, y, format, args);
    va_end(args);
}
void SG_CALL sgFontPrintfv(SGFont* font, float x, float y, const char* format, va_list args)
{
    char* buf = sgAPrintfv(format, args);
    sgFontPrint(font, x, y, buf);
    sgAPrintFree(buf);
}

static SGbool SG_CALL _printChar(SGFont* font, const SGdchar* text, const SGdchar* chr, SGCharInfo* cinfo, float xoffset, float yoffset, void* data)
{
    SGVec2* pos = data;
    sgTextureDrawRads3f2f2f1f(cinfo->texture, pos->x + xoffset + cinfo->xpre, ((int)(pos->y + yoffset)) + cinfo->ypre, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0);
    return SG_FALSE;
}
void SG_CALL sgFontPrintU32(SGFont* font, float x, float y, const SGdchar* text)
{
    SGVec2 pos = sgVec2f(x, y);
    _sgFontExecuteU32(font, text, NULL, _printChar, NULL, NULL, &pos);
}
void SG_CALL sgFontPrintU16(SGFont* font, float x, float y, const SGwchar* text)
{
    SGdchar* dtext = _sgFontU16ToU32(font, text);
    sgFontPrintU32(font, x, y, dtext);
    free(dtext);
}
void SG_CALL sgFontPrintU8(SGFont* font, float x, float y, const SGchar* text)
{
    SGdchar* dtext = _sgFontU8ToU32(font, text);
    sgFontPrintU32(font, x, y, dtext);
    free(dtext);
}
void SG_CALL sgFontPrintW(SGFont* font, float x, float y, const wchar_t* text)
{
    SGdchar* dtext = _sgFontWToU32(font, text);
    sgFontPrintU32(font, x, y, dtext);
    free(dtext);
}
void SG_CALL sgFontPrint(SGFont* font, float x, float y, const char* text)
{
    SGdchar* dtext = _sgFontToU32(font, text);
    sgFontPrintU32(font, x, y, dtext);
    free(dtext);
}

void SG_CALL sgFontPrintAlignedfW(SGFont* font, float x, float y, SGenum align, const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    sgFontPrintAlignedfvW(font, x, y, align, format, args);
    va_end(args);
}
void SG_CALL sgFontPrintAlignedfvW(SGFont* font, float x, float y, SGenum align, const wchar_t* format, va_list args)
{
    wchar_t* buf = sgAPrintfvW(format, args);
    sgFontPrintAlignedW(font, x, y, align, buf);
    sgAPrintFree(buf);
}

void SG_CALL SG_HINT_PRINTF(5, 6) sgFontPrintAlignedf(SGFont* font, float x, float y, SGenum align, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    sgFontPrintAlignedfv(font, x, y, align, format, args);
    va_end(args);
}
void SG_CALL SG_HINT_PRINTF(5, 0) sgFontPrintAlignedfv(SGFont* font, float x, float y, SGenum align, const char* format, va_list args)
{
    char* buf = sgAPrintfv(format, args);
    sgFontPrintAligned(font, x, y, align, buf);
    sgAPrintFree(buf);
}

void SG_CALL sgFontPrintAlignedU32(SGFont* font, float x, float y, SGenum align, const SGdchar* text)
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
void SG_CALL sgFontPrintAlignedU16(SGFont* font, float x, float y, SGenum align, const SGwchar* text)
{
    SGdchar* dtext = _sgFontU16ToU32(font, text);
    sgFontPrintAlignedU32(font, x, y, align, dtext);
    free(dtext);
}
void SG_CALL sgFontPrintAlignedU8(SGFont* font, float x, float y, SGenum align, const SGchar* text)
{
    SGdchar* dtext = _sgFontU8ToU32(font, text);
    sgFontPrintAlignedU32(font, x, y, align, dtext);
    free(dtext);
}
void SG_CALL sgFontPrintAlignedW(SGFont* font, float x, float y, SGenum align, const wchar_t* text)
{
    SGdchar* dtext = _sgFontWToU32(font, text);
    sgFontPrintAlignedU32(font, x, y, align, dtext);
    free(dtext);
}
void SG_CALL sgFontPrintAligned(SGFont* font, float x, float y, SGenum align, const char* text)
{
    SGdchar* dtext = _sgFontToU32(font, text);
    sgFontPrintAlignedU32(font, x, y, align, dtext);
    free(dtext);
}

void SG_CALL sgFontStrSizefW(SGFont* font, float* x, float* y, const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    sgFontStrSizefvW(font, x, y, format, args);
    va_end(args);
}
void SG_CALL sgFontStrSizefvW(SGFont* font, float* x, float* y, const wchar_t* format, va_list args)
{
    wchar_t* buf = sgAPrintfvW(format, args);
    sgFontStrSizeW(font, x, y, buf);
    sgAPrintFree(buf);
}

void SG_CALL sgFontStrSizef(SGFont* font, float* x, float* y, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    sgFontStrSizefv(font, x, y, format, args);
    va_end(args);
}
void SG_CALL sgFontStrSizefv(SGFont* font, float* x, float* y, const char* format, va_list args)
{
    char* buf = sgAPrintfv(format, args);
    sgFontStrSize(font, x, y, buf);
    sgAPrintFree(buf);
}

static SGbool SG_CALL _strSizeLineEnd(SGFont* font, const SGdchar* text, const SGdchar* start, const SGdchar* end, float xoffset, float yoffset, void* data)
{
    SGVec2* size = data;
    if(size->x < xoffset)
        size->x = xoffset;
    return SG_FALSE;
}
static SGbool SG_CALL _strSizeDone(SGFont* font, float xoffset, float yoffset, void* data)
{
    SGVec2* size = data;
    size->y = yoffset + font->ascent - font->descent;
    return SG_TRUE;
}
void SG_CALL sgFontStrSizeU32(SGFont* font, float* x, float* y, const SGdchar* text)
{
    SGVec2 size = sgVec2f(0.0, 0.0);
    _sgFontExecuteU32(font, text, NULL, NULL, _strSizeLineEnd, _strSizeDone, &size);
    *x = size.x;
    *y = size.y;
}
void SG_CALL sgFontStrSizeU16(SGFont* font, float* x, float* y, const SGwchar* text)
{
    SGdchar* dtext = _sgFontU16ToU32(font, text);
    sgFontStrSizeU32(font, x, y, dtext);
    free(dtext);
}
void SG_CALL sgFontStrSizeU8(SGFont* font, float* x, float* y, const SGchar* text)
{
    SGdchar* dtext = _sgFontU8ToU32(font, text);
    sgFontStrSizeU32(font, x, y, dtext);
    free(dtext);
}
void SG_CALL sgFontStrSizeW(SGFont* font, float* x, float* y, const wchar_t* text)
{
    SGdchar* dtext = _sgFontWToU32(font, text);
    sgFontStrSizeU32(font, x, y, dtext);
    free(dtext);
}
void SG_CALL sgFontStrSize(SGFont* font, float* x, float* y, const char* text)
{
    SGdchar* dtext = _sgFontToU32(font, text);
    sgFontStrSizeU32(font, x, y, dtext);
    free(dtext);
}

size_t SG_CALL sgFontFindIndexfW(SGFont* font, float x, float y, const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    size_t pos = sgFontFindIndexfvW(font, x, y, format, args);
    va_end(args);
    return pos;
}
size_t SG_CALL sgFontFindIndexfvW(SGFont* font, float x, float y, const wchar_t* format, va_list args)
{
    wchar_t* buf = sgAPrintfvW(format, args);
    size_t ind = sgFontFindIndexW(font, x, y, buf);
    sgAPrintFree(buf);
    return ind;
}

size_t SG_CALL sgFontFindIndexf(SGFont* font, float x, float y, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    size_t pos = sgFontFindIndexfv(font, x, y, format, args);
    va_end(args);
    return pos;
}
size_t SG_CALL sgFontFindIndexfv(SGFont* font, float x, float y, const char* format, va_list args)
{
    char* buf = sgAPrintfv(format, args);
    size_t ind = sgFontFindIndex(font, x, y, buf);
    sgAPrintFree(buf);
    return ind;
}

// todo: make this bisect instead of performing a linear search
size_t SG_CALL sgFontFindIndexU32(SGFont* font, float x, float y, const SGdchar* text)
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

size_t SG_CALL sgFontFindIndexU16(SGFont* font, float x, float y, const SGwchar* text)
{
    SGdchar* dtext = _sgFontU16ToU32(font, text);
    size_t pos = sgFontFindIndexU32(font, x, y, dtext);
    free(dtext);
    return pos;
}
size_t SG_CALL sgFontFindIndexU8(SGFont* font, float x, float y, const SGchar* text)
{
    SGdchar* dtext = _sgFontU8ToU32(font, text);
    size_t pos = sgFontFindIndexU32(font, x, y, dtext);
    free(dtext);
    return pos;
}
size_t SG_CALL sgFontFindIndexW(SGFont* font, float x, float y, const wchar_t* text)
{
    SGdchar* dtext = _sgFontWToU32(font, text);
    size_t pos = sgFontFindIndexU32(font, x, y, dtext);
    free(dtext);
    return pos;
}
size_t SG_CALL sgFontFindIndex(SGFont* font, float x, float y, const char* text)
{
    SGdchar* dtext = _sgFontToU32(font, text);
    size_t pos = sgFontFindIndexU32(font, x, y, dtext);
    free(dtext);
    return pos;
}

void SG_CALL sgFontGetPosfW(SGFont* font, float* x, float* y, size_t index, const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    sgFontGetPosfvW(font, x, y, index, format, args);
    va_end(args);
}
void SG_CALL sgFontGetPosfvW(SGFont* font, float* x, float* y, size_t index, const wchar_t* format, va_list args)
{
    wchar_t* buf = sgAPrintfvW(format, args);
    sgFontGetPosW(font, x, y, index, buf);
    sgAPrintFree(buf);
}

void SG_CALL SG_HINT_PRINTF(5, 6) sgFontGetPosf(SGFont* font, float* x, float* y, size_t index, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    sgFontGetPosfv(font, x, y, index, format, args);
    va_end(args);
}
void SG_CALL SG_HINT_PRINTF(5, 0) sgFontGetPosfv(SGFont* font, float* x, float* y, size_t index, const char* format, va_list args)
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

static SGbool SG_CALL _getPosLineStart(SGFont* font, const SGdchar* text, const SGdchar* start, const SGdchar* end, void* data)
{
    PosInfo* pi = data;
    if(start - text > pi->index)
        return SG_TRUE;
    return SG_FALSE;
}
static SGbool SG_CALL _getPosChar(SGFont* font, const SGdchar* text, const SGdchar* chr, SGCharInfo* cinfo, float xoffset, float yoffset, void* data)
{
    PosInfo* pi = data;
    if(chr - text == pi->index)
    {
        pi->pos.x += cinfo->xpre;
        return SG_TRUE;
    }
    return SG_FALSE;
}
static SGbool SG_CALL _getPosDone(SGFont* font, float xoffset, float yoffset, void* data)
{
    PosInfo* pi = data;
    pi->pos.x += xoffset;
    pi->pos.y += yoffset;
    return SG_TRUE;
}
void SG_CALL sgFontGetPosU32(SGFont* font, float* x, float* y, size_t index, const SGdchar* text)
{
    PosInfo pi;
    pi.pos = sgVec2f(0.0, 0.0);
    pi.index = index;
    _sgFontExecuteU32(font, text, _getPosLineStart, _getPosChar, NULL, _getPosDone, &pi);
    *x = pi.pos.x;
    *y = pi.pos.y;
}
void SG_CALL sgFontGetPosU16(SGFont* font, float* x, float* y, size_t index, const SGwchar* text)
{
    SGdchar* dtext = _sgFontU16ToU32(font, text);
    sgFontGetPosU32(font, x, y, index, dtext);
    free(dtext);
}
void SG_CALL sgFontGetPosU8(SGFont* font, float* x, float* y, size_t index, const SGchar* text)
{
    SGdchar* dtext = _sgFontU8ToU32(font, text);
    sgFontGetPosU32(font, x, y, index, dtext);
    free(dtext);
}
void SG_CALL sgFontGetPosW(SGFont* font, float* x, float* y, size_t index, const wchar_t* text)
{
    SGdchar* dtext = _sgFontWToU32(font, text);
    sgFontGetPosU32(font, x, y, index, dtext);
    free(dtext);
}
void SG_CALL sgFontGetPos(SGFont* font, float* x, float* y, size_t index, const char* text)
{
    SGdchar* dtext = _sgFontToU32(font, text);
    sgFontGetPosU32(font, x, y, index, dtext);
    free(dtext);
}
