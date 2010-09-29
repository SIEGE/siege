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
#include "draw.h"

#include <stdio.h>
#include <stdlib.h>

SGuint SG_EXPORT sgmGraphicsDrawPrimitive(void* context, void* texture, SGuint type, SGuint numverts, float* vertices, float* texcoords, float* colors)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

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
    SGuint i;
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
