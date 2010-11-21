#include <siege/siege.h>

#include <stdlib.h>
#include <math.h>

SGFont* font;
int main()
{
	sgLoadModule("SDL");
	sgLoadModule("OpenGL");
	sgLoadModule("DevIL");
	sgInit(640, 480, 32, 0);
	sgWindowSetTitle("SIEGE Collision Detection Example");

	SGSprite* pacman = sgSpriteCreateFile("data/sprites/Pacman.png");
	SGMask* pacmanm = sgMaskCreateSprite(pacman);

	SGSprite* support = sgSpriteCreateFile("data/sprites/SupportBar.png");
	SGMask* supportm = sgMaskCreateSprite(support);

	SGint mx, my;
	while(sgLoop(NULL))
	{
		sgMouseGetPos(&mx, &my);
		mx -= mx % 2;
		my -= my % 2;

		sgDrawColor4f(1.0, 1.0, 1.0, 1.0);

		if(sgMaskCheckCollision(supportm, 320, 240,
								pacmanm, mx, my))
			sgDrawColor4f(1.0, 0.0, 0.0, 1.0);
		//sgMaskDrawDBG(supportm, 320, 240, SG_TRUE);
		//sgMaskDrawDBG(pacmanm, mx, my, SG_TRUE);

		sgSpriteDraw2f(support, 320, 240);
		sgSpriteDraw2f(pacman, mx, my);

		sgDrawColor4f(1.0, 1.0, 1.0, 1.0);
		sgMaskDrawDBG(supportm, 480, 360, SG_TRUE);
		sgMaskDrawDBG(pacmanm, 544, 360, SG_TRUE);

		sgWindowSwapBuffers();
		sgDrawClear();
	}

	sgMaskDestroy(supportm);
	sgSpriteDestroy(support);

	sgMaskDestroy(pacmanm);
	sgSpriteDestroy(pacman);

	sgDeinit();

	return 0;
}
