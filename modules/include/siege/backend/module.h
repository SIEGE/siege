#ifndef __SIEGE_FONTS_FACE_H__
#define __SIEGE_FONTS_FACE_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgModuleInit(void* gc, SGModuleInfo** minfo);
    SGuint SG_EXPORT sgModuleExit(SGModuleInfo* minfo);
    //SGuint SG_EXPORT sgModuleFree(void* data);

    SGuint SG_EXPORT sgModuleMatch(SGModuleInfo** minfos, SGuint numinfos, SGbool* ok);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_FONTS_FACE_H__
