/**
    \brief Holds the Window class, which maintains and provides an interface for window handling
*/
module siege.core.window;

private
{
    import siege.core.core;
    import siege.core.event;

    import siege.input.joystick;

    import siege.graphics.viewport;

    import siege.util.vector;
    import siege.util.linkedlist;

    import std.format;
    import std.string;
    import std.c.stdarg;

    import siege.modules.graphics;
    import siege.modules.window;
    import siege.modules.input;

    extern(C)
    {
        void cbWindowOpen(void* window)
        {
            foreach(client; clientList)
                if((client !is null) && client.active)
                    client.evWindowOpen();
        }
        void cbWindowClose(void* window)
        {
            foreach(client; clientList)
                if((client !is null) && client.active)
                    client.evWindowClose();
            game.stop();
        }
        void cbWindowResize(void* window, uint width, uint height)
        {
            foreach(client; clientList)
                if((client !is null) && client.active)
                    client.evWindowResize(width, height);
        }
    }
}

class Window
{
    private
    {
        char[] format(TypeInfo[] arguments, va_list argptr)
        {
            char[] text;
            void putc(dchar c)
            {
                text ~= c;
            }
            doFormat(&putc, arguments, argptr);

            return text;
        }

        SGCoreWindowCallbacks callbacks;
        void* whandle;
        void* ghandle;

        char[] _title;
    }

    this()
    {
        //callbacks.open = &cbWindowOpen;
        callbacks.close = &cbWindowClose;
        //callbacks.resize = &cbWindowResize;

        if(sgmCoreWindowCreate !is null)
            sgmCoreWindowCreate(&whandle);

        if(sgmCoreWindowSetCallbacks !is null)
            sgmCoreWindowSetCallbacks(whandle, &callbacks);
    }
    ~this()
    {
        if(sgmCoreWindowDestroy !is null)
            sgmCoreWindowDestroy(whandle);
    }

    void open(uint width, uint height, uint bpp, uint flags)
    {
        if(width == 0)
            width = 640;
        if(height == 0)
            height = 480;
        if(bpp == 0)
            bpp = 32;

        if(opened())
            close();

        if(sgmCoreWindowOpen !is null)
            sgmCoreWindowOpen(whandle, width, height, bpp, flags);

        uint joynum;
        if(sgmCoreJoystickGetNumJoysticks !is null)
            sgmCoreJoystickGetNumJoysticks(whandle, &joynum);
        joysticks.length = joynum;
        foreach(i, inout joy; joysticks)
            joy = new Joystick(i + 1);
        if(joysticks.length > 0)
            joystick = joysticks[0];


        Vector s = size();
        if(sgmGraphicsContextCreate !is null)
            sgmGraphicsContextCreate(&ghandle, cast(uint)s.x, cast(uint)s.y, bpp); /// PROBLEM SPOT (sgmGraphicsContextResize -> sgmGraphicsTextureCreate)
        Viewport.main = new Viewport(Vector(0, 0), s);

        cbWindowOpen(whandle);
        cbWindowResize(whandle, cast(uint)s.x, cast(uint)s.y);
    }
    bool opened()
    {
        bool opened;
        if(sgmCoreWindowIsOpened !is null)
            sgmCoreWindowIsOpened(whandle, &opened);
        return opened;
    }
    void close()
    {
        if(sgmGraphicsContextDestroy !is null)
            sgmGraphicsContextDestroy(ghandle);
        if(sgmCoreWindowClose !is null)
            sgmCoreWindowClose(whandle);
    }

    void title(...)
    {
        titleT(format(_arguments, _argptr));
    }
    void titleT(char[] title)
    {
        _title = title.dup;
        if(sgmCoreWindowSetTitle !is null)
            sgmCoreWindowSetTitle(whandle, toStringz(_title));
    }
    char[] title()
    {
        return _title.dup;
    }

    void size(uint width, uint height)
    {
        if(sgmCoreWindowSetSize !is null)
            sgmCoreWindowSetSize(whandle, width, height);
        if(sgmGraphicsContextResize !is null)
            sgmGraphicsContextResize(ghandle, width, height);
    }
    void size(Vector s)
    {
        size(cast(uint)s.x, cast(uint)s.y);
    }
    Vector size()
    {
        uint x;
        uint y;
        if(sgmCoreWindowGetSize !is null)
            sgmCoreWindowGetSize(whandle, &x, &y);
        return Vector(x, y);
    }

    void width(uint w)
    {
        size(Vector(w, size().y));
    }
    uint width()
    {
        return cast(uint)size().x;
    }
    void height(uint h)
    {
        size(Vector(size().x, h));
    }
    uint height()
    {
        return cast(uint)size().y;
    }

    void swapBuffers()
    {
        if(sgmCoreWindowSwapBuffers !is null)
            sgmCoreWindowSwapBuffers(whandle);
    }

    void* handle()
    {
        return whandle;
    }
    void* context()
    {
        return ghandle;
    }
}
Window window;
