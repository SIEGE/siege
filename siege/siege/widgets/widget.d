module siege.widgets.widget;

private
{
    import siege.core.event;

    import siege.graphics.draw;

    import siege.input.mouse;

    import siege.util.linkedlist;
    import siege.util.vector;
    import siege.util.misc;

    import siege.widgets.context;
    import siege.widgets.common;
}

/**
    PreWidget is added as a workaround for a linking problem
*/
abstract class PreWidget: EventClient
{
}
abstract class Widget: PreWidget
{
    private
    {
        bool _hide;
    }

    UIContext context;
    Widget parent;
    LinkedList!(PreWidget) children;

    iVector position;
    iVector size;

    Style style;

    this(UIContext context, Widget parent, iVector position, iVector size)
    {
        context.widgets.append(this);

        this.context = context;
        this.parent = parent;
        this.position = position;
        this.size = size;

        children = new LinkedList!(PreWidget);

        if(parent !is null)
            parent.children.append(this);
            //style = parent.style;

        resetStyle();
    }

    void resetStyle()
    {
        style = context.getStyle(this);
        style.background.generate(size, style.spacing);

        if(style.background.cbRedraw !is null)
            style.background.cbRedraw(this, style);
    }

    void show()
    {
        _hide = false;
    }
    void hide()
    {
        _hide = true;
    }
    bool hidden()
    {
        return _hide;
    }

    iVector transform(iVector input)
    {
        iVector pos = position + iVector(style.spacing.left, style.spacing.top) + iVector(style.padding.left, style.padding.top);

        if(parent !is null)
            return pos + parent.transform(input);
        return pos + input;
    }
    iVector transform()
    {
        return transform(iVector(0, 0));
    }

    void evDraw()
    {
        style.background.draw(transform(), size, style.spacing);

        //debug drawDBG();
    }

    void drawDBG()
    {
        iVector pos = transform();
        iVector s = size;

        draw.color(1.0, 0.0, 0.0, 1.0);
        draw.line(pos, pos + iVector(s.x, 0));
        draw.line(pos + iVector(s.x, 0), pos + s);
        draw.line(pos + s, pos + iVector(0, s.y));
        draw.line(pos + iVector(0, s.y), pos);

        pos = pos + iVector(style.spacing.left, style.spacing.top);
        s = s - iVector(style.spacing.left + style.spacing.right, style.spacing.top + style.spacing.bottom);

        draw.color(1.0, 1.0, 1.0, 1.0);
        draw.line(pos, pos + iVector(s.x, 0));
        draw.line(pos + iVector(s.x, 0), pos + s);
        draw.line(pos + s, pos + iVector(0, s.y));
        draw.line(pos + iVector(0, s.y), pos);

        pos = pos + iVector(style.padding.left, style.padding.top);
        s = s - iVector(style.padding.left + style.padding.right, style.padding.top + style.padding.bottom);

        draw.color(0.0, 1.0, 0.0, 1.0);
        draw.line(pos, pos + iVector(s.x, 0));
        draw.line(pos + iVector(s.x, 0), pos + s);
        draw.line(pos + s, pos + iVector(0, s.y));
        draw.line(pos + iVector(0, s.y), pos);
    }

    void evMouseButton(uint button, bool down)
    {
        if(inside(mouse.position.current))
            lcMouseButton(button, down);
    }
    void evMouseButtonPressed(uint button)
    {
        if(inside(mouse.position.current))
            lcMouseButtonPressed(button);
    }
    void evMouseButtonReleased(uint button)
    {
        if(inside(mouse.position.current))
            lcMouseButtonReleased(button);
    }

    void evMouseButtonLeft(bool down)
    {
        if(inside(mouse.position.current))
            lcMouseButtonLeft(down);
    }
    void evMouseButtonLeftPressed()
    {
        if(inside(mouse.position.current))
            lcMouseButtonLeftPressed();
    }
    void evMouseButtonLeftReleased()
    {
        if(inside(mouse.position.current))
            lcMouseButtonLeftReleased();
    }

    void evMouseButtonMiddle(bool down)
    {
        if(inside(mouse.position.current))
            lcMouseButtonMiddle(down);
    }
    void evMouseButtonMiddlePressed()
    {
        if(inside(mouse.position.current))
            lcMouseButtonMiddlePressed();
    }
    void evMouseButtonMiddleReleased()
    {
        if(inside(mouse.position.current))
            lcMouseButtonMiddleReleased();
    }

    void evMouseButtonRight(bool down)
    {
        if(inside(mouse.position.current))
            lcMouseButtonRight(down);
    }
    void evMouseButtonRightPressed()
    {
        if(inside(mouse.position.current))
            lcMouseButtonRightPressed();
    }
    void evMouseButtonRightReleased()
    {
        if(inside(mouse.position.current))
            lcMouseButtonRightReleased();
    }

    void evMouseMove(int x, int y)
    {
        if(inside(mouse.position.current))
        {
            if(!inside(mouse.position.previous))
                lcMouseEnter();
            lcMouseMove(x, y);
        }
        else
        {
            if(inside(mouse.position.previous))
                lcMouseExit();
        }
    }
    void evMouseWheel(int wheel)
    {
        if(inside(mouse.position.current))
            lcMouseWheel(wheel);
    }

    bool inside(float x, float y, bool border = true)
    {
        iVector t = transform();
        if(inRange(x, cast(float)t.x, cast(float)t.x + size.x, border, border) && inRange(y, cast(float)t.y, cast(float)t.y + size.y, border, border))
            return true;
        return false;
    }
    bool inside(Vector pos, bool border = true)
    {
        return inside(pos.x, pos.y, border);
    }
    bool inside(iVector pos, bool border = true)
    {
        return inside(pos.x, pos.y, border);
    }

    void lcMouseEnter()
    {
    }
    void lcMouseExit()
    {
    }

    void lcMouseButton(uint button, bool down)
    {
    }
    void lcMouseButtonPressed(uint button)
    {
    }
    void lcMouseButtonReleased(uint button)
    {
    }

    void lcMouseButtonLeft(bool down)
    {
    }
    void lcMouseButtonLeftPressed()
    {
    }
    void lcMouseButtonLeftReleased()
    {
    }

    void lcMouseButtonMiddle(bool down)
    {
    }
    void lcMouseButtonMiddlePressed()
    {
    }
    void lcMouseButtonMiddleReleased()
    {
    }

    void lcMouseButtonRight(bool down)
    {
    }
    void lcMouseButtonRightPressed()
    {
    }
    void lcMouseButtonRightReleased()
    {
    }

    void lcMouseMove(int x, int y)
    {
    }
    void lcMouseWheel(int wheel)
    {
    }
}
