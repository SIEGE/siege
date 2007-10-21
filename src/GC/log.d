module GC.log;

private import std.stream;

File fhandle;

    int LogOpen(char[] fname = "gamelog.log")
    {
        fhandle = new File(fname,FileMode.Out);
        return 1;
    }

    void LogClose()
    {
        fhandle.close();
    }

    void LogWrite(char[] text,int space = 0)
    {
        for(int i=0; i<space; i++)
        {
            fhandle.write(' ');
        }
        fhandle.write(text ~ "\n");
    }
