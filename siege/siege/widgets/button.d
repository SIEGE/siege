module siege.widgets.button;

private
{
    import std.math;

    import siege.widgets.widget;

    import siege.graphics.draw;

    import siege.util.misc;
    import siege.util.vector;

    import siege.input.mouse;

    import siege.widgets.context;
    import siege.widgets.common;
}

enum ButtonState
{
    UP,
    OVER,
    DOWN,
}

class Button: Widget
{
    protected
    {
        char[] btext;
    }

    ButtonState state = ButtonState.UP;
    Style over;
    Style down;

    this(UIContext context, Widget parent, iVector position, iVector size = iVector(0, 0))
    {
        super(context, parent, position, size);
    }

    void resetStyle()
    {
        style = context.getStyle(this);

        setSize();
        generateBG();

        over = context.getStyle(this, "Over");
        down = context.getStyle(this, "Down");

        redraw();
    }
    void setSize()
    {
        iVector psize = size;
        Vector tsize = style.font.strSizeT(btext);

        size.x = cast(uint) ceil(tsize.x) + 4;
        size.x = max(size.x + style.spacing.left + style.spacing.right + style.padding.left + style.padding.right, psize.x);

        size.y = cast(uint) ceil(tsize.y) + 2;
        size.y = max(size.y + style.spacing.top + style.spacing.bottom + style.padding.top + style.padding.bottom, psize.y);
    }
    void generateBG()
    {
        style.background.generate(size, style.spacing);
    }
    void redraw()
    {
        if(style.background.cbRedraw !is null)
            style.background.cbRedraw(this, style);
    }

    void evDraw()
    {
        if(state == ButtonState.OVER)
            swap(style, over);
        else if(state == ButtonState.DOWN)
            swap(style, down);

        //setSize();

        iVector tp = transform();
        Vector t = Vector(tp.x, tp.y)
                 + Vector(style.spacing.left + style.padding.left, style.spacing.top + style.padding.top)
                 + Vector(size.x - style.spacing.left - style.spacing.right - style.padding.left - style.padding.right, size.y - style.spacing.top - style.spacing.bottom - style.padding.top - style.padding.bottom) / 2.0;

        //if(std.string.split(this.classinfo.name,".")[$-1] == "Button")
        //    printf("TRANSFORM: %f,%f\n", t.x, t.y);

        super.evDraw();
        draw.color(style.textColor);
        style.font.printCenteredT(t, btext);

        if(state == ButtonState.OVER)
            swap(style, over);
        else if(state == ButtonState.DOWN)
            swap(style, down);
    }

    void lcMouseEnter()
    {
        if(mouse.button.left.down)
            state = ButtonState.DOWN;
        else
            state = ButtonState.OVER;
    }
    void lcMouseExit()
    {
        state = ButtonState.UP;
    }
    void lcMouseButtonLeft(bool down)
    {
        if(down)
            state = ButtonState.DOWN;
        else
            state = ButtonState.OVER;
    }

    void text(char[] t)
    {
        btext = t;

        setSize();
        generateBG();
        redraw();
    }
    char[] text()
    {
        return btext;
    }
}
