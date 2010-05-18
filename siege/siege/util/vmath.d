module siege.util.vmath;

private
{
    import std.math;

    import siege.util.vector;
}
public import std.math;

/**
    Distance between two points defined by vectors: (a - b).length
*/
float distance(Vector a, Vector b)
{
    return (a - b).length;
}

/**
    Get the longer/shorter of two vectors
*/
Vector longer(Vector a, Vector b)
{
    return (a.length2 > b.length2) ? a : b;
}
/// ditto
Vector shorter(Vector a, Vector b)
{
    return (a.length2 < b.length2) ? a : b;
}

/**
    Get the per-component max/min of two vectors (not to be confused with longer/shorter)
*/
Vector max(Vector a, Vector b)
{
    return Vector((a.x > b.x) ? a.x : b.x,
                  (a.y > b.y) ? a.y : b.y,
                  (a.z > b.z) ? a.z : b.z,
                  (a.w > b.w) ? a.w : b.w);
}
/// ditto
Vector min(Vector a, Vector b)
{
    return Vector((a.x < b.x) ? a.x : b.x,
                  (a.y < b.y) ? a.y : b.y,
                  (a.z < b.z) ? a.z : b.z,
                  (a.w < b.w) ? a.w : b.w);
}

/**
    Per-component absolute of the vector
*/
Vector abs(Vector x)
{
    return Vector(std.math.abs(x.x), std.math.abs(x.y));
}
alias std.math.abs abs;

/**
    Per-component power of the vector
*/
Vector pow(Vector x, float n)
{
    return Vector(std.math.pow(x.x, n), std.math.pow(x.y, n));
}
/// ditto
Vector pow(Vector x, uint n)
{
    return Vector(std.math.pow(cast(real)x.x, n), std.math.pow(cast(real)x.y, n));
}
alias std.math.pow pow;

/**
    Get the dot product of two <N>D vectors (for dotN)
    Default 2
*/
alias dot2 dot;
/// ditto
float dot2(Vector a, Vector b)
{
    return a.x * b.x + a.y * b.y;
}
/// ditto
float dot3(Vector a, Vector b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
/// ditto
float dot4(Vector a, Vector b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

/**
    Get the cross product of two <N>D vectors (for crossN)
    Default 2 (returns only the Z component)
*/
alias cross2 cross;
/// ditto
float cross2(Vector a, Vector b)
{
    return a.x * b.y - a.y * b.x;
}
/// ditto
Vector cross3(Vector a, Vector b)
{
    Vector p;
	p.x = a.y * b.z - b.y * a.z;
	p.y = a.z * b.x - b.z * a.x;
	p.z = a.x * b.y - b.x * a.y;
	return p;
}
/**
    Dot product with 'a' rotated by 90 deg to the left - same as the Z of the cross product in this case

    Note: may be removed in the future
*/
deprecated alias cross perp;

/**
    "Normal" multiplication of two vectors (not per-component)
*/
Vector mul(Vector a, Vector b)
{
    return Vector(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

