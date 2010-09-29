#ifndef __SIEGE_BACKEND_GRAPHICS_PRIMITIVE_H__
#define __SIEGE_BACKEND_GRAPHICS_PRIMITIVE_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgmGraphicsDrawPrimitive(void* context, void* texture, SGuint type, SGuint numverts, float* vertices, float* texcoords, float* colors);
    SGuint SG_EXPORT sgmGraphicsDrawSetColor(void* context, float* color);
    SGuint SG_EXPORT sgmGraphicsDrawPointSetSize(void* context, float size);
    //SGuint SG_EXPORT sgmGraphicsDrawPointGetSize(void* context, float* size);
    SGuint SG_EXPORT sgmGraphicsDrawLineSetWidth(void* context, float size);
    //SGuint SG_EXPORT sgmGraphicsDrawLineGetWidth(void* context, float* size);
    //SGuint SG_EXPORT sgmGraphicsDrawLineSetStipple(void* context, SGuint factor, SGuint pattern);
    //SGuint SG_EXPORT sgmGraphicsDrawLineGetStipple(void* context, SGuint* factor, SGuint* pattern);
    //SGuint SG_EXPORT sgmGraphicsDrawPolygonSetStipple(void* context, SGubyte* pattern);
    //SGuint SG_EXPORT sgmGraphicsDrawPolygonGetStipple(void* context*, SGubyte** pattern);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_GRAPHICS_PRIMITIVE_H__
