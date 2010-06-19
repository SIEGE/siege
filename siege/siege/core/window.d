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
            LinkedNode!(EventClient) *c = clientList.firstNode;
            while(c !is null)
            {
                if(cast(WindowEventClient)c !is null)
                    c.item.evWindowOpen();
                c = c.next;
            }
            //runEvent!(WindowEventClient, "WindowOpen", false);
        }
        void cbWindowClose(void* window)
        {
            LinkedNode!(EventClient) *c = clientList.firstNode;
            while(c !is null)
            {
                if(cast(WindowEventClient)c !is null)
                    c.item.evWindowClose();
                c = c.next;
            }
            //runEvent!(WindowEventClient, "WindowClose", false);
            game.stop();
        }
        void cbWindowResize(void* window, uint width, uint height)
        {
            LinkedNode!(EventClient) *c = clientList.firstNode;
            while(c !is null)
            {
                if(cast(WindowEventClient)c !is null)
                    c.item.evWindowResize(width, height);
                c = c.next;
            }
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

        if(sgCoreWindowCreate !is null)
            sgCoreWindowCreate(&whandle);

        if(sgCoreWindowSetCallbacks !is null)
            sgCoreWindowSetCallbacks(whandle, &callbacks);
    }
    ~this()
    {
        if(sgCoreWindowDestroy !is null)
            sgCoreWindowDestroy(whandle);
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

        if(sgCoreWindowOpen !is null)
            sgCoreWindowOpen(whandle, width, height, bpp, flags);

        uint joynum;
        if(sgCoreJoystickGetNumJoysticks !is null)
            sgCoreJoystickGetNumJoysticks(whandle, &joynum);
        joysticks.length = joynum;
        foreach(i, inout joy; joysticks)
            joy = new Joystick(i + 1);
        if(joysticks.length > 0)
            joystick = joysticks[0];


        Vector s = size();
        if(sgGraphicsContextCreate !is null)
            sgGraphicsContextCreate(&ghandle, cast(uint)s.x, cast(uint)s.y, bpp); /// PROBLEM SPOT (sgGraphicsContextResize -> sgGraphicsTextureCreate)
        Viewport.main = new Viewport(Vector(0, 0), s);

        cbWindowOpen(whandle);
        cbWindowResize(whandle, width, height);
    }
    bool opened()
    {
        bool opened;
        if(sgCoreWindowIsOpened !is null)
            sgCoreWindowIsOpened(whandle, &opened);
        return opened;
    }
    void close()
    {
        if(sgGraphicsContextDestroy !is null)
            sgGraphicsContextDestroy(ghandle);
        if(sgCoreWindowClose !is null)
            sgCoreWindowClose(whandle);
    }

    void title(...)
    {
        titleT(format(_arguments, _argptr));
    }
    void titleT(char[] title)
    {
        _title = title.dup;
        if(sgCoreWindowSetTitle !is null)
            sgCoreWindowSetTitle(whandle, toStringz(_title));
    }
    char[] title()
    {
        return _title.dup;
    }

    void size(uint width, uint height)
    {
        if(sgCoreWindowSetSize !is null)
            sgCoreWindowSetSize(whandle, width, height);
        if(sgGraphicsContextResize !is null)
            sgGraphicsContextResize(ghandle, width, height);
    }
    void size(Vector s)
    {
        size(cast(uint)s.x, cast(uint)s.y);
    }
    Vector size()
    {
        uint x;
        uint y;
        if(sgCoreWindowGetSize !is null)
            sgCoreWindowGetSize(whandle, &x, &y);
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
        if(sgCoreWindowSwapBuffers !is null)
            sgCoreWindowSwapBuffers(whandle);
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
