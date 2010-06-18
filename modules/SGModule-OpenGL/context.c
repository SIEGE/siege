#include "main.h"
#include "context.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SGuint SG_EXPORT sgGraphicsContextCreate(void** context, SGuint width, SGuint height, SGuint bpp)
{
    ContextData** cdata = (ContextData**)context;
    *context = calloc(1, sizeof(ContextData));
    (*cdata)->temp = NULL;
    (*cdata)->target = NULL;
    (*cdata)->bpp = bpp;

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);

    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    const char* extensions = glGetString(GL_EXTENSIONS);
    char* ext = strstr(extensions, "_framebuffer_object"); // EXT_framebuffer_object or ARB_framebuffer_object or w/e
    (*cdata)->fbo.hasFBO = (ext != NULL);
    checkFBO(&(*cdata)->fbo);

    //sgGraphicsContextResize(*context, width, height);
    return SG_OK;
}

SGuint SG_EXPORT sgGraphicsContextDestroy(void* context)
{
    if(context == NULL)
        return SG_OK; // SG_INVALID_VALUE

    sgGraphicsTextureDestroy(((ContextData*)context)->temp);
    free(context);

    return SG_OK;
}

SGuint SG_EXPORT sgGraphicsContextResize(void* context, SGuint width, SGuint height)
{
    if(context == NULL)
        return SG_OK; // SG_INVALID_VALUE
    ContextData* cdata = (ContextData*)context;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, width, height, 0, -128, 127);

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    sgGraphicsTextureDestroy(cdata->temp);
    sgGraphicsTextureCreate((void**)&cdata->temp, cdata);
    sgGraphicsTextureSetData(cdata->temp, width, height, cdata->bpp, NULL);

    return SG_OK;
}

SGuint SG_EXPORT sgGraphicsContextClear(void* context, float* color)
{
    if(context == NULL)
        return SG_OK; // SG_INVALID_VALUE

    glClearColor(color[0], color[1], color[2], color[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT/* | GL_STENCIL_BUFFER_BIT | GL_ACCUM_BUFFER_BIT*/);

    return SG_OK;
}
