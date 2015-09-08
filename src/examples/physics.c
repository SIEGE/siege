#include <siege/siege.h>

#include <stdlib.h>
#include <stdio.h>

SGPhysicsSpace* space;

SGSprite* sprCrateSmall;
SGSprite* sprFloorMetalPlate;
SGSprite* sprHazardWall;
SGSprite* sprPacman;
SGSprite* sprStrongboxSmall;
SGSprite* sprSupportBar;
SGEntity* controller;

size_t numboxes = 0;
SGEntity** boxes = NULL;
SGbool overlay = SG_FALSE;

#define MAXCOLLS 32
#define MAXCONTS 64

typedef struct Box
{
    SGPhysicsShape* shape;
    size_t numcoll;

    size_t numcontacts[MAXCOLLS];
    SGVec2 points[MAXCOLLS][MAXCONTS];
    SGVec2 normals[MAXCOLLS][MAXCONTS];
    //SGVec2 impulse[MAXCOLLS][MAXCONTS];
} Box;

void boxCollisionBegin(SGEntity* entity, SGEntity* other, SGPhysicsCollision* collision, SGubyte idx)
{
    Box* box = entity->data;

    float dist;
    if(box->numcoll < MAXCOLLS)
    {
        box->numcontacts[box->numcoll] = sgPhysicsCollisionGetNumContacts(collision) % MAXCONTS;
        size_t i;
        for(i = 0; i < box->numcontacts[box->numcoll]; i++)
        {
            sgPhysicsCollisionGetPoint(collision, i, &box->points[box->numcoll][i].x, &box->points[box->numcoll][i].y);
            sgPhysicsCollisionGetNormal(collision, i, &box->normals[box->numcoll][i].x, &box->normals[box->numcoll][i].y);
            //sgPhysicsCollisionGetImpulse(collision, &box->impulse[box->numcoll][i].x, &box->impulse[box->numcoll][i].y, SG_TRUE);
            dist = sgPhysicsCollisionGetDepth(collision, i);

            box->normals[box->numcoll][i] = sgVec2Resize(box->normals[box->numcoll][i], dist);
        }
    }

    box->numcoll++;
}
void boxCollisionEnd(SGEntity* entity, SGEntity* other, SGPhysicsCollision* collision, SGubyte idx)
{
    Box* box = entity->data;
    if(box->numcoll)
        box->numcoll--;
}

void destroyBox(SGEntity* entity)
{
    if(entity == NULL)
        return;

    Box* box = entity->data;
    sgPhysicsShapeDestroy(box->shape);
    sgPhysicsBodyDestroy(entity->body);

    free(box);
}

SGEntity* createBox(SGSprite* spr, float x, float y, float angle, float density, SGbool stat)
{
    SGuint type = SG_BODY_NORMAL;
    if(stat)
        type = (density == SG_INF) ? SG_BODY_STATIC : SG_BODY_SEMISTATIC;

    SGPhysicsBody* body = sgPhysicsBodyCreate(NULL, type);

    float w = sgSpriteGetWidth(spr);
    float h = sgSpriteGetHeight(spr);

    float verts[8] = {-w / 2.0, -h / 2.0,
                      -w / 2.0,  h / 2.0,
                       w / 2.0,  h / 2.0,
                       w / 2.0, -h / 2.0};

    SGEntity* entity = sgEntityCreate();

    Box* box = calloc(1, sizeof(Box));
    entity->data = box;

    sgEntitySetPhysicsBody(entity, body);
    sgEntitySetSprite(entity, spr);
    sgEntitySetPos2f(entity, x, y);
    sgEntitySetAngleDegs(entity, angle);

    box->shape = sgPhysicsShapeCreatePoly(body, 0.0, 0.0, verts, 4);
    sgPhysicsShapeSetRestitution(box->shape, 0.25);
    sgPhysicsShapeSetFriction(box->shape, 0.75);
    if(density != SG_INF)
    {
        sgPhysicsBodySetMass(body, sgPhysicsShapeGetMass(box->shape, density));
        sgPhysicsBodySetMoment(body, sgPhysicsShapeGetMomentDensity(box->shape, density));
    }

    entity->lcCollisionBegin = boxCollisionBegin;
    entity->lcCollisionEnd = boxCollisionEnd;
    entity->evExit = destroyBox;

    numboxes++;
    boxes = realloc(boxes, numboxes * sizeof(SGEntity*));
    boxes[numboxes - 1] = entity;
    return entity;
}
SGEntity* createWoodenBox(float x, float y, float angle)
{
    return createBox(sprCrateSmall, x, y, angle, 1.0, SG_FALSE);
}
SGEntity* createMetalBox(float x, float y, float angle)
{
    return createBox(sprStrongboxSmall, x, y, angle, 2.5, SG_FALSE);
}
SGEntity* createFloor(SGSprite* sprite, float x, float y)
{
    return createBox(sprite, x, y, 0.0, SG_INF, SG_TRUE);
}
void boxDrawDBG(SGEntity* entity)
{
    if(entity == NULL)
        return;

    Box* box = entity->data;

    if(box->numcoll)
    {
        sgDrawColor4f(1.0, 0.0, 0.0, 1.0);
        sgEntityDraw(entity);
    }
    else
    {
        sgDrawColor4f(1.0, 1.0, 1.0, 1.0);
        sgEntityDraw(entity);
    }

    //sgDrawSetLineWidth(2.0);
    sgDrawSetPointSize(2.0);

    /*SGVec2 pos;
    sgEntityGetPos(entity, &pos.x, &pos.y);*/

    sgDrawColor4f(1.0, 0.0, 0.0, 1.0);

    size_t i, j;
    for(i = 0; i < SG_MIN(box->numcoll, MAXCOLLS); i++)
    {
        for(j = 0; j < box->numcontacts[i]; j++)
        {
            //sgDrawColor4f(1.0, 0.0, 0.0, 1.0);
            sgDrawPoint2f(box->points[i][j].x, box->points[i][j].y);

            //sgDrawColor4f(0.0, 1.0, 0.0, 1.0);
            //sgDrawLine2f(box->points[i][j].x, box->points[i][j].y, box->points[i][j].x + box->normals[i][j].x, box->points[i][j].y + box->normals[i][j].y);

            //sgDrawColor4f(0.0, 0.0, 1.0, 1.0);
            //sgDrawLine2f(pos.x, pos.y, pos.x + box->impulse[i][j].x, pos.y + box->impulse[i][j].y);
        }
    }

    //sgDrawSetLineWidth(1.0);
    sgDrawSetPointSize(1.0);

    sgDrawColor4f(1.0, 1.0, 1.0, 1.0);
    sgPhysicsShapeDrawDBG(box->shape);
}

void SG_CALL evInputButtonPress(SGEntity* entity, SGint id, SGenum button)
{
    if(id == SG_INPUT_ID_KEYBOARD && button == SG_KEY_F1)
        overlay = !overlay;
    else if(id == SG_INPUT_ID_MOUSE)
    {
        if(button == SG_MOUSE_BUTTON_LEFT)
            createMetalBox(sgMouseGetPosX(), sgMouseGetPosY(), 0.0);
        else if(button == SG_MOUSE_BUTTON_RIGHT)
            createWoodenBox(sgMouseGetPosX(), sgMouseGetPosY(), 0.0);
    }
}

int main(void)
{
    sgInit(0);
    sgWindowOpen(640, 480, 32, 0);
    sgWindowSetTitle("SIEGE Physics Demo - Press F1 for debug overlay");
    sgWindowSetFPSLimit(60.0f);

    space = sgPhysicsSpaceGetDefault();
    sgPhysicsSpaceSetIterations(space, 10);
    sgPhysicsSpaceSetDamping(space, 0.75);
    sgPhysicsSpaceSetGravity(space, 0.0, 25.0);

    sprCrateSmall = sgSpriteCreateFile("data/sprites/CrateSmall.png");
    sprFloorMetalPlate = sgSpriteCreateFile("data/sprites/FloorMetalPlate.png");
    sprHazardWall = sgSpriteCreateFile("data/sprites/HazardWall.png");
    sprPacman = sgSpriteCreateFile("data/sprites/Pacman.png");
    sprStrongboxSmall = sgSpriteCreateFile("data/sprites/StrongboxSmall.png");
    sprSupportBar = sgSpriteCreateFile("data/sprites/SupportBar.png");
    SGFont* font = sgFontCreate("data/fonts/DejaVuSans.ttf", 7.0, 0, 127);

    SGuint i;
    for(i = 32; i < 640; i += 64)
        createFloor(sprFloorMetalPlate, i, 448);
    for(i = 224; i < 448; i += 64)
        createFloor(sprSupportBar, i, 384);
    for(i = 224; i < 448; i += 64)
        createFloor(sprHazardWall, i, 320);

    controller = sgEntityCreate();
    controller->evInputButtonPress = evInputButtonPress;

    SGlong accum = SG_NANOSECONDS_IN_A_SECOND, origin = sgGetTime();
    SGfloat fps = 0.0;
    while(sgLoop(NULL))
    {
        accum += sgGetTime() - origin;
        if(overlay)
            for(i = 0; i < numboxes; i++)
                boxDrawDBG(boxes[i]);
        if(accum >= SG_NANOSECONDS_IN_A_SECOND)
        {
            accum = 0;
            origin = sgGetTime();
            fps = sgWindowGetFPS();
        }
        sgFontPrintf(font, 1.0, 10.0, "FPS: %.2f", fps);

        sgWindowSwapBuffers();
        sgDrawClear();
    }

    sgSpriteDestroy(sprCrateSmall);
    sgSpriteDestroy(sprFloorMetalPlate);
    sgSpriteDestroy(sprHazardWall);
    sgSpriteDestroy(sprPacman);
    sgSpriteDestroy(sprStrongboxSmall);
    sgSpriteDestroy(sprSupportBar);
    sgFontDestroy(font);

    sgDeinit();

    free(boxes);

    return 0;
}
