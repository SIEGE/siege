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

SGImageData* SG_EXPORT sgImageDataCreateFile(const char* fname)
{
    SGImageData* idata = malloc(sizeof(SGImageData));
    if(!idata) return NULL;

    SGenum ret;
    if(psgmGraphicsLoadFile)
    {
        ret = psgmGraphicsLoadFile(fname, &idata->width, &idata->height, &idata->bpp, &idata->data);
        if(ret != SG_OK)
            fprintf(stderr, "Could not load image %s\n", fname);
    }
    else
        fprintf(stderr, "Could not load image %s\n", fname);

    return idata;
}
SGImageData* SG_EXPORT sgImageDataCreateData(size_t width, size_t height, SGenum bpp, void* data)
{
    SGImageData* idata = malloc(sizeof(SGImageData));
    idata->width = width;
    idata->height = height;
    idata->bpp = bpp;
    idata->data = data;

    return idata;
}
SGImageData* SG_EXPORT sgImageDataCreate(size_t width, size_t height, SGenum bpp)
{
    return sgImageDataCreateData(width, height, bpp, NULL);
}
void SG_EXPORT sgImageDataDestroy(SGImageData* idata)
{
    if(!idata) return;

    if(psgmGraphicsLoadFreeData)
        psgmGraphicsLoadFreeData(idata->data);
    free(idata);
}

//SGbool SG_EXPORT sgImageDataConvert(SGImageData* idata, SGenum bpp);

//void SG_EXPORT sgImageDataSetData(SGImageData* idata, size_t width, size_t height, SGenum bpp, void* data);
void SG_EXPORT sgImageDataGetData(SGImageData* idata, size_t* width, size_t* height, SGenum* bpp, void** data)
{
    if(width) *width = idata->width;
    if(height) *height = idata->height;
    if(bpp) *bpp = idata->bpp;
    if(data) *data = idata->data;
}

void SG_EXPORT sgImageDataGetSize(SGImageData* idata, size_t* width, size_t* height)
{
    if(width) *width = idata->width;
    if(height) *height = idata->height;
}
size_t SG_EXPORT sgImageDataGetWidth(SGImageData* idata)
{
    return idata->width;
}
size_t SG_EXPORT sgImageDataGetHeight(SGImageData* idata)
{
    return idata->height;
}

SGenum SG_EXPORT sgImageDataGetBpp(SGImageData* idata)
{
    return idata->bpp;
}
