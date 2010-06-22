#ifndef __SIEGE_CORE_MOUSE_H__
#define __SIEGE_CORE_MOUSE_H__

#include "../../common.h"

typedef struct SGCoreMouseCallbacks
{
    void SG_EXPORT (*button)(void* mouse, SGuint button, SGbool action);
    void SG_EXPORT (*move)(void* mouse, SGint x, SGint y);
    void SG_EXPORT (*wheel)(void* mouse, SGint w);
} SGCoreMouseCallbacks;

#ifdef __cplusplus
extern "C"
{
#endif
    /**
        WARNING: Subject to change
    */
    SGuint SG_EXPORT sgCoreMouseCreate(void** mouse, void* window);
    SGuint SG_EXPORT sgCoreMouseDestroy(void* mouse);
    // should these two [sgCoreMouseShow,sgCoreMouseHide] be put into a single function?
    SGuint SG_EXPORT sgCoreMouseShow(void* mouse);
    SGuint SG_EXPORT sgCoreMouseHide(void* mouse);
    //SGuint SG_EXPORT sgCoreMouseIsShown(void* mouse, SGbool* shown);
    //SGuint SG_EXPORT sgCoreMouseIsHidden(void* mouse, SGbool* hidden);
    SGuint SG_EXPORT sgCoreMouseGetNumButtons(void* mouse, SGuint* numbuttons);
    //SGuint SG_EXPORT sgCoreMouseSetButtons(void* mouse, SGbool* state);
    SGuint SG_EXPORT sgCoreMouseGetButtons(void* mouse, SGbool* state);
    SGuint SG_EXPORT sgCoreMouseSetPosition(void* mouse, SGint x, SGint y);
    SGuint SG_EXPORT sgCoreMouseGetPosition(void* mouse, SGint* x, SGint* y);
    //SGuint SG_EXPORT sgCoreMouseSetWheel(void* mouse, SGint w);
    SGuint SG_EXPORT sgCoreMouseGetWheel(void* mouse, SGint* w);

    SGuint SG_EXPORT sgCoreMouseSetCallbacks(void* mouse, SGCoreMouseCallbacks* callbacks);
    //SGuint SG_EXPORT sgCoreMouseGetCallbacks(void* mouse, SGCoreMouseCallbacks** callbacks);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_CORE_MOUSE_H__
