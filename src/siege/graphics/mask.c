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
// for DrawDBG
#include <siege/graphics/draw.h>

#include <stdlib.h>
#include <math.h>

void SG_EXPORT _sgMaskEvTick(SGEntity* client)
{
    SGMask* mask = client->data;
    mask->image += mask->speed;

	while((SGuint)mask->image >= mask->numimages)
		mask->image -= mask->numimages;
}

SGMask* SG_EXPORT sgMaskCreateSprite(SGSprite* sprite)
{
	/// \todo Use all subimages (REMOVE if not animated)
	return sgMaskCreateTexture2i(sprite->subimages[0], sprite->xoffset, sprite->yoffset);
}
SGMask* SG_EXPORT sgMaskCreateTexture2i(SGTexture* texture, SGint xoffset, SGint yoffset)
{
    SGMask* mask = malloc(sizeof(SGMask));
    if(mask == NULL)
        return NULL;

	SGuint i;

    mask->entity = sgEntityCreate(0.0, SG_EVT_CORE);
    mask->entity->data = mask;
    mask->entity->evTick = _sgMaskEvTick;

	mask->width = sgTextureGetWidth(texture);
	mask->height = sgTextureGetHeight(texture);

    mask->numimages = 1;
    mask->subimages = malloc(sizeof(SGbool**));
	mask->subimages[0] = malloc(mask->width * sizeof(SGbool*));
	for(i = 0; i < mask->width; i++)
		mask->subimages[0][i] = calloc(mask->height, sizeof(SGbool));

    mask->xoffset = xoffset;
    mask->yoffset = yoffset;

    mask->image = 0.0;
    mask->speed = 1.0;

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
    if(mask == NULL)
    {
        sgTextureDestroy(texture);
        return NULL;
    }
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

	sgEntityDestroy(mask->entity);

    SGuint i, j;
    for(i = 0; i < mask->numimages; i++)
	{
		for(j = 0; j < mask->width; j++)
			free(mask->subimages[i][j]);
		free(mask->subimages[i]);
	}
	free(mask->subimages);
    free(mask);
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
				sgDrawColor1f(mask->subimages[(SGuint)mask->image][i][j] ? 1.0 : 0.0);
				sgDrawVertex2f(x, y);
			}
		}
	sgDrawEnd();
}
