#define SG_BUILD_MODULE
#include <siege/physics/module.h>
#include <siege/physics/space.h>

SGbool SG_CALL _sgPhysicsInit(void)
{
    return _sgPhysicsSpaceInit();
}
SGbool SG_CALL _sgPhysicsDeinit(void)
{
    return _sgPhysicsSpaceDeinit();
}
