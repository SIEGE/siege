module siege.modules.modules;

private
{
    import derelict.util.loader;

    import siege.core.core;
    import siege.core.event;
    //import siege.util.misc;

    import siege.modules.audio;
    import siege.modules.fonts;
    import siege.modules.graphics;
    import siege.modules.input;
    import siege.modules.physics;
    import siege.modules.windowing;

    import std.path;
    import std.file;
    import std.gc;
}

struct CheckBinder(T)
{
    void opCall(char[] n, SharedLib lib)
    {
        void* pptr = *fptr;
        //if(*fptr is null)
        *fptr = Derelict_GetProc(lib, n);
        if(*fptr is null)
            *fptr = pptr;
    }

    private void** fptr;
}
CheckBinder!(T) checkBindFunc(T)(inout T a)
{
    CheckBinder!(T) res;
    res.fptr = cast(void**)&a;
    return res;
}

void loadModule(SharedLib lib)
{
    /// General
    //checkBindFunc(sgModuleInit)("sgModuleInit", lib);
    //checkBindFunc(sgModuleExit)("sgModuleExit", lib);
    //checkBindFunc(sgModuleFree)("sgModuleFree", lib);

    loadModuleAudio(lib);
    loadModuleFonts(lib);
    loadModuleGraphics(lib);
    loadModuleInput(lib);
    loadModulePhysics(lib);
    loadModuleWindowing(lib);
}

extern(C)
{
    struct SGModuleInfo
    {
        ushort imajor;
        ushort iminor;
        ushort ipatch;

        ushort vmajor;
        ushort vminor;
        ushort vpatch;

        char* name;
    }

    //uint function(void* id, void* gc, SGModuleInfo** minfo) sgModuleInit;
    //uint function()                                         sgModuleExit;
    //uint function(void* data)                               sgModuleFree;

    /// Windowing
    /// Font Load
    /// Physics
}

/*GenericLoader ModuleLoader;
static this()
{
    ModuleLoader.setup("", "", "", &loadModule);
}*/

class SiegeModule
{
    extern(C)
    {
        uint function(void* gc, SGModuleInfo** minfo)    sgModuleInit;
        uint function(SGModuleInfo* minfo)               sgModuleExit;
        //uint function(void* data)                        sgModuleFree;
    }

    void loadModuleGeneral(SharedLib lib)
    {
        checkBindFunc(sgModuleInit)("sgModuleInit", lib);
        checkBindFunc(sgModuleExit)("sgModuleExit", lib);
        //checkBindFunc(sgModuleFree)("sgModuleFree", lib);
    }

    SharedLib lib;
    SGModuleInfo* moduleInfo;
    char[] fname;
    this(char[] name)
    {
        char[][] files = listdir("Modules", "*[\\/]SGModule-"~name~".*");
        if(files.length == 0)
            throw new Exception("Cannot load module " ~ name);
        fname = files[0];

        lib = Derelict_LoadSharedLib(fname);
        loadModuleGeneral(lib);
        loadModule(lib);
        //ModuleLoader.load(fname);

        if(sgModuleInit !is null)
            sgModuleInit(getGCHandle(), &moduleInfo);
    }

    ~this()
    {
        //if(sgModuleFree !is null)
        //    sgModuleFree(moduleInfo);
        if(sgModuleExit !is null)
            sgModuleExit(moduleInfo);

        //ModuleLoader.unload();
    }
}

