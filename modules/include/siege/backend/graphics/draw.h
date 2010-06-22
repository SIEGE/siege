#ifndef __SIEGE_GRAPHICS_PRIMITIVE_H__
#define __SIEGE_GRAPHICS_PRIMITIVE_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgGraphicsDrawPrimitive(void* context, void* texture, SGuint type, SGuint numverts, float* vertices, float* texcoords, float* colors);
    SGuint SG_EXPORT sgGraphicsDrawSetColor(void* context, float* color);
    SGuint SG_EXPORT sgGraphicsDrawPointSetSize(void* context, float size);
    //SGuint SG_EXPORT sgGraphicsDrawPointGetSize(void* context, float* size);
    SGuint SG_EXPORT sgGraphicsDrawLineSetWidth(void* context, float size);
    //SGuint SG_EXPORT sgGraphicsDrawLineGetWidth(void* context, float* size);
    //SGuint SG_EXPORT sgGraphicsDrawLineSetStipple(void* context, SGuint factor, SGuint pattern);
    //SGuint SG_EXPORT sgGraphicsDrawLineGetStipple(void* context, SGuint* factor, SGuint* pattern);
    //SGuint SG_EXPORT sgGraphicsDrawPolygonSetStipple(void* context, SGubyte* pattern);
    //SGuint SG_EXPORT sgGraphicsDrawPolygonGetStipple(void* context*, SGubyte** pattern);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_GRAPHICS_PRIMITIVE_H__
