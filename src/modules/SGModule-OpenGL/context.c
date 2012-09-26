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
#include "context.h"

#include <stdlib.h>
#include <string.h>

SGenum SG_EXPORT sgmGraphicsContextCreate(void** context, SGuint width, SGuint height, SGuint bpp)
{
    ContextData** cdata = (ContextData**)context;
    *context = calloc(1, sizeof(ContextData));
    (*cdata)->target = NULL;
    (*cdata)->bpp = bpp;
    (*cdata)->vact = SG_FALSE;
    (*cdata)->cact = SG_FALSE;
    (*cdata)->tact = SG_FALSE;
    (*cdata)->iact = SG_FALSE;
    (*cdata)->vptr = NULL;
    (*cdata)->cptr = NULL;
    (*cdata)->tptr = NULL;
    (*cdata)->iptr = NULL;

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);

    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    const char* extensions = (const char*)glGetString(GL_EXTENSIONS);
    char* ext = strstr(extensions, "_framebuffer_object"); // EXT_framebuffer_object or ARB_framebuffer_object or w/e
    (*cdata)->fbo.hasFBO = (ext != NULL);
    checkFBO(&(*cdata)->fbo);

    //sgmGraphicsContextResize(*context, width, height);
    return SG_OK;
}

SGenum SG_EXPORT sgmGraphicsContextDestroy(void* context)
{
    if(!context) return SG_INVALID_VALUE;
    ContextData* cdata = context;

    if(cdata->vptr) free(cdata->vptr);
    if(cdata->cptr) free(cdata->cptr);
    if(cdata->tptr) free(cdata->tptr);
    if(cdata->iptr) free(cdata->iptr);

    free(context);

    return SG_OK;
}

SGenum SG_EXPORT sgmGraphicsContextResize(void* context, SGuint width, SGuint height)
{
    if(context == NULL)
        return SG_OK; // SG_INVALID_VALUE
    //ContextData* cdata = (ContextData*)context;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, width, height, 0, 127, -128);

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    return SG_OK;
}

SGenum SG_EXPORT sgmGraphicsContextClear(void* context, float* color)
{
    if(context == NULL)
        return SG_OK; // SG_INVALID_VALUE

    glClearColor(color[0], color[1], color[2], color[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT/* | GL_STENCIL_BUFFER_BIT | GL_ACCUM_BUFFER_BIT*/);

    return SG_OK;
}
