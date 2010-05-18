module siege.core.core;

private
{
    import siege.core.event;

    ///
    import siege.graphics.draw;
    import siege.core.console;
    import siege.core.window;
    import siege.input.mouse;
    import siege.input.keyboard;
    import siege.input.joystick;
    import siege.util.linkedlist;
    import siege.physics.space;
    ///

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
LinkedNode!(EventClient) *currentClient;

class Game
{
    protected
    {
        SiegeModule[] modules;
        bool hasLoaded;
        bool hasInited;
        bool exitNow;
    }

    this(char[][] names ...)
    {
        writefln("Compiled with %s %s.%s", __VENDOR__, std.string.toString(__VERSION__)[0], std.string.toString(__VERSION__)[1..$]);
        writefln("Date: %s", __DATE__);
        writefln("Time: %s", __TIME__);
        writefln("----------------------------------------");

        derelict.util.exception.Derelict_SetMissingProcCallback(&cbMissingProc);
        game = this;

        loadModules(names);
    }

    void loadModules(char[][] names ...)
    {
        foreach(name; names)
            loadModule(name);
    }

    void loadModule(char[] name)
    {
        modules ~= new SiegeModule(name);
    }

    bool init()
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

        ///
        siege.graphics.draw.draw = new DrawModule;
        siege.core.window.window = new Window;

        siege.core.console.console = new Console;
        siege.input.mouse.mouse = new Mouse;
        siege.input.keyboard.keyboard = new Keyboard;
        ///

        return true;
    }
    void deinit()
    {
        evUninit();
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

    void run()
    {
        window.open(0, 0, 0, false);

        //EventClient[] clients;
        //CoreEventClient ec;
        alias currentClient c;

        scope(exit)
        {
            c = clientList.firstNode;
            while(c !is null)
            {
                c.item.evExit();
                c = c.next;
            }
        }

        /*foreach(c; classList)
        {
            ec = cast(CoreEventClient)c;
            if(ec !is null)
                clients ~= c;
        }*/

        c = clientList.firstNode;
        while(c !is null)
        {
            c.item.evStart();
            c = c.next;
        }

        while(!exitNow)
        {
            if(console.opened)
            {
                console.evTickBegin();
                console.evTick();
                console.evTickEnd();

                draw.clear();

                c = clientList.firstNode;
                while(c !is null)
                {
                    if(cast(CoreEventClient)c !is null && cast(Console)c !is null)
                        c.item.evDraw();
                    c = c.next;
                }

                console.evDraw();

                window.swapBuffers();
                continue;
            }

            c = clientList.firstNode;
            while(c !is null)
            {
                if(cast(CoreEventClient)c !is null)
                    c.item.evTickBegin();
                c = c.next;
            }

            Space.main.step(0.125); // todo: make it not const
            c = clientList.firstNode;
            while(c !is null)
            {
                if(cast(CoreEventClient)c !is null)
                    c.item.evTick();
                c = c.next;
            }

            c = clientList.firstNode;
            while(c !is null)
            {
                if(cast(CoreEventClient)c !is null)
                    c.item.evTickEnd();
                c = c.next;
            }

            //draw.clear();

            c = clientList.firstNode;
            while(c !is null)
            {
                if(cast(CoreEventClient)c !is null)
                    c.item.evDraw();
                c = c.next;
            }

            window.swapBuffers();
            foreach(joy; joysticks)
                joy._poll();
            draw.clear();
        }
    }

    void evLoad()
    {
        alias currentClient c;

        c = clientList.firstNode;
        while(c !is null)
        {
            if(cast(ModuleEventClient)c !is null)
                c.item.evLoad();
            c = c.next;
        }

        hasLoaded = true;
    }
    void evUnload()
    {
        alias currentClient c;

        hasLoaded = false;

        c = clientList.firstNode;
        while(c !is null)
        {
            if(cast(ModuleEventClient)c !is null)
                c.item.evUnload();
            c = c.next;
        }
    }
    void evInit()
    {
        alias currentClient c;

        c = clientList.firstNode;
        while(c !is null)
        {
            if(cast(ModuleEventClient)c !is null)
                c.item.evInit();
            c = c.next;
        }

        hasInited = true;
    }
    void evUninit()
    {
        alias currentClient c;

        hasInited = false;

        c = clientList.firstNode;
        while(c !is null)
        {
            if(cast(ModuleEventClient)c !is null)
                c.item.evUninit();
            c = c.next;
        }
    }

    void exit()
    {
        exitNow = true;
    }

    /*template runEvent(T, char[] name, bool self = false)
    {
        void runEvent()
        {
            T ec;
            foreach(c; classList)
            {
                ec = cast(T)c;
                static if(self)
                {
                    if(ec !is null)
                        mixin("ec"~name~"();");
                }
                else
                {
                    if((ec !is null) && (ec !is cast(T)this))
                        mixin("ec"~name~"();");
                }
            }
        }
    }*/
}
Game game;
