module siege.graphics.texture;

private
{
    import std.c.stdio;

    import siege.util.color;
    import siege.util.vector;

    import siege.core.window;

    import siege.modules.graphics;
}

class Texture
{
    private
    {
        static void* ttarget;
        void* texture;
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

        if(sgmGraphicsTextureCreate !is null)
            sgmGraphicsTextureCreate(&texture, window.context());
        if(sgmGraphicsTextureSetData !is null)
            sgmGraphicsTextureSetData(texture, width, height, bpp, data.ptr);
    }
    ~this()
    {
        if(sgmGraphicsTextureDestroy !is null)
            sgmGraphicsTextureDestroy(texture);
    }

    void draw(Vector location = Vector(0.0, 0.0, 0.0), Vector scale = Vector(1.0, 1.0), float angle = 0.0)
    {
        /*if(!(location.z == location.z))
            location.z = 0;

        if(sgmGraphicsTextureDraw !is null)
            sgmGraphicsTextureDraw(texture, location.x, location.y, location.z, scale.x, scale.y, angle);*/
        draw(location, scale, Vector(0.0, 0.0), angle);
    }
    void draw(Vector location, Vector scale, Vector offset, float angle = 0.0)
    {
        //draw(location, scale, angle);
        if(!(location.z == location.z))
            location.z = 0;

        if(sgmGraphicsTextureDraw !is null)
            sgmGraphicsTextureDraw(texture, location.x, location.y, location.z, scale.x, scale.y, offset.x, offset.y, angle);
    }

    Vector size()
    {
        uint x;
        uint y;
        if(sgmGraphicsTextureGetSize !is null)
            sgmGraphicsTextureGetSize(texture, &x, &y);
        return Vector(x, y);
    }
    /*iVector asize()
    {
        uint[] asize = texture.getASize(ghandle);
        return iVector(asize[0], asize[1]);
    }*/
    /*Vector ratio()
    {
        float[] ratio = texture.getRatio(ghandle);
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
        return texture.getASize(ghandle)[0];
    }
    uint aheight()
    {
        return texture.getASize(ghandle)[1];
    }*/

    void* handle()
    {
        return texture;
    }
}
