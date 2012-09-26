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

    ILuint img;

    ilGenImages(1, &img);
    ilBindImage(img);

    ilLoadF(IL_TYPE_UNKNOWN, stream);

    *width = ilGetInteger(IL_IMAGE_WIDTH);
    *height = ilGetInteger(IL_IMAGE_HEIGHT);

    *bpp = 32;//ilGetInteger(IL_IMAGE_BPP);
    //format = GL_RGBA;//ilGetInteger(IL_IMAGE_FORMAT);
    //type = GL_UNSIGNED_BYTE;

    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

    *data = malloc(*width * *height * *bpp / 8);
    *data = memcpy(*data, ilGetData(), *width * *height * *bpp / 8);

    ilDeleteImages(1, &img);

    return SG_OK;
}

SGenum sgmGraphicsLoadFreeData(void* data)
{
    free(data);
    return SG_OK;
}
