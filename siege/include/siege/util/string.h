#ifndef __SIEGE_UTIL_STRING_H__
#define __SIEGE_UTIL_STRING_H__

#include "../common.h"

#include <stdarg.h>

char* SG_EXPORT SG_HINT_PRINTF(1, 2) sgPrintf(char* format, ...);
char* SG_EXPORT SG_HINT_PRINTF(1, 0) sgPrintfv(char* format, va_list args);

char* SG_EXPORT sgLineEnd(char* text);
SGuint SG_EXPORT sgLineLength(char* text);
char* SG_EXPORT sgNextLine(char* text);
SGuint SG_EXPORT sgNumLines(char* text);

/// \todo TODO
void SG_EXPORT sgCharToUTF32(char* text, SGuint textlen, SGdchar* str);

#endif // __SIEGE_UTIL_STRING_H__
