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

#define SG_BUILD_LIBRARY
#include <siege/util/stream.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static SGbool SG_CALL cbFileSeek(void* stream, SGlong offset, SGenum origin)
{
    int corigin;
    switch(origin)
    {
        case SG_SEEK_SET: corigin = SEEK_SET; break;
        case SG_SEEK_CUR: corigin = SEEK_CUR; break;
        case SG_SEEK_END: corigin = SEEK_END; break;
        default: return SG_FALSE;
    }
    return !fseek((FILE*)stream, offset, corigin);
}
static SGlong SG_CALL cbFileTell(void* stream)
{
    return ftell((FILE*)stream);
}
static SGulong SG_CALL cbFileRead(void* stream, void* ptr, size_t size, size_t count)
{
    return fread(ptr, size, count, (FILE*)stream);
}
static SGulong SG_CALL cbFileWrite(void* stream, const void* ptr, size_t size, size_t count)
{
    return fwrite(ptr, size, count, (FILE*)stream);
}
static SGbool SG_CALL cbFileClose(void* stream)
{
    return !fclose((FILE*)stream);
}
static SGbool SG_CALL cbFileEOF(void* stream)
{
    return feof((FILE*)stream);
}

typedef struct MemoryInfo
{
    SGubyte* ptr;
    SGubyte* cur;
    SGubyte* end;

    SGFree* free;
} MemoryInfo;

static SGbool SG_CALL cbMemorySeek(void* stream, SGlong offset, SGenum origin)
{
    MemoryInfo* minfo = stream;
    SGlong pos;
    switch(origin)
    {
        case SG_SEEK_SET: pos = offset; break;
        case SG_SEEK_CUR: pos = minfo->cur - minfo->ptr + offset; break;
        case SG_SEEK_END: pos = minfo->end - minfo->ptr + offset; break;
        default: return SG_FALSE;
    }
    if(pos < 0)
        return SG_FALSE;
    if(pos > minfo->end - minfo->ptr)
        return SG_FALSE;
    minfo->cur = minfo->ptr + pos;
    return SG_TRUE;
}
static SGlong SG_CALL cbMemoryTell(void* stream)
{
    MemoryInfo* minfo = stream;
    return minfo->cur - minfo->ptr;
}
static SGulong SG_CALL cbMemoryRead(void* stream, void* ptr, size_t size, size_t count)
{
    MemoryInfo* minfo = stream;
    size_t avail = minfo->end - minfo->cur;
    if(avail < size * count)
        count = avail / size;

    memcpy(ptr, minfo->cur, size * count);
    minfo->cur += size * count;
    return count;
}
static SGulong SG_CALL cbMemoryWrite(void* stream, const void* ptr, size_t size, size_t count)
{
    MemoryInfo* minfo = stream;
    size_t avail = minfo->end - minfo->cur;
    if(avail < size * count)
        count = avail / size;

    memcpy(minfo->cur, ptr, size * count);
    minfo->cur += size * count;
    return count;
}
static SGbool SG_CALL cbMemoryClose(void* stream)
{
    MemoryInfo* minfo = stream;
    if(minfo->free)
        minfo->free(minfo->ptr);
    free(minfo);
    return SG_TRUE;
}
static SGbool SG_CALL cbMemoryEOF(void* stream)
{
    MemoryInfo* minfo = stream;
    return minfo->cur == minfo->end;
}

static void SG_CALL cbBufferFree(void* ptr)
{
    free(ptr);
}

SGStream* SG_CALL sgStreamInit(SGStream* stream, SGStreamSeek* seek, SGStreamTell* tell, SGStreamRead* read, SGStreamWrite* write, SGStreamClose* close, SGStreamEOF* eof, void* data)
{
    if(!stream) return NULL;

    stream->seek = seek;
    stream->tell = tell;
    stream->read = read;
    stream->write = write;
    stream->close = close;
    stream->eof = eof;

    stream->data = data;

    return stream;
}
SGStream* SG_CALL sgStreamInitFile(SGStream* stream, const char* fname, SGenum fmode)
{
    if(!stream) return NULL;

    const char* modestr;
    switch(fmode)
    {
        case SG_FMODE_READ: modestr = "rb"; break;
        case SG_FMODE_WRITE: modestr = "wb"; break;
        case SG_FMODE_APPEND: modestr = "ab"; break;
        /* TODO: Should a RDWR mode be added? */
        default: return NULL;
    }

    FILE* file = fopen(fname, modestr);
    if(!file) return NULL;

    stream = sgStreamInit(stream, cbFileSeek, cbFileTell, cbFileRead, cbFileWrite, cbFileClose, cbFileEOF, file);
    if(!stream)
        fclose(file);
    return stream;
}
SGStream* SG_CALL sgStreamInitMemory(SGStream* stream, void* mem, size_t size, SGFree* cbFree)
{
    if(!stream) return NULL;

    MemoryInfo* minfo = malloc(sizeof(MemoryInfo));
    if(!minfo) return NULL;

    minfo->ptr = mem;
    minfo->cur = minfo->ptr;
    minfo->end = minfo->ptr + size;

    minfo->free = free;

    stream = sgStreamInit(stream, cbMemorySeek, cbMemoryTell, cbMemoryRead, cbMemoryWrite, cbMemoryClose, cbMemoryEOF, minfo);
    if(!stream)
        free(minfo);
    return stream;
}
SGStream* SG_CALL sgStreamInitCMemory(SGStream* stream, const void* mem, size_t size, SGFree* cbFree)
{
    if(!stream) return NULL;

    MemoryInfo* minfo = malloc(sizeof(MemoryInfo));
    if(!minfo) return NULL;

    minfo->ptr = (void*)mem;
    minfo->cur = minfo->ptr;
    minfo->end = minfo->ptr + size;

    minfo->free = free;

    stream = sgStreamCreate(cbMemorySeek, cbMemoryTell, cbMemoryRead, NULL, cbMemoryClose, cbMemoryEOF, minfo);
    if(!stream)
        free(minfo);
    return stream;
}
SGStream* SG_CALL sgStreamInitBuffer(SGStream* stream, size_t size)
{
    if(!stream) return NULL;

    void* mem = malloc(size);
    if(!mem) return NULL;

    stream = sgStreamInitMemory(stream, mem, size, cbBufferFree);
    if(!stream)
    {
        free(mem);
        return NULL;
    }
    return stream;
}
void SG_CALL sgStreamDeinit(SGStream* stream)
{
    if(!stream) return;
    sgStreamClose(stream);
    /*if(stream->close)
        stream->close(stream->data);*/
}

SGStream* SG_CALL sgStreamCreate(SGStreamSeek* seek, SGStreamTell* tell, SGStreamRead* read, SGStreamWrite* write, SGStreamClose* close, SGStreamEOF* eof, void* data)
{
    return sgStreamInit(malloc(sizeof(SGStream)), seek, tell, read, write, close, eof, data);
}
SGStream* SG_CALL sgStreamCreateFile(const char* fname, SGenum fmode)
{
    SGStream* stream = malloc(sizeof(SGStream));
    if(!sgStreamInitFile(stream, fname, fmode))
    {
        free(stream);
        return NULL;
    }
    return stream;
}
SGStream* SG_CALL sgStreamCreateMemory(void* mem, size_t size, SGFree* cbFree)
{
    return sgStreamInitMemory(malloc(sizeof(SGStream)), mem, size, cbFree);
}
SGStream* SG_CALL sgStreamCreateCMemory(const void* mem, size_t size, SGFree* cbFree)
{
    return sgStreamInitCMemory(malloc(sizeof(SGStream)), mem, size, cbFree);
}
SGStream* SG_CALL sgStreamCreateBuffer(size_t size)
{
    SGStream* stream = malloc(sizeof(SGStream));
    if(!sgStreamInitBuffer(stream, size))
    {
        free(stream);
        return NULL;
    }
    return stream;
}
void SG_CALL sgStreamDestroy(SGStream* stream)
{
    sgStreamDeinit(stream);
    free(stream);
}

SGlong SG_CALL sgStreamTellSize(SGStream* stream)
{
    SGlong pos = sgStreamTell(stream);
    if(pos < 0)
        return -1;
    sgStreamSeek(stream, 0, SG_SEEK_END);
    SGlong size = sgStreamTell(stream);
    sgStreamSeek(stream, pos, SG_SEEK_SET);
    return size;
}
SGbool SG_CALL sgStreamSeek(SGStream* stream, SGlong offset, SGenum origin)
{
    if(!stream->seek)
        return SG_FALSE;
    return stream->seek(stream->data, offset, origin);
}
SGlong SG_CALL sgStreamTell(SGStream* stream)
{
    if(!stream->tell)
        return -1;
    return stream->tell(stream->data);
}
SGulong SG_CALL sgStreamRead(SGStream* stream, void* ptr, size_t size, size_t count)
{
    if(!stream->read)
        return 0;
    return stream->read(stream->data, ptr, size, count);
}
SGulong SG_CALL sgStreamWrite(SGStream* stream, const void* ptr, size_t size, size_t count)
{
    if(!stream->write)
        return 0;
    return stream->write(stream->data, ptr, size, count);
}
SGbool SG_CALL sgStreamClose(SGStream* stream)
{
    SGbool ret = SG_TRUE;
    if(stream->close)
        ret = stream->close(stream->data);
    stream->seek = NULL;
    stream->tell = NULL;
    stream->read = NULL;
    stream->write = NULL;
    stream->close = NULL;
    return ret;
}
