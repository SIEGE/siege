#include <siege/siege.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define NSHAPES 3
#define NLIGHTS 4

SGShadowShape* shapes[NSHAPES];

void drawPoly(SGShadowShape* shape)
{
    size_t i;

    sgDrawColor4f(0.0, 0.5, 0.75, 1.0);
    sgDrawBegin(SG_GRAPHICS_PRIMITIVE_CONVEX_POLYGON);
        for(i = 0; i < shape->numverts; i++)
            sgDrawVertex2f(shape->verts[i].x, shape->verts[i].y);
    sgDrawEnd();

    sgDrawColor4f(0.0, 1.0, 0.75, 1.0);
    sgDrawBegin(SG_GRAPHICS_PRIMITIVE_LINE_LOOP);
        for(i = 0; i < shape->numverts; i++)
            sgDrawVertex2f(shape->verts[i].x, shape->verts[i].y);
    sgDrawEnd();
}

SGLight* lights[NLIGHTS];
SGSurface* lightBuf;

void drawLight(SGLight* light)
{
    sgSurfaceClear4f(lightBuf, 0.0, 0.0, 0.0, 1.0);
    sgSurfaceTarget(lightBuf);
    sgLightDraw(light);
    sgLightDrawShadows(light);
    sgSurfaceUntarget(lightBuf);
}

SGLight* createLight(SGVec2 pos, SGColor color, float radius, float angle, float arc)
{
    SGLight* light = sgLightCreate(pos.x, pos.y, radius);
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
    sgWindowSetTitleF("SIEGE Shadows Demo - Press F1 for debug overlay, 1-%d to toggle lights", NLIGHTS);

    SGEntity* handler = sgEntityCreate(0.0, SG_EVT_ALL);
    handler->evKeyboardKeyPress = evKeyboardKeyPress;

    SGSprite* tile = sgSpriteCreateFile2f("data/sprites/FloorMetalPlate.png", 0.0, 0.0);
    SGSurface* tileset = sgSurfaceCreate(640, 480, 32);

    lightBuf = sgSurfaceCreate(640, 480, 32);

    size_t i, j;

    sgSurfaceClear(tileset);
    sgDrawColor4f(1.0, 1.0, 1.0, 1.0);
    sgSurfaceTarget(tileset);
        for(i = 0; i <= 640 / sgSpriteGetWidth(tile); i++)
            for(j = 0; j <= 480 / sgSpriteGetHeight(tile); j++)
                sgSpriteDraw2f(tile, i * sgSpriteGetWidth(tile), j * sgSpriteGetHeight(tile));
    sgSurfaceUntarget(tileset);

    shapes[0] = sgShadowShapeCreatePoly(0, 0,
                                       (float[]){200, 250
                                                ,400, 250
                                                ,375, 350
                                                ,225, 350}, 4);
    shapes[1] = sgShadowShapeCreatePoly(0, 0,
                                       (float[]){100,  50
                                                ,200,  50
                                                ,200, 150
                                                ,100, 150}, 4);
    shapes[2] = sgShadowShapeCreatePoly(0, 0,
                                       (float[]){400, 100
                                                ,500, 100
                                                ,450, 200}, 3);

    lights[0] = createLight((SGVec2){60 , 60 }, (SGColor){0.5 , 1.0, 1.0, 1.0}, 192, 0, 360);
    lights[1] = createLight((SGVec2){500, 300}, (SGColor){0.75, 1.0, 0.0, 0.5}, 256, 0, 360);
    lights[2] = createLight((SGVec2){200, 400}, (SGColor){1.0 , 0.5, 0.0, 1.0}, 128, 0, 360);
    lights[3] = createLight((SGVec2){50 , 50 }, (SGColor){1.0 , 1.0, 1.0, 1.0}, 320, 45, 60);

    SGSurface* buffer = sgSurfaceCreate(640, 480, 32);

    // SG_TRUE if they should be mulplicative, SG_FALSE for additive!
    SGbool multLights = SG_TRUE;
    SGbool sqrmult = SG_TRUE;
    SGColor ambience = {0.125, 0.0625, 0.0, 1.0};

    while(sgLoop(NULL))
    {
        sgSurfaceClear4f(buffer, ambience.r, ambience.g, ambience.b, ambience.a);

        for(i = 0; i < NLIGHTS; i++)
        {
            if(!sgLightGetActive(lights[i]))
                continue;

            sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_ONE, SG_GRAPHICS_FUNC_ZERO);
            drawLight(lights[i]);

            sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_SRC_ALPHA, SG_GRAPHICS_FUNC_ONE);
            sgDrawColor4f(1.0, 1.0, 1.0, 1.0);
            sgSurfaceTarget(buffer);
            sgSurfaceDraw(lightBuf);
            sgSurfaceUntarget(buffer);
            //sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_SRC_ALPHA, SG_GRAPHICS_FUNC_ONE_MINUS_SRC_ALPHA);
        }
        sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_SRC_ALPHA, SG_GRAPHICS_FUNC_ONE_MINUS_SRC_ALPHA);

        if(multLights)
        {
            if(sqrmult)
                sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_DST_COLOR, SG_GRAPHICS_FUNC_SRC_COLOR);
            else
                sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_DST_COLOR, SG_GRAPHICS_FUNC_ZERO);
        }
        else
            sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_SRC_ALPHA, SG_GRAPHICS_FUNC_ONE);
        sgSurfaceDraw(buffer);

        sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_SRC_ALPHA, SG_GRAPHICS_FUNC_ONE_MINUS_SRC_ALPHA);

        lights[0]->pos.x = sgMouseGetPosX();
        lights[0]->pos.y = sgMouseGetPosY();

        if(overlayDBG)
        {
            for(i = 0; i < NSHAPES; i++)
            {
                sgShadowShapeDrawDBG(shapes[i]);
            }
            for(i = 0; i < NLIGHTS; i++)
            {
                if(!sgLightGetActive(lights[i]))
                    continue;
                sgLightDrawDBG(lights[i]);
                sgLightDrawShadowsDBG(lights[i]);
            }
        }

        sgWindowSwapBuffers();
        sgDrawClear();

        sgDrawColor4f(1.0, 1.0, 1.0, 1.0);
        sgSurfaceDraw(tileset);

        for(i = 0; i < NSHAPES; i++)
            drawPoly(shapes[i]);
    }

    for(i = 0; i < NSHAPES; i++)
        sgShadowShapeDestroy(shapes[i]);
    for(i = 0; i < NLIGHTS; i++)
        sgLightDestroy(lights[i]);

    sgSurfaceDestroy(lightBuf);

    sgSurfaceDestroy(buffer);
    sgSurfaceDestroy(tileset);
    sgSpriteDestroy(tile);

    sgDeinit();

    return 0;
}
