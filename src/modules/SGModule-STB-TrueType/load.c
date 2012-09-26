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
    float height;
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
SGenum SG_EXPORT sgmFontsFaceSetHeight(void* face, float height)
{
    if(!face) return SG_INVALID_VALUE;
    FontFace* fface = face;
    fface->height = height;
    return SG_OK;
}
SGenum SG_EXPORT sgmFontsCharsCreate(void* face, SGuint* chars, SGuint charnum, float* width, float* height, float* prex, float* prey, float* postx, float* posty, SGuint* datawidth, SGuint* dataheight, void** data)
{
    if(!face) return SG_INVALID_VALUE;

    FontFace* fface = (FontFace*)face;
    //float scale = stbtt_ScaleForPixelHeight(&fface->info, fface->height);
    float scale = stbtt_ScaleForMappingEmToPixels(&fface->info, fface->height);

    int adv, left;
    int dw, dh;
    int xo, yo;
    int kern = 0;

    int glyph;
    size_t i;
    for(i = 0; i < charnum; i++)
    {
        glyph = stbtt_FindGlyphIndex(&fface->info, chars[i]);

        data[i] = stbtt_GetGlyphBitmap(&fface->info, scale, scale, glyph, &dw, &dh, &xo, &yo);
        datawidth[i] = dw;
        dataheight[i] = dh;

        if(i) kern = stbtt_GetGlyphKernAdvance(&fface->info, chars[i-1], chars[i]);

        stbtt_GetGlyphHMetrics(&fface->info, glyph, &adv, &left);
        prex[i] = (left + kern) * scale + xo;
        prey[i] = yo;
        postx[i] = adv * scale;
        posty[i] = 0;
    }

    return SG_OK;
}

SGenum SG_EXPORT sgmFontsCharsFreeData(void* data)
{
    stbtt_FreeBitmap(data, NULL);
    return SG_OK;
}
