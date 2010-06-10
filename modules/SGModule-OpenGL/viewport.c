#include "main.h"
#include "viewport.h"

SGuint SG_EXPORT sgGraphicsViewportCreate(void** viewport, void* context)
{
    // OpenGL doesn't need this
    return SG_OK;
}
//SGuint SG_EXPORT sgGraphicsViewportCreateView(void** viewport, void* context, SGuint wx, SGuint wy, SGuint wwidth, SGuint wheight, float x, float y, float width, float height)
SGuint SG_EXPORT sgGraphicsViewportDestroy(void* viewport)
{
    // neither does it need this
    return SG_OK;
}
SGuint SG_EXPORT sgGraphicsViewportSetView(void* viewport, SGuint wx, SGuint wy, SGuint wwidth, SGuint wheight, float x, float y, float width, float height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(wx, wy, wwidth, wheight);
    glOrtho(x, width, height, y, -128, 127);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    return SG_OK;
}
//SGuint SG_EXPORT sgGraphicsViewportGetView(void* viewport, SGuint* wx, SGuint* wy, SGuint* wwidth, SGuint* wheight, float* x, float* y, float* width, float* height)
