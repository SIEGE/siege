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

#define SG_BUILD_LIBRARY
#include <siege/graphics/mask.h>
// for DrawDBG && _sg_drawCurColor
#include <siege/graphics/draw.h>

#include <stdlib.h>
#include <math.h>
// for fprintf
#include <stdio.h>

SGMask* SG_CALL sgMaskCreateSprite(SGSprite* sprite)
{
    return sgMaskCreateTexture2iv(sprite->subimages[0], sgIVec2fv(sprite->offset));
}
SGMask* SG_CALL sgMaskCreateTexture2i(SGTexture* texture, SGint xoffset, SGint yoffset)
{
    return sgMaskCreateTexture2iv(texture, sgIVec2i(xoffset, yoffset));
}
SGMask* SG_CALL sgMaskCreateTexture2iv(SGTexture* texture, SGIVec2 offset)
{
    SGMask* mask = malloc(sizeof(SGMask));
    if(mask == NULL)
        return NULL;
    sgRCountInit(&mask->cnt);

    SGuint i, j;

    mask->width = sgTextureGetWidth(texture);
    mask->height = sgTextureGetHeight(texture);

    mask->offset = offset;

    mask->precise = SG_TRUE;

    mask->field = malloc(mask->width * sizeof(SGbool*));
    for(i = 0; i < mask->width; i++)
        mask->field[i] = calloc(mask->height, sizeof(SGbool));

    SGIVec2 asize = sgTextureGetSize2iv(texture);
    SGuint awidth = asize.x;
    SGuint bpp = sgTextureGetBPP(texture);
    char* data = sgTextureGetData(texture);

    /*SGubyte bypp = 0;*/
    SGubyte r, g, b, a;
    SGubyte rbits = 0;
    SGubyte gbits = 0;
    SGubyte bbits = 0;
    SGubyte abits = 0;

    switch(bpp)
    {
        case 32:
            rbits = 8;
            gbits = 8;
            bbits = 8;
            abits = 8;
            /*bypp = 4;*/
            break;
        case 24:
            rbits = 8;
            gbits = 8;
            bbits = 8;
            /*bypp = 3;*/
            break;
        case 16:
            rbits = 5;
            gbits = 6;
            bbits = 5;
            /*bypp = 2;*/
            break;
        case 15:
            rbits = 5;
            gbits = 5;
            bbits = 5;
            abits = 1; // ?
            /*bypp = 2;*/
            break;
        case 8:
            abits = 8;
            /*bypp = 1;*/
            break;

        default:
            fprintf(stderr, "Unsupported BPP '%d'\n", bpp);
    }

    float col[4];
    sgDrawGetColor4fv(col);

    r = (SGubyte)(col[0] * ((1 << rbits) - 1));
    g = (SGubyte)(col[1] * ((1 << gbits) - 1));
    b = (SGubyte)(col[2] * ((1 << bbits) - 1));
    a = (SGubyte)(col[3] * ((1 << abits) - 1));

    SGuint ui = a
            |    (b << abits)
            |    (g << (abits + bbits))
            |    (r << (abits + bbits + gbits));

    for(i = 0; i < mask->width; i++)
    {
        for(j = 0; j < mask->height; j++)
        {
            switch(bpp)
            {
                case 32:
                    mask->field[i][j] = data[(j * awidth + i) * 4 + 3] ? SG_TRUE : SG_FALSE;
                    break;
                case 24:
                    mask->field[i][j] = (data[(j * awidth + i) * 3 + 0] == r)
                                    &&    (data[(j * awidth + i) * 3 + 1] == g)
                                    &&    (data[(j * awidth + i) * 3 + 2] == b);
                    break;
                case 16:
                case 15:
                    mask->field[i][j] = *(SGushort*)&data[(j * awidth + i) * 2] == ui;
                    break;
                case 8:
                    mask->field[i][j] = data[(j * awidth + i)] == a;
                    break;
            }
        }
    }

    sgTextureFreeData(data);

    return mask;
}
SGMask* SG_CALL sgMaskCreateTexture(SGTexture* texture)
{
    SGMask* mask = sgMaskCreateTexture2i(texture, 0, 0);
    if(mask == NULL)
        return NULL;
    mask->offset.x = mask->width / 2;
    mask->offset.y = mask->height / 2;
    return mask;
}
SGMask* SG_CALL sgMaskCreateFile2i(const char* fname, SGint xoffset, SGint yoffset)
{
    return sgMaskCreateFile2iv(fname, sgIVec2i(xoffset, yoffset));
}
SGMask* SG_CALL sgMaskCreateFile2iv(const char* fname, SGIVec2 offset)
{
    SGTexture* texture = sgTextureCreateFile(fname);
    if(texture == NULL)
        return NULL;
    SGMask* mask = sgMaskCreateTexture2iv(texture, offset);
    sgTextureRelease(texture);
    return mask;
}
SGMask* SG_CALL sgMaskCreateFile(const char* fname)
{
    SGMask* mask = sgMaskCreateFile2i(fname, 0, 0);
    if(mask == NULL)
        return NULL;
    mask->offset.x = mask->width / 2;
    mask->offset.y = mask->height / 2;
    return mask;
}
void SG_CALL sgMaskForceDestroy(SGMask* mask)
{
    if(mask == NULL)
        return;

    SGuint i;
    for(i = 0; i < mask->width; i++)
        free(mask->field[i]);
    free(mask->field);
    sgRCountDeinit(&mask->cnt);
    free(mask);
}

void SG_CALL sgMaskRelease(SGMask* mask)
{
    sgMaskUnlock(mask);
}
void SG_CALL sgMaskLock(SGMask* mask)
{
    if(!mask) return;
    sgRCountInc(&mask->cnt);
}
void SG_CALL sgMaskUnlock(SGMask* mask)
{
    if(!mask) return;
    if(!sgRCountDec(&mask->cnt))
        sgMaskForceDestroy(mask);
}

SGbool SG_CALL sgMaskCheckCollision2i(SGMask* m1, SGint x1, SGint y1, SGMask* m2, SGint x2, SGint y2)
{
    return sgMaskCheckCollision2iv(m1, sgIVec2i(x1, y1), m2, sgIVec2i(x2, y2));
}
SGbool SG_CALL sgMaskCheckCollision2iv(SGMask* m1, SGIVec2 p1, SGMask* m2, SGIVec2 p2)
{
    int x1 = p1.x;
    int y1 = p1.y;
    int x2 = p2.x;
    int y2 = p2.y;

    x1 -= m1->offset.x;
    y1 -= m1->offset.y;
    x2 -= m2->offset.x;
    y2 -= m2->offset.y;

    if(x2 > x1)
    {
        x2 -= x1;
        x1 = 0;
    }
    else
    {
        x1 -= x2;
        x2 = 0;
    }
    if(y2 > y1)
    {
        y2 -= y1;
        y1 = 0;
    }
    else
    {
        y1 -= y2;
        y2 = 0;
    }

    ptrdiff_t i, j;
    for(i = 0; i < SG_MAX(m1->width, m2->width); i++)
        if((0 <= i - x1) && (i - x1 < m1->width)
        && (0 <= i - x2) && (i - x2 < m2->width))
            for(j = 0; j < SG_MAX(m1->height, m2->height); j++)
                if((0 <= j - y1) && (j - y1 < m1->height)
                && (0 <= j - y2) && (j - y2 < m2->height))
                    if((!m1->precise || m1->field[i - x1][j - y1])
                    && (!m2->precise || m2->field[i - x2][j - y2]))
                        return SG_TRUE;
    return SG_FALSE;
}

SGIVec2 SG_CALL sgMaskGetSize2iv(SGMask* mask)
{
    return sgIVec2i(mask->width, mask->height);
}
SGVec2 SG_CALL sgMaskGetSize2fv(SGMask* mask)
{
    return sgVec2iv(sgMaskGetSize2iv(mask));
}
SGuint SG_CALL sgMaskGetWidth(SGMask* mask)
{
    if(mask == NULL)
        return 0;
    return mask->width;
}
SGuint SG_CALL sgMaskGetHeight(SGMask* mask)
{
    if(mask == NULL)
        return 0;
    return mask->height;
}

void SG_CALL sgMaskDrawDBG(SGMask* mask, SGint x, SGint y, SGbool transparent)
{
    if(mask == NULL)
        return;
    SGuint i, j;

    sgDrawBegin(SG_POINTS);
        for(i = 0; i < mask->width; i++)
        {
            for(j = 0; j < mask->height; j++)
            {
                if(!transparent)
                    sgDrawColor1f(mask->field[i][j] ? 1.0 : 0.0);
                if(mask->field[i][j] || !transparent)
                    sgDrawVertex2f(x - mask->offset.x + i, y - mask->offset.y + j);
            }
        }
    sgDrawEnd();
}

/* DEPRECATED */
SGbool SG_CALL SG_HINT_DEPRECATED sgMaskCheckCollision(SGMask* m1, SGint x1, SGint y1, SGMask* m2, SGint x2, SGint y2)
{
    return sgMaskCheckCollision2i(m1, x1, y1, m2, x2, y2);
}

void SG_CALL SG_HINT_DEPRECATED sgMaskDestroy(SGMask* mask)
{
    sgMaskRelease(mask);
}
void SG_CALL SG_HINT_DEPRECATED sgMaskGetSize(SGMask* mask, SGuint* width, SGuint* height)
{
    SGIVec2 size = sgMaskGetSize2iv(mask);
    if(width)   *width = size.x;
    if(height)  *height = size.y;
}
