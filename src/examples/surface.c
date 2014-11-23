#include <siege/siege.h>

#include <stdlib.h>
#include <math.h>

int main(void)
{
    sgInit(0);
    sgWindowOpen(640, 480, 32, 0);
    sgWindowSetTitle("SIEGE Surface Demo - Press F1 to clear surface");

    SGSurface* surf = sgSurfaceCreate(640, 480, 32);
    sgSurfaceClear(surf);

    SGIVec2 mpos;
    while(sgLoop(NULL))
    {
        if(sgKeyboardKeyPress(SG_KEY_F1))
            sgSurfaceClear(surf);

        mpos = sgMouseGetPos2iv();

        sgSurfaceTarget(surf);
        sgDrawColor4f(0.0, 0.5, 0.75, 1.0);
        sgDrawCircle2f(mpos.x, mpos.y, 16, SG_TRUE);

        sgDrawColor4f(0.0, 0.75, 1.0, 1.0);
        sgDrawCircle2f(mpos.x, mpos.y, 16, SG_FALSE);
        sgSurfaceUntarget(surf);

        sgDrawColor4f(1.0, 1.0, 1.0, 1.0);
        sgSurfaceDraw(surf);

        sgWindowSwapBuffers();
        sgDrawClear();
    }

    sgSurfaceDestroy(surf);

    sgDeinit();

    return 0;
}
