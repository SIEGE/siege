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
#include <siege/modules/graphics.h>

#include <stdlib.h>
#include <stdio.h>

SGImageData* SG_CALL sgImageDataCreateStream(SGStream* stream, SGbool delstream)
{
    SGImageData* idata = malloc(sizeof(SGImageData));
    if(!idata) goto err;

    SGenum ret;
    if(psgmGraphicsLoad)
    {
        ret = psgmGraphicsLoad(stream, &idata->width, &idata->height, &idata->bpp, &idata->data);
        if(ret != SG_OK)
            goto err;
    }
    else
        goto err;
    return idata;
err:
    fprintf(stderr, "Could not load image\n");
    if(idata)
    {
        if(idata->data)
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

    return idata;
}
SGImageData* SG_CALL sgImageDataCreate(size_t width, size_t height, SGenum bpp)
{
    return sgImageDataCreateData(width, height, bpp, NULL);
}
void SG_CALL sgImageDataDestroy(SGImageData* idata)
{
    if(!idata) return;

    if(psgmGraphicsLoadFreeData)
        psgmGraphicsLoadFreeData(idata->data);
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
