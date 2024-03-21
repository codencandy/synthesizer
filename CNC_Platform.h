#ifndef CNC_PLATFORM_H
#define CNC_PLATFORM_H

struct Platform
{
    void(*startPlayer)();
    void(*stopPlayer)();
};

#endif//CNC_PLATFORM_H
