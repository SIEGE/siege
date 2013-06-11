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

#ifndef __SIEGE_BACKEND_AUDIO_LOAD_H__
#define __SIEGE_BACKEND_AUDIO_LOAD_H__

#include "../../common.h"
#include "../util/stream.h"

#ifndef SG_FPTR
#define SG_FPTR(name)    name
#endif // SG_FPTR

#ifdef __cplusplus
extern "C"
{
#endif
    SGenum SG_CALL SG_FPTR(sgmAudioFileCreate)(void** file, SGStream* stream, SGuint* channels, SGuint* format, SGuint* frequency);
    SGenum SG_CALL SG_FPTR(sgmAudioFileDestroy)(void* file);
    SGenum SG_CALL SG_FPTR(sgmAudioFileNumSamples)(void* file, SGuint* samples);
    SGenum SG_CALL SG_FPTR(sgmAudioFileRead)(void* file, void* data, SGuint* datalen);

    SGenum SG_CALL SG_FPTR(sgmAudioFileGetHandle)(void* file, void** handle);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_AUDIO_LOAD_H__
