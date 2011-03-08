#include <siege/siege.h>

#include <stdlib.h>
#include <math.h>

int main()
{
    sgLoadModule("SDL");
    sgLoadModule("OpenGL");
    //sgLoadModule("DevIL");
    sgInit(640, 480, 32, 0);
    sgWindowSetTitle("SIEGE A-Star Demo");

    SGuint i;
    while(sgLoop(NULL))
    {


        sgWindowSwapBuffers();
        sgDrawClear();
    }

    sgDeinit();

    return 0;
}
