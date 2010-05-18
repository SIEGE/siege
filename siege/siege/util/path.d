module siege.util.path;

private
{
    import siege.graphics.draw;

    import siege.util.color;
    import siege.util.vector;
}

class Path
{
    Vector[] points;
    bool smooth;
    bool round;

    this(bool smooth, bool round, Vector[] points ...)
    {
        this.points = points;
        this.smooth = smooth;
        this.round = round;
    }

    /// TODO: ANGLE, SMOOTH
    void drawDBG(Vector location = Vector(0.0, 0.0), float angle = 0, Color c = Color(1.0, 1.0, 1.0, 1.0))
    {
        draw.color(c);

        if(round)
            draw.begin(Primitive.LineLoop);
        else
            draw.begin(Primitive.Lines);
        foreach(p; points)
        {
            draw.vertex(location + p);
        }
        draw.end();
    }
}
