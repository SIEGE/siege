#ifndef __SIEGE_BACKEND_CORE_MOUSE_H__
#define __SIEGE_BACKEND_CORE_MOUSE_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct SGCoreMouseCallbacks
    {
        void SG_EXPORT (*button)(void* mouse, SGuint button, SGbool action);
        void SG_EXPORT (*move)(void* mouse, SGint x, SGint y);
        void SG_EXPORT (*wheel)(void* mouse, SGint w);
    } SGCoreMouseCallbacks;
    /**
        WARNING: Subject to change
    */
    SGuint SG_EXPORT sgmCoreMouseCreate(void** mouse, void* window);
    SGuint SG_EXPORT sgmCoreMouseDestroy(void* mouse);
    // should these two [sgCoreMouseShow,sgCoreMouseHide] be put into a single function?
    SGuint SG_EXPORT sgmCoreMouseShow(void* mouse);
    SGuint SG_EXPORT sgmCoreMouseHide(void* mouse);
    //SGuint SG_EXPORT sgmCoreMouseIsShown(void* mouse, SGbool* shown);
    //SGuint SG_EXPORT sgmCoreMouseIsHidden(void* mouse, SGbool* hidden);
    SGuint SG_EXPORT sgmCoreMouseGetNumButtons(void* mouse, SGuint* numbuttons);
    //SGuint SG_EXPORT sgmCoreMouseSetButtons(void* mouse, SGbool* state);
    SGuint SG_EXPORT sgmCoreMouseGetButtons(void* mouse, SGbool* state);
    SGuint SG_EXPORT sgmCoreMouseSetPosition(void* mouse, SGint x, SGint y);
    SGuint SG_EXPORT sgmCoreMouseGetPosition(void* mouse, SGint* x, SGint* y);
    //SGuint SG_EXPORT sgmCoreMouseSetWheel(void* mouse, SGint w);
    SGuint SG_EXPORT sgmCoreMouseGetWheel(void* mouse, SGint* w);

    SGuint SG_EXPORT sgmCoreMouseSetCallbacks(void* mouse, SGCoreMouseCallbacks* callbacks);
    //SGuint SG_EXPORT sgmCoreMouseGetCallbacks(void* mouse, SGCoreMouseCallbacks** callbacks);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_CORE_MOUSE_H__
