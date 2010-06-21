module demos.widgets;

private
{
    import demos.common;

    import siege.all;
    import std.stdio;
    import std.utf;
}

class WidgetDemo: Demo
{
    WidgetHandle handle;
    this()
    {
        name = "Widgets";
        brief = "Widgets test (WiP)";
        description = "A work in progress testing/demo for SIEGE widgets toolkit";
    }

    void evStart()
    {
        handle = new WidgetHandle;
        new Button(handle, Vector(16, 16), Vector(96, 16), "Test button");
        new Input(handle, Vector(16, 32), Vector(96, 16), "Input box");
    }
}

static this()
{
    demoinfo ~= WidgetDemo.classinfo;
}

class WidgetHandle: EventClient
{
    LinkedList!(Widget) widgets;
    Font font;

    this(Font font = null)
    {
        // NOTE: fonts cause a segfault on exit!
        if(font is null)
            font = new Font("Data/Fonts/DejaVuLGCSansMono.ttf", 10, 256);
            //font = new Font("Data/Fonts/DejaVuLGCSans.ttf", 10, 256);

        widgets = new LinkedList!(Widget);
        this.font = font;
    }

    void evDraw()
    {
        foreach(widget; widgets)
            widget.evDraw();
    }

    void evMouseButtonPress(uint button)
    {
        foreach(widget; widgets)
        {
            if(widget.inside(mouse.position.current))
                widget.lcMouseButtonPress(button);
        }
    }
    void evMouseButtonRelease(uint button)
    {
        foreach(widget; widgets)
        {
            if(widget.inside(mouse.position.current))
                widget.lcMouseButtonRelease(button);
        }
    }
    void evMouseMove(int x, int y)
    {
        foreach(widget; widgets)
        {
            widget.evMouseMove(x, y);
            if(!widget.inside(mouse.position.previous) && widget.inside(x, y))
                widget.lcMouseEnter();
            else if(widget.inside(mouse.position.previous) && !widget.inside(x, y))
                widget.lcMouseExit();
        }
    }
}

abstract class Widget: EventClient
{
    WidgetHandle handle;
    LinkedNode!(Widget) *node;

    Vector position;
    Vector size;

    this(WidgetHandle handle)
    {
        this.handle = handle;
        node = handle.widgets.append(this);
    }

    ~this()
    {
        handle.widgets.remove(node);
    }

    void evDraw()
    {
        draw.color(0.0, 0.5, 0.75, 1.0);
        draw.quad(position, position + size, true);

        draw.color(0.0, 0.75, 1.0, 1.0);
        draw.quad(position, position + size, false);
    }

    bool inside(float x, float y)
    {
        if(inRange(x, position.x, position.x + size.x) && inRange(y, position.y, position.y + size.y))
            return true;
        return false;
    }
    bool inside(Vector pos)
    {
        return inside(pos.x, pos.y);
    }

    void lcMouseButtonPress(uint button)
    {
    }
    void lcMouseButtonRelease(uint button)
    {
    }
    void lcMouseEnter()
    {
    }
    void lcMouseExit()
    {
    }
}

class Button: Widget
{
    bool over = false;
    bool down = false;
    char[] text;

    this(WidgetHandle handle, Vector position, Vector size, char[] text)
    {
        if(size == Vector(0, 0))
            size = handle.font.strSizeT(text);

        super(handle);
        this.position = position;
        this.size = size;
        this.text = text;
    }

    void evDraw()
    {
        if(!over)
            draw.color(0.0, 0.25, 0.5, 1.0);
        else if(!down)
            draw.color(0.0, 0.5, 0.75, 1.0);
        else
            draw.color(0.0, 1.0, 1.0, 1.0);
        draw.quad(position, position + size, true);

        if(!over)
            draw.color(0.0, 0.5, 0.75, 1.0);
        else if(!down)
            draw.color(0.0, 0.75, 1.0, 1.0);
        else
            draw.color(0.0, 0.5, 0.75, 1.0);
        draw.quad(position, position + size, false);

        handle.font.printCenteredT(position + size / 2, text);
    }

    void lcMouseButtonPress(uint button)
    {
        if(button == 1)
            down = true;
    }
    void evMouseButtonRelease(uint button)
    {
        if(button == 1)
            down = false;
    }
    void lcMouseEnter()
    {
        over = true;
    }
    void lcMouseExit()
    {
        over = false;
    }
}

class Input: Widget
{
    bool focus = false;
    dchar[] input = null;
    uint cursor = 0;
    bool insert = true;

    this(WidgetHandle handle, Vector position, Vector size, char[] def = null)
    {
        super(handle);
        this.position = position;
        this.size = size;

        input = toUTF32(def);
    }

    void evDraw()
    {
        draw.color(0.0, 0.25, 0.5, 1.0);
        draw.quad(position, position + size, true);

        draw.color(0.0, 0.5, 0.75, 1.0);
        draw.quad(position, position + size, false);

        if(focus && ((time() % 1) > 0.5))
        {
            Vector lpos = handle.font.strSizeT(toUTF8(input[0..cursor]));
            lpos.y = 0;

            draw.color(1.0, 1.0, 1.0, 1.0);
            if(insert)
                draw.line(position + lpos, position + lpos + Vector(0, size.y));
            else
            {
                Vector lposnext;
                if(cursor < input.length)
                    lposnext = handle.font.strSizeT(toUTF8(input[cursor..cursor + 1]));
                else
                    lposnext = handle.font.strSizeT("W");
                lposnext.y = 0;
                draw.line(position + lpos + Vector(0, size.y), position + lpos + lposnext + Vector(0, size.y));
            }
            draw.color(0.0, 0.5, 0.75, 1.0);
        }

        handle.font.printT(position + Vector(0, size.y / 2), toUTF8(input));
    }

    void evKeyboardKeyPress(uint key)
    {
        evKeyboardKeyRepeat(key);
    }
    void evKeyboardKeyRepeat(uint key)
    {
        if(!focus)
            return;

        if(key == SG_KEYBOARD_KEY_LEFT)
        {
            if(cursor > 0)
                cursor--;
        }
        else if(key == SG_KEYBOARD_KEY_RIGHT)
        {
            if(cursor < input.length)
                cursor++;
        }
        else if(key == SG_KEYBOARD_KEY_BACKSPACE)
        {
            if(cursor > 0)
            {
                input = input[0..cursor-1] ~ input[cursor..$];
                cursor--;
            }
        }
        else if(key == SG_KEYBOARD_KEY_DELETE)
        {
            if(cursor < input.length)
            {
                input = input[0..cursor] ~ input[cursor+1..$];
            }
        }
        else if(key == SG_KEYBOARD_KEY_INSERT)
            insert = !insert;
    }
    void evKeyboardCharPress(dchar chr)
    {
        evKeyboardCharRepeat(chr);
    }
    void evKeyboardCharRepeat(dchar chr)
    {
        if(!focus)
            return;

        if(chr == '\b') // backspace -- handled in evKeyboardKey
            return;
        else if(chr == '\x7F') // delete (127)
            return;
        else if(chr == '\n') // not accepted in one-line inputs
            return;
        else if(chr == '\r') // ditto
            return;

        if(insert)
            input = input[0..cursor] ~ [chr] ~ input[cursor..$];
        else if(cursor < input.length)
            input[cursor] = chr;
        else
            input ~= chr;
        cursor++;
    }

    void evMouseButtonPress(uint button)
    {
        if(!inside(mouse.position.current))
            focus = false;
    }
    void lcMouseButtonPress(uint button)
    {
        focus = true;
    }
}
