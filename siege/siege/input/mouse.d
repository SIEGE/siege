module siege.input.mouse;

private
{
    import siege.core.core;
    import siege.core.event;
    import siege.core.window;

    import siege.util.misc;
    import siege.util.vector;
    import siege.util.linkedlist;

    import siege.modules.input;

    import siege.core.console;

    extern(C)
    {
        void cbMouseButton(void* cmouse, uint button, bool down)
        {
            mouse.button.update(button, down);

            bool pressed = siege.input.mouse.mouse.button[button].pressed;

            if(console.opened)
            {
                console.evMouseButton(button, down);
                if(pressed)
                    console.evMouseButtonPressed(button);
                else
                    console.evMouseButtonReleased(button);

                switch(button)
                {
                    case 1:
                        console.evMouseButtonLeft(down);
                        if(pressed)
                            console.evMouseButtonLeftPressed();
                        else
                            console.evMouseButtonLeftReleased();
                        break;
                    case 2:
                        console.evMouseButtonMiddle(down);
                        if(pressed)
                            console.evMouseButtonMiddlePressed();
                        else
                            console.evMouseButtonMiddleReleased();
                        break;
                    case 3:
                        console.evMouseButtonRight(down);
                        if(pressed)
                            console.evMouseButtonRightPressed();
                        else
                            console.evMouseButtonRightReleased();
                        break;
                    default:
                        break;
                }
                return;
            }

            LinkedNode!(EventClient) *c = clientList.firstNode;
            while(c !is null)
            {
                if(cast(MouseEventClient)c !is null)
                {
                    c.item.evMouseButton(button, down);
                    if(pressed)
                        c.item.evMouseButtonPressed(button);
                    else
                        c.item.evMouseButtonReleased(button);

                    switch(button)
                    {
                        case 1:
                            c.item.evMouseButtonLeft(down);
                            if(pressed)
                                c.item.evMouseButtonLeftPressed();
                            else
                                c.item.evMouseButtonLeftReleased();
                            break;
                        case 2:
                            c.item.evMouseButtonRight(down);
                            if(pressed)
                                c.item.evMouseButtonRightPressed();
                            else
                                c.item.evMouseButtonRightReleased();
                            break;
                        case 3:
                            c.item.evMouseButtonMiddle(down);
                            if(pressed)
                                c.item.evMouseButtonMiddlePressed();
                            else
                                c.item.evMouseButtonMiddleReleased();
                            break;
                        default:
                            break;
                    }
                }
                c = c.next;
            }
        }
        void cbMouseMove(void* cmouse, int x, int y)
        {
            mouse.position.update(x, y);

            if(console.opened)
            {
                console.evMouseMove(x, y);
                return;
            }

            LinkedNode!(EventClient) *c = clientList.firstNode;
            while(c !is null)
            {
                if(cast(MouseEventClient)c !is null)
                    c.item.evMouseMove(x, y);
                c = c.next;
            }
        }
        void cbMouseWheel(void* cmouse, int w)
        {
            mouse.wheel.update(w);

            if(console.opened)
            {
                console.evMouseWheel(w);
                return;
            }

            LinkedNode!(EventClient) *c = clientList.firstNode;
            while(c !is null)
            {
                if(cast(MouseEventClient)c !is null)
                    c.item.evMouseWheel(w);
                c = c.next;
            }
        }
    }
}

class MouseButton
{
    protected
    {
        bool prev;
        bool curr;

        void update(bool state)
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

class MouseButtonHandle
{
    protected
    {
        MouseButton[] buttons;

        void update(ubyte button, bool state)
        {
            buttons[button].update(state);
        }
    }

    MouseButton left, middle, right;

    this(ubyte num)
    {
        num = max(num, 3U);

        buttons.length = num;
        foreach(inout button; buttons)
        {
            button = new MouseButton;
        }

        left = buttons[0];
        right = buttons[1];
        middle = buttons[2];
    }

    bool[] previous()
    {
       bool[] but;
       foreach(i, button; buttons)
       {
           but[i] = button.prev;
       }
       return but;
    }
    bool[] down()
    {
       bool[] but;
       foreach(i, button; buttons)
       {
           but[i] = button.down;
       }
       return but;
    }
    bool[] up()
    {
       bool[] but;
       foreach(i, button; buttons)
       {
           but[i] = button.up;
       }
       return but;
    }
    bool[] pressed()
    {
       bool[] but;
       foreach(i, button; buttons)
       {
           but[i] = button.pressed;
       }
       return but;
    }
    bool[] released()
    {
       bool[] but;
       foreach(i, button; buttons)
       {
           but[i] = button.released;
       }
       return but;
    }

    MouseButton opIndex(ubyte index)
    {
        return buttons[index];
    }
    MouseButton[] opSlice(ubyte index1, ubyte index2)
    {
        return buttons[index1..index2];
    }
    MouseButton[] opSlice()
    {
        return buttons[];
    }
}

class MousePosition
{
    protected
    {
        int[] prev;
        int[] curr;

        void update(int x, int y)
        {
            prev = curr.dup;
            curr = [x, y];
        }
    }

    this()
    {
        prev.length = 2;
        curr.length = 2;
    }

    /*void opAssign(Vector pos)
    {
        mouse.mouse.setPosition(cast(int)pos.x, cast(int)pos.y);
    }
    void opAssign(iVector pos)
    {
        mouse.mouse.setPosition(pos.x, pos.y);
    }*/

    iVector previous()
    {
        return iVector(prev[0], prev[1]);
    }
    iVector current()
    {
        return iVector(curr[0], curr[1]);
    }
    iVector delta()
    {
        return current - previous;
    }
}

class MouseWheel
{
    protected
    {
        int curr;
        int prev;

        void update(int w)
        {
            prev = curr;
            curr = w;
        }
    }

    /*void opAssign(int pos)
    {
        mouse.mouse.setWheel(pos);
    }
    void opAssign(float pos)
    {
        mouse.mouse.setWheel(cast(int)pos);
    }*/

    int previous()
    {
        return prev;
    }
    int current()
    {
        return curr;
    }
    int delta()
    {
        return curr - prev;
    }
}

class Mouse
{
    //protected
    //{
        SGCoreMouseCallbacks callbacks;
        void* mhandle;
    //}

    MouseButtonHandle button;
    MousePosition position;
    MouseWheel wheel;

    this()
    {
        callbacks.button = &cbMouseButton;
        callbacks.move = &cbMouseMove;
        callbacks.wheel = &cbMouseWheel;

        if(sgCoreMouseCreate !is null)
            sgCoreMouseCreate(&mhandle, window.handle());

        if(sgCoreMouseSetCallbacks !is null)
            sgCoreMouseSetCallbacks(mhandle, &callbacks);

        uint buttons;
        if(sgCoreMouseGetNumButtons !is null)
            sgCoreMouseGetNumButtons(mhandle, &buttons);
        button = new MouseButtonHandle(buttons);
        position = new MousePosition;
        wheel = new MouseWheel;
    }
    ~this()
    {
        if(sgCoreMouseDestroy !is null)
            sgCoreMouseDestroy(mhandle);
    }

    void* handle()
    {
        return mhandle;
    }
}
Mouse mouse;
