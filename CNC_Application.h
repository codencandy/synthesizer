#ifndef CNC_APPLICATION_H
#define CNC_APPLICATION_H

#include "CNC_Types.h"
#include "CNC_Platform.h"

struct Application
{
    Platform m_platform;
};

// application services
void Load( Application* application );
void Update( Application* application );
void Render( Application* applicaiton );
void RenderSound( f32* soundBuffer, u32 numberOfSamples );
void Exit( Application* application );

#endif//CNC_APPLICATION_H
