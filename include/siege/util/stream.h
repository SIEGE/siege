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

#ifndef __SIEGE_UTIL_STREAM_H__
#define __SIEGE_UTIL_STREAM_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/* SGStream structures and typedefs declared in common.h */

SGStream* SG_EXPORT sgStreamCreate(SGStreamSeek* seek, SGStreamTell* tell, SGStreamRead* read, SGStreamWrite* write, SGStreamClose* close, void* data);
SGStream* SG_EXPORT sgStreamCreateFile(const char* fname, const char* mode);
SGStream* SG_EXPORT sgStreamCreateMemory(void* mem, size_t size, SGFree* cbfree);
SGStream* SG_EXPORT sgStreamCreateCMemory(const void* mem, size_t size, SGFree* cbfree);
SGStream* SG_EXPORT sgStreamCreateBuffer(size_t size);
void SG_EXPORT sgStreamDestroy(SGStream* stream);

SGlong SG_EXPORT sgStreamTellSize(SGStream* stream);
SGbool SG_EXPORT sgStreamSeek(SGStream* stream, SGlong offset, SGenum origin);
SGlong SG_EXPORT sgStreamTell(SGStream* stream);
SGulong SG_EXPORT sgStreamRead(SGStream* stream, void* ptr, size_t size, size_t count);
SGulong SG_EXPORT sgStreamWrite(SGStream* stream, const void* ptr, size_t size, size_t count);
SGbool SG_EXPORT sgStreamClose(SGStream* stream);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_STREAM_H__
