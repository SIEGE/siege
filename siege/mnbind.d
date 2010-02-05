module mnbind;

pragma(lib, "monster.lib");

import siege.siege;
import monster.monster;
import monster.modules.console;

import std.stdio;

import actors;

char[] wbuffer;
void doWrite(bool space)
{
    AIndex[] args = stack.popAArray();

    if(space)
        wbuffer ~= " ";

    foreach(AIndex ind; args)

    wbuffer ~= std.utf.toUTF8(arrays.getRef(ind).carr);

    console.printT(wbuffer);
    wbuffer = "";
}
void doLine()
{
    writefln();
    console.printT("\n");
}

union ObjPtr
{
    Object obj;
    ulong ptr;
}

ulong box_init(float angle, float y, float x)
{
    ObjPtr p;
    p.obj = new Box(Vector(x, y), angle);

    return p.ptr;
}
void box_uninit(ulong id)
{
    ObjPtr p;
    p.ptr = id;

    Box b = cast(Box)p.obj;
    delete b;
}

ulong metalbox_init(float angle, float y, float x)
{
    ObjPtr p;
    p.obj = new MetalBox(Vector(x, y), angle);

    return p.ptr;
}
void metalbox_uninit(ulong id)
{
    ObjPtr p;
    p.ptr = id;

    MetalBox b = cast(MetalBox)p.obj;
    delete b;
}

char[][][char[]] abbrev(char[][] list)
{
    char[][][char[]] abbr;
    abbr[""] = list;

    char[] name;

    foreach(item; list)
    {
        foreach(c; item)
        {
            name ~= c;

            if(name in abbr)
                abbr[name.dup] ~= item;
            else
                abbr[name.dup] = [item];
        }
        name.length = 0;
    }

    /*foreach(key, item; abbr)
    {
        writefln("%s => %s", key, item);
    }*/
    //writefln("ABBREV ", abbr);
    return abbr;
}

class MonsterVM
{
    char[][][char[]] abbrevs;

    MonsterClass mc;

    monster.modules.console.Console cn;
    this()
    {
        char[][] list = ["Box", "MetalBox", "write", "writeln", "writes", "writelns", "print", "mousex", "mousey", "exit"];
        abbrevs = abbrev(list);

        mc = vm.loadString(`
            module demo;

            native write(char[][] args...);
            native writeln(char[][] args...);

            native writes(char[][] args...);
            native writelns(char[][] args...);

            native print(char[][] args...);

            native ulong box_init(float x, float y, float angle);
            native box_uninit(ulong id);

            native ulong metalbox_init(float x, float y, float angle);
            native metalbox_uninit(ulong id);

            native exit();

            native float mousex();
            native float mousey();
        `, "demo");

        //mc.bind("write",    { doWrite(false);             });
        mc.bind("writeln",  { doWrite(false); /*doLine();*/ });
        //mc.bind("writes",   { doWrite(true);              });
        mc.bind("writelns", { doWrite(true);  /*doLine();*/ });

        // Print is just another name for writelns
        mc.bind("print", { doWrite(true);  /*doLine();*/ });

        mc.bind("box_init", { stack.pushUlong(box_init(stack.popFloat(), stack.popFloat(), stack.popFloat())); });
        mc.bind("box_uninit", { box_uninit(stack.popUlong()); });
        mc.bind("metalbox_init", { stack.pushUlong(metalbox_init(stack.popFloat(), stack.popFloat(), stack.popFloat())); });
        mc.bind("metalbox_uninit", { metalbox_uninit(stack.popUlong()); });

        mc.bind("exit", { game.exit(); });

        mc.bind("mousex", { stack.pushFloat(mouse.position.current.x); });
        mc.bind("mousey", { stack.pushFloat(mouse.position.current.y); });

        vm.loadString(`
            class Box;

            import demo;

            ulong id;

            float x;
            float y;
            float angle = 0;

            new
            {
                if(x == float.nan || x == -float.nan)
                    x = mousex();
                if(y == float.nan || y == -float.nan)
                    y = mousey();

                id = box_init(x, y, angle);
            }

            /*delete
            {
                box_uninit(id);
            }*/
            `);

        vm.loadString(`
            class MetalBox;

            import demo;

            ulong id;

            float x;
            float y;
            float angle = 0;

            new
            {
                if(x == float.nan || x == -float.nan)
                    x = mousex();
                if(y == float.nan || y == -float.nan)
                    y = mousey();

                id = metalbox_init(x, y, angle);
            }

            /*delete
            {
                metalbox_uninit(id);
            }*/
            `);

        cn = new monster.modules.console.Console();
        cn.allowVar = true;
        cn.addImports("demo", "Box", "MetalBox");

        // a hack
        //cn.input("import demo");
        //cn.output();
    }

    char[] command(char[] input)
    {
        char[] ret = ">>> " ~ input ~ "\n";

        try
        {
            cn.input(input);
        }
        catch(Exception e)
        {
            writefln("Unable to execute: %s\n", e.toString());
        }

        char[] output = cn.output();
        if(output == "")
            return ret;
        return ret ~ output;
    }

    char[][] autocomplete(char[] input)
    {
        if(input.length == 0)
            return null;

        char[][] split = std.string.split(input);
        char[] join = std.string.join(split[0..$-1], " ");
        char[] ident = split[$-1];

        char[][] ret;
        if(ident in abbrevs)
        {
            if(abbrevs[ident].length == 1)
                return [std.string.join(split[0..$-1] ~ abbrevs[ident][0], " ")];

            return abbrevs[ident];
        }

        return null;
        //if(box.find() == "Box")
    }
}

