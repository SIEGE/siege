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
#include <siege/graphics/surface.h>
#include <siege/graphics/bitmap.h>
#include <siege/graphics/draw.h>
#include <siege/core/window.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../internal/gl.h"

SGbool SG_CALL _sgSurfaceInit(void)
{
    return SG_TRUE;
}
SGbool SG_CALL _sgSurfaceDeinit(void)
{
    return SG_TRUE;
}

SGSurface* SG_CALL sgSurfaceCreateBitmap(SGBitmap* bmp, SGbool delbmp)
{
    size_t width;
    size_t height;
    SGenum bpp;
    void* data;

    sgBitmapGetData(bmp, &width, &height, &bpp, &data);
    SGSurface* surface = sgSurfaceCreateData(width, height, bpp, data);
    if(delbmp)
        sgBitmapDestroy(bmp);
    return surface;
}
SGSurface* SG_CALL sgSurfaceCreateStream(SGStream* stream, SGbool delstream)
{
    SGBitmap* bmp = sgBitmapCreateStream(stream, delstream);
    if(!bmp) return NULL;
    return sgSurfaceCreateBitmap(bmp, SG_TRUE);
}
SGSurface* SG_CALL sgSurfaceCreateFile(const char* fname)
{
    SGStream* stream = sgStreamCreateFile(fname, "r");
    if(!stream)
    {
        fprintf(stderr, "Could not load image %s\n", fname);
        return NULL;
    }
    return sgSurfaceCreateStream(stream, SG_TRUE);
}
SGSurface* SG_CALL sgSurfaceCreateData(SGuint width, SGuint height, SGenum bpp, void* data)
{
    SGTexture* texture = sgTextureCreateData(width, height, bpp, data);
    if(!texture) return NULL;

    SGSurface* surface = sgSurfaceCreateTexture(texture, SG_TRUE);
    if(!surface)
        sgTextureDestroy(texture);
    return surface;
}
SGSurface* SG_CALL sgSurfaceCreateTexture(SGTexture* texture, SGbool deltex)
{
    SGSurface* surface = malloc(sizeof(SGSurface));
    if(!surface) return NULL;

    surface->fboid = malloc(sizeof(GLuint));
    surface->rbid = malloc(sizeof(GLuint));
    surface->texture = NULL;
    surface->deltex = SG_FALSE;

    glGenFramebuffersEXT(1, surface->fboid);
    glGenRenderbuffersEXT(1, surface->rbid);

    if(!sgSurfaceSetTexture(surface, texture, deltex))
    {
        sgSurfaceDestroy(surface);
        return NULL;
    }

    return surface;
}
SGSurface* SG_CALL sgSurfaceCreate(SGuint width, SGuint height, SGenum bpp)
{
    return sgSurfaceCreateData(width, height, bpp, NULL);
}
void SG_CALL sgSurfaceDestroy(SGSurface* surface)
{
    glDeleteRenderbuffersEXT(1, surface->rbid);
    glDeleteFramebuffersEXT(1, surface->fboid);
    free(surface->rbid);
    free(surface->fboid);
    if(surface->deltex && surface->texture)
        sgTextureDestroy(surface->texture);
    free(surface);
}

SGbool SG_CALL sgSurfaceSetTexture(SGSurface* surface, SGTexture* texture, SGbool deltex)
{
    if(!texture) return SG_FALSE;
    if(surface->deltex)
    {
        if(surface->texture != texture)
            sgTextureDestroy(surface->texture);
    }
    surface->texture = texture;
    surface->deltex = deltex;

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, GLFBO(surface));
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, GLTEX(texture), 0);

    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, GLRB(surface));
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH24_STENCIL8_EXT, texture->width, texture->height);
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, GLRB(surface));
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, GLRB(surface));
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

    GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    return status == GL_FRAMEBUFFER_COMPLETE_EXT;
}
SGTexture* SG_CALL sgSurfaceGetTexture(SGSurface* surface)
{
    return surface->texture;
}

void SG_CALL sgSurfaceSetData(SGSurface* surface, size_t width, size_t height, SGenum bpp, void* data)
{
    sgTextureSetData(surface->texture, width, height, bpp, data);
    sgSurfaceSetTexture(surface, surface->texture, surface->deltex);
}
void SG_CALL sgSurfaceSetSubData(SGSurface* surface, size_t x, size_t y, size_t width, size_t height, SGenum bpp, void* data)
{
    sgTextureSetSubData(surface->texture, x, y, width, height, bpp, data);
}
void* SG_CALL sgSurfaceGetData(SGSurface* surface)
{
    return sgTextureGetData(surface->texture);
}
void SG_CALL sgSurfaceFreeData(void* data)
{
    sgTextureFreeData(data);
}

void SG_CALL sgSurfaceDrawRads3f2f2f1f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    sgTextureDrawRads3f2f2f1f(surface->texture, x, y, z, xscale, yscale, xoffset, yoffset, angle);
}
void SG_CALL sgSurfaceDrawDegs3f2f2f1f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, z, xscale, yscale, xoffset, yoffset, angle * SG_PI / 180.0);
}
void SG_CALL sgSurfaceDrawRads2f2f2f1f(SGSurface* surface, float x, float y, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, 0.0, xscale, yscale, xoffset, yoffset, angle);
}
void SG_CALL sgSurfaceDrawDegs2f2f2f1f(SGSurface* surface, float x, float y, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    sgSurfaceDrawDegs3f2f2f1f(surface, x, y, 0.0, xscale, yscale, xoffset, yoffset, angle);
}
void SG_CALL sgSurfaceDrawRads3f2f1f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float angle)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, z, xscale, yscale, 0.0, 0.0, angle);
}
void SG_CALL sgSurfaceDrawDegs3f2f1f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float angle)
{
    sgSurfaceDrawDegs3f2f2f1f(surface, x, y, z, xscale, yscale, 0.0, 0.0, angle);
}
void SG_CALL sgSurfaceDrawRads2f2f1f(SGSurface* surface, float x, float y, float xscale, float yscale, float angle)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, 0.0, xscale, yscale, 0.0, 0.0, angle);
}
void SG_CALL sgSurfaceDrawDegs2f2f1f(SGSurface* surface, float x, float y, float xscale, float yscale, float angle)
{
    sgSurfaceDrawDegs3f2f2f1f(surface, x, y, 0.0, xscale, yscale, 0.0, 0.0, angle);
}
void SG_CALL sgSurfaceDrawRads3f1f(SGSurface* surface, float x, float y, float z, float angle)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, z, 1.0, 1.0, 0.0, 0.0, angle);
}
void SG_CALL sgSurfaceDrawDegs3f1f(SGSurface* surface, float x, float y, float z, float angle)
{
    sgSurfaceDrawDegs3f2f2f1f(surface, x, y, z, 1.0, 1.0, 0.0, 0.0, angle);
}
void SG_CALL sgSurfaceDrawRads2f1f(SGSurface* surface, float x, float y, float angle)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, 0.0, 1.0, 1.0, 0.0, 0.0, angle);
}
void SG_CALL sgSurfaceDrawDegs2f1f(SGSurface* surface, float x, float y, float angle)
{
    sgSurfaceDrawDegs3f2f2f1f(surface, x, y, 0.0, 1.0, 1.0, 0.0, 0.0, angle);
}
void SG_CALL sgSurfaceDraw3f2f2f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, z, xscale, yscale, xoffset, yoffset, 0.0);
}
void SG_CALL sgSurfaceDraw2f2f2f(SGSurface* surface, float x, float y, float xscale, float yscale, float xoffset, float yoffset)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, 0.0, xscale, yscale, xoffset, yoffset, 0.0);
}
void SG_CALL sgSurfaceDraw3f2f(SGSurface* surface, float x, float y, float z, float xscale, float yscale)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, z, xscale, yscale, 0.0, 0.0, 0.0);
}
void SG_CALL sgSurfaceDraw2f2f(SGSurface* surface, float x, float y, float xscale, float yscale)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, 0.0, xscale, yscale, 0.0, 0.0, 0.0);
}
void SG_CALL sgSurfaceDraw3f(SGSurface* surface, float x, float y, float z)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, z, 1.0, 1.0, 0.0, 0.0, 0.0);
}
void SG_CALL sgSurfaceDraw2f(SGSurface* surface, float x, float y)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0);
}
void SG_CALL sgSurfaceDraw(SGSurface* surface)
{
    sgSurfaceDrawRads3f2f2f1f(surface, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
}

void SG_CALL sgSurfaceTarget(SGSurface* surface)
{
    glPushAttrib(GL_VIEWPORT_BIT);
    glViewport(0, 0, surface->texture->width, surface->texture->height);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, surface->texture->width, surface->texture->height, 0, 127, -128);
    glMatrixMode(GL_MODELVIEW);

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, GLFBO(surface));
}
void SG_CALL sgSurfaceUntarget(SGSurface* surface)
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopAttrib();

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}
void SG_CALL sgSurfaceClear4f(SGSurface* surface, float r, float g, float b, float a)
{
    sgSurfaceTarget(surface);
    sgDrawClear4f(r, g, b, a);
    sgSurfaceUntarget(surface);
}
void SG_CALL sgSurfaceClear3f(SGSurface* surface, float r, float g, float b)
{
    sgSurfaceClear4f(surface, r, g, b, 1.0f);
}
void SG_CALL sgSurfaceClear2f(SGSurface* surface, float g, float a)
{
    sgSurfaceClear4f(surface, g, g, g, a);
}
void SG_CALL sgSurfaceClear1f(SGSurface* surface, float g)
{
    sgSurfaceClear4f(surface, g, g, g, 1.0f);
}
void SG_CALL sgSurfaceClear4ub(SGSurface* surface, SGubyte r, SGubyte g, SGubyte b, SGubyte a)
{
    sgSurfaceClear4f(surface, r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}
void SG_CALL sgSurfaceClear3ub(SGSurface* surface, SGubyte r, SGubyte g, SGubyte b)
{
    sgSurfaceClear4f(surface, r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
}
void SG_CALL sgSurfaceClear2ub(SGSurface* surface, SGubyte g, SGubyte a)
{
    sgSurfaceClear4f(surface, g / 255.0f, g / 255.0f, g / 255.0f, a / 255.0f);
}
void SG_CALL sgSurfaceClear1ub(SGSurface* surface, SGubyte g)
{
    sgSurfaceClear4f(surface, g / 255.0f, g / 255.0f, g / 255.0f, 1.0f);
}
void SG_CALL sgSurfaceClear(SGSurface* surface)
{
    sgSurfaceClear4f(surface, 0.0f, 0.0f, 0.0f, 0.0f);
}

SGIVec2 SG_CALL sgSurfaceGetSize2iv(SGSurface* surface)
{
    return sgTextureGetSize2iv(surface->texture);
}
SGVec2 SG_CALL sgSurfaceGetSize2fv(SGSurface* surface)
{
    return sgVec2iv(sgSurfaceGetSize2iv(surface));
}
SGuint SG_CALL sgSurfaceGetWidth(SGSurface* surface)
{
    return sgTextureGetWidth(surface->texture);
}
SGuint SG_CALL sgSurfaceGetHeight(SGSurface* surface)
{
    return sgTextureGetHeight(surface->texture);
}
SGenum SG_CALL sgSurfaceGetBPP(SGSurface* surface)
{
    return sgTextureGetBPP(surface->texture);
}

/* DEPRECATED */
void SG_CALL SG_HINT_DEPRECATED sgSurfaceGetSize(SGSurface* surface, SGuint* width, SGuint* height)
{
    SGIVec2 size = sgSurfaceGetSize2iv(surface);
    if(width)   *width = size.x;
    if(height)  *height = size.y;
}
