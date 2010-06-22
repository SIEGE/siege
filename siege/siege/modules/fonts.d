module siege.modules.fonts;

private
{
    import derelict.util.loader;

    import siege.modules.modules;
}

void loadModuleFonts(SharedLib lib)
{
    /// Fonts
    checkBindFunc(sgmFontsFaceCreate)("sgmFontsFaceCreate", lib);
    checkBindFunc(sgmFontsFaceDestroy)("sgmFontsFaceDestroy", lib);
    checkBindFunc(sgmFontsFaceSetHeight)("sgmFontsFaceSetHeight", lib);
    //checkBindFunc(sgmFontsFaceGetHeight)("sgmFontsFaceGetHeight", lib);
    checkBindFunc(sgmFontsCharsCreate)("sgmFontsCharsCreate", lib);
    checkBindFunc(sgmFontsCharsFreeData)("sgmFontsCharsFreeData", lib);
}

extern(C)
{
    /// Fonts
    uint function(void** face, char* fname)                                                                                                                          sgmFontsFaceCreate;
    uint function(void* face)                                                                                                                                        sgmFontsFaceDestroy;
    uint function(void* face, float height)                                                                                                                          sgmFontsFaceSetHeight;
    //uint function(void* face, float* height)                                                                                                                         sgmFontsFaceGetHeight;
    uint function(void* face,
                dchar* chars, uint charnum,
                float* width, float* height,
                float* prex, float* prey,
                float* postx, float* posty,
                uint* datawidth, uint* dataheight, void** data) sgmFontsCharsCreate;
    uint function(void* data) sgmFontsCharsFreeData;
}
