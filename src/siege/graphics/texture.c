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
#include <siege/graphics/texture.h>
#include <siege/core/window.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../internal/gl.h"

static SGubyte texinfoGL(GLuint* gliformat, GLuint* glformat, GLuint* gltype, SGenum bpp)
{
    GLuint tmp;
    if(!gliformat)  gliformat = &tmp;
    if(!glformat)   glformat = &tmp;
    if(!gltype)     gltype = &tmp;
    switch(bpp)
    {
        case 8:
            *gliformat = GL_R3_G3_B2;
            *glformat = GL_RGB;
            *gltype = GL_UNSIGNED_BYTE_3_3_2;
            return 1;
        case 15:
            *gliformat = GL_RGB5; // GL_RGB5_A1
            *glformat = GL_RGB;
            *gltype = GL_UNSIGNED_SHORT_5_5_5_1;
            return 2;
        case 16:
            *gliformat = GL_RGB5;
            *glformat = GL_RGB;
            *gltype = GL_UNSIGNED_SHORT_5_6_5;
            return 2;
        case 24:
            *gliformat = GL_RGB8;
            *glformat = GL_RGB;
            *gltype = GL_UNSIGNED_BYTE;
            return 3;
        case 32:
            *gliformat = GL_RGBA8;
            *glformat = GL_RGBA;
            *gltype = GL_UNSIGNED_BYTE;
            return 4;
        default:
            SG_ASSERT(0, "Invalid BPP passed to texture");
            *gliformat = 0;
            *glformat = 0;
            *gltype = 0;
            return 0;
    }
}
static GLenum wrapSGtoGL(SGenum wrap)
{
    // Note: depends on GL_* not being 0
    switch(wrap)
    {
        case SG_WRAP_CLAMP:             return GL_CLAMP;
        case SG_WRAP_CLAMP_TO_EDGE:     return GL_CLAMP_TO_EDGE;
        case SG_WRAP_MIRRORED_REPEAT:   return GL_MIRRORED_REPEAT;
        case SG_WRAP_REPEAT:            return GL_REPEAT;
        case SG_WRAP_CURRENT:
        default:
            return 0;
    }
}
static GLenum interpSGtoGL(SGenum interp)
{
    // Note: depends on GL_* not being 0
    switch(interp)
    {
        case SG_INTERP_NEAREST: return GL_NEAREST;
        case SG_INTERP_LINEAR:  return GL_LINEAR;
        case SG_INTERP_CURRENT:
        default:
            return 0;
    }
}

SGTexture* SG_CALL sgTextureCreateBitmap(SGBitmap* bmp, SGbool delbmp)
{
    size_t width;
    size_t height;
    SGenum bpp;
    void* data;

    sgBitmapGetData(bmp, &width, &height, &bpp, &data);

    SGTexture* texture = sgTextureCreateData(width, height, bpp, data);
    if(delbmp)
        sgBitmapDestroy(bmp);
    return texture;
}
SGTexture* SG_CALL sgTextureCreateStream(SGStream* stream, SGbool delstream)
{
    SGBitmap* bmp = sgBitmapCreateStream(stream, delstream);
    if(!bmp) return NULL;
    return sgTextureCreateBitmap(bmp, SG_TRUE);
}
SGTexture* SG_CALL sgTextureCreateFile(const char* fname)
{
    SGStream* stream = sgStreamCreateFile(fname, "r");
    if(!stream)
    {
        fprintf(stderr, "Could not load image %s\n", fname);
        return NULL;
    }
    return sgTextureCreateStream(stream, SG_TRUE);
}
SGTexture* SG_CALL sgTextureCreateData(SGuint width, SGuint height, SGenum bpp, void* data)
{
    SGTexture* texture = malloc(sizeof(SGTexture));
    if(!texture) return NULL;

    texture->handle = malloc(sizeof(GLuint));

    glGenTextures(1, texture->handle);
    glBindTexture(GL_TEXTURE_2D, GLTEX(texture));

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    sgTextureSetData(texture, width, height, bpp, data);

    return texture;
}
SGTexture* SG_CALL sgTextureCreate(SGuint width, SGuint height, SGenum bpp)
{
    return sgTextureCreateData(width, height, bpp, NULL);
}
void SG_CALL sgTextureDestroy(SGTexture* texture)
{
    if(!texture) return;

    glDeleteTextures(1, texture->handle);
    free(texture->handle);
    free(texture);
}

void SG_CALL sgTextureSetData(SGTexture* texture, size_t width, size_t height, SGenum bpp, void* data)
{
    texture->width = width;
    texture->height = height;
    texture->bpp = bpp;

    glBindTexture(GL_TEXTURE_2D, GLTEX(texture));

    GLuint gliformat, glformat, gltype;
    SGubyte bypp = texinfoGL(&gliformat, &glformat, &gltype, bpp);

    glTexImage2D(GL_TEXTURE_2D, 0, gliformat, width, height, 0, glformat, gltype, NULL);

    /*if(data)
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, glformat, gltype, data);*/

    size_t i;
    if(data)
        for(i = 0; i < height; i++)
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, texture->height - i - 1, width, 1, glformat, gltype, ((char*)data) + (i * width) * bypp);
}
void SG_CALL sgTextureSetSubData(SGTexture* texture, size_t x, size_t y, size_t width, size_t height, SGenum bpp, void* data)
{
    glBindTexture(GL_TEXTURE_2D, GLTEX(texture));

    GLuint glformat, gltype;
    SGubyte bypp = texinfoGL(NULL, &glformat, &gltype, bpp);

    size_t i;
    if(data)
        for(i = 0; i < height; i++)
            glTexSubImage2D(GL_TEXTURE_2D, 0, x, texture->height - y - i - 1, width, 1, glformat, gltype, ((char*)data) + (i * width) * bypp);
}
void* SG_CALL sgTextureGetData(SGTexture* texture)
{
    GLuint glformat, gltype;
    GLubyte bypp = texinfoGL(NULL, &glformat, &gltype, texture->bpp);
    void* data = malloc(texture->width * texture->height * bypp);

    glBindTexture(GL_TEXTURE_2D, GLTEX(texture));
    glGetTexImage(GL_TEXTURE_2D, 0, glformat, gltype, data);

    return data;
}
void SG_CALL sgTextureFreeData(void* data)
{
    if(data)
        free(data);
}

void SG_CALL sgTextureDrawRads3f2f2f1f(SGTexture* texture, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glRotatef(angle * 180.0 / SG_PI, 0.0, 0.0, 1.0);
    glScalef(xscale, yscale, 1.0);
    glTranslatef(-x - xoffset, -y - yoffset, 0.0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    float vertices[4*3] = {
            x                 , y                  , z,
            x + texture->width, y                  , z,
            x + texture->width, y + texture->height, z,
            x                 , y + texture->height, z
        };
    float texcoords[4*2] = {
            0.0, 1.0,
            1.0, 1.0,
            1.0, 0.0,
            0.0, 0.0
        };

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, GLTEX(texture));

    glDrawArrays(GL_QUADS, 0, 4);

    glDisable(GL_TEXTURE_2D);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
}
void SG_CALL sgTextureDrawDegs3f2f2f1f(SGTexture* texture, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    sgTextureDrawRads3f2f2f1f(texture, x, y, z, xscale, yscale, xoffset, yoffset, angle * SG_PI / 180.0);
}
void SG_CALL sgTextureDrawRads2f2f2f1f(SGTexture* texture, float x, float y, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    sgTextureDrawRads3f2f2f1f(texture, x, y, 0.0, xscale, yscale, xoffset, yoffset, angle);
}
void SG_CALL sgTextureDrawDegs2f2f2f1f(SGTexture* texture, float x, float y, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    sgTextureDrawDegs3f2f2f1f(texture, x, y, 0.0, xscale, yscale, xoffset, yoffset, angle);
}
void SG_CALL sgTextureDrawRads3f2f1f(SGTexture* texture, float x, float y, float z, float xscale, float yscale, float angle)
{
    sgTextureDrawRads3f2f2f1f(texture, x, y, z, xscale, yscale, 0.0, 0.0, angle);
}
void SG_CALL sgTextureDrawDegs3f2f1f(SGTexture* texture, float x, float y, float z, float xscale, float yscale, float angle)
{
    sgTextureDrawDegs3f2f2f1f(texture, x, y, z, xscale, yscale, 0.0, 0.0, angle);
}
void SG_CALL sgTextureDrawRads2f2f1f(SGTexture* texture, float x, float y, float xscale, float yscale, float angle)
{
    sgTextureDrawRads3f2f2f1f(texture, x, y, 0.0, xscale, yscale, 0.0, 0.0, angle);
}
void SG_CALL sgTextureDrawDegs2f2f1f(SGTexture* texture, float x, float y, float xscale, float yscale, float angle)
{
    sgTextureDrawDegs3f2f2f1f(texture, x, y, 0.0, xscale, yscale, 0.0, 0.0, angle);
}
void SG_CALL sgTextureDrawRads3f1f(SGTexture* texture, float x, float y, float z, float angle)
{
    sgTextureDrawRads3f2f2f1f(texture, x, y, z, 1.0, 1.0, 0.0, 0.0, angle);
}
void SG_CALL sgTextureDrawDegs3f1f(SGTexture* texture, float x, float y, float z, float angle)
{
    sgTextureDrawDegs3f2f2f1f(texture, x, y, z, 1.0, 1.0, 0.0, 0.0, angle);
}
void SG_CALL sgTextureDrawRads2f1f(SGTexture* texture, float x, float y, float angle)
{
    sgTextureDrawRads3f2f2f1f(texture, x, y, 0.0, 1.0, 1.0, 0.0, 0.0, angle);
}
void SG_CALL sgTextureDrawDegs2f1f(SGTexture* texture, float x, float y, float angle)
{
    sgTextureDrawDegs3f2f2f1f(texture, x, y, 0.0, 1.0, 1.0, 0.0, 0.0, angle);
}
void SG_CALL sgTextureDraw3f2f2f(SGTexture* texture, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset)
{
    sgTextureDrawRads3f2f2f1f(texture, x, y, z, xscale, yscale, xoffset, yoffset, 0.0);
}
void SG_CALL sgTextureDraw2f2f2f(SGTexture* texture, float x, float y, float xscale, float yscale, float xoffset, float yoffset)
{
    sgTextureDrawRads3f2f2f1f(texture, x, y, 0.0, xscale, yscale, xoffset, yoffset, 0.0);
}
void SG_CALL sgTextureDraw3f2f(SGTexture* texture, float x, float y, float z, float xscale, float yscale)
{
    sgTextureDrawRads3f2f2f1f(texture, x, y, z, xscale, yscale, 0.0, 0.0, 0.0);
}
void SG_CALL sgTextureDraw2f2f(SGTexture* texture, float x, float y, float xscale, float yscale)
{
    sgTextureDrawRads3f2f2f1f(texture, x, y, 0.0, xscale, yscale, 0.0, 0.0, 0.0);
}
void SG_CALL sgTextureDraw3f(SGTexture* texture, float x, float y, float z)
{
    sgTextureDrawRads3f2f2f1f(texture, x, y, z, 1.0, 1.0, 0.0, 0.0, 0.0);
}
void SG_CALL sgTextureDraw2f(SGTexture* texture, float x, float y)
{
    sgTextureDrawRads3f2f2f1f(texture, x, y, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0);
}
void SG_CALL sgTextureDraw(SGTexture* texture)
{
    sgTextureDrawRads3f2f2f1f(texture, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
}

void SG_CALL sgTextureSetWrap(SGTexture* texture, SGenum swrap, SGenum twrap)
{
    glBindTexture(GL_TEXTURE_2D, GLTEX(texture));

    GLenum glwrap;

    glwrap = wrapSGtoGL(swrap);
    if(glwrap)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glwrap);

    glwrap = wrapSGtoGL(twrap);
    if(glwrap)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glwrap);
}
void SG_CALL sgTextureSetInterpolation(SGTexture* texture, SGenum interp)
{
    glBindTexture(GL_TEXTURE_2D, GLTEX(texture));

    GLenum glinterp = interpSGtoGL(interp);
    if(glinterp)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glinterp);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glinterp);
    }
}

SGIVec2 SG_CALL sgTextureGetSize2iv(SGTexture* texture)
{
    return sgIVec2i(texture->width, texture->height);
}
SGVec2 SG_CALL sgTextureGetSize2fv(SGTexture* texture)
{
    return sgVec2iv(sgTextureGetSize2iv(texture));
}
SGuint SG_CALL sgTextureGetWidth(SGTexture* texture)
{
    return texture->width;
}
SGuint SG_CALL sgTextureGetHeight(SGTexture* texture)
{
    return texture->height;
}
SGenum SG_CALL sgTextureGetBPP(SGTexture* texture)
{
    return texture->bpp;
}

/* DEPRECATED */
void SG_CALL SG_HINT_DEPRECATED sgTextureGetSize(SGTexture* texture, SGuint* width, SGuint* height)
{
    SGIVec2 size = sgTextureGetSize2iv(texture);
    if(width)   *width = size.x;
    if(height)  *height = size.y;
}
