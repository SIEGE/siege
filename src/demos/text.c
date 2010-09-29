#include <siege/siege.h>

#include <stdlib.h>
#include <math.h>

SGFont* font;
int main()
{
    sgLoadModule("SDL");
    sgLoadModule("OpenGL");
    sgLoadModule("Freetype");
    sgInit(640, 480, 32, 0);
    sgWindowSetTitle("SIEGE Text Demo");

    font = sgFontCreate("data/fonts/DejaVuLGCSans.ttf", 10, 256);

    SGuint width = sgWindowGetWidth();
    SGuint height = sgWindowGetHeight();

    while(sgLoop(NULL))
    {
        sgDrawColor4f(1.0, 0.0, 0.0, 1.0);

        sgFontPrint(font, width / 2, height - 64.0, "Mouse angle: %f", atan2(-sgMouseGetPosY() + (float)height / 2, sgMouseGetPosX() - (float)width / 2) * 180.0 / M_PI);

        sgDrawColor4f(0.0, 1.0, 0.0, 1.0);
        sgFontPrint(font, width / 2, height - 92.0, "Mouse: %d,%d %d", sgMouseGetPosX(), sgMouseGetPosY(), sgMouseGetWheel());

        sgFontPrint(font, 128.0, height - 128.0, "AAA\nBBB\nCCC\nDDD\n\nEEE");

        sgDrawColor4f(0.0, 0.5, 0.75, 0.75);
        sgFontPrint(font, width / 4, height / 3, "Well, this is some more text...\nUseful for UI, consoles, etc...");

        sgDrawColor4f(1.0, 1.0, 0.0, 0.75);
        sgDrawLine(width / 2, height / 2, sgMouseGetPosX(), sgMouseGetPosY());
        sgDrawLine(width / 2, height / 2, sgMouseGetPosX(), height / 2);
        sgDrawLine(width / 2, height / 2, width / 2, sgMouseGetPosY());

        sgDrawColor4f(1.0, 1.0, 1.0, 1.0);
        sgFontPrint(font, 2, 256, "Testing: ABC abc 012");

        sgWindowSwapBuffers();
        sgDrawClear();
    }

    sgDeinit();

    return 0;
}
