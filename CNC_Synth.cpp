#include "CNC_Synth.h"

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
    f32 level = 1.0f;

    // A 
    // time from 0 to attack time
    // level from 0 to attack level
    if( time < env->m_attackTime )
    {
        level = level * env->m_attackLevel;
    }
    // D
    // time form attack time to decay time
    // level from attack level to decay level
    if( time > env->m_attackTime && time < env->m_decayTime )
    {
        level = level * env->m_decayLevel;
    }
    // S
    // time from decay time to sustain time
    // level stays at decay level
    if( time > env->m_decayTime && time < env->m_sustainTime )
    {
        level = level * env->m_decayLevel;
    }
    // R
    // time from sustain time to release time
    // level from decay level to 0
    if( time > env->m_sustainTime && time < env->m_releaseTime )
    {
        level = level * env->m_decayLevel;
    }

    return level;
}

f32 mixSample( Osc* osc, Env* env, f64 time )
{
    f32 newSample = oscSample( osc );
    //newSample *= envLevel( env, time );

    return newSample;
}
