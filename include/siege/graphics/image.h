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

#ifndef __SIEGE_GRAPHICS_IMAGE_H__
#define __SIEGE_GRAPHICS_IMAGE_H__

#include "../common.h"
#include "../util/stream.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGImageData
{
    size_t width;
    size_t height;
    SGenum bpp;
    void* data;
} SGImageData;

SGImageData* SG_CALL sgImageDataCreateStream(SGStream* stream, SGbool delstream);
SGImageData* SG_CALL sgImageDataCreateFile(const char* fname);
SGImageData* SG_CALL sgImageDataCreateData(size_t width, size_t height, SGenum bpp, void* data);
SGImageData* SG_CALL sgImageDataCreate(size_t width, size_t height, SGenum bpp);
void SG_CALL sgImageDataDestroy(SGImageData* idata);

//SGbool SG_CALL sgImageDataConvert(SGImageData* idata, SGenum bpp);

//void SG_CALL sgImageDataSetData(SGImageData* idata, size_t width, size_t height, SGenum bpp, void* data);
void SG_CALL sgImageDataGetData(SGImageData* idata, size_t* width, size_t* height, SGenum* bpp, void** data);

void SG_CALL sgImageDataGetSize(SGImageData* idata, size_t* width, size_t* height);
size_t SG_CALL sgImageDataGetWidth(SGImageData* idata);
size_t SG_CALL sgImageDataGetHeight(SGImageData* idata);

SGenum SG_CALL sgImageDataGetBpp(SGImageData* idata);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_IMAGE_H__
