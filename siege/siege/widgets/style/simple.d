module siege.widgets.style.simple;

private
{
    import std.bind;
    import std.string;

    import siege.graphics.draw;
    import siege.graphics.surface;
    import siege.graphics.texture;
    import siege.graphics.font;

    import siege.util.color;
    import siege.util.vector;

    import siege.widgets.widget;
    import siege.widgets.context;
    import siege.widgets.common;
}

enum SUnit
{
    Inherit,
    Percent,
    Inch,
    Centimeter,
    Millimeter,
    Em,
    Ex,
    Point,
    Pica,
    Pixel,
}
enum SBAttachment
{
    Inherit,
    Scroll,
    Fixed,
}
enum SBRepeat
{
    Inherit,
    NoRepeat = 0b001,
    RepeatX  = 0b010,
    RepeatY  = 0b100,
    RepeatXY = 0b110,
}
enum SBStyle
{
    Inherit,
    None,
    Hidden,
    Dotted,
    Dashed,
    Solid,
    Double,
    Groove,
    Ridge,
    Inset,
    Outset,
}
enum SFStyle
{
    Inherit,
    Normal,
    Italic,
    Oblique,
}
enum SFVariant
{
    Inherit,
    Normal,
    SmallCaps
}
enum SFWeight
{
    Inherit,
    W100, // light
    W200, // light
    W300, // normal /light?
    W400, // normal
    W500, // normal
    W600, // bold /normal?
    W700, // bold
    W800, // bold
    W900, // bold
    Lighter = W100,
    Normal  = W400,
    Bold    = W700,
    Bolder  = W900,
}
struct SSize
{
    int value;
    SUnit unit = SUnit.Inherit;
}
struct SBackground
{
    SBAttachment attachment = SBAttachment.Inherit;
    Color color;
    Surface/**Texture*/ image;
    SSize xpos;
    SSize ypos;
    SBRepeat repeat;
}
struct SBorder
{
    Color color;
    SBStyle style = SBStyle.Inherit;
    SSize width;
}
alias SBorder SOutline;
struct SBorders
{
    SBorder top;
    SBorder right;
    SBorder bottom;
    SBorder left;
}
struct SDimension
{
    SSize width;
    SSize height;
}
struct SDimensions
{
    SDimension size;
    SDimension min;
    SDimension max;
}
struct SFont
{
    char[] family;
    SSize size;
    SFStyle style = SFStyle.Inherit;
    SFVariant variant = SFVariant.Inherit;
}
/*struct SContent
{
}*/
/*struct SList
{
}*/
struct SMargin
{
    SSize top;
    SSize right;
    SSize bottom;
    SSize left;
}
alias SMargin SPadding;

struct SStyle
{
    SBackground background;
    SBorders borders;
    SOutline outline;
    SDimensions dimensions;
    SFont font;
    SMargin margin;
    SPadding padding;
}

class SimpleStyle
{
    protected
    {
        void delegate(Widget widget, inout Style style) cbDlg;
    }

    Font[uint][char[]] fonts;
    SStyle[char[]] items;

    UIContext context;

    this(UIContext context, Font sans, Font serif = null, Font mono = null)
    {
        this.context = context;

        if(serif is null)
            serif = sans;
        if(mono is null)
            mono = sans;

        fonts["Sans-serif"][cast(uint)sans.height] = sans;
        fonts["Serif"][cast(uint)sans.height] = serif;
        fonts["Monospace"][cast(uint)sans.height] = mono;

        context.defstyle.background.cbRedraw = &cbRedraw;
    }

    void cbRedraw(Widget widget, inout Style style)
    {
        style.background.surface.target();

        draw.color(0.0, 1.0, 0.0);
        draw.quad(widget.position, widget.position + widget.size, true);

        style.background.surface.untarget();
    }

    char[][] getBaseStyles(ClassInfo info)
    {
        char[] name = info.name.split(".")[$-1];

        if(name == "Object")
            return null;

        char[][] styles;

        styles ~= getBaseStyles(info.base);
        if(name in items)
            styles ~= name;

        return styles;
    }
}
