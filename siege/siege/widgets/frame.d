module siege.widgets.frame;

private
{
    import siege.widgets.widget;

    import siege.util.vector;

    import siege.widgets.context;
}

class Frame: Widget
{
    this(UIContext context, Widget parent, iVector position, iVector size)
    {
        super(context, parent, position, size);
    }
}
