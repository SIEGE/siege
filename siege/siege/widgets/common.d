module siege.widgets.common;

private
{
    import siege.graphics.surface;
    import siege.graphics.font;

    import siege.util.color;
    import siege.util.vector;

    import siege.widgets.widget;
}

struct Spacing
{
    int top = 0;
    int right = 0;
    int bottom = 0;
    int left = 0;

    static Spacing opCall(int top, int right, int bottom, int left)
    {
        Spacing s;
        s.top = top;
        s.right = right;
        s.bottom = bottom;
        s.left = left;
        return s;
        //return Spacing(top, right, bottom, left);
    }
    static Spacing opCall(int top, int lr, int bottom)
    {
        return Spacing(top, lr, bottom, lr);
    }
    static Spacing opCall(int tb, int lr)
    {
        return Spacing(tb, lr, tb, lr);
    }
    static Spacing opCall(int all)
    {
        return Spacing(all, all, all, all);
    }
    static Spacing opCall()
    {
        Spacing s;
        return s;
        //return Spacing();
    }
}
alias Spacing Padding;

struct Background
{
    Surface surface;

    void delegate(Widget widget, inout Style style) cbRedraw;
    void generate(iVector size, Spacing spacing)
    {
        surface = new Surface(size.x, size.y, 32);
    }

    void draw(iVector position, iVector size, Spacing spacing)
    {
        if(surface !is null)
            surface.draw(Vector(position.x, position.y),
                         Vector(size.x / cast(float)surface.size.x,
                                size.y / cast(float)surface.size.y));
    }
}

struct Style
{
    Spacing spacing;
    Spacing padding;

    Color textColor;
    iVector textAlign;
    Background background;

    Font font;
}

alias Style[char[]] Theme;
