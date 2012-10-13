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
#include <siege/core/window.h>
#include <siege/modules/graphics.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

SGbool SG_EXPORT _sgSurfaceInit(void)
{
    _sg_surfTarget = NULL;
    return SG_TRUE;
}
SGbool SG_EXPORT _sgSurfaceDeinit(void)
{
    return SG_TRUE;
}

SGSurface* SG_EXPORT sgSurfaceCreateStream(SGStream* stream, SGbool delstream)
{
    size_t width;
    size_t height;
    SGuint bpp;
    void* data;

    SGuint ret;
    if(psgmGraphicsLoad)
    {
        ret = psgmGraphicsLoad(stream, &width, &height, &bpp, &data);
        if(ret != SG_OK)
            fprintf(stderr, "Could not load image\n");
    }
    else
        fprintf(stderr, "Could not load image\n");

    SGSurface* surface = sgSurfaceCreateData(width, height, bpp, data);
    if(psgmGraphicsLoadFreeData != NULL)
        psgmGraphicsLoadFreeData(data);
    if(delstream)
        sgStreamDestroy(stream);
    return surface;
}
SGSurface* SG_EXPORT sgSurfaceCreateFile(const char* fname)
{
    SGStream* stream = sgStreamCreateFile(fname, "r");
    if(!stream)
        fprintf(stderr, "Could not load image %s\n", fname);
    return sgSurfaceCreateStream(stream, SG_TRUE);
}
SGSurface* SG_EXPORT sgSurfaceCreateData(SGuint width, SGuint height, SGenum bpp, void* data)
{
    SGSurface* surface = malloc(sizeof(SGSurface));
    if(surface == NULL)
        return NULL;

    if(psgmGraphicsSurfaceCreate != NULL)
        psgmGraphicsSurfaceCreate(&surface->handle, _sg_gfxHandle);
    sgSurfaceSetData(surface, width, height, bpp, data);

    return surface;
}
SGSurface* SG_EXPORT sgSurfaceCreate(SGuint width, SGuint height, SGenum bpp)
{
    return sgSurfaceCreateData(width, height, bpp, NULL);
}
void SG_EXPORT sgSurfaceDestroy(SGSurface* surface)
{
    if(psgmGraphicsSurfaceDestroy != NULL)
        psgmGraphicsSurfaceDestroy(surface->handle);
    free(surface);
}

void SG_EXPORT sgSurfaceSetData(SGSurface* surface, size_t width, size_t height, SGenum bpp, void* data)
{
    if(psgmGraphicsSurfaceSetData)
        psgmGraphicsSurfaceSetData(surface->handle, width, height, bpp, data);
}
void SG_EXPORT sgSurfaceSetSubData(SGSurface* surface, size_t x, size_t y, size_t width, size_t height, SGenum bpp, void* data)
{
    if(psgmGraphicsSurfaceSetSubData)
        psgmGraphicsSurfaceSetSubData(surface->handle, x, y, width, height, bpp, data);
}
void* SG_EXPORT sgSurfaceGetData(SGSurface* surface)
{
    SGuint w, h;
    SGenum bpp;
    void* data = NULL;
    if(psgmGraphicsSurfaceGetData)
        psgmGraphicsSurfaceGetData(surface->handle, &w, &h, &bpp, &data);
    return data;
}
void SG_EXPORT sgSurfaceFreeData(void* data)
{
    psgmGraphicsSurfaceFreeData(data);
}

void SG_EXPORT sgSurfaceDrawRads3f2f2f1f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    if(psgmGraphicsSurfaceDraw != NULL)
        psgmGraphicsSurfaceDraw(surface->handle, x, y, z, xscale, yscale, xoffset, yoffset, angle);
}
void SG_EXPORT sgSurfaceDrawDegs3f2f2f1f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, z, xscale, yscale, xoffset, yoffset, angle * SG_PI / 180.0);
}
void SG_EXPORT sgSurfaceDrawRads2f2f2f1f(SGSurface* surface, float x, float y, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, 0.0, xscale, yscale, xoffset, yoffset, angle);
}
void SG_EXPORT sgSurfaceDrawDegs2f2f2f1f(SGSurface* surface, float x, float y, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    sgSurfaceDrawDegs3f2f2f1f(surface, x, y, 0.0, xscale, yscale, xoffset, yoffset, angle);
}
void SG_EXPORT sgSurfaceDrawRads3f2f1f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float angle)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, z, xscale, yscale, 0.0, 0.0, angle);
}
void SG_EXPORT sgSurfaceDrawDegs3f2f1f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float angle)
{
    sgSurfaceDrawDegs3f2f2f1f(surface, x, y, z, xscale, yscale, 0.0, 0.0, angle);
}
void SG_EXPORT sgSurfaceDrawRads2f2f1f(SGSurface* surface, float x, float y, float xscale, float yscale, float angle)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, 0.0, xscale, yscale, 0.0, 0.0, angle);
}
void SG_EXPORT sgSurfaceDrawDegs2f2f1f(SGSurface* surface, float x, float y, float xscale, float yscale, float angle)
{
    sgSurfaceDrawDegs3f2f2f1f(surface, x, y, 0.0, xscale, yscale, 0.0, 0.0, angle);
}
void SG_EXPORT sgSurfaceDrawRads3f1f(SGSurface* surface, float x, float y, float z, float angle)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, z, 1.0, 1.0, 0.0, 0.0, angle);
}
void SG_EXPORT sgSurfaceDrawDegs3f1f(SGSurface* surface, float x, float y, float z, float angle)
{
    sgSurfaceDrawDegs3f2f2f1f(surface, x, y, z, 1.0, 1.0, 0.0, 0.0, angle);
}
void SG_EXPORT sgSurfaceDrawRads2f1f(SGSurface* surface, float x, float y, float angle)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, 0.0, 1.0, 1.0, 0.0, 0.0, angle);
}
void SG_EXPORT sgSurfaceDrawDegs2f1f(SGSurface* surface, float x, float y, float angle)
{
    sgSurfaceDrawDegs3f2f2f1f(surface, x, y, 0.0, 1.0, 1.0, 0.0, 0.0, angle);
}
void SG_EXPORT sgSurfaceDraw3f2f2f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, z, xscale, yscale, xoffset, yoffset, 0.0);
}
void SG_EXPORT sgSurfaceDraw2f2f2f(SGSurface* surface, float x, float y, float xscale, float yscale, float xoffset, float yoffset)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, 0.0, xscale, yscale, xoffset, yoffset, 0.0);
}
void SG_EXPORT sgSurfaceDraw3f2f(SGSurface* surface, float x, float y, float z, float xscale, float yscale)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, z, xscale, yscale, 0.0, 0.0, 0.0);
}
void SG_EXPORT sgSurfaceDraw2f2f(SGSurface* surface, float x, float y, float xscale, float yscale)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, 0.0, xscale, yscale, 0.0, 0.0, 0.0);
}
void SG_EXPORT sgSurfaceDraw3f(SGSurface* surface, float x, float y, float z)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, z, 1.0, 1.0, 0.0, 0.0, 0.0);
}
void SG_EXPORT sgSurfaceDraw2f(SGSurface* surface, float x, float y)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0);
}
void SG_EXPORT sgSurfaceDraw(SGSurface* surface)
{
    sgSurfaceDrawRads3f2f2f1f(surface, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
}

void SG_EXPORT sgSurfaceTarget(SGSurface* surface)
{
    if(psgmGraphicsSurfaceTarget != NULL)
        psgmGraphicsSurfaceTarget(surface->handle);
    _sg_surfTarget = surface->handle;
}
void SG_EXPORT sgSurfaceUntarget(SGSurface* surface)
{
    if(psgmGraphicsSurfaceUntarget != NULL)
        psgmGraphicsSurfaceUntarget(_sg_surfTarget);
    _sg_surfTarget = NULL;
}
void SG_EXPORT sgSurfaceClear4f(SGSurface* surface, float r, float g, float b, float a)
{
    float col[4];
    col[0] = r;
    col[1] = g;
    col[2] = b;
    col[3] = a;
    sgSurfaceTarget(surface);
    if(psgmGraphicsContextClear != NULL)
        psgmGraphicsContextClear(_sg_gfxHandle, col);
    sgSurfaceUntarget(surface);
}
void SG_EXPORT sgSurfaceClear3f(SGSurface* surface, float r, float g, float b)
{
    sgSurfaceClear4f(surface, r, g, b, 1.0f);
}
void SG_EXPORT sgSurfaceClear2f(SGSurface* surface, float g, float a)
{
    sgSurfaceClear4f(surface, g, g, g, a);
}
void SG_EXPORT sgSurfaceClear1f(SGSurface* surface, float g)
{
    sgSurfaceClear4f(surface, g, g, g, 1.0f);
}
void SG_EXPORT sgSurfaceClear4ub(SGSurface* surface, SGubyte r, SGubyte g, SGubyte b, SGubyte a)
{
    sgSurfaceClear4f(surface, r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}
void SG_EXPORT sgSurfaceClear3ub(SGSurface* surface, SGubyte r, SGubyte g, SGubyte b)
{
    sgSurfaceClear4f(surface, r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
}
void SG_EXPORT sgSurfaceClear2ub(SGSurface* surface, SGubyte g, SGubyte a)
{
    sgSurfaceClear4f(surface, g / 255.0f, g / 255.0f, g / 255.0f, a / 255.0f);
}
void SG_EXPORT sgSurfaceClear1ub(SGSurface* surface, SGubyte g)
{
    sgSurfaceClear4f(surface, g / 255.0f, g / 255.0f, g / 255.0f, 1.0f);
}
void SG_EXPORT sgSurfaceClear(SGSurface* surface)
{
    sgSurfaceClear4f(surface, 0.0f, 0.0f, 0.0f, 0.0f);
}

void SG_EXPORT sgSurfaceGetSize(SGSurface* surface, SGuint* width, SGuint* height)
{
    if((width == NULL) && (height == NULL))
        return;
    SGuint buf;

    // make sure we don't pass any nulls
    if(width == NULL)
        width = &buf;
    if(height == NULL)
        height = &buf;

    if(psgmGraphicsSurfaceGetSize != NULL)
        psgmGraphicsSurfaceGetSize(surface->handle, width, height);
}
SGuint SG_EXPORT sgSurfaceGetWidth(SGSurface* surface)
{
    SGuint width;
    SGuint height;
    if(psgmGraphicsSurfaceGetSize != NULL)
        psgmGraphicsSurfaceGetSize(surface->handle, &width, &height);
    return width;
}
SGuint SG_EXPORT sgSurfaceGetHeight(SGSurface* surface)
{
    SGuint width;
    SGuint height;
    if(psgmGraphicsSurfaceGetSize != NULL)
        psgmGraphicsSurfaceGetSize(surface->handle, &width, &height);
    return height;
}
SGenum SG_EXPORT sgSurfaceGetBPP(SGSurface* surface)
{
    SGenum bpp;
    if(psgmGraphicsSurfaceGetBPP)
        psgmGraphicsSurfaceGetBPP(surface->handle, &bpp);
    return bpp;
}
