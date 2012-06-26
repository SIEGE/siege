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

    *sdata = malloc(sizeof(SurfaceData));

    (*sdata)->context = context;
    (*sdata)->isFBO = cdata->fbo.hasFBO;

    sgmGraphicsTextureCreate((void**)&(*sdata)->texture, context);

    if(cdata->fbo.hasFBO)
    {
        cdata->fbo.glGenFramebuffersEXT(1, &(*sdata)->fboid);
        cdata->fbo.glGenRenderbuffersEXT(1, &(*sdata)->rbid);
    }
    return sgmGraphicsSurfaceSetTexture(*sdata, (*sdata)->texture);
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
    cdata->fbo.glDeleteRenderbuffersEXT(1, &sdata->rbid);

    free(surface);

    return SG_OK;
}
SGuint SG_EXPORT sgmGraphicsSurfaceSetTexture(void* surface, void* texture)
{
    if(surface == NULL)
        return SG_OK; // SG_INVALID_VALUE
    SurfaceData* sdata = (SurfaceData*)surface;
    ContextData* cdata = (ContextData*)sdata->context;
    sdata->texture = texture;

    int status;
    if(cdata->fbo.hasFBO)
    {
        cdata->fbo.glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, sdata->fboid);
        cdata->fbo.glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, sdata->texture->texid, 0);

        cdata->fbo.glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, sdata->rbid);
        cdata->fbo.glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, sdata->texture->awidth, sdata->texture->aheight);
        cdata->fbo.glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, sdata->rbid);
        cdata->fbo.glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

        status = cdata->fbo.glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
        if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
        {
            cdata->fbo.glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
            return SG_UNKNOWN_ERROR;
        }
        cdata->fbo.glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    }

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
    SurfaceData* sdata = surface;
    ContextData* cdata = (ContextData*)sdata->context;

    SGuint ret = sgmGraphicsTextureSetData(sdata->texture, width, height, bpp, data);
    if(cdata->fbo.hasFBO)
        sgmGraphicsSurfaceSetTexture(sdata, sdata->texture);
    return ret;
}
SGenum SG_EXPORT sgmGraphicsSurfaceSetSubData(void* surface, SGuint x, SGuint y, SGuint width, SGuint height, SGenum bpp, void* data)
{
    if(surface == NULL)
        return SG_OK; // SG_INVALID_VALUE
    SurfaceData* sdata = surface;
    //ContextData* cdata = (ContextData*)sdata->context;

    SGuint ret = sgmGraphicsTextureSetSubData(sdata->texture, x, y, width, height, bpp, data);
    return ret;
}
SGuint SG_EXPORT sgmGraphicsSurfaceGetData(void* surface, SGuint* width, SGuint* height, SGuint* bpp, void** data)
{
	if(surface == NULL)
		return SG_OK; // SG_INVALID_VALUE
	SurfaceData* sdata = surface;

	return sgmGraphicsTextureGetData(sdata->texture, width, height, bpp, data);
}
SGuint SG_EXPORT sgmGraphicsSurfaceFreeData(void* data)
{
	return sgmGraphicsTextureFreeData(data);
}
SGuint SG_EXPORT sgmGraphicsSurfaceGetSize(void* surface, SGuint* width, SGuint* height)
{
    if(surface == NULL)
        return SG_OK; // SG_INVALID_VALUE

    SurfaceData* sdata = (SurfaceData*)surface;
    return sgmGraphicsTextureGetSize(sdata->texture, width, height);
}
SGenum SG_EXPORT sgmGraphicsSurfaceGetBPP(void* surface, SGenum* bpp)
{
    if(!surface)
        return SG_OK; // SG_INVALID_VALUE

    SurfaceData* sdata = (SurfaceData*)surface;
    return sgmGraphicsTextureGetBPP(sdata->texture, bpp);
}
SGuint SG_EXPORT sgmGraphicsSurfaceDraw(void* surface, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    if(surface == NULL)
        return SG_OK; // SG_INVALID_VALUE
    SurfaceData* sdata = (SurfaceData*)surface;

    return sgmGraphicsTextureDraw(sdata->texture, x, y, z, xscale, yscale, xoffset, yoffset, angle);
}
SGenum SG_EXPORT sgmGraphicsSurfaceTarget(void* surface)
{
    if(surface == NULL)
        return SG_OK; // SG_INVALID_VALUE
    SurfaceData* sdata = (SurfaceData*)surface;
    ContextData* cdata = (ContextData*)sdata->context;

    glPushAttrib(GL_VIEWPORT_BIT);
    glViewport(0, 0, sdata->texture->width, sdata->texture->height);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, sdata->texture->width, sdata->texture->height, 0, 127, -128);
    glMatrixMode(GL_MODELVIEW);

    if(cdata->fbo.hasFBO)
        cdata->fbo.glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, sdata->fboid);

    return SG_OK;
}
SGenum SG_EXPORT sgmGraphicsSurfaceUntarget(void* surface)
{
    if(surface == NULL)
        return SG_OK; // SG_INVALID_VALUE
    SurfaceData* sdata = (SurfaceData*)surface;
    ContextData* cdata = (ContextData*)sdata->texture->context;

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopAttrib();

    if(cdata->fbo.hasFBO)
        cdata->fbo.glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

    return SG_OK;
}
