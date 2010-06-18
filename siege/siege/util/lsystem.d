/**
    \brief A module for <a href="http://en.wikipedia.org/wiki/L-system">Lindenmayer Systems</a>
*/
module siege.util.lsystem;

private
{
    import siege.util.misc;
}

/**
    \brief A class which implements a <a href="http://en.wikipedia.org/wiki/L-system">L-System</a>
    \todo Optimize
*/
class LSystem
{
    /// \brief The callbacks which are called for each character, on each loop
    void delegate(uint)[char] callbacks;

    char[][char] rules;
    char[] string;

    /// \brief Initialize the L-System with a string
    this(char[] string = "")
    {
        this.string = string;
    }

    /**
        \brief Add a rule to the system, start->end
        \param start What to replace
        \param end The replacement for start
    */
    void addRule(char start, char[] end)
    {
        rules[start] = end;
    }

    /**
        \brief Add a callback for the system, called on each loop for each character
        \see callbacks
    */
    void addCallback(char c, void delegate(uint) callback)
    {
        callbacks[c] = callback;
    }

    /**
        \brief Solve the system
        \param iterations The number of iterations to run
        \return The final string
    */
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
