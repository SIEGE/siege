/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "license.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
*/

#define SG_BUILD_LIBRARY
#include <siege/graphics/sprite.h>
#include <siege/core/core.h>

#include <stdlib.h>
#include <math.h>

void SG_CALL _sgSpriteUpdateTick(SGSprite* sprite)
{
    SGulong tick = sgGetTick();
    sprite->image += sprite->speed * (tick - sprite->tick);
    sprite->tick = tick;

    while((SGuint)sprite->image >= sprite->numimages)
        sprite->image -= sprite->numimages;
}

SGSprite* SG_CALL sgSpriteCreateTexture2f(SGTexture* texture, float xoffset, float yoffset)
{
    return sgSpriteCreateTexture2fv(texture, sgVec2f(xoffset, yoffset));
}
SGSprite* SG_CALL sgSpriteCreateTexture2fv(SGTexture* texture, SGVec2 offset)
{
    SGSprite* sprite = malloc(sizeof(SGSprite));
    if(sprite == NULL)
        return NULL;
    sgRCountInit(&sprite->cnt);

    sprite->tick = sgGetTick();

    sprite->numimages = 1;
    sprite->subimages = malloc(sizeof(SGTexture*));
    sprite->subimages[0] = texture;
    sgTextureLock(texture);

    if(SG_IS_NAN(offset.x))
        offset.x = sgTextureGetWidth(texture) / 2.0;
    if(SG_IS_NAN(offset.y))
        offset.y = sgTextureGetHeight(texture) / 2.0;
    sprite->offset = offset;

    sprite->image = 0.0;
    sprite->speed = 1.0;

    return sprite;
}
SGSprite* SG_CALL sgSpriteCreateTexture(SGTexture* texture)
{
    return sgSpriteCreateTexture2f(texture, SG_NAN, SG_NAN);
}
SGSprite* SG_CALL sgSpriteCreateFile2f(const char* fname, float xoffset, float yoffset)
{
    return sgSpriteCreateFile2fv(fname, sgVec2f(xoffset, yoffset));
}
SGSprite* SG_CALL sgSpriteCreateFile2fv(const char* fname, SGVec2 offset)
{
    SGTexture* texture = sgTextureCreateFile(fname);
    if(texture == NULL)
        return NULL;
    sgTextureSetWrap(texture, SG_WRAP_CLAMP_TO_EDGE, SG_WRAP_CLAMP_TO_EDGE);
    SGSprite* sprite = sgSpriteCreateTexture2fv(texture, offset);
    sgTextureRelease(texture);
    return sprite;
}
SGSprite* SG_CALL sgSpriteCreateFile(const char* fname)
{
    return sgSpriteCreateFile2f(fname, SG_NAN, SG_NAN);
}
void SG_CALL sgSpriteForceDestroy(SGSprite* sprite)
{
    if(sprite == NULL)
        return;

    SGuint i;
    for(i = 0; i < sprite->numimages; i++)
        sgTextureUnlock(sprite->subimages[i]);
    free(sprite->subimages);
    sgRCountDeinit(&sprite->cnt);
    free(sprite);
}

void SG_CALL sgSpriteRelease(SGSprite* sprite)
{
    sgSpriteUnlock(sprite);
}
void SG_CALL sgSpriteLock(SGSprite* sprite)
{
    if(!sprite) return;
    sgRCountInc(&sprite->cnt);
}
void SG_CALL sgSpriteUnlock(SGSprite* sprite)
{
    if(!sprite) return;
    if(!sgRCountDec(&sprite->cnt))
        sgSpriteForceDestroy(sprite);
}

SGbool SG_CALL sgSpriteAddFrameFile(SGSprite* sprite, const char* fname)
{
    sprite->numimages++;
    sprite->subimages = realloc(sprite->subimages, (sprite->numimages + 1) * sizeof(SGTexture*));
    sprite->subimages[sprite->numimages] = sgTextureCreateFile(fname);
    if(!sprite->subimages[sprite->numimages])
        return SG_FALSE;
    sprite->numimages++;
    return SG_TRUE;
}

void SG_CALL sgSpriteSetImage(SGSprite* sprite, float image)
{
    sprite->image = image;
}
float SG_CALL sgSpriteGetImage(SGSprite* sprite)
{
    return sprite->image;
}

void SG_CALL sgSpriteSetOffset2f(SGSprite* sprite, float xoffset, float yoffset)
{
    sgSpriteSetOffset2fv(sprite, sgVec2f(xoffset, yoffset));
}
void SG_CALL sgSpriteSetOffset2fv(SGSprite* sprite, SGVec2 offset)
{
    sprite->offset = offset;
}
SGVec2 SG_CALL sgSpriteGetOffset2fv(SGSprite* sprite)
{
    return sprite->offset;
}

void SG_CALL sgSpriteDrawRads3f2f1f(SGSprite* sprite, float x, float y, float z, float xscale, float yscale, float angle)
{
    if(sprite == NULL)
        return;

    _sgSpriteUpdateTick(sprite);

    sgTextureDrawRads3f2f2f1f(sprite->subimages[(SGuint)sprite->image], x, y, z, xscale, yscale, sprite->offset.x, sprite->offset.y, angle);
}
void SG_CALL sgSpriteDrawRads2f2f1f(SGSprite* sprite, float x, float y, float xscale, float yscale, float angle)
{
    sgSpriteDrawRads3f2f1f(sprite, x, y, 0.0, xscale, yscale, angle);
}
void SG_CALL sgSpriteDrawRads3f1f(SGSprite* sprite, float x, float y, float z, float angle)
{
    sgSpriteDrawRads3f2f1f(sprite, x, y, z, 1.0, 1.0, angle);
}
void SG_CALL sgSpriteDrawRads2f1f(SGSprite* sprite, float x, float y, float angle)
{
    sgSpriteDrawRads3f2f1f(sprite, x, y, 0.0, 1.0, 1.0, angle);
}

void SG_CALL sgSpriteDrawDegs3f2f1f(SGSprite* sprite, float x, float y, float z, float xscale, float yscale, float angle)
{
    sgSpriteDrawRads3f2f1f(sprite, x, y, z, xscale, yscale, angle * SG_PI / 180.0);
}
void SG_CALL sgSpriteDrawDegs2f2f1f(SGSprite* sprite, float x, float y, float xscale, float yscale, float angle)
{
    sgSpriteDrawRads3f2f1f(sprite, x, y, 0.0, xscale, yscale, angle * SG_PI / 180.0);
}
void SG_CALL sgSpriteDrawDegs3f1f(SGSprite* sprite, float x, float y, float z, float angle)
{
    sgSpriteDrawRads3f2f1f(sprite, x, y, z, 1.0, 1.0, angle * SG_PI / 180.0);
}
void SG_CALL sgSpriteDrawDegs2f1f(SGSprite* sprite, float x, float y, float angle)
{
    sgSpriteDrawRads3f2f1f(sprite, x, y, 0.0, 1.0, 1.0, angle * SG_PI / 180.0);
}

void SG_CALL sgSpriteDraw3f2f(SGSprite* sprite, float x, float y, float z, float xscale, float yscale)
{
    sgSpriteDrawRads3f2f1f(sprite, x, y, z, xscale, yscale, 0.0);
}
void SG_CALL sgSpriteDraw2f2f(SGSprite* sprite, float x, float y, float xscale, float yscale)
{
    sgSpriteDrawRads3f2f1f(sprite, x, y, 0.0, xscale, yscale, 0.0);
}
void SG_CALL sgSpriteDraw3f(SGSprite* sprite, float x, float y, float z)
{
    sgSpriteDrawRads3f2f1f(sprite, x, y, z, 1.0, 1.0, 0.0);
}
void SG_CALL sgSpriteDraw2f(SGSprite* sprite, float x, float y)
{
    sgSpriteDrawRads3f2f1f(sprite, x, y, 0.0, 1.0, 1.0, 0.0);
}

SGIVec2 SG_CALL sgSpriteGetSize2iv(SGSprite* sprite)
{
    return sgTextureGetSize2iv(sprite->subimages[0]);
}
SGVec2 SG_CALL sgSpriteGetSize2fv(SGSprite* sprite)
{
    return sgVec2iv(sgSpriteGetSize2iv(sprite));
}
SGuint SG_CALL sgSpriteGetWidth(SGSprite* sprite)
{
    if(sprite == NULL)
        return 0;

    return sgTextureGetWidth(sprite->subimages[0]);
}
SGuint SG_CALL sgSpriteGetHeight(SGSprite* sprite)
{
    if(sprite == NULL)
        return 0;

    return sgTextureGetHeight(sprite->subimages[0]);
}

/* DEPRECATED */
void SG_CALL SG_HINT_DEPRECATED sgSpriteSetOffset(SGSprite* sprite, float x, float y)
{
    sgSpriteSetOffset2f(sprite, x, y);
}
void SG_CALL sgSpriteGetOffset(SGSprite* sprite, float* x, float* y)
{
    SGVec2 offset = sgSpriteGetOffset2fv(sprite);
    if(x) *x = offset.x;
    if(y) *y = offset.y;
}
void SG_CALL SG_HINT_DEPRECATED sgSpriteSetSpeed(SGSprite* sprite, float speed)
{
}
float SG_CALL SG_HINT_DEPRECATED sgSpriteGetSpeed(SGSprite* sprite)
{
    return 0.0f;
}

void SG_CALL SG_HINT_DEPRECATED sgSpriteDestroy(SGSprite* sprite)
{
    sgSpriteRelease(sprite);
}
void SG_CALL SG_HINT_DEPRECATED sgSpriteGetSize(SGSprite* sprite, SGuint* width, SGuint* height)
{
    SGIVec2 size = sgSpriteGetSize2iv(sprite);
    if(width)   *width = size.x;
    if(height)  *height = size.y;
}
