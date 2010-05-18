module main;

import siege.siege;

import std.stdio;
import std.string;
import std.file;

import actors;

class Test: EventClient
{
    Polygon poly, poly2, poly3;
    Polygon[] mesh;
    Surface surf;
    Entity pacman;
    Music music;
    Font mouseFont;
    Font sansFont;
    Font serifFont;
    Font monoFont;
    Box[] boxes;
    Floor[] floor;
    UIContext context;
    SimpleStyle style;
    char[] command(char[] str)
    {
    	switch(tolower(str))
    	{
        	case "test":
            		return "TEST command executed";
            case "":
                    return "";
        	default:
            		return "unknown command!";
    	}
    	assert(0, "Something went horribly wrong in the switch statement");
    }

    void evStart()
    {
        poly = new Polygon(cast(Vector[])[]);

        poly2 = new Polygon(cast(Vector[])[Vector(200,2),Vector(220,50),Vector(270,80),Vector(300,70),Vector(310,65),Vector(280,33),Vector(275,31),Vector(210,12)]);

        mesh = poly2.toMesh();

        poly3 = new Polygon(cast(Vector[])[]);

        poly3 = poly2.dup;

        poly3.toConvex();

        poly3 = poly2.toDeMesh(mesh);

        std.random.rand_seed(0, 0);

        smpMusic = new Sample("Data/Audio/WagnerRideOfTheValkyries.ogg");
        smpBoom = new Sample("Data/Audio/boom.flac");

        music = new Music(smpMusic);
        sansFont = new Font("Data/Fonts/DejaVuLGCSans.ttf", "Data/Fonts/DejaVuLGCSans-Bold.ttf", "Data/Fonts/DejaVuLGCSans-Oblique.ttf", "Data/Fonts/DejaVuLGCSans-BoldOblique.ttf", 10, 256);
        serifFont = new Font("Data/Fonts/DejaVuLGCSerif.ttf", "Data/Fonts/DejaVuLGCSerif-Bold.ttf", "Data/Fonts/DejaVuLGCSerif-Italic.ttf", "Data/Fonts/DejaVuLGCSerif-BoldItalic.ttf", 10, 256);
        monoFont = new Font("Data/Fonts/DejaVuLGCSansMono.ttf", "Data/Fonts/DejaVuLGCSansMono-Bold.ttf", "Data/Fonts/DejaVuLGCSansMono-Oblique.ttf", "Data/Fonts/DejaVuLGCSansMono-BoldOblique.ttf", 10, 256);
        console.font = monoFont.resize(10, 256, true);
        mouseFont = monoFont.resize(8, 128);

        sprBox = new Sprite("Data/Sprites/CrateSmall.png");
        sprMetalBox = new Sprite("Data/Sprites/StrongboxSmall.png");
        sprFloor = new Sprite("Data/Sprites/FloorMetalPlate.png");
        sprSupport = new Sprite("Data/Sprites/SupportBar.png");
        sprHazard = new Sprite("Data/Sprites/HazardWall.png");

        pacman = new Entity(mouse.position.current, 0.0, new Sprite("Data/Sprites/Pacman.png"), null, false);

        surf = new Surface(640, 480, 24);
        surf.clear();

        surf.target();
            //draw.quad(64, 64, 256, 64, 256, 256, 64, 256);

            draw.begin(Primitive.Triangles);
                draw.color(1.0, 0.0, 0.0);
                draw.vertex(64, 64);

                draw.color(0.0, 1.0, 0.0);
                draw.vertex(256, 64);

                draw.color(0.0, 0.0, 1.0);
                draw.vertex(64, 256);
            draw.end();

            draw.line.width = 8;
            draw.line(0, 0, 640, 480);
            draw.line.width = 1;
        surf.untarget();

        music.play();

        for(uint i = 32; i < 640; i += 64)
        {
            floor ~= new Floor(sprFloor, Vector(i, 448));
        }
        for(uint i = 224; i < 448; i += 64)
        {
            floor ~= new Floor(sprSupport, Vector(i, 384));
        }
        for(uint i = 224; i < 448; i += 64)
        {
            floor ~= new Floor(sprHazard, Vector(i, 320));
        }

        console.command = &command;
        //console.autocomplete = &autocomplete;

        context = new UIContext(Style(Spacing(0, 0, 0, 0), Padding(0, 0, 0, 0), Color(0.9, 1.0, 0.9, 1.0), iVector(-1, -1), Background(), sansFont));

        style = new SimpleStyle(context, sansFont);
        context.defstyle.background.cbRedraw = &style.cbRedraw;

        Frame f = new Frame(context, null, iVector(16, 16), iVector(128, 128));

        Button b = new Button(context, f, iVector(0, 0), iVector(0, 0));
        b.text = "Hello, Button";
    }

    void evDraw()
    {
        draw.color(1.0, 1.0, 1.0, 1.0);
        surf.draw(Vector(0, 0));
        ///draw.blendFunc(BlendFunc.SrcAlpha, BlendFunc.OneMinusSrcAlpha);

        monoFont.style = FontStyle.None;
        monoFont.printT(Vector(0, 120), "Text!\nTesting for UTF:\nČŠŽ čšž ░▒▓\nNOTE: Might not work if the font does not support UTF");

        draw.color(1.0, 1.0, 0.0, 1.0);
        monoFont.style = FontStyle.Bold | FontStyle.Italic;
        monoFont.printCentered(window.size / 2, "String: %s\nFloat: %f\nHexadecimal: 0x%X", "hello, string", 0.51, 0xAABBCC);

        draw.color(1.0, 0.0, 0.0, 0.75);
        char[] str = mouseFont.strFormat("Mouse: %d,%d", mouse.position.current.x, mouse.position.current.y);
        mouseFont.printCentered(mouse.position.current.x - mouseFont.strSize(str).x / 2 - 16, mouse.position.current.y, str);

        poly.drawDBG();

        float inc=0.1;
        poly2.drawDBG(Vector(150,50,0),0,Color(1, 1, 1, 1));
        foreach(Polygon f; mesh)
        {
            f.drawDBG(Vector(150,130,0),0,Color(1-inc, 0.3, 0.3 , 1));
            inc+=0.1;
        }
        poly3.drawDBG(Vector(250,50,0),0,Color(1, 1, 1, 1));

        /*draw.line.width = 2;
        foreach(f; floor)
            f.drawDBG();
        foreach(b; boxes)
            b.drawDBG();
        draw.color(1.0, 1.0, 1.0, 1.0);
        draw.begin(Primitive.Points);
            draw.vertex(-1, -1);
        draw.end();
        draw.line.width = 1;*/
    }

    void evWindowClose()
    {
        printf("Window closed!\n");
    }

    void evMouseButtonLeftPressed()
    {
        //poly.points ~= Vector(mouse.position.current.x, mouse.position.current.y);

        //writefln(PolygonDict(poly.type));
        (new Source(smpBoom)).play();
    }

    void evMouseButtonMiddlePressed()
    {
        boxes ~= new MetalBox(Vector(mouse.position.current.x, mouse.position.current.y), 0.0);
    }

    void evMouseButtonRightPressed()
    {
        boxes ~= new Box(Vector(mouse.position.current.x, mouse.position.current.y), 0.0);
    }

    void evMouseMove(int x, int y)
    {
        window.title = format("SIEGE Window: %d,%d", x, y);
        if(pacman !is null)
            pacman.position = Vector(x, y);
    }

    void evMouseWheel(int w)
    {
        if(pacman !is null)
            pacman.angle = w * 5;
    }
}

int main(char[][] args)
{
    game = new Game;
    game.loadModule("SDL");
    game.loadModule("OpenGL");
    game.loadModule("DevIL");
    game.loadModule("OpenAL");
    game.loadModule("SndFile");
    game.loadModule("Freetype");
    game.loadModule("Chipmunk");
    game.init();
    new Test;
    game.run();
    game.deinit();

    return 0;
}
