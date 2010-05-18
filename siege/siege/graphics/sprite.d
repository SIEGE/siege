module siege.graphics.sprite;

private
{
    import siege.graphics.texture;

    import siege.util.vector;
    import siege.core.event;
}

class Sprite: EventClient
{
    Vector offset;
    Texture[] subimages;
    float image = 0;
    float speed = 0;

    this(char[] fname, Vector offset = Vector())
    {
        subimages = [new Texture(fname)];

        if(offset.isNan())
        {
            iVector size = subimages[0].size;
            offset.x = size.x / 2.0;
            offset.y = size.y / 2.0;
        }
        this.offset = offset;
    }
    this(char[] fname, float xo, float yo)
    {
        this(fname, Vector(xo, yo));
    }

    void draw(Vector location, Vector scale = Vector(1.0, 1.0), float angle = 0.0)
    {
        subimages[cast(uint)image].draw(location, scale, offset, angle);
    }
    void draw(float x, float y, float angle = 0.0)
    {
        draw(Vector(x, y), Vector(1.0, 1.0), angle);
    }

    void evTick()
    {
        image += speed;

        while(cast(uint)image >= subimages.length)
            image -= subimages.length;
    }

    iVector size()
    {
        return subimages[0].size;
    }
}
