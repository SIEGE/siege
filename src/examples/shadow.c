#include <siege/siege.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

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

// SG_TRUE if they should be mulplicative, SG_FALSE for additive!
SGbool multLights = SG_TRUE;
SGbool sqrmult = SG_TRUE;

SGbool overlayDBG = SG_FALSE;
clock_t prev;
clock_t curr;

SGSprite* tile;
SGSurface* tileset;

void evTick(SGEntity* ent)
{
    sgLightSpaceUpdate(space);

    lights[0]->pos.x = sgMouseGetPosX();
    lights[0]->pos.y = sgMouseGetPosY();

    curr = clock();
    if(curr - prev >= 1000/60)
        sgMSleep(curr - prev - 1000/60);
    prev = curr;
}
void evDraw(SGEntity* ent)
{
    sgDrawColor4f(1.0, 1.0, 1.0, 1.0);
    sgSurfaceDraw(tileset);

    size_t i;
    for(i = 0; i < NSHAPES; i++)
        sgShadowShapeDrawDBG(shapes[i], SG_TRUE);
    for(i = 0; i < NSHAPES; i++)
        sgShadowShapeDrawDBG(shapes[i], SG_FALSE);

    sgDrawColor4f(1.0, 1.0, 1.0, 1.0);
    sgLightSpaceDraw(space, (multLights ? SG_SHADOW_DRAW_MUL : 0) | (sqrmult ? SG_SHADOW_DRAW_SQR : 0));

    //sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_SRC_ALPHA, SG_GRAPHICS_FUNC_ONE_MINUS_SRC_ALPHA);

    if(overlayDBG)
        sgLightSpaceDrawDBG(space, 0);
}
void evKeyboardKeyPress(SGEntity* ent, SGenum key)
{
    switch(key)
    {
        case SG_KEY_F1:
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

int main(void)
{
    sgLoadModule("SDL");
    sgLoadModule("OpenGL");
    sgLoadModule("STB-Image");
    sgInit(/*SG_INIT_RENDERTHREAD*/0);
    sgWindowOpen(640, 480, 32, 0);
    sgWindowSetTitlef("SIEGE Shadows Demo - Press F1 for debug overlay, 1-%u to toggle lights", NLIGHTS);

    space = sgLightSpaceCreate();
    sgLightSpaceSetAmbience4f(space, 0.125, 0.0625, 0.0, 1.0);

    SGEntity* handler = sgEntityCreate();
    handler->evTick = evTick;
    handler->evDraw = evDraw;
    handler->evKeyboardKeyPress = evKeyboardKeyPress;

    tile = sgSpriteCreateFile2f("data/sprites/FloorMetalPlate.png", 0.0, 0.0);
    tileset = sgSurfaceCreate(640, 480, 32);

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

    prev = clock();

    SGint ret = sgRun();

    sgSurfaceDestroy(tileset);
    sgSpriteDestroy(tile);

    sgLightSpaceDestroy(space);

    sgDeinit();

    return ret;
}
