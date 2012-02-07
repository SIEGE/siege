#include <siege/siege.h>

#include <stdlib.h>
#include <math.h>

int main(void)
{
	sgLoadModule("SDL");
	sgLoadModule("OpenGL");
	sgInit(0);
	sgWindowOpen(640, 480, 32, 0);
	sgWindowSetTitle("SIEGE Draw Demo");

	while(sgLoop(NULL))
	{
		sgDrawColor4f(0.0, 0.0, 1.0, 1.0);
		sgDrawEArcDegs(192, 32, 64, 32, 0, 45, SG_FALSE, SG_TRUE);
		sgDrawColor4f(0.0, 1.0, 0.0, 1.0);
		sgDrawEArcDegs(320, 32, 64, 32, 45, 0, SG_FALSE, SG_TRUE);

		sgDrawColor4f(0.0, 1.0, 1.0, 1.0);
		sgDrawEArcDegs(192, 96, 64, 32, 0, 45, SG_TRUE, SG_TRUE);
		sgDrawColor4f(1.0, 0.0, 0.0, 1.0);
		sgDrawEArcDegs(320, 96, 64, 32, 45, 0, SG_TRUE, SG_TRUE);

		sgDrawColor4f(1.0, 1.0, 1.0, 1.0);
		sgDrawEllipse2R(64, 32, 64, 32, SG_TRUE);

		sgDrawEllipse2R(192, 32, 64, 32, SG_FALSE);
		sgDrawEllipse2R(320, 32, 64, 32, SG_FALSE);
		sgDrawEllipse2R(192, 96, 64, 32, SG_FALSE);
		sgDrawEllipse2R(320, 96, 64, 32, SG_FALSE);

		sgDrawColor4f(1.0, 0.0, 0.0, 1.0);
		sgDrawLine(64, 160, 192, 288);

        sgDrawColor4f(0.0, 0.5, 0.75, 1.0);
        sgDrawRectangleRoundWH(320, 240, 128, 128, 32, 16, SG_TRUE);

        sgDrawColor4f(0.0, 0.75, 1.0, 1.0);
        sgDrawRectangleRoundWH(320, 240, 128, 128, 32, 16, SG_FALSE);

		sgWindowSwapBuffers();
		sgDrawClear();
	}

	sgDeinit();

	return 0;
}
