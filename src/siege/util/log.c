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
#include <siege/util/log.h>
#include <siege/util/string.h>

#include <stdlib.h>
#include <stdio.h>

static const char* _sg_logLevelH[] = {
    "DEBUG",
    "INFO",
    "INIT",
    "WARNING",
    "ERROR",
    "FATAL",
    NULL
};
static const char* _sg_logLevelL[] = {
    "debug",
    "info",
    "init",
    "warning",
    "error",
    "fatal",
    NULL
};

static SGLogCallback* _sg_logCB;
static void* _sg_logData;
static SGenum _sg_logLevel = SG_LOGL_DEFAULT;

static void SG_CALL _sgLogDefaultCallback(SGLogContext* ctx, SGenum level, const char* msg, void* data)
{
    fflush(stdout);
    fprintf(stderr, "%s: ", sgLogGetLevelString(level, SG_TRUE));
    if(level == SG_LOGL_DEBUG && ctx)
        fprintf(stderr, "%s:%s(%u): ", ctx->file, ctx->func, ctx->line);
    fprintf(stderr, "%s\n", msg);
    fflush(stderr);
}

SGLogContext SG_CALL sgLogContext(const char* file, const char* func, SGuint line)
{
    SGLogContext ctx;
    ctx.file = file;
    ctx.func = func;
    ctx.line = line;
    return ctx;
}

void SG_CALL sgLogSetCallback(SGLogCallback* cb, void* data)
{
    _sg_logCB = cb;
    _sg_logData = data;
}

char* SG_CALL sgLogGetLevelString(SGenum level, SGbool upper)
{
    if(level >= SG_LOGL_NUM)
        return NULL; /* TODO: should we return an empty string or "???" or something instead? */
    return (char*)(upper ? _sg_logLevelH : _sg_logLevelL)[level];
}

void SG_CALL sgLogSetMinLevel(SGenum level)
{
    _sg_logLevel = level;
}
SGenum SG_CALL sgLogGetMinLevel(void)
{
    return _sg_logLevel;
}

void SG_CALL sgLogCtxfv(SGLogContext ctx, SGenum level, const char* format, va_list args)
{
    if(level < _sg_logLevel) return;
    char* str = sgAPrintfv(format, args);
    if(!_sg_logCB)
        _sgLogDefaultCallback(&ctx, level, str, NULL);
    else
        _sg_logCB(&ctx, level, str, _sg_logData);
    sgAPrintFree(str);
}
void SG_CALL sgLogCtxf(SGLogContext ctx, SGenum level, const char* format, ...)
{
    if(level < _sg_logLevel) return;
    va_list args;
    va_start(args, format);
    sgLogCtxfv(ctx, level, format, args);
    va_end(args);
}
void SG_CALL sgLogCtx(SGLogContext ctx, SGenum level, const char* msg)
{
    if(level < _sg_logLevel) return;
    sgLogCtxf(ctx, level, "%s", msg);
}

void SG_CALL sgLogfv(SGenum level, const char* format, va_list args)
{
    if(level < _sg_logLevel) return;
    char* str = sgAPrintfv(format, args);
    if(!_sg_logCB)
        _sgLogDefaultCallback(NULL, level, str, NULL);
    else
        _sg_logCB(NULL, level, str, _sg_logData);
    sgAPrintFree(str);
}
void SG_CALL sgLogf(SGenum level, const char* format, ...)
{
    if(level < _sg_logLevel) return;
    va_list args;
    va_start(args, format);
    sgLogfv(level, format, args);
    va_end(args);
}
void SG_CALL sgLog(SGenum level, const char* msg)
{
    if(level < _sg_logLevel) return;
    sgLogf(level, "%s", msg);
}
