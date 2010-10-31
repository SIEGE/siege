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
 * \todo Get the pixel info from the texture [requires backend support].
 * \todo Add a bounding box.
 */
typedef struct SGMask
{
	SGEntity* entity;		// REMOVE if not animated

	SGuint width;
	SGuint height;

	SGint xoffset;
	SGint yoffset;

	SGbool precise;

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

/**
 * \brief Check the collision between two masks
 * \param m1 The first mask to test
 * \param x1 First mask's x position
 * \param y1 First mask's y position
 * \param m2 The second mask to test
 * \param x2 Second mask's x position
 * \param y2 Second mask's y position
 * \return SG_TRUE if the masks collide, SG_FALSE otherwise.
 *
 * \todo Get this working.
 * \todo Should the order of arguments be <em>m1,x1,y1,m2,x2,y2</em> or <em>m1,m2,x1,y1,x2,y2</em>?
 */
SGbool SG_EXPORT sgMaskCheckCollision(SGMask* m1, SGint x1, SGint y1, SGMask* m2, SGint x2, SGint y2);

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
