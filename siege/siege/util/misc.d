module siege.util.misc;

private
{
    import std.math;
    import std.date: getUTCtime, TicksPerSecond;

    import siege.util.vector;
}

real time()
{
    return getUTCtime() / cast(real) TicksPerSecond;
}

/**
    Get the next higher (or equal) power of two number.
*/
uint higherPower(uint x)
{
    uint i = 2;
    while(i < x)
    {
        i <<= 1;
    }
    return i;
}
/**
    Get the next lower (or equal) power of two number.
*/
uint lowerPower(uint x)
{
    return higherPower(x) >> 1;
}

/**
    Converts a D array to a C array.
*/
T** toCArray(T, A)(T[][] arr, out A[] len)
{
    T*[] ptr;
    len.length = arr.length;
    ptr.length = arr.length;

    foreach(i, a; arr)
    {
        len[i] = a.length;
        ptr[i] = (a~cast(T)'\0').ptr;
    }

    return ptr.ptr;
}
/**
    Converts a C array to a D array
*/
T[][] fromCArray(T, A)(T** carr, A[] len)
{
    T[][] arr;
    arr.length = len.length;

    for(uint i = 0; i < len.length; i++)
    {
        arr[i] = carr[i][0..len[i]];
    }

    return arr;
}

/**
    Get the higher of two numbers.
*/
A max(A,B)(A one, B two)
{
    return (one > two) ? one : two;
}
/**
    Get the lower of two numbers.
*/
A min(A,B)(A one, B two)
{
    return (one < two) ? one : two;
}

/**
    Find the item in an array.

    Returns:
        The index of the item if found, -1 otherwise.
*/
int find(T)(T[] arr, T item)
{
    foreach(i, a; arr)
    {
        if(a == item)
            return i;
    }
    return -1;
}

/**
    Removes a member at index ind from the array.
*/
void remove(T)(inout T[] arr, size_t ind)
{
    arr = arr[0..ind] ~ arr[ind+1..$];
}

/**
    Sleep for some time.
    TODO
*/
/*void sleep(double seconds)
{
    double end = glfwGetTime() + seconds;

    while(glfwGetTime() < end)
    {}
}*/

/**
    Swap two values.
*/
void swap(T)(inout T one, inout T two)
{
    T temp = one;
    one = two;
    two = temp;
}

/**
    Swap three values, so that:
        one -> three
        two -> one
        three -> two
*/
void swap(T)(inout T one, inout T two, inout T three)
{
    T temp = one;
    one = two;
    two = three;
    three = temp;
}

/**
    Returns the angle difference, [-PI, PI)

    Returns:
        If a2 > a1 (counter-clockwise test), returns a counter-clockwise (positive) angle
        If a2 < a1 (counter-clockwise test), returns a clockwise (negative) angle
*/
float angleDiff(float a1, float a2)
{
    return -((a2 - a1 + PI) % (2*PI) - PI);
}

/**
    Convert a hexadecimal string into a number
*/
ulong fromHex(char[] str)
{
    if(str.length / 2.0 != floor(str.length / 2.0))
        return 0;

    uint ret;

    foreach(c; str)
    {
        if(inRange(c, '0', '9'))
        {
            ret <<= 1;
            ret |= c - '0';
        }
        else if(inRange(c, 'A', 'F'))
        {
            ret <<= 1;
            ret |= c - 'A';
        }
        else if(inRange(c, 'a', 'f'))
        {
            ret <<= 1;
            ret |= c - 'a';
        }
        else
        {
            break;
        }
    }

    return ret;
}

/**
    Returns true if num is in interval [min, max]

    Arguments:
        num: The number to test
        min: The start of the interval
        max: The end of the interval
        incMin: Should min be considered as inside of the interval?
        incMac: Should max be considered as inside of the interval?
*/
bool inRange(T)(T num, T min, T max, bool incMin = true, bool incMax = true)
{
    bool mn = incMin ? (num >= min) : (num > min);
    bool nm = incMax ? (num <= max) : (num < max);

    if(mn && nm)
        return true;
    return false;
}

/**
    Returns an intersection point between line segments (S) or lines (L), or a NaN vector if there is none.

    Source: http://local.wasp.uwa.edu.au/~pbourke/geometry/lineline2d/
*/
Vector intersectionSS(Vector p1, Vector p2, Vector p3, Vector p4)
{
    float ua;
    float ub;
    Vector i;

    ua = ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x))
             / ((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y));

    ub = ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x))
             / ((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y));

    if(!inRange(ua, 0.0f, 1.0f, true, true) || !inRange(ub, 0.0f, 1.0f, true, true))
        return Vector();

    i.x = p1.x + ua * (p2.x - p1.x);
    i.y = p1.y + ua * (p2.y - p1.y);

    return i;
}
/// ditto
Vector intersectionLL(Vector p1, Vector p2, Vector p3, Vector p4)
{
    float ua;
    float ub;
    Vector i;

    ua = ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x))
             / ((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y));

    ub = ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x))
             / ((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y));

    i.x = p1.x + ua * (p2.x - p1.x);
    i.y = p1.y + ua * (p2.y - p1.y);

    return i;
}
/// ditto
Vector intersectionSL(Vector p1, Vector p2, Vector p3, Vector p4)
{
    float ua;
    float ub;
    Vector i;

    ua = ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x))
             / ((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y));

    ub = ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x))
             / ((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y));

    if(!inRange(ua, 0.0f, 1.0f, true, true))
        return Vector();

    i.x = p1.x + ua * (p2.x - p1.x);
    i.y = p1.y + ua * (p2.y - p1.y);

    return i;
}
/// ditto
Vector intersectionLS(Vector p1, Vector p2, Vector p3, Vector p4)
{
    float ua;
    float ub;
    Vector i;

    ua = ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x))
             / ((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y));

    ub = ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x))
             / ((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y));

    if(!inRange(ub, 0.0f, 1.0f, true, true))
        return Vector();

    i.x = p1.x + ua * (p2.x - p1.x);
    i.y = p1.y + ua * (p2.y - p1.y);

    return i;
}
