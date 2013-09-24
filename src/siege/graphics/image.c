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

#define SG_BUILD_LIBRARY
#include <siege/graphics/image.h>

#include <stdlib.h>
#include <stdio.h>

#include "../internal/stb/stb_image.h"

static int f_read(void* data, char* ptr, int size)
{
    SGStream* stream = data;
    return stream->read(stream->data, ptr, 1, size);
}
static void f_skip(void* data, unsigned n)
{
    SGStream* stream = data;
    stream->seek(stream->data, n, SG_SEEK_CUR);
}
static int f_eof(void* data)
{
    SGStream* stream = data;
    return stream->eof(stream->data);
}

static stbi_io_callbacks imgCallbacks;

SGbool SG_CALL _sgImageDataInit(void)
{
    imgCallbacks.read = f_read;
    imgCallbacks.skip = f_skip;
    imgCallbacks.eof = f_eof;
    return SG_TRUE;
}
SGbool SG_CALL _sgImageDataDeinit(void)
{
    return SG_TRUE;
}

SGImageData* SG_CALL sgImageDataCreateStream(SGStream* stream, SGbool delstream)
{
    SGImageData* idata = NULL;
    if(!stream) goto err;
    idata = malloc(sizeof(SGImageData));
    if(!idata) goto err;


    // TODO: Load with image BPP
    int w, h, n;
    idata->data = stbi_load_from_callbacks(&imgCallbacks, stream, &w, &h, &n, 4);
    if(!idata->data)
        goto err;
    idata->deldata = SG_TRUE;
    idata->width = w;
    idata->height = h;
    idata->bpp = 32;
    return idata;
err:
    fprintf(stderr, "Could not load image\n");
    if(idata)
    {
        if(idata->deldata && idata->data)
            free(idata->data);
        free(idata);
    }
    return NULL;
}
SGImageData* SG_CALL sgImageDataCreateFile(const char* fname)
{
    SGStream* stream = sgStreamCreateFile(fname, "r");
    if(!stream)
        fprintf(stderr, "Could not load image %s\n", fname);
    return sgImageDataCreateStream(stream, SG_TRUE);
}
SGImageData* SG_CALL sgImageDataCreateData(size_t width, size_t height, SGenum bpp, void* data)
{
    SGImageData* idata = malloc(sizeof(SGImageData));
    idata->width = width;
    idata->height = height;
    idata->bpp = bpp;
    idata->data = data;
    idata->deldata = SG_FALSE;

    return idata;
}
SGImageData* SG_CALL sgImageDataCreate(size_t width, size_t height, SGenum bpp)
{
    return sgImageDataCreateData(width, height, bpp, NULL);
}
void SG_CALL sgImageDataDestroy(SGImageData* idata)
{
    if(!idata) return;

    if(idata->deldata)
        free(idata->data);
    free(idata);
}

//SGbool SG_CALL sgImageDataConvert(SGImageData* idata, SGenum bpp);

//void SG_CALL sgImageDataSetData(SGImageData* idata, size_t width, size_t height, SGenum bpp, void* data);
void SG_CALL sgImageDataGetData(SGImageData* idata, size_t* width, size_t* height, SGenum* bpp, void** data)
{
    if(width) *width = idata->width;
    if(height) *height = idata->height;
    if(bpp) *bpp = idata->bpp;
    if(data) *data = idata->data;
}

void SG_CALL sgImageDataGetSize(SGImageData* idata, size_t* width, size_t* height)
{
    if(width) *width = idata->width;
    if(height) *height = idata->height;
}
size_t SG_CALL sgImageDataGetWidth(SGImageData* idata)
{
    return idata->width;
}
size_t SG_CALL sgImageDataGetHeight(SGImageData* idata)
{
    return idata->height;
}

SGenum SG_CALL sgImageDataGetBpp(SGImageData* idata)
{
    return idata->bpp;
}
