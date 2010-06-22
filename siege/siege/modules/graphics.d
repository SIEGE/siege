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
    checkBindFunc(sgmGraphicsContextCreate)("sgmGraphicsContextCreate", lib);
    checkBindFunc(sgmGraphicsContextDestroy)("sgmGraphicsContextDestroy", lib);
    checkBindFunc(sgmGraphicsContextResize)("sgmGraphicsContextResize", lib);
    checkBindFunc(sgmGraphicsContextClear)("sgmGraphicsContextClear", lib);

    checkBindFunc(sgmGraphicsViewportCreate)("sgmGraphicsViewportCreate", lib);
    //checkBindFunc(sgmGraphicsViewportCreateView)("sgmGraphicsViewportCreateView", lib);
    checkBindFunc(sgmGraphicsViewportDestroy)("sgmGraphicsViewportDestroy", lib);
    checkBindFunc(sgmGraphicsViewportSetView)("sgmGraphicsViewportSetView", lib);
    //checkBindFunc(sgmGraphicsViewportGetView)("sgmGraphicsViewportGetView", lib);

    checkBindFunc(sgmGraphicsSurfaceCreate)("sgmGraphicsSurfaceCreate", lib);
    //checkBindFunc(sgmGraphicsSurfaceCreateTexture)("sgmGraphicsSurfaceCreateTexture", lib);
    //checkBindFunc(sgmGraphicsSurfaceCreateData)("sgmGraphicsSurfaceCreateData", lib);
    checkBindFunc(sgmGraphicsSurfaceDestroy)("sgmGraphicsSurfaceDestroy", lib);
    checkBindFunc(sgmGraphicsSurfaceSetTexture)("sgmGraphicsSurfaceSetTexture", lib);
    checkBindFunc(sgmGraphicsSurfaceGetTexture)("sgmGraphicsSurfaceGetTexture", lib);
    checkBindFunc(sgmGraphicsSurfaceSetData)("sgmGraphicsSurfaceSetData", lib);
    //checkBindFunc(sgmGraphicsSurfaceGetData)("sgmGraphicsSurfaceGetData", lib);
    //checkBindFunc(sgmGraphicsSurfaceFreeData)("sgmGraphicsSurfaceFreeData", lib);
    checkBindFunc(sgmGraphicsSurfaceGetSize)("sgmGraphicsSurfaceGetSize", lib);
    checkBindFunc(sgmGraphicsSurfaceDraw)("sgmGraphicsSurfaceDraw", lib);
    checkBindFunc(sgmGraphicsSurfaceSetTarget)("sgmGraphicsSurfaceSetTarget", lib);
    //checkBindFunc(sgmGraphicsSurfaceGetTarget)("sgmGraphicsSurfaceGetTarget", lib);
    checkBindFunc(sgmGraphicsSurfaceResetTarget)("sgmGraphicsSurfaceResetTarget", lib);

    checkBindFunc(sgmGraphicsTextureCreate)("sgmGraphicsTextureCreate", lib);
    //checkBindFunc(sgmGraphicsTextureCreateData)("sgmGraphicsTextureCreateData", lib);
    checkBindFunc(sgmGraphicsTextureDestroy)("sgmGraphicsTextureDestroy", lib);
    checkBindFunc(sgmGraphicsTextureSetData)("sgmGraphicsTextureSetData", lib);
    //checkBindFunc(sgmGraphicsTextureGetData)("sgmGraphicsTextureGetData", lib);
    //checkBindFunc(sgmGraphicsTextureFreeData)("sgmGraphicsTextureFreeData", lib);
    checkBindFunc(sgmGraphicsTextureGetSize)("sgmGraphicsTextureGetSize", lib);
    checkBindFunc(sgmGraphicsTextureDraw)("sgmGraphicsTextureDraw", lib);

    checkBindFunc(sgmGraphicsDrawPrimitive)("sgmGraphicsDrawPrimitive", lib);
    checkBindFunc(sgmGraphicsDrawSetColor)("sgmGraphicsDrawSetColor", lib);
    checkBindFunc(sgmGraphicsDrawPointSetSize)("sgmGraphicsDrawPointSetSize", lib);
    //checkBindFunc(sgmGraphicsDrawPointGetSize)("sgmGraphicsDrawPointGetSize", lib);
    checkBindFunc(sgmGraphicsDrawLineSetWidth)("sgmGraphicsDrawLineSetWidth", lib);
    //checkBindFunc(sgmGraphicsDrawLineGetWidth)("sgmGraphicsDrawLineGetWidth", lib);
    //checkBindFunc(sgmGraphicsDrawLineSetStipple)("sgmGraphicsDrawLineSetStipple", lib);
    //checkBindFunc(sgmGraphicsDrawLineGetStipple)("sgmGraphicsDrawLineGetStipple", lib);
    //checkBindFunc(sgmGraphicsDrawPolygonSetStipple)("sgmGraphicsDrawPolygonSetStipple", lib);
    //checkBindFunc(sgmGraphicsDrawPolygonGetStipple)("sgmGraphicsDrawPolygonGetStipple", lib);

    /// Graphics Load
    checkBindFunc(sgmGraphicsLoadFile)("sgmGraphicsLoadFile", lib);
    //checkBindFunc(sgmGraphicsLoadStream)("sgmGraphicsLoadStream", lib);
    checkBindFunc(sgmGraphicsLoadFreeData)("sgmGraphicsLoadFreeData", lib);
}

extern(C)
{
    /// Graphics
    uint function(void** context, uint width, uint height, uint bpp) sgmGraphicsContextCreate;
    uint function(void* context) sgmGraphicsContextDestroy;
    uint function(void* context, uint width, uint height) sgmGraphicsContextResize;
    uint function(void* context, float* color) sgmGraphicsContextClear;

    uint function(void** viewport, void* context) sgmGraphicsViewportCreate;
    //uint function(void** viewport, void* context, uint wx, uint wy, uint wwidth, uint wheight, float x, float y, float width, float height) sgmGraphicsViewportCreateView;
    uint function(void* viewport) sgmGraphicsViewportDestroy;
    uint function(void* viewport, uint wx, uint wy, uint wwidth, uint wheight, float x, float y, float width, float height) sgmGraphicsViewportSetView;
    //uint function(void* viewport, uint* wx, uint* wy, uint* wwidth, uint* wheight, float* x, float* y, float* width, float* height) sgmGraphicsViewportGetView;

    uint function(void** surface, void* context) sgmGraphicsSurfaceCreate;
    //uint function(void** surface, void* context, void* texture) sgmGraphicsSurfaceCreateTexture;
    //uint function(void** surface, void* context, uint width, uint height, uint bpp, void* data) sgmGraphicsSurfaceCreateData;
    uint function(void* surface) sgmGraphicsSurfaceDestroy;
    uint function(void* surface, void* texture) sgmGraphicsSurfaceSetTexture;
    uint function(void* surface, void** texture) sgmGraphicsSurfaceGetTexture;
    uint function(void* surface, uint width, uint height, uint bpp, void* data) sgmGraphicsSurfaceSetData;
    //uint function(void* surface, uint* width, uint* height, uint* bpp, void** data) sgmGraphicsSurfaceGetData;
    //uint function(void* surface, void* data) sgmGraphicsSurfaceFreeData;
    uint function(void* surface, uint* width, uint* height) sgmGraphicsSurfaceGetSize;
    uint function(void* surface, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle) sgmGraphicsSurfaceDraw;
    uint function(void* surface) sgmGraphicsSurfaceSetTarget;
    //uint function(void** surface) sgmGraphicsSurfaceGetTarget;
    uint function(void* surface) sgmGraphicsSurfaceResetTarget;

    uint function(void** texture, void* context) sgmGraphicsTextureCreate;
    //uint function(void** texture, void* context, uint width, uint height, uint bpp, void* data) sgmGraphicsTextureCreateData;
    uint function(void* texture) sgmGraphicsTextureDestroy;
    uint function(void* texture, uint width, uint height, uint bpp, void* data) sgmGraphicsTextureSetData;
    //uint function(void* texture, uint* width, uint* height, uint* bpp, void** data) sgmGraphicsTextureGetData;
    //uint function(void* data) sgmGraphicsTextureFreeData;
    uint function(void* texture, uint* width, uint* height) sgmGraphicsTextureGetSize;
    uint function(void* texture, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle) sgmGraphicsTextureDraw;

    uint function(void* context, void* texture, uint type, uint numverts, float* points, float* texcoords, float* colors) sgmGraphicsDrawPrimitive;
    uint function(void* context, float* color) sgmGraphicsDrawSetColor;
    uint function(void* context, float size) sgmGraphicsDrawPointSetSize;
    //uint function(void* context, float* size) sgmGraphicsDrawPointGetSize;
    uint function(void* context, float size) sgmGraphicsDrawLineSetWidth;
    //uint function(void* context, float* size) sgmGraphicsDrawLineGetWidth;
    //uint function(void* context, uint factor, uint pattern) sgmGraphicsDrawLineSetStipple;
    //uint function(void* context, uint* factor, uint* pattern) sgmGraphicsDrawLineGetStipple;
    //uint function(void* context, SGubyte* pattern) sgmGraphicsDrawPolygonSetStipple;
    //uint function(void* context*, SGubyte** pattern) sgmGraphicsDrawPolygonGetStipple;

    /// Graphics Load
    uint function(char* fname, uint* width, uint* height, uint* bpp, void** data) sgmGraphicsLoadFile;
    //uint function(void* stream, uint* width, uint* height, uint* bpp, void** data) sgmGraphicsLoadStream;
    uint function(void* data) sgmGraphicsLoadFreeData;
}

bool load(char[] fname, out uint width, out uint height, out uint bpp, out ubyte[] data)
{
    void* cdata;
    uint ret;
    if(sgmGraphicsLoadFile !is null)
        ret = sgmGraphicsLoadFile(toStringz(fname), &width, &height, &bpp, &cdata);
    else
        return false;
    data = cast(ubyte[])cdata[0..width*height*bpp/8].dup;
    if(sgmGraphicsLoadFreeData !is null)
        sgmGraphicsLoadFreeData(cdata);
    if(ret != 0)
        return false;
    //data = toCanvasSize(data, width, height, bpp, flipData);
    return true;
}

ubyte[] toCanvasSize(ubyte[] data, uint width, uint height, uint bypp)
{
    uint awidth = nextPower2(width);
    uint aheight = nextPower2(height);
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

