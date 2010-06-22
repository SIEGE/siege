module siege.graphics.surface;

private
{
    import std.c.stdio;

    import siege.util.color;
    import siege.util.vector;

    import siege.core.window;

    import siege.modules.graphics;
}

class Surface
{
    private
    {
        static void* starget;
        void* surface;
    }

    this(char[] fname)
    {
        uint width;
        uint height;
        uint bpp;
        ubyte[] data;

        if(!siege.modules.graphics.load(fname, width, height, bpp, data))
            fprintf(stderr, "Could not load image %.*s\n", fname);

        this(width, height, bpp, data);
    }
    this(uint width, uint height, uint bpp, ubyte[] data = null)
    {
        uint bypp;
        switch(bpp)
        {
            case 0:
                fprintf(stderr, "Getting bpp from window unimplemented, using 24\n");
                bypp = 3;
                break;
            case 8:
                bypp = 1;
                break;
            case 15:
                bypp = 2;
                break;
            case 16:
                bypp = 2;
                break;
            case 24:
                bypp = 3;
                break;
            case 32:
                bypp = 4;
                break;
            default:
                assert(0, "Bad bit depth\n");
        }

        if(data !is null)
            data = toCanvasSize(data, width, height, bypp);

        if(sgmGraphicsSurfaceCreate !is null)
            sgmGraphicsSurfaceCreate(&surface, window.context());
        if(sgmGraphicsSurfaceSetData !is null)
            sgmGraphicsSurfaceSetData(surface, width, height, bpp, data.ptr);
    }
    ~this()
    {
        if(sgmGraphicsSurfaceDestroy !is null)
            sgmGraphicsSurfaceDestroy(surface);
    }

    void draw(Vector location = Vector(0.0, 0.0, 0.0), Vector scale = Vector(1.0, 1.0), float angle = 0.0)
    {
        /*if(!(location.z == location.z))
            location.z = 0;

        if(sgmGraphicsSurfaceDraw !is null)
            sgmGraphicsSurfaceDraw(surface, location.x, location.y, location.z, scale.x, scale.y, angle);*/
        draw(location, scale, Vector(0.0, 0.0), angle);
    }
    void draw(Vector location, Vector scale, Vector offset, float angle = 0.0)
    {
        //draw(location, scale, angle);
        if(!(location.z == location.z))
            location.z = 0;

        if(sgmGraphicsSurfaceDraw !is null)
            sgmGraphicsSurfaceDraw(surface, location.x, location.y, location.z, scale.x, scale.y, offset.x, offset.y, angle);
    }

    void target()
    {
        if(sgmGraphicsSurfaceSetTarget !is null)
            sgmGraphicsSurfaceSetTarget(surface);
        starget = surface;
    }
    void untarget()
    {
        if(sgmGraphicsSurfaceResetTarget !is null)
            sgmGraphicsSurfaceResetTarget(starget);
        starget = null;
    }

    void clear(Color color = Color(0, 0, 0, 0))
    {
        target();
        if(sgmGraphicsContextClear !is null)
            sgmGraphicsContextClear(window.context(), color.rgba.ptr);
        untarget();
    }

    Vector size()
    {
        uint x;
        uint y;
        if(sgmGraphicsSurfaceGetSize !is null)
            sgmGraphicsSurfaceGetSize(surface, &x, &y);
        return Vector(x, y);
    }
    /*iVector asize()
    {
        uint[] asize = surface.getASize(ghandle);
        return iVector(asize[0], asize[1]);
    }*/
    /*Vector ratio()
    {
        float[] ratio = surface.getRatio(ghandle);
        return Vector(ratio[0], ratio[1]);
    }*/

    uint width()
    {
        return cast(uint)size().x;
    }
    uint height()
    {
        return cast(uint)size().y;
    }
    /*uint awidth()
    {
        return surface.getASize(ghandle)[0];
    }
    uint aheight()
    {
        return surface.getASize(ghandle)[1];
    }*/

    void* handle()
    {
        return surface;
    }
}
