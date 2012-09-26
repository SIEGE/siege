/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "license.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
*/

#include "main.h"

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

static ILHANDLE ILAPIENTRY f_open(ILconst_string str)
{
    return NULL;
}
static void ILAPIENTRY f_close(ILHANDLE data)
{
}
static ILboolean ILAPIENTRY f_eof(ILHANDLE data)
{
    SGStream* stream = data;
    if(!stream->eof) return IL_TRUE; /* error */

    return stream->eof(stream->data);
}
static ILint ILAPIENTRY f_getc(ILHANDLE data)
{
    SGStream* stream = data;
    if(!stream->read) return EOF;

    char c;
    return stream->read(stream->data, &c, 1, 1) == 1 ? c : EOF;
}
static ILint ILAPIENTRY f_read(void* ptr, ILuint size, ILuint count, ILHANDLE data)
{
    SGStream* stream = data;
    if(!stream->read) return EOF;

    return stream->read(stream->data, ptr, size, count);
}
static ILint ILAPIENTRY f_seek(ILHANDLE data, ILint pos, ILint whence)
{
    SGStream* stream = data;
    if(!stream->seek) return EOF;

    SGenum swhence;
    switch(whence)
    {
        case SEEK_SET: swhence = SG_SEEK_SET; break;
        case SEEK_CUR: swhence = SG_SEEK_CUR; break;
        case SEEK_END: swhence = SG_SEEK_END; break;
        default: return -1;
    }

    return stream->seek(stream->data, pos, swhence);
}
static ILint ILAPIENTRY f_tell(ILHANDLE data)
{
    SGStream* stream = data;
    if(!stream->tell) return EOF;

    return stream->tell(stream->data);
}

SGuint SG_EXPORT sgmModuleInit(SGModuleInfo** minfo)
{
    *minfo = (SGModuleInfo*)calloc(1, sizeof(SGModuleInfo));
    (*minfo)->vmajor = SG_VERSION_MAJOR;
    (*minfo)->vminor = SG_VERSION_MINOR;
    (*minfo)->vpatch = SG_VERSION_PATCH;

    ilInit();

    int version = ilGetInteger(IL_VERSION_NUM);

    (*minfo)->mmajor = version / 100;
    (*minfo)->mminor = version / 10 - (*minfo)->mmajor * 100;
    (*minfo)->mpatch = version / 1 - (*minfo)->mminor * 10 - (*minfo)->mmajor * 100;
    (*minfo)->type = SG_MODULE_GRAPHICSLOAD;
    (*minfo)->name = "DevIL";

    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_UPPER_LEFT);

    ilSetRead(f_open, f_close, f_eof, f_getc, f_read, f_seek, f_tell);

    return SG_OK;
}

SGuint SG_EXPORT sgmModuleExit(SGModuleInfo* minfo)
{
    ilShutDown();
    free(minfo);

    return SG_OK;
}

//SGuint SG_EXPORT sgmModuleFree(void* data)

SGuint SG_EXPORT sgmModuleMatch(SGModuleInfo** minfos, SGuint numinfos, SGbool* ok)
{
    *ok = SG_TRUE; // we're independent of modules...
    return SG_OK;
}

