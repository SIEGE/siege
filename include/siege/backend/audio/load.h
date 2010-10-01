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

#ifndef __SIEGE_BACKEND_AUDIO_LOAD_H__
#define __SIEGE_BACKEND_AUDIO_LOAD_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT SG_HINT_DEPRECATED sgmAudioLoadFile(char* fname, SGuint* channels, SGuint* format, SGuint* frequency, void** data, SGuint* datalen);
    //SGuint SG_EXPORT SG_HINT_DEPRECATED sgmAudioLoadStream(void* stream, SGuint* channels, SGuint* format, SGuint* frequency, void** data, SGuint* datalen);
    SGuint SG_EXPORT SG_HINT_DEPRECATED sgmAudioLoadFreeData(void* data);

    SGuint SG_EXPORT sgmAudioFileCreate(void** file, char* fname, SGuint* channels, SGuint* format, SGuint* frequency);
    SGuint SG_EXPORT sgmAudioFileDestroy(void* file);
    SGuint SG_EXPORT sgmAudioFileNumSamples(void* file, SGuint* samples);
    SGuint SG_EXPORT sgmAudioFileRead(void* file, void* data, SGuint* datalen);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_AUDIO_LOAD_H__
