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

void SG_CALL sgLogfv(SGenum level, const char* format, va_list args)
{
    if(!_sg_logCB)
    {
        fprintf(stderr, "%s: ", sgLogGetLevelString(level, SG_TRUE));
        vfprintf(stderr, format, args);
        fprintf(stderr, "\n");
        fflush(stderr);
        return;
    }
    char* str = sgAPrintfv(format, args);
    _sg_logCB(level, str, _sg_logData);
    sgAPrintFree(str);
}
void SG_CALL sgLogf(SGenum level, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    sgLogfv(level, format, args);
    va_end(args);
}
void SG_CALL sgLog(SGenum level, const char* msg)
{
    sgLogf(level, "%s", msg);
}
