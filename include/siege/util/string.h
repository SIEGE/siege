/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "license.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
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

// has to be done to avoid a doxygen bug
#define _SG_PRINTF SG_HINT_PRINTF(1, 2)
#define _SG_VPRINTF SG_HINT_PRINTF(1, 0)

char* SG_EXPORT _SG_PRINTF sgPrintf(const char* format, ...);
char* SG_EXPORT _SG_VPRINTF sgPrintfv(const char* format, va_list args);

#undef _SG_PRINTF
#undef _SG_VPRINTF

const char* SG_EXPORT sgLineEnd(const char* text);
SGuint SG_EXPORT sgLineLength(const char* text);
const char* SG_EXPORT sgNextLine(const char* text);
SGuint SG_EXPORT sgNumLines(const char* text);

/// \todo TODO
void SG_EXPORT sgCharToUTF32(const char* text, SGuint textlen, SGdchar* str);

#endif // __SIEGE_UTIL_STRING_H__
