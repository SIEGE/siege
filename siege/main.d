module main;

import siege.siege;
import demos.common;
import std.stdio;
import std.string;

int main(char[][] args)
{
    writefln("Compiled with %s %s.%s", __VENDOR__, toString(__VERSION__)[0], toString(__VERSION__)[1..$]);
    writefln("Date: %s", __DATE__);
    writefln("Time: %s", __TIME__);
    writefln("----------------------------------------");

    game.loadModule("SDL");
    game.loadModule("OpenGL");
    game.loadModule("DevIL");
    game.loadModule("OpenAL");
    game.loadModule("SndFile");
    game.loadModule("Freetype");
    game.loadModule("Chipmunk");
    game.init(640, 480, 32, 0);
    new DemoHandler;
    game.run();
    game.deinit();

    return 0;
}
