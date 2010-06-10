/**
    \brief The ingame console
    \todo to be done
*/
module siege.core.console;

private
{
    import std.string;
    import std.math;
    import std.utf;

    import siege.core.event;

    import siege.input.keyboard;

    import siege.graphics.font;

    import siege.util.color;
    import siege.util.vector;
    import siege.util.linkedlist;
    import siege.util.misc;

    //for now
    import siege.graphics.draw;
    import siege.modules.input;
}


struct CharStyle
{
    Color fgcolor;
    Color bgcolor;

    bool bold;
    bool under;
    bool italic;
}

class Console: EventClient
{
    private
    {
        bool _opened = false;
        bool _insert = true;

        uint cols;
        uint rows;
        char[][] buffer;
        char[][] history;
    }

    CharStyle defstyle;

    Font font;
    uint toggleKey = SG_KEYBOARD_KEY_F1;
    /**
        Argument: Input string
        Returns: What to write to console
    */
    char[] delegate(char[]) command = null;
    /**
        Argument: Input string
        Returns: List of possible commands
    */
    char[][] delegate(char[]) autocomplete = null;

    this(iVector size, Font font = null)
    {
        cols = size.x;
        rows = size.y;
        deactivate();
    }
    this(uint width, uint height, Font font = null)
    {
        this(iVector(width, height), font);
    }
    this()
    {
        this(iVector(79, 20), null);
    }

    void open()
    {
        _opened = true;
    }

    void close()
    {
        _opened = false;
    }

    void toggle()
    {
        _opened = !_opened;
    }

    bool opened()
    {
        return _opened;
    }
    bool closed()
    {
        return !_opened;
    }
    void evKeyboardKeyPressed(uint key)
    {
        if(key == toggleKey)
        {
            toggle();
        }
        if(!opened())
            return;

        if(key == SG_KEYBOARD_KEY_ENTER)
        {

        }
        else if(key == SG_KEYBOARD_KEY_TAB)
        {

        }
        else if(key == SG_KEYBOARD_KEY_BACKSPACE)
        {

        }
        else if(key == SG_KEYBOARD_KEY_DELETE)
        {

        }
        else if(key == SG_KEYBOARD_KEY_RIGHT)
        {

        }
        else if(key == SG_KEYBOARD_KEY_LEFT)
        {

        }
        else if(key == SG_KEYBOARD_KEY_HOME)
        {

        }
        else if(key == SG_KEYBOARD_KEY_END)
        {

        }
        else if(key == SG_KEYBOARD_KEY_UP)
        {

        }
        else if(key == SG_KEYBOARD_KEY_DOWN)
        {

        }
        else if(key == SG_KEYBOARD_KEY_PAGEUP)
        {

        }
        else if(key == SG_KEYBOARD_KEY_PAGEDOWN)
        {

        }
        else if(key == SG_KEYBOARD_KEY_INSERT)
        {
            _insert = !_insert;
        }
    }
    void evKeyboardCharPressed(dchar chr)
    {
        if(!_opened)
            return;

        addInput(chr);
    }

    void addInput(dchar chr)
    {

    }

    void newline()
    {

    }
    void clear()
    {

    }
    void reset()
    {

    }
    uint printT(char[] text)
    {
        return text.length;
    }
    uint print(...)
    {
        return printT(font.strFormatX(_arguments, _argptr));
    }

    void draw()
    {

    }
    void evDraw()
    {
        if(_opened)
            draw();
    }

    char[] linewrap(char[] text)
    {
        return text;
    }

    static dchar[] cmdInsert(dchar[] str, uint index, dchar sub)
    {
        if(index == str.length)
            return str ~ sub;

        return str[0..index] ~ sub ~ str[index..$];
    }
    static dchar[] cmdReplace(dchar[] str, uint index, dchar sub)
    {
        if(index == str.length)
            return str ~ sub;

        str[index] = sub;
        return str;
    }
}
Console console;
