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

#define SG_FMODE_READ       1
#define SG_FMODE_WRITE      2
#define SG_FMODE_APPEND     4

#define SG_SEEK_SET 0
#define SG_SEEK_CUR 1
#define SG_SEEK_END 2

typedef SGbool  SG_CALL SGStreamSeek(void* stream, SGlong offset, SGenum origin);
typedef SGlong  SG_CALL SGStreamTell(void* stream);
typedef SGulong SG_CALL SGStreamRead(void* stream, void* ptr, size_t size, size_t count);
typedef SGulong SG_CALL SGStreamWrite(void* stream, const void* ptr, size_t size, size_t count);
typedef SGbool  SG_CALL SGStreamClose(void* stream);
typedef SGbool  SG_CALL SGStreamEOF(void* stream);

typedef struct SGStream
{
    SGStreamSeek* seek;
    SGStreamTell* tell;
    SGStreamRead* read;
    SGStreamWrite* write;
    SGStreamClose* close;
    SGStreamEOF* eof;

    void* data;
} SGStream;

SGStream* SG_CALL sgStreamInit(SGStream* stream, SGStreamSeek* seek, SGStreamTell* tell, SGStreamRead* read, SGStreamWrite* write, SGStreamClose* close, SGStreamEOF* eof, void* data);
SGStream* SG_CALL sgStreamInitFile(SGStream* stream, const char* fname, SGenum fmode);
SGStream* SG_CALL sgStreamInitMemory(SGStream* stream, void* mem, size_t size, SGFree* cbFree);
SGStream* SG_CALL sgStreamInitCMemory(SGStream* stream, const void* mem, size_t size, SGFree* cbFree);
SGStream* SG_CALL sgStreamInitBuffer(SGStream* stream, size_t size);
void SG_CALL sgStreamDeinit(SGStream* stream);

SGStream* SG_CALL sgStreamCreate(SGStreamSeek* seek, SGStreamTell* tell, SGStreamRead* read, SGStreamWrite* write, SGStreamClose* close, SGStreamEOF* eof, void* data);
SGStream* SG_CALL sgStreamCreateFile(const char* fname, SGenum fmode);
SGStream* SG_CALL sgStreamCreateMemory(void* mem, size_t size, SGFree* cbFree);
SGStream* SG_CALL sgStreamCreateCMemory(const void* mem, size_t size, SGFree* cbFree);
SGStream* SG_CALL sgStreamCreateBuffer(size_t size);
void SG_CALL sgStreamDestroy(SGStream* stream);

SGlong SG_CALL sgStreamTellSize(SGStream* stream);
SGbool SG_CALL sgStreamSeek(SGStream* stream, SGlong offset, SGenum origin);
SGlong SG_CALL sgStreamTell(SGStream* stream);
SGulong SG_CALL sgStreamRead(SGStream* stream, void* ptr, size_t size, size_t count);
SGulong SG_CALL sgStreamWrite(SGStream* stream, const void* ptr, size_t size, size_t count);
SGbool SG_CALL sgStreamClose(SGStream* stream);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_STREAM_H__
