/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "COPYING.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#include "common.h"

#include <stdlib.h>

typedef struct FontFace
{
    stbtt_fontinfo info;
    void* buf;
    float scale;
} FontFace;

SGenum SG_EXPORT sgmFontsFaceCreate(void** face, SGStream* stream)
{
    if(!stream || !stream->read || !stream->seek || !stream->tell)
        return SG_INVALID_VALUE;

    *face = malloc(sizeof(FontFace));
    FontFace* fface = *face;

    SGlong pos;
    SGlong size;

    pos = stream->tell(stream->data);
    if(pos < 0)
        goto err;

    stream->seek(stream->data, 0, SG_SEEK_END);
    size = stream->tell(stream->data);
    stream->seek(stream->data, pos, SG_SEEK_SET);
    // "size < pos" is a sanity test
    if(size < 0 || size < pos)
        goto err;

    fface->buf = malloc(size);
    if(stream->read(stream->data, fface->buf, 1, size) != size)
        goto err;
    stbtt_InitFont(&fface->info, fface->buf, 0);

    fface->scale = 1.0;

    return SG_OK;

err:
    free(*face);
    return SG_UNKNOWN_ERROR;
}
SGenum SG_EXPORT sgmFontsFaceDestroy(void* face)
{
    if(!face) return SG_OK; // SG_INVALID_VALUE
    FontFace* fface = face;
    free(fface->buf);
    free(fface);
    return SG_OK;
}

SGenum SG_EXPORT sgmFontsFaceSetHeight(void* face, float height, SGuint dpi)
{
    if(!face) return SG_INVALID_VALUE;
    FontFace* fface = face;
    //fface->scale = stbtt_ScaleForPixelHeight(&fface->info, height);
    fface->scale = stbtt_ScaleForMappingEmToPixels(&fface->info, height * dpi / 72.0);
    return SG_OK;
}
SGenum SG_EXPORT sgmFontsFaceGetMetrics(void* face, float* ascent, float* descent, float* linegap)
{
    if(!face) return SG_INVALID_VALUE;
    FontFace* fface = face;

    int iasc, idesc, igap;
    stbtt_GetFontVMetrics(&fface->info, &iasc, &idesc, &igap);
    *ascent = iasc * fface->scale;
    *descent = idesc * fface->scale;
    *linegap = igap * fface->scale;

    return SG_OK;
}

SGenum SG_EXPORT sgmFontsCharsCreate(void* face, const SGdchar* chars, size_t numchars, float* width, float* height, float* prex, float* prey, float* postx, float* posty, size_t* datawidth, size_t* dataheight, void** data)
{
    if(!face) return SG_INVALID_VALUE;

    FontFace* fface = (FontFace*)face;

    int adv, left;
    int dw, dh;
    int xo, yo;

    int glyph;
    size_t i;
    for(i = 0; i < numchars; i++)
    {
        glyph = stbtt_FindGlyphIndex(&fface->info, chars[i]);

        //dw = dh = 0;
        data[i] = stbtt_GetGlyphBitmap(&fface->info, fface->scale, fface->scale, glyph, &dw, &dh, &xo, &yo);
        datawidth[i] = dw;
        dataheight[i] = dh;

        stbtt_GetGlyphHMetrics(&fface->info, glyph, &adv, &left);
        prex[i] = xo;
        prey[i] = yo;
        postx[i] = adv * fface->scale;
        posty[i] = 0;
        width[i] = adv * fface->scale;
        height[i] = 0; /* TODO */
    }

    return SG_OK;
}
SGenum SG_EXPORT sgmFontsCharsFreeData(void* data)
{
    stbtt_FreeBitmap(data, NULL);
    return SG_OK;
}

SGenum SG_EXPORT sgmFontsCharsGetKerning(void* face, const SGdchar* chars, size_t numchars, float* kerning)
{
    if(!face) return SG_INVALID_VALUE;
    FontFace* fface = face;

    size_t i;
    for(i = 1; i < numchars; i++)
        kerning[i-1] = stbtt_GetCodepointKernAdvance(&fface->info, chars[i-1], chars[i]) * fface->scale;

    return SG_OK;
}
