/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "COPYING.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#include "common.h"
#include "texture.h"

#include <stdlib.h>

SGenum SG_CALL sgmGraphicsTextureCreate(void** texture, void* context)
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
//SGenum SG_CALL sgmGraphicsTextureCreateData(void** texture, void* context, SGuint width, SGuint height, SGuint bpp, void* data)
SGenum SG_CALL sgmGraphicsTextureDestroy(void* texture)
{
    if(texture == NULL)
        return SG_OK; // SG_INVALID_VALUE

    TextureData* tdata = (TextureData*)texture;
    glDeleteTextures(1, &tdata->texid);
    free(tdata);

    return SG_OK;
}
SGenum SG_CALL sgmGraphicsTextureSetData(void* texture, SGuint width, SGuint height, SGuint bpp, void* data)
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

    /*if(data)
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, tdata->width, tdata->height, tdata->glformat, tdata->gltype, data);*/

    size_t i;
    if(data)
        for(i = 0; i < tdata->height; i++)
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, tdata->height - i - 1, tdata->width, 1, tdata->glformat, tdata->gltype, ((char*)data) + (i * tdata->width) * bypp);

    return SG_OK;
}
SGenum SG_CALL sgmGraphicsTextureSetSubData(void* texture, SGuint x, SGuint y, SGuint width, SGuint height, SGenum bpp, void* data)
{
    if(texture == NULL)
        return SG_OK; // SG_INVALID_VALUE

    TextureData* tdata = texture;
    glBindTexture(GL_TEXTURE_2D, tdata->texid);

    GLuint glformat;
    GLuint gltype;
    SGubyte bypp;
    switch(bpp)
    {
        case 8:
            glformat = GL_RGB;
            gltype = GL_UNSIGNED_BYTE_3_3_2;
            bypp = 1;
            break;
        case 15:
            glformat = GL_RGB;
            gltype = GL_UNSIGNED_SHORT_5_5_5_1;
            bypp = 2;
            break;
        case 16:
            glformat = GL_RGB;
            gltype = GL_UNSIGNED_SHORT_5_6_5;
            bypp = 2;
            break;
        case 24:
            glformat = GL_RGB;
            gltype = GL_UNSIGNED_BYTE;
            bypp = 3;
            break;
        case 32:
            glformat = GL_RGBA;
            gltype = GL_UNSIGNED_BYTE;
            bypp = 4;
            break;
        default:
            return SG_INVALID_VALUE;
    }

    size_t i;
    if(data)
        for(i = 0; i < height; i++)
            glTexSubImage2D(GL_TEXTURE_2D, 0, x, tdata->height - y - i - 1, width, 1, glformat, gltype, ((char*)data) + (i * width) * bypp);

    return SG_OK;
}
SGenum SG_CALL sgmGraphicsTextureGetData(void* texture, SGuint* width, SGuint* height, SGuint* bpp, void** data)
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
SGenum SG_CALL sgmGraphicsTextureFreeData(void* data)
{
    free(data);

    return SG_OK;
}
SGenum SG_CALL sgmGraphicsTextureGetSize(void* texture, SGuint* width, SGuint* height)
{
    if(texture == NULL)
        return SG_OK; // SG_INVALID_VALUE

    TextureData* tdata = (TextureData*)texture;
    *width = tdata->width;
    *height = tdata->height;
    return SG_OK;
}
SGenum SG_CALL sgmGraphicsTextureGetBPP(void* texture, SGenum* bpp)
{
    if(!texture)
        return SG_OK; // SG_INVALID_VALUE

    TextureData* tdata = (TextureData*)texture;
    *bpp = tdata->bpp;
    return SG_OK;
}

SGenum SG_CALL sgmGraphicsTextureDraw(void* texture, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    if(texture == NULL)
        return SG_OK; // SG_INVALID_VALUE
    TextureData* tdata = texture;

    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glRotatef(angle * 180.0 / SG_PI, 0.0, 0.0, 1.0);
    glScalef(xscale, yscale, 1.0);
    glTranslatef(-x - xoffset, -y - yoffset, 0.0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    float vertices[4*3] = {
            x               , y                , z,
            x + tdata->width, y                , z,
            x + tdata->width, y + tdata->height, z,
            x               , y + tdata->height, z
        };
    float texcoords[4*2] = {
            0.0               , tdata->hratio/*1*/,
            tdata->wratio/*1*/, tdata->hratio/*1*/,
            tdata->wratio/*1*/, 0.0               ,
            0.0               , 0.0
        };

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tdata->texid);

    glDrawArrays(GL_QUADS, 0, 4);

    glDisable(GL_TEXTURE_2D);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();

    return SG_OK;
}

SGenum SG_CALL sgmGraphicsTextureSetWrap(void* texture, SGenum swrap, SGenum twrap)
{
    if(texture == NULL)
        return SG_OK; // SG_INVALID_VALUE
    TextureData* tdata = texture;

    glBindTexture(GL_TEXTURE_2D, tdata->texid);

    GLenum glwrap = 0;
    switch(swrap)
    {
        case SG_WRAP_CURRENT:                                          break;
        case SG_WRAP_CLAMP:            glwrap = GL_CLAMP;              break;
        case SG_WRAP_CLAMP_TO_EDGE:    glwrap = GL_CLAMP_TO_EDGE;      break;
        case SG_WRAP_MIRRORED_REPEAT:  glwrap = GL_MIRRORED_REPEAT;    break;
        case SG_WRAP_REPEAT:           glwrap = GL_REPEAT;             break;
        default: swrap = SG_WRAP_CURRENT;
    }
    if(swrap != SG_WRAP_CURRENT)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glwrap);

    switch(twrap)
    {
        case SG_WRAP_CURRENT:                                          break;
        case SG_WRAP_CLAMP:            glwrap = GL_CLAMP;              break;
        case SG_WRAP_CLAMP_TO_EDGE:    glwrap = GL_CLAMP_TO_EDGE;      break;
        case SG_WRAP_MIRRORED_REPEAT:  glwrap = GL_MIRRORED_REPEAT;    break;
        case SG_WRAP_REPEAT:           glwrap = GL_REPEAT;             break;
        default: twrap = SG_WRAP_CURRENT;
    }
    if(twrap != SG_WRAP_CURRENT)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glwrap);

    //glBindTexture(GL_TEXTURE_2D, 0);

    return SG_OK;
}

SGenum SG_CALL sgmGraphicsTextureSetInterpolation(void* texture, SGenum interp)
{
    if(texture == NULL)
        return SG_OK; // SG_INVALID_VALUE
    TextureData* tdata = texture;

    glBindTexture(GL_TEXTURE_2D, tdata->texid);

    GLenum glinterp = 0;
    switch(interp)
    {
        case SG_INTERP_CURRENT:                        break;
        case SG_INTERP_NEAREST: glinterp = GL_NEAREST; break;
        case SG_INTERP_LINEAR:  glinterp = GL_LINEAR;  break;
        default: interp = SG_INTERP_CURRENT;
    }
    if(interp != SG_INTERP_CURRENT)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glinterp);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glinterp);
    }

    //glBindTexture(GL_TEXTURE_2D, 0);

    return SG_OK;
}
