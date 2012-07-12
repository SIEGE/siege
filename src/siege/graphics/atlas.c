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
#include <siege/graphics/draw.h>

#include <stdlib.h>
#include <stdio.h>

static SGbool _sgAtlasNodeIsLeaf(SGAtlasNode* node)
{
    return !node->child[0] && !node->child[1];
}
static SGAtlasNode* _sgAtlasNodeCreate(SGushort x, SGushort y, SGushort w, SGushort h, size_t index)
{
    SGAtlasNode* node = malloc(sizeof(SGAtlasNode));
    if(!node) return NULL;

    node->child[0] = NULL;
    node->child[1] = NULL;

    node->area.x = x;
    node->area.y = y;
    node->area.w = w;
    node->area.h = h;
    node->area.index = index;

    node->reserved = SG_FALSE;

    return node;
}
static void _sgAtlasNodeDestroy(SGAtlasNode* node)
{
    if(!node) return;
    _sgAtlasNodeDestroy(node->child[0]);
    _sgAtlasNodeDestroy(node->child[1]);
    free(node);
}
static SGAtlasNode* _sgAtlasNodeInsert(SGAtlasNode* node, SGushort w, SGushort h, size_t index)
{
    SGAtlasNode* nnode;
    if(!_sgAtlasNodeIsLeaf(node))
    {
        nnode = _sgAtlasNodeInsert(node->child[0], w, h, index);
        if(nnode) return nnode;

        return _sgAtlasNodeInsert(node->child[1], w, h, index);
    }
    if(node->reserved) return NULL;
    if(node->area.w < w || node->area.h < h) return NULL;
    if(node->area.w == w && node->area.h == h)
    {
        node->reserved = SG_TRUE;
        return node;
    }

    SGushort dw = node->area.w - w;
    SGushort dh = node->area.h - h;

    if(dw > dh)
    {
        node->child[0] = _sgAtlasNodeCreate(node->area.x    , node->area.y,  w, node->area.h, index);
        node->child[1] = _sgAtlasNodeCreate(node->area.x + w, node->area.y, dw, node->area.h, index);
    }
    else
    {
        node->child[0] = _sgAtlasNodeCreate(node->area.x, node->area.y    , node->area.w,  h, index);
        node->child[1] = _sgAtlasNodeCreate(node->area.x, node->area.y + h, node->area.w, dh, index);
    }

    return _sgAtlasNodeInsert(node->child[0], w, h, index);
}

static void SG_EXPORT _sgAtlasNodeDrawDBG(SGAtlasNode* node, float x, float y)
{
    if(!node) return;
    _sgAtlasNodeDrawDBG(node->child[0], x, y);
    _sgAtlasNodeDrawDBG(node->child[1], x, y);

    /*sgDrawRectangleWH(node->x + x - BORDER, node->y + y - BORDER, node->w, BORDER, SG_TRUE);
    sgDrawRectangleWH(node->x + x - BORDER, node->y + y - BORDER + node->h, node->w, BORDER, SG_TRUE);
    sgDrawRectangleWH(node->x + x - BORDER, node->y + y - BORDER, BORDER, node->h, SG_TRUE);
    sgDrawRectangleWH(node->x + x - BORDER + node->w, node->y + y - BORDER, BORDER, node->h, SG_TRUE);*/
    sgDrawRectangleWH(node->area.x + x, node->area.y + y, node->area.w, node->area.h, SG_FALSE);
}

static SGTexture* _sgAtlasAddTexture(SGAtlas* atlas, SGTexture* texture, SGbool owner)
{
    if(!texture) return NULL;
    atlas->textures = realloc(atlas->textures, (atlas->numtextures + 1) * sizeof(SGAtlasTexture));
    atlas->textures[atlas->numtextures].texture = texture;
    atlas->textures[atlas->numtextures].owner = owner;
    atlas->textures[atlas->numtextures].root = _sgAtlasNodeCreate(0, 0, atlas->width, atlas->height, atlas->numtextures);
    atlas->numtextures++;
    return texture;
}

SGAtlas* SG_EXPORT sgAtlasCreate(size_t width, size_t height, SGenum bpp)
{
    return sgAtlasCreateData(width, height, bpp, NULL);
}
SGAtlas* SG_EXPORT sgAtlasCreateData(size_t width, size_t height, SGenum bpp, void* data)
{
    SGAtlas* atlas = malloc(sizeof(SGAtlas));
    if(!atlas) return NULL;

    atlas->width = width;
    atlas->height = height;
    atlas->bpp = bpp;
    atlas->numtextures = 0;
    atlas->textures = NULL;

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
        _sgAtlasNodeDestroy(atlas->textures[i].root);
    }
    free(atlas->textures);
    free(atlas);
}

SGAtlasArea* SG_EXPORT sgAtlasAreaReserve(SGAtlas* atlas, size_t width, size_t height, SGbool overflow)
{
    if(width > atlas->width || height > atlas->height)
        return NULL;

    SGAtlasNode* node = _sgAtlasNodeInsert(atlas->textures[atlas->numtextures - 1].root, width, height, atlas->numtextures - 1);
    if(node) return &node->area;

    // no node, and we don't allow overflow
    if(!overflow) return NULL;

    _sgAtlasAddTexture(atlas, sgTextureCreateData(atlas->width, atlas->height, atlas->bpp, NULL), SG_TRUE);
    node = _sgAtlasNodeInsert(atlas->textures[atlas->numtextures - 1].root, width, height, atlas->numtextures - 1);
    if(node) return &node->area;

    return NULL;
}
void SG_EXPORT sgAtlasAreaSetData(SGAtlas* atlas, SGAtlasArea* area, size_t width, size_t height, SGenum bpp, void* data)
{
    if(area->index >= atlas->numtextures)
        return;
    if(width > area->w || height > area->h)
        return;
    sgTextureSetSubData(atlas->textures[area->index].texture, area->x, area->y, width, height, bpp, data);
}

void SG_EXPORT sgAtlasGetTexCoords4i(SGAtlas* atlas, SGint x, SGint y, SGint w, SGint h, float* x0, float* y0, float* x1, float* y1)
{
    *x0 = x / (float)atlas->width;
    *y0 = y / (float)atlas->height;
    *x1 = (x + w) / (float)atlas->width;
    *y1 = (y + h) / (float)atlas->width;
}
void SG_EXPORT sgAtlasGetTexCoordsA(SGAtlas* atlas, SGAtlasArea* area, float* x0, float* y0, float* x1, float* y1)
{
    sgAtlasGetTexCoords4i(atlas, area->x, area->y, area->w, area->h, x0, y0, x1, y1);
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

void SG_EXPORT sgAtlasDrawDBG(SGAtlas* atlas, float x, float y, size_t index, SGbool wires)
{
    if(index > atlas->numtextures)
    {
        sgDrawRectangleWH(x, y, atlas->width, atlas->height, SG_FALSE);
        return;
    }
    if(wires)
        _sgAtlasNodeDrawDBG(atlas->textures[index].root, x, y);
    else
        sgTextureDraw2f(atlas->textures[index].texture, x, y);
}
