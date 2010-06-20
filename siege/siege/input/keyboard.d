module siege.input.keyboard;

private
{
    import siege.core.core;
    import siege.core.event;
    import siege.core.window;

    import siege.core.console;

    import siege.util.linkedlist;

    import siege.modules.input;

    extern(C)
    {
        void cbKeyboardKey(void* ckeyboard, uint key, bool down)
        {
            keyboard.updateKey(key, down);

            bool pressed = keyboard.keyPressed(key);

            foreach(client; clientList)
                if((client !is null) && client.active)
                {
                    client.evKeyboardKey(key);
                    if(pressed)
                        client.evKeyboardKeyPress(key);
                    else if(!down)
                        client.evKeyboardKeyRelease(key);
                    else
                        client.evKeyboardKeyRepeat(key);
                }
        }
        void cbKeyboardChar(void* ckeyboard, dchar chr, bool down)
        {
            keyboard.updateChar(chr, down);

            bool pressed = keyboard.characterPressed(chr);

            foreach(client; clientList)
                if((client !is null) && client.active)
                {
                    if(pressed)
                        client.evKeyboardCharPress(chr);
                    else if(down)
                        client.evKeyboardCharRepeat(chr);
                }
        }
    }
}

class Keyboard
{
    protected
    {
        bool[uint] prevKey;
        bool[uint] currKey;
        bool[dchar] prevChr;
        bool[dchar] currChr;

        void updateKey(uint key, bool down)
        {
            if(key in currKey)
                prevKey[key] = currKey[key];
            else
                prevKey[key] = !down;
            currKey[key] = down;
        }
        void updateChar(dchar chr, bool down)
        {
            if(chr in currChr)
                prevChr[chr] = currChr[chr];
            else
                prevChr[chr] = !down;
            currChr[chr] = down;
        }

        SGCoreKeyboardCallbacks callbacks;
        void* khandle;
    }

    this()
    {
        callbacks.key = &cbKeyboardKey;
        callbacks.chr = &cbKeyboardChar;

        if(sgCoreKeyboardCreate !is null)
            sgCoreKeyboardCreate(&khandle, window.handle);

        if(sgCoreKeyboardSetCallbacks !is null)
            sgCoreKeyboardSetCallbacks(khandle, &callbacks);
    }
    ~this()
    {
        if(sgCoreKeyboardDestroy !is null)
            sgCoreKeyboardDestroy(khandle);
    }

    bool key(uint key)
    {
        if(key in currKey)
            return currKey[key];
        return false;
    }
    bool keyPressed(uint key)
    {
        if(key in currKey)
        {
            if(key in prevKey)
                return !prevKey[key] && currKey[key];
            return currKey[key];
        }
        return false;
    }
    bool keyReleased(uint key)
    {
        if(key in prevKey)
        {
            if(key in currKey)
                return prevKey[key] && !currKey[key];
            return prevKey[key];
        }
        return false;
    }
    bool character(dchar chr)
    {
        if(chr in currChr)
            return currChr[chr];
        return false;
    }
    bool characterPressed(dchar chr)
    {
        if(chr in currChr)
        {
            if(chr in prevChr)
                return !prevChr[chr] && currChr[chr];
            return currChr[chr];
        }
        return false;
    }
    bool characterReleased(dchar chr)
    {
        if(chr in prevChr)
        {
            if(chr in currChr)
                return prevChr[chr] && !currChr[chr];
            return prevChr[chr];
        }
        return false;
    }

    void* handle()
    {
        return khandle;
    }
}
Keyboard keyboard;
