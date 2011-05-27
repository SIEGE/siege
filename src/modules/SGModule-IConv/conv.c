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

#include "main.h"
#include <stdlib.h>
#include <string.h>
//#include <errno.h>

/// \todo Maybe SGenum -> SG_ENCODING_*?
SGenum SG_EXPORT sgmFontsConvCreate(void** conv, const char* from, const char* to)
{
	if(!strcmp(from, "char"))
		from = "";
	if(!strcmp(to, "char"))
		to = "";
	if(!strcmp(to, "UTF-32"))
		to = "UTF-32LE";

	iconv_t** cconv = (iconv_t**)conv;

	*cconv = malloc(sizeof(iconv_t));
	**cconv = iconv_open(to, from);
	return SG_OK;
}
SGenum SG_EXPORT sgmFontsConvDestroy(void* conv)
{
	if(conv == NULL)
		return SG_OK; // SG_UNKNOWN_ERROR

	if(iconv_close(*(iconv_t*)conv))
		return SG_UNKNOWN_ERROR;
	free(conv);
	return SG_OK;
}
SGenum SG_EXPORT sgmFontsConv(void* conv, void** outbuf, size_t* outlen, void* inbuf, size_t inlen)
{
	iconv_t* cconv = conv;
	if(!cconv)
		return SG_OK; // SG_INVALID_VALUE

	*outbuf = malloc(inlen * 4);

	void* iinbuf = inbuf;
	void* ioutbuf = *outbuf;
	size_t iinlen = inlen;
	size_t ioutlen = inlen * 4;

	iconv(*cconv, (char**)&iinbuf, &iinlen, (char**)&ioutbuf, &ioutlen);
	*outlen = inlen * 4 - ioutlen;

	return SG_OK;
}

SGenum SG_EXPORT sgmFontsConvFreeData(void* ptr)
{
	free(ptr);
	return SG_OK;
}
