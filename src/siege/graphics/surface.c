#define SG_BUILD_LIBRARY
#include <siege/graphics/surface.h>
#include <siege/core/window.h>
#include <siege/modules/graphics.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

SGbool SG_EXPORT _sgSurfaceInit()
{
    _sg_surfTarget = NULL;
    return SG_TRUE;
}
SGbool SG_EXPORT _sgSurfaceDeinit()
{
    return SG_TRUE;
}

SGSurface* SG_EXPORT sgSurfaceCreateFile(char* fname)
{
    SGuint width;
    SGuint height;
    SGuint bpp;
    void* data;

    SGuint ret;
    if(_sg_modGraphics.sgmGraphicsLoadFile != NULL)
        ret = _sg_modGraphics.sgmGraphicsLoadFile(fname, &width, &height, &bpp, &data);
    if((_sg_modGraphics.sgmGraphicsLoadFile == NULL) || (ret != SG_OK))
        fprintf(stderr, "Could not load image %s\n", fname);

    SGSurface* surface = sgSurfaceCreateData(width, height, bpp, data);
    if(_sg_modGraphics.sgmGraphicsLoadFreeData != NULL)
        _sg_modGraphics.sgmGraphicsLoadFreeData(data);
    return surface;
}
SGSurface* SG_EXPORT sgSurfaceCreateData(SGuint width, SGuint height, SGenum bpp, void* data)
{
    SGSurface* surface = malloc(sizeof(SGSurface));
    if(surface == NULL)
        return NULL;

    if(data != NULL)
        data = _sgGraphicsToCanvasSize(width, height, bpp, data);

    if(_sg_modGraphics.sgmGraphicsSurfaceCreate != NULL)
        _sg_modGraphics.sgmGraphicsSurfaceCreate(&surface->handle, _sg_gfxHandle);
    if(_sg_modGraphics.sgmGraphicsSurfaceSetData != NULL)
        _sg_modGraphics.sgmGraphicsSurfaceSetData(surface->handle, width, height, bpp, data);

    // as allocated by _sgGraphicsToCanvasSize (or else it's null, and we don't care)
    free(data);
    return surface;
}
SGSurface* SG_EXPORT sgSurfaceCreate(SGuint width, SGuint height, SGenum bpp)
{
    return sgSurfaceCreateData(width, height, bpp, NULL);
}
void SG_EXPORT sgSurfaceDestroy(SGSurface* surface)
{
    if(_sg_modGraphics.sgmGraphicsSurfaceDestroy != NULL)
        _sg_modGraphics.sgmGraphicsSurfaceDestroy(surface->handle);
    free(surface);
}

void SG_EXPORT sgSurfaceDrawRads3f2f2f1f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    if(_sg_modGraphics.sgmGraphicsSurfaceDraw != NULL)
        _sg_modGraphics.sgmGraphicsSurfaceDraw(surface->handle, x, y, z, xscale, yscale, xoffset, yoffset, angle);
}
void SG_EXPORT sgSurfaceDrawDegs3f2f2f1f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, z, xscale, yscale, xoffset, yoffset, angle * M_PI / 180.0);
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
    if(_sg_modGraphics.sgmGraphicsSurfaceSetTarget != NULL)
        _sg_modGraphics.sgmGraphicsSurfaceSetTarget(surface->handle);
    _sg_surfTarget = surface->handle;
}
void SG_EXPORT sgSurfaceUntarget(SGSurface* surface)
{
    if(_sg_modGraphics.sgmGraphicsSurfaceResetTarget != NULL)
        _sg_modGraphics.sgmGraphicsSurfaceResetTarget(_sg_surfTarget);
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
    if(_sg_modGraphics.sgmGraphicsContextClear != NULL)
        _sg_modGraphics.sgmGraphicsContextClear(_sg_gfxHandle, col);
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

    if(_sg_modGraphics.sgmGraphicsSurfaceGetSize != NULL)
        _sg_modGraphics.sgmGraphicsSurfaceGetSize(surface->handle, width, height);
}
SGuint SG_EXPORT sgSurfaceGetWidth(SGSurface* surface)
{
    SGuint width;
    SGuint height;
    if(_sg_modGraphics.sgmGraphicsSurfaceGetSize != NULL)
        _sg_modGraphics.sgmGraphicsSurfaceGetSize(surface->handle, &width, &height);
    return width;
}
SGuint SG_EXPORT sgSurfaceGetHeight(SGSurface* surface)
{
    SGuint width;
    SGuint height;
    if(_sg_modGraphics.sgmGraphicsSurfaceGetSize != NULL)
        _sg_modGraphics.sgmGraphicsSurfaceGetSize(surface->handle, &width, &height);
    return height;
}
