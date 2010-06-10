/**
    \brief Core of SIEGE
    \todo Should this be renamed to siege.core.game?
*/
module siege.core.core;

private
{
    import siege.core.event;

    //
    import siege.graphics.draw;
    import siege.core.console;
    import siege.core.window;
    import siege.input.mouse;
    import siege.input.keyboard;
    import siege.input.joystick;
    import siege.util.linkedlist;
    import siege.physics.space;
    //

    import derelict.util.exception;

    import siege.modules.modules;
    import std.stdio;
}

pragma(lib, "DerelictUtil.lib");

bool cbMissingProc(char[] lib, char[] proc)
{
    return true;
}

LinkedList!(EventClient) clientList;

/**
    \brief Core game singleton class
*/
class Game
{
static:
    private
    {
        SiegeModule[] modules;
        bool hasLoaded;
        bool hasInited;
        bool exitNow;
        int exitVal;
        bool firstLoop = true;

        void evLoad()
        {
            signal!("evLoad");
            hasLoaded = true;
        }
        void evUnload()
        {
            hasLoaded = false;
            signal!("evUnload");
        }
        void evInit()
        {
            signal!("evInit");
            hasInited = true;
        }
        void evDeinit()
        {
            hasInited = false;
            signal!("evDeinit");
        }
    }

    /* @{ */
    /**
        \brief Load a number of modules
        \param names Names of the modules to load
    */
    void loadModules(char[][] names ...)
    {
        foreach(name; names)
            loadModule(name);
    }

    /**
        \brief Load a single module
        \param name Name of the module to load
        \warning May be removed in the future
    */
    void loadModule(char[] name)
    {
        // TODO: put this SetMissingProcCallback to a better location, so that it doesn't get loaded for every module
        derelict.util.exception.Derelict_SetMissingProcCallback(&cbMissingProc);

        modules ~= new SiegeModule(name);
    }
    /* @} */

    /**
        \brief Init SIEGE
        \note Must be called after loading modules, but before any other operations.
        \param width Window width
        \param height Window height
        \param bpp Window bits (not bytes) per pixel
        \param flags Flags for opening the window
        \return true on success, false on failure
    */
    bool init(uint width, uint height, uint bpp, uint flags)
    {
        SGModuleInfo*[] infos = new SGModuleInfo*[](modules.length);
        foreach(i, mod; modules)
            infos[i] = mod.moduleInfo;
        bool ok = true;
        foreach(i, mod; modules)
        {
            bool mok = true;
            if(mod.sgModuleMatch !is null)
                mod.sgModuleMatch(infos.ptr, infos.length, &mok);
            if(!mok)
            {
                std.c.stdio.fprintf(std.c.stdio.stderr, "Could not load module %s: Uncompatiable with other modules\n", infos[i].name);
                ok = false;
            }
        }
        if(!ok)
            return false;

        clientList = new LinkedList!(EventClient);

        evLoad();
        evInit();
        Space.main = new Space;

        //
        siege.core.window.window = new Window;

        siege.core.console.console = new Console;
        siege.input.mouse.mouse = new Mouse;
        siege.input.keyboard.keyboard = new Keyboard;
        //

        window.open(width, height, bpp, flags);

        return true;
    }
    /**
        \brief Deinit SIEGE
        \note Must be called just before exiting the program
    */
    void deinit()
    {
        evDeinit();
        evUnload();

        LinkedNode!(EventClient)* curr = clientList.firstNode;
        LinkedNode!(EventClient)* next;

        while(curr !is null)
        {
            delete curr.item;
            curr.item = null;
            next = curr.next;
            //delete curr;

            curr = next;
        }
        delete clientList;

        foreach(mod; modules)
            delete mod;
    }

    /**
        \name Main loop
    */
    // @{
    /**
        \brief Enter the main loop
        \return Zero on success, nonzero on failure (usually used as the return value of the main function)
    */
    int run()
    {
        firstLoop = true;
        exitNow = false;
        while(loop())
        {
            window.swapBuffers();
            draw.clear();
        }
        return exitVal;
    }

    /**
        \brief Run a single loop
        \note Signals evStart if this is the first run and evExit if it is the last run
        \param code The return code, as if returned from \ref run "run". Should be ignored unless false is returned
        \return true if the game is to continue to run, false if exit has been requested
    */
    bool loop(out int code)
    {
        code = exitVal;
        return loop();
    }

    /**
        \brief Run a single loop
        \note Signals evStart if this is the first run and evExit if it is the last run
        \return true if the game is to continue to run, false if exit has been requested
    */
    bool loop()
    {
        scope(exit)
        {
            if(exitNow)
            {
                signal!("evExit");
                exitNow = false;
            }
        }

        if(firstLoop)
        {
            signal!("evStart");
            firstLoop = false;
        }

        if(console.active)
        {
            console.evTickBegin();
            console.evTick();
            console.evTickEnd();

            LinkedNode!(EventClient)* c = clientList.firstNode;
            while(c !is null)
            {
                if(cast(CoreEventClient)c !is null && cast(Console)c !is null)
                    c.item.evDraw();
                c = c.next;
            }

            console.evDraw();

            return !exitNow;
        }

        signal!("evTickBegin");

        Space.main.step(0.125); // TODO: make it not const

        signal!("evTick");
        signal!("evTickEnd");

        //draw.clear();

        signal!("evDraw");

        foreach(joy; joysticks)
            joy._poll();

        return !exitNow;
    }
    // @}

    /**
        \brief Stop the main loop
        \param ret The value to return from \ref run
    */
    void stop(int ret = 0)
    {
        exitNow = true;
        exitVal = ret;
    }

    /**
        \brief Send a signal (an event)
        \param name The name of the event (including the ev- part)
        \param args The arguments to pass to the event
    */
    void signal(char[] name, args ...)()
    {
        static if(args.length > 0)
            void delegate(typeof(args)) func;
        else
            void delegate() func;
        for(LinkedNode!(EventClient)* c = clientList.firstNode; c != null; c = c.next)
        {
            if((c.item !is null) && c.item.active)
            {
                func = mixin("&c.item."~name);
                func(args);
            }
        }
    }
}
Game game;