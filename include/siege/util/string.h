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

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#define SG_OCTDIGITS "01234567"
#define SG_DECDIGITS SG_OCTDIGITS "89"
#define SG_HEXDIGITS "ABCDEFabcdef" SG_DECDIGITS
#define SG_ALPHA     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define SG_ALNUM     SG_ALPHA SG_DECDIGITS

char* _sgStringAppend(char** str, size_t* len, size_t* mem, const char* what);

// wprintf, locked with a mutex for thread-safety
size_t SG_EXPORT sgPrintfW(const wchar_t* format, ...);
size_t SG_EXPORT sgPrintfvW(const wchar_t* format, va_list args);

// printf, locked with a mutex for thread-safety
size_t SG_EXPORT SG_HINT_PRINTF(1, 2) sgPrintf(const char* format, ...);
size_t SG_EXPORT SG_HINT_PRINTF(1, 0) sgPrintfv(const char* format, va_list args);

size_t SG_EXPORT sgSPrintfW(wchar_t* buf, size_t buflen, const wchar_t* format, ...);
size_t SG_EXPORT sgSPrintfvW(wchar_t* buf, size_t buflen, const wchar_t* format, va_list args);

wchar_t* SG_EXPORT sgAPrintfW(const wchar_t* format, ...);
wchar_t* SG_EXPORT sgAPrintfvW(const wchar_t* format, va_list args);

size_t SG_EXPORT SG_HINT_PRINTF(3, 4) sgSPrintf(char* buf, size_t buflen, const char* format, ...);
size_t SG_EXPORT SG_HINT_PRINTF(3, 0) sgSPrintfv(char* buf, size_t buflen, const char* format, va_list args);

char* SG_EXPORT SG_HINT_PRINTF(1, 2) sgAPrintf(const char* format, ...);
char* SG_EXPORT SG_HINT_PRINTF(1, 0) sgAPrintfv(const char* format, va_list args);

void SG_EXPORT sgAPrintFree(void* str);

SGbool SG_EXPORT sgStartsWith(const char* text, const char* what);
char* SG_EXPORT sgSpaceEnd(const char* text);
char* SG_EXPORT sgLineEnd(const char* text);
SGuint SG_EXPORT sgLineLength(const char* text);
char* SG_EXPORT sgNextLine(const char* text);
SGuint SG_EXPORT sgNumLines(const char* text);

SGdchar* SG_EXPORT sgLineEndU32(const SGdchar* text);
SGuint SG_EXPORT sgLineLengthU32(const SGdchar* text);
SGdchar* SG_EXPORT sgNextLineU32(const SGdchar* text);
SGuint SG_EXPORT sgNumLinesU32(const SGdchar* text);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __SIEGE_UTIL_STRING_H__
