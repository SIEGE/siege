module siege.modules.input;

private
{
    import derelict.util.loader;

    import siege.modules.modules;
}

enum: uint
{
    SG_JOYSTICK_BUTTON_NOCB = 0x01,
    SG_JOYSTICK_AXIS_NOCB   = 0x11,
}

enum: uint
{
    SD_KEYBOARD_KEY_UNKNOWN     = 0x000,
    SG_KEYBOARD_KEY_SPACE       = 0x020,
    SG_KEYBOARD_KEY_ESC         = 0x100,
    SG_KEYBOARD_KEY_F1          = 0x101,
    SG_KEYBOARD_KEY_F2          = 0x102,
    SG_KEYBOARD_KEY_F3          = 0x103,
    SG_KEYBOARD_KEY_F4          = 0x104,
    SG_KEYBOARD_KEY_F5          = 0x105,
    SG_KEYBOARD_KEY_F6          = 0x106,
    SG_KEYBOARD_KEY_F7          = 0x107,
    SG_KEYBOARD_KEY_F8          = 0x108,
    SG_KEYBOARD_KEY_F9          = 0x109,
    SG_KEYBOARD_KEY_F10         = 0x10A,
    SG_KEYBOARD_KEY_F11         = 0x10B,
    SG_KEYBOARD_KEY_F12         = 0x10C,
    SG_KEYBOARD_KEY_F13         = 0x10D,
    SG_KEYBOARD_KEY_F14         = 0x10E,
    SG_KEYBOARD_KEY_F15         = 0x10F,
    SG_KEYBOARD_KEY_F16         = 0x110,
    SG_KEYBOARD_KEY_F17         = 0x111,
    SG_KEYBOARD_KEY_F18         = 0x112,
    SG_KEYBOARD_KEY_F19         = 0x113,
    SG_KEYBOARD_KEY_F20         = 0x114,
    SG_KEYBOARD_KEY_F21         = 0x115,
    SG_KEYBOARD_KEY_F22         = 0x116,
    SG_KEYBOARD_KEY_F23         = 0x117,
    SG_KEYBOARD_KEY_F24         = 0x118,
    SG_KEYBOARD_KEY_F25         = 0x119,
    SG_KEYBOARD_KEY_UP          = 0x200,
    SG_KEYBOARD_KEY_DOWN        = 0x201,
    SG_KEYBOARD_KEY_LEFT        = 0x202,
    SG_KEYBOARD_KEY_RIGHT       = 0x203,
    SG_KEYBOARD_KEY_LSHIFT      = 0x210,
    SG_KEYBOARD_KEY_RSHIFT      = 0x211,
    SG_KEYBOARD_KEY_LCTRL       = 0x220,
    SG_KEYBOARD_KEY_RCTRL       = 0x221,
    SG_KEYBOARD_KEY_LALT        = 0x230,
    SG_KEYBOARD_KEY_RALT        = 0x231,
    SG_KEYBOARD_KEY_TAB         = 0x240,
    SG_KEYBOARD_KEY_ENTER       = 0x241,
    SG_KEYBOARD_KEY_BACKSPACE   = 0x242,
    SG_KEYBOARD_KEY_INSERT      = 0x250,
    SG_KEYBOARD_KEY_DELETE      = 0x251,
    SG_KEYBOARD_KEY_HOME        = 0x252,
    SG_KEYBOARD_KEY_END         = 0x253,
    SG_KEYBOARD_KEY_PAGEUP      = 0x254,
    SG_KEYBOARD_KEY_PAGEDOWN    = 0x255,
    SG_KEYBOARD_KEY_KP0         = 0x300,
    SG_KEYBOARD_KEY_KP1         = 0x301,
    SG_KEYBOARD_KEY_KP2         = 0x302,
    SG_KEYBOARD_KEY_KP3         = 0x303,
    SG_KEYBOARD_KEY_KP4         = 0x304,
    SG_KEYBOARD_KEY_KP5         = 0x305,
    SG_KEYBOARD_KEY_KP6         = 0x306,
    SG_KEYBOARD_KEY_KP7         = 0x307,
    SG_KEYBOARD_KEY_KP8         = 0x308,
    SG_KEYBOARD_KEY_KP9         = 0x309,
    SG_KEYBOARD_KEY_KP_ADD      = 0x310,
    SG_KEYBOARD_KEY_KP_SUBTRACT = 0x311,
    SG_KEYBOARD_KEY_KP_MULTIPLY = 0x312,
    SG_KEYBOARD_KEY_KP_DIVIDE   = 0x313,
    SG_KEYBOARD_KEY_KP_DECIMAL  = 0x314,
    SG_KEYBOARD_KEY_KP_EQUAL    = 0x315,
    SG_KEYBOARD_KEY_KP_ENTER    = 0x316,
}

void loadModuleInput(SharedLib lib)
{
    /// Input - Joystick
    checkBindFunc(sgCoreJoystickGetFlags)("sgCoreJoystickGetFlags", lib);
    checkBindFunc(sgCoreJoystickFreeFlags)("sgCoreJoystickFreeFlags", lib);

    checkBindFunc(sgCoreJoystickGetNumJoysticks)("sgCoreJoystickGetNumJoysticks", lib);
    checkBindFunc(sgCoreJoystickCreate)("sgCoreJoystickCreate", lib);
    checkBindFunc(sgCoreJoystickDestroy)("sgCoreJoystickDestroy", lib);
    checkBindFunc(sgCoreJoystickGetID)("sgCoreJoystickGetID", lib);
    checkBindFunc(sgCoreJoystickGetNumButtons)("sgCoreJoystickGetNumButtons", lib);
    //checkBindFunc(sgCoreJoystickSetButtons)("sgCoreJoystickButtonSetState", lib);
    checkBindFunc(sgCoreJoystickGetButtons)("sgCoreJoystickButtonGetState", lib);
    checkBindFunc(sgCoreJoystickGetNumAxis)("sgCoreJoystickGetNumAxis", lib);
    //checkBindFunc(sgCoreJoystickSetAxis)("sgCoreJoystickAxisSetPosition", lib);
    checkBindFunc(sgCoreJoystickGetAxis)("sgCoreJoystickAxisGetPosition", lib);

    checkBindFunc(sgCoreJoystickSetCallbacks)("sgCoreJoystickSetCallbacks", lib);
    //checkBindFunc(sgCoreJoystickGetCallbacks)("sgCoreJoystickGetCallbacks", lib);

    /// Input - Keyboard
    checkBindFunc(sgCoreKeyboardCreate)("sgCoreKeyboardCreate", lib);
    checkBindFunc(sgCoreKeyboardDestroy)("sgCoreKeyboardDestroy", lib);
    //checkBindFunc(sgCoreKeyboardSetKey)("sgCoreKeyboardSetKey", lib);
    checkBindFunc(sgCoreKeyboardGetKey)("sgCoreKeyboardGetKey", lib);
    //checkBindFunc(sgCoreKeyboardSetChr)("sgCoreKeyboardSetChr", lib);
    //checkBindFunc(sgCoreKeyboardGetChr)("sgCoreKeyboardGetChr", lib);

    checkBindFunc(sgCoreKeyboardSetCallbacks)("sgCoreKeyboardSetCallbacks", lib);
    //checkBindFunc(sgCoreKeyboardGetCallbacks)("sgCoreKeyboardGetCallbacks", lib);

    /// Input - Mouse
    checkBindFunc(sgCoreMouseCreate)("sgCoreMouseCreate", lib);
    checkBindFunc(sgCoreMouseDestroy)("sgCoreMouseDestroy", lib);
    // should these two [sgCoreMouseShow,sgCoreMouseHide] be put into a single function?
    checkBindFunc(sgCoreMouseShow)("sgCoreMouseShow", lib);
    checkBindFunc(sgCoreMouseHide)("sgCoreMouseHide", lib);
    //checkBindFunc(sgCoreMouseIsShown)("sgCoreMouseIsShown", lib);
    //checkBindFunc(sgCoreMouseIsHidden)("sgCoreMouseIsHidden", lib);
    checkBindFunc(sgCoreMouseGetNumButtons)("sgCoreMouseGetNumButtons", lib);
    //checkBindFunc(sgCoreMouseSetButtons)("sgCoreMouseButtonSetState", lib);
    checkBindFunc(sgCoreMouseGetButtons)("sgCoreMouseButtonGetState", lib);
    checkBindFunc(sgCoreMouseSetPosition)("sgCoreMouseSetPosition", lib);
    checkBindFunc(sgCoreMouseGetPosition)("sgCoreMouseGetPosition", lib);
    //checkBindFunc(sgCoreMouseSetWheel)("sgCoreMouseSetWheel", lib);
    checkBindFunc(sgCoreMouseGetWheel)("sgCoreMouseGetWheel", lib);

    checkBindFunc(sgCoreMouseSetCallbacks)("sgCoreMouseSetCallbacks", lib);
    //checkBindFunc(sgCoreMouseGetCallbacks)("sgCoreMouseGetCallbacks", lib);
}

extern(C)
{
    struct SGCoreJoystickCallbacks
    {
        void function(void* joystick, uint button, bool down)      button;
        //void function(void* joystick, bool* buttons)               button;
        //void function(void* joystick, uint axis, float position)   move;
        void function(void* joystick, float* axis)                 move;
    }

    struct SGCoreKeyboardCallbacks
    {
        void function(void* keyboard, uint key, bool down)  key;
        void function(void* keyboard, dchar chr, bool down) chr;
    }

    struct SGCoreMouseCallbacks
    {
        void function(void* mouse, uint button, bool action) button;
        void function(void* mouse, int x, int y)             move;
        void function(void* mouse, int w)                    wheel;
    }

    /// Input - Joystick
    uint function(uint** flags) sgCoreJoystickGetFlags;
    uint function(uint* flags) sgCoreJoystickFreeFlags;

    uint function(void* window, uint* numjoys) sgCoreJoystickGetNumJoysticks;
    uint function(void** joystick, void* window, uint id) sgCoreJoystickCreate;
    uint function(void* joystick) sgCoreJoystickDestroy;
    uint function(void* joystick, uint* id) sgCoreJoystickGetID;
    uint function(void* joystick, uint* numbuttons) sgCoreJoystickGetNumButtons;
    //uint function(void* joystick, bool* state) sgCoreJoystickSetButtons;
    uint function(void* joystick, bool* state) sgCoreJoystickGetButtons;
    uint function(void* joystick, uint* numaxis) sgCoreJoystickGetNumAxis;
    //uint function(void* joystick, float* position) sgCoreJoystickSetAxis;
    uint function(void* joystick, float* position) sgCoreJoystickGetAxis;

    uint function(void* joystick, SGCoreJoystickCallbacks* callbacks) sgCoreJoystickSetCallbacks;
    //uint function(void* joystick, SGCoreJoystickCallbacks** callbacks) sgCoreJoystickGetCallbacks;

    /// Input - Keyboard
    uint function(void** keyboard, void* window) sgCoreKeyboardCreate;
    uint function(void* keyboard) sgCoreKeyboardDestroy;
    //uint function(void* keyboard, uint key, bool down) sgCoreKeyboardSetKey;
    uint function(void* keyboard, uint key, bool* down) sgCoreKeyboardGetKey;
    //uint function(void* keyboard, uint chr, bool down) sgCoreKeyboardSetChr;
    //uint function(void* keyboard, dchar chr, bool* down) sgCoreKeyboardGetChr;

    uint function(void* keyboard, SGCoreKeyboardCallbacks* callbacks) sgCoreKeyboardSetCallbacks;
    //uint function(void* keyboard, SGCoreKeyboardCallbacks** callbacks) sgCoreKeyboardGetCallbacks;

    /// Input - Mouse
    uint function(void** mouse, void* window) sgCoreMouseCreate;
    uint function(void* mouse) sgCoreMouseDestroy;
    // should these two [sgCoreMouseShow,sgCoreMouseHide] be put into a single function?
    uint function(void* mouse) sgCoreMouseShow;
    uint function(void* mouse) sgCoreMouseHide;
    //uint function(void* mouse, bool* shown) sgCoreMouseIsShown;
    //uint function(void* mouse, bool* hidden) sgCoreMouseIsHidden;
    uint function(void* mouse, uint* numbuttons) sgCoreMouseGetNumButtons;
    //uint function(void* mouse, bool* state) sgCoreMouseSetButtons;
    uint function(void* mouse, bool* state) sgCoreMouseGetButtons;
    uint function(void* mouse, int x, int y) sgCoreMouseSetPosition;
    uint function(void* mouse, int* x, int* y) sgCoreMouseGetPosition;
    //uint function(void* mouse, int w) sgCoreMouseSetWheel;
    uint function(void* mouse, int* w) sgCoreMouseGetWheel;

    uint function(void* mouse, SGCoreMouseCallbacks* callbacks) sgCoreMouseSetCallbacks;
    //uint function(void* mouse, SGCoreMouseCallbacks** callbacks) sgCoreMouseGetCallbacks;
}
