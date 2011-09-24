/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "license.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
*/

#include "main.h"
#include "texture.h"
#include "draw.h"

#include <stdio.h>
#include <stdlib.h>

SGuint SG_EXPORT sgmGraphicsDrawPrimitive(void* context, void* texture, SGenum type, size_t numverts, float* vertices, float* texcoords, float* colors)
{
    TextureData* tdata = texture;

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    if(tdata)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tdata->texid);
    }

    if(texcoords != NULL)
    {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
    }
    if(colors != NULL)
    {
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(4, GL_FLOAT, 0, colors);
    }

    GLuint* indices;
    size_t i;
    switch(type)
    {
        case SG_GRAPHICS_PRIMITIVE_POINTS:
            glDrawArrays(GL_POINTS, 0, numverts);
            break;
        case SG_GRAPHICS_PRIMITIVE_LINES:
            glDrawArrays(GL_LINES, 0, numverts);
            break;
        case SG_GRAPHICS_PRIMITIVE_LINE_STRIP:
            glDrawArrays(GL_LINE_STRIP, 0, numverts);
            break;
        case SG_GRAPHICS_PRIMITIVE_LINE_FAN:
            indices = malloc((numverts - 1) * sizeof(GLuint) * 2);
            for(i = 0; i < numverts - 1; i++)
            {
                indices[2*i  ] = 0;
                indices[2*i+1] = i+1;
            }
            glDrawElements(GL_LINES, numverts, GL_UNSIGNED_INT, indices);
            free(indices);
            break;
        case SG_GRAPHICS_PRIMITIVE_LINE_LOOP:
            glDrawArrays(GL_LINE_LOOP, 0, numverts);
            break;
        case SG_GRAPHICS_PRIMITIVE_TRIANGLES:
            glDrawArrays(GL_TRIANGLES, 0, numverts);
            break;
        case SG_GRAPHICS_PRIMITIVE_TRIANGLE_STRIP:
            glDrawArrays(GL_TRIANGLE_STRIP, 0, numverts);
            break;
        case SG_GRAPHICS_PRIMITIVE_TRIANGLE_FAN:
            glDrawArrays(GL_TRIANGLE_FAN, 0, numverts);
            break;
        //case SG_GRAPHICS_PRIMITIVE_TRIANGLE_LOOP:
        //    break;
        case SG_GRAPHICS_PRIMITIVE_QUADS:
            glDrawArrays(GL_QUADS, 0, numverts);
            break;
        case SG_GRAPHICS_PRIMITIVE_QUAD_STRIP:
            glDrawArrays(GL_QUAD_STRIP, 0, numverts);
            break;
        //case SG_GRAPHICS_PRIMITIVE_QUAD_FAN:
        //    break;
        //case SG_GRAPHICS_PRIMITIVE_QUAD_LOOP:
        //    break;
        case SG_GRAPHICS_PRIMITIVE_CONVEX_POLYGON:
            glDrawArrays(GL_POLYGON, 0, numverts);
            break;

        // we don't bother converting at this point (as the frontend will soon handle it)
        // so we just try our luck with GL_POLYGON
        case SG_GRAPHICS_PRIMITIVE_CONCAVE_POLYGON:
        case SG_GRAPHICS_PRIMITIVE_INTERSECTING_POLYGON:
            glDrawArrays(GL_POLYGON, 0, numverts);
            break;

        default:
            if(texcoords != NULL)
                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            if(colors != NULL)
                glDisableClientState(GL_COLOR_ARRAY);
            glDisableClientState(GL_VERTEX_ARRAY);
            return SG_INVALID_VALUE;
    }

    if(texcoords != NULL)
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    if(colors != NULL)
        glDisableClientState(GL_COLOR_ARRAY);

    glDisableClientState(GL_VERTEX_ARRAY);

    if(tdata)
    {
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    return SG_OK;
}
SGuint SG_EXPORT sgmGraphicsDrawSetColor(void* context, float* color)
{
    glColor4fv(color);
    return SG_OK;
}
SGuint SG_EXPORT sgmGraphicsDrawPointSetSize(void* context, float size)
{
    glPointSize(size);
    return SG_OK;
}
SGuint SG_EXPORT sgmGraphicsDrawLineSetWidth(void* context, float size)
{
    glLineWidth(size);
    return SG_OK;
}

/*#define SG_GRAPHICS_FUNC_ZERO                   0x00
#define SG_GRAPHICS_FUNC_ONE                    0x01
#define SG_GRAPHICS_FUNC_SRC_COLOR              0x02
#define SG_GRAPHICS_FUNC_ONE_MINUS_SRC_COLOR    0x03
#define SG_GRAPHICS_FUNC_DST_COLOR              0x04
#define SG_GRAPHICS_FUNC_ONE_MINUS_DST_COLOR    0x05
#define SG_GRAPHICS_FUNC_SRC_ALPHA              0x06
#define SG_GRAPHICS_FUNC_ONE_MINUS_SRC_ALPHA    0x07
#define SG_GRAPHICS_FUNC_DST_ALPHA              0x08
#define SG_GRAPHICS_FUNC_ONE_MINUS_DST_ALPHA    0x09

#define SG_GRAPHICS_EQUATION_ADD                0x00
#define SG_GRAPHICS_EQUATION_SUBTRACT           0x01
#define SG_GRAPHICS_EQUATION_REVERSE_SUBTRACT   0x02
#define SG_GRAPHICS_EQUATION_MIN                0x03
#define SG_GRAPHICS_EQUATION_MAX                0x04*/
SGuint SG_EXPORT sgmGraphicsDrawSetBlendFunc(void* context, SGenum src, SGenum dst)
{
    static GLenum table[] = {GL_ZERO, GL_ONE,
                             GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR,
                             GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR,
                             GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,
                             GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA,};

    if(src >= sizeof(table) / sizeof(GLenum)
    || dst >= sizeof(table) / sizeof(GLenum))
        return SG_OK; // SG_INVALID_ENUM

    glBlendFunc(table[src], table[dst]);

    return SG_OK;
}
// todo
SGuint SG_EXPORT sgmGraphicsDrawSetBlendEquation(void* context, SGenum equation)
{
    static GLenum table[] = {GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT, GL_MIN, GL_MAX};

    if(equation >= sizeof(table) / sizeof(GLenum))
        return SG_OK; // SG_INVALID_ENUM

    return SG_UNKNOWN_ERROR;
    //glBlendEquation(table[equation]);

    return SG_OK;
}

SGenum SG_EXPORT SG_FPTR(sgmGraphicsDrawSetDepthTest)(void* context, SGbool test)
{
    if(test)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
    return SG_OK;
}

SGenum SG_EXPORT SG_FPTR(sgmGraphicsDrawSetSmooth)(void* context, SGbool smooth)
{
    GLenum mode = smooth ? GL_NICEST : GL_FASTEST;

    glHint(GL_POINT_SMOOTH_HINT  , mode);
    glHint(GL_LINE_SMOOTH_HINT   , mode);
    glHint(GL_POLYGON_SMOOTH_HINT, mode);

    if(smooth)
    {
        glEnable(GL_POINT_SMOOTH);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_POLYGON_SMOOTH);
    }
    else
    {
        glDisable(GL_POINT_SMOOTH);
        glDisable(GL_LINE_SMOOTH);
        glDisable(GL_POLYGON_SMOOTH);
    }

    return SG_OK;
}
