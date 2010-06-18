module buffer;

private
{
    import derelict.openal.al;
}

class Buffer
{
    uint id;

    this()
    {
        alGenBuffers(1, &id);
    }
    this(uint id)
    {
        id = this.id;
    }
    ~this()
    {
        alDeleteBuffers(1, &id);
    }

    void data(void[] data, uint format, uint frequency)
    {
        alBufferData(id, format, data.ptr, data.length, frequency);
    }
}
