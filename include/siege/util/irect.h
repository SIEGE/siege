#ifndef __SIEGE_UTIL_IRECT_H__
#define __SIEGE_UTIL_IRECT_H__

#include "../common.h"
#include "ivector.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct SGIRect
{
    SGIVec2 a;
    SGIVec2 b;
} SGIRect;

SG_EXPORT SGIRect SG_CALL sgIRect2iv(SGIVec2 a, SGIVec2 b);
SG_EXPORT SGIRect SG_CALL sgIRect2i(SGint x1, SGint y1, SGint x2, SGint y2);
SG_EXPORT SGIRect SG_CALL sgIRect2ivWH(SGIVec2 pos, SGIVec2 size);
SG_EXPORT SGIRect SG_CALL sgIRectWH(SGint x, SGint y, SGint w, SGint h);

SGIVec2 SG_CALL sgIRectSize(SGIRect rect);
SGIRect SG_CALL sgIRectOffset2iv(SGIRect rect, SGIVec2 off);
SGIRect SG_CALL sgIRectOffset2i(SGIRect rect, SGint x, SGint y);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* __SIEGE_UTIL_IRECT_H__ */
