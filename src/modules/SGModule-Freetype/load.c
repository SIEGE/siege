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
#include "load.h"


SGuint SG_EXPORT sgmFontsFaceCreate(void** face, const char* fname)
{
    *face = malloc(sizeof(FontFace));
    int ret = FT_New_Face(library, fname, 0, &(*(FontFace**)face)->ftface);
    if(ret != 0)
        return SG_UNKNOWN_ERROR;
    return SG_OK;
}
SGuint SG_EXPORT sgmFontsFaceDestroy(void* face)
{
    if(face == NULL)
        return SG_OK; // SG_INVALID_VALUE
    FT_Done_Face(((FontFace*)face)->ftface);
    free(face);
    return SG_OK;
}
SGuint SG_EXPORT sgmFontsFaceSetHeight(void* face, float height)
{
    if(face == NULL)
        return SG_OK; // SG_INVALID_VALUE
    ((FontFace*)face)->height = height;
    FT_Set_Char_Size(((FontFace*)face)->ftface, (SGuint)(height * 64), (SGuint)(height * 64), 96, 96);
    return SG_OK;
}
/*SGuint SG_EXPORT sgmFontsFaceGetHeight(void* face, float* height)
{
    *height = ((FontFace*)face)->height;
    return SG_OK;
}*/
SGuint SG_EXPORT sgmFontsCharsCreate(void* face, SGuint* chars, SGuint charnum, float* width, float* height, float* prex, float* prey, float* postx, float* posty, SGuint* datawidth, SGuint* dataheight, void** data)
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
    for(i = 0; i < charnum; i++)
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
        data[i] = memcpy(data[i], bitmap.buffer, bitmap.width * bitmap.rows);

        prex[i] = bitmap_glyph->left;
        prey[i] = -bitmap_glyph->top + bitmap.rows;

        postx[i] = fface->ftface->glyph->advance.x >> 6;
        posty[i] = 0;

        width[i] = fface->ftface->glyph->/*bitmap.width*/advance.x >> 6;
        height[i] = fface->height;

        FT_Done_Glyph(glyph);
    }

    return SG_OK;
}

SGuint SG_EXPORT sgmFontsCharsFreeData(void* data)
{
    free(data);
    return SG_OK;
}
