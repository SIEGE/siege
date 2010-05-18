module siege.graphics.texture;

private
{
    import std.c.stdio;

    import siege.util.color;
    import siege.util.vector;

    import siege.core.window;

    import siege.modules.graphics;
}

// todo...
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

        if(sgGraphicsTextureCreate !is null)
            sgGraphicsTextureCreate(&texture, window.context());
        if(sgGraphicsTextureSetData !is null)
            sgGraphicsTextureSetData(texture, width, height, bpp, data.ptr);
    }
    ~this()
    {
        if(sgGraphicsTextureDestroy !is null)
            sgGraphicsTextureDestroy(texture);
    }

    void draw(Vector location = Vector(0.0, 0.0, 0.0), Vector scale = Vector(1.0, 1.0), float angle = 0.0)
    {
        /*if(!(location.z == location.z))
            location.z = 0;

        if(sgGraphicsTextureDraw !is null)
            sgGraphicsTextureDraw(texture, location.x, location.y, location.z, scale.x, scale.y, angle);*/
        draw(location, scale, Vector(0.0, 0.0), angle);
    }
    void draw(Vector location, Vector scale, Vector offset, float angle = 0.0)
    {
        //draw(location, scale, angle);
        if(!(location.z == location.z))
            location.z = 0;

        if(sgGraphicsTextureDraw !is null)
            sgGraphicsTextureDraw(texture, location.x, location.y, location.z, scale.x, scale.y, offset.x, offset.y, angle);
    }

    iVector size()
    {
        iVector ret;
        if(sgGraphicsTextureGetSize !is null)
            sgGraphicsTextureGetSize(texture, cast(uint*)&ret.x, cast(uint*)&ret.y);
        return ret;
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
        return size().x;
    }
    uint height()
    {
        return size().y;
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
