#include <siege/siege.h>

#include <stdlib.h>
#include <math.h>

SGSprite* sprCrateSmall;
SGSprite* sprFloorMetalPlate;
SGSprite* sprHazardWall;
SGSprite* sprPacman;
SGSprite* sprStrongboxSmall;
SGSprite* sprSupportBar;

int main(void)
{
    sgInit(0);
    sgWindowOpen(640, 480, 32, 0);
    sgWindowSetTitle("SIEGE Sprite Demo");

    sprCrateSmall = sgSpriteCreateFile("data/sprites/CrateSmall.png");
    sprFloorMetalPlate = sgSpriteCreateFile("data/sprites/FloorMetalPlate.png");
    sprHazardWall = sgSpriteCreateFile("data/sprites/HazardWall.png");
    sprPacman = sgSpriteCreateFile("data/sprites/Pacman.png");
    sprStrongboxSmall = sgSpriteCreateFile("data/sprites/StrongboxSmall.png");
    sprSupportBar = sgSpriteCreateFile("data/sprites/SupportBar.png");

    SGuint i;
    while(sgLoop(NULL))
    {
        sgSpriteDraw2f(sprCrateSmall, 64, 256);
        sgSpriteDraw2f(sprStrongboxSmall, 640 - 64, 256);
        sgSpriteDrawRads2f1f(sprPacman, 320, 128, atan2(sgMouseGetPosY() - 128, sgMouseGetPosX() - 320));

        for(i = 32; i < 640; i += 64)
            sgSpriteDraw2f(sprFloorMetalPlate, i, 448);
        for(i = 224; i < 448; i += 64)
            sgSpriteDraw2f(sprSupportBar, i, 384);
        for(i = 224; i < 448; i += 64)
            sgSpriteDraw2f(sprHazardWall, i, 320);

        sgWindowSwapBuffers();
        sgDrawClear();
    }

    sgSpriteDestroy(sprCrateSmall);
    sgSpriteDestroy(sprFloorMetalPlate);
    sgSpriteDestroy(sprHazardWall);
    sgSpriteDestroy(sprPacman);
    sgSpriteDestroy(sprStrongboxSmall);
    sgSpriteDestroy(sprSupportBar);

    sgDeinit();

    return 0;
}
