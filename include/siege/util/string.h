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

#ifndef __SIEGE_UTIL_STRING_H__
#define __SIEGE_UTIL_STRING_H__

#include "../common.h"

#include <stdarg.h>

#ifdef SG_BUILD_LIBRARY
size_t _sg_strBufLen;
char* _sg_strBuf;
#endif // SG_BUILD_LIBRARY

SGbool SG_EXPORT _sgStringInit(void);
SGbool SG_EXPORT _sgStringDeinit(void);

wchar_t* SG_EXPORT sgPrintfW(const wchar_t* format, ...);
wchar_t* SG_EXPORT sgPrintfvW(const wchar_t* format, va_list args);

char* SG_EXPORT SG_HINT_PRINTF(1, 2) sgPrintf(const char* format, ...);
char* SG_EXPORT SG_HINT_PRINTF(1, 0) sgPrintfv(const char* format, va_list args);

char* SG_EXPORT sgLineEnd(const char* text);
SGuint SG_EXPORT sgLineLength(const char* text);
char* SG_EXPORT sgNextLine(const char* text);
SGuint SG_EXPORT sgNumLines(const char* text);

SGdchar* SG_EXPORT sgLineEnd32(const SGdchar* text);
SGuint SG_EXPORT sgLineLength32(const SGdchar* text);
SGdchar* SG_EXPORT sgNextLine32(const SGdchar* text);
SGuint SG_EXPORT sgNumLines32(const SGdchar* text);
#endif // __SIEGE_UTIL_STRING_H__
