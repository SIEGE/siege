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

#ifndef __SIEGE_UTIL_LOG_H__
#define __SIEGE_UTIL_LOG_H__

#include "../common.h"
#include "debug.h"

#include <stdarg.h>

#define SG_LOGL_DEBUG    0
#define SG_LOGL_INFO     1
#define SG_LOGL_INIT     2
#define SG_LOGL_WARNING  3
#define SG_LOGL_ERROR    4
#define SG_LOGL_FATAL    5

#define SG_LOGL_NUM (SG_LOGL_FATAL + 1)

#define SG_LOGL_DEFAULT SG_LOGL_INIT

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGLogContext
{
    const char* file;
    const char* func;
    SGuint line;
} SGLogContext;

SGLogContext SG_CALL sgLogContext(const char* file, const char* func, SGuint line);

#define SG_LOG_CONTEXT() sgLogContext(SG_DEBUG_FILE, SG_DEBUG_FUNCTION, SG_DEBUG_LINE)

typedef void SG_CALL (SGLogCallback)(SGLogContext* ctx, SGenum level, const char* msg, void* data);

void SG_CALL sgLogSetCallback(SGLogCallback* cb, void* data);

char* SG_CALL sgLogGetLevelString(SGenum level, SGbool upper);

void SG_CALL sgLogSetMinLevel(SGenum level);
SGenum SG_CALL sgLogGetMinLevel(void);

void SG_CALL sgLogCtxfv(SGLogContext ctx, SGenum level, const char* format, va_list args);
void SG_CALL sgLogCtxf(SGLogContext ctx, SGenum level, const char* format, ...);
void SG_CALL sgLogCtx(SGLogContext ctx, SGenum level, const char* msg);

void SG_CALL sgLogfv(SGenum level, const char* format, va_list args);
void SG_CALL sgLogf(SGenum level, const char* format, ...);
void SG_CALL sgLog(SGenum level, const char* msg);

#define SG_LOGF(level, ...) sgLogCtxf(SG_LOG_CONTEXT(), (level), __VA_ARGS__)
#define SG_LOG(level, msg) sgLogCtx(SG_LOG_CONTEXT(), (level), (msg))

#ifdef SG_DEBUG
#define SG_LOG_DEBUGF(...) SG_LOGF(SG_LOGL_DEBUG, __VA_ARGS__)
#define SG_LOG_DEBUG(msg) SG_LOG(SG_LOGL_DEBUG, msg)
#else
#define SG_LOG_DEBUGF(...)
#define SG_LOG_DEBUG(msg)
#endif /* SG_DEBUG */

#define SG_LOG_INFOF(...) SG_LOGF(SG_LOGL_INFO, __VA_ARGS__)
#define SG_LOG_INFO(msg) SG_LOG(SG_LOGL_INFO, msg)

#define SG_LOG_INITF(...) SG_LOGF(SG_LOGL_INIT, __VA_ARGS__)
#define SG_LOG_INIT(msg) SG_LOG(SG_LOGL_INIT, msg)

#define SG_LOG_WARNINGF(...) SG_LOGF(SG_LOGL_WARNING, __VA_ARGS__)
#define SG_LOG_WARNING(msg) SG_LOG(SG_LOGL_WARNING, msg)

#define SG_LOG_ERRORF(...) SG_LOGF(SG_LOGL_ERROR, __VA_ARGS__)
#define SG_LOG_ERROR(msg) SG_LOG(SG_LOGL_ERROR, msg)

#define SG_LOG_FATALF(...) SG_LOGF(SG_LOGL_FATAL, __VA_ARGS__)
#define SG_LOG_FATAL(msg) SG_LOG(SG_LOGL_FATAL, msg)

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_LOG_H__
