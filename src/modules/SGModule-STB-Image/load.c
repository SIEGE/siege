/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "license.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#include <siege/backend.h>
#include "stb_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SGenum SG_EXPORT sgmGraphicsLoadFile(const char* fname, size_t* width, size_t* height, SGenum* bpp, void** data)
{
    if(strcmp(fname, "") == 0)
    {
        *width = 2;
        *height = 2;
        *bpp = 4;
        *data = NULL;

        return SG_OK;
    }

    int w, h, n;

    *data = stbi_load(fname, &w, &h, &n, 4);
    *width = w;
    *height = h;
    *bpp = 32;

    printf("%s: %p\n", fname, *data);

    return *data ? SG_OK : SG_UNKNOWN_ERROR;
}

/*SGenum SG_EXPORT sgmGraphicsLoadStream(char* fname, size_t* width, size_t* height, SGenum* bpp, void** data)
{
    return 1;
}*/

SGenum sgmGraphicsLoadFreeData(void* data)
{
    free(data);
    return SG_OK;
}
