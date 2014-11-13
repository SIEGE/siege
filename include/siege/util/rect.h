#ifndef __SIEGE_UTIL_RECT_H__
#define __SIEGE_UTIL_RECT_H__

#include "../common.h"
#include "vector.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct SGRect
{
    SGVec2 a;
    SGVec2 b;
} SGRect;

SGRect SG_CALL sgRect(float x1, float y1, float x2, float y2);
SGRect SG_CALL sgRectWH(float x, float y, float w, float h);

SGVec2 SG_CALL sgRectSize(SGRect rect);
SGVec2 SG_CALL sgRectCenter(SGRect rect);
SGRect SG_CALL sgRectOffset2f(SGRect rect, float x, float y);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* __SIEGE_UTIL_RECT_H__ */
