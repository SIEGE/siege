/**
    \brief Holds a class containing the whole level
    \todo to be done
*/
module siege.core.level;

private
{
    import siege.core.event;
}

class Level: EventClient
{
    bool persistent = false;

    void evLevelStart()
    {
    }
    void evLevelEnd()
    {
    }

    void reset()
    {
    }
}
