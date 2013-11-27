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

#ifndef __SIEGE_GRAPHICS_BITMAP_H__
#define __SIEGE_GRAPHICS_BITMAP_H__

#include "../common.h"
#include "../util/stream.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGBitmap
{
    size_t width;
    size_t height;
    SGenum bpp;
    void* data;
    SGbool deldata;
} SGBitmap;

SGbool SG_CALL _sgBitmapInit(void);
SGbool SG_CALL _sgBitmapDeinit(void);

SGBitmap* SG_CALL sgBitmapCreateStream(SGStream* stream, SGbool delstream);
SGBitmap* SG_CALL sgBitmapCreateFile(const char* fname);
SGBitmap* SG_CALL sgBitmapCreateData(size_t width, size_t height, SGenum bpp, void* data);
SGBitmap* SG_CALL sgBitmapCreate(size_t width, size_t height, SGenum bpp);
void SG_CALL sgBitmapDestroy(SGBitmap* bmp);

//SGbool SG_CALL sgBitmapConvert(SGBitmap* bmp, SGenum bpp);

//void SG_CALL sgBitmapSetData(SGBitmap* bmp, size_t width, size_t height, SGenum bpp, void* data);
void SG_CALL sgBitmapGetData(SGBitmap* bmp, size_t* width, size_t* height, SGenum* bpp, void** data);

void SG_CALL sgBitmapGetSize(SGBitmap* bmp, size_t* width, size_t* height);
size_t SG_CALL sgBitmapGetWidth(SGBitmap* bmp);
size_t SG_CALL sgBitmapGetHeight(SGBitmap* bmp);

SGenum SG_CALL sgBitmapGetBpp(SGBitmap* bmp);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_BITMAP_H__
