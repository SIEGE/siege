module main;

import siege.siege;
import demos.all;
import std.stdio;
import std.string;
import std.compiler;

int main(char[][] args)
{
    writefln("Compiled with %s %d.%.3d", std.compiler.name, std.compiler.version_major, std.compiler.version_minor);
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
