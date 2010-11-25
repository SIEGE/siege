#include <siege/siege.h>
#include <stdlib.h>

int main()
{
	sgLoadModule("SDL");
	sgLoadModule("OpenGL");
    sgLoadModule("Freetype");
	sgInit(640, 480, 32, 0);
    SGFont* font = sgFontCreate("data/fonts/DejaVuLGCSans.ttf", 24.0, 127);
	SGint ret;
	while(sgLoop(&ret))
	{
		sgFontPrintCentered(font, sgWindowGetWidth() / 2, sgWindowGetHeight() / 2, "hello, world");

		sgWindowSwapBuffers();
		sgDrawClear();
	}
	sgFontDestroy(font);
	sgDeinit();
	return ret;
}

