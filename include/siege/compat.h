#ifndef __SIEGE_COMPAT_H__
#define __SIEGE_COMPAT_H__

//#define SG_NEW_API
//#define SG_OLD_API

#if defined(SG_NEW_API) && defined(SG_OLD_API)
#error "Only one of SG_NEW_API and SG_OLD_API must be defined"
#elif !defined(SG_NEW_API) && !defined(SG_OLD_API)
#define SG_OLD_API
#endif

#define sgDrawVertex2fvNEW(vert)    sgdrawVertex2fv(vert)
#define sgDrawVertex3fvNEW(vert)    sgdrawVertex3fv(vert)

#ifdef SG_OLD_API
#define sgColor4fv(rgba)    sgColor4fp(rgba)
#define sgColor3fv(rgb)     sgColor4fp(rgb)
#define sgColor2fv(ga)      sgColor4fp(ga)
#define sgColor1fv(g)       sgColor4fp(g)
#define sgRect(x,y)         sgRect2f(x,y)
#define sgRectWH(x,y)       sgRect2fWH(x,y)

#define sgEntitySetPos(entity, x, y)                        sgEntitySetPos2f(entity, x, y)
#define sgEntityGetPos(entity, px, py)                      do { SGVec2 _sg_tmp = sgEntityGetPos2fv(entity); *(px) = _sg_tmp.x; *(py) = _sg_tmp.y; } while(0)
#define sgDrawColor4fv(rgba)                                sgDrawColor4fp(rgba)
#define sgDrawColor3fv(rgb)                                 sgDrawColor4fp(rgb)
#define sgDrawColor2fv(ga)                                  sgDrawColor4fp(ga)
#define sgDrawColor1fv(g)                                   sgDrawColor4fp(g)
#define sgDrawVertex3fv(xyz)                                sgDrawVertex3fp(xyz)
#define sgDrawVertex2fv(xy)                                 sgDrawVertex2fp(xy)
#define sgDrawTexCoord2fv(st)                               sgDrawTexCoord2fp(st)
#define sgDrawClear4fv(rgba)                                sgDrawClear4fp(rgba)
#define sgDrawClear3fv(rgb)                                 sgDrawClear4fp(rgb)
#define sgDrawClear2fv(ga)                                  sgDrawClear4fp(ga)
#define sgDrawClear1fv(g)                                   sgDrawClear4fp(g)
#define sgDrawPoint(x, y)                                   sgDrawPoint2f(x, y)
#define sgDrawLine(x1, y1, x2, y2)                          sgDrawLine2f(x1, y1, x2, y2)
#define sgDrawTriangle(x1, y1, x2, y2, x3, y3, fill)        sgDrawTriangle2f(x1, y1, x2, y2, x3, y3, fill)
#define sgDrawQuad(x1, y1, x2, y2, x3, y3, x4, y4, fill)    sgDrawQuad2f(x1, y1, x2, y2, x3, y3, x4, y4, fill)
#define sgDrawRectangle(x1, y1, x2, y2, fill)               sgDrawRectangle2f(x1, y1, x2, y2, fill)
#define sgDrawRectangleWH(x1, y1, x2, y2, fill)             sgDrawRectangle2fWH(x1, y1, x2, y2, fill)
#define sgDrawRectangleRound(x1, y1, x2, y2, rx, ry, fill)   sgDrawRectangleRound2f(x1, y1, x2, y2, rx, ry, fill)
#define sgDrawRectangleRoundWH(x1, y1, x2, y2, rx, ry, fill) sgDrawRectangleRound2fWH(x1, y1, x2, y2, rx, ry, fill)
#define sgDrawEllipse2R(x, y, rx, ry, fill)                 sgDrawEllipse2f2R(x, y, rx, ry, fill)
#define sgDrawCircle(x, y, radius, fill)                    sgDrawCircle2f(x, y, radius, fill)
#define sgDrawEArcRads(x, y, rx, ry, a1, a2, ccw, fill)     sgDrawEArcRads2f(x, y, rx, ry, a1, a2, ccw, fill)
#define sgDrawEArcDegs(x, y, rx, ry, a1, a2, ccw, fill)     sgDrawEArcDegs2f(x, y, rx, ry, a1, a2, ccw, fill)
#define sgDrawArcRads(x, y, r, a1, a2, ccw, fill)           sgDrawArcRads2f(x, y, r, a1, a2, ccw, fill)
#define sgDrawArcDegs(x, y, r, a1, a2, ccw, fill)           sgDrawArcDegs2f(x, y, r, a1, a2, ccw, fill)
#endif

#endif /* __SIEGE_COMPAT_H__ */
