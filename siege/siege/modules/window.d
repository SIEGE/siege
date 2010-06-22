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
    checkBindFunc(sgmCoreWindowCreate)("sgmCoreWindowCreate", lib);
    checkBindFunc(sgmCoreWindowDestroy)("sgmCoreWindowDestroy", lib);
    checkBindFunc(sgmCoreWindowOpen)("sgmCoreWindowOpen", lib);
    checkBindFunc(sgmCoreWindowIsOpened)("sgmCoreWindowIsOpened", lib);
    checkBindFunc(sgmCoreWindowClose)("sgmCoreWindowClose", lib);
    //checkBindFunc(sgmCoreWindowIsClosed)("sgmCoreWindowIsClosed", lib);
    checkBindFunc(sgmCoreWindowSetTitle)("sgmCoreWindowSetTitle", lib);
    //checkBindFunc(sgmCoreWindowGetTitle)("sgmCoreWindowGetTitle", lib);
    //checkBindFunc(sgmCoreWindowFreeTitle)("sgmCoreWindowFreeTitle", lib);
    checkBindFunc(sgmCoreWindowSetSize)("sgmCoreWindowSetSize", lib);
    checkBindFunc(sgmCoreWindowGetSize)("sgmCoreWindowGetSize", lib);
    //checkBindFunc(sgmCoreWindowPollEvents)("sgmCoreWindowPollEvents", lib);
    checkBindFunc(sgmCoreWindowSwapBuffers)("sgmCoreWindowSwapBuffers", lib);

    checkBindFunc(sgmCoreWindowSetCallbacks)("sgmCoreWindowSetCallbacks", lib);
    //checkBindFunc(sgmCoreWindowGetCallbacks)("sgmCoreWindowGetCallbacks", lib);
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
    uint function(void** window) sgmCoreWindowCreate;
    uint function(void* window) sgmCoreWindowDestroy;
    uint function(void* window, uint width, uint height, ubyte bpp, uint flags) sgmCoreWindowOpen;
    uint function(void* window, bool* opened) sgmCoreWindowIsOpened;
    uint function(void* window) sgmCoreWindowClose;
    //uint function(void* window, bool* closed) sgmCoreWindowIsClosed;
    uint function(void* window, char* title) sgmCoreWindowSetTitle;
    //uint function(void* window, char** title) sgmCoreWindowGetTitle;
    //uint function(char* title) sgmCoreWindowFreeTitle;
    uint function(void* window, uint width, uint height) sgmCoreWindowSetSize;
    uint function(void* window, uint* width, uint* height) sgmCoreWindowGetSize;
    //uint function(void* window) sgmCoreWindowPollEvents;
    uint function(void* window) sgmCoreWindowSwapBuffers;

    uint function(void* window, SGCoreWindowCallbacks* callbacks) sgmCoreWindowSetCallbacks;
    //uint function(void* window, SGCoreWindowCallbacks** callbacks) sgmCoreWindowGetCallbacks;
}
