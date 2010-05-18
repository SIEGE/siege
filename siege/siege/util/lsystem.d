module siege.util.lsystem;

private
{
    import siege.util.misc;
}

class LSystem
{
    void delegate(uint)[char] callbacks;

    char[][char] rules;
    char[] string;

    this(char[] string = "")
    {
        this.string = string;
    }

    void addRule(char start, char[] end)
    {
        rules[start] = end;
    }

    void addCallback(char c, void delegate(uint) callback)
    {
        callbacks[c] = callback;
    }

    char[] solve(uint iterations = 3)
    {
        char[] buffer1;
        char[] buffer2 = string.dup;

        for(uint i = 0; i < iterations; i++)
        {
            buffer1 = "";

            foreach(c; buffer2)
            {
                if(c in callbacks) // if a callback exists for the character
                {
                    //if(&callbacks[c] !is null) /// not required, but just to be safe...
                        callbacks[c](i);
                }

                if(c in rules) // if there is a rule for replacing the character...
                {
                    buffer1 ~= rules[c]; // then replace it, according to the rule
                }
                else
                {
                    buffer1 ~= c; // ...otherwise, it
                }
            }

            //writefln(buffer2);
            swap(buffer1, buffer2);
        }

        return buffer2;
    }
}
