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

#include <stdlib.h>
#include <string.h>

SGenum SG_EXPORT sgmGraphicsLoad(SGStream* stream, size_t* width, size_t* height, SGenum* bpp, void** data)
{
    if(!stream)
    {
        *width = 2;
        *height = 2;
        *bpp = 4;
        *data = NULL;

        return SG_OK;
    }
    if(!stream->read || !stream->seek || !stream->eof)
        return SG_INVALID_VALUE;

    int w, h, n;

    *data = stbi_load_from_callbacks(&callbacks, stream, &w, &h, &n, 4);
    *width = w;
    *height = h;
    *bpp = 32;

    return *data ? SG_OK : SG_UNKNOWN_ERROR;
}

SGenum sgmGraphicsLoadFreeData(void* data)
{
    free(data);
    return SG_OK;
}
