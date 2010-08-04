#define SG_BUILD_LIBRARY
#include <siege/util/link.h>
#include <siege/modules/modules.h>
#include <siege/modules/window.h>

void SG_EXPORT _sgModuleLoadWindow(SGLibrary* lib)
{
    void* fptr;

    /// Windowing
    _SG_BINDS(_sg_modWindow, sgmCoreWindowCreate);
    _SG_BINDS(_sg_modWindow, sgmCoreWindowDestroy);
    _SG_BINDS(_sg_modWindow, sgmCoreWindowOpen);
    _SG_BINDS(_sg_modWindow, sgmCoreWindowIsOpened);
    _SG_BINDS(_sg_modWindow, sgmCoreWindowClose);
    //_SG_BINDS(_sg_modWindow, sgmCoreWindowIsClosed);
    _SG_BINDS(_sg_modWindow, sgmCoreWindowSetTitle);
    //_SG_BINDS(_sg_modWindow, sgmCoreWindowGetTitle);
    //_SG_BINDS(_sg_modWindow, sgmCoreWindowFreeTitle);
    _SG_BINDS(_sg_modWindow, sgmCoreWindowSetSize);
    _SG_BINDS(_sg_modWindow, sgmCoreWindowGetSize);
    //_SG_BINDS(_sg_modWindow, sgmCoreWindowPollEvents);
    _SG_BINDS(_sg_modWindow, sgmCoreWindowSwapBuffers);

    _SG_BINDS(_sg_modWindow, sgmCoreWindowSetCallbacks);
    //_SG_BINDS(_sg_modWindow, sgmCoreWindowGetCallbacks);

    _SG_BINDS(_sg_modWindow, sgmCoreWindowMatchGraphics);
}

SGModuleWindow* SG_EXPORT sgModuleGetWindow(void)
{
    return &_sg_modWindow;
}
