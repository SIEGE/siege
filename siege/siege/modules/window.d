module siege.modules.window;

private
{
    import derelict.util.loader;

    import siege.modules.modules;
}

enum: uint
{
    SG_WINDOW_FULLSCREEN = 0x01,
    SG_WINDOW_RESIZABLE  = 0x02,
}

void loadModuleWindowing(SharedLib lib)
{
    /// Windowing
    checkBindFunc(sgCoreWindowCreate)("sgmCoreWindowCreate", lib);
    checkBindFunc(sgCoreWindowDestroy)("sgmCoreWindowDestroy", lib);
    checkBindFunc(sgCoreWindowOpen)("sgmCoreWindowOpen", lib);
    checkBindFunc(sgCoreWindowIsOpened)("sgmCoreWindowIsOpened", lib);
    checkBindFunc(sgCoreWindowClose)("sgmCoreWindowClose", lib);
    //checkBindFunc(sgCoreWindowIsClosed)("sgmCoreWindowIsClosed", lib);
    checkBindFunc(sgCoreWindowSetTitle)("sgmCoreWindowSetTitle", lib);
    //checkBindFunc(sgCoreWindowGetTitle)("sgmCoreWindowGetTitle", lib);
    //checkBindFunc(sgCoreWindowFreeTitle)("sgmCoreWindowFreeTitle", lib);
    checkBindFunc(sgCoreWindowSetSize)("sgmCoreWindowSetSize", lib);
    checkBindFunc(sgCoreWindowGetSize)("sgmCoreWindowGetSize", lib);
    //checkBindFunc(sgCoreWindowPollEvents)("sgmCoreWindowPollEvents", lib);
    checkBindFunc(sgCoreWindowSwapBuffers)("sgmCoreWindowSwapBuffers", lib);

    checkBindFunc(sgCoreWindowSetCallbacks)("sgmCoreWindowSetCallbacks", lib);
    //checkBindFunc(sgCoreWindowGetCallbacks)("sgmCoreWindowGetCallbacks", lib);
}

extern(C)
{
    struct SGCoreWindowCallbacks
    {
        void function(void* window)                          open;
        void function(void* window)                          close;
        void function(void* window, uint width, uint height) resize;
    }

    /// Windowing
    uint function(void** window) sgCoreWindowCreate;
    uint function(void* window) sgCoreWindowDestroy;
    uint function(void* window, uint width, uint height, ubyte bpp, uint flags) sgCoreWindowOpen;
    uint function(void* window, bool* opened) sgCoreWindowIsOpened;
    uint function(void* window) sgCoreWindowClose;
    //uint function(void* window, bool* closed) sgCoreWindowIsClosed;
    uint function(void* window, char* title) sgCoreWindowSetTitle;
    //uint function(void* window, char** title) sgCoreWindowGetTitle;
    //uint function(char* title) sgCoreWindowFreeTitle;
    uint function(void* window, uint width, uint height) sgCoreWindowSetSize;
    uint function(void* window, uint* width, uint* height) sgCoreWindowGetSize;
    //uint function(void* window) sgCoreWindowPollEvents;
    uint function(void* window) sgCoreWindowSwapBuffers;

    uint function(void* window, SGCoreWindowCallbacks* callbacks) sgCoreWindowSetCallbacks;
    //uint function(void* window, SGCoreWindowCallbacks** callbacks) sgCoreWindowGetCallbacks;
}
