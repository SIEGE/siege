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

#include "common.h"

typedef struct StreamInfo
{
    SGStream* stream;
    size_t offset;
} StreamInfo;

typedef struct FontFace
{
    FT_Face ftface;
    FT_StreamRec stream;
    StreamInfo sinfo;
    FT_Open_Args oargs;
    float height;
} FontFace;

static unsigned long f_read(FT_Stream data, unsigned long offset, unsigned char* buffer, unsigned long count)
{
    StreamInfo* sinfo = data->descriptor.pointer;
    SGStream* stream = sinfo->stream;

    stream->seek(stream->data, sinfo->offset + offset, SG_SEEK_SET);
    return stream->read(stream->data, buffer, 1, count);
}
static void f_close(FT_Stream data)
{
    StreamInfo* sinfo = data->descriptor.pointer;
    SGStream* stream = sinfo->stream;
    stream->seek(stream->data, sinfo->offset + data->size, SG_SEEK_SET);
}

static SGenum initStream(FT_Stream fstream, StreamInfo* sinfo, SGStream* stream)
{
    if(!stream->read || !stream->seek || !stream->tell)
        return SG_INVALID_VALUE;

    SGlong pos = stream->tell(stream->data);
    if(pos < 0)
        return SG_UNKNOWN_ERROR;

    SGlong size;
    stream->seek(stream->data, 0, SG_SEEK_END);
    size = stream->tell(stream->data);
    stream->seek(stream->data, pos, SG_SEEK_SET);
    // sanity check with size, even though it should always be >= pos
    if(size < 0 || size < pos)
        return SG_UNKNOWN_ERROR;

    sinfo->stream = stream;
    sinfo->offset = pos;

    fstream->base = NULL;
    fstream->size = size - pos;
    fstream->pos = 0;
    fstream->descriptor.pointer = sinfo;
    fstream->pathname.pointer = NULL;
    fstream->read = f_read;
    fstream->close = f_close;

    return SG_OK;
}

SGenum SG_EXPORT sgmFontsFaceCreate(void** face, SGStream* stream)
{
    *face = malloc(sizeof(FontFace));
    FontFace* fface = *face;
    SGenum iret = initStream(&fface->stream, &fface->sinfo, stream);
    if(iret != SG_OK)
    {
        free(*face);
        return iret;
    }

    fface->oargs.flags = FT_OPEN_STREAM;
    fface->oargs.stream = &fface->stream;

    int ret = FT_Open_Face(library, &fface->oargs, 0, &fface->ftface);
    if(ret != 0)
        return SG_UNKNOWN_ERROR;
    return SG_OK;
}
SGenum SG_EXPORT sgmFontsFaceDestroy(void* face)
{
    if(face == NULL)
        return SG_OK; // SG_INVALID_VALUE
    FT_Done_Face(((FontFace*)face)->ftface);
    free(face);
    return SG_OK;
}

SGenum SG_EXPORT sgmFontsFaceSetHeight(void* face, float height, SGuint dpi)
{
    if(face == NULL)
        return SG_OK; // SG_INVALID_VALUE
    ((FontFace*)face)->height = height;
    FT_Set_Char_Size(((FontFace*)face)->ftface, (SGuint)(height * 64), (SGuint)(height * 64), dpi, dpi);
    return SG_OK;
}
SGenum SG_EXPORT sgmFontsFaceGetMetrics(void* face, float* ascent, float* descent, float* linegap)
{
    if(!face) return SG_INVALID_VALUE;
    FontFace* fface = face;

    *ascent = fface->ftface->size->metrics.ascender / 64.0;
    *descent = fface->ftface->size->metrics.descender / 64.0;
    *linegap = fface->ftface->size->metrics.height / 64.0 + *descent - *ascent;

    return SG_OK;
}

SGenum SG_EXPORT sgmFontsCharsCreate(void* face, const SGdchar* chars, size_t numchars, float* width, float* height, float* prex, float* prey, float* postx, float* posty, size_t* datawidth, size_t* dataheight, void** data)
{
    if(face == NULL)
    {
        *width = 2;
        *height = 2;
        *prex = 0;
        *prey = 0;
        *postx = 2;
        *posty = 0;
        *datawidth = 2;
        *dataheight = 2;
        *data = malloc(2 * 2);
        return SG_OK; // SG_INVALID_VALUE
    }

    FontFace* fface = (FontFace*)face;

    int ret;
    FT_Glyph glyph;
    FT_BitmapGlyph bitmap_glyph;
    FT_Bitmap bitmap;
    SGuint i;
    for(i = 0; i < numchars; i++)
    {
        ret = FT_Load_Glyph(fface->ftface, FT_Get_Char_Index(fface->ftface, chars[i]), FT_LOAD_DEFAULT);
        if(ret)
            return SG_UNKNOWN_ERROR;

        ret = FT_Get_Glyph(fface->ftface->glyph, &glyph);
        if(ret)
            return SG_UNKNOWN_ERROR;

        FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, NULL, 1);

        bitmap_glyph = (FT_BitmapGlyph)glyph;
        bitmap = bitmap_glyph->bitmap;

        // ----------

        datawidth[i] = bitmap.width;
        dataheight[i] = bitmap.rows;

        data[i] = malloc(bitmap.width * bitmap.rows);
        memcpy(data[i], bitmap.buffer, bitmap.width * bitmap.rows);

        prex[i] = bitmap_glyph->left;
        prey[i] = -bitmap_glyph->top;

        postx[i] = fface->ftface->glyph->advance.x / 64.0;
        posty[i] = 0;

        width[i] = fface->ftface->glyph->metrics.width;
        height[i] = fface->ftface->glyph->metrics.height;

        FT_Done_Glyph(glyph);
    }

    return SG_OK;
}
SGenum SG_EXPORT sgmFontsCharsFreeData(void* data)
{
    free(data);
    return SG_OK;
}

SGenum SG_EXPORT sgmFontsCharsGetKerning(void* face, const SGdchar* chars, size_t numchars, float* kerning)
{
    if(!face) return SG_INVALID_VALUE;
    FontFace* fface = face;

    FT_Vector vec;

    FT_UInt prev = numchars ? FT_Get_Char_Index(fface->ftface, chars[0]) : 0;
    FT_UInt curr;

    size_t i;
    for(i = 1; i < numchars; i++)
    {
        curr = FT_Get_Char_Index(fface->ftface, chars[i]);
        FT_Get_Kerning(fface->ftface, prev, curr, FT_KERNING_DEFAULT, &vec);
        kerning[i-1] = vec.x / 64.0;
        prev = curr;
    }

    return SG_OK;
}
