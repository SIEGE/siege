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

void SG_EXPORT _sgSpriteUpdateTick(SGSprite* sprite);

SGSprite* SG_EXPORT sgSpriteCreateTexture2f(SGTexture* texture, float xoffset, float yoffset);
SGSprite* SG_EXPORT sgSpriteCreateTexture(SGTexture* texture);
SGSprite* SG_EXPORT sgSpriteCreateFile2f(const char* fname, float xoffset, float yoffset);
SGSprite* SG_EXPORT sgSpriteCreateFile(const char* fname);
void SG_EXPORT sgSpriteDestroy(SGSprite* sprite);

SGbool SG_EXPORT sgSpriteAddFrameFile(SGSprite* sprite, const char* fname);

void SG_EXPORT sgSpriteSetImage(SGSprite* sprite, float image);
float SG_EXPORT sgSpriteGetImage(SGSprite* sprite);
void SG_EXPORT sgSpriteSetSpeed(SGSprite* sprite, float speed);
float SG_EXPORT sgSpriteGetSpeed(SGSprite* sprite);

void SG_EXPORT sgSpriteDrawRads3f2f1f(SGSprite* sprite, float x, float y, float z, float xscale, float yscale, float angle);
void SG_EXPORT sgSpriteDrawDegs3f2f1f(SGSprite* sprite, float x, float y, float z, float xscale, float yscale, float angle);
void SG_EXPORT sgSpriteDrawRads2f2f1f(SGSprite* sprite, float x, float y, float xscale, float yscale, float angle);
void SG_EXPORT sgSpriteDrawDegs2f2f1f(SGSprite* sprite, float x, float y, float xscale, float yscale, float angle);
void SG_EXPORT sgSpriteDrawRads3f1f(SGSprite* sprite, float x, float y, float z, float angle);
void SG_EXPORT sgSpriteDrawDegs3f1f(SGSprite* sprite, float x, float y, float z, float angle);
void SG_EXPORT sgSpriteDrawRads2f1f(SGSprite* sprite, float x, float y, float angle);
void SG_EXPORT sgSpriteDrawDegs2f1f(SGSprite* sprite, float x, float y, float angle);
void SG_EXPORT sgSpriteDraw3f2f(SGSprite* sprite, float x, float y, float z, float xscale, float yscale);
void SG_EXPORT sgSpriteDraw2f2f(SGSprite* sprite, float x, float y, float xscale, float yscale);
void SG_EXPORT sgSpriteDraw3f(SGSprite* sprite, float x, float y, float z);
void SG_EXPORT sgSpriteDraw2f(SGSprite* sprite, float x, float y);

void SG_EXPORT sgSpriteGetSize(SGSprite* sprite, SGuint* width, SGuint* height);
SGuint SG_EXPORT sgSpriteGetWidth(SGSprite* sprite);
SGuint SG_EXPORT sgSpriteGetHeight(SGSprite* sprite);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_SPRITE_H__
