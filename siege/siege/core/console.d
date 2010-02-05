module siege.core.console;

private
{
    //import std.stdio;
    import std.format;
    import std.string;
    import std.math;
    import std.utf;

    import siege.core.event;

    import siege.input.keyboard;

    import siege.graphics.font;

    import siege.util.color;
    import siege.util.queue;
    import siege.util.vector;
    import siege.util.linkedlist;
    import siege.util.misc;

    //for now
    import derelict.opengl.glfw;
    import siege.core.window;
    import siege.graphics.draw;


}

enum Key
{
    F1 = GLFW_KEY_F1,
    LSHIFT = GLFW_KEY_LSHIFT,
    RSHIFT = GLFW_KEY_RSHIFT,
    TAB = GLFW_KEY_TAB,
    ENTER = GLFW_KEY_ENTER,
    RIGHT = GLFW_KEY_RIGHT,
    LEFT = GLFW_KEY_LEFT,
    UP = GLFW_KEY_UP,
    DOWN = GLFW_KEY_DOWN,
    PAGEDOWN = GLFW_KEY_PAGEDOWN,
    PAGEUP = GLFW_KEY_PAGEUP,
    BACKSPACE = GLFW_KEY_BACKSPACE,
    DEL = GLFW_KEY_DEL,
    HOME = GLFW_KEY_HOME,
    END = GLFW_KEY_END,
    INSERT = GLFW_KEY_INSERT,
}

/*
    column
    wrap
    insert
    replaceSlice
*/

class Console: EventClient
{
    private
    {
        bool _opened = false;
        bool _insert = true;

        LinkedList!(dchar[]) cmdHistory = null;
        uint cmdHistoryLength = 10; /// TODO
        LinkedNode!(dchar[]) *cmdPtr;
        uint cmdPos;

        iVector curPos = iVector(0, 0);
        real curFreq = 1;
        bool curDisplay = false;
        ulong curTime = 0;

        dchar[][] buffer;
        dchar[] eline;

        iVector _size = iVector(0, 0);
    }

    Font font;
    uint tabsize = 4;
    uint toggleKey = Key.F1; // default
    Color background = Color(0.125, 0.25, 0.5, 1);
    Color border = Color(1.0, 0.5, 0.0, 0.75);
    Color text = Color(1.0, 1.0, 1.0, 1.0);
    //char[] prompt = ">>>";
    //char[] promptline = "...";

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
	    if(font is null)
		    font = new Font("Data/Fonts/DejaVuLGCSansMono.ttf", "Data/Fonts/DejaVuLGCSansMono-Bold.ttf", "Data/Fonts/DejaVuLGCSansMono-Oblique.ttf", "Data/Fonts/DejaVuLGCSansMono-BoldOblique.ttf", 10, 256);

	    if(size.x == 0)
		    size.x = 79;
	    if(size.y == 0)
		    size.y = 20;

        _size = size;
        this.font = font;

        buffer = new dchar[][](size.y, size.x);
        eline = new dchar[](size.x);
        eline[] = ' ';

        reset();
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

        if(key == Key.ENTER)
        {
            // soft enter -- add a newline to input
            if(keyboard.key(Key.LSHIFT) || keyboard.key(Key.RSHIFT))
            {
                //addInput('\n'); // enter now always inserts
                cmdPtr.item = cmdInsert(cmdPtr.item, cmdPos, '\n');
            }
            else
            {
                if(command !is null)
                    printT(command(toUTF8(cmdPtr.item)));
                else
                    printT(toUTF8(cmdPtr.item) ~ "\n");

                if(cmdHistory.lastNode.item != cmdPtr.item)
                {
                    if(cmdHistory.lastNode.item == "")
                        cmdHistory.lastNode.item = cmdPtr.item;
                    else
                        cmdHistory.append(cmdPtr.item.dup);
                }

                //printT(prompt);
                cmdHistory.append("");
                cmdPtr = cmdHistory.lastNode;
                cmdPos = 0;
            }
        }
        else if(key == Key.TAB)
        {
            if(autocomplete !is null)
            {
                char[][] complete = autocomplete(toUTF8(cmdPtr.item));

                if(complete.length == 1)
                {
                    cmdPtr.item = toUTF32(complete[0]);
                    cmdPos = cmdPtr.item.length;
                }
                /// TODO: do something (else) with the list - like display a tooltip
                else
                    print("%s", complete);
            }
            else
            {
                char[] str = expandtabs("\t", tabsize);

                cmdPtr.item ~= toUTF32(str);
                printT(str);
            }
        }
        else if(key == Key.BACKSPACE)
        {
            if(cmdPos > 0)
            {
                cmdPtr.item = cmdPtr.item[0..cmdPos-1] ~ cmdPtr.item[cmdPos..$];
                cmdPos--;
            }
        }
        else if(key == Key.DEL)
        {
            if(cmdPos + 1 < cmdPtr.item.length)
                cmdPtr.item = cmdPtr.item[0..cmdPos] ~ cmdPtr.item[cmdPos+1..$];
            else// if(cmdPos == cmdPtr.item.length - 1)
                cmdPtr.item = cmdPtr.item[0..cmdPos];
        }
        else if(key == Key.RIGHT)
        {
            if(cmdPos < cmdPtr.item.length)
                cmdPos++;
        }
        else if(key == Key.LEFT)
        {
            if(cmdPos > 0)
                cmdPos--;
        }
        else if(key == Key.HOME)
        {
            cmdPos = 0;
        }
        else if(key == Key.END)
        {
            cmdPos = cmdPtr.item.length;
        }
        else if(key == Key.UP)
        {
            if(cmdPtr.previous !is null)
            {
                cmdPtr = cmdPtr.previous;
                cmdPos = cmdPtr.item.length;
            }
        }
        else if(key == Key.DOWN)
        {
            if(cmdPtr.next !is null)
            {
                cmdPtr = cmdPtr.next;
                cmdPos = cmdPtr.item.length;
            }
            else if(cmdPtr.item != "")
            {
                cmdHistory.append("");
                cmdPtr = cmdHistory.lastNode;
                cmdPos = 0;
            }
        }
        else if(key == Key.PAGEUP)
        {
            cmdPtr = cmdHistory.firstNode;
            cmdPos = cmdPtr.item.length;
        }
        else if(key == Key.PAGEDOWN)
        {
            cmdPtr = cmdHistory.lastNode;
            cmdPos = cmdPtr.item.length;
        }
        else if(key == Key.INSERT)
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
        /*if(cmdPos == cmdPtr.item.length)
            cmdPtr.item ~= chr;
        else */if(_insert)
            cmdPtr.item = cmdInsert(cmdPtr.item, cmdPos, chr);
        else
            cmdPtr.item = cmdReplace(cmdPtr.item, cmdPos, chr);
        cmdPos++;
    }

    void newline()
    {
        if(curPos.y == _size.y - 1)
            buffer = buffer[1..$] ~ eline.dup;
        else
            curPos.y++;
        curPos.x = 0;
    }
    void clear()
    {
        buffer.length = _size.y;
        foreach(inout line; buffer)
        {
            line = eline.dup;
        }
    }
    void reset()
    {
        clear();

        cmdHistory = new LinkedList!(dchar[]);
        cmdHistory.append("");
        cmdPtr = cmdHistory.firstNode;
        cmdPos = 0;

        curPos = iVector(0, 0);
        curFreq = 1;
    }
    uint printT(char[] text)
    {
        alias curPos cp;
        //iVector cp = curPos;

        //text = (toUTF8(buffer[cp.y][0..cp.x]) ~ text).replace(" ", "\U00000091");
        //text = wrap(/*toUTF8(buffer[cp.y][0..cp.x]) ~ text*/text, _size.x, null, null, tabsize).replace("\U00000091", " ");
        text = linewrap(toUTF8(buffer[cp.y][0..cp.x]) ~ text);

        char[][] lines = splitlines(text);
        //if(lines.length > _size.y - cp.y)
            /*for(uint i = lines.length - _size.y + cp.y; i > 0; i--)
            {
                printf("NL\n");
                newline();
            }*/

        foreach(line; lines)
        {
            buffer[cp.y] = toUTF32(line);
            newline();
        }

        /*foreach(i, inout buf; buffer[cp.y..cp.y+lines.length])
        {
            buf = eline.dup;
            buf[0..lines[i].length] = toUTF32(lines[i]);
            //cp.x = 0;
        }*/

        //curPos.x = cp.x;
    	return text.length;
    }
    uint print(...)
    {
        return printT(font.strFormatX(_arguments, _argptr));
    }

    void draw()
    {
        ulong ctime = cast(ulong)floor(time() * curFreq * 2);
        if(curTime != ctime)
        {
            curDisplay = !curDisplay;
            curTime = ctime;
        }

        char[][] lines = new char[][](buffer.length);

        foreach(i, inout line; lines)
        {
            line = toUTF8(buffer[i]);
        }
        char[] joined = join(lines, "\n");


        char[] cmdw;
        cmdw = toUTF8(cmdPtr.item).replace(" ", "\U00000091").replace("\n", "\U00000092");
        cmdw = (cmdPtr.item != "") ? wrap(cmdw, _size.x, null, null, tabsize).replace("\n", "").replace("\U00000091", " ").replace("\U00000092", "\n") : " ";

        dchar[] cmd = toUTF32(cmdw.dup);
        char[] cmdwa;
        if(curDisplay)
        {
            dchar chr;
            if(!_insert)
                chr = '\U00002588'; // solid block
            else
                chr = '\U00002502'; // straight line

            int pptr = -1;
            foreach(i, inout c; cmd)
            {
                if(c != '\n')
                {
                    if(pptr != -2)
                        pptr++;
                }
                else
                    continue;
                c = ' ';

                if(pptr == cmdPos) // found the position
                {
                    c = chr;
                    pptr = -2;
                }
            }
            if(pptr != -2) // didn't find the position - it is in front of the whole string
                cmd ~= chr;
            cmdwa = toUTF8(cmd);
        }

        font.style = 0;
        Vector bsize = font.strSizeT(joined) + 8;
        Vector isize = font.strSizeT(cmdw) + 8;

        siege.graphics.draw.draw.quad(Vector(0, 0), bsize + Vector(0, isize.y), background, true);

        siege.graphics.draw.draw.color(text);
        font.printCenteredT(bsize / 2, joined);

        siege.graphics.draw.draw.quad(Vector(0, 0), bsize, border, false);

        //siege.graphics.draw.draw.quad(Vector(0, bsize.y), bsize + Vector(0, isize.y), background, true);

        if(curDisplay)
        {
            siege.graphics.draw.draw.color(border);
            if(_insert)
            {
                font.printT(Vector(-font.strSizeT("X").x / 2, bsize.y + isize.y / 2), cmdwa);
            }
            else
            {
                //siege.graphics.draw.draw.color(text); // called above

                /*font.printT(Vector(0, bsize.y) + Vector(0, isize.y) / 2, cmdwa);

                dchar[] uw = toUTF32(cmdwa);
                uw[cmdPos] = toUTF32(cmdw)[cmdPos];
                cmdwa = toUTF8(uw);

                siege.graphics.draw.draw.color(background);*/
                font.printT(Vector(0, bsize.y + isize.y / 2), cmdwa);
            }
        }
        siege.graphics.draw.draw.color(text);
        font.printT(Vector(0, bsize.y + isize.y / 2), cmdw);

        siege.graphics.draw.draw.quad(Vector(0, bsize.y), bsize + Vector(0, isize.y), border, false);
    }
    void evDraw()
    {
        if(_opened)
            draw();
    }

    char[] linewrap(char[] text)
    {
        text = expandtabs(text, tabsize);
        char[][] lines = splitlines(text);

        for(uint i = 0; i < lines.length; i++)
        {
            lines[i] = stripr(lines[i]);
            if(lines[i].length > _size.x)
            {
                if(i == lines.length - 1)
                    lines = lines[0..i] ~ lines[i][0.._size.x] ~ lines[i][_size.x..$];
                else
                    lines = lines[0..i] ~ lines[i][0.._size.x] ~ lines[i][_size.x..$] ~ lines[i+1..$];
            }
            else if(lines[i].length < _size.x)
                lines[i] ~= repeat(" ", _size.x - lines[i].length);
        }

        /*if(lines.length > _size.y)
            lines = lines[lines.length-_size.y..$];
        else if(lines.length < _size.y)
        {
            for(uint i = _size.y - lines.length; i > 0; i--)
            {
                lines ~= toUTF8(eline);
            }
        }*/

        return join(lines, "\n");
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
