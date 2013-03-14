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
#include <siege/util/error.h>
#include <siege/util/string.h>

#include <stdlib.h>

static SGErrorCallback* _sg_errIntCB;
static void*            _sg_errIntData;

static SGErrorCallback* _sg_errUserCB;
static void*            _sg_errUserData;

static void SG_CALL _sgDefaultIntCB(SGenum reason, SGenum level, const char* msg, void* data)
{
    sgLog(level, msg);
    if(level == SG_ERRL_FATAL)
        exit(1);
}
static void SG_CALL _sgDefaultUserCB(SGenum reason, SGenum level, const char* msg, void* data)
{
    sgLog(level, msg);
    if(level == SG_ERRL_FATAL)
        exit(1);
}

void SG_CALL sgiRaisefv(SGenum reason, SGenum level, const char* format, va_list args)
{
    char* str = sgAPrintf(format, args);
    if(_sg_errIntCB)
        _sg_errIntCB(reason, level, str, _sg_errUserData);
    else
        _sgDefaultIntCB(reason, level, str, NULL);
    sgAPrintFree(str);
}
void SG_CALL sgiRaisef(SGenum reason, SGenum level, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    sgiRaisefv(reason, level, format, args);
    va_end(args);
}
void SG_CALL sgiRaise(SGenum reason, SGenum level, const char* msg)
{
    sgiRaisef(reason, level, "%s", msg);
}

void SG_CALL sgiWarningfv(SGenum reason, const char* format, va_list args)
{
    sgiRaisefv(reason, SG_ERRL_WARNING, format, args);
}
void SG_CALL sgiWarningf(SGenum reason, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    sgiWarningfv(reason, format, args);
    va_end(args);
}
void SG_CALL sgiWarning(SGenum reason, const char* msg)
{
    sgiWarningf(reason, "%s", msg);
}

void SG_CALL sgiErrorfv(SGenum reason, const char* format, va_list args)
{
    sgiRaisefv(reason, SG_ERRL_ERROR, format, args);
}
void SG_CALL sgiErrorf(SGenum reason, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    sgiErrorfv(reason, format, args);
    va_end(args);
}
void SG_CALL sgiError(SGenum reason, const char* msg)
{
    sgiErrorf(reason, "%s", msg);
}

void SG_CALL sgiFatalfv(SGenum reason, const char* format, va_list args)
{
    sgiRaisefv(reason, SG_ERRL_FATAL, format, args);
}
void SG_CALL sgiFatalf(SGenum reason, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    sgiFatalfv(reason, format, args);
    va_end(args);
}
void SG_CALL sgiFatal(SGenum reason, const char* msg)
{
    sgiFatalf(reason, "%s", msg);
}

void SG_CALL sgErrorSetIntCallback(SGErrorCallback* cb, void* data)
{
    _sg_errIntCB = cb;
    _sg_errIntData = data;
}
void SG_CALL sgErrorSetUserCallback(SGErrorCallback* cb, void* data)
{
    _sg_errUserCB = cb;
    _sg_errUserData = data;
}

void SG_CALL sgRaisefv(SGenum reason, SGenum level, const char* format, va_list args)
{
    char* str = sgAPrintf(format, args);
    if(_sg_errUserCB)
        _sg_errUserCB(reason, level, str, _sg_errUserData);
    else
        _sgDefaultUserCB(reason, level, str, NULL);
    sgAPrintFree(str);
}
void SG_CALL sgRaisef(SGenum reason, SGenum level, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    sgRaisefv(reason, level, format, args);
    va_end(args);
}
void SG_CALL sgRaise(SGenum reason, SGenum level, const char* msg)
{
    sgRaisef(reason, level, "%s", msg);
}

void SG_CALL sgWarningfv(SGenum reason, const char* format, va_list args)
{
    sgRaisefv(reason, SG_ERRL_WARNING, format, args);
}
void SG_CALL sgWarningf(SGenum reason, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    sgWarningfv(reason, format, args);
    va_end(args);
}
void SG_CALL sgWarning(SGenum reason, const char* msg)
{
    sgWarningf(reason, "%s", msg);
}

void SG_CALL sgErrorfv(SGenum reason, const char* format, va_list args)
{
    sgRaisefv(reason, SG_ERRL_ERROR, format, args);
}
void SG_CALL sgErrorf(SGenum reason, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    sgErrorfv(reason, format, args);
    va_end(args);
}
void SG_CALL sgError(SGenum reason, const char* msg)
{
    sgErrorf(reason, "%s", msg);
}

void SG_CALL sgFatalfv(SGenum reason, const char* format, va_list args)
{
    sgRaisefv(reason, SG_ERRL_FATAL, format, args);
}
void SG_CALL sgFatalf(SGenum reason, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    sgFatalfv(reason, format, args);
    va_end(args);
}
void SG_CALL sgFatal(SGenum reason, const char* msg)
{
    sgFatalf(reason, "%s", msg);
}
