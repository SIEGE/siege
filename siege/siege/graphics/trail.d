module siege.graphics.trail;

private
{
    import siege.graphics.draw;

    import siege.util.color;
    import siege.util.vector;
    import siege.util.queue;
}

class Trail
{
    Queue!(Vector) trail;
    Color startColor;
    Color endColor;

    uint maxLength;

    this(uint maxLength, Color startColor = Color(1.0, 1.0, 1.0, 1.0), Color endColor = Color(1.0, 1.0, 1.0, 0.0))
    {
        this.maxLength = maxLength;
        this.startColor = startColor;
        this.endColor = endColor;
    }

    void addPoint(Vector pos)
    {
        trail.push(pos);
        if(trail.length > maxLength)
            trail.pop();
    }

    void addBreak()
    {
        trail.push(Vector.nan);
    }

    void draw()
    {
        if(trail.length != 0 && trail[0].isNan)
            trail.pop();

        if(trail.length == 0)
            return;

        size_t i;

        float totalLength = 0.0;
        float currentLength = 0.0;
        Vector ppos = trail[0];
        Vector pos;
        Color col;
        for(i = 0; i < trail.length; i++)
        {
            pos = trail[i];
            if(pos.isNan)
                continue;
            totalLength += (ppos - pos).length;
            ppos = pos;
        }

        //glPushAttrib(GL_CURRENT_BIT);
            siege.graphics.draw.draw.begin(Primitive.LineStrip);
                ppos = trail[0];
                for(i = 0; i < trail.length; i++)
                {
                    pos = trail[i];
                    if(pos.isNan)
                    {
                        siege.graphics.draw.draw.end();
                        siege.graphics.draw.draw.begin(Primitive.LineStrip);
                        continue;
                    }
                    col = Color.mix(endColor, startColor, currentLength / totalLength);
                    siege.graphics.draw.draw.color(col);
                    siege.graphics.draw.draw.vertex(pos);

                    currentLength += (ppos - pos).length;
                    ppos = pos;
                }
            siege.graphics.draw.draw.end();
        //glPopAttrib();
    }
}
