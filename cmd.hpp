//
// Created by 余天泽 on 2020/12/26.
//

#ifndef FILE_SYSTEM_DESIGN_FS_CMD
#define FILE_SYSTEM_DESIGN_FS_CMD

enum command
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
};

#endif