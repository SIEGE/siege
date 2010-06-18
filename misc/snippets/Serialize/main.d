// todo:
// -ignore pointers to null
// -handle void*
import std.stdio;
import std.stream;
import std.string;
import std.c.string;
import std.zlib;

class Class
{
    int a;
    float f;
    Struct* pstr;
    Struct str;
    char[] string;
    char* cstring;

    char[] toString()
    {
        char[] output;
            output ~= format("a       = %s\n", a);
            output ~= format("f       = %s\n", f);
            output ~= format("pstr %.8X\n", pstr);
            output ~= format("    pstr.a = %s\n", pstr.a);
            output ~= format("    pstr.a = %s\n", pstr.f);
            output ~= format("str\n");
            output ~= format("     str.a = %s\n", str.a);
            output ~= format("     str.a = %s\n", str.f);
            output ~= format("string  = %s\n", string);
            output ~= format("cstring = %s\n", std.string.toString(cstring));
        return output;
    }
}

struct Struct
{
    int a;
    float f;
}

int main(char[][] args)
{
    Class c = new Class;
    c.a = 5;
    c.f = 7.5;
    c.pstr = new Struct;
    c.pstr.a = 3;
    c.pstr.f = 2.25;
    c.str.a = 17;
    c.str.f = 102.75;
    c.string = "D hi!";
    c.cstring = "C hi!";

    serialize("output.txt", c);
    writefln("Class to be serialized:");
    writefln("--------------------");
    writefln(c);
    Class n = new Class;
    unserialize("output.txt", n);
    writefln("Read back file:");
    writefln("--------------------");
    writefln(n);

    return 0;
}

// output:
/*
Header:
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+=========+
| D   S   E   R | 0 |VMAJOR |VMINOR |VPATCH |LF |    DATALEN    | Data... |
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+=========+
Data:
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+======+---+---+---+---+
|              ID               | FLAGS |    LENGTH     | Data |     CRC32     |
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+======+---+---+---+---+
*/
enum Flags: ushort
{
    Compressed = 0x01,
}

void serialize(T)(char[] fname, T item)
{
    File file = new File(fname, FileMode.OutNew);
    serialize(file, item);
    file.close();
}

void serialize(T)(File file, T item)
{
    void[][ulong] data;
    data[0] = serialize(data, item);

    file.write(cast(ubyte[])"DSER\0");
    file.write(cast(ubyte[])cast(void[])cast(ushort[])[0, 1, 0]);
    file.write(cast(ubyte[])"\n");
    file.write(cast(uint)data.length);

    ushort flags = Flags.Compressed;
    foreach(key, value; data)
    {
        void[] compr = value;
        if(flags & Flags.Compressed)
            compr = compress(value);
        file.write(cast(ulong)key);
        file.write(cast(ushort)flags);
        file.write(cast(uint)compr.length);
        file.writeExact(compr.ptr, compr.length);
        file.write(crc32(0, value));
    }
}

// class
// char* (special case)
// foo*
// int, float...
void[] serialize(T)(inout void[][ulong] data, T item)
{
    void[] array;
    static if(is(T == class))
    {
        array = cast(void[])[cast(ulong)cast(void*)item];
        if(!((cast(size_t)cast(void*)item) in data))
            foreach(t; item.tupleof)
                data[cast(size_t)cast(void*)item] ~= serialize(data, t);
    }
    else static if(is(T == struct))
    {
        foreach(t; item.tupleof)
            array ~= serialize(data, t);
    }
    else static if(is(T == char*)) // special handling
    {
        uint len = strlen(item);
        array = (item[0..len] ~ '\0').dup;
    }
    else static if(IsPtr!(T))
    {
        array = cast(void[])[cast(ulong)item];
        if(!((cast(size_t)item) in data)) // 0 is always in data, so null pointers are never followed
            data[cast(size_t)item] = serialize(data, *item);
    }
    else static if(IsArray!(T))
    {
        array = cast(void[])cast(uint[])[item.length];
        array ~= item.dup;
    }
    else
    {
        array = cast(void[])[item];
    }
    return array;
}

void unserialize(T)(char[] fname, out T item)
{
    File file = new File(fname, FileMode.In);
    unserialize(file, item);
    file.close();
}

void unserialize(T)(File file, out T item)
{
    ubyte tmp;
    ubyte[4] header;
    ushort[3] vinfo;
    uint datalen;
    file.read(header);
    if(header != cast(ubyte[])"DSER")
        throw new Exception("Unknown file format or malformed header");
    file.read(tmp); // discard \0
    file.read(vinfo[0]);
    file.read(vinfo[1]);
    file.read(vinfo[2]);
    file.read(tmp); // discard \n
    file.read(datalen);

    ulong id;
    ushort flags;// = Flags.Compressed;
    uint length;
    uint crc;
    void[][ulong] data;
    for(uint i = 0; i < datalen; i++)
    {
        file.read(id);
        data[id] = [];
        file.read(flags);
        file.read(length);
        data[id].length = length;
        file.readExact(data[id].ptr, length);
        file.read(crc);
        if(flags & Flags.Compressed)
            data[id] = uncompress(data[id]);
        if(crc32(0, data[id]) != crc)
            throw new Exception("Bad file data - checksum mismatch");
    }

    unserialize(data, data[0], item);
}

void unserialize(T)(inout void[][ulong] data, void[] array, out T item)
{
    //void[] array;
    static if(is(T == class))
    {
        item = new T;
        ulong ptr = *cast(ulong*)array[0..ulong.sizeof];
        //array = cast(void[])[cast(size_t)cast(void*)item];
        if(ptr in data)
        {
            foreach(i, _; item.tupleof)
            {
                uint size = item.tupleof[i].sizeof;
                static if(is(typeof(item.tupleof[i]) == char*))
                    size = strlen(cast(char*)data[ptr][0..$].ptr) + 1;
                else static if(IsPtr!(typeof(item.tupleof[i])))
                    size = ulong.sizeof;
                else static if(IsArray!(typeof(item.tupleof[i])))
                {
                    uint l = BaseType!(typeof(item.tupleof[i])).sizeof;
                    static if(IsPtr!(BaseType!(typeof(item.tupleof[i]))))
                        l = ulong.sizeof;
                    size = l * (*cast(uint*)data[ptr][0..uint.sizeof].ptr) + uint.sizeof;
                }
                unserialize(data, data[ptr][0..size], item.tupleof[i]);
                data[ptr] = data[ptr][size..$];
            }
            data.remove(ptr);
        }
    }
    else static if(is(T == struct))
    {
        foreach(i, _; item.tupleof)
        {
            uint size = item.tupleof[i].sizeof;
            static if(IsPtr!(typeof(item.tupleof[i])))
                size = ulong.sizeof;
            unserialize(data, array[0..item.tupleof[i].sizeof], item.tupleof[i]);
            array = array[item.tupleof[i].sizeof..$];
        }
    }
    else static if(is(T == char*)) // special handling
    {
        uint len;
        for(uint i = 0; (cast(char[])array)[i] != '\0'; i++)
            len = i + 1;

        item = cast(char*)array[0..len].dup.ptr;
    }
    else static if(IsPtr!(T))
    {
        item = new BaseType!(T);
        ulong ptr = *cast(ulong*)array[0..ulong.sizeof];
        //array = cast(void[])[cast(size_t)item];
        if(ptr in data)
        {
            unserialize(data, data[ptr], *item);
            data.remove(ptr);
        }
    }
    else static if(IsArray!(T))
    {
        uint len = *cast(uint*)array[0..uint.sizeof].ptr;
        array = array[uint.sizeof..$];
        item = (cast(T)array)[0..len].dup;
    }
    else
    {
        item = *cast(T*)array[0..T.sizeof].ptr;
    }
    //return array;
}

template PtrLevel(T)
{
    static if(IsPtr!(T))
        const PtrLevel = 1 + PtrLevel!(BaseType!(T));
    else
        const PtrLevel = 0;
}

template IsPtr(T)
{
    const bool IsPtr = is(BaseType!(T)* == T);
}

template IsArray(T)
{
    const bool IsArray = is(BaseType!(T)[]: T);
}

template BaseType(T: T[])
{
    alias T BaseType;
}
template BaseType(T: T*)
{
    alias T BaseType;
}
template BaseType(alias A)
{
    alias BaseType!(typeof(A)) BaseType;
}
