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

#include "main.h"
#include "load.h"

#include <stdlib.h>
#include <stdio.h>

SGenum SG_EXPORT sgmFontsFaceCreate(void** face, const char* fname)
{
    *face = malloc(sizeof(FontFace));
    FontFace* fface = *face;

    SGenum err = SG_UNKNOWN_ERROR;
    FILE* file = NULL;
    size_t size;

    file = fopen(fname, "rb");
    if(!file) goto end;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);

    fface->buf = malloc(size);
    if(fread(fface->buf, 1, size, file) != size) goto end;
    stbtt_InitFont(&fface->info, fface->buf, 0);

    err = SG_OK;
end:
    if(file)
        fclose(file);
    return err;
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

    int glyph;
    size_t i;
    for(i = 0; i < charnum; i++)
    {
        glyph = stbtt_FindGlyphIndex(&fface->info, chars[i]);

        data[i] = stbtt_GetGlyphBitmap(&fface->info, scale, scale, glyph, &dw, &dh, &xo, &yo);
        datawidth[i] = dw;
        dataheight[i] = dh;

        stbtt_GetGlyphHMetrics(&fface->info, glyph, &adv, &left);
        prex[i] = left * scale + xo;
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
