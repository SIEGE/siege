module GC.objects;

private import GC.sprites;

    class cObject
    {
        public:
            long id;
            int layer;
            cSprite* sprite;
            cObject* parent;
    } ;

    cObject NULL_OBJECT;
    long gObjectID = 0;
    cObject gObjectArray[255];

    long ObjectAdd(long sprite = -1, long parent = -1)
    {
        cObject object = new cObject;
        object.id = gObjectID;

        if(sprite >= 0)
        {
            object.sprite = &gSpriteArray[sprite];
        }
        else
        {
            object.sprite = &NULL_SPRITE;
        }

        if(parent >= 0)
        {
            object.parent = &gObjectArray[parent];
        }
        else
        {
            object.parent = &NULL_OBJECT;
        }

        gObjectArray[gObjectID] = object;

        gObjectID++;

        return gObjectID-1;
    }

    long ObjectReplace(long object, long sprite = -1, long parent = -1)
    {
        //nothing just yet!
        return object;
    }

    long ObjectRemove(long object)
    {
        long id = gObjectArray[object].id;
        gObjectArray[object].id = -1;

        return id;
    }
