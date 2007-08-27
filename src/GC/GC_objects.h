#ifndef _GC_objects_h
#define _GC_objects_h

namespace GC
{
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
        cObject object;

        object.id = gObjectID;
        object.sprite = &gSpriteArray[sprite];
        object.parent = &gObjectArray[parent];

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
}

#endif
