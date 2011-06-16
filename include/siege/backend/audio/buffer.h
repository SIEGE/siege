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

#ifndef __SIEGE_BACKEND_AUDIO_BUFFER_H__
#define __SIEGE_BACKEND_AUDIO_BUFFER_H__

#include "../../common.h"

#ifndef SG_FPTR
#define SG_FPTR(name)	name
#endif // SG_FPTR

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT SG_FPTR(sgmAudioBufferCreate)(void** buffer);
    //SGuint SG_EXPORT SG_FPTR(sgmAudioBufferCreateData)(void** buffer, SGuint channels, SGuint format, SGuint frequency, void* data, SGuint datalen);
    SGuint SG_EXPORT SG_FPTR(sgmAudioBufferDestroy)(void* buffer);
    SGuint SG_EXPORT SG_FPTR(sgmAudioBufferSetData)(void* buffer, SGuint channels, SGuint format, SGuint frequency, void* data, SGuint datalen);
    //SGuint SG_EXPORT SG_FPTR(sgmAudioBufferGetData)(void* buffer, SGuint* channels, SGuint* format, SGuint* frequency, void* data, SGuint* datalen);
    //SGuint SG_EXPORT SG_FPTR(sgmAudioBufferFreeData)(void* data);

    SGuint SG_EXPORT SG_FPTR(sgmAudioBufferSetHandle)(void* buffer, void* handle);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_AUDIO_BUFFER_H__
