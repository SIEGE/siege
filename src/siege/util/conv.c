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

SGConv* SG_EXPORT sgConvCreate(const char* from, const char* to)
{
	SGConv* conv;
	if(_sg_modFonts.sgmFontsConvCreate != NULL)
	{
		conv = malloc(sizeof(SGConv));
		conv->handle = NULL;
		_sg_modFonts.sgmFontsConvCreate(&conv->handle, from, to);
		return conv;
	}
	return NULL;
}
void SG_EXPORT sgConvDestroy(SGConv* conv)
{
	if(conv == NULL)
		return;

	if(_sg_modFonts.sgmFontsConvDestroy != NULL)
		_sg_modFonts.sgmFontsConvDestroy(conv->handle);
	free(conv);
}

// todo: copy and use own free!
void* SG_EXPORT sgConv(SGConv* conv, size_t* outlen, const void* str, size_t len)
{
	if(conv == NULL)
		return NULL;

	size_t tmpout;
	if(outlen == NULL)
		outlen = &tmpout;

	void* buf = NULL;
	void* outbuf;
	if(_sg_modFonts.sgmFontsConv != NULL)
		_sg_modFonts.sgmFontsConv(conv->handle, &buf, outlen, (void*)str, len);
	outbuf = malloc(*outlen + 4);
	memcpy(outbuf, buf, *outlen);
	memset(outbuf + *outlen, 0, 4);
	if(_sg_modFonts.sgmFontsConvFreeData != NULL)
		_sg_modFonts.sgmFontsConvFreeData(buf);
	return outbuf;
}

void* SG_EXPORT sgConv2s(const char* from, const char* to, size_t* outlen, const void* str, size_t len)
{
	SGConv* conv = sgConvCreate(from, to);
	void* buf = sgConv(conv, outlen, str, len);
	sgConvDestroy(conv);
	return buf;
}
