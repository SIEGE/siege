module siege.modules.windowing;

private
{
    import derelict.util.loader;

    import siege.modules.modules;
}

enum: uint
{
    SG_WINDOW_FULLSCREEN = 0x01,
}

void loadModuleWindowing(SharedLib lib)
{
    /// Windowing
    checkBindFunc(sgCoreWindowCreate)("sgCoreWindowCreate", lib);
    checkBindFunc(sgCoreWindowDestroy)("sgCoreWindowDestroy", lib);
    checkBindFunc(sgCoreWindowOpen)("sgCoreWindowOpen", lib);
    checkBindFunc(sgCoreWindowIsOpened)("sgCoreWindowIsOpened", lib);
    checkBindFunc(sgCoreWindowClose)("sgCoreWindowClose", lib);
    //checkBindFunc(sgCoreWindowIsClosed)("sgCoreWindowIsClosed", lib);
    checkBindFunc(sgCoreWindowSetTitle)("sgCoreWindowSetTitle", lib);
    //checkBindFunc(sgCoreWindowGetTitle)("sgCoreWindowGetTitle", lib);
    //checkBindFunc(sgCoreWindowFreeTitle)("sgCoreWindowFreeTitle", lib);
    checkBindFunc(sgCoreWindowSetSize)("sgCoreWindowSetSize", lib);
    checkBindFunc(sgCoreWindowGetSize)("sgCoreWindowGetSize", lib);
    //checkBindFunc(sgCoreWindowPollEvents)("sgCoreWindowPollEvents", lib);
    checkBindFunc(sgCoreWindowSwapBuffers)("sgCoreWindowSwapBuffers", lib);

    checkBindFunc(sgCoreWindowSetCallbacks)("sgCoreWindowSetCallbacks", lib);
    //checkBindFunc(sgCoreWindowGetCallbacks)("sgCoreWindowGetCallbacks", lib);

    checkBindFunc(sgCoreWindowMatchGraphics)("sgCoreWindowMatchGraphics", lib);
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

    uint function(SGModuleInfo* other, ubyte* level) sgCoreWindowMatchGraphics;
}
