module siege.core.error;

class SiegeError: Error
{
    this(char[] str)
    {
        super(str);
    }
}
