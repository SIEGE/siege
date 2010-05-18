module siege.widgets.context;

private
{
    import std.string;

    import siege.util.linkedlist;

    import siege.widgets.widget;
    import siege.widgets.common;
}

class UIContext
{
    Style defstyle;
    Theme theme;

    LinkedList!(Widget) widgets;
    this(Style defstyle)
    {
        this.defstyle = defstyle;

        widgets = new LinkedList!(Widget);
    }

    void resetStyle()
    {
        LinkedNode!(Widget) *w = widgets.firstNode;
        for(uint i = 0; i < widgets.length; i++)
        {
            w.item.resetStyle();
            w = w.next;
        }
    }

    Style getStyle(Object o)
    {
        return getStyle(o.classinfo.name.split(".")[$-1]);
    }
    Style getStyle(Object o, char[] attr)
    {
        char[] name = o.classinfo.name.split(".")[$-1];
        char[] full = name ~ "#" ~ attr;

        if(full in theme)
            return theme[full];
        if(name in theme)
            return theme[name];
        return defstyle;
    }
    Style getStyle(char[] name)
    {
        if(name in theme)
            return theme[name];
        return defstyle;
    }
}
