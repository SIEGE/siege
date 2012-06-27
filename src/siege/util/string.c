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
#include <siege/util/thread/thread.h>
#include <siege/util/thread/mutex.h>

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <stdio.h>
#include <wchar.h>

#ifdef __MINGW32__
/*
 * MinGW thinks it's smart and uses its own variant of vswprintf, though
 * I suppose it's mostly Microsoft's fault since this is the variant
 * present in WinAPI...
 *
 * Either way, because of this problem, we we have to use this
 * workaround...
 */
static int ugly_vswprintf_hack(wchar_t* wcs, size_t maxlen, const wchar_t* format, va_list args)
{
    int len;
    va_list argcpy;
    va_copy(argcpy, args);
    len = _vscwprintf(format, argcpy);
    va_end(argcpy);

    if(maxlen < len + 1)
        return len;
    return vswprintf(wcs, format, args);
}
#else /* and if it's not MinGW, we need a different hack... UGH */
static int ugly_vswprintf_hack(wchar_t* wcs, size_t maxlen, const wchar_t* format, va_list args)
{
    size_t buflen = 32;
    wchar_t* buf = NULL;
    int len;
    va_list argcpy;
    do
    {
        buflen <<= 1;
        buf = realloc(buf, buflen * sizeof(wchar_t));
        va_copy(argcpy, args);
        len = vswprintf(buf, buflen, format, argcpy);
        va_end(argcpy);
        if(len < 0)
        {
            free(buf);
            return -1;
        }
    }
    while(len == -1 || len == buflen - 1);
    free(buf);

    if(maxlen < len + 1)
        return len;
    return vswprintf(wcs, maxlen, format, args);
}
#endif /* __MINGW32__ */
#define vswprintf ugly_vswprintf_hack

/*
 * Windows' snprintf is non-conforming in that it returns -1 instead of
 * the to-be size if the buffer is not large enough.
 *
 * MinGW gets around this problem, but at least some other compilers do
 * not. What follows is a super-ugly workaround.
 */
#if defined(__WIN32__) && !defined(__MINGW32__)
static int ugly_vsnprintf_hack(char* str, size_t size, const char* format, va_list args)
{
    int len;
    va_list argcpy;
    va_copy(argcpy, args);
    len = _vscprintf(format, argcpy);
    va_end(argcpy);

    if(size < len + 1)
        return len;
    return vsnprintf(str, size, format, args);
}
#define vsnprintf ugly_vsnprintf_hack
#endif /* defined(__WIN32__) && !defined(__MINGW32__) */

char* _sgStringAppend(char** str, size_t* len, size_t* mem, const char* what)
{
    size_t wlen = strlen(what);
    if(*len + wlen >= *mem)
    {
        *mem = *mem ? *mem << 1 : 32;
        *str = realloc(*str, *mem);
    }
    memcpy(*str + *len, what, wlen);
    *len += wlen;
    (*str)[*len] = 0;
    return *str;
}

size_t _sgStrbufAppend(size_t sz, size_t pos, void* out, size_t outlen, const void* in, size_t inlen)
{
    if(pos + 1 >= outlen)
        return inlen;

    memcpy(((char*)out) + pos * sz, in, SG_MIN(outlen - pos - 1, inlen) * sz);
    return inlen;
}

static SGMutex* _sg_strMutex;

static void SG_EXPORT _sgStringDeinit(void)
{
    sgMutexDestroy(_sg_strMutex);
}
/*
 * Will have to solve the race condition regarding two sgPrintf's
 * getting called for the first time, at the same time...
 *
 * Maybe a global mutex for just this purpose?
 */
static void SG_EXPORT _sgStringInit(void)
{
    sgThreadAtExit(_sgStringDeinit);
    _sg_strMutex = sgMutexCreate();
}

size_t SG_EXPORT sgPrintfW(const wchar_t* format, ...)
{
    size_t ret;
    va_list args;
    va_start(args, format);
    ret = sgPrintfvW(format, args);
    va_end(args);
    return ret;
}
size_t SG_EXPORT sgPrintfvW(const wchar_t* format, va_list args)
{
    if(!_sg_strMutex)
        _sgStringInit();
    sgMutexLock(_sg_strMutex);
    size_t ret = vwprintf(format, args);
    sgMutexUnlock(_sg_strMutex);
    return ret;
}
size_t SG_EXPORT SG_HINT_PRINTF(1, 2) sgPrintf(const char* format, ...)
{
    size_t ret;
    va_list args;
    va_start(args, format);
    ret = sgPrintfv(format, args);
    va_end(args);
    return ret;
}
size_t SG_EXPORT SG_HINT_PRINTF(1, 0) sgPrintfv(const char* format, va_list args)
{
    if(!_sg_strMutex)
        _sgStringInit();
    sgMutexLock(_sg_strMutex);
    size_t ret = vprintf(format, args);
    sgMutexUnlock(_sg_strMutex);
    return ret;
}

size_t SG_EXPORT sgSPrintfW(wchar_t* buf, size_t buflen, const wchar_t* format, ...)
{
    size_t ret;
    va_list args;
    va_start(args, format);
    ret = sgSPrintfvW(buf, buflen, format, args);
    va_end(args);
    return ret;
}
size_t SG_EXPORT sgSPrintfvW(wchar_t* buf, size_t buflen, const wchar_t* format, va_list args)
{
    int ret = vswprintf(buf, buflen, format, args);
    if(ret < 0)
        return 0;
    return ret;
}

wchar_t* SG_EXPORT sgAPrintfW(const wchar_t* format, ...)
{
    wchar_t* str;
    va_list args;
    va_start(args, format);
    str = sgAPrintfvW(format, args);
    va_end(args);
    return str;
}
wchar_t* SG_EXPORT sgAPrintfvW(const wchar_t* format, va_list args)
{
    wchar_t buf;
    size_t len;

    va_list argcpy;
    va_copy(argcpy, args);
    len = sgSPrintfvW(&buf, 1, format, argcpy);
    va_end(argcpy);

    wchar_t* str = malloc((len + 1) * sizeof(wchar_t));
    if(!str)
        return NULL;
    sgSPrintfvW(str, len + 1, format, args);

    return str;
}

size_t SG_EXPORT SG_HINT_PRINTF(3, 4) sgSPrintf(char* buf, size_t buflen, const char* format, ...)
{
    size_t ret;
	va_list args;
	va_start(args, format);
    ret = sgSPrintfv(buf, buflen, format, args);
	va_end(args);
    return ret;
}
size_t SG_EXPORT SG_HINT_PRINTF(3, 0) sgSPrintfv(char* buf, size_t buflen, const char* format, va_list args)
{
    int ret = vsnprintf(buf, buflen, format, args);
    if(ret < 0)
        return 0;
    return ret;
}

char* SG_EXPORT SG_HINT_PRINTF(1, 2) sgAPrintf(const char* format, ...)
{
    char* str;
	va_list args;
	va_start(args, format);
    str = sgAPrintfv(format, args);
	va_end(args);
    return str;
}
char* SG_EXPORT SG_HINT_PRINTF(1, 0) sgAPrintfv(const char* format, va_list args)
{
    char buf;

    va_list argcpy;
    va_copy(argcpy, args);
    size_t len = sgSPrintfv(&buf, 1, format, argcpy);
    va_end(argcpy);

    char* str = malloc(len + 1);
    if(!str)
        return NULL;
    sgSPrintfv(str, len + 1, format, args);

    return str;
}

void SG_EXPORT sgAPrintFree(void* str)
{
    free(str);
}

SGbool SG_EXPORT sgStartsWith(const char* text, const char* what)
{
    return !strncmp(text, what, strlen(what));
}
char* SG_EXPORT sgSpaceEnd(const char* text)
{
    if(!text)
        return NULL;

    while(isspace(*text))
        text++;
    return (char*)text;
}
char* SG_EXPORT sgLineEnd(const char* text)
{
    if(!text) return NULL;
    return (char*)text + strcspn(text, "\r\n");
}
SGuint SG_EXPORT sgLineLength(const char* text)
{
	return sgLineEnd(text) - text;
}
char* SG_EXPORT sgNextLine(const char* text)
{
    if(!text) return NULL;

	char* brk = strpbrk(text, "\r\n");
    if(!brk)
		return NULL;
	if((brk[0] == '\r') && (brk[1] == '\n'))
		return brk + 2;
	return brk + 1;
}
SGuint SG_EXPORT sgNumLines(const char* text)
{
	SGuint numlines = 0;

	const char* ptr = text;
    while(ptr)
	{
		ptr = sgNextLine(ptr);
		numlines++;
	}
	return numlines;
}

/*size_t SG_EXPORT sgStrcspnU32(const SGdchar* text, const SGdchar* sel)
{
    size_t i, j;
    for(i = 0; text[i]; i++)
        for(j = 0; sel[j]; j++)
            if(text[i] == sel[j])
                return i;
    return i;
}*/
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
