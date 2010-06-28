module siege.input.joystick;

private
{
    import siege.core.core;
    import siege.core.event;
    import siege.core.window;

    import siege.util.misc;
    import siege.util.linkedlist;

    import siege.modules.input;

    extern(C)
    {
        void cbJoystickButton(void* joystick, uint button, bool down)
        {
            uint joy;
            if(sgmCoreJoystickGetID !is null)
                sgmCoreJoystickGetID(joystick, &joy);

            bool pressed = joysticks[joy].button[button].pressed;

            foreach(client; clientList)
                if((client !is null) && client.active)
                {
                    client.evJoystickButton(joy, button);
                    if(pressed)
                        client.evJoystickButtonPress(joy, button);
                    else
                        client.evJoystickButtonRelease(joy, button);
                }
        }
        void cbJoystickMove(void* joystick, float* axis)
        {
            uint joy;
            if(sgmCoreJoystickGetID !is null)
                sgmCoreJoystickGetID(joystick, &joy);

            uint numaxis;
            if(sgmCoreJoystickGetNumAxis !is null)
                sgmCoreJoystickGetNumAxis(joystick, &numaxis);
            float[] pos = axis[0..numaxis];

            foreach(client; clientList)
                if((client !is null) && client.active)
                    client.evJoystickMove(joy, pos.dup);
        }
    }
}

class JoystickButton
{
    protected
    {
        bool prev;
        bool curr;

        void _update(bool state)
        {
            prev = curr;
            curr = state;
        }
    }

    void opAssign(bool down)
    {
        assert(0, "UNIMPLEMENTED"); //TODO
    }

    bool previous()
    {
        return prev;
    }
    bool down()
    {
        return curr;
    }
    bool up()
    {
        return !curr;
    }
    bool pressed()
    {
        return !prev && curr;
    }
    bool released()
    {
        return prev && !curr;
    }
}

class JoystickButtonHandle
{
    protected
    {
        JoystickButton[] buttons;

        void _update(ubyte button, bool state)
        {
            buttons[button]._update(state);
        }
    }

    this(ubyte num)
    {
        buttons.length = num;
        foreach(inout button; buttons)
        {
            button = new JoystickButton;
        }
    }

    bool[] previous()
    {
        bool[] but = new bool[](buttons.length);
        foreach(i, button; buttons)
            but[i] = button.prev;
        return but;
    }
    bool[] down()
    {
        bool[] but = new bool[](buttons.length);
        foreach(i, button; buttons)
            but[i] = button.down;
        return but;
    }
    bool[] up()
    {
        bool[] but = new bool[](buttons.length);
        foreach(i, button; buttons)
            but[i] = button.up;
        return but;
    }
    bool[] pressed()
    {
        bool[] but = new bool[](buttons.length);
        foreach(i, button; buttons)
            but[i] = button.pressed;
        return but;
    }
    bool[] released()
    {
        bool[] but = new bool[](buttons.length);
        foreach(i, button; buttons)
            but[i] = button.released;
        return but;
    }

    JoystickButton opIndex(ubyte index)
    {
        return buttons[index];
    }
    JoystickButton[] opSlice(ubyte index1, ubyte index2)
    {
        return buttons[index1..index2];
    }
    JoystickButton[] opSlice()
    {
        return buttons[];
    }

    size_t length()
    {
        return buttons.length;
    }
    alias length number;
}

class JoystickPosition
{
    protected
    {
        float prev;
        float curr;

        void _update(float p)
        {
            prev = curr;
            curr = p;
        }
    }

    void opAssign(float pos)
    {
        assert(0, "UNIMPLEMENTED"); //TODO
    }

    float previous()
    {
        return prev;
    }
    float current()
    {
        return curr;
    }
    float delta()
    {
        return curr - prev;
    }
}

class JoystickPositionHandle
{
    protected
    {
        JoystickPosition[] positions;

        void _update(ubyte axis, float pos)
        {
            positions[axis]._update(pos);
        }
    }

    this(ubyte num)
    {
        positions.length = num;
        foreach(inout position; positions)
            position = new JoystickPosition;
    }

    float[] previous()
    {
        float[] pos = new float[](positions.length);
        foreach(i, position; positions)
            pos[i] = position.prev;
        return pos;
    }
    float[] current()
    {
        float[] pos = new float[](positions.length);
        foreach(i, position; positions)
            pos[i] = position.curr;
        return pos;
    }
    float[] delta()
    {
        float[] pos = new float[](positions.length);
        foreach(i, position; positions)
            pos[i] = position.curr - position.prev;
        return pos;
    }

    JoystickPosition opIndex(ubyte index)
    {
        return positions[index];
    }
    JoystickPosition[] opSlice(ubyte index1, ubyte index2)
    {
        return positions[index1..index2];
    }
    JoystickPosition[] opSlice()
    {
        return positions[];
    }

    size_t length()
    {
        return positions.length;
    }
    alias length number;
}

class Joystick
{
    package
    {
        uint number;

        SGCoreJoystickCallbacks callbacks;
        void* jhandle;

        static uint[] flags;
    }

    void _poll()
    {
        if(find(flags, SG_JOYSTICK_BUTTON_NOCB) != -1)
        {
            bool[] barr = new bool[](button.length);
            if(sgmCoreJoystickGetButtons !is null)
                sgmCoreJoystickGetButtons(jhandle, barr.ptr);
            foreach(i, b; barr)
            {
                button._update(i, b);
                if(button[i].prev != button[i].curr)
                    cbJoystickButton(jhandle, i, b);
            }
        }
        if(find(flags, SG_JOYSTICK_AXIS_NOCB) != -1)
        {
            float[] parr = new float[](position.length);
            if(sgmCoreJoystickGetAxis !is null)
                sgmCoreJoystickGetAxis(jhandle, parr.ptr);
            foreach(i, p; parr)
            {
                position._update(i, p);
                if(position[i].prev != position[i].curr)
                {
                    cbJoystickMove(jhandle, parr.ptr);
                    break;
                }
            }
        }
    }

    this(uint number)
    {
        // TODO: PUT FLAGS INTO STATIC THIS
        uint* cflags;
        if(sgmCoreJoystickGetFlags !is null)
            sgmCoreJoystickGetFlags(&cflags);
        if(cflags !is null)
        {
            uint i;
            while(flags[i] != 0)
                i++;
            flags = cflags[0..i].dup;
        }
        if(sgmCoreJoystickFreeFlags !is null)
            sgmCoreJoystickFreeFlags(cflags);
        // --------------------------------

        callbacks.button = &cbJoystickButton;
        callbacks.move = &cbJoystickMove;

        if(sgmCoreJoystickCreate !is null)
            sgmCoreJoystickCreate(&jhandle, window.handle, number);

        if(sgmCoreJoystickSetCallbacks !is null)
            sgmCoreJoystickSetCallbacks(jhandle, &callbacks);

        this.number = number;

        uint buttons;
        if(sgmCoreJoystickGetNumButtons !is null)
            sgmCoreJoystickGetNumButtons(jhandle, &buttons);

        uint axis;
        if(sgmCoreJoystickGetNumAxis !is null)
            sgmCoreJoystickGetNumAxis(jhandle, &buttons);

        button = new JoystickButtonHandle(buttons);
        position = new JoystickPositionHandle(axis);
    }
    ~this()
    {
        if(sgmCoreJoystickDestroy !is null)
            sgmCoreJoystickDestroy(jhandle);
    }

    JoystickButtonHandle button;
    JoystickPositionHandle position;

    uint id()
    {
        return number;
    }
    void* handle()
    {
        return jhandle;
    }
}

Joystick[] joysticks;
Joystick joystick;
