#include <siege/siege.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STEP 1

int main(void)
{
    sgInit(0);
    sgWindowOpen(640, 480, 32, 0);
    sgWindowSetTitle("SIEGE Gradient Demo");

    SGGradient* grad = sgGradientCreate();

    sgGradientSetStopKey(grad, 0.00, 1.0);
    sgGradientSetStopKey(grad, 0.25, 0.5);
    sgGradientSetStopKey(grad, 0.30, 0.0);
    sgGradientSetStopKey(grad, 0.50, 1.0);
    sgGradientSetStopKey(grad, 0.70, 1.0);
    sgGradientSetStopKey(grad, 0.75, 0.5);
    sgGradientSetStopKey(grad, 1.00, 1.0);

    size_t i;
    while(sgLoop(NULL))
    {
        for(i = 0; i < 640; i += STEP)
        {
            grad->interp = _sgGradientInterpNearest;
            sgDrawColor2f(1.0, sgGradientGetValue(grad, i / (640.0 - STEP)));
            sgDrawRectangle2fWH(i, 480 / 4 * 0, STEP, 480 / 4, SG_TRUE);

            grad->interp = _sgGradientInterpLinear;
            sgDrawColor2f(1.0, sgGradientGetValue(grad, i / (640.0 - STEP)));
            sgDrawRectangle2fWH(i, 480 / 4 * 1, STEP, 480 / 4, SG_TRUE);

            grad->interp = _sgGradientInterpCosine;
            sgDrawColor2f(1.0, sgGradientGetValue(grad, i / (640.0 - STEP)));
            sgDrawRectangle2fWH(i, 480 / 4 * 2, STEP, 480 / 4, SG_TRUE);

            grad->interp = _sgGradientInterpCubic;
            sgDrawColor2f(1.0, sgGradientGetValue(grad, i / (640.0 - STEP)));
            sgDrawRectangle2fWH(i, 480 / 4 * 3, STEP, 480 / 4, SG_TRUE);
        }
        sgDrawColor4f(1.0, 0.75, 0.0, 0.25);
        for(i = 0; i < grad->numvals; i++)
            sgDrawLine2f(grad->vals[i].x * 640, 0, grad->vals[i].x * 640, 480);

        sgWindowSwapBuffers();
        sgDrawClear();
    }

    sgGradientDestroy(grad);

    sgDeinit();

    return 0;
}
