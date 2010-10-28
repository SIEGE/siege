#include <siege/siege.h>

#include <stdlib.h>

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

void destroyBox(SGEntity* box)
{
    if(box == NULL)
        return;

    sgPhysicsShapeDestroy(box->data);
    sgPhysicsBodyDestroy(box->body);
    sgEntityDestroy(box);
}

SGEntity* createBox(SGSprite* spr, float x, float y, float angle, float density, SGbool stat)
{
    SGuint type = SG_PHYSICS_BODY_NORMAL;
    if(stat)
        type = (density == SG_INF) ? SG_PHYSICS_BODY_STATIC : SG_PHYSICS_BODY_SEMISTATIC;

    SGPhysicsBody* body = sgPhysicsBodyCreate(NULL, type);

    float w = sgSpriteGetWidth(spr);
    float h = sgSpriteGetHeight(spr);

    float verts[8] = {-w / 2.0, -h / 2.0,
                      -w / 2.0,  h / 2.0,
                       w / 2.0,  h / 2.0,
                       w / 2.0, -h / 2.0};

    SGEntity* box = sgEntityCreate(0.0, SG_EVT_ALL);

    sgEntitySetPhysicsBody(box, body);
    sgEntitySetSprite(box, spr);
    sgEntitySetPos(box, x, y);
    sgEntitySetAngleDegs(box, angle);

    box->data = sgPhysicsShapeCreatePoly(body, 0.0, 0.0, verts, 4);
    sgPhysicsBodySetMass(body, sgPhysicsShapeGetMass(box->data, density));
    sgPhysicsBodySetMoment(body, sgPhysicsShapeGetMomentDensity(box->data, density));

    box->evExit = destroyBox;

    numboxes++;
    boxes = realloc(boxes, numboxes * sizeof(SGEntity*));
    boxes[numboxes - 1] = box;
    return box;
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
void boxDrawDBG(SGEntity* box)
{
    if(box == NULL)
        return;

    sgPhysicsShapeDrawDBG(box->data);
}

void evKeyboardKeyPress(SGEntity* entity, SGenum key)
{
    if(key == SG_KEYBOARD_KEY_F1)
        overlay = !overlay;
}
void evKeyboardKeyRepeat(SGEntity* entity, SGenum key)
{
    evKeyboardKeyPress(entity, key);
}
void evMouseButtonLeftPress(SGEntity* entity)
{
    createMetalBox(sgMouseGetPosX(), sgMouseGetPosY(), 0.0);
}
void evMouseButtonRightPress(SGEntity* entity)
{
    createWoodenBox(sgMouseGetPosX(), sgMouseGetPosY(), 0.0);
}

int main()
{
    sgLoadModule("SDL");
    sgLoadModule("OpenGL");
    sgLoadModule("DevIL");
    sgLoadModule("Chipmunk");
    sgInit(640, 480, 32, 0);
    sgWindowSetTitle("SIEGE Physics Demo - Press F1 for debug overlay");

    sprCrateSmall = sgSpriteCreateFile("data/sprites/CrateSmall.png");
    sprFloorMetalPlate = sgSpriteCreateFile("data/sprites/FloorMetalPlate.png");
    sprHazardWall = sgSpriteCreateFile("data/sprites/HazardWall.png");
    sprPacman = sgSpriteCreateFile("data/sprites/Pacman.png");
    sprStrongboxSmall = sgSpriteCreateFile("data/sprites/StrongboxSmall.png");
    sprSupportBar = sgSpriteCreateFile("data/sprites/SupportBar.png");

    SGuint i;
    for(i = 32; i < 640; i += 64)
        createFloor(sprFloorMetalPlate, i, 448);
    for(i = 224; i < 448; i += 64)
        createFloor(sprSupportBar, i, 384);
    for(i = 224; i < 448; i += 64)
        createFloor(sprHazardWall, i, 320);

    controller = sgEntityCreate(0.0, SG_EVT_ALL);
    controller->evMouseButtonLeftPress = evMouseButtonLeftPress;
    controller->evMouseButtonRightPress = evMouseButtonRightPress;
    controller->evKeyboardKeyPress = evKeyboardKeyPress;
    controller->evKeyboardKeyRepeat = evKeyboardKeyRepeat;

    while(sgLoop(NULL))
    {
        if(overlay)
            for(i = 0; i < numboxes; i++)
                boxDrawDBG(boxes[i]);

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

    free(boxes);

    return 0;
}
