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
        ubyte bpp;
        ubyte[] data;

        if(!siege.modules.graphics.load(fname, width, height, bpp, data))
            fprintf(stderr, "Could not load image %.*s\n", fname);

        this(width, height, bpp, data);
    }
    this(uint width, uint height, ubyte bpp, ubyte[] data = null)
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

        if(sgGraphicsSurfaceCreate !is null)
            sgGraphicsSurfaceCreate(&surface, window.context());
        if(sgGraphicsSurfaceSetData !is null)
            sgGraphicsSurfaceSetData(surface, width, height, bpp, data.ptr);
    }
    ~this()
    {
        if(sgGraphicsSurfaceDestroy !is null)
            sgGraphicsSurfaceDestroy(surface);
    }

    void draw(Vector location = Vector(0.0, 0.0, 0.0), Vector scale = Vector(1.0, 1.0), float angle = 0.0)
    {
        /*if(!(location.z == location.z))
            location.z = 0;

        if(sgGraphicsSurfaceDraw !is null)
            sgGraphicsSurfaceDraw(surface, location.x, location.y, location.z, scale.x, scale.y, angle);*/
        draw(location, scale, Vector(0.0, 0.0), angle);
    }
    void draw(Vector location, Vector scale, Vector offset, float angle = 0.0)
    {
        //draw(location, scale, angle);
        if(!(location.z == location.z))
            location.z = 0;

        if(sgGraphicsSurfaceDraw !is null)
            sgGraphicsSurfaceDraw(surface, location.x, location.y, location.z, scale.x, scale.y, offset.x, offset.y, angle);
    }

    void target()
    {
        if(sgGraphicsSurfaceSetTarget !is null)
            sgGraphicsSurfaceSetTarget(surface);
        starget = surface;
    }
    void untarget()
    {
        if(sgGraphicsSurfaceResetTarget !is null)
            sgGraphicsSurfaceResetTarget(starget);
        starget = null;
    }

    void clear(Color color = Color(0, 0, 0, 0))
    {
        target();
        if(sgGraphicsContextClear !is null)
            sgGraphicsContextClear(window.context(), color.rgba.ptr);
        untarget();
    }

    iVector size()
    {
        iVector ret;
        if(sgGraphicsSurfaceGetSize !is null)
            sgGraphicsSurfaceGetSize(surface, cast(uint*)&ret.x, cast(uint*)&ret.y);
        return ret;
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
        return size().x;
    }
    uint height()
    {
        return size().y;
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
