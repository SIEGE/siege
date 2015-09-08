#include <siege/siege.h>

/* TODO: Improve, show warning for no detected joysticks, etc... */

static SGSprite* sprPacman;

static SGVec2 entMov = {0, 0};
static SGVec2 entRot = {1, 0};
static float entSpeed = 1.0;

static void SG_CALL evTick(SGEntity* entity)
{
    sgEntitySetPos2fv(entity, sgVec2Add(sgEntityGetPos2fv(entity), sgVec2Mulf(entMov, entSpeed)));
    sgEntitySetAngleRads(entity, -sgVec2AngleRads(entRot));
}
static void SG_CALL evInputAxisMove(SGEntity* entity, SGint id, float* axis, size_t numaxis)
{
    if(id > SG_INPUT_ID_JOYSTICK0) return; /* ignore non-joystick inputs */
    if(numaxis >= 2)
        entMov = sgVec2fp(&axis[0]);
    if(numaxis >= 3)
        entSpeed = SG_MAX(0.0, -axis[2]); /* disable reverse */
    if(numaxis >= 5)
        entRot = sgVec2Cross(sgVec2fp(&axis[3]));
}

int main(void)
{
    sgInit(0);
    sgWindowOpen(640, 480, 32, 0);
    sgWindowSetTitle("SIEGE Joystick Demo");

    sprPacman = sgSpriteCreateFile("data/sprites/Pacman.png");

    SGEntity* entPacman = sgEntityCreate();
    entPacman->evTick = evTick;
    entPacman->evInputAxisMove = evInputAxisMove;
    sgEntitySetPos2fv(entPacman, sgVec2Divf(sgWindowGetSize2fv(), 2));
    sgEntitySetSprite(entPacman, sprPacman);

    SGint ret;
    for(;;)
    {
        sgDrawClear();
        if(!sgLoop(&ret))
            break;
        sgWindowSwapBuffers();
    }

    sgSpriteDestroy(sprPacman);

    sgDeinit();

    return ret;
}
