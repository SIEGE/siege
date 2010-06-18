module demos.sprite;

private
{
    import demos.common;

    import siege.core.entity;
    import siege.core.window;

    import siege.input.mouse;

    import siege.graphics.sprite;
    import siege.graphics.draw;

    import siege.util.color;
    import siege.util.vector;

    import std.math;
    import std.stdio;
}

class SpriteDemo: Demo
{
    Sprite[char[]] sprites;
    this()
    {
        name = "Sprites";
        brief = "SIEGE sprite handling";
        description = "This demo shows SIEGE's handling of sprites";
    }

    void evStart()
    {
        sprites["CrateSmall"] = new Sprite("Data/Sprites/CrateSmall.png");
        sprites["FloorMetalPlate"] = new Sprite("Data/Sprites/FloorMetalPlate.png");
        sprites["HazardWall"] = new Sprite("Data/Sprites/HazardWall.png");
        sprites["Pacman"] = new Sprite("Data/Sprites/Pacman.png");
        sprites["StrongboxSmall"] = new Sprite("Data/Sprites/StrongboxSmall.png");
        sprites["SupportBar"] = new Sprite("Data/Sprites/SupportBar.png");
    }

    void evDraw()
    {
        sprites["CrateSmall"].draw(64, 256, 0);
        sprites["StrongboxSmall"].draw(640 - 64, 256, 0);
        sprites["Pacman"].draw(320, 128, (mouse.position.current - Vector(320, 128)).angle() / PI * 180);

        uint i;
        for(i = 32; i < 640; i += 64)
            sprites["FloorMetalPlate"].draw(i, 448);
        for(i = 224; i < 448; i += 64)
            sprites["SupportBar"].draw(i, 384);
        for(i = 224; i < 448; i += 64)
            sprites["HazardWall"].draw(i, 320);
    }
}

static this()
{
    demoinfo ~= SpriteDemo.classinfo;
}
