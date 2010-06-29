module siege.modules.common;

private
{
    import derelict.util.loader;
}

struct CheckBinder(T)
{
    void opCall(char[] n, SharedLib lib)
    {
        void* pptr = *fptr;
        //if(*fptr is null)
        *fptr = Derelict_GetProc(lib, n); // first check new name
        if(*fptr is null)
            *fptr = pptr;
    }

    private void** fptr;
}
CheckBinder!(T) checkBindFunc(T)(inout T a)
{
    CheckBinder!(T) res;
    res.fptr = cast(void**)&a;
    return res;
}
