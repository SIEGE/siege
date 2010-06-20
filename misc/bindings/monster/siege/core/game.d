module monster.siege.core.core;

import monster.monster;
import siege.all;

import std.utf;
import std.string;
import std.c.stdarg;

void readf(...)
{
    void* val;
    void** dptr = cast(void**)_argptr;
    foreach_reverse(i, arg; _arguments)
    {
        if(arg == typeid(bool*))
            *cast(bool*)dptr[i] = stack.popBool();
        //else if(arg == typeid(short*))
        //    *cast(short*)dptr[i] = stack.popShort();
        //else if(arg == typeid(ushort*))
        //    *cast(short*)dptr[i] = stack.popUshort();
        else if(arg == typeid(int*))
            *cast(int*)dptr[i] = stack.popInt();
        else if(arg == typeid(uint*))
            *cast(uint*)dptr[i] = stack.popUint();
        else if(arg == typeid(long*))
            *cast(long*)dptr[i] = stack.popLong();
        else if(arg == typeid(ulong*))
            *cast(ulong*)dptr[i] = stack.popUlong();
        else if(arg == typeid(float*))
            *cast(float*)dptr[i] = stack.popFloat();
        else if(arg == typeid(double*))
            *cast(double*)dptr[i] = stack.popDouble();
        else if(arg == typeid(char[]*))
            *cast(char[]*)dptr[i] = toUTF8(stack.popString());
        else if(arg == typeid(wchar[]*))
            *cast(wchar[]*)dptr[i] = toUTF16(stack.popString());
        else if(arg == typeid(dchar[]*))
            *cast(dchar[]*)dptr[i] = stack.popString();
    }
}

class MNSiegeCoreGame
{
    MonsterClass mc;
    this()
    {
        mc = vm.load("monster.siege.core.game");
        mc.bind("loadModules", &loadModules);
        mc.bind("loadModule", &loadModule);
        mc.bind("initSiege", &init);
        mc.bind("deinitSiege", &deinit);
        mc.bind("run", &run);
        //mc.bind("loop", &loopC);
        mc.bind("loop", &loop);
        mc.bind("stop", &stop);
        mc.bind("stopEvent", &stopEvent);
    }

    void loadModules()
    {
        char[][] names;
        AIndex[] args = stack.popAArray();
        foreach(ind; args)
            names ~= toUTF8(arrays.getRef(ind).carr);
        game.loadModules(names);
    }
    void loadModule()
    {
        game.loadModule(toUTF8(stack.popString()));
    }
    void init()
    {
        uint flags = stack.popUint();
        uint bpp = stack.popUint();
        uint height = stack.popUint();
        uint width = stack.popUint();
        stack.pushBool(game.init(width, height, bpp, flags));
    }
    void deinit()
    {
        game.deinit();
    }
    void run()
    {
        stack.pushInt(game.run());
    }
    //void bool loopC(out int code);
    void loop()
    {
        stack.pushBool(game.loop());
    }
    void stop()
    {
        game.stop(stack.popInt());
    }
    void stopEvent()
    {
        game.stopEvent();
    }
}
