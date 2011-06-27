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
#include <string.h>

// MinGW thinks it's smart and uses its own variant of vswprintf...
#define __STRICT_ANSI__
#include <stdio.h>
#include <wchar.h>

int vswprintf(wchar_t *wcs, size_t maxlen, const wchar_t *format, va_list args);

SGbool SG_EXPORT _sgStringInit(void)
{
	_sg_strBufLen = 0;
	_sg_strBuf = NULL;
	return SG_TRUE;
}
SGbool SG_EXPORT _sgStringDeinit(void)
{
	if(_sg_strBuf)
		free(_sg_strBuf);
	return SG_TRUE;
}

wchar_t* SG_EXPORT sgPrintfW(const wchar_t* format, ...)
{
    va_list args;
    va_start(args, format);
    wchar_t* str = sgPrintfvW(format, args);
    va_end(args);
    return str;
}
wchar_t* SG_EXPORT sgPrintfvW(const wchar_t* format, va_list args)
{
    int ret = 0;
    _sg_strBufLen = 0;

    do
    {
        _sg_strBufLen += 256;
        _sg_strBuf = realloc(_sg_strBuf, _sg_strBufLen * sizeof(wchar_t));
        ret = vswprintf((wchar_t*)_sg_strBuf, _sg_strBufLen, format, args);
    }
    while(ret >= _sg_strBufLen);

    if(ret < 0)
        return NULL;

    return (wchar_t*)_sg_strBuf;
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

	char* ret = strpbrk(text, "\r\n");
	if(ret == NULL)
		ret = (char*)text + strlen(text);
	return ret;
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

SGdchar* SG_EXPORT sgLineEndU32(const SGdchar* text)
{
	if(text == NULL)
		return NULL;

	while(*text != '\r' && *text != '\n' && *text != '\0')
		text++;

	return (SGdchar*)text;
}
SGuint SG_EXPORT sgLineLengthU32(const SGdchar* text)
{
	return sgLineEndU32(text) - text;
}
SGdchar* SG_EXPORT sgNextLineU32(const SGdchar* text)
{
	if(text == NULL)
		return NULL;

	SGdchar* end = sgLineEndU32(text);
	if(end[0] == 0)
		return NULL;

	if(end[0] == '\r' && end[1] == '\n')
		return end + 2;
	return end + 1;
}
SGuint SG_EXPORT sgNumLinesU32(const SGdchar* text)
{
	SGuint numlines = 0;

	const SGdchar* ptr = text;
	while(ptr != NULL)
	{
		ptr = sgNextLineU32(ptr);
		numlines++;
	}
	return numlines;
}
