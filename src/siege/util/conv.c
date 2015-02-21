/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "COPYING.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#define SG_BUILD_LIBRARY
#include <siege/util/conv.h>
#include <siege/util/string.h>

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>

#include <stdio.h>

/*static size_t ceildiv(size_t a, size_t b)
{
    return (a / b) + ((a % b) ? 1 : 0);
}
static size_t getfactor(SGenum type)
{
    switch(type)
    {
        case SG_CONV_TYPE_CHAR:
        case SG_CONV_TYPE_UTF8:
            return 1;
        case SG_CONV_TYPE_WCHAR_T:
            return sizeof(wchar_t);
        case SG_CONV_TYPE_UTF16:
        //case SG_CONV_TYPE_UTF16LE:
        //case SG_CONV_TYPE_UTF16BE:
            return 2;
        case SG_CONV_TYPE_UTF32:
        //case SG_CONV_TYPE_UTF32LE:
        //case SG_CONV_TYPE_UTF32BE:
            return 4;
    }
    return 0;
}*/

static size_t SG_CALL _sgConvCToC(char* out, const char* in, size_t* inlen, SGbool strict);
static size_t SG_CALL _sgConvCToW(wchar_t* out, const char* in, size_t* inlen, SGbool strict);
static size_t SG_CALL _sgConvCToU8(SGchar* out, const char* in, size_t* inlen, SGbool strict);
static size_t SG_CALL _sgConvCToU16(SGwchar* out, const char* in, size_t* inlen, SGbool strict);
static size_t SG_CALL _sgConvCToU32(SGdchar* out, const char* in, size_t* inlen, SGbool strict);

static size_t SG_CALL _sgConvWToC(char* out, const wchar_t* in, size_t* inlen, SGbool strict);
static size_t SG_CALL _sgConvWToW(wchar_t* out, const wchar_t* in, size_t* inlen, SGbool strict);
static size_t SG_CALL _sgConvWToU8(SGchar* out, const wchar_t* in, size_t* inlen, SGbool strict);
static size_t SG_CALL _sgConvWToU16(SGwchar* out, const wchar_t* in, size_t* inlen, SGbool strict);
static size_t SG_CALL _sgConvWToU32(SGdchar* out, const wchar_t* in, size_t* inlen, SGbool strict);

static size_t SG_CALL _sgConvU8ToC(char* out, const SGchar* in, size_t* inlen, SGbool strict);
static size_t SG_CALL _sgConvU8ToW(wchar_t* out, const SGchar* in, size_t* inlen, SGbool strict);
static size_t SG_CALL _sgConvU8ToU8(SGchar* out, const SGchar* in, size_t* inlen, SGbool strict);
static size_t SG_CALL _sgConvU8ToU16(SGwchar* out, const SGchar* in, size_t* inlen, SGbool strict);
static size_t SG_CALL _sgConvU8ToU32(SGdchar* out, const SGchar* in, size_t* inlen, SGbool strict);

static size_t SG_CALL _sgConvU16ToC(char* out, const SGwchar* in, size_t* inlen, SGbool strict);
static size_t SG_CALL _sgConvU16ToW(wchar_t* out, const SGwchar* in, size_t* inlen, SGbool strict);
static size_t SG_CALL _sgConvU16ToU8(SGchar* out, const SGwchar* in, size_t* inlen, SGbool strict);
static size_t SG_CALL _sgConvU16ToU16(SGwchar* out, const SGwchar* in, size_t* inlen, SGbool strict);
static size_t SG_CALL _sgConvU16ToU32(SGdchar* out, const SGwchar* in, size_t* inlen, SGbool strict);

static size_t SG_CALL _sgConvU32ToC(char* out, const SGdchar* in, size_t* inlen, SGbool strict);
static size_t SG_CALL _sgConvU32ToW(wchar_t* out, const SGdchar* in, size_t* inlen, SGbool strict);
static size_t SG_CALL _sgConvU32ToU8(SGchar* out, const SGdchar* in, size_t* inlen, SGbool strict);
static size_t SG_CALL _sgConvU32ToU16(SGwchar* out, const SGdchar* in, size_t* inlen, SGbool strict);
static size_t SG_CALL _sgConvU32ToU32(SGdchar* out, const SGdchar* in, size_t* inlen, SGbool strict);

static size_t SG_CALL _sgConvCToC(char* out, const char* in, size_t* inlen, SGbool strict)
{
    (*inlen)--;
    *out = *in;
    return 1;
}
static size_t SG_CALL _sgConvCToW(wchar_t* out, const char* in, size_t* inlen, SGbool strict)
{
    mbtowc(NULL, NULL, 0);
    int sz = mbtowc(out, in, *inlen);
    if(sz <= 0)
        return 0;
    *inlen -= sz;
    return 1;
}
static size_t SG_CALL _sgConvCToU8(SGchar* out, const char* in, size_t* inlen, SGbool strict)
{
    size_t ilen = 1;
    wchar_t buf;
    size_t len = _sgConvCToW(&buf, in, inlen, strict);
    if(!len)
        return 0;
    return _sgConvWToU8(out, &buf, &ilen, strict);
}
static size_t SG_CALL _sgConvCToU16(SGwchar* out, const char* in, size_t* inlen, SGbool strict)
{
    size_t ilen = 1;
    wchar_t buf;
    size_t len = _sgConvCToW(&buf, in, inlen, strict);
    if(!len)
        return 0;
    return _sgConvWToU16(out, &buf, &ilen, strict);
}
static size_t SG_CALL _sgConvCToU32(SGdchar* out, const char* in, size_t* inlen, SGbool strict)
{
    size_t ilen = 1;
    wchar_t buf;
    size_t len = _sgConvCToW(&buf, in, inlen, strict);
    if(!len)
        return 0;
    return _sgConvWToU32(out, &buf, &ilen, strict);
}

static size_t SG_CALL _sgConvWToC(char* out, const wchar_t* in, size_t* inlen, SGbool strict)
{
    wctomb(NULL, 0);
    int sz = wctomb(out, *in);
    if(sz <= 0)
        return 0;
    (*inlen)--;
    return sz;
}
static size_t SG_CALL _sgConvWToW(wchar_t* out, const wchar_t* in, size_t* inlen, SGbool strict)
{
    (*inlen)--;
    *out = *in;
    return 1;
}
static size_t SG_CALL _sgConvWToU8(SGchar* out, const wchar_t* in, size_t* inlen, SGbool strict)
{
    size_t ilen = 1;
    SGdchar buf;
    size_t len = _sgConvWToU32(&buf, in, inlen, strict);
    if(!len)
        return 0;
    return _sgConvU32ToU8(out, &buf, &ilen, strict);
}
static size_t SG_CALL _sgConvWToU16(SGwchar* out, const wchar_t* in, size_t* inlen, SGbool strict)
{
//#ifdef __STDC_ISO_10646__
    if(sizeof(wchar_t) == sizeof(SGwchar))
    {
        (*inlen)--;
        *out = *in;
        return 1;
    }
    size_t ilen = 1;
    SGdchar buf;
    size_t len = _sgConvWToU32(&buf, in, inlen, strict);
    if(!len)
        return 0;
    return _sgConvU32ToU16(out, &buf, &ilen, strict);
//#else
    /* TODO */
//    #error TODO
//#endif /* __STDC_ISO_10646__ */
}
static size_t SG_CALL _sgConvWToU32(SGdchar* out, const wchar_t* in, size_t* inlen, SGbool strict)
{
//#ifdef __STDC_ISO_10646__
    if(sizeof(wchar_t) == sizeof(SGdchar))
    {
        (*inlen)--;
        *out = *in;
        return 1;
    }
    size_t ilen = 1;
    SGwchar buf;
    size_t len = _sgConvWToU16(&buf, in, inlen, strict);
    if(!len)
        return 0;
    return _sgConvU16ToU32(out, &buf, &ilen, strict);
//#else
    /* TODO */
//    #error TODO
//#endif /* __STDC_ISO_10646__ */
}

static size_t SG_CALL _sgConvU8ToC(char* out, const SGchar* in, size_t* inlen, SGbool strict)
{
    size_t ilen = 1;
    SGdchar buf;
    size_t len = _sgConvU8ToU32(&buf, in, inlen, strict);
    if(!len)
        return 0;
    return _sgConvU32ToC(out, &buf, &ilen, strict);
}
static size_t SG_CALL _sgConvU8ToW(wchar_t* out, const SGchar* in, size_t* inlen, SGbool strict)
{
    size_t ilen = 1;
    SGdchar buf;
    size_t len = _sgConvU8ToU32(&buf, in, inlen, strict);
    if(!len)
        return 0;
    return _sgConvU32ToW(out, &buf, &ilen, strict);
}
static size_t SG_CALL _sgConvU8ToU8(SGchar* out, const SGchar* in, size_t* inlen, SGbool strict) /* TODO: Normalize */
{
    (*inlen)--;
    *out = *in;
    return 1;
}
static size_t SG_CALL _sgConvU8ToU16(SGwchar* out, const SGchar* in, size_t* inlen, SGbool strict)
{
    size_t ilen = 1;
    SGdchar buf;
    size_t len = _sgConvU8ToU32(&buf, in, inlen, strict);
    if(!len)
        return 0;
    return _sgConvU32ToU16(out, &buf, &ilen, strict);
}
static size_t SG_CALL _sgConvU8ToU32(SGdchar* out, const SGchar* in, size_t* inlen, SGbool strict)
{
    (*inlen)--;

    const unsigned char* uin = (const unsigned char*)in;

    if(strict && (uin[0] == 0xFF || uin[0] == 0xFE))
    {
        //tcode_error_raisef("Invalid value (0x%.2X)", uin[0]);
        return 0;
    }

    if(uin[0] & 0x80) /* bit 1 */
    {
        if(uin[0] & 0x40) /* bit 2 */
        {
            if(uin[0] & 0x20) /* bit 3 */
            {
                if(uin[0] & 0x10) /* bit 4 */
                {
                    if(uin[0] & 0x08) /* bit 5 */
                    {
                        //tcode_error_raisef("Too long sequence (0x%.2X)", uin[0]);
                        return 0;
                    }
                    else /* +3 bytes */
                    {
                        if(3 > *inlen)
                        {
                            //tcode_error_raisef("Unterminated sequence 0x%.2X------", uin[0]);
                            return 0;
                        }
                        out[0] = (uin[0] & 0x07) << 18;
                        (*inlen)--;
                        out[0] |= (uin[1] & 0x3F) << 12;
                        (*inlen)--;
                        out[0] |= (uin[2] & 0x3F) << 6;
                        (*inlen)--;
                        out[0] |= (uin[3] & 0x3F);

                        if(strict && out[0] < 0x010000)
                        {
                            //tcode_error_raisef("Un-normalized input (0x%.6X)", uin[0]);
                            return 0;
                        }
                    }
                }
                else /* +2 bytes */
                {
                    if(2 > *inlen)
                    {
                        //tcode_error_raisef("Unterminated sequence 0x%.2X----", uin[0]);
                        return 0;
                    }
                    out[0] = (uin[0] & 0x0F) << 12;
                    (*inlen)--;
                    out[0] |= (uin[1] & 0x3F) << 6;
                    (*inlen)--;
                    out[0] |= (uin[2] & 0x3F);

                    if(strict && out[0] < 0x000800)
                    {
                        //tcode_error_raisef("Un-normalized input (0x%.4X)", uin[0]);
                        return 0;
                    }
                }
            }
            else /* +1 byte */
            {
                if(1 > *inlen)
                {
                    //tcode_error_raisef("Unterminated sequence 0x%.2X--", uin[0]);
                    return 0;
                }
                out[0] = (uin[0] & 0x1F) << 6;
                (*inlen)--;
                out[0] |= uin[1] & 0x3F;

                if(strict && out[0] < 0x000080)
                {
                    //tcode_error_raisef("Un-normalized input (0x%.2X)", uin[0]);
                    return 0;
                }
            }
        }
        else
        {
            //tcode_error_raisef("Found sequence continuation character without start (0x%.2X)", uin[0]);
            return 0;
        }
    }
    else /* +0 bytes (ASCII) */
        out[0] = uin[0] & 0x7F;
    return 1;
}

static size_t SG_CALL _sgConvU16ToC(char* out, const SGwchar* in, size_t* inlen, SGbool strict)
{
    size_t ilen = 1;
    SGdchar buf;
    size_t len = _sgConvU16ToU32(&buf, in, inlen, strict);
    if(!len)
        return 0;
    return _sgConvU32ToC(out, &buf, &ilen, strict);
}
static size_t SG_CALL _sgConvU16ToW(wchar_t* out, const SGwchar* in, size_t* inlen, SGbool strict)
{
//#ifdef __STDC_ISO_10646__
    if(sizeof(wchar_t) == sizeof(SGwchar))
    {
        (*inlen)--;
        *out = *in;
        return 1;
    }
    size_t ilen = 1;
    SGdchar buf;
    size_t len = _sgConvU16ToU32(&buf, in, inlen, strict);
    if(!len)
        return 0;
    return _sgConvU32ToW(out, &buf, &ilen, strict);
//#else
    /* TODO */
//    #error TODO
//#endif /* __STDC_ISO_10646__ */
}
static size_t SG_CALL _sgConvU16ToU8(SGchar* out, const SGwchar* in, size_t* inlen, SGbool strict)
{
    size_t ilen = 1;
    SGdchar buf;
    size_t len = _sgConvU16ToU32(&buf, in, inlen, strict);
    if(!len)
        return 0;
    return _sgConvU32ToU8(out, &buf, &ilen, strict);
}
static size_t SG_CALL _sgConvU16ToU16(SGwchar* out, const SGwchar* in, size_t* inlen, SGbool strict) /* TODO: Normalize */
{
    (*inlen)--;
    *out = *in;
    return 1;
}
static size_t SG_CALL _sgConvU16ToU32(SGdchar* out, const SGwchar* in, size_t* inlen, SGbool strict)
{
    (*inlen)--;

    if(0xD800 <= in[0] && in[0] <= 0xDBFF)
    {
        if(1 > *inlen)
        {
            //tcode_error_raisef("Unterminated sequence 0x.4X----", in[0]);
            return 0;
        }
        out[0] = (in[0] & 0x3FF) << 10;
        (*inlen)--;
        out[0] |= in[1] & 0x3FF;
        out[0] += 0x10000;
        return 1;
    }
    else if(in[0] < 0xD800 || 0xDFFF < in[0])
    {
        out[0] = in[0];
        return 1;
    }

    /* error */
    //tcode_error_raisef("Errorneous sequence (0x%.4X)", in[0]);
    return 0;
}

static size_t SG_CALL _sgConvU32ToC(char* out, const SGdchar* in, size_t* inlen, SGbool strict)
{
    size_t ilen = 1;
    wchar_t buf;
    size_t len = _sgConvU32ToW(&buf, in, inlen, strict);
    if(!len)
        return 0;
    return _sgConvWToC(out, &buf, &ilen, strict);
}
static size_t SG_CALL _sgConvU32ToW(wchar_t* out, const SGdchar* in, size_t* inlen, SGbool strict)
{
//#ifdef __STDC_ISO_10646__
    if(sizeof(wchar_t) == sizeof(SGdchar))
    {
        (*inlen)--;
        *out = *in;
        return 1;
    }
    SGwchar buf[2];
    size_t len = _sgConvU32ToU16(buf, in, inlen, strict);
    if(!len)
        return 0;
    return _sgConvU16ToW(out, buf, &len, strict);
//#else
    /* TODO */
//    #error TODO
//#endif /* __STDC_ISO_10646__ */
}
static size_t SG_CALL _sgConvU32ToU8(SGchar* out, const SGdchar* in, size_t* inlen, SGbool strict)
{
    (*inlen)--;

    if(in[0] <= 0x7F) /* 1 octet */
    {
        out[0] = in[0];
        return 1;
    }
    else if(in[0] <= 0x07FF) /* 2 octets */
    {
        out[0] = 0xC0 | (in[0] >> 6);
        out[1] = 0x80 | (in[0] & 0x3F);
        return 2;
    }
    else if(in[0] <= 0xFFFF) /* 3 octets */
    {
        out[0] = 0xE0 | (in[0] >> 12);
        out[1] = 0x80 | ((in[0] >> 6) & 0x3F);
        out[2] = 0x80 | (in[0] & 0x3F);
        return 3;
    }
    else if(in[0] <= 0x10FFFF) /* 4 octets */
    {
        out[0] = 0xF0 | (in[0] >> 18);
        out[1] = 0x80 | ((in[0] >> 12) & 0x3F);
        out[2] = 0x80 | ((in[0] >> 6) & 0x3F);
        out[3] = 0x80 | (in[0] & 0x3F);
        return 4;
    }

    /* error */
    //tcode_error_raisef("Cannot encode value %.8X into UTF-8 (it is larger than 0x10FFFF)", in[0]);
    return 0;
}
static size_t SG_CALL _sgConvU32ToU16(SGwchar* out, const SGdchar* in, size_t* inlen, SGbool strict)
{
    (*inlen)--;

    if(strict && 0xD800 <= in[0] && in[0] <= 0xDFFF) /* reserved for UTF-16 */
    {
        //tcode_error_raisef("Cannot encode value %.4X into UTF-16 (value reserved for the UTF-16 encoding itself)", in[0]);
        return 0;
    }

    if(in[0] <= 0xFFFF) /* 2 octets */
    {
        out[0] = in[0];
        return 1;
    }
    else if(in[0] <= 0x10FFFF) /* 4 octets */
    {
        out[0] = 0xD800 | ((in[0] - 0x10000) >> 10);
        out[1] = 0xDC00 | ((in[0] - 0x10000) & 0x3FF);
        return 2;
    }

    /* error */
    //tcode_error_raisef("Cannot encode value %.8X into UTF-16 (it is larger than 0x10FFFF)", in[0]);
    return 0;
}
static size_t SG_CALL _sgConvU32ToU32(SGdchar* out, const SGdchar* in, size_t* inlen, SGbool strict)
{
    (*inlen)--;
    *out = *in;
    return 1;
}

static SGConvFunction* _sgConvFunction(SGenum dst, SGenum src)
{
    static SGConvFunction* mat[SG_CONV_TYPE_LAST][SG_CONV_TYPE_LAST] =
    {
                     /* UNKNOWN CHAR                            WCHAR_T                         UTF8                              UTF16LE                           UTF16BE UTF32LE                           UTF32BE */
        /* UNKNOWN */ { NULL  , NULL                          , NULL                          , NULL                            , NULL                            , NULL  , NULL                            , NULL },
        /* CHAR    */ { NULL  , (SGConvFunction*)_sgConvCToC  , (SGConvFunction*)_sgConvCToW  , (SGConvFunction*)_sgConvCToU8   , (SGConvFunction*)_sgConvCToU16  , NULL  , (SGConvFunction*)_sgConvCToU32  , NULL },
        /* WCHAR_T */ { NULL  , (SGConvFunction*)_sgConvWToC  , (SGConvFunction*)_sgConvWToW  , (SGConvFunction*)_sgConvWToU8   , (SGConvFunction*)_sgConvWToU16  , NULL  , (SGConvFunction*)_sgConvWToU32  , NULL },
        /* UTF8    */ { NULL  , (SGConvFunction*)_sgConvU8ToC , (SGConvFunction*)_sgConvU8ToW , (SGConvFunction*)_sgConvU8ToU8  , (SGConvFunction*)_sgConvU8ToU16 , NULL  , (SGConvFunction*)_sgConvU8ToU32 , NULL },
        /* UTF16LE */ { NULL  , (SGConvFunction*)_sgConvU16ToC, (SGConvFunction*)_sgConvU16ToW, (SGConvFunction*)_sgConvU16ToU8 , (SGConvFunction*)_sgConvU16ToU16, NULL  , (SGConvFunction*)_sgConvU16ToU32, NULL },
        /* UTF16BE */ { NULL  , NULL                          , NULL                          , NULL                            , NULL                            , NULL  , NULL                            , NULL },
        /* UTF32LE */ { NULL  , (SGConvFunction*)_sgConvU32ToC, (SGConvFunction*)_sgConvU32ToW, (SGConvFunction*)_sgConvU32ToU8 , (SGConvFunction*)_sgConvU32ToU16, NULL  , (SGConvFunction*)_sgConvU32ToU32, NULL },
        /* UTF32BE */ { NULL  , NULL                          , NULL                          , NULL                            , NULL                            , NULL  , NULL                            , NULL },
    };

    if(dst >= SG_CONV_TYPE_LAST || src >= SG_CONV_TYPE_LAST)
        return NULL;
    return mat[src][dst];
}
static size_t _sgConvSize(SGenum type)
{
    switch(type)
    {
        case SG_CONV_TYPE_CHAR:    return sizeof(char);
        case SG_CONV_TYPE_WCHAR_T: return sizeof(wchar_t);
        case SG_CONV_TYPE_UTF8:    return sizeof(SGchar);
        case SG_CONV_TYPE_UTF16LE:
        case SG_CONV_TYPE_UTF16BE: return sizeof(SGwchar);
        case SG_CONV_TYPE_UTF32LE:
        case SG_CONV_TYPE_UTF32BE: return sizeof(SGdchar);
    }
    return 0;
}

SGConv* SG_CALL sgConvInit(SGConv* conv, SGenum dst, SGenum src)
{
    if(!conv) return NULL;

    SGConvFunction* func = _sgConvFunction(dst, src);
    if(!func) return NULL;

    conv->func = func;
    conv->dst = dst;
    conv->src = src;

    return conv;
}
void SG_CALL sgConvDeinit(SGConv* conv)
{
    if(!conv) return;
}

SGConv* SG_CALL sgConvCreate(SGenum dst, SGenum src)
{
    SGConv* conv = malloc(sizeof(SGConv));
    if(!sgConvInit(conv, dst, src))
    {
        free(conv);
        return NULL;
    }
    return conv;
}
void SG_CALL sgConvDestroy(SGConv* conv)
{
    sgConvDeinit(conv);
    free(conv);
}

size_t SG_CALL sgConvEstimate(SGConv* conv, size_t inlen)
{
    static size_t mat[SG_CONV_TYPE_LAST][SG_CONV_TYPE_LAST] = {
                     /* UNKNOWN CHAR WCHAR_T              UTF8 UTF16LE UTF16BE UTF32LE UTF32BE */
        /* UNKNOWN */ { 0     , 0  , 0                  , 0  , 0     , 0      ,0      ,0 },
        /* CHAR    */ { 0     , 1  , 4 / sizeof(wchar_t), 4  , 2     , 2      ,1      ,1 },
        /* WCHAR_T */ { 0     , 4  , 1                  , 4  , 2     , 2      ,1      ,1 },
        /* UTF8    */ { 0     , 1  , 4 / sizeof(wchar_t), 1  , 1     , 1      ,1      ,1 },
        /* UTF16LE */ { 0     , 4  , 4 / sizeof(wchar_t), 4  , 1     , 1      ,1      ,1 },
        /* UTF16BE */ { 0     , 4  , 4 / sizeof(wchar_t), 4  , 1     , 1      ,1      ,1 },
        /* UTF32LE */ { 0     , 4  , 4 / sizeof(wchar_t), 4  , 2     , 2      ,1      ,1 },
        /* UTF32BE */ { 0     , 4  , 4 / sizeof(wchar_t), 4  , 2     , 2      ,1      ,1 },
    };
    if(conv->dst >= SG_CONV_TYPE_LAST || conv->src >= SG_CONV_TYPE_LAST)
        return 0;
    return mat[conv->src][conv->dst];
}

size_t SG_CALL sgConv(SGConv* conv, void* out, size_t outlen, const void* in, size_t inlen, SGbool strict)
{
    size_t outsize = _sgConvSize(conv->dst);
    size_t insize = _sgConvSize(conv->src);

    size_t ilen;
    size_t len;
    char buf[4];
    size_t num = 0;

    size_t i;
    for(i = 0; i < inlen; i++)
    {
        ilen = inlen - i;
        len = conv->func(buf, ((const char*)in) + i * insize, &ilen, strict);
        if(!len)
            goto error;
        i += (inlen - i) - ilen - 1;

        num += _sgStrbufAppend(outsize, num, out, outlen, buf, len);
    }
    if(outlen)
        memset(((char*)out) + SG_MIN(num, outlen-1) * outsize, 0, outsize); /* 0-terminate */
    return num;
error:
    if(outlen)
        memset(((char*)out) + SG_MIN(num, outlen-1) * outsize, 0, outsize); /* 0-terminate */
    return 0;
}
size_t SG_CALL sgConv2s(SGenum dst, SGenum src, void* out, size_t outlen, const void* in, size_t inlen, SGbool strict)
{
    SGConv* conv = sgConvCreate(dst, src);
    if(!conv) return 0;
    size_t len = sgConv(conv, out, outlen, in, inlen, strict);
    sgConvDestroy(conv);
    return len;
}
