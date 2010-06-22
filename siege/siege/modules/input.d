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
    checkBindFunc(sgmCoreJoystickGetFlags)("sgmCoreJoystickGetFlags", lib);
    checkBindFunc(sgmCoreJoystickFreeFlags)("sgmCoreJoystickFreeFlags", lib);

    checkBindFunc(sgmCoreJoystickGetNumJoysticks)("sgmCoreJoystickGetNumJoysticks", lib);
    checkBindFunc(sgmCoreJoystickCreate)("sgmCoreJoystickCreate", lib);
    checkBindFunc(sgmCoreJoystickDestroy)("sgmCoreJoystickDestroy", lib);
    checkBindFunc(sgmCoreJoystickGetID)("sgmCoreJoystickGetID", lib);
    checkBindFunc(sgmCoreJoystickGetNumButtons)("sgmCoreJoystickGetNumButtons", lib);
    //checkBindFunc(sgmCoreJoystickSetButtons)("sgmCoreJoystickButtonSetState", lib);
    checkBindFunc(sgmCoreJoystickGetButtons)("sgmCoreJoystickButtonGetState", lib);
    checkBindFunc(sgmCoreJoystickGetNumAxis)("sgmCoreJoystickGetNumAxis", lib);
    //checkBindFunc(sgmCoreJoystickSetAxis)("sgmCoreJoystickAxisSetPosition", lib);
    checkBindFunc(sgmCoreJoystickGetAxis)("sgmCoreJoystickAxisGetPosition", lib);

    checkBindFunc(sgmCoreJoystickSetCallbacks)("sgmCoreJoystickSetCallbacks", lib);
    //checkBindFunc(sgmCoreJoystickGetCallbacks)("sgmCoreJoystickGetCallbacks", lib);

    /// Input - Keyboard
    checkBindFunc(sgmCoreKeyboardCreate)("sgmCoreKeyboardCreate", lib);
    checkBindFunc(sgmCoreKeyboardDestroy)("sgmCoreKeyboardDestroy", lib);
    //checkBindFunc(sgmCoreKeyboardSetKey)("sgmCoreKeyboardSetKey", lib);
    checkBindFunc(sgmCoreKeyboardGetKey)("sgmCoreKeyboardGetKey", lib);
    //checkBindFunc(sgmCoreKeyboardSetChr)("sgmCoreKeyboardSetChr", lib);
    //checkBindFunc(sgmCoreKeyboardGetChr)("sgmCoreKeyboardGetChr", lib);

    checkBindFunc(sgmCoreKeyboardSetCallbacks)("sgmCoreKeyboardSetCallbacks", lib);
    //checkBindFunc(sgmCoreKeyboardGetCallbacks)("sgmCoreKeyboardGetCallbacks", lib);

    /// Input - Mouse
    checkBindFunc(sgmCoreMouseCreate)("sgmCoreMouseCreate", lib);
    checkBindFunc(sgmCoreMouseDestroy)("sgmCoreMouseDestroy", lib);
    // should these two [sgmCoreMouseShow,sgmCoreMouseHide] be put into a single function?
    checkBindFunc(sgmCoreMouseShow)("sgmCoreMouseShow", lib);
    checkBindFunc(sgmCoreMouseHide)("sgmCoreMouseHide", lib);
    //checkBindFunc(sgmCoreMouseIsShown)("sgmCoreMouseIsShown", lib);
    //checkBindFunc(sgmCoreMouseIsHidden)("sgmCoreMouseIsHidden", lib);
    checkBindFunc(sgmCoreMouseGetNumButtons)("sgmCoreMouseGetNumButtons", lib);
    //checkBindFunc(sgmCoreMouseSetButtons)("sgmCoreMouseButtonSetState", lib);
    checkBindFunc(sgmCoreMouseGetButtons)("sgmCoreMouseButtonGetState", lib);
    checkBindFunc(sgmCoreMouseSetPosition)("sgmCoreMouseSetPosition", lib);
    checkBindFunc(sgmCoreMouseGetPosition)("sgmCoreMouseGetPosition", lib);
    //checkBindFunc(sgmCoreMouseSetWheel)("sgmCoreMouseSetWheel", lib);
    checkBindFunc(sgmCoreMouseGetWheel)("sgmCoreMouseGetWheel", lib);

    checkBindFunc(sgmCoreMouseSetCallbacks)("sgmCoreMouseSetCallbacks", lib);
    //checkBindFunc(sgmCoreMouseGetCallbacks)("sgmCoreMouseGetCallbacks", lib);
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
    uint function(uint** flags) sgmCoreJoystickGetFlags;
    uint function(uint* flags) sgmCoreJoystickFreeFlags;

    uint function(void* window, uint* numjoys) sgmCoreJoystickGetNumJoysticks;
    uint function(void** joystick, void* window, uint id) sgmCoreJoystickCreate;
    uint function(void* joystick) sgmCoreJoystickDestroy;
    uint function(void* joystick, uint* id) sgmCoreJoystickGetID;
    uint function(void* joystick, uint* numbuttons) sgmCoreJoystickGetNumButtons;
    //uint function(void* joystick, bool* state) sgmCoreJoystickSetButtons;
    uint function(void* joystick, bool* state) sgmCoreJoystickGetButtons;
    uint function(void* joystick, uint* numaxis) sgmCoreJoystickGetNumAxis;
    //uint function(void* joystick, float* position) sgmCoreJoystickSetAxis;
    uint function(void* joystick, float* position) sgmCoreJoystickGetAxis;

    uint function(void* joystick, SGCoreJoystickCallbacks* callbacks) sgmCoreJoystickSetCallbacks;
    //uint function(void* joystick, SGCoreJoystickCallbacks** callbacks) sgmCoreJoystickGetCallbacks;

    /// Input - Keyboard
    uint function(void** keyboard, void* window) sgmCoreKeyboardCreate;
    uint function(void* keyboard) sgmCoreKeyboardDestroy;
    //uint function(void* keyboard, uint key, bool down) sgmCoreKeyboardSetKey;
    uint function(void* keyboard, uint key, bool* down) sgmCoreKeyboardGetKey;
    //uint function(void* keyboard, uint chr, bool down) sgmCoreKeyboardSetChr;
    //uint function(void* keyboard, dchar chr, bool* down) sgmCoreKeyboardGetChr;

    uint function(void* keyboard, SGCoreKeyboardCallbacks* callbacks) sgmCoreKeyboardSetCallbacks;
    //uint function(void* keyboard, SGCoreKeyboardCallbacks** callbacks) sgmCoreKeyboardGetCallbacks;

    /// Input - Mouse
    uint function(void** mouse, void* window) sgmCoreMouseCreate;
    uint function(void* mouse) sgmCoreMouseDestroy;
    // should these two [sgmCoreMouseShow,sgmCoreMouseHide] be put into a single function?
    uint function(void* mouse) sgmCoreMouseShow;
    uint function(void* mouse) sgmCoreMouseHide;
    //uint function(void* mouse, bool* shown) sgmCoreMouseIsShown;
    //uint function(void* mouse, bool* hidden) sgmCoreMouseIsHidden;
    uint function(void* mouse, uint* numbuttons) sgmCoreMouseGetNumButtons;
    //uint function(void* mouse, bool* state) sgmCoreMouseSetButtons;
    uint function(void* mouse, bool* state) sgmCoreMouseGetButtons;
    uint function(void* mouse, int x, int y) sgmCoreMouseSetPosition;
    uint function(void* mouse, int* x, int* y) sgmCoreMouseGetPosition;
    //uint function(void* mouse, int w) sgmCoreMouseSetWheel;
    uint function(void* mouse, int* w) sgmCoreMouseGetWheel;

    uint function(void* mouse, SGCoreMouseCallbacks* callbacks) sgmCoreMouseSetCallbacks;
    //uint function(void* mouse, SGCoreMouseCallbacks** callbacks) sgmCoreMouseGetCallbacks;
}
