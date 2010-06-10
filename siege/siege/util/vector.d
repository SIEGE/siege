/**
    \brief Vectors
    \todo Should \ref siege.util.vmath "vmath" be auto-imported?
*/
module siege.util.vector;

private
{
    import std.math;
    import std.string;

    import siege.util.random;
}

/**
    \brief A 4-dimensional vector with floating point components
*/
struct Vector
{
    float x;
    float y;
    float z = 0;
    float w = 0;
    /// \name Aliases for color coordinates
    /* @{ */
    alias x r;
    alias y g;
    alias z b;
    alias w a;
    /* @} */
    /// \name Aliases for texture coordinates
    /* @{ */
    alias x s;
    alias y t;
    alias z q;
    alias w p;
    /* @} */
    /// \name Aliases for size/depth
    /* @{ */
    alias x width;
    alias y height;
    alias z depth;
    /* @} */

    /**
        \brief Is this vector a NaN?
        \return true if it is, false otherwise
    */
    bool isNan()
    {
        if(!(x == x) || !(y == y) || !(z == z) || !(w == w))
            return true;
        return false;
    }

    /// \brief Get the unit length vector of this vector.
    Vector normalize()
    {
        return Vector(x, y, z, w) / length;
    }

    /// \brief Get the string representation of the vector
    char[] toString()
    {
        char[] ret = std.string.toString(x);
        if(y == y)
        {
            ret ~= ","~std.string.toString(y);
            if(z == z)
            {
                ret ~= ","~std.string.toString(z);
                if(w == w)
                    ret ~= ","~std.string.toString(w);
            }
        }
        return ret;
    }

    /* @{ */
    /**
        \brief Get the angle of the vector
        \note Only x and y components used
        \return The angle in radians
    */
    float angle()
    {
        return -atan2(y, x);
    }
    /**
        \brief Set the angle of the vector
        \note Only x and y components used
        \param a angle in radians
    */
    void angle(float a)
    {
        /*
            expi(a) = cos(a) + i*sin(a)
            on most PCs, it is much faster than calculating them separately
        */
        cfloat i = expi(-a) * length();
        x = i.re;
        y = i.im;
    }
    /* @} */
    /* @{ */
    /**
        \brief Get the length of the vector
        \todo Only x and y components considered (should it be kept this way?)
    */
    float length()
    {
        return hypot(x, y);
        //return sqrt(x*x + y*y);
    }
    /**
        \brief Set the length of the vector
        \todo Only x and y components considered (should it be kept this way?)
    */
    void length(float l)
    {
        /*
            expi(a) = cos(a) + i*sin(a)
            on most PCs, it is much faster than calculating them separately
        */
        cfloat i = expi(angle()) * l;
        x = i.re;
        y = i.im;
    }

    /**
        \brief Square length of the vector
        \todo Only x and y components considered (should it be kept this way?)
    */
    float length2()
    {
        return x*x + y*y;
    }
    /* @} */

    /// \name Per-component operations on the vector
    /* @{ */
    Vector opPos()
    {
        return Vector(x, y, z, w);
    }
    Vector opNeg()
    {
        return Vector(-x, -y, -z, -w);
    }
    Vector opAdd(Vector v)
    {
        return Vector(x + v.x, y + v.y, z + v.z, w + v.w);
    }
    Vector opSub(Vector v)
    {
        return Vector(x - v.x, y - v.y, z - v.z, w - v.w);
    }
    Vector opMul(Vector v)
    {
        return Vector(x * v.x, y * v.y, z * v.z, w * v.w);
    }
    Vector opDiv(Vector v)
    {
        return Vector(x / v.x, y / v.y, z / v.z, w / v.w);
    }

    Vector opAdd(iVector v)
    {
        return Vector(x + v.x, y + v.y, z + v.z, w + v.w);
    }
    Vector opSub(iVector v)
    {
        return Vector(x - v.x, y - v.y, z - v.z, w - v.w);
    }
    Vector opMul(iVector v)
    {
        return Vector(x * v.x, y * v.y, z * v.z, w * v.w);
    }
    Vector opDiv(iVector v)
    {
        return Vector(x / v.x, y / v.y, z / v.z, w / v.w);
    }

    Vector opAddAssign(Vector v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;

        return *this;
    }
    Vector opSubAssign(Vector v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;

        return *this;
    }
    Vector opMulAssign(Vector v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;

        return *this;
    }
    Vector opDivAssign(Vector v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        w /= v.w;

        return *this;
    }

    Vector opAddAssign(iVector v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;

        return *this;
    }
    Vector opSubAssign(iVector v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;

        return *this;
    }
    Vector opMulAssign(iVector v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;

        return *this;
    }
    Vector opDivAssign(iVector v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        w /= v.w;

        return *this;
    }
    /* @} */

    /// \name Scalar operations on the vector
    /* @{ */
    Vector opAdd(float f)
    {
        return Vector(x + f, y + f, z + f, w + f);
    }
    Vector opAdd_r(float f)
    {
        return Vector(f + x, f + y, f + z, f + w);
    }
    Vector opSub(float f)
    {
        return Vector(x - f, y - f, z - f, w - f);
    }
    Vector opSub_r(float f)
    {
        return Vector(f - x, f - y, f - z, f - w);
    }
    Vector opMul(float f)
    {
        return Vector(x * f, y * f, z * f, w * f);
    }
    Vector opMul_r(float f)
    {
        return Vector(f * x, f * y, f * z, f * w);
    }
    Vector opDiv(float f)
    {
        return Vector(x / f, y / f, z / f, w / f);
    }
    Vector opDiv_r(float f)
    {
        return Vector(f / x, f / y, f / z, f / w);
    }

    Vector opAddAssign(float f)
    {
        x += f;
        y += f;
        z += f;
        w += f;

        return *this;
    }
    Vector opSubAssign(float f)
    {
        x -= f;
        y -= f;
        z -= f;
        w -= f;

        return *this;
    }
    Vector opMulAssign(float f)
    {
        x *= f;
        y *= f;
        z *= f;
        w *= f;

        return *this;
    }
    Vector opDivAssign(float f)
    {
        x /= f;
        y /= f;
        z /= f;
        w /= f;

        return *this;
    }
    /* @} */

    /**
        \name Randomization functions
        The result of these depends on the seed and index, which can be set with \ref siege.util.random.seed "siege.util.random.seed".
    */
    /* @{ */
    /// \brief Get a vector with each component in the interval [0.0, 1.0)
    static Vector rand()
    {
        return rand(0, 1);
    }
    /// \brief Get a vector with each component in the interval [0.0, max)
    static Vector rand(float max)
    {
        return rand(0, max);
    }
    /// \brief Get a vector with each component in the interval [min, max)
    static Vector rand(float min, float max)
    {
        float xx = (min + siege.util.random.rand() / cast(float)uint.max * (max - min));
        float yy = (min + siege.util.random.rand() / cast(float)uint.max * (max - min));
        float zz = (min + siege.util.random.rand() / cast(float)uint.max * (max - min));
        float ww = (min + siege.util.random.rand() / cast(float)uint.max * (max - min));

        return Vector(xx, yy, zz, ww);
    }
    /* @} */

    /// \brief Get a vector with all components float.nan
    static Vector nan()
    {
        return Vector(float.nan, float.nan, float.nan, float.nan);
    }
    /// \brief Get a vector with all components at positive infinity
    static Vector infinity()
    {
        return Vector(float.infinity, float.infinity, float.infinity, float.infinity);
    }
    /// \brief Get a vector with all components float.max
    static Vector max()
    {
        return Vector(float.max, float.max, float.max, float.max);
    }
    /// \brief Get a vector with all components float.min
    static Vector min()
    {
        return Vector(float.min, float.min, float.min, float.min);
    }
    /// \brief The initial value of a vector
    static alias nan init;
    /// \brief An alias for infinity
    static alias infinity inf;
}

/**
    \brief A 4-dimensional vector with integer point components
    \todo document
    \todo Should this be simply removed?
*/
struct iVector
{
    int x;
    int y;
    int z = 0;
    int w = 0;

    alias x r;
    alias y g;
    alias z b;
    alias w a;

    alias x s;
    alias y t;
    alias z q;
    alias w p;

    alias x width;
    alias y height;
    alias z depth;

    bool isNan()
    {
        if(!(x == x) || !(y == y) || !(z == z) || !(w == w))
            return true;
        return false;
    }

    float angle()
    {
        return -atan2(y, x);
    }
    void angle(float a)
    {
        /*
            expi(a) = cos(a) + i*sin(a)
            on most PCs, it is much faster than calculating them separately
        */
        cfloat i = expi(a) * length();
        x = cast(int)i.re;
        y = cast(int)i.im;
    }

    float length()
    {
        return hypot(x, y);
        //return sqrt(x*x + y*y);
    }
    void length(float l)
    {
        /*
            expi(a) = cos(a) + i*sin(a)
            on most PCs, it is much faster than calculating them separately
        */
        cfloat i = expi(angle()) * l;
        x = cast(int)i.re;
        y = cast(int)i.im;
    }

    float length2()
    {
        return x*x + y*y;
    }

    Vector opNeg()
    {
        return Vector(-x, -y, -z, -w);
    }
    Vector opAdd(Vector v)
    {
        return Vector(x + v.x, y + v.y, z + v.z, w + v.w);
    }

    Vector opSub(Vector v)
    {
        return Vector(x - v.x, y - v.y, z - v.z, w - v.w);
    }

    Vector opMul(Vector v)
    {
        return Vector(x * v.x, y * v.y, z * v.z, w * v.w);
    }

    Vector opDiv(Vector v)
    {
        return Vector(x / v.x, y / v.y, z / v.z, w / v.w);
    }


    iVector opAdd(iVector v)
    {
        return iVector(x + v.x, y + v.y, z + v.z, w + v.w);
    }

    iVector opSub(iVector v)
    {
        return iVector(x - v.x, y - v.y, z - v.z, w - v.w);
    }

    iVector opMul(iVector v)
    {
        return iVector(x * v.x, y * v.y, z * v.z, w * v.w);
    }

    iVector opDiv(iVector v)
    {
        return iVector(x / v.x, y / v.y, z / v.z, w / v.w);
    }

    /*
    Vector opAddAssign(Vector v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;

        return *this;
    }

    Vector opSubAssign(Vector v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;

        return *this;
    }

    Vector opMulAssign(Vector v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;

        return *this;
    }

    Vector opDivAssign(Vector v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        w /= v.w;

        return *this;
    }*/


    iVector opAddAssign(iVector v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;

        return *this;
    }

    iVector opSubAssign(iVector v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;

        return *this;
    }

    iVector opMulAssign(iVector v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;

        return *this;
    }

    iVector opDivAssign(iVector v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        w /= v.w;

        return *this;
    }

    Vector opAdd(float f)
    {
        return Vector(x + f, y + f, z + f, w + f);
    }

    Vector opAdd_r(float f)
    {
        return Vector(f + x, f + y, f + z, f + w);
    }

    Vector opSub(float f)
    {
        return Vector(x - f, y - f, z - f, w - f);
    }

    Vector opSub_r(float f)
    {
        return Vector(f - x, f - y, f - z, f - w);
    }

    Vector opMul(float f)
    {
        return Vector(x * f, y * f, z * f, w * f);
    }

    Vector opMul_r(float f)
    {
        return Vector(f * x, f * y, f * z, f * w);
    }

    Vector opDiv(float f)
    {
        return Vector(x / f, y / f, z / f, w / f);
    }

    Vector opDiv_r(float f)
    {
        return Vector(f / x, f / y, f / z, f / w);
    }

    /*
    Vector opAddAssign(float f)
    {
        x += f;
        y += f;
        z += f;
        w += f;

        return *this;
    }

    Vector opSubAssign(float f)
    {
        x -= f;
        y -= f;
        z -= f;
        w -= f;

        return *this;
    }

    Vector opMulAssign(float f)
    {
        x *= f;
        y *= f;
        z *= f;
        w *= f;

        return *this;
    }

    Vector opDivAssign(float f)
    {
        x /= f;
        y /= f;
        z /= f;
        w /= f;

        return *this;
    }*/

    iVector opAddAssign(int f)
    {
        x += f;
        y += f;
        z += f;
        w += f;

        return *this;
    }

    iVector opSubAssign(int f)
    {
        x -= f;
        y -= f;
        z -= f;
        w -= f;

        return *this;
    }

    iVector opMulAssign(int f)
    {
        x *= f;
        y *= f;
        z *= f;
        w *= f;

        return *this;
    }

    iVector opDivAssign(int f)
    {
        x /= f;
        y /= f;
        z /= f;
        w /= f;

        return *this;
    }

    /**
        Get the unit length vector of this vector.
    */
    Vector normalize()
    {
        return Vector(x, y, z, w) / length;
    }

    char[] toString()
    {
        char[] ret = std.string.toString(x);
        if(y == y)
        {
            ret ~= ","~std.string.toString(y);
            if(z == z)
            {
                ret ~= ","~std.string.toString(z);
                if(w == w)
                    ret ~= ","~std.string.toString(w);
            }
        }
        return ret;
    }

    iVector* ptr()
    {
        return this;
    }

    static iVector rand()
    {
        return rand(0, int.max);
    }

    static iVector rand(int max)
    {
        return rand(0, max);
    }

    static iVector rand(int min, int max)
    {
        int xx = cast(int)(min + siege.util.random.rand() / cast(float)uint.max * (max - min));
        int yy = cast(int)(min + siege.util.random.rand() / cast(float)uint.max * (max - min));
        int zz = cast(int)(min + siege.util.random.rand() / cast(float)uint.max * (max - min));
        int ww = cast(int)(min + siege.util.random.rand() / cast(float)uint.max * (max - min));

        return iVector(xx, yy, zz, ww);
    }

    static iVector init()
    {
        return iVector(0,0,0,0);
        //return Vector(float.nan, float.nan, float.nan, float.nan);
    }
    //static alias nan init;
    /*static Vector infinity()
    {
        assert(0);
        //return Vector(float.infinity, float.infinity, float.infinity, float.infinity);
    }
    static alias infinity inf;*/

    static iVector max()
    {
        return iVector(int.max, int.max, int.max, int.max);
    }
    static iVector min()
    {
        return iVector(int.min, int.min, int.min, int.min);
    }
}

