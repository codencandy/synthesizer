#ifndef CNC_APPLICATION_H
#define CNC_APPLICATION_H

#include "CNC_Types.h"
#include "CNC_Platform.h"
#include "CNC_Synth.h"

struct Application
{
    Platform    m_platform;
    Synthesizer m_synth;
};

// application services
void Load( Application* application );
void Update( Application* application );
void Render( Application* applicaiton );
void RenderSound( SoundBuffer* soundBuffer, void* applicationContext );
void Exit( Application* application );

#endif//CNC_APPLICATION_H
