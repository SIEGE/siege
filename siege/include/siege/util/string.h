#ifndef __SIEGE_UTIL_STRING_H__
#define __SIEGE_UTIL_STRING_H__

#include "../common.h"

#include <stdarg.h>

char* sgPrintf(char* format, ...);
char* sgPrintfv(char* format, va_list args);

char* sgLineEnd(char* text);
SGuint sgLineLength(char* text);
char* sgNextLine(char* text);
SGuint sgNumLines(char* text);

/// \todo TODO
void sgCharToUTF32(char* text, SGuint textlen, SGdchar* str);

#endif // __SIEGE_UTIL_STRING_H__
