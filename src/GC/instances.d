module GC.instances;

//private import GC.sprites;
//private import GC.objects;
private import GC.GC;

    class cInstance
    {
        public:
            // sprites
            cSprite* sprSprite;
            short sprAngle;

            // object
            cObject* objObject;
            cObject* objParent;
            int layer;
            int alpha;

            // instance
            long id;
            int x;
            int y;
    } ;

    cInstance NULL_INSTANCE;
    long gInstanceID = 0;
    cInstance gInstanceArray[255];

    long InstanceAdd(long object, int x = 0, int y = 0)
    {
        cInstance instance = new cInstance;

        instance.id = gInstanceID;
        instance.x = x;
        instance.y = y;

        instance.layer = 0;
        instance.alpha = 1;
        instance.objObject = &gObjectArray[object];

        if(gObjectArray[object].sprite.id != NULL_SPRITE.id)
        {
            instance.sprSprite = &gSpriteArray[gObjectArray[object].sprite.id];
        }
        else
        {
            instance.sprSprite = &NULL_SPRITE;
        }

        gInstanceArray[gInstanceID] = instance;

        gInstanceID++;

        return gInstanceID-1;
    }

    long InstanceRemove(long instance)
    {
        long id = gInstanceArray[instance].id;
        gInstanceArray[instance].id = -1;

        return id;
    }
