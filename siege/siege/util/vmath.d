/**
    \brief Vector math
*/
module siege.util.vmath;

private
{
    import std.math;

    import siege.util.vector;
}
public import std.math;

/// \brief Get the distance between two points defined by vectors: (a - b).length
float distance(Vector a, Vector b)
{
    return (a - b).length;
}

/// \brief Get the longer of two vectors
Vector longer(Vector a, Vector b)
{
    return (a.length2 > b.length2) ? a : b;
}
/// \brief Get the shorter of two vectors
Vector shorter(Vector a, Vector b)
{
    return (a.length2 < b.length2) ? a : b;
}

/// \brief Get the per-component max of two vectors (not to be confused with longer)
Vector max(Vector a, Vector b)
{
    return Vector((a.x > b.x) ? a.x : b.x,
                  (a.y > b.y) ? a.y : b.y,
                  (a.z > b.z) ? a.z : b.z,
                  (a.w > b.w) ? a.w : b.w);
}
/// \brief Get the per-component min of two vectors (not to be confused with shorter)
Vector min(Vector a, Vector b)
{
    return Vector((a.x < b.x) ? a.x : b.x,
                  (a.y < b.y) ? a.y : b.y,
                  (a.z < b.z) ? a.z : b.z,
                  (a.w < b.w) ? a.w : b.w);
}

/// \brief Get the per-component absolute value of the vector (note to be confused with the mathematical notation for the length of a vector)
Vector abs(Vector x)
{
    return Vector(std.math.abs(x.x), std.math.abs(x.y));
}
/// \brief Aliases the math module's abs, so that it remains valid
alias std.math.abs abs;

/// \brief Get the per-component power of the vector
Vector pow(Vector x, float n)
{
    return Vector(std.math.pow(x.x, n), std.math.pow(x.y, n));
}
/// \brief Get the per-component power of the vector
Vector pow(Vector x, uint n)
{
    return Vector(std.math.pow(cast(real)x.x, n), std.math.pow(cast(real)x.y, n));
}
/// \brief Aliases the math module's pow, so that it remains valid
alias std.math.pow pow;

/// \brief An alias for two-dimensional dot product
alias dot2 dot;
/**
    \name Dot product
*/
/* @{ */
/// \brief Two-dimensional dot product of two vectors
float dot2(Vector a, Vector b)
{
    return a.x * b.x + a.y * b.y;
}
/// \brief Three-dimensional dot product of two vectors
float dot3(Vector a, Vector b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
/// \brief Four-dimensional dot product of two vectors
float dot4(Vector a, Vector b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
/* @} */

/// \brief An alias for two-dimensional cross product
alias cross2 cross;
/**
    \name Cross product
*/
/* @{ */
/**
    \brief Two-dimensional cross product of two vectors
    \return The Z component of the cross product [x1, y1, 0]x[x2, y2, 0]
*/
float cross2(Vector a, Vector b)
{
    return a.x * b.y - a.y * b.x;
}
/// \brief Three-dimensional cross product of two vectors
Vector cross3(Vector a, Vector b)
{
    Vector p;
	p.x = a.y * b.z - b.y * a.z;
	p.y = a.z * b.x - b.z * a.x;
	p.z = a.x * b.y - b.x * a.y;
	return p;
}
/* @} */

/**
    \brief "Normal" multiplication of two vectors (as opposed to per-component multiplication)
*/
Vector mul(Vector a, Vector b)
{
    return Vector(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

