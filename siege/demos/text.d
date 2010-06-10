module demos.text;

private
{
    import demos.common;

    import siege.core.window;
    import siege.graphics.draw;
    import siege.input.mouse;

    import siege.util.color;
    import siege.util.vector;

    import std.math;
}

class TextDemo: Demo
{
    this()
    {
        name = "Text";
        brief = "SIEGE text handling";
        description = "This demo shows SIEGE text handling";
    }

    void evDraw()
    {
        draw.color(1.0, 0.0, 0.0, 1.0);
        font.print(window.width / 2, window.height - 64.0, "Mouse Angle: %f", (mouse.position.current - window.size / 2).angle / PI * 180.0);
        draw.color(0.0, 1.0, 0.0, 1.0);
        font.print(window.width / 2, window.height - 92.0, "Mouse: %s,%s %d", mouse.position.current.x, mouse.position.current.y, mouse.wheel.current);

        font.print(128.0, window.height - 128.0, "AAA\nBBB\nCCC\nDDD\nEEE");

        draw.color(0.0, 0.5, 0.75, 0.75);
        font.print(window.width / 4, window.height / 3, "Well, this is some more text...\nUseful for UI, consoles, etc...");

        draw.line(window.size / 2                , Vector(mouse.position.current.x, mouse.position.current.y), Color(1.0, 1.0, 0.0, 0.75), Color(1.0, 1.0, 0.0, 0.75));
        draw.line(window.size / 2                , Vector(mouse.position.current.x, window.height / 2), Color(1.0, 1.0, 0.0, 0.75), Color(1.0, 1.0, 0.0, 0.75));
        draw.line(Vector(mouse.position.current.x, window.height / 2), Vector(mouse.position.current.x, mouse.position.current.y), Color(1.0, 1.0, 0.0, 0.75), Color(1.0, 1.0, 0.0, 0.75));

        draw.color(1.0, 1.0, 1.0, 1.0);
        font.printT(Vector(2, 256), "Testing UTF: ČŠŽ čšž ░▒▓\nNOTE: Might not work if the font does not support UTF");
    }
}

static this()
{
    demoinfo ~= TextDemo.classinfo;
}
