module siege.core.event;

private
{
    import siege.core.core;
    import siege.core.entity;

    import siege.util.linkedlist;

    import siege.physics.pbody: CollisionPoint, CollisionResult;
}

interface CoreEventClient
{
    // runs when game.run() is called
    void evStart();
    // just before closing down the program, just before game.run() exits
    void evExit();

    void evTick();
    void evTickBegin();
    void evTickEnd();

    void evDraw();
}
interface ModuleEventClient
{
    void evLoad();
    void evUnload();
    void evInit();
    void evUninit();
}

interface WindowEventClient
{
    void evWindowOpen();
    void evWindowClose();

    void evWindowResize(uint width, uint height);
}

interface MouseEventClient
{
    void evMouseButton(uint button, bool down);
    void evMouseButtonPressed(uint button);
    void evMouseButtonReleased(uint button);

    void evMouseButtonLeft(bool down);
    void evMouseButtonLeftPressed();
    void evMouseButtonLeftReleased();

    void evMouseButtonMiddle(bool down);
    void evMouseButtonMiddlePressed();
    void evMouseButtonMiddleReleased();

    void evMouseButtonRight(bool down);
    void evMouseButtonRightPressed();
    void evMouseButtonRightReleased();

    void evMouseMove(int x, int y);
    void evMouseWheel(int wheel);
}

interface KeyboardEventClient
{
    void evKeyboardKey(uint key, bool down);
    void evKeyboardKeyPressed(uint key);
    void evKeyboardKeyReleased(uint key);

    void evKeyboardChar(dchar chr, bool down);
    void evKeyboardCharPressed(dchar chr);
    void evKeyboardCharReleased(dchar chr);
}

interface JoystickEventClient
{
    void evJoystickButton(uint joy, uint button, bool down);
    void evJoystickButtonPressed(uint joy, uint button);
    void evJoystickButtonReleased(uint joy, uint button);

    void evJoystickMove(uint joy, float[] pos);
}

interface NetworkEventClient
{
    // TODO
}

interface PhysicsEventClient
{
    void evCollision(Entity other, CollisionPoint point);
    void evCollisionOne(Entity other, CollisionPoint point);
    void evCollisionTwo(Entity other, CollisionPoint point);

    void evCollisionBegin(Entity other, CollisionPoint point);
    void evCollisionOneBegin(Entity other, CollisionPoint point);
    void evCollisionTwoBegin(Entity other, CollisionPoint point);

    void evCollisionEnd(Entity other, CollisionPoint point);
    void evCollisionOneEnd(Entity other, CollisionPoint point);
    void evCollisionTwoEnd(Entity other, CollisionPoint point);

    void evCollisionResult(Entity other, CollisionResult result);
    void evCollisionOneResult(Entity other, CollisionResult result);
    void evCollisionTwoResult(Entity other, CollisionResult result);
}

interface LevelEventClient
{
    void evLevelStart();
    void evLevelEnd();
}

abstract class EventClient: CoreEventClient, ModuleEventClient, WindowEventClient, MouseEventClient, KeyboardEventClient, JoystickEventClient, NetworkEventClient, PhysicsEventClient, LevelEventClient
{
    LinkedNode!(EventClient) *node;

    this()
    {
        node = clientList.append(this);
    }
    ~this()
    {
        clientList.remove(node);
    }

    void evStart() {}
    void evExit() {}
    void evTick() {}
    void evTickBegin() {}
    void evTickEnd() {}
    void evDraw() {}

    void evLoad() {}
    void evUnload() {}
    void evInit() {}
    void evUninit() {}

    void evWindowOpen() {}
    void evWindowClose() {}
    void evWindowResize(uint width, uint height) {}

    void evMouseButton(uint button, bool down) {}
    void evMouseButtonPressed(uint button) {}
    void evMouseButtonReleased(uint button) {}
    void evMouseButtonLeft(bool down) {}
    void evMouseButtonLeftPressed() {}
    void evMouseButtonLeftReleased() {}
    void evMouseButtonMiddle(bool down) {}
    void evMouseButtonMiddlePressed() {}
    void evMouseButtonMiddleReleased() {}
    void evMouseButtonRight(bool down) {}
    void evMouseButtonRightPressed() {}
    void evMouseButtonRightReleased() {}
    void evMouseMove(int x, int y) {}
    void evMouseWheel(int wheel) {}

    void evKeyboardKey(uint key, bool down) {}
    void evKeyboardKeyPressed(uint key) {}
    void evKeyboardKeyReleased(uint key) {}
    void evKeyboardChar(dchar chr, bool down) {}
    void evKeyboardCharPressed(dchar chr) {}
    void evKeyboardCharReleased(dchar chr) {}

    void evJoystickButton(uint joy, uint button, bool down) {}
    void evJoystickButtonPressed(uint joy, uint button) {}
    void evJoystickButtonReleased(uint joy, uint button) {}
    void evJoystickMove(uint joy, float[] pos) {}

    void evCollision(Entity other, CollisionPoint point) {}
    void evCollisionOne(Entity other, CollisionPoint point) {}
    void evCollisionTwo(Entity other, CollisionPoint point) {}

    void evCollisionBegin(Entity other, CollisionPoint point) {}
    void evCollisionOneBegin(Entity other, CollisionPoint point) {}
    void evCollisionTwoBegin(Entity other, CollisionPoint point) {}

    void evCollisionEnd(Entity other, CollisionPoint point) {}
    void evCollisionOneEnd(Entity other, CollisionPoint point) {}
    void evCollisionTwoEnd(Entity other, CollisionPoint point) {}

    void evCollisionResult(Entity other, CollisionResult result) {}
    void evCollisionOneResult(Entity other, CollisionResult result) {}
    void evCollisionTwoResult(Entity other, CollisionResult result) {}

    void evLevelStart() {}
    void evLevelEnd() {}
}
