module siege.modules.graphics;

private
{
    import derelict.util.loader;

    import siege.modules.modules;

    import siege.util.misc;

    import std.string;
}

enum: uint
{
    SG_GRAPHICS_PRIMITIVE_POINTS            = 0x01,
    SG_GRAPHICS_PRIMITIVE_LINES             = 0x02,
    SG_GRAPHICS_PRIMITIVE_LINE_STRIP        = 0x03,
    SG_GRAPHICS_PRIMITIVE_LINE_FAN          = 0x04,
    SG_GRAPHICS_PRIMITIVE_LINE_LOOP         = 0x05,
    SG_GRAPHICS_PRIMITIVE_TRIANGLES         = 0x06,
    SG_GRAPHICS_PRIMITIVE_TRIANGLE_STRIP    = 0x07,
    SG_GRAPHICS_PRIMITIVE_TRIANGLE_FAN      = 0x08,
    //SG_GRAPHICS_PRIMITIVE_TRIANGLE_LOOP     = 0x09,
    SG_GRAPHICS_PRIMITIVE_QUADS             = 0x0A,
    SG_GRAPHICS_PRIMITIVE_QUAD_STRIP        = 0x0B,
    //SG_GRAPHICS_PRIMITIVE_QUAD_FAN          = 0x0C,
    //SG_GRAPHICS_PRIMITIVE_QUAD_LOOP         = 0x0D,

    SG_GRAPHICS_PRIMITIVE_CONVEX_POLYGON        = 0x10,
    SG_GRAPHICS_PRIMITIVE_CONCAVE_POLYGON       = 0x20,
    SG_GRAPHICS_PRIMITIVE_INTERSECTING_POLYGON  = 0x30,

    SG_GRAPHICS_TEXTURE_NPOT    = 0x01,
}

void loadModuleGraphics(SharedLib lib)
{
    /// Graphics
    checkBindFunc(sgGraphicsContextCreate)("sgGraphicsContextCreate", lib);
    checkBindFunc(sgGraphicsContextDestroy)("sgGraphicsContextDestroy", lib);
    checkBindFunc(sgGraphicsContextResize)("sgGraphicsContextResize", lib);
    checkBindFunc(sgGraphicsContextClear)("sgGraphicsContextClear", lib);

    checkBindFunc(sgGraphicsViewportCreate)("sgGraphicsViewportCreate", lib);
    //checkBindFunc(sgGraphicsViewportCreateView)("sgGraphicsViewportCreateView", lib);
    checkBindFunc(sgGraphicsViewportDestroy)("sgGraphicsViewportDestroy", lib);
    checkBindFunc(sgGraphicsViewportSetView)("sgGraphicsViewportSetView", lib);
    //checkBindFunc(sgGraphicsViewportGetView)("sgGraphicsViewportGetView", lib);

    checkBindFunc(sgGraphicsSurfaceCreate)("sgGraphicsSurfaceCreate", lib);
    //checkBindFunc(sgGraphicsSurfaceCreateTexture)("sgGraphicsSurfaceCreateTexture", lib);
    //checkBindFunc(sgGraphicsSurfaceCreateData)("sgGraphicsSurfaceCreateData", lib);
    checkBindFunc(sgGraphicsSurfaceDestroy)("sgGraphicsSurfaceDestroy", lib);
    checkBindFunc(sgGraphicsSurfaceSetTexture)("sgGraphicsSurfaceSetTexture", lib);
    checkBindFunc(sgGraphicsSurfaceGetTexture)("sgGraphicsSurfaceGetTexture", lib);
    checkBindFunc(sgGraphicsSurfaceSetData)("sgGraphicsSurfaceSetData", lib);
    //checkBindFunc(sgGraphicsSurfaceGetData)("sgGraphicsSurfaceGetData", lib);
    //checkBindFunc(sgGraphicsSurfaceFreeData)("sgGraphicsSurfaceFreeData", lib);
    checkBindFunc(sgGraphicsSurfaceGetSize)("sgGraphicsSurfaceGetSize", lib);
    checkBindFunc(sgGraphicsSurfaceDraw)("sgGraphicsSurfaceDraw", lib);
    checkBindFunc(sgGraphicsSurfaceSetTarget)("sgGraphicsSurfaceSetTarget", lib);
    //checkBindFunc(sgGraphicsSurfaceGetTarget)("sgGraphicsSurfaceGetTarget", lib);
    checkBindFunc(sgGraphicsSurfaceResetTarget)("sgGraphicsSurfaceResetTarget", lib);

    checkBindFunc(sgGraphicsTextureCreate)("sgGraphicsTextureCreate", lib);
    //checkBindFunc(sgGraphicsTextureCreateData)("sgGraphicsTextureCreateData", lib);
    checkBindFunc(sgGraphicsTextureDestroy)("sgGraphicsTextureDestroy", lib);
    checkBindFunc(sgGraphicsTextureSetData)("sgGraphicsTextureSetData", lib);
    //checkBindFunc(sgGraphicsTextureGetData)("sgGraphicsTextureGetData", lib);
    //checkBindFunc(sgGraphicsTextureFreeData)("sgGraphicsTextureFreeData", lib);
    checkBindFunc(sgGraphicsTextureGetSize)("sgGraphicsTextureGetSize", lib);
    checkBindFunc(sgGraphicsTextureDraw)("sgGraphicsTextureDraw", lib);

    checkBindFunc(sgGraphicsDrawPrimitive)("sgGraphicsDrawPrimitive", lib);
    checkBindFunc(sgGraphicsDrawPointSetSize)("sgGraphicsDrawPointSetSize", lib);
    //bindFunc(sgGraphicsDrawPointGetSize)("sgGraphicsDrawPointGetSize", lib);
    checkBindFunc(sgGraphicsDrawLineSetWidth)("sgGraphicsDrawLineSetWidth", lib);
    //bindFunc(sgGraphicsDrawLineGetWidth)("sgGraphicsDrawLineGetWidth", lib);
    //bindFunc(sgGraphicsDrawLineSetStipple)("sgGraphicsDrawLineSetStipple", lib);
    //bindFunc(sgGraphicsDrawLineGetStipple)("sgGraphicsDrawLineGetStipple", lib);
    //bindFunc(sgGraphicsDrawPolygonSetStipple)("sgGraphicsDrawPolygonSetStipple", lib);
    //bindFunc(sgGraphicsDrawPolygonGetStipple)("sgGraphicsDrawPolygonGetStipple", lib);

    /// Graphics Load
    checkBindFunc(sgGraphicsLoadFile)("sgGraphicsLoadFile", lib);
    //checkBindFunc(sgGraphicsLoadStream)("sgGraphicsLoadStream", lib);
    checkBindFunc(sgGraphicsLoadFreeData)("sgGraphicsLoadFreeData", lib);
}

extern(C)
{
    /// Graphics
    uint function(void** context, uint width, uint height, ubyte bpp) sgGraphicsContextCreate;
    uint function(void* context) sgGraphicsContextDestroy;
    uint function(void* context, uint width, uint height) sgGraphicsContextResize;
    uint function(void* context, float* color) sgGraphicsContextClear;

    uint function(void** viewport, void* context) sgGraphicsViewportCreate;
    //uint function(void** viewport, void* context, uint wx, uint wy, uint wwidth, uint wheight, float x, float y, float width, float height) sgGraphicsViewportCreateView;
    uint function(void* viewport) sgGraphicsViewportDestroy;
    uint function(void* viewport, uint wx, uint wy, uint wwidth, uint wheight, float x, float y, float width, float height) sgGraphicsViewportSetView;
    //uint function(void* viewport, uint* wx, uint* wy, uint* wwidth, uint* wheight, float* x, float* y, float* width, float* height) sgGraphicsViewportGetView;

    uint function(void** surface, void* context) sgGraphicsSurfaceCreate;
    //uint function(void** surface, void* context, void* texture) sgGraphicsSurfaceCreateTexture;
    //uint function(void** surface, void* context, uint width, uint height, ubyte bpp, void* data) sgGraphicsSurfaceCreateData;
    uint function(void* surface) sgGraphicsSurfaceDestroy;
    uint function(void* surface, void* texture) sgGraphicsSurfaceSetTexture;
    uint function(void* surface, void** texture) sgGraphicsSurfaceGetTexture;
    uint function(void* surface, uint width, uint height, ubyte bpp, void* data) sgGraphicsSurfaceSetData;
    //uint function(void* surface, uint* width, uint* height, ubyte* bpp, void** data) sgGraphicsSurfaceGetData;
    //uint function(void* surface, void* data) sgGraphicsSurfaceFreeData;
    uint function(void* surface, uint* width, uint* height) sgGraphicsSurfaceGetSize;
    uint function(void* surface, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle) sgGraphicsSurfaceDraw;
    uint function(void* surface) sgGraphicsSurfaceSetTarget;
    //uint function(void** surface) sgGraphicsSurfaceGetTarget;
    uint function(void* surface) sgGraphicsSurfaceResetTarget;

    uint function(void** texture, void* context) sgGraphicsTextureCreate;
    //uint function(void** texture, void* context, uint width, uint height, ubyte bpp, void* data) sgGraphicsTextureCreateData;
    uint function(void* texture) sgGraphicsTextureDestroy;
    uint function(void* texture, uint width, uint height, ubyte bpp, void* data) sgGraphicsTextureSetData;
    //uint function(void* texture, uint* width, uint* height, ubyte* bpp, void** data) sgGraphicsTextureGetData;
    //uint function(void* data) sgGraphicsTextureFreeData;
    uint function(void* texture, uint* width, uint* height) sgGraphicsTextureGetSize;
    uint function(void* texture, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle) sgGraphicsTextureDraw;

    uint function(void* context, void* texture, uint type, uint numverts, float* points, float* texcoords, float* colors) sgGraphicsDrawPrimitive;
    uint function(void* context, float size) sgGraphicsDrawPointSetSize;
    //uint function(void* context, float* size) sgGraphicsDrawPointGetSize;
    uint function(void* context, float size) sgGraphicsDrawLineSetWidth;
    //uint function(void* context, float* size) sgGraphicsDrawLineGetWidth;
    //uint function(void* context, uint factor, uint pattern) sgGraphicsDrawLineSetStipple;
    //uint function(void* context, uint* factor, uint* pattern) sgGraphicsDrawLineGetStipple;
    //uint function(void* context, SGubyte* pattern) sgGraphicsDrawPolygonSetStipple;
    //uint function(void* context*, SGubyte** pattern) sgGraphicsDrawPolygonGetStipple;

    /// Graphics Load
    uint function(char* fname, uint* width, uint* height, ubyte* bpp, void** data) sgGraphicsLoadFile;
    //uint function(void* stream, uint* width, uint* height, ubyte* bpp, void** data) sgGraphicsLoadStream;
    uint function(void* data) sgGraphicsLoadFreeData;
}

bool load(char[] fname, out uint width, out uint height, out ubyte bpp, out ubyte[] data)
{
    void* cdata;
    uint ret;
    if(sgGraphicsLoadFile !is null)
        ret = sgGraphicsLoadFile(toStringz(fname), &width, &height, &bpp, &cdata);
    else
        return false;
    data = cast(ubyte[])cdata[0..width*height*bpp].dup;
    if(sgGraphicsLoadFreeData !is null)
        sgGraphicsLoadFreeData(cdata);
    if(ret != 0)
        return false;
    //data = toCanvasSize(data, width, height, bpp, flipData);
    bpp *= 8;
    return true;
}

ubyte[] toCanvasSize(ubyte[] data, uint width, uint height, uint bypp)
{
    uint awidth = higherPower(width);
    uint aheight = higherPower(height);
    if(awidth == width && aheight == height)
        return data;

    ubyte[] newData = new ubyte[](bypp * awidth * aheight);
    uint x, y;
    for(y = 0; y < height; y++)
    {
        for(x = 0; x < width; x++)
        {
            newData[bypp * (x+y*awidth)..bypp * (x+y*awidth)+bypp] = data[bypp * (x+y*width)..bypp * (x+y*width)+bypp].dup;
        }
    }

    return newData;
}

