module siege.graphics.viewport;

private
{
    import siege.util.vector;

    import siege.core.window;

    import siege.modules.graphics;
}

class Viewport
{
    private
    {
        void* viewport;

        iVector wpos;
        iVector wsize;
        Vector pos;
        Vector size;
    }
    this(iVector wpos, iVector wsize, Vector pos = Vector(), Vector size = Vector())
    {
        if(sgGraphicsViewportCreate !is null)
            sgGraphicsViewportCreate(&viewport, window.context());

        set(wpos, wsize, pos, size);
    }
    this(uint wx, uint wy, uint wwidth, uint wheight, uint x, uint y, uint width, uint height)
    {
        this(iVector(wx, wy), iVector(wwidth, wheight), Vector(x, y), Vector(width, height));
    }
    ~this()
    {
        if(sgGraphicsViewportDestroy !is null)
            sgGraphicsViewportDestroy(viewport);
    }

    void set(iVector wpos, iVector wsize, Vector pos, Vector size)
    {
        if(pos.isNan)
            pos = Vector(wpos.x, wpos.y);
        if(size.isNan)
            size = Vector(wsize.x, wsize.y);

        this.wpos = wpos;
        this.wsize = wsize;
        this.pos = pos;
        this.size = size;

        reset();
    }
    void set(uint wx, uint wy, uint wwidth, uint wheight, float x, float y, float width, float height)
    {
        set(iVector(wx, wy), iVector(wwidth, wheight), Vector(x, y), Vector(width, height));
    }
    void set()
    {
        reset();
    }
    void reset()
    {
        if(sgGraphicsViewportSetView !is null)
            sgGraphicsViewportSetView(viewport, wpos.x, wpos.y, wsize.x, wsize.y, pos.x, pos.y, size.x, size.y);
    }

    /*void get(out uint wx, out uint wy, out uint wwidth, out uint wheight, out float x, out float y, out float width, out float height)
    {
        viewport.get(wx, wy, wwidth, wheight, x, y, width, height);
    }*/

    static Viewport main;
}
