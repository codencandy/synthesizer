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

    f32 m_level;

    u32 m_plotIndex;
    f32 m_plotLevels[200];
};

struct Synthesizer
{
    Osc m_osc;
    Env m_env;
    
    f64 m_currentTime;
    
    f64 m_samplerate;
    f64 m_timePerSample;

    f32 m_level;
};

void resetSynth( Synthesizer* synth );
void changeVolume( Synthesizer* synth, f32 level );
void changePitch( Synthesizer* synth, Osc* osc, f32 hz );
void updateEnvelope( Env* env, f32 attack, f32 decay, f32 sustain, f32 release, f32 attackL, f32 decayL );
f32  oscSample( Osc* osc );
f32  envLevel( Env* env, f64 time );
f32  mixSample( Osc* osc, Env* env, f64 time );

#endif//CNC_SYNTH_H
