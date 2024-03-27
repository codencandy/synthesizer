#include "CNC_Application.h"
#include "CNC_Synth.h"

void Load( Application* application )
{
    Synthesizer* synth = &application->m_synth;
    Osc*         osc   = &application->m_synth.m_osc;
    Env*         env   = &application->m_synth.m_env;

    // init synth
    // samples per 2PI = 44100 / hz
    synth->m_currentTime   = 0.0;
    synth->m_samplerate    = 44100.0;
    synth->m_timePerSample = 1.0 / synth->m_samplerate;
    synth->m_level         = 0.2;

    // init osc
    osc->m_freq           = 200.0f;
    osc->m_phaseOffset    = 0.0f;
    osc->m_phase          = 0.0f;
    osc->m_phaseIncrement = (2.0f * M_PI) / (synth->m_samplerate / osc->m_freq); 

    // init env
    env->m_attackTime     = 0.2f;
    env->m_decayTime      = env->m_attackTime  + 0.2f;
    env->m_sustainTime    = env->m_decayTime   + 0.2f;    
    env->m_releaseTime    = env->m_sustainTime + 0.2f;
    
    env->m_attackLevel    = 0.8f;
    env->m_decayLevel     = 0.5f;
    
}

void Update( Application* application )
{

}

void Render( Application* application )
{

}

void RenderSound( SoundBuffer* soundBuffer, void* applicationContext )
{
    Application* app   = (Application*)applicationContext;
    Synthesizer* synth = &app->m_synth;

    f32* left  = (f32*)soundBuffer->m_buffer[0];
    f32* right = (f32*)soundBuffer->m_buffer[1];
    f32 sample = 0.0f;

    for( u32 i=0; i<soundBuffer->m_numberOfSamples; ++i )
    {
        sample = mixSample( &synth->m_osc, &synth->m_env, synth->m_currentTime );
        *left++  = sample * synth->m_level;
        *right++ = sample * synth->m_level;

        synth->m_currentTime += synth->m_timePerSample;
    }
    
    if( synth->m_env.m_plotIndex < 200 )
    {
        synth->m_env.m_plotLevels[synth->m_env.m_plotIndex++] = synth->m_env.m_level;
    }
}

void Exit( Application* application )
{

}
