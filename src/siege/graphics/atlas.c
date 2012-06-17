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
#include <siege/graphics/atlas.h>

#include <stdlib.h>
#include <stdio.h>

static SGTexture* _sgAtlasAddTexture(SGAtlas* atlas, SGTexture* texture, SGbool owner)
{
    SGAtlasNode* root;

    if(!texture) return NULL;
    atlas->textures = realloc(atlas->textures, (atlas->numtextures + 1) * sizeof(SGAtlasTexture));
    atlas->textures[atlas->numtextures].texture = texture;
    atlas->textures[atlas->numtextures].owner = owner;
    root = malloc(sizeof(SGAtlasNode));
    root->child[0] = NULL;
    root->child[1] = NULL;
    root->area.x = 0;
    root->area.y = 0;
    root->area.w = atlas->width;
    root->area.h = atlas->height;
    atlas->textures[atlas->numtextures].root = root;
    atlas->numtextures++;
    return texture;
}

SGAtlas* SG_EXPORT sgAtlasCreate(size_t width, size_t height, SGenum bpp)
{
    SGAtlas* atlas = malloc(sizeof(SGAtlas));
    if(!atlas) return NULL;

    atlas->width = width;
    atlas->height = height;
    atlas->bpp = bpp;
    atlas->numtextures = 0;
    atlas->textures = NULL;

    return atlas;
}
SGAtlas* SG_EXPORT sgAtlasCreateData(size_t width, size_t height, SGenum bpp, void* data)
{
    SGAtlas* atlas = sgAtlasCreate(width, height, bpp);
    if(!atlas) return NULL;

    _sgAtlasAddTexture(atlas, sgTextureCreateData(width, height, bpp, data), SG_TRUE);

    return atlas;
}
SGAtlas* SG_EXPORT sgAtlasCreateTexture(SGTexture* texture, SGbool owner)
{
    SGAtlas* atlas = sgAtlasCreate(sgTextureGetWidth(texture), sgTextureGetHeight(texture), sgTextureGetBPP(texture));
    if(!atlas) return NULL;

    _sgAtlasAddTexture(atlas, texture, owner);

    return atlas;
}
SGAtlas* SG_EXPORT sgAtlasCreateFile(const char* fname)
{
    return sgAtlasCreateTexture(sgTextureCreateFile(fname), SG_TRUE);
}
void SG_EXPORT sgAtlasDestroy(SGAtlas* atlas)
{
    if(!atlas)
        return;

    size_t i;
    for(i = 0; i < atlas->numtextures; i++)
    {
        if(atlas->textures[i].owner)
            sgTextureDestroy(atlas->textures[i].texture);
    }
    free(atlas->textures);
}

SGAtlasArea* SG_EXPORT sgAtlasAreaReserve(SGAtlas* atlas, size_t width, size_t height, SGbool overflow);
void SG_EXPORT sgAtlasAreaSetData(SGAtlas* atlas, SGAtlasArea* area, size_t width, size_t height, SGenum bpp, void* data);

void SG_EXPORT sgAtlasGetTexCoords(SGAtlas* atlas, SGint x, SGint y, SGint w, SGint h, float* x0, float* y0, float* x1, float* y1)
{
    *x0 = x / (float)atlas->width;
    *y0 = y / (float)atlas->height;
    *x1 = (x + w) / (float)atlas->width;
    *y1 = (y + h) / (float)atlas->width;
}
void SG_EXPORT sgAtlasGetTexCoordsA(SGAtlas* atlas, SGAtlasArea* area, float* x0, float* y0, float* x1, float* y1)
{
    sgAtlasGetTexCoords(atlas, area->x, area->y, area->w, area->h, x0, y0, x1, y1);
}

size_t SG_EXPORT sgAtlasGetNumTextures(SGAtlas* atlas)
{
    return atlas->numtextures;
}
SGTexture* SG_EXPORT sgAtlasGetTexture(SGAtlas* atlas, size_t index)
{
    if(index >= atlas->numtextures)
        return NULL;
    return atlas->textures[index].texture;
}

void SG_EXPORT sgAtlasGetSize(SGAtlas* atlas, size_t* width, size_t* height)
{
    if(width) *width = atlas->width;
    if(height) *height = atlas->height;
}
size_t SG_EXPORT sgAtlasGetWidth(SGAtlas* atlas)
{
    return atlas->width;
}
size_t SG_EXPORT sgAtlasGetHeight(SGAtlas* atlas)
{
    return atlas->height;
}
