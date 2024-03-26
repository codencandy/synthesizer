#include "CNC_Synth.h"
#include <string.h>

void resetSynth( Synthesizer* synth )
{
    synth->m_currentTime     = 0.0;
    synth->m_env.m_plotIndex = 0;
    memset( synth->m_env.m_plotLevels, 0, sizeof( f32 ) * 200 );
}

void changeVolume( Synthesizer* synth, f32 level )
{
    synth->m_level = level * 0.01f;
}

void changePitch( Synthesizer* synth, Osc* osc, f32 hz )
{
    osc->m_freq           = hz;
    osc->m_phaseIncrement = (2.0f * M_PI) / (synth->m_samplerate / osc->m_freq);
}

f32 oscSample( Osc* osc )
{
    f32 sample = sin( osc->m_phase );
    osc->m_phase += osc->m_phaseIncrement;

    if( osc->m_phase > (M_PI * 2.0) )  
    {
        osc->m_phase -= (M_PI * 2.0);
    }
    return sample;
}

f32 envLevel( Env* env, f64 time )
{
    if( time == 0.0 )
    {
        return 0.0f;
    }

    env->m_level = 0.0f;
    f32 factor = 0.0f;
    // linear change -> y = m*x + t

    // A 
    // time from 0 to attack time
    // level from 0 to attack level
    if( time < env->m_attackTime )
    {
        factor = (time / env->m_attackTime);
        env->m_level  = env->m_attackLevel * factor;
    }
    // D
    // time form attack time to decay time
    // level from attack level to decay level
    if( time > env->m_attackTime && time < env->m_decayTime )
    {
        f32 diff = env->m_attackLevel - env->m_decayLevel;
        factor = (time - env->m_attackTime) / env->m_decayTime;
        env->m_level  = env->m_attackLevel - (diff * factor);
    }
    // S
    // time from decay time to sustain time
    // level stays at decay level
    if( time > env->m_decayTime && time < env->m_sustainTime )
    {
        env->m_level = env->m_decayLevel;
    }
    // R
    // time from sustain time to release time
    // level from decay level to 0
    if( time > env->m_sustainTime && time < env->m_releaseTime )
    {
        factor = (time - env->m_attackTime - env->m_decayTime - env->m_sustainTime) / env->m_releaseTime;
        env->m_level  = env->m_decayLevel - ( env->m_decayLevel * factor);
    }

    return env->m_level;
}

f32 mixSample( Osc* osc, Env* env, f64 time )
{
    f32 newSample = oscSample( osc );
    newSample *= envLevel( env, time );
    
    return newSample;
}
