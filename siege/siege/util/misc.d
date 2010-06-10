/**
    \brief Miscellaneous utilities that don't belong anywhere else
    \todo Very messy - will have to clean up
*/
module siege.util.misc;

private
{
    import std.math;
    import std.date: getUTCtime, TicksPerSecond;

    import siege.util.vector;
}

/**
    \brief Get the current time
    \return The current time in seconds
    \todo Currently returns the UTC time - probably should return local time?
*/
real time()
{
    return getUTCtime() / cast(real) TicksPerSecond;
}

/**
    \brief Sleep for some time
    \param seconds The time to sleep for in seconds
*/
void sleep(double seconds)
{
    double end = time() + seconds;
    while(time() < end)
    {
    }
}

/// \brief Get the next higher (or equal) power of two number (smallest 2^n so that x <= 2^n)
uint higherPower(uint x)
{
    uint i = 2;
    while(i < x)
    {
        i <<= 1;
    }
    return i;
}
/// \brief Get the next higher (or equal) power of two number (smallest 2^n so that 2^n <= x)
uint lowerPower(uint x)
{
    return higherPower(x) >> 1;
}

/// \brief Converts a D 2D array to a C 2D array
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
/// \brief Converts a C array to a D array
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
    \brief Get the larger of two numbers
    \return The larger of two numbers casted to the first
*/
A max(A,B)(A one, B two)
{
    return (one > two) ? one : two;
}
/**
    \brief Get the smaller of two numbers
    \return The smaller of two numbers casted to the first
*/
A min(A,B)(A one, B two)
{
    return (one < two) ? one : two;
}

/**
    \brief Find an item in an array
    \param arr The array to search in
    \param item The item to search for
    \return The index of the item if found, -1 otherwise
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

/// \brief Removes a member at index ind from the array
void remove(T)(inout T[] arr, size_t ind)
{
    arr = arr[0..ind] ~ arr[ind+1..$];
}

/// \brief Swap two values with one another
void swap(T)(inout T one, inout T two)
{
    T temp = one;
    one = two;
    two = temp;
}

/**
    \brief Swap three values, so that:
        \li one -> three
        \li two -> one
        \li three -> two
*/
void swap(T)(inout T one, inout T two, inout T three)
{
    T temp = one;
    one = two;
    two = three;
    three = temp;
}

/**
    \brief Get the angle difference

    \return In radians:
        \li If a2 > a1 (counter-clockwise test), a counter-clockwise (positive) angle
        \li If a2 < a1 (counter-clockwise test), a clockwise (negative) angle
*/
float angleDiff(float a1, float a2)
{
    return -((a2 - a1 + PI) % (2*PI) - PI);
}

/// \brief Convert a hexadecimal string into a number
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
    \brief Test if num is in the range [min, max]
    \param num The number to test
    \param min The start of the interval
    \param max The end of the interval
    \param incMin Should min be considered as inside of the interval?
    \param incMax should max be considered as inside of the interval?
    \return true if it is, false otherwise
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
    \name Intersections
    \brief Get the intersection point between between line segments (S) or lines (L)
    \param p1 The first point of the first segment/line
    \param p2 The second point of the first segment/line
    \param p3 The first point of the second segment/line
    \param p4 The second point of the second segment/line
    \return The intersection point or a NaN vector if there is none
    \todo Intersection with rays
    \todo Move to a more appropriate location
*/
/* @{ */
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
/* @} */
