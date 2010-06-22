#ifndef __SIEGE_FONTS_FACE_H__
#define __SIEGE_FONTS_FACE_H__

#include "../common.h"

#ifdef SG_LEGACY_API
#    define sgModuleInit sgmModuleInit
#    define sgModuleExit sgmModuleExit
//#    define sgModuleFree sgmModuleFree

#    define sgModuleMatch sgmModuleMatch
#endif // SG_LEGACY_API

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgmModuleInit(void* gc, SGModuleInfo** minfo);
    SGuint SG_EXPORT sgmModuleExit(SGModuleInfo* minfo);
    //SGuint SG_EXPORT sgmModuleFree(void* data);

    SGuint SG_EXPORT sgmModuleMatch(SGModuleInfo** minfos, SGuint numinfos, SGbool* ok);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_FONTS_FACE_H__
