#ifndef __SIEGE_CORE_KEYBOARD_H__
#define __SIEGE_CORE_KEYBOARD_H__

#include "../../common.h"

typedef struct SGCoreKeyboardCallbacks
{
    void SG_EXPORT (*key)(void* keyboard, SGuint key, SGbool down);
    void SG_EXPORT (*chr)(void* keyboard, SGuint chr, SGbool down);
} SGCoreKeyboardCallbacks;

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgCoreKeyboardCreate(void** keyboard, void* window);
    SGuint SG_EXPORT sgCoreKeyboardDestroy(void* keyboard);
    //SGuint SG_EXPORT sgCoreKeyboardSetKey(void* keyboard, SGuint key, SGbool down);
    SGuint SG_EXPORT sgCoreKeyboardGetKey(void* keyboard, SGuint key, SGbool* down);
    //SGuint SG_EXPORT sgCoreKeyboardSetChr(void* keyboard, SGuint chr, SGbool down);
    //SGuint SG_EXPORT sgCoreKeyboardGetChr(void* keyboard, SGuint chr, SGbool* down);

    SGuint SG_EXPORT sgCoreKeyboardSetCallbacks(void* keyboard, SGCoreKeyboardCallbacks* callbacks);
    //SGuint SG_EXPORT sgCoreKeyboardGetCallbacks(void* keyboard, SGCoreKeyboardCallbacks** callbacks);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_CORE_KEYBOARD_H__
