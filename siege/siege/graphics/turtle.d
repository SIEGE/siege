module siege.graphics.turtle;

private
{
    import std.math;

    import siege.graphics.draw;
    import siege.util.vector;
}

class Turtle
{
    Vector previous;
    Vector position;

    bool drawing;
    float angle;

    private
    {
        Vector sposition;

        bool sdrawing;
        float sangle;
    }

    this(Vector position = Vector(), float angle = 0.0f, bool drawing = false)
    {
        this.previous = position;
        this.position = position;
        this.angle = angle;
        this.drawing = drawing;

        this.sposition = position;
        this.sdrawing = drawing;
        this.sangle = angle;
    }

    void move(float length = 1.0f)
    {
        float a = angle / 180.0 * PI;
        cfloat e = expi(a) * length;
        previous = position;
        position = position + Vector(e.re, e.im);

        if(drawing)
        {
            draw.begin(Primitive.Lines);
                draw.vertex(previous);
                draw.vertex(position);
            draw.end();
        }
    }

    void up()
    {
        drawing = false;
    }
    void down()
    {
        drawing = true;
    }

    bool isUp()
    {
        return !drawing;
    }
    bool isDown()
    {
        return drawing;
    }

    void reset()
    {
        previous = sposition;
        position = sposition;
        angle = sangle;
        drawing = sdrawing;
    }
}
