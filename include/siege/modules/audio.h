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

#ifndef __SIEGE_MODULES_AUDIO_H__
#define __SIEGE_MODULES_AUDIO_H__
#include "../common.h"
#include "../util/link.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#ifdef SG_BUILD_LIBRARY

#define SG_FPTR(name) (*p##name)
#include "../backend/audio/buffer.h"
#include "../backend/audio/source.h"
#include "../backend/audio/load.h"
#undef SG_FPTR

#endif // SG_BUILD_LIBRARY

void SG_EXPORT _sgModuleLoadAudio(SGLibrary* lib);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_MODULES_AUDIO_H__
