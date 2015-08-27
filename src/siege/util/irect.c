#include <siege/util/irect.h>

SGIRect SG_CALL sgIRect2iv(SGIVec2 a, SGIVec2 b)
{
    SGIRect rect;
    rect.a = a;
    rect.b = b;
    return rect;
}
SGIRect SG_CALL sgIRect2i(SGint x1, SGint y1, SGint x2, SGint y2)
{
    return sgIRect2iv(sgIVec2i(x1, y1), sgIVec2i(x2, y2));
}
SGIRect SG_CALL sgIRect2ivWH(SGIVec2 pos, SGIVec2 size)
{
    return sgIRect2iv(pos, sgIVec2Add(pos, size));
}
SGIRect SG_CALL sgIRectWH(SGint x, SGint y, SGint w, SGint h)
{
    return sgIRect2ivWH(sgIVec2i(x, y), sgIVec2i(w, h));
}

SGIVec2 SG_CALL sgIRectSize(SGIRect rect)
{
    return sgIVec2Sub(rect.b, rect.a);
}
SGIRect SG_CALL sgIRectOffset2fv(SGIRect rect, SGIVec2 off)
{
    rect.a = sgIVec2Add(rect.a, off);
    rect.b = sgIVec2Add(rect.b, off);
    return rect;
}
SGIRect SG_CALL sgIRectOffset2f(SGIRect rect, SGint x, SGint y)
{
    return sgIRectOffset2fv(rect, sgIVec2i(x, y));
}
