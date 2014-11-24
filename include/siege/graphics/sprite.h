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

#ifndef __SIEGE_GRAPHICS_SPRITE_H__
#define __SIEGE_GRAPHICS_SPRITE_H__

#include "../common.h"
#include "texture.h"
#include "../util/ivector.h"
#include "../util/vector.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
typedef struct SGSprite
{
    SGulong tick;

    float xoffset;
    float yoffset;
    SGbool extimages;
    SGuint numimages;
    SGTexture** subimages;
    float image;
    float speed;
} SGSprite;

void SG_CALL _sgSpriteUpdateTick(SGSprite* sprite);

SGSprite* SG_CALL sgSpriteCreateTexture2f(SGTexture* texture, float xoffset, float yoffset);
SGSprite* SG_CALL sgSpriteCreateTexture(SGTexture* texture);
SGSprite* SG_CALL sgSpriteCreateFile2f(const char* fname, float xoffset, float yoffset);
SGSprite* SG_CALL sgSpriteCreateFile(const char* fname);
void SG_CALL sgSpriteDestroy(SGSprite* sprite);

SGbool SG_CALL sgSpriteAddFrameFile(SGSprite* sprite, const char* fname);

void SG_CALL sgSpriteSetImage(SGSprite* sprite, float image);
float SG_CALL sgSpriteGetImage(SGSprite* sprite);
void SG_CALL sgSpriteSetSpeed(SGSprite* sprite, float speed);
float SG_CALL sgSpriteGetSpeed(SGSprite* sprite);

void SG_CALL sgSpriteSetOffset(SGSprite* sprite, float x, float y);
void SG_CALL sgSpriteGetOffset(SGSprite* sprite, float* x, float* y);

void SG_CALL sgSpriteDrawRads3f2f1f(SGSprite* sprite, float x, float y, float z, float xscale, float yscale, float angle);
void SG_CALL sgSpriteDrawDegs3f2f1f(SGSprite* sprite, float x, float y, float z, float xscale, float yscale, float angle);
void SG_CALL sgSpriteDrawRads2f2f1f(SGSprite* sprite, float x, float y, float xscale, float yscale, float angle);
void SG_CALL sgSpriteDrawDegs2f2f1f(SGSprite* sprite, float x, float y, float xscale, float yscale, float angle);
void SG_CALL sgSpriteDrawRads3f1f(SGSprite* sprite, float x, float y, float z, float angle);
void SG_CALL sgSpriteDrawDegs3f1f(SGSprite* sprite, float x, float y, float z, float angle);
void SG_CALL sgSpriteDrawRads2f1f(SGSprite* sprite, float x, float y, float angle);
void SG_CALL sgSpriteDrawDegs2f1f(SGSprite* sprite, float x, float y, float angle);
void SG_CALL sgSpriteDraw3f2f(SGSprite* sprite, float x, float y, float z, float xscale, float yscale);
void SG_CALL sgSpriteDraw2f2f(SGSprite* sprite, float x, float y, float xscale, float yscale);
void SG_CALL sgSpriteDraw3f(SGSprite* sprite, float x, float y, float z);
void SG_CALL sgSpriteDraw2f(SGSprite* sprite, float x, float y);

SGIVec2 SG_CALL sgSpriteGetSize2iv(SGSprite* sprite);
SGVec2 SG_CALL sgSpriteGetSize2fv(SGSprite* sprite);
SGuint SG_CALL sgSpriteGetWidth(SGSprite* sprite);
SGuint SG_CALL sgSpriteGetHeight(SGSprite* sprite);

/* DEPRECATED */
void SG_CALL SG_HINT_DEPRECATED sgSpriteGetSize(SGSprite* sprite, SGuint* width, SGuint* height);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_SPRITE_H__
