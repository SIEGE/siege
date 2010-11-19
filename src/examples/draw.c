#include <siege/siege.h>

#include <stdlib.h>
#include <math.h>

SGFont* font;
int main()
{
	sgLoadModule("SDL");
	sgLoadModule("OpenGL");
	sgInit(640, 480, 32, 0);
	sgWindowSetTitle("SIEGE Draw Demo");

	while(sgLoop(NULL))
	{
		sgDrawColor4f(0.0, 0.0, 1.0, 1.0);
		sgDrawEArcDegs(96, 32, 32, 32, 0, 45, SG_FALSE, SG_TRUE);
		sgDrawColor4f(0.0, 1.0, 0.0, 1.0);
		sgDrawEArcDegs(160, 32, 32, 32, 45, 0, SG_FALSE, SG_TRUE);

		sgDrawColor4f(0.0, 1.0, 1.0, 1.0);
		sgDrawEArcDegs(96, 96, 32, 32, 0, 45, SG_TRUE, SG_TRUE);
		sgDrawColor4f(1.0, 0.0, 0.0, 1.0);
		sgDrawEArcDegs(160, 96, 32, 32, 45, 0, SG_TRUE, SG_TRUE);

		sgDrawColor4f(1.0, 1.0, 1.0, 1.0);
		sgDrawCircle(32, 32, 32, SG_TRUE);

		sgDrawCircle(96, 32, 32, SG_FALSE);
		sgDrawCircle(160, 32, 32, SG_FALSE);
		sgDrawCircle(96, 96, 32, SG_FALSE);
		sgDrawCircle(160, 96, 32, SG_FALSE);

		sgWindowSwapBuffers();
		sgDrawClear();
	}

	sgDeinit();

	return 0;
}
