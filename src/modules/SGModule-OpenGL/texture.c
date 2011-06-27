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

#include "main.h"
#include "texture.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

SGuint SG_EXPORT sgmGraphicsTextureCreate(void** texture, void* context)
{
    TextureData** tdata = (TextureData**)texture;
    *tdata = calloc(1, sizeof(TextureData));

    (*tdata)->context = context;

    glGenTextures(1, &(*tdata)->texid);
    glBindTexture(GL_TEXTURE_2D, (*tdata)->texid);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);*/

    return SG_OK;
}
//SGuint SG_EXPORT sgmGraphicsTextureCreateData(void** texture, void* context, SGuint width, SGuint height, SGuint bpp, void* data)
SGuint SG_EXPORT sgmGraphicsTextureDestroy(void* texture)
{
    if(texture == NULL)
        return SG_OK; // SG_INVALID_VALUE

    TextureData* tdata = (TextureData*)texture;
    glDeleteTextures(1, &tdata->texid);
    free(tdata);

    return SG_OK;
}
SGuint SG_EXPORT sgmGraphicsTextureSetData(void* texture, SGuint width, SGuint height, SGuint bpp, void* data)
{
    if(texture == NULL)
        return SG_OK; // SG_INVALID_VALUE

    TextureData* tdata = texture;
    glBindTexture(GL_TEXTURE_2D, tdata->texid);
    tdata->width = width;
    tdata->height = height;
    tdata->awidth = higherPower(width);
    tdata->aheight = higherPower(height);
    tdata->wratio = tdata->width / (float)tdata->awidth;
    tdata->hratio = tdata->height / (float)tdata->aheight;
    tdata->bpp = bpp;

    SGubyte bypp;
    switch(bpp)
    {
        case 8:
			tdata->gliformat = GL_R3_G3_B2;
			tdata->glformat = GL_RGB;
			tdata->gltype = GL_UNSIGNED_BYTE_3_3_2;
			bypp = 1;
            break;
        case 15:
			tdata->gliformat = GL_RGB5; // GL_RGB5_A1
			tdata->glformat = GL_RGB;
			tdata->gltype = GL_UNSIGNED_SHORT_5_5_5_1;
            bypp = 2;
            break;
        case 16:
            tdata->gliformat = GL_RGB5;
            tdata->glformat = GL_RGB;
			tdata->gltype = GL_UNSIGNED_SHORT_5_6_5;
            bypp = 2;
            break;
        case 24:
            tdata->gliformat = GL_RGB8;
            tdata->glformat = GL_RGB;
			tdata->gltype = GL_UNSIGNED_BYTE;
            bypp = 3;
            break;
        case 32:
            tdata->gliformat = GL_RGBA8;
            tdata->glformat = GL_RGBA;
			tdata->gltype = GL_UNSIGNED_BYTE;
            bypp = 4;
            break;
        default:
            return SG_INVALID_VALUE;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, tdata->gliformat, tdata->awidth, tdata->aheight, 0, tdata->glformat, tdata->gltype, NULL);

    if(data != NULL)
    {
        size_t i;
        for(i = 0; i < tdata->height; i++)
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, tdata->height - i - 1, tdata->width, 1, tdata->glformat, tdata->gltype, ((char*)data) + (i * tdata->width) * bypp);
    }

    return SG_OK;
}
SGuint SG_EXPORT sgmGraphicsTextureGetData(void* texture, SGuint* width, SGuint* height, SGuint* bpp, void** data)
{
	if(texture == NULL)
		return SG_OK; // SG_INVALID_VALUE
	TextureData* tdata = texture;

	glBindTexture(GL_TEXTURE_2D, tdata->texid);

	*width = tdata->awidth;
	*height = tdata->aheight;
	*bpp = tdata->bpp;

	*data = malloc(tdata->awidth * tdata->aheight * (tdata->bpp == 15 ? 2 : (tdata->bpp / 8)));
	glGetTexImage(GL_TEXTURE_2D, 0, tdata->glformat, tdata->gltype, *data);

	return SG_OK;
}
SGuint SG_EXPORT sgmGraphicsTextureFreeData(void* data)
{
	free(data);

	return SG_OK;
}
SGuint SG_EXPORT sgmGraphicsTextureGetSize(void* texture, SGuint* width, SGuint* height)
{
    if(texture == NULL)
        return SG_OK; // SG_INVALID_VALUE

    TextureData* tdata = (TextureData*)texture;
    *width = tdata->width;
    *height = tdata->height;
    return SG_OK;
}

SGuint SG_EXPORT sgmGraphicsTextureDraw(void* texture, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    if(texture == NULL)
        return SG_OK; // SG_INVALID_VALUE
    TextureData* tdata = texture;

    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glRotatef(angle * 180.0 / SG_PI, 0.0, 0.0, 1.0);
    glScalef(xscale, yscale, 1.0);
    glTranslatef(-x - xoffset, -y - yoffset, 0.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tdata->texid);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, tdata->hratio/*1*/);
        glVertex3f(x, y, z);

        glTexCoord2f(tdata->wratio/*1*/, tdata->hratio/*1*/);
        glVertex3f(x + tdata->width, y, z);

        glTexCoord2f(tdata->wratio/*1*/, 0.0);
        glVertex3f(x + tdata->width, y + tdata->height, z);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(x, y + tdata->height, z);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    return SG_OK;
}

SGenum SG_EXPORT sgmGraphicsTextureSetWrap(void* texture, SGenum swrap, SGenum twrap)
{
    if(texture == NULL)
        return SG_OK; // SG_INVALID_VALUE
    TextureData* tdata = texture;

    glBindTexture(GL_TEXTURE_2D, tdata->texid);

    GLenum glwrap = 0;
    switch(swrap)
    {
        case SG_GRAPHICS_WRAP_CURRENT:                                          break;
        case SG_GRAPHICS_WRAP_CLAMP:            glwrap = GL_CLAMP;              break;
        case SG_GRAPHICS_WRAP_CLAMP_TO_EDGE:    glwrap = GL_CLAMP_TO_EDGE;      break;
        case SG_GRAPHICS_WRAP_MIRRORED_REPEAT:  glwrap = GL_MIRRORED_REPEAT;    break;
        case SG_GRAPHICS_WRAP_REPEAT:           glwrap = GL_REPEAT;             break;
        default: swrap = SG_GRAPHICS_WRAP_CURRENT;
    }
    if(swrap != SG_GRAPHICS_WRAP_CURRENT)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glwrap);

    switch(twrap)
    {
        case SG_GRAPHICS_WRAP_CURRENT:                                          break;
        case SG_GRAPHICS_WRAP_CLAMP:            glwrap = GL_CLAMP;              break;
        case SG_GRAPHICS_WRAP_CLAMP_TO_EDGE:    glwrap = GL_CLAMP_TO_EDGE;      break;
        case SG_GRAPHICS_WRAP_MIRRORED_REPEAT:  glwrap = GL_MIRRORED_REPEAT;    break;
        case SG_GRAPHICS_WRAP_REPEAT:           glwrap = GL_REPEAT;             break;
        default: twrap = SG_GRAPHICS_WRAP_CURRENT;
    }
    if(twrap != SG_GRAPHICS_WRAP_CURRENT)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glwrap);

    //glBindTexture(GL_TEXTURE_2D, 0);

    return SG_OK;
}
