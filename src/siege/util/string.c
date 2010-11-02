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
#include <siege/util/string.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

SGbool SG_EXPORT _sgStringInit(void)
{
    _sg_strBufLen = 0;
    _sg_strBuf = NULL;
    return SG_TRUE;
}
SGbool SG_EXPORT _sgStringDeinit(void)
{
    free(_sg_strBuf);
    return SG_TRUE;
}

char* SG_EXPORT sgPrintf(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    char* str = sgPrintfv(format, args);
    va_end(args);
    return str;
}
char* SG_EXPORT sgPrintfv(const char* format, va_list args)
{
    int ret = 0;
    _sg_strBufLen = 0;

    do
    {
        _sg_strBufLen += 256;
        _sg_strBuf = realloc(_sg_strBuf, _sg_strBufLen);
        ret = vsnprintf(_sg_strBuf, _sg_strBufLen, format, args);
    }
    while(ret >= _sg_strBufLen);

    if(ret < 0)
        return NULL;

    return _sg_strBuf;
}

char* SG_EXPORT sgLineEnd(const char* text)
{
    if(text == NULL)
        return NULL;

    return strpbrk(text, "\r\n");
}
SGuint SG_EXPORT sgLineLength(const char* text)
{
    return sgLineEnd(text) - text;
}
char* SG_EXPORT sgNextLine(const char* text)
{
    if(text == NULL)
        return NULL;

    char* brk = strpbrk(text, "\r\n");
    if(brk == NULL)
        return NULL;
    if((brk[0] == '\r') && (brk[1] == '\n'))
        return brk + 2;
    return brk + 1;
}
SGuint SG_EXPORT sgNumLines(const char* text)
{
    SGuint numlines = 0;

    const char* ptr = text;
    while(ptr != NULL)
    {
        ptr = sgNextLine(ptr);
        numlines++;
    }
    return numlines;
}
/// \todo TODO
void SG_EXPORT sgCharToUTF32(const char* text, SGuint textlen, SGdchar* str)
{
    size_t i;
    for(i = 0; i < textlen; i++)
        str[i] = text[i];
}
