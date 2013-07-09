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

SGenum SG_CALL sgmGLoadInit(void)
{
    callbacks.read = f_read;
    callbacks.skip = f_skip;
    callbacks.eof = f_eof;
    return SG_OK;
}
SGenum SG_CALL sgmGLoadDeinit(void)
{
    return SG_OK;
}

