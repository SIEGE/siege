#define SG_BUILD_LIBRARY
#include <siege/modules/modules.h>
#include <siege/modules/input.h>

void SG_EXPORT _sgModuleLoadInput(SGLibrary* lib)
{
    void* fptr;
    /// Input - Joystick
    _SG_BINDS(_sg_modInput, sgmCoreJoystickGetNumJoysticks);
    _SG_BINDS(_sg_modInput, sgmCoreJoystickCreate);
    _SG_BINDS(_sg_modInput, sgmCoreJoystickDestroy);
    _SG_BINDS(_sg_modInput, sgmCoreJoystickGetID);
    _SG_BINDS(_sg_modInput, sgmCoreJoystickGetNumButtons);
    //_SG_BINDS(_sg_modInput, sgmCoreJoystickSetButtons);
    _SG_BINDS(_sg_modInput, sgmCoreJoystickGetButtons);
    _SG_BINDS(_sg_modInput, sgmCoreJoystickGetNumAxis);
    //_SG_BINDS(_sg_modInput, sgmCoreJoystickSetAxis);
    _SG_BINDS(_sg_modInput, sgmCoreJoystickGetAxis);

    _SG_BINDS(_sg_modInput, sgmCoreJoystickSetCallbacks);
    //_SG_BINDS(_sg_modInput, sgmCoreJoystickGetCallbacks);

    /// Input - Keyboard
    _SG_BINDS(_sg_modInput, sgmCoreKeyboardCreate);
    _SG_BINDS(_sg_modInput, sgmCoreKeyboardDestroy);
    //_SG_BINDS(_sg_modInput, sgmCoreKeyboardSetKey);
    _SG_BINDS(_sg_modInput, sgmCoreKeyboardGetKey);
    //_SG_BINDS(_sg_modInput, sgmCoreKeyboardSetChr);
    //_SG_BINDS(_sg_modInput, sgmCoreKeyboardGetChr);

    _SG_BINDS(_sg_modInput, sgmCoreKeyboardSetCallbacks);
    //_SG_BINDS(_sg_modInput, sgmCoreKeyboardGetCallbacks);

    /// Input - Mouse
    _SG_BINDS(_sg_modInput, sgmCoreMouseCreate);
    _SG_BINDS(_sg_modInput, sgmCoreMouseDestroy);
    // should these two [sgmCoreMouseShow,sgmCoreMouseHide] be put into a single function?
    _SG_BINDS(_sg_modInput, sgmCoreMouseShow);
    _SG_BINDS(_sg_modInput, sgmCoreMouseHide);
    //_SG_BINDS(_sg_modInput, sgmCoreMouseIsShown);
    //_SG_BINDS(_sg_modInput, sgmCoreMouseIsHidden);
    _SG_BINDS(_sg_modInput, sgmCoreMouseGetNumButtons);
    //_SG_BINDS(_sg_modInput, sgmCoreMouseSetButtons);
    _SG_BINDS(_sg_modInput, sgmCoreMouseGetButtons);
    _SG_BINDS(_sg_modInput, sgmCoreMouseSetPosition);
    _SG_BINDS(_sg_modInput, sgmCoreMouseGetPosition);
    //_SG_BINDS(_sg_modInput, sgmCoreMouseSetWheel);
    _SG_BINDS(_sg_modInput, sgmCoreMouseGetWheel);

    _SG_BINDS(_sg_modInput, sgmCoreMouseSetCallbacks);
    //_SG_BINDS(_sg_modInput, sgmCoreMouseGetCallbacks);
}

SGModuleInput* SG_EXPORT sgModuleGetInput(void)
{
    return &_sg_modInput;
}
