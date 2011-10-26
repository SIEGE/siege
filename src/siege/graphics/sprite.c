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

void SG_EXPORT _sgSpriteUpdateTick(SGSprite* sprite)
{
    SGulong tick = sgGetTick();
    sprite->image += sprite->speed * (tick - sprite->tick);
    sprite->tick = tick;

    while((SGuint)sprite->image >= sprite->numimages)
        sprite->image -= sprite->numimages;
}

SGSprite* SG_EXPORT sgSpriteCreateTexture2f(SGTexture* texture, float xoffset, float yoffset)
{
    SGSprite* sprite = malloc(sizeof(SGSprite));
    if(sprite == NULL)
        return NULL;

    sprite->tick = sgGetTick();

    sprite->extimages = SG_TRUE;
    sprite->numimages = 1;
    sprite->subimages = malloc(sizeof(SGTexture*));
    sprite->subimages[0] = texture;

    if(xoffset != xoffset)
        xoffset = sgTextureGetWidth(texture) / 2.0;
    if(yoffset != yoffset)
        yoffset = sgTextureGetHeight(texture) / 2.0;
    sprite->xoffset = xoffset;
    sprite->yoffset = yoffset;

    sprite->image = 0.0;
    sprite->speed = 1.0;

    return sprite;
}
SGSprite* SG_EXPORT sgSpriteCreateTexture(SGTexture* texture)
{
    return sgSpriteCreateTexture2f(texture, SG_NAN, SG_NAN);
}
SGSprite* SG_EXPORT sgSpriteCreateFile2f(const char* fname, float xoffset, float yoffset)
{
    SGTexture* texture = sgTextureCreateFile(fname);
    if(texture == NULL)
        return NULL;
    SGSprite* sprite = sgSpriteCreateTexture2f(texture, xoffset, yoffset);
    if(sprite == NULL)
    {
        sgTextureDestroy(texture);
        return NULL;
    }
    sprite->extimages = SG_FALSE;
    return sprite;
}
SGSprite* SG_EXPORT sgSpriteCreateFile(const char* fname)
{
    return sgSpriteCreateFile2f(fname, SG_NAN, SG_NAN);
}
void SG_EXPORT sgSpriteDestroy(SGSprite* sprite)
{
    if(sprite == NULL)
        return;

    SGuint i;
    if(!sprite->extimages)
    {
        for(i = 0; i < sprite->numimages; i++)
            sgTextureDestroy(sprite->subimages[i]);
    }
    free(sprite->subimages);
    free(sprite);
}

SGbool SG_EXPORT sgSpriteAddFrameFile(SGSprite* sprite, const char* fname)
{
    sprite->numimages++;
    sprite->subimages = realloc(sprite->subimages, sprite->numimages * sizeof(SGTexture*));
    sprite->subimages[sprite->numimages - 1] = sgTextureCreateFile(fname);
    if(!sprite->subimages[sprite->numimages - 1])
    {
        sprite->numimages--; // failed, reset the number of images
        return SG_FALSE;
    }
    return SG_TRUE;
}

void SG_EXPORT sgSpriteSetImage(SGSprite* sprite, float image)
{
    sprite->image = image;
}
float SG_EXPORT sgSpriteGetImage(SGSprite* sprite)
{
    return sprite->image;
}
void SG_EXPORT sgSpriteSetSpeed(SGSprite* sprite, float speed)
{
    sprite->speed = speed;
}
float SG_EXPORT sgSpriteGetSpeed(SGSprite* sprite)
{
    return sprite->speed;
}

void SG_EXPORT sgSpriteDrawRads3f2f1f(SGSprite* sprite, float x, float y, float z, float xscale, float yscale, float angle)
{
    if(sprite == NULL)
        return;

    _sgSpriteUpdateTick(sprite);

    sgTextureDrawRads3f2f2f1f(sprite->subimages[(SGuint)sprite->image], x, y, z, xscale, yscale, sprite->xoffset, sprite->yoffset, angle);
}
void SG_EXPORT sgSpriteDrawRads2f2f1f(SGSprite* sprite, float x, float y, float xscale, float yscale, float angle)
{
    sgSpriteDrawRads3f2f1f(sprite, x, y, 0.0, xscale, yscale, angle);
}
void SG_EXPORT sgSpriteDrawRads3f1f(SGSprite* sprite, float x, float y, float z, float angle)
{
    sgSpriteDrawRads3f2f1f(sprite, x, y, z, 1.0, 1.0, angle);
}
void SG_EXPORT sgSpriteDrawRads2f1f(SGSprite* sprite, float x, float y, float angle)
{
    sgSpriteDrawRads3f2f1f(sprite, x, y, 0.0, 1.0, 1.0, angle);
}

void SG_EXPORT sgSpriteDrawDegs3f2f1f(SGSprite* sprite, float x, float y, float z, float xscale, float yscale, float angle)
{
    sgSpriteDrawRads3f2f1f(sprite, x, y, z, xscale, yscale, angle * SG_PI / 180.0);
}
void SG_EXPORT sgSpriteDrawDegs2f2f1f(SGSprite* sprite, float x, float y, float xscale, float yscale, float angle)
{
    sgSpriteDrawRads3f2f1f(sprite, x, y, 0.0, xscale, yscale, angle * SG_PI / 180.0);
}
void SG_EXPORT sgSpriteDrawDegs3f1f(SGSprite* sprite, float x, float y, float z, float angle)
{
    sgSpriteDrawRads3f2f1f(sprite, x, y, z, 1.0, 1.0, angle * SG_PI / 180.0);
}
void SG_EXPORT sgSpriteDrawDegs2f1f(SGSprite* sprite, float x, float y, float angle)
{
    sgSpriteDrawRads3f2f1f(sprite, x, y, 0.0, 1.0, 1.0, angle * SG_PI / 180.0);
}

void SG_EXPORT sgSpriteDraw3f2f(SGSprite* sprite, float x, float y, float z, float xscale, float yscale)
{
    sgSpriteDrawRads3f2f1f(sprite, x, y, z, xscale, yscale, 0.0);
}
void SG_EXPORT sgSpriteDraw2f2f(SGSprite* sprite, float x, float y, float xscale, float yscale)
{
    sgSpriteDrawRads3f2f1f(sprite, x, y, 0.0, xscale, yscale, 0.0);
}
void SG_EXPORT sgSpriteDraw3f(SGSprite* sprite, float x, float y, float z)
{
    sgSpriteDrawRads3f2f1f(sprite, x, y, z, 1.0, 1.0, 0.0);
}
void SG_EXPORT sgSpriteDraw2f(SGSprite* sprite, float x, float y)
{
    sgSpriteDrawRads3f2f1f(sprite, x, y, 0.0, 1.0, 1.0, 0.0);
}

void SG_EXPORT sgSpriteGetSize(SGSprite* sprite, SGuint* width, SGuint* height)
{
    if(sprite == NULL)
        return;

    sgTextureGetSize(sprite->subimages[0], width, height);
}
SGuint SG_EXPORT sgSpriteGetWidth(SGSprite* sprite)
{
    if(sprite == NULL)
        return 0;

    return sgTextureGetWidth(sprite->subimages[0]);
}
SGuint SG_EXPORT sgSpriteGetHeight(SGSprite* sprite)
{
    if(sprite == NULL)
        return 0;

    return sgTextureGetHeight(sprite->subimages[0]);
}
