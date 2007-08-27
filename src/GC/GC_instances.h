#ifndef GC_instances_h
#define GC_instances_h

namespace GC
{
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

            // instance
            long instID;
            int x;
            int y;
    } ;

    cInstance NULL_INSTANCE;
    long gInstanceID = 0;
    cInstance gInstanceArray[255];

    long InstanceAdd(long object, int x = 0, int y = 0)
    {
        cInstance instance;

        instance.instID = gInstanceID;
        instance.x = x;
        instance.y = y;
        instance.objObject = &gObjectArray[object];
        instance.sprSprite = &gSpriteArray[gObjectArray[object].sprite->id];

        gInstanceArray[gInstanceID] = instance;

        gInstanceID++;

        return gInstanceID-1;
    }

    long InstanceRemove(long instance)
    {
        long id = gInstanceArray[instance].instID;
        gInstanceArray[instance].instID = -1;

        return id;
    }
}

#endif
