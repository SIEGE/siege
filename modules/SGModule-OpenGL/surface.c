#include "main.h"
#include "surface.h"
#include "context.h"

#include <stdio.h>
#include <stdlib.h>

SGuint SG_EXPORT sgmGraphicsSurfaceCreate(void** surface, void* context)
{
    if(context == NULL)
        return SG_INVALID_VALUE;
    SurfaceData** sdata = (SurfaceData**)surface;
    ContextData* cdata = (ContextData*)context;

    *surface = malloc(sizeof(SurfaceData));

    (*sdata)->context = context;
    (*sdata)->isFBO = cdata->fbo.hasFBO;

    sgmGraphicsTextureCreate((void**)&(*sdata)->texture, context);

    if(cdata->fbo.hasFBO)
    {
        cdata->fbo.glGenFramebuffersEXT(1, &(*sdata)->fboid);
        sgmGraphicsSurfaceSetTexture(*sdata, (*sdata)->texture);
    }

    return SG_OK;
}
//SGuint SG_EXPORT sgmGraphicsSurfaceCreateTexture(void** surface, void* context, void* texture);
//SGuint SG_EXPORT sgmGraphicsSurfaceCreateData(void** surface, void* context, SGuint width, SGuint height, SGuint bpp, void* data);
SGuint SG_EXPORT sgmGraphicsSurfaceDestroy(void* surface)
{
    if(surface == NULL)
        return SG_OK; // SG_INVALID_VALUE

    SurfaceData* sdata = (SurfaceData*)surface;
    ContextData* cdata = (ContextData*)sdata->context;
    cdata->fbo.glDeleteFramebuffersEXT(1, &sdata->fboid);

    return SG_OK;
}
SGuint SG_EXPORT sgmGraphicsSurfaceSetTexture(void* surface, void* texture) // TODO: handle no FBOs available
{
    if(surface == NULL)
        return SG_OK; // SG_INVALID_VALUE
    SurfaceData* sdata = (SurfaceData*)surface;
    ContextData* cdata = (ContextData*)sdata->context;

    cdata->fbo.glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, sdata->fboid);
    cdata->fbo.glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, sdata->texture->texid, 0);
    int status = cdata->fbo.glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
    {
        cdata->fbo.glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
        return SG_UNKNOWN_ERROR;
    }
    cdata->fbo.glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

    return SG_OK;
}
SGuint SG_EXPORT sgmGraphicsSurfaceGetTexture(void* surface, void** texture)
{
    if(surface == NULL)
        return SG_OK; // SG_INVALID_VALUE

    SurfaceData* sdata = (SurfaceData*)surface;
    *texture = sdata->texture;

    return SG_OK;
}
SGuint SG_EXPORT sgmGraphicsSurfaceSetData(void* surface, SGuint width, SGuint height, SGuint bpp, void* data)
{
    if(surface == NULL)
        return SG_OK; // SG_INVALID_VALUE
    SurfaceData* sdata = (SurfaceData*)surface;

    return sgmGraphicsTextureSetData(sdata->texture, width, height, bpp, data);
}
//SGuint SG_EXPORT sgmGraphicsSurfaceGetData(void* surface, SGuint* width, SGuint* height, SGuint* bpp, void** data)
//SGuint SG_EXPORT sgmGraphicsSurfaceFreeData(void* surface, void* data)
SGuint SG_EXPORT sgmGraphicsSurfaceGetSize(void* surface, SGuint* width, SGuint* height)
{
    if(surface == NULL)
        return SG_OK; // SG_INVALID_VALUE

    SurfaceData* sdata = (SurfaceData*)surface;
    return sgmGraphicsTextureGetSize(sdata->texture, width, height);
}
SGuint SG_EXPORT sgmGraphicsSurfaceDraw(void* surface, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    if(surface == NULL)
        return SG_OK; // SG_INVALID_VALUE
    SurfaceData* sdata = (SurfaceData*)surface;

    return sgmGraphicsTextureDraw(sdata->texture, x, y, z, xscale, yscale, xoffset, yoffset, angle);
}
SGuint SG_EXPORT sgmGraphicsSurfaceSetTarget(void* surface)
{
    if(surface == NULL)
        return SG_OK; // SG_INVALID_VALUE
    SurfaceData* sdata = (SurfaceData*)surface;
    ContextData* cdata = (ContextData*)sdata->context;

// I HAS A HAX (doing the absolute best I can to solve the offset/scale problem in sgmGraphicsTextureDraw
/*    glMatrixMode(GL_PROJECTION);
    //glPushAttrib(GL_VIEWPORT_BIT);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(0, ((TextureData*)sdata->texture)->width, ((TextureData*)sdata->texture)->aheight, ((TextureData*)sdata->texture)->height - (float)((TextureData*)sdata->texture)->aheight, -128, 127);
    glMatrixMode(GL_MODELVIEW);*/
// I HAS A HAX NO MOAR

    if(sdata->isFBO)
        cdata->fbo.glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, sdata->fboid);
    else
    {
        ContextData* context = (ContextData*)sdata->texture->context;
        if(context->target != NULL)
            sgmGraphicsSurfaceResetTarget(context->target);

        if(context->temp == NULL)
            return SG_UNKNOWN_ERROR; // temp surface not properly loaded

        // copy screen to TEMP
        glBindTexture(GL_TEXTURE_2D, context->temp->texid);
        //glEnable(GL_TEXTURE_2D);
        glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, context->temp->awidth, context->temp->aheight, 0);
        //glDisable(GL_TEXTURE_2D);

        // draw SURF
        glDisable(GL_DEPTH_TEST);
        sgmGraphicsSurfaceDraw(sdata, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0);
        glEnable(GL_DEPTH_TEST);

        context->target = sdata;
    }

    return SG_OK;
}
//SGuint SG_EXPORT sgmGraphicsSurfaceGetTarget(void** surface)
SGuint SG_EXPORT sgmGraphicsSurfaceResetTarget(void* surface)
{
    if(surface == NULL)
        return SG_OK; // SG_INVALID_VALUE
    SurfaceData* sdata = (SurfaceData*)surface;
    ContextData* cdata = (ContextData*)sdata->texture->context;

    if(sdata->isFBO)
        cdata->fbo.glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    else
    {
        if(cdata->target == NULL)
            return SG_OK; // SG_INVALID_VALUE

        if(cdata->temp == NULL)
            return SG_UNKNOWN_ERROR; // temporary surface not properly loaded

        // copy screen to SURF
        glBindTexture(GL_TEXTURE_2D, cdata->target->texture->texid);
        //glEnable(GL_TEXTURE_2D);
        glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, cdata->target->texture->awidth, cdata->target->texture->aheight, 0);
        //glDisable(GL_TEXTURE_2D);

        // draw TEMP
        glDisable(GL_DEPTH_TEST);
        sgmGraphicsSurfaceDraw(sdata, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0);
        glEnable(GL_DEPTH_TEST);

        cdata->target = NULL;
    }

// I HAS A HAX
/*    glMatrixMode(GL_PROJECTION);
    //glPopAttrib(GL_VIEWPORT_BIT);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);*/
// I HAS A HAX NO MOAR

    return SG_OK;
}
