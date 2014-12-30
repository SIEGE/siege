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
#include <siege/util/vector.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

static void SG_CALL _sgAtlasNodeDrawDBG(SGAtlasNode* node, float x, float y)
{
    if(!node) return;
    _sgAtlasNodeDrawDBG(node->child[0], x, y);
    _sgAtlasNodeDrawDBG(node->child[1], x, y);

    /*sgDrawRectangle2fWH(node->x + x - BORDER, node->y + y - BORDER, node->w, BORDER, SG_TRUE);
    sgDrawRectangle2fWH(node->x + x - BORDER, node->y + y - BORDER + node->h, node->w, BORDER, SG_TRUE);
    sgDrawRectangle2fWH(node->x + x - BORDER, node->y + y - BORDER, BORDER, node->h, SG_TRUE);
    sgDrawRectangle2fWH(node->x + x - BORDER + node->w, node->y + y - BORDER, BORDER, node->h, SG_TRUE);*/
    sgDrawRectangle2fWH(node->area.x + x, node->area.y + y, node->area.w, node->area.h, SG_FALSE);
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

SGAtlas* SG_CALL sgAtlasCreate(size_t width, size_t height, SGenum bpp)
{
    return sgAtlasCreateData(width, height, bpp, NULL);
}
SGAtlas* SG_CALL sgAtlasCreateData(size_t width, size_t height, SGenum bpp, void* data)
{
    SGAtlas* atlas = malloc(sizeof(SGAtlas));
    if(!atlas) return NULL;
    sgRCountInit(&atlas->cnt);

    atlas->width = width;
    atlas->height = height;
    atlas->bpp = bpp;
    atlas->numtextures = 0;
    atlas->textures = NULL;

    _sgAtlasAddTexture(atlas, sgTextureCreateData(width, height, bpp, data), SG_TRUE);

    return atlas;
}
SGAtlas* SG_CALL sgAtlasCreateTexture(SGTexture* texture, SGbool owner)
{
    SGAtlas* atlas = sgAtlasCreate(sgTextureGetWidth(texture), sgTextureGetHeight(texture), sgTextureGetBPP(texture));
    if(!atlas) return NULL;

    _sgAtlasAddTexture(atlas, texture, owner);

    return atlas;
}
SGAtlas* SG_CALL sgAtlasCreateFile(const char* fname)
{
    return sgAtlasCreateTexture(sgTextureCreateFile(fname), SG_TRUE);
}
void SG_CALL sgAtlasForceDestroy(SGAtlas* atlas)
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
    sgRCountDeinit(&atlas->cnt);
    free(atlas);
}

void SG_CALL sgAtlasRelease(SGAtlas* atlas)
{
    sgAtlasUnlock(atlas);
}
void SG_CALL sgAtlasLock(SGAtlas* atlas)
{
    if(!atlas) return;
    sgRCountInc(&atlas->cnt);
}
void SG_CALL sgAtlasUnlock(SGAtlas* atlas)
{
    if(!atlas) return;
    if(!sgRCountDec(&atlas->cnt))
        sgAtlasForceDestroy(atlas);
}

SGAtlasArea* SG_CALL sgAtlasAreaReserve(SGAtlas* atlas, size_t width, size_t height, SGbool overflow)
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
void SG_CALL sgAtlasAreaSetData(SGAtlas* atlas, SGAtlasArea* area, size_t width, size_t height, SGenum bpp, void* data)
{
    if(area->index >= atlas->numtextures)
        return;
    if(width > area->w || height > area->h)
        return;
    sgTextureSetSubData(atlas->textures[area->index].texture, area->x, area->y, width, height, bpp, data);
}

void SG_CALL sgAtlasAreaDrawRads3f2f2f1f(SGAtlas* atlas, SGAtlasArea* area, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    float s0, t0, s1, t1;
    sgAtlasGetTexCoordsA(atlas, area, &s0, &t0, &s1, &t1);

    // offset -> scale -> rotate -> translate
    SGVec2 pos = sgVec2f(x, y);
    SGVec2 p0, p1, p2, p3;
    p0 = sgVec2f(-xoffset                   , -yoffset                   );
    p1 = sgVec2f(-xoffset                   , -yoffset + area->h * yscale);
    p2 = sgVec2f(-xoffset + area->w * xscale, -yoffset + area->h * yscale);
    p3 = sgVec2f(-xoffset + area->w * xscale, -yoffset                   );

    p0 = sgVec2RotateRads(p0, sgVec2AngleRads(p0) + angle);
    p1 = sgVec2RotateRads(p1, sgVec2AngleRads(p1) + angle);
    p2 = sgVec2RotateRads(p2, sgVec2AngleRads(p2) + angle);
    p3 = sgVec2RotateRads(p3, sgVec2AngleRads(p3) + angle);

    p0 = sgVec2Add(p0, pos);
    p1 = sgVec2Add(p1, pos);
    p2 = sgVec2Add(p2, pos);
    p3 = sgVec2Add(p3, pos);

    sgDrawBeginT(SG_QUADS, sgAtlasGetTextureA(atlas, area));
        sgDrawTexCoord2f(s0, t0);
        sgDrawVertex3f(p0.x, p0.y, z);
        sgDrawTexCoord2f(s0, t1);
        sgDrawVertex3f(p1.x, p1.y, z);
        sgDrawTexCoord2f(s1, t1);
        sgDrawVertex3f(p2.x, p3.y, z);
        sgDrawTexCoord2f(s1, t0);
        sgDrawVertex3f(p2.x, p3.y, z);
    sgDrawEnd();
}
void SG_CALL sgAtlasAreaDrawDegs3f2f2f1f(SGAtlas* atlas, SGAtlasArea* area, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    sgAtlasAreaDrawRads3f2f2f1f(atlas, area, x, y, z, xscale, yscale, xoffset, yoffset, angle * SG_PI / 180.0);
}
void SG_CALL sgAtlasAreaDrawRads2f2f2f1f(SGAtlas* atlas, SGAtlasArea* area, float x, float y, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    sgAtlasAreaDrawRads3f2f2f1f(atlas, area, x, y, 0.0, xscale, yscale, xoffset, yoffset, angle);
}
void SG_CALL sgAtlasAreaDrawDegs2f2f2f1f(SGAtlas* atlas, SGAtlasArea* area, float x, float y, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    sgAtlasAreaDrawDegs3f2f2f1f(atlas, area, x, y, 0.0, xscale, yscale, xoffset, yoffset, angle);
}
void SG_CALL sgAtlasAreaDrawRads3f2f1f(SGAtlas* atlas, SGAtlasArea* area, float x, float y, float z, float xscale, float yscale, float angle)
{
    sgAtlasAreaDrawRads3f2f2f1f(atlas, area, x, y, z, xscale, yscale, 0.0, 0.0, angle);
}
void SG_CALL sgAtlasAreaDrawDegs3f2f1f(SGAtlas* atlas, SGAtlasArea* area, float x, float y, float z, float xscale, float yscale, float angle)
{
    sgAtlasAreaDrawDegs3f2f2f1f(atlas, area, x, y, z, xscale, yscale, 0.0, 0.0, angle);
}
void SG_CALL sgAtlasAreaDrawRads2f2f1f(SGAtlas* atlas, SGAtlasArea* area, float x, float y, float xscale, float yscale, float angle)
{
    sgAtlasAreaDrawRads3f2f2f1f(atlas, area, x, y, 0.0, xscale, yscale, 0.0, 0.0, angle);
}
void SG_CALL sgAtlasAreaDrawDegs2f2f1f(SGAtlas* atlas, SGAtlasArea* area, float x, float y, float xscale, float yscale, float angle)
{
    sgAtlasAreaDrawDegs3f2f2f1f(atlas, area, x, y, 0.0, xscale, yscale, 0.0, 0.0, angle);
}
void SG_CALL sgAtlasAreaDrawRads3f1f(SGAtlas* atlas, SGAtlasArea* area, float x, float y, float z, float angle)
{
    sgAtlasAreaDrawRads3f2f2f1f(atlas, area, x, y, z, 1.0, 1.0, 0.0, 0.0, angle);
}
void SG_CALL sgAtlasAreaDrawDegs3f1f(SGAtlas* atlas, SGAtlasArea* area, float x, float y, float z, float angle)
{
    sgAtlasAreaDrawDegs3f2f2f1f(atlas, area, x, y, z, 1.0, 1.0, 0.0, 0.0, angle);
}
void SG_CALL sgAtlasAreaDrawRads2f1f(SGAtlas* atlas, SGAtlasArea* area, float x, float y, float angle)
{
    sgAtlasAreaDrawRads3f2f2f1f(atlas, area, x, y, 0.0, 1.0, 1.0, 0.0, 0.0, angle);
}
void SG_CALL sgAtlasAreaDrawDegs2f1f(SGAtlas* atlas, SGAtlasArea* area, float x, float y, float angle)
{
    sgAtlasAreaDrawDegs3f2f2f1f(atlas, area, x, y, 0.0, 1.0, 1.0, 0.0, 0.0, angle);
}
void SG_CALL sgAtlasAreaDraw3f2f2f(SGAtlas* atlas, SGAtlasArea* area, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset)
{
    sgAtlasAreaDrawRads3f2f2f1f(atlas, area, x, y, z, xscale, yscale, xoffset, yoffset, 0.0);
}
void SG_CALL sgAtlasAreaDraw2f2f2f(SGAtlas* atlas, SGAtlasArea* area, float x, float y, float xscale, float yscale, float xoffset, float yoffset)
{
    sgAtlasAreaDrawRads3f2f2f1f(atlas, area, x, y, 0.0, xscale, yscale, xoffset, yoffset, 0.0);
}
void SG_CALL sgAtlasAreaDraw3f2f(SGAtlas* atlas, SGAtlasArea* area, float x, float y, float z, float xscale, float yscale)
{
    sgAtlasAreaDrawRads3f2f2f1f(atlas, area, x, y, z, xscale, yscale, 0.0, 0.0, 0.0);
}
void SG_CALL sgAtlasAreaDraw2f2f(SGAtlas* atlas, SGAtlasArea* area, float x, float y, float xscale, float yscale)
{
    sgAtlasAreaDrawRads3f2f2f1f(atlas, area, x, y, 0.0, xscale, yscale, 0.0, 0.0, 0.0);
}
void SG_CALL sgAtlasAreaDraw3f(SGAtlas* atlas, SGAtlasArea* area, float x, float y, float z)
{
    sgAtlasAreaDrawRads3f2f2f1f(atlas, area, x, y, z, 1.0, 1.0, 0.0, 0.0, 0.0);
}
void SG_CALL sgAtlasAreaDraw2f(SGAtlas* atlas, SGAtlasArea* area, float x, float y)
{
    sgAtlasAreaDrawRads3f2f2f1f(atlas, area, x, y, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0);
}
void SG_CALL sgAtlasAreaDraw(SGAtlas* atlas, SGAtlasArea* area)
{
    sgAtlasAreaDrawRads3f2f2f1f(atlas, area, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0);
}

void SG_CALL sgAtlasGetTexCoords4i(SGAtlas* atlas, SGint x, SGint y, SGint w, SGint h, float* s0, float* t0, float* s1, float* t1)
{
    *s0 = x / (float)atlas->width;
    *t0 = y / (float)atlas->height;
    *s1 = (x + w) / (float)atlas->width;
    *t1 = (y + h) / (float)atlas->width;
}
void SG_CALL sgAtlasGetTexCoordsA(SGAtlas* atlas, SGAtlasArea* area, float* s0, float* t0, float* s1, float* t1)
{
    sgAtlasGetTexCoords4i(atlas, area->x, area->y, area->w, area->h, s0, t0, s1, t1);
}

size_t SG_CALL sgAtlasGetNumTextures(SGAtlas* atlas)
{
    return atlas->numtextures;
}
SGTexture* SG_CALL sgAtlasGetTexture(SGAtlas* atlas, size_t index)
{
    if(index >= atlas->numtextures)
        return NULL;
    return atlas->textures[index].texture;
}
SGTexture* SG_CALL sgAtlasGetTextureA(SGAtlas* atlas, SGAtlasArea* area)
{
    return sgAtlasGetTexture(atlas, area->index);
}

SGIVec2 SG_CALL sgAtlasGetSize2iv(SGAtlas* atlas)
{
    return sgIVec2i(atlas->width, atlas->height);
}
SGVec2 SG_CALL sgAtlasGetSize2fv(SGAtlas* atlas)
{
    return sgVec2iv(sgAtlasGetSize2iv(atlas));
}
size_t SG_CALL sgAtlasGetWidth(SGAtlas* atlas)
{
    return atlas->width;
}
size_t SG_CALL sgAtlasGetHeight(SGAtlas* atlas)
{
    return atlas->height;
}

void SG_CALL sgAtlasDrawDBG(SGAtlas* atlas, float x, float y, size_t index, SGbool wires)
{
    if(index > atlas->numtextures)
    {
        sgDrawRectangle2fWH(x, y, atlas->width, atlas->height, SG_FALSE);
        return;
    }
    if(wires)
        _sgAtlasNodeDrawDBG(atlas->textures[index].root, x, y);
    else
        sgTextureDraw2f(atlas->textures[index].texture, x, y);
}

/* DEPRECATED */
void SG_CALL SG_HINT_DEPRECATED sgAtlasDestroy(SGAtlas* atlas)
{
    sgAtlasRelease(atlas);
}
void SG_CALL SG_HINT_DEPRECATED sgAtlasGetSize(SGAtlas* atlas, size_t* width, size_t* height)
{
    SGIVec2 size = sgAtlasGetSize2iv(atlas);
    if(width)   *width = size.x;
    if(height)  *height = size.y;
}
