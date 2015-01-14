#include <siege/siege.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
//#include <time.h>

#define NLIGHTS 4
#define OP >=

SGPhysicsSpace* space;

SGAudioBuffer* bufBoom;

float frand2(float min, float max)
{
    return min + rand() / (float)RAND_MAX * (max - min);
}

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

    SGIVec2 mpos = sgMouseGetPos2iv();

    float w = sgTextureGetWidth(tex);
    float h = sgTextureGetHeight(tex);

    float verts[8] = {-w / 2.0, -h / 2.0,
                       -w / 2.0, +h / 2.0,
                       w / 2.0, +h / 2.0,
                       w / 2.0, -h / 2.0};

    createPoly(mpos.x, mpos.y, (SGVec2*)verts, 4, tex, dens, SG_FALSE);
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
                    lights[key - '1']->enabled = !lights[key - '1']->enabled;
            }
            break;
    }
}

void destroyPoly(Polygon* poly)
{
    sgEntityKillRelease(poly->entity);
}

void destroyPolyEntity(SGEntity* ent)
{
    Polygon* poly = ent->data;

    free(poly->points);
    sgPhysicsShapeDestroy(poly->shape);
    sgPhysicsBodyDestroy(poly->body);
    free(poly);
}

void lcPolyCollisionOneBegin(SGEntity* entity, SGEntity* other, SGPhysicsCollision* coll)
{
    SGVec2 v1;
    sgPhysicsBodyGetVel(sgEntityGetPhysicsBody(entity), &v1.x, &v1.y);
    SGVec2 v2;
    sgPhysicsBodyGetVel(sgEntityGetPhysicsBody(other), &v2.x, &v2.y);

    float dist = sgPhysicsCollisionGetDepth(coll, 0);

    float vdiff = sgVec2Length(sgVec2Sub(v1, v2));

    if(vdiff <= 10.0)
        return;

    //float pitch = 10.0 - log(fabs(vdiff))/* / 0.125*/;
    //float pitch = 10.0 + frand2(-1.0, 1.0);
    float pitch = 10.0 - fabs(dist);
    float gain = log(vdiff) / 30.0/* fabs(dist)*/;

    SGAudioSource* srcBoom = sgAudioSourceCreate(1.0, gain, pitch, SG_FALSE);
    sgAudioSourceQueueBuffer(srcBoom, bufBoom);
    sgAudioSourcePlay(srcBoom);
    sgAudioSourceDestroyLazy(srcBoom);
}

void drawPoly(Polygon* poly)
{
    size_t i;

    SGVec2 pos;
    float x, y;
    SGVec2 tpos;
    pos = sgEntityGetPos2fv(poly->entity);
    x = pos.x;
    y = pos.y;

    if(poly->texture == NULL)
        sgDrawColor4f(0.0, 0.5, 0.75, 1.0);
    else
        sgDrawColor4f(1.0, 1.0, 1.0, 1.0);
    sgDrawBeginT(SG_CONVEX_POLYGON, poly->texture);
        for(i = 0; i < poly->nump; i++)
        {
            sgDrawTexCoord2f((poly->points[i].x - poly->min.x) / (poly->max.x - poly->min.x)
                            ,(poly->points[i].y - poly->min.y) / (poly->max.y - poly->min.y));
            tpos = sgVec2RotateRads(poly->points[i], sgVec2AngleRads(poly->points[i]) + sgEntityGetAngleRads(poly->entity));
            sgDrawVertex2f(x + tpos.x, y + tpos.y);
        }
    sgDrawEnd();

    if(poly->texture == NULL)
        sgDrawColor4f(0.0, 1.0, 0.75, 1.0);
    else
        sgDrawColor4f(0.75, 0.75, 0.75, 1.0);
    sgDrawBeginT(SG_LINE_LOOP, poly->texture);
        for(i = 0; i < poly->nump; i++)
        {
            sgDrawTexCoord2f((poly->points[i].x - poly->min.x) / (poly->max.x - poly->min.x)
                            ,(poly->points[i].y - poly->min.y) / (poly->max.y - poly->min.y));
            tpos = sgVec2RotateRads(poly->points[i], sgVec2AngleRads(poly->points[i]) + sgEntityGetAngleRads(poly->entity));
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


    poly->entity = sgEntityCreate();
    poly->entity->data = poly;
    poly->entity->lcDestroy = destroyPolyEntity;
    poly->entity->lcCollisionOneBegin = lcPolyCollisionOneBegin;
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

    poly->body = sgPhysicsBodyCreate(NULL, stat ? SG_BODY_STATIC : SG_BODY_NORMAL);
    sgEntitySetPhysicsBody(poly->entity, poly->body);
    sgEntitySetPos2f(poly->entity, x, y);
    poly->shape = sgPhysicsShapeCreatePoly(poly->body, 0.0, 0.0, (float*)points, nump);
    sgPhysicsShapeSetRestitution(poly->shape, 0.25);
    sgPhysicsShapeSetFriction(poly->shape, 0.75);
    if(density != SG_INF)
    {
        sgPhysicsBodySetMass(poly->body, sgPhysicsShapeGetMass(poly->shape, density));
        sgPhysicsBodySetMoment(poly->body, sgPhysicsShapeGetMomentDensity(poly->shape, density));
    }

    npolys++;
    polys = realloc(polys, npolys * sizeof(Polygon*));
    polys[npolys - 1] = poly;

    return poly;
}

void destroyLight(Light* light)
{
    sgEntityKillRelease(light->entity);
}

void destroyLightEntity(SGEntity* ent)
{
    Light* light = ent->data;

    sgSurfaceRelease(light->surface);
    free(light);
}

void drawLight(Light* light)
{
    sgSurfaceClear4f(light->surface, 0.0, 0.0, 0.0, 0.0);
    if(!light->enabled)
        return;
    sgSurfaceTarget(light->surface);

    sgDrawColor4f(light->color.r, light->color.g, light->color.b, light->color.a);

    SGVec2 tcurr, tnext;
    /*SGVec2* curr;*/
    SGVec2* next;
    Polygon* poly;
    SGVec2 tmpc, tmpn;
    size_t i, p;
    SGVec2 pos;
    float x, y;

    int sides = SG_MAX(3, (int)(light->radius * 0.5));
    float f = 2 * SG_PI / sides;
    sgDrawBegin(SG_TRIANGLE_FAN);
        sgDrawColor4f(light->color.r, light->color.g, light->color.b, light->color.a);
        sgDrawVertex2f(light->pos.x, light->pos.y);
        sgDrawColor4f(light->color.r, light->color.g, light->color.b, 0.0);
        for(i = 0; i <= sides; i++)
        {
            sgDrawVertex2f(light->pos.x + cos(f * i) * light->radius,
                           light->pos.y + sin(f * i) * light->radius);
        }
    sgDrawEnd();
    //sgDrawCircle2f(light->pos.x, light->pos.y, light->radius, SG_TRUE);

    sgDrawColor4f(0.0, 0.0, 0.0, 1.0);
    for(p = 0; p < npolys; p++)
    {
        sgDrawBegin(SG_TRIANGLES);
        poly = polys[p];

        pos = sgEntityGetPos2fv(poly->entity);
        x = pos.x;
        y = pos.y;
        if(poly->nump > 0)
        {
            tcurr = sgVec2RotateRads(poly->points[0], sgVec2AngleRads(poly->points[0]) + sgEntityGetAngleRads(poly->entity));
            tcurr = sgVec2Add(tcurr, sgVec2f(x, y));
        }
        for(i = 0; i < poly->nump; i++)
        {
            /*curr = &poly->points[i];*/
            next = &poly->points[(i + 1) % poly->nump];

            tnext = sgVec2RotateRads(*next, sgVec2AngleRads(*next) + sgEntityGetAngleRads(poly->entity));
            tnext = sgVec2Add(tnext, sgVec2f(x, y));

            if(sgVec2PDot(sgVec2Sub(tnext, tcurr), sgVec2Sub(tnext, light->pos)) OP 0)
            {
                tmpc = sgVec2Add(tcurr, sgVec2Resize(sgVec2Sub(tcurr, light->pos), 640 + 480));
                tmpn = sgVec2Add(tnext, sgVec2Resize(sgVec2Sub(tnext, light->pos), 640 + 480));

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
    light->angle = angle * SG_PI / 180.0;
    light->arc = arc * SG_PI / 180.0;

    light->entity = sgEntityCreate();
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
    sgDrawBegin(SG_LINE_LOOP);
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
    /*SGVec2* curr;*/
    SGVec2* next;
    Polygon* poly;
    SGVec2 tmpc, tmpn;
    size_t p, i;
    SGVec2 pos;
    float x, y;

    sgDrawColor4f(1.0, 1.0, 0.0, 1.0);
    sgDrawCircle2fv(light->pos, light->radius, SG_FALSE);

    sgDrawColor4f(1.0, 0.0, 0.0, 1.0);
    sgDrawBegin(SG_LINES);
    for(p = 0; p < npolys; p++)
    {
        poly = polys[p];

        pos = sgEntityGetPos2fv(poly->entity);
        x = pos.x;
        y = pos.y;
        if(poly->nump > 0)
        {
            tcurr = sgVec2RotateRads(poly->points[0], sgVec2AngleRads(poly->points[0]) + sgEntityGetAngleRads(poly->entity));
            tcurr = sgVec2Add(tcurr, sgVec2f(x, y));
        }
        for(i = 0; i < poly->nump; i++)
        {
            /*curr = &poly->points[i];*/
            next = &poly->points[(i + 1) % poly->nump];

            tnext = sgVec2RotateRads(*next, sgVec2AngleRads(*next) + sgEntityGetAngleRads(poly->entity));
            tnext = sgVec2Add(tnext, sgVec2f(x, y));

            if(sgVec2PDot(sgVec2Sub(tnext, tcurr), sgVec2Sub(tnext, light->pos)) OP 0)
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
        sgDrawBegin(SG_LINES);
        poly = polys[p];

        pos = sgEntityGetPos2fv(poly->entity);
        x = pos.x;
        y = pos.y;
        if(poly->nump > 0)
        {
            tcurr = sgVec2RotateRads(poly->points[0], sgVec2AngleRads(poly->points[0]) + sgEntityGetAngleRads(poly->entity));
            tcurr = sgVec2Add(tcurr, sgVec2f(x, y));
        }
        for(i = 0; i < poly->nump; i++)
        {
            /*curr = &poly->points[i];*/
            next = &poly->points[(i + 1) % poly->nump];

            tnext = sgVec2RotateRads(*next, sgVec2AngleRads(*next) + sgEntityGetAngleRads(poly->entity));
            tnext = sgVec2Add(tnext, sgVec2f(x, y));

            if(sgVec2PDot(sgVec2Sub(tnext, tcurr), sgVec2Sub(tnext, light->pos)) OP 0)
            {
                tmpc = sgVec2Add(tcurr, sgVec2Resize(sgVec2Sub(tcurr, light->pos), 640 + 480));
                tmpn = sgVec2Add(tnext, sgVec2Resize(sgVec2Sub(tnext, light->pos), 640 + 480));

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

int main(void)
{
    sgInit(0);
    sgWindowOpen(640, 480, 32, 0);
    sgWindowSetTitlef("SIEGE Demo - Press F1 for debug overlay, 1-%d to toggle lights", NLIGHTS);

    //srand((unsigned int)time(NULL));

    sgWindowSetFPSLimit(60.0);

    bufBoom = sgAudioBufferCreateFile("data/audio/boom.ogg");

    space = sgPhysicsSpaceGetDefault();
    sgPhysicsSpaceSetIterations(space, 10);
    sgPhysicsSpaceSetDamping(space, 0.75);

    SGEntity* handler = sgEntityCreate();
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
    SGbool multLights = SG_TRUE;
    SGbool sqrmult = SG_TRUE;
    SGColor ambience = {0.125, 0.0625, 0.0, 1.0};

    while(sgLoop(NULL))
    {
        sgDrawColor4f(1.0, 1.0, 1.0, 1.0);

        sgSurfaceClear4f(buffer, ambience.r, ambience.g, ambience.b, ambience.a);
        sgSurfaceTarget(buffer);
        sgDrawSetBlendFunc(SG_FUNC_ONE, SG_FUNC_ONE);
        for(i = 0; i < NLIGHTS; i++)
        {
            if(lights[i]->enabled)
                sgSurfaceDraw(lights[i]->surface);
        }
        sgDrawSetBlendFunc(SG_FUNC_SRC_ALPHA, SG_FUNC_ONE_MINUS_SRC_ALPHA);
        sgSurfaceUntarget(buffer);

        if(multLights)
        {
            if(sqrmult)
                sgDrawSetBlendFunc(SG_FUNC_DST_COLOR, SG_FUNC_SRC_COLOR);
            else
                sgDrawSetBlendFunc(SG_FUNC_DST_COLOR, SG_FUNC_ZERO);
        }
        else
            sgDrawSetBlendFunc(SG_FUNC_ONE, SG_FUNC_ONE);
        sgSurfaceDraw(buffer);

        sgDrawSetBlendFunc(SG_FUNC_SRC_ALPHA, SG_FUNC_ONE_MINUS_SRC_ALPHA);

        lights[0]->pos = sgVec2iv(sgMouseGetPos2iv());

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

    sgTextureRelease(mbox);
    sgTextureRelease(wbox);

    sgTextureRelease(ptexture);

    sgSurfaceRelease(buffer);
    sgSurfaceRelease(tileset);
    sgSpriteRelease(tile);

    sgAudioBufferDestroy(bufBoom);

    sgDeinit();

    free(polys);

    return 0;
}
