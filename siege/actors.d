module actors;

import siege.physics.pbody;
import siege.siege;

Sample smpBoom;
Sample smpMusic;

Sprite sprBox;
Sprite sprMetalBox;
Sprite sprFloor;
Sprite sprSupport;
Sprite sprHazard;

class Box: Entity
{
    this(Vector position, float angle)
    {
        this(sprBox, position, angle, 1.0, 1.0, false);
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

    void evCollisionOneBegin(Entity other, CollisionPoint point)
    {
        if(point.velocity.length < 10.0)
            return;

        float pitch = 10.0;//log(point.velocity.length);
        float gain = std.math.log(point.velocity.length) / 30.0;

        Source snd = new Source(smpBoom, pitch, gain, false);
        snd.play();
    }
}

class MetalBox: Box
{
    this(Vector position, float angle)
    {
        this(sprMetalBox, position, angle, 2.5, 1.0);
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
