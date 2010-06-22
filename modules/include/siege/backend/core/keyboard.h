#ifndef __SIEGE_CORE_KEYBOARD_H__
#define __SIEGE_CORE_KEYBOARD_H__

#include "../../common.h"

#ifdef SG_LEGACY_API
#    define sgCoreKeyboardCreate sgmCoreKeyboardCreate
#    define sgCoreKeyboardDestroy sgmCoreKeyboardDestroy
//#    define sgCoreKeyboardSetKey sgmCoreKeyboardSetKey
#    define sgCoreKeyboardGetKey sgmCoreKeyboardGetKey
//#    define sgCoreKeyboardSetChr sgmCoreKeyboardSetChr
//#    define sgCoreKeyboardGetChr sgmCoreKeyboardGetChr

#    define sgCoreKeyboardSetCallbacks sgmCoreKeyboardSetCallbacks
//#    define sgCoreKeyboardGetCallbacks sgmCoreKeyboardGetCallbacks
#endif // SG_LEGACY_API

#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct SGCoreKeyboardCallbacks
    {
        void SG_EXPORT (*key)(void* keyboard, SGuint key, SGbool down);
        void SG_EXPORT (*chr)(void* keyboard, SGuint chr, SGbool down);
    } SGCoreKeyboardCallbacks;

    SGuint SG_EXPORT sgmCoreKeyboardCreate(void** keyboard, void* window);
    SGuint SG_EXPORT sgmCoreKeyboardDestroy(void* keyboard);
    //SGuint SG_EXPORT sgmCoreKeyboardSetKey(void* keyboard, SGuint key, SGbool down);
    SGuint SG_EXPORT sgmCoreKeyboardGetKey(void* keyboard, SGuint key, SGbool* down);
    //SGuint SG_EXPORT sgmCoreKeyboardSetChr(void* keyboard, SGuint chr, SGbool down);
    //SGuint SG_EXPORT sgmCoreKeyboardGetChr(void* keyboard, SGuint chr, SGbool* down);

    SGuint SG_EXPORT sgmCoreKeyboardSetCallbacks(void* keyboard, SGCoreKeyboardCallbacks* callbacks);
    //SGuint SG_EXPORT sgmCoreKeyboardGetCallbacks(void* keyboard, SGCoreKeyboardCallbacks** callbacks);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_CORE_KEYBOARD_H__
