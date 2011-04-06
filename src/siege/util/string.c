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

size_t SG_EXPORT sgStrlen32(const SGdchar* text)
{
	const SGdchar* ptr = text;
	while(*ptr)
		ptr++;
	return ptr - text;
}
SGdchar* SG_EXPORT sgLineEnd32(const SGdchar* text)
{
	if(text == NULL)
		return NULL;

	while(*text != '\r' && *text != '\n' && *text != '\0')
		text++;

	return (SGdchar*)text;
}
SGuint SG_EXPORT sgLineLength32(const SGdchar* text)
{
	return sgLineEnd32(text) - text;
}
SGdchar* SG_EXPORT sgNextLine32(const SGdchar* text)
{
	if(text == NULL)
		return NULL;

	SGdchar* end = sgLineEnd32(text);
	if(end[0] == 0)
		return NULL;

	if(end[0] == '\r' && end[1] == '\n')
		return end + 2;
	return end + 1;
}
SGuint SG_EXPORT sgNumLines32(const SGdchar* text)
{
	SGuint numlines = 0;

	const SGdchar* ptr = text;
	while(ptr != NULL)
	{
		ptr = sgNextLine32(ptr);
		numlines++;
	}
	return numlines;
}
