#include <siege/siege.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define NPOLYS 3

typedef struct Polygon
{
    SGEntity* entity;
    SGVec2* points;
    size_t nump;
} Polygon;
Polygon* polys[NPOLYS];

void destroyPoly(Polygon* poly)
{
    poly->entity->lcDestroy = NULL;
    sgEntityDestroy(poly->entity);
    free(poly->points);
    free(poly);
}

void destroyPolyEntity(SGEntity* ent)
{
    destroyPoly(ent->data);
}

void drawPoly(Polygon* poly)
{
    size_t i;

    sgDrawColor4f(0.0, 0.5, 0.75, 1.0);
    sgDrawBegin(SG_GRAPHICS_PRIMITIVE_CONVEX_POLYGON);
        for(i = 0; i < poly->nump; i++)
            sgDrawVertex2f(poly->points[i].x, poly->points[i].y);
    sgDrawEnd();

    sgDrawColor4f(0.0, 1.0, 0.75, 0.5);
    sgDrawBegin(SG_GRAPHICS_PRIMITIVE_LINE_LOOP);
        for(i = 0; i < poly->nump; i++)
            sgDrawVertex2f(poly->points[i].x, poly->points[i].y);
    sgDrawEnd();
}

void drawPolyEntity(SGEntity* ent)
{
    drawPoly(ent->data);
}

Polygon* createPoly(SGVec2* points, size_t nump)
{
    Polygon* poly = malloc(sizeof(Polygon));
    poly->points = malloc(nump * sizeof(SGVec2));
    memcpy(poly->points, points, nump * sizeof(SGVec2));
    poly->nump = nump;

    poly->entity = sgEntityCreate(0.0, SG_EVT_CORE);
    poly->entity->data = poly;
    poly->entity->lcDestroy = destroyPolyEntity;
    poly->entity->evDraw = drawPolyEntity;

    return poly;
}

typedef struct Light
{
    SGEntity* entity;
    SGSurface* surface;
    SGVec2 pos;
    SGColor color;
    float radius;
} Light;
Light* lights[3];

void destroyLight(Light* light)
{
    light->entity->lcDestroy = NULL;
    sgEntityDestroy(light->entity);
    sgSurfaceDestroy(light->surface);
    free(light);
}

void destroyLightEntity(SGEntity* ent)
{
    destroyLight(ent->data);
}

void drawLight(Light* light)
{
    sgSurfaceClear4f(light->surface, 0.0, 0.0, 0.0, 0.0);
    sgSurfaceTarget(light->surface);

    sgDrawColor4f(light->color.r, light->color.g, light->color.b, light->color.a);

    SGVec2* curr;
    SGVec2* next;
    Polygon* poly;
    SGVec2 tmpc, tmpn;
    size_t p, i;

    int sides = SG_MAX(3, (int)(light->radius * 0.5));
    float f = 2 * M_PI / sides;
    sgDrawBegin(SG_GRAPHICS_PRIMITIVE_TRIANGLE_FAN);
        sgDrawColor4f(light->color.r, light->color.g, light->color.b, light->color.a);
        sgDrawVertex2f(light->pos.x, light->pos.y);
        sgDrawColor4f(light->color.r, light->color.g, light->color.b, 0.0);
        for(i = 0; i <= sides; i++)
        {
            sgDrawVertex2f(light->pos.x + cos(f * i) * light->radius,
                           light->pos.y + sin(f * i) * light->radius);
        }
    sgDrawEnd();
    //sgDrawCircle(light->pos.x, light->pos.y, light->radius, SG_TRUE);

    //if(light != lights[0])
    //    return;

    /*sgDrawBegin(SG_GRAPHICS_PRIMITIVE_LINES);
    sgDrawColor4f(1.0, 0.0, 0.0, 1.0);
    for(p = 0; p < NPOLYS; p++)
    {
        poly = polys[p];
        for(i = 0; i < poly->nump; i++)
        {
            curr = &poly->points[i];
            next = &poly->points[(i + 1) % poly->nump];
            if(sgVec2Cross(sgVec2Sub(*next, *curr), sgVec2Sub(*next, light->pos)) <= 0)
            {
                sgDrawVertex2f(curr->x, curr->y);
                sgDrawVertex2f(next->x, next->y);
            }
        }
    }
    sgDrawEnd();*/

    sgDrawColor4f(0.0, 0.0, 0.0, 1.0);
    for(p = 0; p < NPOLYS; p++)
    {
        sgDrawBegin(SG_GRAPHICS_PRIMITIVE_TRIANGLES);
        poly = polys[p];
        for(i = 0; i < poly->nump; i++)
        {
            curr = &poly->points[i];
            next = &poly->points[(i + 1) % poly->nump];
            if(sgVec2Cross(sgVec2Sub(*next, *curr), sgVec2Sub(*next, light->pos)) <= 0)
            {
                tmpc = sgVec2Add(*curr, sgVec2SetLength(sgVec2Sub(*curr, light->pos), 640 + 480));
                tmpn = sgVec2Add(*next, sgVec2SetLength(sgVec2Sub(*next, light->pos), 640 + 480));

                sgDrawVertex2f(curr->x, curr->y);
                sgDrawVertex2f(next->x, next->y);
                sgDrawVertex2f(tmpc.x, tmpc.y);

                sgDrawVertex2f(tmpc.x, tmpc.y);
                sgDrawVertex2f(tmpn.x, tmpn.y);
                sgDrawVertex2f(next->x, next->y);
            }
        }
        sgDrawEnd();
    }

    sgSurfaceUntarget(light->surface);
}

void drawLightEntity(SGEntity* ent)
{
    drawLight(ent->data);
}

Light* createLight(SGVec2 pos, SGColor color, float radius)
{
    Light* light = malloc(sizeof(Light));
    light->pos = pos;
    light->color = color;
    light->radius = radius;

    light->entity = sgEntityCreate(0.0, SG_EVT_CORE);
    light->entity->data = light;
    light->entity->lcDestroy = destroyLightEntity;
    light->entity->evDraw = drawLightEntity;

    light->surface = sgSurfaceCreate(640, 480, 32);

    return light;
}

int main()
{
    sgLoadModule("SDL");
    sgLoadModule("OpenGL");
    sgLoadModule("DevIL");
    sgInit(640, 480, 32, 0);
    sgWindowSetTitle("SIEGE Shadows Demo");

    SGSprite* tile = sgSpriteCreateFile("data/sprites/FloorMetalPlate.png");
    SGSurface* tileset = sgSurfaceCreate(640, 480, 32);

    size_t i, j;

    sgSurfaceClear(tileset);
    sgDrawColor4f(1.0, 1.0, 1.0, 1.0);
    sgSurfaceTarget(tileset);
        for(i = 0; i <= 640 / sgSpriteGetWidth(tile); i++)
            for(j = 0; j <= 480 / sgSpriteGetHeight(tile); j++)
                sgSpriteDraw2f(tile, i * sgSpriteGetWidth(tile), j * sgSpriteGetHeight(tile));
    sgSurfaceUntarget(tileset);

    polys[0] = createPoly((SGVec2[]){(SGVec2){200, 250},
                                     (SGVec2){400, 250},
                                     (SGVec2){375, 350},
                                     (SGVec2){225, 350}}, 4);
    polys[1] = createPoly((SGVec2[]){(SGVec2){100,  50},
                                     (SGVec2){200,  50},
                                     (SGVec2){200, 150},
                                     (SGVec2){100, 150}}, 4);
    polys[2] = createPoly((SGVec2[]){(SGVec2){400, 100},
                                     (SGVec2){500, 100},
                                     (SGVec2){450, 200}}, 3);

    lights[0] = createLight((SGVec2){60, 60}, (SGColor){0.5, 1.0, 1.0, 1.0}, 192);
    lights[1] = createLight((SGVec2){500, 300}, (SGColor){0.75, 1.0, 0.0, 0.5}, 256);
    lights[2] = createLight((SGVec2){200, 400}, (SGColor){1.0, 0.5, 0.0, 1.0}, 128);

    SGSurface* buffer = sgSurfaceCreate(640, 480, 32);

    // SG_TRUE if they should be mulplicative, SG_FALSE for additive!
    SGbool multLights = SG_TRUE;

    while(sgLoop(NULL))
    {
        sgDrawColor4f(1.0, 1.0, 1.0, 1.0);

        sgSurfaceClear(buffer);
        sgSurfaceTarget(buffer);
        sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_ONE, SG_GRAPHICS_FUNC_ONE);
        for(i = 0; i < 3; i++)
            sgSurfaceDraw(lights[i]->surface);
        sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_SRC_ALPHA, SG_GRAPHICS_FUNC_ONE_MINUS_SRC_ALPHA);
        sgSurfaceUntarget(buffer);

        if(multLights)
            sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_SRC_COLOR, SG_GRAPHICS_FUNC_SRC_COLOR);
        else
            sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_ONE, SG_GRAPHICS_FUNC_ONE);
        sgSurfaceDraw(buffer);
        sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_SRC_ALPHA, SG_GRAPHICS_FUNC_ONE_MINUS_SRC_ALPHA);

        /*if(multLights)
        {
            for(i = 0; i < NPOLYS; i++)
                drawPoly(polys[i]);
        }*/

        lights[0]->pos.x = sgMouseGetPosX();
        lights[0]->pos.y = sgMouseGetPosY();

        sgWindowSwapBuffers();
        sgDrawClear();

        sgDrawColor4f(1.0, 1.0, 1.0, 1.0);
        sgSurfaceDraw(tileset);
    }

    sgSurfaceDestroy(buffer);
    sgSurfaceDestroy(tileset);
    sgSpriteDestroy(tile);

    sgDeinit();

    return 0;
}
