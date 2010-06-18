module wrapper;

private
{
    import derelict.openal.al;
}

public
{
    import buffer;
    import capture;
    import source;
}

ALCdevice* device;
ALCcontext* context;
void init()
{
    device = alcOpenDevice(null);
    context = alcCreateContext(device, null);
    alcMakeContextCurrent(context);
}

void exit()
{
    alcMakeContextCurrent(null);
    alcDestroyContext(context);
    alcCloseDevice(device);
}
