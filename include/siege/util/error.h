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

#ifndef __SIEGE_UTIL_ERROR_H__
#define __SIEGE_UTIL_ERROR_H__

#include "../common.h"
#include "log.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#define SG_ERRL_WARNING  SG_LOGL_WARNING
#define SG_ERRL_ERROR    SG_LOGL_ERROR
#define SG_ERRL_FATAL    SG_LOGL_FATAL

typedef void SG_CALL (SGErrorCallback)(SGenum reason, SGenum level, const char* msg, void* data);

void SG_CALL sgErrorSetCallback(SGErrorCallback* cb, void* data);

void SG_CALL sgRaisefv(SGenum reason, SGenum level, const char* format, va_list args);
void SG_CALL sgRaisef(SGenum reason, SGenum level, const char* format, ...);
void SG_CALL sgRaise(SGenum reason, SGenum level, const char* msg);

void SG_CALL sgWarningfv(SGenum reason, const char* format, va_list args);
void SG_CALL sgWarningf(SGenum reason, const char* format, ...);
void SG_CALL sgWarning(SGenum reason, const char* msg);

void SG_CALL sgErrorfv(SGenum reason, const char* format, va_list args);
void SG_CALL sgErrorf(SGenum reason, const char* format, ...);
void SG_CALL sgError(SGenum reason, const char* msg);

void SG_CALL sgFatalfv(SGenum reason, const char* format, va_list args);
void SG_CALL sgFatalf(SGenum reason, const char* format, ...);
void SG_CALL sgFatal(SGenum reason, const char* msg);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_ERROR_H__
