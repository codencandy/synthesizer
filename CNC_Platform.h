#ifndef CNC_PLATFORM_H
#define CNC_PLATFORM_H

// services the platform provides to the application
struct Platform
{
    void* m_audioService;
    void(*startPlayer)(void*);
    void(*stopPlayer)(void*);
};

void StartPlayer(void* audio);
void StopPlayer(void* audio);

#endif//CNC_PLATFORM_H
