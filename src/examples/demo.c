#include <siege/siege.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define NLIGHTS 4

typedef struct Polygon
{
    SGEntity* entity;
    SGEntity* uentity;
    SGVec2* points;
    size_t nump;
    SGTexture* texture;
    SGVec2 min;
    SGVec2 max;
    SGPhysicsShape* shape;
    SGPhysicsBody* body;
} Polygon;

typedef struct Light
{
    SGEntity* entity;
    SGSurface* surface;
    SGVec2 pos;
    SGColor color;
    float radius;
    float angle;
    float arc;
    SGbool enabled;
} Light;
Light* lights[NLIGHTS];

SGbool overlayDBG = SG_FALSE;

size_t npolys = 0;
Polygon** polys = NULL;

SGTexture* mbox;
SGTexture* wbox;

Polygon* createPoly(float x, float y, SGVec2* points, size_t nump, SGTexture* texture, float density, SGbool stat);

void evMouseButtonPress(SGEntity* ent, SGuint button)
{
    SGTexture* tex = (button == SG_MOUSE_BUTTON_LEFT) ? mbox : wbox;
    float dens = (button == SG_MOUSE_BUTTON_LEFT) ? 2.5 : 1.0;

    SGint mx, my;
    sgMouseGetPos(&mx, &my);

    float w = sgTextureGetWidth(tex);
    float h = sgTextureGetHeight(tex);

    float verts[8] = {-w / 2.0, -h / 2.0,
                       -w / 2.0, +h / 2.0,
                       w / 2.0, +h / 2.0,
                       w / 2.0, -h / 2.0};

    createPoly(mx, my, (SGVec2*)verts, 4, tex, dens, SG_FALSE);
}

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
                    lights[key - '1']->enabled = !lights[key - '1']->enabled;
            }
            break;
    }
}

void destroyPoly(Polygon* poly)
{
    poly->entity->lcDestroy = NULL;
    sgEntityDestroy(poly->entity);
    free(poly->points);
    sgPhysicsShapeDestroy(poly->shape);
    sgPhysicsBodyDestroy(poly->body);
    free(poly);
}

void destroyPolyEntity(SGEntity* ent)
{
    destroyPoly(ent->data);
}

void drawPoly(Polygon* poly)
{
    size_t i;

    float x, y;
    SGVec2 tpos;
    sgEntityGetPos(poly->entity, &x, &y);

    if(poly->texture == NULL)
        sgDrawColor4f(0.0, 0.5, 0.75, 1.0);
    else
        sgDrawColor4f(1.0, 1.0, 1.0, 1.0);
    sgDrawBeginT(SG_GRAPHICS_PRIMITIVE_CONVEX_POLYGON, poly->texture);
        for(i = 0; i < poly->nump; i++)
        {
            sgDrawTexCoord2f((poly->points[i].x - poly->min.x) / (poly->max.x - poly->min.x)
                            ,(poly->points[i].y - poly->min.y) / (poly->max.y - poly->min.y));
            tpos = sgVec2SetAngleRads(poly->points[i], sgVec2GetAngleRads(poly->points[i]) + sgEntityGetAngleRads(poly->entity));
            sgDrawVertex2f(x + tpos.x, y + tpos.y);
        }
    sgDrawEnd();

    if(poly->texture == NULL)
        sgDrawColor4f(0.0, 1.0, 0.75, 1.0);
    else
        sgDrawColor4f(0.75, 0.75, 0.75, 1.0);
    sgDrawBeginT(SG_GRAPHICS_PRIMITIVE_LINE_LOOP, poly->texture);
        for(i = 0; i < poly->nump; i++)
        {
            sgDrawTexCoord2f((poly->points[i].x - poly->min.x) / (poly->max.x - poly->min.x)
                            ,(poly->points[i].y - poly->min.y) / (poly->max.y - poly->min.y));
            tpos = sgVec2SetAngleRads(poly->points[i], sgVec2GetAngleRads(poly->points[i]) + sgEntityGetAngleRads(poly->entity));
            sgDrawVertex2f(x + tpos.x, y + tpos.y);
        }
    sgDrawEnd();
}

void drawPolyEntity(SGEntity* ent)
{
    drawPoly(ent->data);
}

Polygon* createPoly(float x, float y, SGVec2* points, size_t nump, SGTexture* texture, float density, SGbool stat)
{
    Polygon* poly = malloc(sizeof(Polygon));
    poly->points = malloc(nump * sizeof(SGVec2));
    memcpy(poly->points, points, nump * sizeof(SGVec2));
    poly->nump = nump;


    poly->entity = sgEntityCreate(0.0, SG_EVT_ALL);
    poly->entity->data = poly;
    poly->entity->lcDestroy = destroyPolyEntity;
    poly->entity->evDraw = drawPolyEntity;

    poly->texture = texture;

    poly->min = (SGVec2){0, 0};
    poly->max = (SGVec2){0, 0};

    if(nump == 0)
        return poly;

    poly->min.x = points[0].x;
    poly->min.y = points[0].y;
    poly->max.x = points[0].x;
    poly->max.y = points[0].y;

    size_t i;
    for(i = 1; i < nump; i++)
    {
        if(points[i].x < poly->min.x)
            poly->min.x = points[i].x;
        if(points[i].y < poly->min.y)
            poly->min.y = points[i].y;

        if(points[i].x > poly->max.x)
            poly->max.x = points[i].x;
        if(points[i].y > poly->max.y)
            poly->max.y = points[i].y;
    }

    poly->body = sgPhysicsBodyCreate(NULL, stat ? SG_PHYSICS_BODY_STATIC : SG_PHYSICS_BODY_NORMAL);
    sgEntitySetPhysicsBody(poly->entity, poly->body);
    sgEntitySetPos(poly->entity, x, y);
    poly->shape = sgPhysicsShapeCreatePoly(poly->body, 0.0, 0.0, (float*)points, nump);
    sgPhysicsBodySetMass(poly->body, sgPhysicsShapeGetMass(poly->shape, density));
    sgPhysicsBodySetMoment(poly->body, sgPhysicsShapeGetMomentDensity(poly->shape, density));

    npolys++;
    polys = realloc(polys, npolys * sizeof(Polygon*));
    polys[npolys - 1] = poly;

    return poly;
}

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
    if(!light->enabled)
        return;
    sgSurfaceTarget(light->surface);

    sgDrawColor4f(light->color.r, light->color.g, light->color.b, light->color.a);

    SGVec2 tcurr, tnext;
    SGVec2* curr;
    SGVec2* next;
    Polygon* poly;
    SGVec2 tmpc, tmpn;
    size_t i, p;
    float x, y;

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

    sgDrawColor4f(0.0, 0.0, 0.0, 1.0);
    for(p = 0; p < npolys; p++)
    {
        sgDrawBegin(SG_GRAPHICS_PRIMITIVE_TRIANGLES);
        poly = polys[p];

        sgEntityGetPos(poly->entity, &x, &y);
        if(poly->nump > 0)
        {
            tcurr = sgVec2SetAngleRads(poly->points[0], sgVec2GetAngleRads(poly->points[0]) + sgEntityGetAngleRads(poly->entity));
            tcurr = sgVec2Add(tcurr, sgVec2f(x, y));
        }
        for(i = 0; i < poly->nump; i++)
        {
            curr = &poly->points[i];
            next = &poly->points[(i + 1) % poly->nump];

            tnext = sgVec2SetAngleRads(*next, sgVec2GetAngleRads(*next) + sgEntityGetAngleRads(poly->entity));
            tnext = sgVec2Add(tnext, sgVec2f(x, y));

            if(sgVec2Cross(sgVec2Sub(tnext, tcurr), sgVec2Sub(tnext, light->pos)) <= 0)
            {
                tmpc = sgVec2Add(tcurr, sgVec2SetLength(sgVec2Sub(tcurr, light->pos), 640 + 480));
                tmpn = sgVec2Add(tnext, sgVec2SetLength(sgVec2Sub(tnext, light->pos), 640 + 480));

                sgDrawVertex2f(tcurr.x, tcurr.y);
                sgDrawVertex2f(tnext.x, tnext.y);
                sgDrawVertex2f(tmpc.x, tmpc.y);

                sgDrawVertex2f(tmpc.x, tmpc.y);
                sgDrawVertex2f(tmpn.x, tmpn.y);
                sgDrawVertex2f(tnext.x, tnext.y);
            }
            tcurr = tnext;
        }
        sgDrawEnd();
    }

    sgSurfaceUntarget(light->surface);
}

void drawLightEntity(SGEntity* ent)
{
    drawLight(ent->data);
}

Light* createLight(SGVec2 pos, SGColor color, float radius, float angle, float arc)
{
    Light* light = malloc(sizeof(Light));
    light->pos = pos;
    light->color = color;
    light->radius = radius;
    light->angle = angle * M_PI / 180.0;
    light->arc = arc * M_PI / 180.0;

    light->entity = sgEntityCreate(0.0, SG_EVT_ALL);
    light->entity->data = light;
    light->entity->lcDestroy = destroyLightEntity;
    light->entity->evDraw = drawLightEntity;

    light->surface = sgSurfaceCreate(640, 480, 32);

    light->enabled = SG_TRUE;

    return light;
}

void drawPolyDBG(Polygon* poly)
{
    /*size_t i;
    sgDrawColor4f(0.0, 1.0, 1.0, 1.0);
    sgDrawBegin(SG_GRAPHICS_PRIMITIVE_LINE_LOOP);
        for(i = 0; i < poly->nump; i++)
            sgDrawVertex2f(poly->points[i].x, poly->points[i].y);
    sgDrawEnd();*/
    sgPhysicsShapeDrawDBG(poly->shape);
}

void drawLightDBG(Light* light)
{
    if(!light->enabled)
        return;

    SGVec2 tcurr, tnext;
    SGVec2* curr;
    SGVec2* next;
    Polygon* poly;
    SGVec2 tmpc, tmpn;
    size_t p, i;
    float x, y;

    sgDrawColor4f(1.0, 1.0, 0.0, 1.0);
    sgDrawCircle(light->pos.x, light->pos.y, light->radius, SG_FALSE);

    sgDrawColor4f(1.0, 0.0, 0.0, 1.0);
    sgDrawBegin(SG_GRAPHICS_PRIMITIVE_LINES);
    for(p = 0; p < npolys; p++)
    {
        poly = polys[p];

        sgEntityGetPos(poly->entity, &x, &y);
        if(poly->nump > 0)
        {
            tcurr = sgVec2SetAngleRads(poly->points[0], sgVec2GetAngleRads(poly->points[0]) + sgEntityGetAngleRads(poly->entity));
            tcurr = sgVec2Add(tcurr, sgVec2f(x, y));
        }
        for(i = 0; i < poly->nump; i++)
        {
            curr = &poly->points[i];
            next = &poly->points[(i + 1) % poly->nump];

            tnext = sgVec2SetAngleRads(*next, sgVec2GetAngleRads(*next) + sgEntityGetAngleRads(poly->entity));
            tnext = sgVec2Add(tnext, sgVec2f(x, y));

            if(sgVec2Cross(sgVec2Sub(tnext, tcurr), sgVec2Sub(tnext, light->pos)) <= 0)
            {
                sgDrawVertex2f(tcurr.x, tcurr.y);
                sgDrawVertex2f(tnext.x, tnext.y);
            }
            tcurr = tnext;
        }
    }
    sgDrawEnd();

    sgDrawColor4f(1.0, 0.0, 0.0, 1.0);
    for(p = 0; p < npolys; p++)
    {
        sgDrawBegin(SG_GRAPHICS_PRIMITIVE_LINES);
        poly = polys[p];

        sgEntityGetPos(poly->entity, &x, &y);
        if(poly->nump > 0)
        {
            tcurr = sgVec2SetAngleRads(poly->points[0], sgVec2GetAngleRads(poly->points[0]) + sgEntityGetAngleRads(poly->entity));
            tcurr = sgVec2Add(tcurr, sgVec2f(x, y));
        }
        for(i = 0; i < poly->nump; i++)
        {
            curr = &poly->points[i];
            next = &poly->points[(i + 1) % poly->nump];

            tnext = sgVec2SetAngleRads(*next, sgVec2GetAngleRads(*next) + sgEntityGetAngleRads(poly->entity));
            tnext = sgVec2Add(tnext, sgVec2f(x, y));

            if(sgVec2Cross(sgVec2Sub(tnext, tcurr), sgVec2Sub(tnext, light->pos)) <= 0)
            {
                tmpc = sgVec2Add(tcurr, sgVec2SetLength(sgVec2Sub(tcurr, light->pos), 640 + 480));
                tmpn = sgVec2Add(tnext, sgVec2SetLength(sgVec2Sub(tnext, light->pos), 640 + 480));

                sgDrawVertex2f(tcurr.x, tcurr.y);
                sgDrawVertex2f(tmpc.x, tmpc.y);
                //sgDrawVertex2f(next->x, next->y);

                //sgDrawVertex2f(tmpc.x, tmpc.y);
                sgDrawVertex2f(tmpn.x, tmpn.y);
                sgDrawVertex2f(tnext.x, tnext.y);
            }
            tcurr = tnext;
        }
        sgDrawEnd();
    }
}

int main()
{
    sgLoadModule("SDL");
    sgLoadModule("OpenGL");
    sgLoadModule("DevIL");
    sgLoadModule("Chipmunk");
    sgInit(640, 480, 32, 0);
    sgWindowSetTitleF("SIEGE Shadows Demo - Press F1 for debug overlay, 1-%d to toggle lights", NLIGHTS);

    SGEntity* handler = sgEntityCreate(0.0, SG_EVT_ALL);
    handler->evMouseButtonPress = evMouseButtonPress;
    handler->evKeyboardKeyPress = evKeyboardKeyPress;

    SGSprite* tile = sgSpriteCreateFile2f("data/sprites/FloorMetalPlate.png", 0.0, 0.0);
    SGSurface* tileset = sgSurfaceCreate(640, 480, 32);

    SGTexture* ptexture = sgTextureCreateFile("data/sprites/Concrete.png");

    mbox = sgTextureCreateFile("data/sprites/StrongboxSmall.png");
    wbox = sgTextureCreateFile("data/sprites/CrateSmall.png");

    size_t i, j;

    sgSurfaceClear(tileset);
    sgDrawColor4f(1.0, 1.0, 1.0, 1.0);
    sgSurfaceTarget(tileset);
        for(i = 0; i <= 640 / sgSpriteGetWidth(tile); i++)
            for(j = 0; j <= 480 / sgSpriteGetHeight(tile); j++)
                sgSpriteDraw2f(tile, i * sgSpriteGetWidth(tile), j * sgSpriteGetHeight(tile));
    sgSurfaceUntarget(tileset);

    createPoly(0.0, 0.0,
               (SGVec2[]){(SGVec2){200, 250},
                          (SGVec2){225, 350},
                          (SGVec2){375, 350},
                          (SGVec2){400, 250}}, 4, ptexture, SG_INF, SG_TRUE);
    createPoly(0.0, 0.0,
               (SGVec2[]){(SGVec2){100,  50},
                          (SGVec2){100, 150},
                          (SGVec2){200, 150},
                          (SGVec2){200,  50}}, 4, ptexture, SG_INF, SG_TRUE);
    createPoly(0.0, 0.0,
               (SGVec2[]){(SGVec2){400, 100},
                          (SGVec2){450, 200},
                          (SGVec2){500, 100}}, 3, ptexture, SG_INF, SG_TRUE);

    lights[0] = createLight((SGVec2){60 , 60 }, (SGColor){0.5 , 1.0, 1.0, 1.0}, 192, 0, 360);
    lights[1] = createLight((SGVec2){500, 300}, (SGColor){0.75, 1.0, 0.0, 0.5}, 256, 0, 360);
    lights[2] = createLight((SGVec2){200, 400}, (SGColor){1.0 , 0.5, 0.0, 1.0}, 128, 0, 360);
    lights[3] = createLight((SGVec2){50 , 50 }, (SGColor){1.0 , 1.0, 1.0, 1.0}, 320, 45, 60);

    SGSurface* buffer = sgSurfaceCreate(640, 480, 32);

    // SG_TRUE if they should be mulplicative, SG_FALSE for additive!
    SGbool multLights = SG_FALSE;
    SGbool sqrmult = SG_TRUE;
    SGColor ambience = {0.125, 0.0625, 0.0, 1.0};

    while(sgLoop(NULL))
    {
        sgDrawColor4f(1.0, 1.0, 1.0, 1.0);

        sgSurfaceClear4f(buffer, ambience.r, ambience.g, ambience.b, ambience.a);
        sgSurfaceTarget(buffer);
        sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_ONE, SG_GRAPHICS_FUNC_ONE);
        for(i = 0; i < NLIGHTS; i++)
        {
            if(lights[i]->enabled)
                sgSurfaceDraw(lights[i]->surface);
        }
        sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_SRC_ALPHA, SG_GRAPHICS_FUNC_ONE_MINUS_SRC_ALPHA);
        sgSurfaceUntarget(buffer);

        if(multLights)
        {
            if(sqrmult)
                sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_DST_COLOR, SG_GRAPHICS_FUNC_SRC_COLOR);
            else
                sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_DST_COLOR, SG_GRAPHICS_FUNC_ZERO);
        }
        else
            sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_ONE, SG_GRAPHICS_FUNC_ONE);
        sgSurfaceDraw(buffer);

        sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_SRC_ALPHA, SG_GRAPHICS_FUNC_ONE_MINUS_SRC_ALPHA);

        lights[0]->pos.x = sgMouseGetPosX();
        lights[0]->pos.y = sgMouseGetPosY();

        if(overlayDBG)
        {
            for(i = 0; i < npolys; i++)
            {
                drawPolyDBG(polys[i]);
            }
            for(i = 0; i < NLIGHTS; i++)
            {
                drawLightDBG(lights[i]);
            }
        }

        sgWindowSwapBuffers();
        sgDrawClear();

        sgDrawColor4f(1.0, 1.0, 1.0, 1.0);
        sgSurfaceDraw(tileset);
    }

    sgTextureDestroy(mbox);
    sgTextureDestroy(wbox);

    sgTextureDestroy(ptexture);

    sgSurfaceDestroy(buffer);
    sgSurfaceDestroy(tileset);
    sgSpriteDestroy(tile);

    sgDeinit();

    free(polys);

    return 0;
}
