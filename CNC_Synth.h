#ifndef CNC_SYNTH_H
#define CNC_SYNTH_H

#include "CNC_Types.h"

struct Osc
{
    f32 m_phaseOffset;
    f32 m_phase;
    f32 m_phaseIncrement;
    f32 m_freq;
};

struct Env // ADSR
{
    f64 m_startTime;
    f32 m_attackLevel;
    f64 m_attackTime;
    f32 m_decayLevel;
    f64 m_decayTime;
    f32 m_sustainTime;
    f64 m_releaseTime;
};

struct Synthesizer
{
    Osc m_osc;
    Env m_env;
    
    f64 m_currentTime;
    
    f64 m_samplerate;
    f64 m_samplesPerMs;

    f32 m_level;
};

f32 oscSample( Osc* osc );
f32 envLevel( Env* env, f64 time );
f32 mixSample( Osc* osc, Env* env, f64 time );

#endif//CNC_SYNTH_H
