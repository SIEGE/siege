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

#ifndef __SIEGE_GRAPHICS_MASK_H__
#define __SIEGE_GRAPHICS_MASK_H__

#include "../common.h"
// REMOVE if not animated
#include "../core/entity.h"
#include "sprite.h"
#include "texture.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/**
 * \todo Should this support animation (as in, have multiple frames/subimages)?
 * \todo Get this completed & working!
 */
typedef struct SGMask
{
    SGEntity* entity;		// REMOVE if not animated

    SGuint width;
    SGuint height;

    SGint xoffset;
    SGint yoffset;

    SGuint numimages;		// REMOVE if not animated
    SGbool*** subimages;	// CHANGE to SGbool** if not animated
    float image;			// REMOVE if not animated
    float speed;			// REMOVE if not animated
} SGMask;

void SG_EXPORT _sgMaskEvTick(SGEntity* client); // REMOVE if not animated

SGMask* SG_EXPORT sgMaskCreateSprite(SGSprite* sprite);
SGMask* SG_EXPORT sgMaskCreateTexture2i(SGTexture* texture, SGint xoffset, SGint yoffset);
SGMask* SG_EXPORT sgMaskCreateTexture(SGTexture* texture);
SGMask* SG_EXPORT sgMaskCreateFile2i(const char* fname, SGint xoffset, SGint yoffset);
SGMask* SG_EXPORT sgMaskCreateFile(const char* fname);
void SG_EXPORT sgMaskDestroy(SGMask* mask);

void SG_EXPORT sgMaskGetSize(SGMask* mask, SGuint* width, SGuint* height);
SGuint SG_EXPORT sgMaskGetWidth(SGMask* mask);
SGuint SG_EXPORT sgMaskGetHeight(SGMask* mask);

/**
 * \brief A function used for debugging the mask
 * \warning This draws the mask pixel-for-pixel and is <em>slow</em>!
 * \warning This function may be removed in the future!
 * \todo sgSpriteCreateMask(SGMask* mask)
 */
void SG_EXPORT sgMaskDrawDBG(SGMask* mask, float x, float y);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_MASK_H__
