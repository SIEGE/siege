#include <siege/siege.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define NSHAPES 3
#define NLIGHTS 4

SGLightSpace* space;
SGShadowShape* shapes[NSHAPES];

SGLight* lights[NLIGHTS];
SGSurface* lightBuf;

SGLight* createLight(SGVec2 pos, SGColor color, float radius, float angle, float arc)
{
    SGLight* light = sgLightCreate(space, pos.x, pos.y, radius);
    sgLightSetColor4f(light, color.r, color.g, color.b, color.a);
    sgLightSetAngleDegs(light, angle);
    sgLightSetConeDegs(light, arc);
    return light;
}

SGbool overlayDBG = SG_FALSE;

void evKeyboardKeyPress(SGEntity* ent, SGenum key)
{
    switch(key)
    {
        case SG_KEYBOARD_KEY_F1:
            overlayDBG = !overlayDBG;
            break;

        default:
            if('1' <= key && key <= '9')
            {
                if(key - '1' < NLIGHTS)
                    sgLightSetActive(lights[key - '1'], !sgLightGetActive(lights[key - '1']));
            }
            break;
    }
}

int main()
{
    sgLoadModule("SDL");
    sgLoadModule("OpenGL");
    sgLoadModule("DevIL");
    sgInit(640, 480, 32, 0);
    sgWindowSetTitlef("SIEGE Shadows Demo - Press F1 for debug overlay, 1-%d to toggle lights", NLIGHTS);

    space = sgLightSpaceCreate();
    sgLightSpaceSetAmbience4f(space, 0.125, 0.0625, 0.0, 1.0);

    SGEntity* handler = sgEntityCreate(0.0, SG_EVT_ALL);
    handler->evKeyboardKeyPress = evKeyboardKeyPress;

    SGSprite* tile = sgSpriteCreateFile2f("data/sprites/FloorMetalPlate.png", 0.0, 0.0);
    SGSurface* tileset = sgSurfaceCreate(640, 480, 32);

    size_t i, j;

    sgSurfaceClear(tileset);
    sgDrawColor4f(1.0, 1.0, 1.0, 1.0);
    sgSurfaceTarget(tileset);
        for(i = 0; i <= 640 / sgSpriteGetWidth(tile); i++)
            for(j = 0; j <= 480 / sgSpriteGetHeight(tile); j++)
                sgSpriteDraw2f(tile, i * sgSpriteGetWidth(tile), j * sgSpriteGetHeight(tile));
    sgSurfaceUntarget(tileset);

    shapes[0] = sgShadowShapeCreatePoly(space, 0, 0,
                                       (float[]){200, 250
                                                ,400, 250
                                                ,375, 350
                                                ,225, 350}, 4);
    shapes[1] = sgShadowShapeCreatePoly(space, 0, 0,
                                       (float[]){100,  50
                                                ,200,  50
                                                ,200, 150
                                                ,100, 150}, 4);
    shapes[2] = sgShadowShapeCreatePoly(space, 0, 0,
                                       (float[]){400, 100
                                                ,500, 100
                                                ,450, 200}, 3);

    lights[0] = createLight((SGVec2){60 , 60 }, (SGColor){0.5 , 1.0, 1.0, 1.0}, 192, 0, 360);
    lights[1] = createLight((SGVec2){500, 300}, (SGColor){0.75, 1.0, 0.0, 0.5}, 256, 0, 360);
    lights[2] = createLight((SGVec2){200, 400}, (SGColor){1.0 , 0.5, 0.0, 1.0}, 128, 0, 360);
    lights[3] = createLight((SGVec2){50 , 50 }, (SGColor){1.0 , 1.0, 1.0, 1.0}, 320, 45, 60);

    // SG_TRUE if they should be mulplicative, SG_FALSE for additive!
    SGbool multLights = SG_TRUE;
    SGbool sqrmult = SG_TRUE;

    while(sgLoop(NULL))
    {
        sgLightSpaceUpdate(space);
        sgLightSpaceDraw(space, (multLights ? SG_SHADOW_DRAW_MUL : 0) | (sqrmult ? SG_SHADOW_DRAW_SQR : 0));

        //sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_SRC_ALPHA, SG_GRAPHICS_FUNC_ONE_MINUS_SRC_ALPHA);

        lights[0]->pos.x = sgMouseGetPosX();
        lights[0]->pos.y = sgMouseGetPosY();

        if(overlayDBG)
            sgLightSpaceDrawDBG(space, 0);

        sgWindowSwapBuffers();
        sgDrawClear();

        sgDrawColor4f(1.0, 1.0, 1.0, 1.0);
        sgSurfaceDraw(tileset);

        for(i = 0; i < NSHAPES; i++)
            sgShadowShapeDrawDBG(shapes[i], SG_TRUE);
        for(i = 0; i < NSHAPES; i++)
            sgShadowShapeDrawDBG(shapes[i], SG_FALSE);
    }

    sgSurfaceDestroy(tileset);
    sgSpriteDestroy(tile);

    sgLightSpaceDestroy(space);

    sgDeinit();

    return 0;
}
