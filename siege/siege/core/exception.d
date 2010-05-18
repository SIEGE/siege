module siege.core.exception;

class SiegeException: Exception
{
    this(char[] str)
    {
        super(str);
    }
}

class CoreException: SiegeException
{
    this(char[] str)
    {
        super(str);
    }
}

class LoadException: CoreException
{
    this(char[] str)
    {
        super(str);
    }
}
class UnloadException: CoreException
{
    this(char[] str)
    {
        super(str);
    }
}
class InitException: CoreException
{
    this(char[] str)
    {
        super(str);
    }
}
class UninitException: CoreException
{
    this(char[] str)
    {
        super(str);
    }
}

class WindowException: CoreException
{
    this(char[] str)
    {
        super(str);
    }
}

class DrawException: SiegeException
{
    this(char[] str)
    {
        super(str);
    }
}

class UnderflowException: SiegeException
{
    this(char[] str)
    {
        super(str);
    }
}

class QueueUnderflowException: UnderflowException
{
    this()
    {
        super("Queue underflow");
    }
}

class StackUnderflowException: UnderflowException
{
    this()
    {
        super("Stack underflow");
    }
}
