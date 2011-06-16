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
#include <siege/util/conv.h>
#include <siege/modules/fonts.h>

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>

SGint SG_EXPORT _sgStrICmp(const char* a, const char* b)
{
	while(*a && *b)
	{
		if(tolower(*a) != tolower(*b))
			return tolower(*a) - tolower(*b);
		a++;
		b++;
	}
	return *a - *b;
}
SGenum SG_EXPORT _sgConvType(const char* type)
{
	if(_sgStrICmp("char", type) == 0)
		return SG_CONV_TYPE_CHAR;
	if(_sgStrICmp("wchar_t", type) == 0)
		return SG_CONV_TYPE_WCHAR_T;
	if(_sgStrICmp("UTF-8", type) == 0)
		return SG_CONV_TYPE_UTF8;
	if(_sgStrICmp("UTF-16", type) == 0)
		return SG_CONV_TYPE_UTF16;
	if(_sgStrICmp("UTF-32", type) == 0)
		return SG_CONV_TYPE_UTF32;
	return SG_CONV_TYPE_UNKNOWN;
}

SGConv* SG_EXPORT sgConvCreate(const char* from, const char* to)
{
	SGConv* conv = malloc(sizeof(SGConv));
	if(conv == NULL)
		return NULL;
	conv->handle = NULL;
	conv->from = _sgConvType(from);
	conv->to = _sgConvType(to);
	if(sgmFontsConvCreate != NULL)
		sgmFontsConvCreate(&conv->handle, from, to);
	return conv;
}
void SG_EXPORT sgConvDestroy(SGConv* conv)
{
	if(conv == NULL)
		return;

	if(sgmFontsConvDestroy != NULL)
		sgmFontsConvDestroy(conv->handle);
	free(conv);
}

// todo: fallback conversion should be done by font.c and similar, not sgConv!
void* SG_EXPORT sgConv(SGConv* conv, size_t* outlen, const void* str, size_t len)
{
	if(conv == NULL)
		return NULL;

	size_t tmpout;
	if(outlen == NULL)
		outlen = &tmpout;

	void* buf = NULL;
	void* outbuf;
	if(sgmFontsConv != NULL)
	{
		sgmFontsConv(conv->handle, &buf, outlen, (void*)str, len);
		outbuf = malloc(*outlen + 4);
		memcpy(outbuf, buf, *outlen);
		memset(outbuf + *outlen, 0, 4);
		if(sgmFontsConvFreeData != NULL)
			sgmFontsConvFreeData(buf);
	}
	else
	{
		size_t i;
		const char* cstr = str;
		const wchar_t* wcstr = str;
		const SGwchar* wstr = str;
		const SGdchar* dstr = str;
		SGdchar* doutbuf = NULL;
		switch(conv->from)
		{
			case SG_CONV_TYPE_CHAR:
				doutbuf = malloc(4 * (len + 1));
				for(i = 0; i < len; i++)
					doutbuf[i] = cstr[i];
				doutbuf[len] = 0;
				*outlen = len * 4;
				break;
			case SG_CONV_TYPE_WCHAR_T:
				len /= sizeof(wchar_t);
				doutbuf = malloc(4 * (len + 1));
				for(i = 0; i < len; i++)
					doutbuf[i] = wcstr[i];
				doutbuf[len] = 0;
				*outlen = len * 4;
				break;
			case SG_CONV_TYPE_UTF8:
				doutbuf = malloc(4 * (len + 1));
				for(i = 0; i < len; i++)
					doutbuf[i] = cstr[i];
				doutbuf[len] = 0;
				break;
			case SG_CONV_TYPE_UTF16:
				len /= sizeof(SGwchar);
				doutbuf = malloc(4 * (len + 1));
				for(i = 0; i < len; i++)
					doutbuf[i] = wstr[i];
				doutbuf[len] = 0;
				*outlen = len * 4;
				break;
			case SG_CONV_TYPE_UTF32:
				len /= sizeof(SGdchar);
				doutbuf = malloc(4 * (len + 1));
				memcpy(doutbuf, dstr, 4 * (len + 1));
				*outlen = len * 4;
				break;
		}
		outbuf = doutbuf;
	}
	return outbuf;
}

void* SG_EXPORT sgConv2s(const char* from, const char* to, size_t* outlen, const void* str, size_t len)
{
	SGConv* conv = sgConvCreate(from, to);
	void* buf = sgConv(conv, outlen, str, len);
	sgConvDestroy(conv);
	return buf;
}
