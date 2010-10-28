#include <siege/siege.h>
#include <stdlib.h>

int main()
{
	sgLoadModule("SDL");
	sgLoadModule("OpenGL");
	sgInit(640, 480, 32, 0);
	SGint ret;
	while(sgLoop(&ret))
	{
		sgWindowSwapBuffers();
		sgDrawClear();
	}
	sgDeinit();
	return ret;
}

/**
 * \example hello/main_step2.c
 * The minimal running program.
 */

