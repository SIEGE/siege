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

static SGbool SG_EXPORT cbFileSeek(void* stream, SGlong offset, SGenum origin)
{
    int corigin;
    switch(origin)
    {
        case SG_SEEK_SET: corigin = SEEK_SET; break;
        case SG_SEEK_CUR: corigin = SEEK_CUR; break;
        case SG_SEEK_END: corigin = SEEK_END; break;
        default: return SG_FALSE;
    }
    return !fseek(stream, offset, corigin);
}
static SGlong SG_EXPORT cbFileTell(void* stream)
{
    return ftell(stream);
}
static SGulong SG_EXPORT cbFileRead(void* stream, void* ptr, size_t size, size_t count)
{
    return fread(ptr, size, count, stream);
}
static SGulong SG_EXPORT cbFileWrite(void* stream, const void* ptr, size_t size, size_t count)
{
    return fwrite(ptr, size, count, stream);
}
static SGbool SG_EXPORT cbFileClose(void* stream)
{
    return !fclose(stream);
}

typedef struct MemoryInfo
{
    SGubyte* ptr;
    SGubyte* cur;
    SGubyte* end;

    SGFree* free;
} MemoryInfo;

static SGbool SG_EXPORT cbMemorySeek(void* stream, SGlong offset, SGenum origin)
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
static SGlong SG_EXPORT cbMemoryTell(void* stream)
{
    MemoryInfo* minfo = stream;
    return minfo->cur - minfo->ptr;
}
static SGulong SG_EXPORT cbMemoryRead(void* stream, void* ptr, size_t size, size_t count)
{
    MemoryInfo* minfo = stream;
    size_t avail = minfo->end - minfo->cur;
    if(avail < size * count)
        count = avail / size;

    memcpy(ptr, minfo->cur, size * count);
    minfo->cur += size * count;
    return count;
}
static SGulong SG_EXPORT cbMemoryWrite(void* stream, const void* ptr, size_t size, size_t count)
{
    MemoryInfo* minfo = stream;
    size_t avail = minfo->end - minfo->cur;
    if(avail < size * count)
        count = avail / size;

    memcpy(minfo->cur, ptr, size * count);
    minfo->cur += size * count;
    return count;
}
static SGbool SG_EXPORT cbMemoryClose(void* stream)
{
    MemoryInfo* minfo = stream;
    if(minfo->free)
        minfo->free(minfo->ptr);
    free(minfo);
    return SG_TRUE;
}

static void SG_EXPORT cbBufferFree(void* ptr)
{
    free(ptr);
}

SGStream* SG_EXPORT sgStreamCreate(SGStreamSeek* seek, SGStreamTell* tell, SGStreamRead* read, SGStreamWrite* write, SGStreamClose* close, void* data)
{
    SGStream* stream = malloc(sizeof(SGStream));
    if(!stream) return NULL;

    stream->seek = seek;
    stream->tell = tell;
    stream->read = read;
    stream->write = write;
    stream->close = close;

    stream->data = data;

    return stream;
}
SGStream* SG_EXPORT sgStreamCreateFile(const char* fname, const char* mode)
{
    FILE* file = fopen(fname, mode);
    if(!file) return NULL;

    SGStream* stream = sgStreamCreate(cbFileSeek, cbFileTell, cbFileRead, cbFileWrite, cbFileClose, file);
    if(!stream)
    {
        fclose(file);
        return NULL;
    }
    return stream;
}
SGStream* SG_EXPORT sgStreamCreateMemory(void* mem, size_t size, SGFree* cbfree)
{
    MemoryInfo* minfo = malloc(sizeof(MemoryInfo));
    if(!minfo) return NULL;

    minfo->ptr = mem;
    minfo->cur = minfo->ptr;
    minfo->end = minfo->ptr + size;

    minfo->free = free;

    SGStream* stream = sgStreamCreate(cbMemorySeek, cbMemoryTell, cbMemoryRead, cbMemoryWrite, cbMemoryClose, minfo);
    if(!stream)
    {
        free(minfo);
        return NULL;
    }
    return stream;
}
SGStream* SG_EXPORT sgStreamCreateCMemory(const void* mem, size_t size, SGFree* cbfree)
{
    MemoryInfo* minfo = malloc(sizeof(MemoryInfo));
    if(!minfo) return NULL;

    minfo->ptr = (void*)mem;
    minfo->cur = minfo->ptr;
    minfo->end = minfo->ptr + size;

    minfo->free = free;

    SGStream* stream = sgStreamCreate(cbMemorySeek, cbMemoryTell, cbMemoryRead, NULL, cbMemoryClose, minfo);
    if(!stream)
    {
        free(minfo);
        return NULL;
    }
    return stream;
}
SGStream* SG_EXPORT sgStreamCreateBuffer(size_t size)
{
    void* mem = malloc(size);
    if(!mem) return NULL;

    SGStream* stream = sgStreamCreateMemory(mem, size, cbBufferFree);
    if(!stream)
    {
        free(mem);
        return NULL;
    }
    return stream;
}
void SG_EXPORT sgStreamDestroy(SGStream* stream)
{
    if(!stream) return;
    if(stream->close)
        stream->close(stream->data);
    free(stream);
}

SGbool SG_EXPORT sgStreamSeek(SGStream* stream, SGlong offset, SGenum origin)
{
    if(!stream->seek)
        return SG_FALSE;
    return stream->seek(stream->data, offset, origin);
}
SGlong SG_EXPORT sgStreamTell(SGStream* stream)
{
    if(!stream->tell)
        return -1;
    return stream->tell(stream->data);
}
SGulong SG_EXPORT sgStreamRead(SGStream* stream, void* ptr, size_t size, size_t count)
{
    if(!stream->read)
        return 0;
    return stream->read(stream->data, ptr, size, count);
}
SGulong SG_EXPORT sgStreamWrite(SGStream* stream, const void* ptr, size_t size, size_t count)
{
    if(!stream->write)
        return 0;
    return stream->write(stream->data, ptr, size, count);
}
SGbool SG_EXPORT sgStreamClose(SGStream* stream)
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
