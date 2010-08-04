#define SG_BUILD_LIBRARY
#include <siege/graphics/surface.h>
#include <siege/core/window.h>
#include <siege/modules/graphics.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

SGbool _sgSurfaceInit()
{
    _sg_surfTarget = NULL;
    return SG_TRUE;
}
SGbool _sgSurfaceDeinit()
{
    return SG_TRUE;
}

SGSurface* sgSurfaceCreateFile(char* fname)
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
SGSurface* sgSurfaceCreateData(SGuint width, SGuint height, SGenum bpp, void* data)
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
SGSurface* sgSurfaceCreate(SGuint width, SGuint height, SGenum bpp)
{
    return sgSurfaceCreateData(width, height, bpp, NULL);
}
void sgSurfaceDestroy(SGSurface* surface)
{
    if(_sg_modGraphics.sgmGraphicsSurfaceDestroy != NULL)
        _sg_modGraphics.sgmGraphicsSurfaceDestroy(surface->handle);
    free(surface);
}

void sgSurfaceDrawRads3f2f2f1f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    if(_sg_modGraphics.sgmGraphicsSurfaceDraw != NULL)
        _sg_modGraphics.sgmGraphicsSurfaceDraw(surface->handle, x, y, z, xscale, yscale, xoffset, yoffset, angle);
}
void sgSurfaceDrawDegs3f2f2f1f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, z, xscale, yscale, xoffset, yoffset, angle * M_PI / 180.0);
}
void sgSurfaceDrawRads3f2f1f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float angle)
{
    sgSurfaceDrawRads3f2f2f1f(surface, x, y, z, xscale, yscale, 0.0, 0.0, angle);
}
void sgSurfaceDrawDegs3f2f1f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float angle)
{
    sgSurfaceDrawDegs3f2f2f1f(surface, x, y, z, xscale, yscale, 0.0, 0.0, angle);
}
/*void sgSurfaceDraw(SGSurface* surface, float x, float y, float xscale, float yscale, float angle);
void sgSurfaceDraw(SGSurface* surface, float x, float y, float z, float xscale, float yscale);
void sgSurfaceDraw(SGSurface* surface, float x, float y, float xscale, float yscale);
void sgSurfaceDraw(SGSurface* surface, float x, float y, float z, float angle);
void sgSurfaceDraw(SGSurface* surface, float x, float y, float angle);
void sgSurfaceDraw(SGSurface* surface, float x, float y, float z);
void sgSurfaceDraw(SGSurface* surface, float x, float y);*/
void sgSurfaceDraw(SGSurface* surface)
{
    sgSurfaceDrawRads3f2f2f1f(surface, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

void sgSurfaceTarget(SGSurface* surface)
{
    if(_sg_modGraphics.sgmGraphicsSurfaceSetTarget != NULL)
        _sg_modGraphics.sgmGraphicsSurfaceSetTarget(surface->handle);
    _sg_surfTarget = surface->handle;
}
void sgSurfaceUntarget(SGSurface* surface)
{
    if(_sg_modGraphics.sgmGraphicsSurfaceResetTarget != NULL)
        _sg_modGraphics.sgmGraphicsSurfaceResetTarget(_sg_surfTarget);
    _sg_surfTarget = NULL;
}
void sgSurfaceClear4f(SGSurface* surface, float r, float g, float b, float a)
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
void sgSurfaceClear3f(SGSurface* surface, float r, float g, float b)
{
    sgSurfaceClear4f(surface, r, g, b, 1.0f);
}
void sgSurfaceClear2f(SGSurface* surface, float g, float a)
{
    sgSurfaceClear4f(surface, g, g, g, a);
}
void sgSurfaceClear1f(SGSurface* surface, float g)
{
    sgSurfaceClear4f(surface, g, g, g, 1.0f);
}
void sgSurfaceClear4ub(SGSurface* surface, SGubyte r, SGubyte g, SGubyte b, SGubyte a)
{
    sgSurfaceClear4f(surface, r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}
void sgSurfaceClear3ub(SGSurface* surface, SGubyte r, SGubyte g, SGubyte b)
{
    sgSurfaceClear4f(surface, r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
}
void sgSurfaceClear2ub(SGSurface* surface, SGubyte g, SGubyte a)
{
    sgSurfaceClear4f(surface, g / 255.0f, g / 255.0f, g / 255.0f, a / 255.0f);
}
void sgSurfaceClear1ub(SGSurface* surface, SGubyte g)
{
    sgSurfaceClear4f(surface, g / 255.0f, g / 255.0f, g / 255.0f, 1.0f);
}
void sgSurfaceClear(SGSurface* surface)
{
    sgSurfaceClear4f(surface, 0.0f, 0.0f, 0.0f, 0.0f);
}

void sgSurfaceGetSize(SGSurface* surface, SGuint* width, SGuint* height)
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
SGuint sgSurfaceGetWidth(SGSurface* surface)
{
    SGuint width;
    SGuint height;
    if(_sg_modGraphics.sgmGraphicsSurfaceGetSize != NULL)
        _sg_modGraphics.sgmGraphicsSurfaceGetSize(surface->handle, &width, &height);
    return width;
}
SGuint sgSurfaceGetHeight(SGSurface* surface)
{
    SGuint width;
    SGuint height;
    if(_sg_modGraphics.sgmGraphicsSurfaceGetSize != NULL)
        _sg_modGraphics.sgmGraphicsSurfaceGetSize(surface->handle, &width, &height);
    return height;
}
