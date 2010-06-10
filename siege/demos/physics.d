module demos.physics;

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

    import siege.physics.pbody;

    import std.math;
}

Sprite[char[]] sprites;

class Box: Entity
{
    this(Vector position, float angle)
    {
        this(sprites["CrateSmall"], position, angle, 1.0, 1.0, false);
    }

    this(Sprite spr, Vector position, float angle, float density = 1.0, float rotscale = 1.0, bool stat = false)
    {
        sprite = spr;

        BodyData data;
        data.position = position;
        data.angle = angle;
        data.density = density;
        data.rotscale = rotscale;
        data.stat = stat;

        super(data);
        //super(position, angle, spr, null, density, 0.25, 0.25, false, upright, false);
    }

    /*void evCollisionOneBegin(Entity other, CollisionPoint point)
    {
        if(point.velocity.length < 10.0)
            return;

        float pitch = 10.0;//log(point.velocity.length);
        float gain = std.math.log(point.velocity.length) / 30.0;

        Source snd = new Source(smpBoom, pitch, gain, false);
        snd.play();
    }*/
}

class MetalBox: Box
{
    this(Vector position, float angle)
    {
        this(sprites["StrongboxSmall"], position, angle, 2.5, 1.0);
    }
    this(Sprite spr, Vector position, float angle, float density = 2.5, float rotscale = 1.0)
    {
        super(spr, position, angle, density, rotscale, false);
    }
}

class Floor: Box
{
    this(Sprite spr, Vector position)
    {
        super(spr, position, 0.0, float.infinity, float.infinity, true);
    }
}

class PhysicsDemo: Demo
{
    Box[] boxes;
    Floor[] floor;
    this()
    {
        name = "Physics";
        brief = "SIEGE physics";
        description = "This demo shows SIEGE's ability for handling physics";
    }

    void evStart()
    {
        sprites["CrateSmall"] = new Sprite("Data/Sprites/CrateSmall.png");
        sprites["FloorMetalPlate"] = new Sprite("Data/Sprites/FloorMetalPlate.png");
        sprites["HazardWall"] = new Sprite("Data/Sprites/HazardWall.png");
        sprites["Pacman"] = new Sprite("Data/Sprites/Pacman.png");
        sprites["StrongboxSmall"] = new Sprite("Data/Sprites/StrongboxSmall.png");
        sprites["SupportBar"] = new Sprite("Data/Sprites/SupportBar.png");

        uint i;
        for(i = 32; i < 640; i += 64)
            floor ~= new Floor(sprites["FloorMetalPlate"], Vector(i, 448));
        for(i = 224; i < 448; i += 64)
            floor ~= new Floor(sprites["SupportBar"], Vector(i, 384));
        for(i = 224; i < 448; i += 64)
            floor ~= new Floor(sprites["HazardWall"], Vector(i, 320));
    }

    void evMouseButtonLeftPressed()
    {
        boxes ~= new MetalBox(Vector(mouse.position.current.x, mouse.position.current.y), 0.0);
    }

    void evMouseButtonRightPressed()
    {
        boxes ~= new Box(Vector(mouse.position.current.x, mouse.position.current.y), 0.0);
    }
}

static this()
{
    demoinfo ~= PhysicsDemo.classinfo;
}
