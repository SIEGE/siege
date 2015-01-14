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
#include <siege/graphics/bitmap.h>

#include <stdlib.h>
#include <stdio.h>

#include "../internal/stb/stb_image.h"

static int f_read(void* data, char* ptr, int size)
{
    SGStream* stream = data;
    return stream->read(stream->data, ptr, 1, size);
}
static void f_skip(void* data, int n)
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

SGbool SG_CALL _sgBitmapInit(void)
{
    imgCallbacks.read = f_read;
    imgCallbacks.skip = f_skip;
    imgCallbacks.eof = f_eof;
    return SG_TRUE;
}
SGbool SG_CALL _sgBitmapDeinit(void)
{
    return SG_TRUE;
}

SGBitmap* SG_CALL sgBitmapCreateStream(SGStream* stream)
{
    // TODO: Load with image BPP
    int w, h, n;
    void* data = stbi_load_from_callbacks(&imgCallbacks, stream, &w, &h, &n, 4);
    SGBitmap* bmp = sgBitmapCreateData(w, h, 32, data);
    if(bmp)
        bmp->deldata = SG_TRUE;
    else
    {
        stbi_image_free(data);
        fprintf(stderr, "Could not load image\n");
        return NULL;
    }
    return bmp;
}
SGBitmap* SG_CALL sgBitmapCreateFile(const char* fname)
{
    SGStream stream;
    if(!sgStreamInitFile(&stream, fname, SG_FMODE_READ))
    {
        fprintf(stderr, "Could not load image %s\n", fname);
        return NULL;
    }
    SGBitmap* bmp = sgBitmapCreateStream(&stream);
    sgStreamDeinit(&stream);
    return bmp;
}
SGBitmap* SG_CALL sgBitmapCreateData(size_t width, size_t height, SGenum bpp, void* data)
{
    SGBitmap* bmp = malloc(sizeof(SGBitmap));
    if(!bmp) return NULL;
    sgRCountInit(&bmp->cnt);

    bmp->width = width;
    bmp->height = height;
    bmp->bpp = bpp;
    bmp->data = data;
    bmp->deldata = SG_FALSE;

    return bmp;
}
SGBitmap* SG_CALL sgBitmapCreate(size_t width, size_t height, SGenum bpp)
{
    return sgBitmapCreateData(width, height, bpp, NULL);
}
void SG_CALL sgBitmapForceDestroy(SGBitmap* bmp)
{
    if(!bmp) return;

    if(bmp->deldata)
        free(bmp->data);
    sgRCountDeinit(&bmp->cnt);
    free(bmp);
}

void SG_CALL sgBitmapRelease(SGBitmap* bmp)
{
    sgBitmapUnlock(bmp);
}
void SG_CALL sgBitmapLock(SGBitmap* bmp)
{
    if(!bmp) return;
    sgRCountInc(&bmp->cnt);
}
void SG_CALL sgBitmapUnlock(SGBitmap* bmp)
{
    if(!bmp) return;
    if(!sgRCountDec(&bmp->cnt))
        sgBitmapForceDestroy(bmp);
}

//SGbool SG_CALL sgBitmapConvert(SGBitmap* bmp, SGenum bpp);

//void SG_CALL sgBitmapSetData(SGBitmap* bmp, size_t width, size_t height, SGenum bpp, void* data);
void SG_CALL sgBitmapGetData(SGBitmap* bmp, size_t* width, size_t* height, SGenum* bpp, void** data)
{
    if(width) *width = bmp->width;
    if(height) *height = bmp->height;
    if(bpp) *bpp = bmp->bpp;
    if(data) *data = bmp->data;
}

SGIVec2 SG_CALL sgBitmapGetSize2iv(SGBitmap* bmp)
{
    return sgIVec2i(bmp->width, bmp->height);
}
SGVec2 SG_CALL sgBitmapGetSize2fv(SGBitmap* bmp)
{
    return sgVec2iv(sgBitmapGetSize2iv(bmp));
}
size_t SG_CALL sgBitmapGetWidth(SGBitmap* bmp)
{
    return bmp->width;
}
size_t SG_CALL sgBitmapGetHeight(SGBitmap* bmp)
{
    return bmp->height;
}

SGenum SG_CALL sgBitmapGetBPP(SGBitmap* bmp)
{
    return bmp->bpp;
}

/* DEPRECATED */
void SG_CALL SG_HINT_DEPRECATED sgBitmapDestroy(SGBitmap* bmp)
{
    sgBitmapRelease(bmp);
}
void SG_CALL SG_HINT_DEPRECATED sgBitmapGetSize(SGBitmap* bmp, size_t* width, size_t* height)
{
    SGIVec2 size = sgBitmapGetSize2iv(bmp);
    if(width)   *width = size.x;
    if(height)  *height = size.y;
}
