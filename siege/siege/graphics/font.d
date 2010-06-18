module siege.graphics.font;

private
{
    import siege.modules.fonts;

    import std.string;
    import std.format;
    import std.c.stdarg;
    import std.utf;

    import siege.graphics.texture;
    import siege.util.vector;
    import siege.util.misc;
    import siege.util.stack;
}

struct CharInfo
{
    Texture texture;
    Vector size;
    Vector dsize;
    Vector preTranslate;
    Vector postTranslate;
}

enum FontStyle: uint
{
    None        = 0b0,
    Bold        = 0b10,
    Italic      = 0b100,
    Underlined  = 0b1000,
    Strikeout   = 0b10000
}

class FontFace
{
    protected
    {
        void* face;

        Font parent;
        uint preload;

        char[] fname;
    }

    CharInfo[] chars;
    CharInfo[dchar] cache;

    this(Font parent, char[] fname, uint preload = 256)
    {
        this.parent = parent;
        this.fname = fname;
        this.preload = preload;

        uint ret;
        if(sgFontsFaceCreate !is null)
            ret = sgFontsFaceCreate(&face, toStringz(fname));
        if(ret != 0)
            throw new Exception("Cannot create font " ~ fname);

        if(sgFontsFaceSetHeight !is null)
            sgFontsFaceSetHeight(face, parent.fheight);

        chars = new CharInfo[](preload);

        dchar[] prestr = new dchar[](preload);
        foreach(i, inout c; prestr)
            c = i;

        load(prestr, true);
    }

    ~this()
    {
        foreach(c; chars)
            delete c.texture;
        foreach(c; cache)
            delete c.texture;

        if(sgFontsFaceDestroy !is null)
            sgFontsFaceDestroy(face);
    }

    CharInfo[] getChars(dchar[] str)
    {
        if(!load(str, false))
            return null;

        CharInfo[] ci;

        ci = new CharInfo[](str.length); // segfault (sometimes) // I think I've fixed it...
        foreach(i, c; str)
        {
            if(c < preload)
                ci[i] = chars[c];
            //if(c in cache)
            else
                ci[i] = cache[c];
        }
        return ci;
    }

    char[] filename()
    {
        return fname;
    }

    dchar[] toLoad(dchar[] input)
    {
        dchar[] output;
        foreach(c; input)
        {
            if(c < preload)
                continue;
            if(c in cache)
                continue;
            output ~= c;
        }
        return output;
    }

    bool load(dchar[] charset, bool force)
    {
        if(!force)
            charset = toLoad(charset);
        if(charset.length == 0)
            return true;

        if(sgFontsCharsCreate is null)
            return false;

        uint datawidth;
        uint dataheight;
        float width;
        float height;
        float prex;
        float prey;
        float postx;
        float posty;
        void* cdata;
        uint ret;

        ubyte[] rgba;

        foreach(i, c; charset)
        {
            ret |= sgFontsCharsCreate(face, &c, 1, &width, &height, &prex, &prey, &postx, &posty, &datawidth, &dataheight, &cdata);
            if(ret != 0)
                return false;

            rgba = toRGBA(cast(ubyte[])cdata[0..datawidth*dataheight]);
            if(sgFontsCharsFreeData !is null)
                sgFontsCharsFreeData(cdata);

            Texture tex = new Texture(datawidth, dataheight, 32, rgba);
            if(c < preload)
                chars[c] = CharInfo(tex,
                                Vector(width, height),
                                Vector(datawidth, dataheight),
                                Vector(prex, prey),
                                Vector(postx, posty));
            else
                cache[c] = CharInfo(tex,
                                Vector(width, height),
                                Vector(datawidth, dataheight),
                                Vector(prex, prey),
                                Vector(postx, posty));
        }

        return true;
    }

    /*bool load(dchar[] charset, bool force)
    {
        if(!force)
            charset = toLoad(charset);

        SiegeModuleH mid;

        uint[] datawidth = new uint[](charset.length);
        uint[] dataheight = new uint[](charset.length);
        float[] width = new float[](charset.length);
        float[] height = new float[](charset.length);
        float[] prex = new float[](charset.length);
        float[] prey = new float[](charset.length);
        float[] postx = new float[](charset.length);
        float[] posty = new float[](charset.length);
        void*[] cdata = new void*[](charset.length);
        uint ret;

        if(sgFontsCharsCreate !is null)
            ret = sgFontsCharsCreate(cast(void**)&mid, face, charset.ptr, charset.length, width.ptr, height.ptr, prex.ptr, prey.ptr, postx.ptr, posty.ptr, datawidth.ptr, dataheight.ptr, cdata.ptr);
        else
            return false;

        // has to be done this way or we run out of memory
        ubyte[][] rgba = new ubyte[][](charset.length);
        foreach(i, c; charset)
        {
            rgba[i] = toRGBA(cast(ubyte[])cdata[i][0..datawidth[i]*dataheight[i]]);
            if(mid.sgModuleFree !is null)
                mid.sgModuleFree(cdata[i]);
        }

        foreach(i, c; charset)
        {
            Surface surf = new Surface(datawidth[i], dataheight[i], 32, true, rgba[i], false);
            cache[c] = CharInfo(surf,
                                Vector(width[i], height[i]),
                                Vector(prex[i], prey[i]),
                                Vector(postx[i], posty[i]));
        }
        if(ret != 0)
            return false;

        return true;
    }*/

    static ubyte[] toRGBA(ubyte[] data)
    {
        ubyte[] newData = new ubyte[](data.length * 4);
        foreach(i, d; data)
        {
            newData[4*i  ] =
            newData[4*i+1] =
            newData[4*i+2] = 255;
            newData[4*i+3] = d;
        }
        return newData;
    }
}

/**
    \todo Rename font.print to font.writef; add font.printf with C printf syntax; add font.writefln
*/
class Font
{
    protected
    {
        float fheight;
    }

    FontFace nFace;
    FontFace bFace;
    FontFace iFace;
    FontFace biFace;
    uint style;

    this(char[] name, char[] bname, char[] iname, char[] biname, float height, uint preload = 256)
    {
        fheight = height;

        nFace = new FontFace(this, name, preload);

        if(bname != "")
            bFace = new FontFace(this, bname, preload);
        else
            bFace = nFace;

        if(iname != "")
            iFace = new FontFace(this, iname, preload);
        else
            iFace = nFace;

        if(biname != "")
            biFace = new FontFace(this, biname, preload);
        else
            biFace = nFace;
    }
    Font resize(float height, bool dup = false)
    {
        return resize(height, nFace.chars.length, dup);
    }
    Font resize(float height, uint preload, bool dup = false)
    {
        if((height == fheight) && (preload == nFace.chars.length) && !dup)
            return this;

        char[] nName = nFace.fname;
        char[] bName = (bFace is nFace) ? "" : bFace.fname;
        char[] iName = (iFace is nFace) ? "" : iFace.fname;
        char[] biName = (biFace is nFace) ? "" : biFace.fname;

        return new Font(nName, bName, iName, biName, height, preload);
    }

    void print(Vector position, ...)
    {
        printT(position, strFormatX(_arguments, _argptr));
    }
    void print(float x, float y, ...)
    {
        printT(Vector(x, y), strFormatX(_arguments, _argptr));
    }
    void printT(Vector position, char[] text)
    {
        position = strCenterOffsetT(position, text) + Vector(strSizeT(text).x / 2, 0);

        printRawT(position, text);
    }

    void printCentered(Vector position, ...)
    {
        printCenteredT(position, strFormatX(_arguments, _argptr));
    }
    void printCentered(float x, float y, ...)
    {
        printCenteredT(Vector(x, y), strFormatX(_arguments, _argptr));
    }
    /*void printCenteredX(Vector position, TypeInfo[] arguments, void* argptr)
    {
        printCenteredT(position, strFormatX(arguments, argptr));
    }*/
    void printCenteredT(Vector position, char[] text)
    {
        position = strCenterOffsetT(position, text);
        printRawT(position, text);
    }

    Vector strSize(...)
    {
        return strSizeT(strFormatX(_arguments, _argptr));
    }

    Vector strSizeT(char[] text)
    {
        FontFace face = getFace();

        char[][] lines = splitlines(text);

        Vector size = Vector(0.0, 0.0);
        uint i, j;
        float w, h;
        for(i = 0; i < lines.length; i++)
        {
            w = 0.0;
            h = 0.0;
            for(j = 0; j < lines[i].length; j++)
            {
                /*if(j != 0)
                    w += face.chars[i].preTranslate.x;*/
                w += face.chars[i].size.x;
                /*if(j != lines[i].length - 1)
                    w += face.chars[i].postTranslate.x;*/
            }
            size.x = max(size.x, w);
            if(i < lines.length - 1)
                size.y += fheight / 0.63 - fheight;
            size.y += fheight;
        }
        return size;
    }

    size_t strNumLinesT(char[] text)
    {
        return splitlines(text).length;
    }

    Vector strCenterOffsetT(Vector position, char[] text)
    {
        size_t numlines = strNumLinesT(text);
        Vector center = strSizeT(text) / 2.0;
        return position - Vector(center.x, -center.y/* + (fheight / 0.63) * (numlines - 1)*/);
    }

    FontFace getFace()
    {
        bool s_italic, s_bold, s_underlined;

        FontFace norm = nFace;
        FontFace bold = (bFace is null) ? nFace : bFace;
        FontFace ital = (iFace is null) ? nFace : iFace;
        FontFace boit = (biFace is null) ? nFace : biFace;

        if((style & FontStyle.Bold) && (style & FontStyle.Italic))
        {
            return boit;
        }
        else if(style & FontStyle.Italic)
        {
            return ital;
        }
        else if(style & FontStyle.Bold)
        {
            return bold;
        }
        else
        {
            return norm;
        }
    }

    void printRawT(Vector position, char[] text)
    {
        FontFace face = getFace();

        Stack!(Vector) offsets;
        Vector offset = Vector(0.0, 0.0);
        float h = fheight / 0.63;

        // ----------

        //char[][] lines = splitlines(text).reverse;

        //NOTE: used to segfault, the reason was poor unloading in siege.graphics.surface
        char[][] clines = splitlines(text).reverse;
        dchar[][] lines;
        foreach(line; clines)
        {
            lines ~= std.utf.toUTF32(line);
        }


        uint j;
        CharInfo[] ch;
        for(uint i = 0; i < lines.length; i++)
        {
            offsets.push(offset);

            offset = offset + Vector(position.x, position.y - h*i);

            ch = face.getChars(lines[i]);
            if((ch is null) && (lines[i].length != 0))
                continue;
            for(j = 0; j < lines[i].length; j++)
            {
                //offset = offset + ch[j].preTranslate;
                ch[j].texture.draw(/*position + */offset + ch[j].preTranslate, Vector(1.0, -1.0));
                offset = offset + ch[j].postTranslate;
            }

            offset = offsets.pop();
        }

        //font.printRaw(position.x, position.y, text, fheight, getFace());

        //TODO
        /*float width;
        Vector center;
        Vector size;
        if((style & FontStyle.Underlined) || (style & FontStyle.Strikeout))
        {
            width = draw.line.getWidth();
            center = strCenterOffsetT(position, text);
            size = strSizeT(text);

            if(style & FontStyle.Bold)
                draw.line.setWidth(width * 2.0);
        }

        if(style & FontStyle.Underlined)
        {
            draw.line(center + Vector(-size.x, size.y) / 2, center + Vector(size.x, size.y) / 2);
        }
        if(style & FontStyle.Strikeout)
        {
            draw.line(center + Vector(size.x, 0) / 2, center + Vector(size.x, 0));
        }

        if(style & FontStyle.Underlined || style & FontStyle.Strikeout)
            draw.line.setWidth(width);*/
    }

    static char[] strFormat(...)
    {
        return strFormatX(_arguments, _argptr);
    }

    static char[] strFormatX(TypeInfo[] arguments, va_list argptr)
    {
        dchar[] text;

        void formatStep(dchar c)
        {
            text ~= c;
        }

        doFormat(&formatStep, arguments, argptr);

        return toUTF8(text);
    }

    float height()
    {
        return fheight;
    }
}
