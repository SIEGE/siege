/**
    \brief Contains the root Demo class
    \todo Make demos changeable via widgets (UI)
    \todo Make the use of siege.core.level for this
*/
module demos.common;

private
{
    import siege.core.core;
    import siege.core.event;
    import siege.graphics.draw;
    import siege.graphics.font;

    import siege.util.vector;

    import std.stdio;
    import std.string;
}

Font font;

/// \brief Contains the list of demo classes, for switching
Demo[] demos;
ClassInfo[] demoinfo;

/**
    \brief Root demo class
*/
abstract class Demo: EventClient
{
    /// \brief The name (title) of the demo
    char[] name;
    /// \brief A short (brief) description
    char[] brief;
    /// \brief A long description
    char[] description;
    /// \brief Controls, et cetera
    char[] instructions;

    this()
    {
        demos ~= this;
        deactivate();
    }

    ~this()
    {
        foreach(i, demo; demos)
            if(demo is this)
            {
                demos = demos[0..i] ~ demos[i+1..$];
                break;
            }
    }

    /*void evStart() {}
    void evExit() {}
    void evTick() {}
    void evTickBegin() {}
    void evTickEnd() {}
    void evDraw() {}*/
}

class DemoHandler: EventClient
{
    Demo demo;

    this()
    {
        foreach(i, demo; demoinfo)
            demo.create();

        writefln("Available demos:");
        foreach(i, demo; demos)
            writefln("%d %s: %s", i, demo.name, demo.brief);

        char[] input = null;
        while(input is null)
        {
            writef("Select the demo or (q)uit: ");
            input = tolower(chomp(readln()));
            if(input == "quit" || input == "q" || input == "exit" || input == "e")
                game.stop();
            else
            {
                int i = atoi(input);
                if(i < 0 || i >= demos.length)
                    input = null;
                else
                {
                    demo = demos[i];
                    demo.activate();
                }
            }
        }
    }

    void evStart()
    {
        font = new Font("Data/Fonts/DejaVuLGCSans.ttf", "Data/Fonts/DejaVuLGCSans-Bold.ttf", "Data/Fonts/DejaVuLGCSans-Oblique.ttf", "Data/Fonts/DejaVuLGCSans-BoldOblique.ttf", 10, 256);
        demo.evStart();
    }
    void evExit()
    {
        demo.evExit();
    }

    void evTick()
    {
        demo.evTick();
    }
    void evTickBegin()
    {
        demo.evTickBegin();
    }
    void evTickEnd()
    {
        demo.evTickEnd();
    }
    void evDraw()
    {
        demo.evDraw();
        draw.color(1.0, 1.0, 1.0, 1.0);
        font.print(Vector(2, 48), "%s\n%s\n \n%s\n \nInstructions: ", demo.name, demo.brief, demo.description, demo.instructions);
    }
}
