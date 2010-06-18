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

        Vector wpos;
        Vector wsize;
        Vector pos;
        Vector size;
    }
    this(Vector wpos, Vector wsize, Vector pos = Vector(), Vector size = Vector())
    {
        if(sgGraphicsViewportCreate !is null)
            sgGraphicsViewportCreate(&viewport, window.context());

        set(wpos, wsize, pos, size);
    }
    this(uint wx, uint wy, uint wwidth, uint wheight, uint x, uint y, uint width, uint height)
    {
        this(Vector(wx, wy), Vector(wwidth, wheight), Vector(x, y), Vector(width, height));
    }
    ~this()
    {
        if(sgGraphicsViewportDestroy !is null)
            sgGraphicsViewportDestroy(viewport);
    }

    void set(Vector wpos, Vector wsize, Vector pos, Vector size)
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
        set(Vector(wx, wy), Vector(wwidth, wheight), Vector(x, y), Vector(width, height));
    }
    void set()
    {
        reset();
    }
    void reset()
    {
        /// \todo This should use int, not uint - or should it?
        if(sgGraphicsViewportSetView !is null)
            sgGraphicsViewportSetView(viewport, cast(uint)wpos.x, cast(uint)wpos.y, cast(uint)wsize.x, cast(uint)wsize.y, pos.x, pos.y, size.x, size.y);
    }

    /*void get(out uint wx, out uint wy, out uint wwidth, out uint wheight, out float x, out float y, out float width, out float height)
    {
        viewport.get(wx, wy, wwidth, wheight, x, y, width, height);
    }*/

    static Viewport main;
}
