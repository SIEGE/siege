/**
    \brief Color handling structure
*/
module siege.util.color;

private
{
    import std.string;
}

/**
    \brief An union containing RGBA floating-point colors mapped to [0.0, 1.0]
    \todo Should this be integer [0, 255] color instead?
    \todo What do we do with 1.0? 255 or illegal value (but clamped to 255)?
*/
union Color
{
    struct
    {
            float r,
                  g,
                  b,
                  a = 1.0;
    }
    float[4] rgba;

    /**
        \brief Create a new color struct {r, g, b, a}
    */
    static Color opCall(float r, float g, float b, float a)
    {
        Color c;
        c.r = r;
        c.g = g;
        c.b = b;
        c.a = a;
        return c;
    }
    /**
        \brief Create a new color struct {r, g, b, 1.0}
    */
    static Color opCall(float r, float g, float b)
    {
        return opCall(r, g, b, 1.0);
    }
    /**
        \brief Create a new color struct {g, g, g, a} (grayscale)
    */
    static Color opCall(float g, float a)
    {
        return opCall(g, g, g, a);
    }
    /**
        \brief Create a new color struct {g, g, g, 1.0} (grayscale)
    */
    static Color opCall(float g)
    {
        return opCall(g, g, g, 1.0);
    }
    /**
        \brief Create a new color struct {nan, nan, nan, 1.0} (unknown color)
    */
    static Color opCall()
    {
        return opCall(float.nan, float.nan, float.nan, 1.0);
    }

    /**
        \brief Get the color in a single 0xRRGGBBAA integer
        \deprecated Use \ref toRGBAInt instead
    */
    deprecated uint opCast()
    {
        return (cast(uint)(rgba[0]*255) << 24) |
               (cast(uint)(rgba[1]*255) << 16) |
               (cast(uint)(rgba[2]*255) <<  8) |
                cast(uint)(rgba[3]*255);
    }
    /**
        \brief A more descriptive version of opCast
        \deprecated Use \ref toRGBAInt instead
    */
    deprecated alias opCast toInt;

    /* @{ */
    /// \brief A shorthand for Color.rgba[i]
    float opIndex(size_t id)
    {
        assert(id < 4);

        return rgba[id];
    }
    /// \brief A shorthand for Color.rgba[i] = ...
    void opIndexAssign(float c, size_t id)
    {
        assert(id < 4);

        rgba[id] = c;
    }
    /* @} */

    /**
        \brief Is the color undefined?
        \return true if it is, false otherwise
    */
    bool isNan()
    {
        if(!(r == r) || !(g == g) || !(b == b) || !(a == a))
            return true;
        return false;
    }

    /*static Color opCall()
    {
        Color c;
        return c;
    }
    static Color opCall(float rgb, float a = 1.0)
    {
        Color c;
        c.r = rgb;
        c.g = c.r;
        c.b = c.r;
        c.a = a;
        return c;
    }
    static Color opCall(float r, float g, float b, float a = 1.0)
    {
        Color c;
        c.r = r;
        c.g = g;
        c.b = b;
        c.a = a;
        return c;
    }
    static Color opCall(ubyte rgb, ubyte a = 255)
    {
        Color c;
        c.r = rgb / cast(float)255;
        c.g = c.r;
        c.b = c.r;
        c.a = a / cast(float)255;
        return c;
    }
    static Color opCall(ubyte r, ubyte g, ubyte b, ubyte a = 255)
    {
        Color c;
        c.r = r / cast(float)255;
        c.g = g / cast(float)255;
        c.b = b / cast(float)255;
        c.a = a / cast(float)255;
        return c;
    }*/

    /**
        \brief Mix two colors together
        \param color1 The first color
        \param color2 The second color
        \param factor The mixing factor (closer to 1, the less of first color is mixed)
    */
    static Color mix(Color color1, Color color2, float factor)
    {
        float mfactor = 1.0 - factor;
        return Color(color1.r * mfactor + color2.r * factor, color1.g * mfactor + color2.g * factor, color1.b * mfactor + color2.b * factor, color1.a * mfactor + color2.a * factor);
    }

    /// \name Color conversion
    /// \todo Conversion to spaces other than RGB
    /* @{ */
    /// \brief Get the color in a 0xRRGGBB integer
    uint toRGBInt()
    {
        return (cast(uint)(r*255) << 16) |
               (cast(uint)(g*255) <<  8) |
                cast(uint)(b*255);
    }
    /// \brief Get the color in a 0xRRGGBBAA integer
    uint toRGBAInt()
    {
        return (cast(uint)(r*255) << 24) |
               (cast(uint)(g*255) << 16) |
               (cast(uint)(b*255) <<  8) |
                cast(uint)(a*255);
    }
    /// \brief Get the color in a 0xAARRGGBB integer
    uint toARGBInt()
    {
        return (cast(uint)(a*255) << 24) |
               (cast(uint)(r*255) << 16) |
               (cast(uint)(g*255) <<  8) |
                cast(uint)(b*255);
    }
    /// \brief Get the color in a 0xBBGGRR integer
    uint toBGRInt()
    {
        return (cast(uint)(b*255) << 16) |
               (cast(uint)(g*255) <<  8) |
                cast(uint)(r*255);
    }
    /// \brief Get the color in a 0xAABBGGRR integer
    uint toABGRInt()
    {
        return (cast(uint)(a*255) << 24) |
               (cast(uint)(b*255) << 16) |
               (cast(uint)(g*255) <<  8) |
                cast(uint)(r*255);
    }
    /// \brief Get the color in a 0xBBGGRRAA integer
    uint toBGRAInt()
    {
        return (cast(uint)(b*255) << 24) |
               (cast(uint)(g*255) << 16) |
               (cast(uint)(r*255) <<  8) |
                cast(uint)(a*255);
    }

    /// \brief Get the string representation of the color
    char[] toString()
    {
        return std.string.toString(r)~","
              ~std.string.toString(g)~","
              ~std.string.toString(b)~","
              ~std.string.toString(a);
    }

    /**
        \brief Get a color from a 0xRRGGBB integer
        \todo Create different "versions" for conversion from RGB, RGBA, ARGB...
        \attention This will be deprecated in the future
    */
    static Color fromRGBInt(uint c)
    {
        return fromRGBAInt((c << 8) | 0xFF);
    }
    /**
        \brief Get a color from a 0xRRGGBBAA integer
        \todo Create different "versions" for conversion from RGB, RGBA, ARGB...
        \attention This will be deprecated in the future
    */
    static Color fromRGBAInt(uint c)
    {
        return Color(((c >> 24) & 255) / cast(float)255,
                     ((c >> 16) & 255) / cast(float)255,
                     ((c >>  8) & 255) / cast(float)255,
                     ( c        & 255) / cast(float)255);
    }
    /**
        \brief Get a color from a string
        \todo Cleanup the code
    */
    static Color fromString(char[] str)
    {
        if(str.length == 0)
            return Color();

        if(str[0] == '#')
        {
            if(str.length < 7)
                return Color();

            uint color = 0;
            int val;
            foreach(h; str[1..7])
            {
                val = ifind(hexdigits, h);
                if(val < 0)
                    return Color();

                color <<= 4;
                color |= val;
            }

            ubyte alpha = 255;
            if(str.length >= 9)
            {
                alpha = 0;
                foreach(h; str[7..9])
                {
                    val = ifind(hexdigits, h);
                    if(val < 0)
                    {
                        alpha = 255;
                        break;
                    }

                    alpha <<= 4;
                    alpha |= val;
                }
            }

            color <<= 8;
            color |= alpha;

            return fromRGBAInt(color);
        }

        if((str.length >= 16) && (tolower(str[0..3]) == "rgb"))
        {
            int open = find(str, "(");
            if(open < 0)
                return Color();

            int close = find(str, ")");
            if(close < open)
                return Color();

            char[][] parse = split(str[open+1..close], ",");
            if(parse.length < 3 || parse.length > 4)
                return Color();

            uint color = (atoi(parse[0]) << 24) |
                         (atoi(parse[1]) << 16) |
                         (atoi(parse[2]) <<  8);

            if(parse.length == 4)
                color |= atoi(parse[3]);
            else
                color |= 255;

            return fromRGBAInt(color);
        }

        if(!Name[str].isNan())
            return Name[str];

        return Color();
    }
    /* @} */

    static ColorName Name;

    static const Color Nan;
    static this()
    {
        Nan = Color(float.nan, float.nan, float.nan, float.nan);
    }
}

/* @{ */
/**
    \brief A structure for handling HTML color name constants \brief
    <a href="http://www.w3schools.com/css/css_colornames.asp">Reference: http://www.w3schools.com/css/css_colornames.asp</a>
    \todo Should this be moved into a separate module?
*/
struct ColorName
{
    private static this()
    {
        SName["none"]        = Color.fromRGBAInt(0x00000000); // transparent
        SName["transparent"] = Color.fromRGBAInt(0x00000000);

        SName["aliceblue"]            = Color.fromRGBInt(0xF0F8FF);
        SName["antiquewhite"]         = Color.fromRGBInt(0xFAEBD7);
        SName["aqua"]                 = Color.fromRGBInt(0x00FFFF);
        SName["aquamarine"]           = Color.fromRGBInt(0x7FFFD4);
        SName["azure"]                = Color.fromRGBInt(0xF0FFFF);
        SName["beige"]                = Color.fromRGBInt(0xF5F5DC);
        SName["bisque"]               = Color.fromRGBInt(0xFFE4C4);
        SName["black"]                = Color.fromRGBInt(0x000000);
        SName["blanchedalmond"]       = Color.fromRGBInt(0xFFEBCD);
        SName["blue"]                 = Color.fromRGBInt(0x0000FF);
        SName["blueviolet"]           = Color.fromRGBInt(0x8A2BE2);
        SName["brown"]                = Color.fromRGBInt(0xA52A2A);
        SName["burlywood"]            = Color.fromRGBInt(0xDEB887);
        SName["cadetblue"]            = Color.fromRGBInt(0x5F9EA0);
        SName["chartreuse"]           = Color.fromRGBInt(0x7FFF00);
        SName["chocolate"]            = Color.fromRGBInt(0xD2691E);
        SName["coral"]                = Color.fromRGBInt(0xFF7F50);
        SName["cornflowerblue"]       = Color.fromRGBInt(0x6495ED);
        SName["cornsilk"]             = Color.fromRGBInt(0xFFF8DC);
        SName["crimson"]              = Color.fromRGBInt(0xDC143C);
        SName["cyan"]                 = Color.fromRGBInt(0x00FFFF);
        SName["darkblue"]             = Color.fromRGBInt(0x00008B);
        SName["darkcyan"]             = Color.fromRGBInt(0x008B8B);
        SName["darkgoldenrod"]        = Color.fromRGBInt(0xB8860B);
        SName["darkgray"]             = Color.fromRGBInt(0xA9A9A9);
        SName["darkgrey"]             = Color.fromRGBInt(0xA9A9A9);
        SName["darkgreen"]            = Color.fromRGBInt(0x006400);
        SName["darkkhaki"]            = Color.fromRGBInt(0xBDB76B);
        SName["darkmagenta"]          = Color.fromRGBInt(0x8B008B);
        SName["darkolivegreen"]       = Color.fromRGBInt(0x556B2F);
        SName["darkorange"]           = Color.fromRGBInt(0xFF8C00);
        SName["darkorchid"]           = Color.fromRGBInt(0x9932CC);
        SName["darkred"]              = Color.fromRGBInt(0x8B0000);
        SName["darksalmon"]           = Color.fromRGBInt(0xE9967A);
        SName["darkseagreen"]         = Color.fromRGBInt(0x8FBC8F);
        SName["darkslateblue"]        = Color.fromRGBInt(0x483D8B);
        SName["darkslategray"]        = Color.fromRGBInt(0x2F4F4F);
        SName["darkslategrey"]        = Color.fromRGBInt(0x2F4F4F);
        SName["darkturquoise"]        = Color.fromRGBInt(0x00CED1);
        SName["darkviolet"]           = Color.fromRGBInt(0x9400D3);
        SName["deeppink"]             = Color.fromRGBInt(0xFF1493);
        SName["deepskyblue"]          = Color.fromRGBInt(0x00BFFF);
        SName["dimgray"]              = Color.fromRGBInt(0x696969);
        SName["dimgrey"]              = Color.fromRGBInt(0x696969);
        SName["dodgerblue"]           = Color.fromRGBInt(0x1E90FF);
        SName["firebrick"]            = Color.fromRGBInt(0xB22222);
        SName["floralwhite"]          = Color.fromRGBInt(0xFFFAF0);
        SName["forestgreen"]          = Color.fromRGBInt(0x228B22);
        SName["fuchsia"]              = Color.fromRGBInt(0xFF00FF);
        SName["gainsboro"]            = Color.fromRGBInt(0xDCDCDC);
        SName["ghostwhite"]           = Color.fromRGBInt(0xF8F8FF);
        SName["gold"]                 = Color.fromRGBInt(0xFFD700);
        SName["goldenrod"]            = Color.fromRGBInt(0xDAA520);
        SName["gray"]                 = Color.fromRGBInt(0x808080);
        SName["grey"]                 = Color.fromRGBInt(0x808080);
        SName["green"]                = Color.fromRGBInt(0x008000);
        SName["greenyellow"]          = Color.fromRGBInt(0xADFF2F);
        SName["honeydew"]             = Color.fromRGBInt(0xF0FFF0);
        SName["hotpink"]              = Color.fromRGBInt(0xFF69B4);
        SName["indianred"]            = Color.fromRGBInt(0xCD5C5C);
        SName["indigo"]               = Color.fromRGBInt(0x4B0082);
        SName["ivory"]                = Color.fromRGBInt(0xFFFFF0);
        SName["khaki"]                = Color.fromRGBInt(0xF0E68C);
        SName["lavender"]             = Color.fromRGBInt(0xE6E6FA);
        SName["lavenderblush"]        = Color.fromRGBInt(0xFFF0F5);
        SName["lawngreen"]            = Color.fromRGBInt(0x7CFC00);
        SName["lemonchiffon"]         = Color.fromRGBInt(0xFFFACD);
        SName["lightblue"]            = Color.fromRGBInt(0xADD8E6);
        SName["lightcoral"]           = Color.fromRGBInt(0xF08080);
        SName["lightcyan"]            = Color.fromRGBInt(0xE0FFFF);
        SName["lightgoldenrodyellow"] = Color.fromRGBInt(0xFAFAD2);
        SName["lightgrey"]            = Color.fromRGBInt(0xD3D3D3);
        SName["lightgreen"]           = Color.fromRGBInt(0x90EE90);
        SName["lightpink"]            = Color.fromRGBInt(0xFFB6C1);
        SName["lightsalmon"]          = Color.fromRGBInt(0xFFA07A);
        SName["lightseagreen"]        = Color.fromRGBInt(0x20B2AA);
        SName["lightskyblue"]         = Color.fromRGBInt(0x87CEFA);
        SName["lightslategray"]       = Color.fromRGBInt(0x778899);
        SName["lightslategrey"]       = Color.fromRGBInt(0x778899);
        SName["lightsteelblue"]       = Color.fromRGBInt(0xB0C4DE);
        SName["lightyellow"]          = Color.fromRGBInt(0xFFFFE0);
        SName["lime"]                 = Color.fromRGBInt(0x00FF00);
        SName["limegreen"]            = Color.fromRGBInt(0x32CD32);
        SName["linen"]                = Color.fromRGBInt(0xFAF0E6);
        SName["magenta"]              = Color.fromRGBInt(0xFF00FF);
        SName["maroon"]               = Color.fromRGBInt(0x800000);
        SName["mediumaquamarine"]     = Color.fromRGBInt(0x66CDAA);
        SName["mediumblue"]           = Color.fromRGBInt(0x0000CD);
        SName["mediumorchid"]         = Color.fromRGBInt(0xBA55D3);
        SName["mediumpurple"]         = Color.fromRGBInt(0x9370D8);
        SName["mediumseagreen"]       = Color.fromRGBInt(0x3CB371);
        SName["mediumslateblue"]      = Color.fromRGBInt(0x7B68EE);
        SName["mediumspringgreen"]    = Color.fromRGBInt(0x00FA9A);
        SName["mediumturquoise"]      = Color.fromRGBInt(0x48D1CC);
        SName["mediumvioletred"]      = Color.fromRGBInt(0xC71585);
        SName["midnightblue"]         = Color.fromRGBInt(0x191970);
        SName["mintcream"]            = Color.fromRGBInt(0xF5FFFA);
        SName["mistyrose"]            = Color.fromRGBInt(0xFFE4E1);
        SName["moccasin"]             = Color.fromRGBInt(0xFFE4B5);
        SName["navajowhite"]          = Color.fromRGBInt(0xFFDEAD);
        SName["navy"]                 = Color.fromRGBInt(0x000080);
        SName["oldlace"]              = Color.fromRGBInt(0xFDF5E6);
        SName["olive"]                = Color.fromRGBInt(0x808000);
        SName["olivedrab"]            = Color.fromRGBInt(0x6B8E23);
        SName["orange"]               = Color.fromRGBInt(0xFFA500);
        SName["orangered"]            = Color.fromRGBInt(0xFF4500);
        SName["orchid"]               = Color.fromRGBInt(0xDA70D6);
        SName["palegoldenrod"]        = Color.fromRGBInt(0xEEE8AA);
        SName["palegreen"]            = Color.fromRGBInt(0x98FB98);
        SName["paleturquoise"]        = Color.fromRGBInt(0xAFEEEE);
        SName["palevioletred"]        = Color.fromRGBInt(0xD87093);
        SName["papayawhip"]           = Color.fromRGBInt(0xFFEFD5);
        SName["peachpuff"]            = Color.fromRGBInt(0xFFDAB9);
        SName["peru"]                 = Color.fromRGBInt(0xCD853F);
        SName["pink"]                 = Color.fromRGBInt(0xFFC0CB);
        SName["plum"]                 = Color.fromRGBInt(0xDDA0DD);
        SName["powderblue"]           = Color.fromRGBInt(0xB0E0E6);
        SName["purple"]               = Color.fromRGBInt(0x800080);
        SName["red"]                  = Color.fromRGBInt(0xFF0000);
        SName["rosybrown"]            = Color.fromRGBInt(0xBC8F8F);
        SName["royalblue"]            = Color.fromRGBInt(0x4169E1);
        SName["saddlebrown"]          = Color.fromRGBInt(0x8B4513);
        SName["salmon"]               = Color.fromRGBInt(0xFA8072);
        SName["sandybrown"]           = Color.fromRGBInt(0xF4A460);
        SName["seagreen"]             = Color.fromRGBInt(0x2E8B57);
        SName["seashell"]             = Color.fromRGBInt(0xFFF5EE);
        SName["sienna"]               = Color.fromRGBInt(0xA0522D);
        SName["silver"]               = Color.fromRGBInt(0xC0C0C0);
        SName["skyblue"]              = Color.fromRGBInt(0x87CEEB);
        SName["slateblue"]            = Color.fromRGBInt(0x6A5ACD);
        SName["slategray"]            = Color.fromRGBInt(0x708090);
        SName["slategrey"]            = Color.fromRGBInt(0x708090);
        SName["snow"]                 = Color.fromRGBInt(0xFFFAFA);
        SName["springgreen"]          = Color.fromRGBInt(0x00FF7F);
        SName["steelblue"]            = Color.fromRGBInt(0x4682B4);
        SName["tan"]                  = Color.fromRGBInt(0xD2B48C);
        SName["teal"]                 = Color.fromRGBInt(0x008080);
        SName["thistle"]              = Color.fromRGBInt(0xD8BFD8);
        SName["tomato"]               = Color.fromRGBInt(0xFF6347);
        SName["turquoise"]            = Color.fromRGBInt(0x40E0D0);
        SName["violet"]               = Color.fromRGBInt(0xEE82EE);
        SName["wheat"]                = Color.fromRGBInt(0xF5DEB3);
        SName["white"]                = Color.fromRGBInt(0xFFFFFF);
        SName["whitesmoke"]           = Color.fromRGBInt(0xF5F5F5);
        SName["yellow"]               = Color.fromRGBInt(0xFFFF00);
        SName["yellowgreen"]          = Color.fromRGBInt(0x9ACD32);

        AliceBlue            = Color.fromRGBInt(0xF0F8FF);
        AntiqueWhite         = Color.fromRGBInt(0xFAEBD7);
        Aqua                 = Color.fromRGBInt(0x00FFFF);
        Aquamarine           = Color.fromRGBInt(0x7FFFD4);
        Azure                = Color.fromRGBInt(0xF0FFFF);
        Beige                = Color.fromRGBInt(0xF5F5DC);
        Bisque               = Color.fromRGBInt(0xFFE4C4);
        Black                = Color.fromRGBInt(0x000000);
        BlanchedAlmond       = Color.fromRGBInt(0xFFEBCD);
        Blue                 = Color.fromRGBInt(0x0000FF);
        BlueViolet           = Color.fromRGBInt(0x8A2BE2);
        Brown                = Color.fromRGBInt(0xA52A2A);
        BurlyWood            = Color.fromRGBInt(0xDEB887);
        CadetBlue            = Color.fromRGBInt(0x5F9EA0);
        Chartreuse           = Color.fromRGBInt(0x7FFF00);
        Chocolate            = Color.fromRGBInt(0xD2691E);
        Coral                = Color.fromRGBInt(0xFF7F50);
        CornflowerBlue       = Color.fromRGBInt(0x6495ED);
        Cornsilk             = Color.fromRGBInt(0xFFF8DC);
        Crimson              = Color.fromRGBInt(0xDC143C);
        Cyan                 = Color.fromRGBInt(0x00FFFF);
        DarkBlue             = Color.fromRGBInt(0x00008B);
        DarkCyan             = Color.fromRGBInt(0x008B8B);
        DarkGoldenRod        = Color.fromRGBInt(0xB8860B);
        DarkGray             = Color.fromRGBInt(0xA9A9A9);
        DarkGrey             = Color.fromRGBInt(0xA9A9A9);
        DarkGreen            = Color.fromRGBInt(0x006400);
        DarkKhaki            = Color.fromRGBInt(0xBDB76B);
        DarkMagenta          = Color.fromRGBInt(0x8B008B);
        DarkOliveGreen       = Color.fromRGBInt(0x556B2F);
        Darkorange           = Color.fromRGBInt(0xFF8C00);
        DarkOrchid           = Color.fromRGBInt(0x9932CC);
        DarkRed              = Color.fromRGBInt(0x8B0000);
        DarkSalmon           = Color.fromRGBInt(0xE9967A);
        DarkSeaGreen         = Color.fromRGBInt(0x8FBC8F);
        DarkSlateBlue        = Color.fromRGBInt(0x483D8B);
        DarkSlateGray        = Color.fromRGBInt(0x2F4F4F);
        DarkSlateGrey        = Color.fromRGBInt(0x2F4F4F);
        DarkTurquoise        = Color.fromRGBInt(0x00CED1);
        DarkViolet           = Color.fromRGBInt(0x9400D3);
        DeepPink             = Color.fromRGBInt(0xFF1493);
        DeepSkyBlue          = Color.fromRGBInt(0x00BFFF);
        DimGray              = Color.fromRGBInt(0x696969);
        DimGrey              = Color.fromRGBInt(0x696969);
        DodgerBlue           = Color.fromRGBInt(0x1E90FF);
        FireBrick            = Color.fromRGBInt(0xB22222);
        FloralWhite          = Color.fromRGBInt(0xFFFAF0);
        ForestGreen          = Color.fromRGBInt(0x228B22);
        Fuchsia              = Color.fromRGBInt(0xFF00FF);
        Gainsboro            = Color.fromRGBInt(0xDCDCDC);
        GhostWhite           = Color.fromRGBInt(0xF8F8FF);
        Gold                 = Color.fromRGBInt(0xFFD700);
        GoldenRod            = Color.fromRGBInt(0xDAA520);
        Gray                 = Color.fromRGBInt(0x808080);
        Grey                 = Color.fromRGBInt(0x808080);
        Green                = Color.fromRGBInt(0x008000);
        GreenYellow          = Color.fromRGBInt(0xADFF2F);
        HoneyDew             = Color.fromRGBInt(0xF0FFF0);
        HotPink              = Color.fromRGBInt(0xFF69B4);
        IndianRed            = Color.fromRGBInt(0xCD5C5C);
        Indigo               = Color.fromRGBInt(0x4B0082);
        Ivory                = Color.fromRGBInt(0xFFFFF0);
        Khaki                = Color.fromRGBInt(0xF0E68C);
        Lavender             = Color.fromRGBInt(0xE6E6FA);
        LavenderBlush        = Color.fromRGBInt(0xFFF0F5);
        LawnGreen            = Color.fromRGBInt(0x7CFC00);
        LemonChiffon         = Color.fromRGBInt(0xFFFACD);
        LightBlue            = Color.fromRGBInt(0xADD8E6);
        LightCoral           = Color.fromRGBInt(0xF08080);
        LightCyan            = Color.fromRGBInt(0xE0FFFF);
        LightGoldenRodYellow = Color.fromRGBInt(0xFAFAD2);
        LightGrey            = Color.fromRGBInt(0xD3D3D3);
        LightGreen           = Color.fromRGBInt(0x90EE90);
        LightPink            = Color.fromRGBInt(0xFFB6C1);
        LightSalmon          = Color.fromRGBInt(0xFFA07A);
        LightSeaGreen        = Color.fromRGBInt(0x20B2AA);
        LightSkyBlue         = Color.fromRGBInt(0x87CEFA);
        LightSlateGray       = Color.fromRGBInt(0x778899);
        LightSlateGrey       = Color.fromRGBInt(0x778899);
        LightSteelBlue       = Color.fromRGBInt(0xB0C4DE);
        LightYellow          = Color.fromRGBInt(0xFFFFE0);
        Lime                 = Color.fromRGBInt(0x00FF00);
        LimeGreen            = Color.fromRGBInt(0x32CD32);
        Linen                = Color.fromRGBInt(0xFAF0E6);
        Magenta              = Color.fromRGBInt(0xFF00FF);
        Maroon               = Color.fromRGBInt(0x800000);
        MediumAquaMarine     = Color.fromRGBInt(0x66CDAA);
        MediumBlue           = Color.fromRGBInt(0x0000CD);
        MediumOrchid         = Color.fromRGBInt(0xBA55D3);
        MediumPurple         = Color.fromRGBInt(0x9370D8);
        MediumSeaGreen       = Color.fromRGBInt(0x3CB371);
        MediumSlateBlue      = Color.fromRGBInt(0x7B68EE);
        MediumSpringGreen    = Color.fromRGBInt(0x00FA9A);
        MediumTurquoise      = Color.fromRGBInt(0x48D1CC);
        MediumVioletRed      = Color.fromRGBInt(0xC71585);
        MidnightBlue         = Color.fromRGBInt(0x191970);
        MintCream            = Color.fromRGBInt(0xF5FFFA);
        MistyRose            = Color.fromRGBInt(0xFFE4E1);
        Moccasin             = Color.fromRGBInt(0xFFE4B5);
        NavajoWhite          = Color.fromRGBInt(0xFFDEAD);
        Navy                 = Color.fromRGBInt(0x000080);
        OldLace              = Color.fromRGBInt(0xFDF5E6);
        Olive                = Color.fromRGBInt(0x808000);
        OliveDrab            = Color.fromRGBInt(0x6B8E23);
        Orange               = Color.fromRGBInt(0xFFA500);
        OrangeRed            = Color.fromRGBInt(0xFF4500);
        Orchid               = Color.fromRGBInt(0xDA70D6);
        PaleGoldenRod        = Color.fromRGBInt(0xEEE8AA);
        PaleGreen            = Color.fromRGBInt(0x98FB98);
        PaleTurquoise        = Color.fromRGBInt(0xAFEEEE);
        PaleVioletRed        = Color.fromRGBInt(0xD87093);
        PapayaWhip           = Color.fromRGBInt(0xFFEFD5);
        PeachPuff            = Color.fromRGBInt(0xFFDAB9);
        Peru                 = Color.fromRGBInt(0xCD853F);
        Pink                 = Color.fromRGBInt(0xFFC0CB);
        Plum                 = Color.fromRGBInt(0xDDA0DD);
        PowderBlue           = Color.fromRGBInt(0xB0E0E6);
        Purple               = Color.fromRGBInt(0x800080);
        Red                  = Color.fromRGBInt(0xFF0000);
        RosyBrown            = Color.fromRGBInt(0xBC8F8F);
        RoyalBlue            = Color.fromRGBInt(0x4169E1);
        SaddleBrown          = Color.fromRGBInt(0x8B4513);
        Salmon               = Color.fromRGBInt(0xFA8072);
        SandyBrown           = Color.fromRGBInt(0xF4A460);
        SeaGreen             = Color.fromRGBInt(0x2E8B57);
        SeaShell             = Color.fromRGBInt(0xFFF5EE);
        Sienna               = Color.fromRGBInt(0xA0522D);
        Silver               = Color.fromRGBInt(0xC0C0C0);
        SkyBlue              = Color.fromRGBInt(0x87CEEB);
        SlateBlue            = Color.fromRGBInt(0x6A5ACD);
        SlateGray            = Color.fromRGBInt(0x708090);
        SlateGrey            = Color.fromRGBInt(0x708090);
        Snow                 = Color.fromRGBInt(0xFFFAFA);
        SpringGreen          = Color.fromRGBInt(0x00FF7F);
        SteelBlue            = Color.fromRGBInt(0x4682B4);
        Tan                  = Color.fromRGBInt(0xD2B48C);
        Teal                 = Color.fromRGBInt(0x008080);
        Thistle              = Color.fromRGBInt(0xD8BFD8);
        Tomato               = Color.fromRGBInt(0xFF6347);
        Turquoise            = Color.fromRGBInt(0x40E0D0);
        Violet               = Color.fromRGBInt(0xEE82EE);
        Wheat                = Color.fromRGBInt(0xF5DEB3);
        White                = Color.fromRGBInt(0xFFFFFF);
        WhiteSmoke           = Color.fromRGBInt(0xF5F5F5);
        Yellow               = Color.fromRGBInt(0xFFFF00);
        YellowGreen          = Color.fromRGBInt(0x9ACD32);
    }

    /**
        \brief Used for getting the color from a string
    */
    static Color opIndex(char[] name)
    {
        if(tolower(name) in SName)
            return SName[tolower(name)];
        return Color.Nan;
    }

    static:
        private const Color[char[]] SName;

        const Color AliceBlue;
        const Color AntiqueWhite;
        const Color Aqua;
        const Color Aquamarine;
        const Color Azure;
        const Color Beige;
        const Color Bisque;
        const Color Black;
        const Color BlanchedAlmond;
        const Color Blue;
        const Color BlueViolet;
        const Color Brown;
        const Color BurlyWood;
        const Color CadetBlue;
        const Color Chartreuse;
        const Color Chocolate;
        const Color Coral;
        const Color CornflowerBlue;
        const Color Cornsilk;
        const Color Crimson;
        const Color Cyan;
        const Color DarkBlue;
        const Color DarkCyan;
        const Color DarkGoldenRod;
        const Color DarkGray;
        const Color DarkGrey;
        const Color DarkGreen;
        const Color DarkKhaki;
        const Color DarkMagenta;
        const Color DarkOliveGreen;
        const Color Darkorange;
        const Color DarkOrchid;
        const Color DarkRed;
        const Color DarkSalmon;
        const Color DarkSeaGreen;
        const Color DarkSlateBlue;
        const Color DarkSlateGray;
        const Color DarkSlateGrey;
        const Color DarkTurquoise;
        const Color DarkViolet;
        const Color DeepPink;
        const Color DeepSkyBlue;
        const Color DimGray;
        const Color DimGrey;
        const Color DodgerBlue;
        const Color FireBrick;
        const Color FloralWhite;
        const Color ForestGreen;
        const Color Fuchsia;
        const Color Gainsboro;
        const Color GhostWhite;
        const Color Gold;
        const Color GoldenRod;
        const Color Gray;
        const Color Grey;
        const Color Green;
        const Color GreenYellow;
        const Color HoneyDew;
        const Color HotPink;
        const Color IndianRed;
        const Color Indigo;
        const Color Ivory;
        const Color Khaki;
        const Color Lavender;
        const Color LavenderBlush;
        const Color LawnGreen;
        const Color LemonChiffon;
        const Color LightBlue;
        const Color LightCoral;
        const Color LightCyan;
        const Color LightGoldenRodYellow;
        const Color LightGrey;
        const Color LightGreen;
        const Color LightPink;
        const Color LightSalmon;
        const Color LightSeaGreen;
        const Color LightSkyBlue;
        const Color LightSlateGray;
        const Color LightSlateGrey;
        const Color LightSteelBlue;
        const Color LightYellow;
        const Color Lime;
        const Color LimeGreen;
        const Color Linen;
        const Color Magenta;
        const Color Maroon;
        const Color MediumAquaMarine;
        const Color MediumBlue;
        const Color MediumOrchid;
        const Color MediumPurple;
        const Color MediumSeaGreen;
        const Color MediumSlateBlue;
        const Color MediumSpringGreen;
        const Color MediumTurquoise;
        const Color MediumVioletRed;
        const Color MidnightBlue;
        const Color MintCream;
        const Color MistyRose;
        const Color Moccasin;
        const Color NavajoWhite;
        const Color Navy;
        const Color OldLace;
        const Color Olive;
        const Color OliveDrab;
        const Color Orange;
        const Color OrangeRed;
        const Color Orchid;
        const Color PaleGoldenRod;
        const Color PaleGreen;
        const Color PaleTurquoise;
        const Color PaleVioletRed;
        const Color PapayaWhip;
        const Color PeachPuff;
        const Color Peru;
        const Color Pink;
        const Color Plum;
        const Color PowderBlue;
        const Color Purple;
        const Color Red;
        const Color RosyBrown;
        const Color RoyalBlue;
        const Color SaddleBrown;
        const Color Salmon;
        const Color SandyBrown;
        const Color SeaGreen;
        const Color SeaShell;
        const Color Sienna;
        const Color Silver;
        const Color SkyBlue;
        const Color SlateBlue;
        const Color SlateGray;
        const Color SlateGrey;
        const Color Snow;
        const Color SpringGreen;
        const Color SteelBlue;
        const Color Tan;
        const Color Teal;
        const Color Thistle;
        const Color Tomato;
        const Color Turquoise;
        const Color Violet;
        const Color Wheat;
        const Color White;
        const Color WhiteSmoke;
        const Color Yellow;
        const Color YellowGreen;
}
/* @} */
