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

char* SG_EXPORT _SG_PRINTF sgPrintf(char* format, ...);
char* SG_EXPORT _SG_VPRINTF sgPrintfv(char* format, va_list args);

#undef _SG_PRINTF
#undef _SG_VPRINTF

char* SG_EXPORT sgLineEnd(char* text);
SGuint SG_EXPORT sgLineLength(char* text);
char* SG_EXPORT sgNextLine(char* text);
SGuint SG_EXPORT sgNumLines(char* text);

/// \todo TODO
void SG_EXPORT sgCharToUTF32(char* text, SGuint textlen, SGdchar* str);

#endif // __SIEGE_UTIL_STRING_H__
