module siege.util.vector;

private
{
    import std.math;
    import std.string;

    import siege.util.random;
}

struct Vector
{
    float x;
    float y;
    float z = 0;
    float w = 0;

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

    /**
        Get the angle of the vector (in radians).

        Note: only x and y components used
    */
    float angle()
    {
        return atan2(y, x);
    }
    /**
        Set the angle of the vector (in radians).

        Note: only x and y components used
    */
    void angle(float a)
    {
        /*
            expi(a) = cos(a) + i*sin(a)
            on most PCs, it is much faster than calculating them separately
        */
        cfloat i = expi(a) * length();
        x = i.re;
        y = i.im;
    }

    /**
        Get the length of the vector.

        BUGS: only x and y components considered
    */
    float length()
    {
        return hypot(x, y);
        //return sqrt(x*x + y*y);
    }
    /**
        Set the length of the vector.

        BUGS: only x and y components considered
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
        Square length of the vector.

        BUGS: only x and y components considered
    */
    float length2()
    {
        return x*x + y*y;
    }

    /**
        -v, returns the same vector rotated for 180 deg.
    */
    Vector opNeg()
    {
        return Vector(-x, -y, -z, -w);
    }
    /**
        Per-component operations on the vector
    */
    Vector opAdd(Vector v)
    {
        return Vector(x + v.x, y + v.y, z + v.z, w + v.w);
    }
    /// ditto
    Vector opSub(Vector v)
    {
        return Vector(x - v.x, y - v.y, z - v.z, w - v.w);
    }
    /// ditto
    Vector opMul(Vector v)
    {
        return Vector(x * v.x, y * v.y, z * v.z, w * v.w);
    }
    /// ditto
    Vector opDiv(Vector v)
    {
        return Vector(x / v.x, y / v.y, z / v.z, w / v.w);
    }

    /// ditto
    Vector opAdd(iVector v)
    {
        return Vector(x + v.x, y + v.y, z + v.z, w + v.w);
    }
    /// ditto
    Vector opSub(iVector v)
    {
        return Vector(x - v.x, y - v.y, z - v.z, w - v.w);
    }
    /// ditto
    Vector opMul(iVector v)
    {
        return Vector(x * v.x, y * v.y, z * v.z, w * v.w);
    }
    /// ditto
    Vector opDiv(iVector v)
    {
        return Vector(x / v.x, y / v.y, z / v.z, w / v.w);
    }

    /// ditto
    Vector opAddAssign(Vector v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;

        return *this;
    }
    /// ditto
    Vector opSubAssign(Vector v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;

        return *this;
    }
    /// ditto
    Vector opMulAssign(Vector v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;

        return *this;
    }
    /// ditto
    Vector opDivAssign(Vector v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        w /= v.w;

        return *this;
    }

    /// ditto
    Vector opAddAssign(iVector v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;

        return *this;
    }
    /// ditto
    Vector opSubAssign(iVector v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;

        return *this;
    }
    /// ditto
    Vector opMulAssign(iVector v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;

        return *this;
    }
    /// ditto
    Vector opDivAssign(iVector v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        w /= v.w;

        return *this;
    }

    /**
        Scalar operations on the vector
    */
    Vector opAdd(float f)
    {
        return Vector(x + f, y + f, z + f, w + f);
    }
    /// ditto
    Vector opAdd_r(float f)
    {
        return Vector(f + x, f + y, f + z, f + w);
    }
    /// ditto
    Vector opSub(float f)
    {
        return Vector(x - f, y - f, z - f, w - f);
    }
    /// ditto
    Vector opSub_r(float f)
    {
        return Vector(f - x, f - y, f - z, f - w);
    }
    /// ditto
    Vector opMul(float f)
    {
        return Vector(x * f, y * f, z * f, w * f);
    }
    /// ditto
    Vector opMul_r(float f)
    {
        return Vector(f * x, f * y, f * z, f * w);
    }
    /// ditto
    Vector opDiv(float f)
    {
        return Vector(x / f, y / f, z / f, w / f);
    }
    /// ditto
    Vector opDiv_r(float f)
    {
        return Vector(f / x, f / y, f / z, f / w);
    }

    /// ditto
    Vector opAddAssign(float f)
    {
        x += f;
        y += f;
        z += f;
        w += f;

        return *this;
    }
    /// ditto
    Vector opSubAssign(float f)
    {
        x -= f;
        y -= f;
        z -= f;
        w -= f;

        return *this;
    }
    /// ditto
    Vector opMulAssign(float f)
    {
        x *= f;
        y *= f;
        z *= f;
        w *= f;

        return *this;
    }
    /// ditto
    Vector opDivAssign(float f)
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

    Vector* ptr()
    {
        return this;
    }

    /**
        Random functions.
            rand(): Returns a vector with each component in the interval [0.0, 1.0).
            rand(float max): Returns a vector with each component in the interval [0.0, max).
            rand(float min, float max): Returns a vector with each component in the interval [min, max).

        Notes:
            The result of this depends on the seed and index, which can be set with std.random.seed_rand(uint seed, uint index).
    */
    static Vector rand()
    {
        return rand(0, 1);
    }
    /// ditto
    static Vector rand(float max)
    {
        return rand(0, max);
    }
    /// ditto
    static Vector rand(float min, float max)
    {
        float xx = (min + siege.util.random.rand() / cast(float)uint.max * (max - min));
        float yy = (min + siege.util.random.rand() / cast(float)uint.max * (max - min));
        float zz = (min + siege.util.random.rand() / cast(float)uint.max * (max - min));
        float ww = (min + siege.util.random.rand() / cast(float)uint.max * (max - min));

        return Vector(xx, yy, zz, ww);
    }

    static Vector nan()
    {
        return Vector(float.nan, float.nan, float.nan, float.nan);
    }
    static alias nan init;
    static Vector infinity()
    {
        return Vector(float.infinity, float.infinity, float.infinity, float.infinity);
    }
    static alias infinity inf;

    static Vector max()
    {
        return Vector(float.max, float.max, float.max, float.max);
    }
    static Vector min()
    {
        return Vector(float.min, float.min, float.min, float.min);
    }
}

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

    /**
        Get the angle of the vector (in radians).

        Note: only x and y components used
    */
    float angle()
    {
        return atan2(y, x);
    }
    /**
        Set the angle of the vector (in radians).

        Note: only x and y components used
    */
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

    /**
        Get the length of the vector.

        BUGS: only x and y components considered
    */
    float length()
    {
        return hypot(x, y);
        //return sqrt(x*x + y*y);
    }
    /**
        Set the length of the vector.

        BUGS: only x and y components considered
    */
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

    /**
        Square length of the vector.

        BUGS: only x and y components considered
    */
    float length2()
    {
        return x*x + y*y;
    }

    /**
        -v, returns the same vector rotated for 180 deg.
    */
    Vector opNeg()
    {
        return Vector(-x, -y, -z, -w);
    }
    /**
        Per-component operations on the vector
    */
    Vector opAdd(Vector v)
    {
        return Vector(x + v.x, y + v.y, z + v.z, w + v.w);
    }
    /// ditto
    Vector opSub(Vector v)
    {
        return Vector(x - v.x, y - v.y, z - v.z, w - v.w);
    }
    /// ditto
    Vector opMul(Vector v)
    {
        return Vector(x * v.x, y * v.y, z * v.z, w * v.w);
    }
    /// ditto
    Vector opDiv(Vector v)
    {
        return Vector(x / v.x, y / v.y, z / v.z, w / v.w);
    }

    /// ditto
    iVector opAdd(iVector v)
    {
        return iVector(x + v.x, y + v.y, z + v.z, w + v.w);
    }
    /// ditto
    iVector opSub(iVector v)
    {
        return iVector(x - v.x, y - v.y, z - v.z, w - v.w);
    }
    /// ditto
    iVector opMul(iVector v)
    {
        return iVector(x * v.x, y * v.y, z * v.z, w * v.w);
    }
    /// ditto
    iVector opDiv(iVector v)
    {
        return iVector(x / v.x, y / v.y, z / v.z, w / v.w);
    }

    /*/// ditto
    Vector opAddAssign(Vector v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;

        return *this;
    }
    /// ditto
    Vector opSubAssign(Vector v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;

        return *this;
    }
    /// ditto
    Vector opMulAssign(Vector v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;

        return *this;
    }
    /// ditto
    Vector opDivAssign(Vector v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        w /= v.w;

        return *this;
    }*/

    /// ditto
    iVector opAddAssign(iVector v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;

        return *this;
    }
    /// ditto
    iVector opSubAssign(iVector v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;

        return *this;
    }
    /// ditto
    iVector opMulAssign(iVector v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;

        return *this;
    }
    /// ditto
    iVector opDivAssign(iVector v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        w /= v.w;

        return *this;
    }

    /**
        Scalar operations on the vector
    */
    Vector opAdd(float f)
    {
        return Vector(x + f, y + f, z + f, w + f);
    }
    /// ditto
    Vector opAdd_r(float f)
    {
        return Vector(f + x, f + y, f + z, f + w);
    }
    /// ditto
    Vector opSub(float f)
    {
        return Vector(x - f, y - f, z - f, w - f);
    }
    /// ditto
    Vector opSub_r(float f)
    {
        return Vector(f - x, f - y, f - z, f - w);
    }
    /// ditto
    Vector opMul(float f)
    {
        return Vector(x * f, y * f, z * f, w * f);
    }
    /// ditto
    Vector opMul_r(float f)
    {
        return Vector(f * x, f * y, f * z, f * w);
    }
    /// ditto
    Vector opDiv(float f)
    {
        return Vector(x / f, y / f, z / f, w / f);
    }
    /// ditto
    Vector opDiv_r(float f)
    {
        return Vector(f / x, f / y, f / z, f / w);
    }

    /*/// ditto
    Vector opAddAssign(float f)
    {
        x += f;
        y += f;
        z += f;
        w += f;

        return *this;
    }
    /// ditto
    Vector opSubAssign(float f)
    {
        x -= f;
        y -= f;
        z -= f;
        w -= f;

        return *this;
    }
    /// ditto
    Vector opMulAssign(float f)
    {
        x *= f;
        y *= f;
        z *= f;
        w *= f;

        return *this;
    }
    /// ditto
    Vector opDivAssign(float f)
    {
        x /= f;
        y /= f;
        z /= f;
        w /= f;

        return *this;
    }*/
    /// ditto
    iVector opAddAssign(int f)
    {
        x += f;
        y += f;
        z += f;
        w += f;

        return *this;
    }
    /// ditto
    iVector opSubAssign(int f)
    {
        x -= f;
        y -= f;
        z -= f;
        w -= f;

        return *this;
    }
    /// ditto
    iVector opMulAssign(int f)
    {
        x *= f;
        y *= f;
        z *= f;
        w *= f;

        return *this;
    }
    /// ditto
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

    /**
        Random functions.
            rand(): Returns a vector with each component in the interval [0.0, 1.0).
            rand(float max): Returns a vector with each component in the interval [0.0, max).
            rand(float min, float max): Returns a vector with each component in the interval [min, max).

        Notes:
            The result of this depends on the seed and index, which can be set with std.random.seed_rand(uint seed, uint index).
    */
    static iVector rand()
    {
        return rand(0, int.max);
    }
    /// ditto
    static iVector rand(int max)
    {
        return rand(0, max);
    }
    /// ditto
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

