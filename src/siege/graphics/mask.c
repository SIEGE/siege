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

#define SG_BUILD_LIBRARY
#include <siege/graphics/mask.h>
#include <siege/modules/graphics.h>
// for DrawDBG
#include <siege/graphics/draw.h>

#include <stdlib.h>
#include <math.h>

SGMask* SG_EXPORT sgMaskCreateSprite(SGSprite* sprite)
{
	return sgMaskCreateTexture2i(sprite->subimages[0], sprite->xoffset, sprite->yoffset);
}
SGMask* SG_EXPORT sgMaskCreateTexture2i(SGTexture* texture, SGint xoffset, SGint yoffset)
{
	SGMask* mask = malloc(sizeof(SGMask));
	if(mask == NULL)
		return NULL;

	SGuint i, j;

	mask->width = sgTextureGetWidth(texture);
	mask->height = sgTextureGetHeight(texture);

	mask->xoffset = xoffset;
	mask->yoffset = yoffset;

	mask->precise = SG_TRUE;

	mask->field = malloc(mask->width * sizeof(SGbool*));
	for(i = 0; i < mask->width; i++)
		mask->field[i] = calloc(mask->height, sizeof(SGbool));

	for(i = 0; i < mask->width; i++)
	{
		for(j = 0; j < mask->height; j++)
		{
			/// \todo Get texture data here
		}
	}

	return mask;
}
SGMask* SG_EXPORT sgMaskCreateTexture(SGTexture* texture)
{
	SGMask* mask = sgMaskCreateTexture2i(texture, 0, 0);
	if(mask == NULL)
		return NULL;
	mask->xoffset = mask->width / 2;
	mask->yoffset = mask->height / 2;
	return mask;
}
SGMask* SG_EXPORT sgMaskCreateFile2i(const char* fname, SGint xoffset, SGint yoffset)
{
	SGTexture* texture = sgTextureCreateFile(fname);
	if(texture == NULL)
		return NULL;

	SGMask* mask = sgMaskCreateTexture2i(texture, xoffset, yoffset);
	sgTextureDestroy(texture);

	return mask;
}
SGMask* SG_EXPORT sgMaskCreateFile(const char* fname)
{
	SGMask* mask = sgMaskCreateFile2i(fname, 0, 0);
	if(mask == NULL)
		return NULL;
	mask->xoffset = mask->width / 2;
	mask->yoffset = mask->height / 2;
	return mask;
}
void SG_EXPORT sgMaskDestroy(SGMask* mask)
{
	if(mask == NULL)
		return;

	SGuint i;
	for(i = 0; i < mask->width; i++)
		free(mask->field[i]);
	free(mask->field);
	free(mask);
}

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
SGbool SG_EXPORT sgMaskCheckCollision(SGMask* m1, SGint x1, SGint y1, SGMask* m2, SGint x2, SGint y2)
{
	ptrdiff_t i, j;
	/// \todo TODO
	return SG_FALSE;
}

void SG_EXPORT sgMaskGetSize(SGMask* mask, SGuint* width, SGuint* height)
{
	if(mask == NULL)
		return;

	if(width != NULL)
		*width = mask->width;
	if(height != NULL)
		*height = mask->height;
}
SGuint SG_EXPORT sgMaskGetWidth(SGMask* mask)
{
	if(mask == NULL)
		return 0;
	return mask->width;
}
SGuint SG_EXPORT sgMaskGetHeight(SGMask* mask)
{
	if(mask == NULL)
		return 0;
	return mask->height;
}

void SG_EXPORT sgMaskDrawDBG(SGMask* mask, float x, float y)
{
	if(mask == NULL)
		return;
	SGuint i, j;

	sgDrawBegin(SG_GRAPHICS_PRIMITIVE_POINTS);
		for(i = 0; i < mask->width; i++)
		{
			for(j = 0; j < mask->height; j++)
			{
				sgDrawColor1f(mask->field[i][j] ? 1.0f : 0.0f);
				sgDrawVertex2f(x, y);
			}
		}
	sgDrawEnd();
}
