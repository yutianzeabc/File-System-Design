typedef enum Command
{
    CD      = 1,
    LS      = 2,
    MKDIR   = 11,
    RMDIR   = 12,
    CREATE  = 21,
    RM      = 22,
    OPEN    = 31,
    CLOSE   = 32,
    READ    = 41,
    WRITE   = 42,
    EXIT    = 0,
    UNKNOWN = -1,
} command;