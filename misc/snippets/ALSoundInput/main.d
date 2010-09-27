pragma(lib, "DerelictAL");
pragma(lib, "DerelictUtil");

import derelict.openal.al;

import wrapper;

import std.stdio;
import std.date;

void sleep(real secs)
{
    repeat(secs, {});
}
void repeat(real secs, uint delegate() dlg)
{
    repeat(secs, { dlg(); });
}
void repeat(real secs, void delegate() dlg)
{
    real stime = getUTCtime() / cast(real)TicksPerSecond;
    while(((getUTCtime() / cast(real)TicksPerSecond) - stime) <= secs)
        dlg();
}

int main(char[][] args)
{
    DerelictAL.load();
    wrapper.init();

    uint frequency = 44100;
    uint format = AL_FORMAT_MONO16;
    uint bufsize = 44100 * 1;

    Capture capture = new Capture(null, frequency, format, bufsize);

    capture.start();
    repeat(1, &capture.poll); // run capture.poll for 1 second (esentially listening for input for 1s)
    capture.stop();

    Source source = capture.toSource();
    source.bplay();

    delete capture;
    Buffer buffer = source.buffer;
    delete buffer;
    delete source;

    wrapper.exit();
    return 0;
}
