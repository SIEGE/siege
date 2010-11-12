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

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

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

    TextureData* tdata = (TextureData*)texture;
    glBindTexture(GL_TEXTURE_2D, tdata->texid);
    tdata->width = width;
    tdata->height = height;
    tdata->awidth = higherPower(width);
    tdata->aheight = higherPower(height);
    tdata->wratio = tdata->width / (float)tdata->awidth;
    tdata->hratio = tdata->height / (float)tdata->aheight;
    tdata->bpp = bpp;

    GLuint glformat;
    SGubyte bypp;
    switch(bpp)
    {
        case 8:
            tdata->glbpp = GL_R3_G3_B2;
            glformat = GL_RGB;
            bypp = 1;
            break;
        case 15:
            tdata->glbpp = GL_RGB5_A1;
            glformat = GL_RGBA;
            bypp = 2;
            break;
        case 16:
            tdata->glbpp = GL_RGB16;
            glformat = GL_RGB;
            bypp = 2;
            break;
        case 24:
            tdata->glbpp = GL_RGB;
            glformat = GL_RGB;
            bypp = 3;
            break;
        case 32:
            tdata->glbpp = GL_RGBA;
            glformat = GL_RGBA;
            bypp = 4;
            break;
        default:
            return SG_INVALID_VALUE;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, tdata->glbpp, tdata->awidth, tdata->aheight, 0, glformat, GL_UNSIGNED_BYTE, data);

    return SG_OK;
}
//SGuint SG_EXPORT sgmGraphicsTextureGetData(void* texture, SGuint* width, SGuint* height, SGubyte* bpp, void** data)
//SGuint SG_EXPORT sgmGraphicsTextureFreeData(void* data)
SGuint SG_EXPORT sgmGraphicsTextureGetSize(void* texture, SGuint* width, SGuint* height)
{
    if(texture == NULL)
        return SG_OK; // SG_INVALID_VALUE

    TextureData* tdata = (TextureData*)texture;
    *width = tdata->width;
    *height = tdata->height;
    return SG_OK;
}

// TODO: make this work
SGuint SG_EXPORT sgmGraphicsTextureDraw(void* texture, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    if(texture == NULL)
        return SG_OK; // SG_INVALID_VALUE

    TextureData* tdata = (TextureData*)texture;

    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glRotatef(angle * 180.0 / M_PI, 0.0, 0.0, 1.0);
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
