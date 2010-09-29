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

int exRaised(libvlc_exception_t* ex)
{
    if(libvlc_exception_raised(ex))
        return 1;
    return 0;
}

SGuint SG_EXPORT sgModuleInit(void* gc, SGModuleInfo** minfo)
{
    *minfo = (SGModuleInfo*)calloc(1, sizeof(SGModuleInfo));

    char* tmp = tmpnam(NULL);
    const char* const vlcArgs[] = {
              "-I", "dummy", /* Don't use any interface */
              "--ignore-config", /* Don't use VLC's config */
              "--plugin-path=Modules/Plugins",
              "--sout='#transcode{acodec=s16l}:std{access=file,mux=raw,dst=/path/to/pipe}'",
              NULL };

    vlcInstance = libvlc_new(sizeof(vlcArgs) / sizeof(vlcArgs[0]), vlcArgs, &vlcEx);
    if(exRaised(&vlcEx))
        return SG_UNKNOWN_ERROR;

    return SG_OK;
}

SGuint SG_EXPORT sgModuleExit(SGModuleInfo* minfo)
{
    libvlc_release(vlcInstance);

    free(minfo);

    return SG_OK;
}

//SGuint SG_EXPORT sgModuleFree(void* data)

SGuint SG_EXPORT sgAudioLoadFile(char* fname, SGuint* channels, SGuint* type, SGuint* frequency, void** data, SGuint* datalen)
{
    libvlc_media_t* media = libvlc_media_new(vlcInstance, fname, &vlcEx);
    if(exRaised(&vlcEx))
        return SG_UNKNOWN_ERROR;

    libvlc_media_release(media);

    return SG_OK;
}

//SGuint SG_EXPORT sgAudioLoadStream(void* stream, SGuint* channels, SGuint* type, SGuint* frequency, void** data, SGuint* datalen)

SGuint SG_EXPORT sgAudioLoadFreeData(void* data)
{
    free(data);
    return SG_OK;
}
