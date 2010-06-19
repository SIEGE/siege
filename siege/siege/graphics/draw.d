module siege.graphics.draw;

private
{
    import siege.util.color;
    import siege.util.vector;

    import siege.core.window;

    import siege.graphics.texture;
    import siege.modules.graphics;
}

enum Primitive: ubyte
{
    Points              =   0x01,
    Lines               =   0x02,
    LineStrip           =   0x03,
    LineFan             =   0x04,
    LineLoop            =   0x05,
    Triangles           =   0x06,
    TriangleStrip       =   0x07,
    TriangleFan         =   0x08,
//  TriangleLoop        =   0x09,
    Quads               =   0x0A,
    QuadStrip           =   0x0B,
//  QuadFan             =   0x0C,
//  QuadLoop            =   0x0D
    ConvexPolygon       =   0x10,
    ConcavePolygon      =   0x20,
    IntersectingPolygon =   0x30,
    Polygon             =   IntersectingPolygon,
}

enum RenderMode: ubyte
{
    None,
    Point,
    Line,
    Fill
}

enum BlendFunc
{
    Zero,
    One,
    DstColor,
    OneMinusDstColor,
    SrcAlpha,
    OneMinusSrcAlpha,
    DstAlpha,
    OneMinusDstAlpha,
    SrcAlphaSaturate,

    SrcColor,
    OneMinusSrcColor,
}

/*interface DrawLineInterface
{
    void setWidth(float w);
    float getWidth();
}

interface DrawModuleInterface
{
    void begin(ubyte type);

    void end();

    void clear();

    void color(float r, float g, float b, float a = 1.0);
    void color(int r, int g, int b, int a = 0xFF);

    void texCoord(float x, float y);
    void texCoord(int x, int y);

    void vertex(float x, float y, float z = 0.0);
    void vertex(int x, int y, int z = 0);

    void setPolygonMode(ubyte mode);
}*/

class DrawPoint
{
static:
    void opCall(float x, float y, Color c)
    {
        draw.begin(Primitive.Points);
            draw.color(c);
            draw.vertex(x, y);
        draw.end();
    }
    void opCall(Vector p, Color c)
    {
        opCall(p.x, p.y, c);
    }

    void opCall(float x, float y)
    {
        draw.begin(Primitive.Points);
            draw.vertex(x, y);
        draw.end();
    }
    void opCall(Vector p)
    {
        opCall(p.x, p.y);
    }

    void size(float s)
    {
        if(sgGraphicsDrawPointSetSize !is null)
            sgGraphicsDrawPointSetSize(window.context(), s);
    }
    /*float size()
    {
        return point.getSize();
    }*/
}

class DrawLine
{
static:
    void opCall(float x1, float y1, float x2, float y2, Color c1, Color c2)
    {
        draw.begin(Primitive.Lines);
            draw.color(c1);
            draw.vertex(x1, y1);
            draw.color(c2);
            draw.vertex(x2, y2);
        draw.end();
    }
    void opCall(int x1, int y1, int x2, int y2, Color c1, Color c2)
    {
        draw.begin(Primitive.Lines);
            draw.color(c1);
            draw.vertex(x1, y1);
            draw.color(c2);
            draw.vertex(x2, y2);
        draw.end();
    }
    void opCall(Vector p1, Vector p2, Color c1, Color c2)
    {
        opCall(p1.x, p1.y, p2.x, p2.y, c1, c2);
    }

    void opCall(float x1, float y1, float x2, float y2)
    {
        draw.begin(Primitive.Lines);
            draw.vertex(x1, y1);
            draw.vertex(x2, y2);
        draw.end();
    }
    void opCall(int x1, int y1, int x2, int y2)
    {
        draw.begin(Primitive.Lines);
            draw.vertex(x1, y1);
            draw.vertex(x2, y2);
        draw.end();
    }
    void opCall(Vector p1, Vector p2)
    {
        opCall(p1.x, p1.y, p2.x, p2.y);
    }

    void width(float w)
    {
        if(sgGraphicsDrawLineSetWidth !is null)
            sgGraphicsDrawLineSetWidth(window.context(), w);
    }
    /*float width()
    {
        return line.getWidth();
    }*/
}

class DrawTriangle
{
static:
    void opCall(float x1, float y1, float x2, float y2, float x3, float y3, Color c1, Color c2, Color c3, bool fill = true)
    {
        if(fill)
            draw.begin(Primitive.Triangles);
        else
            draw.begin(Primitive.LineLoop);

            draw.color(c1);
            draw.vertex(x1, y1);
            draw.color(c2);
            draw.vertex(x2, y2);
            draw.color(c3);
            draw.vertex(x3, y3);
        draw.end();
    }
    void opCall(int x1, int y1, int x2, int y2, int x3, int y3, Color c1, Color c2, Color c3, bool fill = true)
    {
        if(fill)
            draw.begin(Primitive.Triangles);
        else
            draw.begin(Primitive.LineLoop);

            draw.color(c1);
            draw.vertex(x1, y1);
            draw.color(c2);
            draw.vertex(x2, y2);
            draw.color(c3);
            draw.vertex(x3, y3);
        draw.end();
    }
    void opCall(Vector p1, Vector p2, Vector p3, Color c1, Color c2, Color c3, bool fill = true)
    {
        opCall(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, c1, c2, c3, fill);
    }

    void opCall(float x1, float y1, float x2, float y2, float x3, float y3, bool fill = true)
    {
        if(fill)
            draw.begin(Primitive.Triangles);
        else
            draw.begin(Primitive.LineLoop);

            draw.vertex(x1, y1);
            draw.vertex(x2, y2);
            draw.vertex(x3, y3);
        draw.end();
    }
    void opCall(int x1, int y1, int x2, int y2, int x3, int y3, bool fill = true)
    {
        if(fill)
            draw.begin(Primitive.Triangles);
        else
            draw.begin(Primitive.LineLoop);

            draw.vertex(x1, y1);
            draw.vertex(x2, y2);
            draw.vertex(x3, y3);
        draw.end();
    }
    void opCall(Vector p1, Vector p2, Vector p3, bool fill = true)
    {
        opCall(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, fill);
    }
}

class DrawQuad
{
static:
    void opCall(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, Color c1, Color c2, Color c3, Color c4, bool fill = true)
    {
        if(fill)
            draw.begin(Primitive.Quads);
        else
            draw.begin(Primitive.LineLoop);

            draw.color(c1);
            draw.vertex(x1, y1);
            draw.color(c2);
            draw.vertex(x2, y2);
            draw.color(c3);
            draw.vertex(x3, y3);
            draw.color(c4);
            draw.vertex(x4, y4);
        draw.end();
    }
    void opCall(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, Color c1, Color c2, Color c3, Color c4, bool fill = true)
    {
        if(fill)
            draw.begin(Primitive.Quads);
        else
            draw.begin(Primitive.LineLoop);

            draw.color(c1);
            draw.vertex(x1, y1);
            draw.color(c2);
            draw.vertex(x2, y2);
            draw.color(c3);
            draw.vertex(x3, y3);
            draw.color(c4);
            draw.vertex(x4, y4);
        draw.end();
    }
    void opCall(Vector p1, Vector p2, Vector p3, Vector p4, Color c1, Color c2, Color c3, Color c4, bool fill = true)
    {
        opCall(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y, c1, c2, c3, c4, fill);
    }

    void opCall(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, bool fill = true)
    {
        if(fill)
            draw.begin(Primitive.Quads);
        else
            draw.begin(Primitive.LineLoop);

            draw.vertex(x1, y1);
            draw.vertex(x2, y2);
            draw.vertex(x3, y3);
            draw.vertex(x4, y4);
        draw.end();
    }
    void opCall(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, bool fill = true)
    {
        if(fill)
            draw.begin(Primitive.Quads);
        else
            draw.begin(Primitive.LineLoop);

            draw.vertex(x1, y1);
            draw.vertex(x2, y2);
            draw.vertex(x3, y3);
            draw.vertex(x4, y4);
        draw.end();
    }
    void opCall(Vector p1, Vector p2, Vector p3, Vector p4, bool fill = true)
    {
        opCall(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y, fill);
    }

    /// Rectangle
    void opCall(float x1, float y1, float x2, float y2, Color c1, Color c2, Color c3, Color c4, bool fill = true)
    {
        opCall(x1, y1, x2, y1, x2, y2, x1, y2, c1, c2, c3, c4, fill);
    }
    void opCall(int x1, int y1, int x2, int y2, Color c1, Color c2, Color c3, Color c4, bool fill = true)
    {
        opCall(x1, y1, x2, y1, x2, y2, x1, y2, c1, c2, c3, c4, fill);
    }
    void opCall(Vector p1, Vector p2, Color c1, Color c2, Color c3, Color c4, bool fill = true)
    {
        opCall(p1.x, p1.y, p2.x, p2.y, c1, c2, c3, c4, fill);
    }
    void opCall(float x1, float y1, float x2, float y2, Color c, bool fill = true)
    {
        opCall(x1, y1, x2, y1, x2, y2, x1, y2, c, c, c, c, fill);
    }
    void opCall(int x1, int y1, int x2, int y2, Color c, bool fill = true)
    {
        opCall(x1, y1, x2, y1, x2, y2, x1, y2, c, c, c, c, fill);
    }
    void opCall(Vector p1, Vector p2, Color c, bool fill = true)
    {
        opCall(p1.x, p1.y, p2.x, p2.y, c, c, c, c, fill);
    }
    void opCall(float x1, float y1, float x2, float y2, bool fill = true)
    {
        opCall(x1, y1, x2, y1, x2, y2, x1, y2, fill);
    }
    void opCall(int x1, int y1, int x2, int y2, bool fill = true)
    {
        opCall(x1, y1, x2, y1, x2, y2, x1, y2, fill);
    }
    void opCall(Vector p1, Vector p2, bool fill = true)
    {
        opCall(p1.x, p1.y, p2.x, p2.y, fill);
    }
}

class DrawEllipse
{
static:
}

class DrawModule
{
static:
    package
    {
        Primitive drawType;
        Texture drawTexture;

        float[] drawPoints;
        float[] drawTexCoords;
        float[] drawColors;

        static Color curColor;
        static Vector curTexCoord;
    }

    DrawPoint point;
    DrawLine line;
    DrawTriangle triangle;
    DrawQuad quad;
    DrawEllipse ellipse;

    void begin(Primitive type, Texture texture = null)
    {
        if(drawPoints.length != 0 || drawTexCoords.length != 0 || drawColors.length != 0)
            throw new Exception("Cannot draw.begin - called twice.");

        drawType = type;
        drawTexture = texture;
    }
    void end()
    {
        void* texture;
        if(drawTexture !is null)
            texture = drawTexture.handle();

        if(sgGraphicsDrawPrimitive !is null)
            sgGraphicsDrawPrimitive(window.context(), texture, drawType, drawPoints.length / 3, drawPoints.ptr, drawTexCoords.ptr, drawColors.ptr);
        drawPoints.length = 0;
        drawTexCoords.length = 0;
        drawColors.length = 0;
    }

    void clear(Color col = Color(0, 0, 0, 0))
    {
        if(sgGraphicsContextClear !is null)
            sgGraphicsContextClear(window.context(), col.rgba.ptr);
    }

    void color(Color col)
    {
        if(sgGraphicsDrawSetColor !is null)
            sgGraphicsDrawSetColor(window.context(), col.rgba.ptr);
        curColor = col;
    }
    void color(Vector col)
    {
        color(Color(col.x, col.y, col.z, col.w));
    }
    void color(float r, float g, float b, float a = 1.0)
    {
        color(Color(r, g, b, a));
    }
    void color(ubyte r, ubyte g, ubyte b, ubyte a = 0xFF)
    {
        color(Color(r / 255.0, g / 255.0, b / 255.0, a / 255.0));
    }
    void color(float col, float a = 1.0)
    {
        color(Color(col, col, col, a));
    }
    void color(ubyte col, ubyte a = 255)
    {
        color(Color(col / 255.0, col / 255.0, col / 255.0, a / 255.0));
    }

    void texCoord(float x, float y)
    {
        curTexCoord = Vector(x, y);
    }
    void texCoord(int x, int y)
    {
        curTexCoord = Vector(x, y);
    }
    void texCoord(Vector coord)
    {
        curTexCoord = coord;
    }

    void vertex(float x, float y, float z = 0.0)
    {
        drawPoints ~= [x, y, z];
        drawTexCoords ~= [curTexCoord.x, curTexCoord.y];
        drawColors ~= curColor.rgba;
    }
    void vertex(int x, int y, int z = 0)
    {
        drawPoints ~= [x, y, z];
        drawTexCoords ~= [curTexCoord.x, curTexCoord.y];
        drawColors ~= curColor.rgba;
    }
    void vertex(Vector vert)
    {
        drawPoints ~= [vert.x, vert.y, vert.z];
        drawTexCoords ~= [curTexCoord.x, curTexCoord.y];
        drawColors ~= curColor.rgba;
    }

    /*void polygonMode(ubyte mode)
    {
        draw.setDrawMode(mode);
    }
    void blendFunc(uint src, uint dst)
    {
        draw.setBlendFunc(src, dst);
    }*/
}
DrawModule draw;

///
/*static this()
{
    draw = new DrawModule;
}*/
///
