module siege.modules.fonts;

private
{
    import derelict.util.loader;

    import siege.modules.modules;
}

void loadModuleFonts(SharedLib lib)
{
    /// Fonts
    checkBindFunc(sgFontsFaceCreate)("sgmFontsFaceCreate", lib);
    checkBindFunc(sgFontsFaceDestroy)("sgmFontsFaceDestroy", lib);
    checkBindFunc(sgFontsFaceSetHeight)("sgmFontsFaceSetHeight", lib);
    //checkBindFunc(sgFontsFaceGetHeight)("sgmFontsFaceGetHeight", lib);
    checkBindFunc(sgFontsCharsCreate)("sgmFontsCharsCreate", lib);
    checkBindFunc(sgFontsCharsFreeData)("sgmFontsCharsFreeData", lib);
}

extern(C)
{
    /// Fonts
    uint function(void** face, char* fname)                                                                                                                          sgFontsFaceCreate;
    uint function(void* face)                                                                                                                                        sgFontsFaceDestroy;
    uint function(void* face, float height)                                                                                                                          sgFontsFaceSetHeight;
    //uint function(void* face, float* height)                                                                                                                         sgFontsFaceGetHeight;
    uint function(void* face,
                dchar* chars, uint charnum,
                float* width, float* height,
                float* prex, float* prey,
                float* postx, float* posty,
                uint* datawidth, uint* dataheight, void** data) sgFontsCharsCreate;
    uint function(void* data) sgFontsCharsFreeData;
}
