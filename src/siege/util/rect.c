#include <siege/util/rect.h>

SGRect SG_CALL sgRect2fv(SGVec2 a, SGVec2 b)
{
    SGRect rect;
    rect.a = a;
    rect.b = b;
    return rect;
}
SGRect SG_CALL sgRect2f(float x1, float y1, float x2, float y2)
{
    return sgRect2fv(sgVec2f(x1, y1), sgVec2f(x2, y2));
}
SGRect SG_CALL sgRect2fvWH(SGVec2 pos, SGVec2 size)
{
    return sgRect2fv(pos, sgVec2Add(pos, size));
}
SGRect SG_CALL sgRectWH(float x, float y, float w, float h)
{
    return sgRect2fvWH(sgVec2f(x, y), sgVec2f(w, h));
}

SGVec2 SG_CALL sgRectSize(SGRect rect)
{
    return sgVec2Sub(rect.b, rect.a);
}
SGVec2 SG_CALL sgRectCenter(SGRect rect)
{
    return sgVec2Div(sgVec2Add(rect.a, rect.b), sgVec2f(2.0, 2.0));
}
SGRect SG_CALL sgRectOffset2f(SGRect rect, float x, float y)
{
    SGVec2 off = sgVec2f(x, y);
    rect.a = sgVec2Add(rect.a, off);
    rect.b = sgVec2Add(rect.b, off);
    return rect;
}
