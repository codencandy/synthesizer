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

void updateEnvelope( Env* env, f32 attack, f32 decay, f32 sustain, f32 release, f32 attackL, f32 decayL )
{
    env->m_attackTime  = attack;
    env->m_attackLevel = attackL;
    env->m_decayTime   = attack + decay;
    env->m_decayLevel  = decayL;
    env->m_sustainTime = attack + decay + sustain;
    env->m_releaseTime = attack + decay + sustain + release;

    env->m_a = env->m_attackLevel / (env->m_attackTime * env->m_attackTime);

    f32 t    = (env->m_decayTime - env->m_attackTime);
    env->m_d = (env->m_attackLevel - env->m_decayLevel) / (t*t);

    f32 t1   = env->m_releaseTime - env->m_sustainTime;
    env->m_r = env->m_decayLevel / (t1 * t1);
}

inline f32 oscSample( Osc* osc )
{
    f32 sample = sin( osc->m_phase );
    osc->m_phase += osc->m_phaseIncrement;

    if( osc->m_phase > (M_PI * 2.0) )  
    {
        osc->m_phase -= (M_PI * 2.0);
    }
    return sample;
}

inline f32 envLevel( Env* env, f64 time )
{
    f32 t = 0.0f;

    if( time > env->m_releaseTime )
    {
        env->m_level = 0.0f;
        return 0.0f;
    }

    // RELEASE
    if( time > env->m_sustainTime )    
    {
        t = env->m_releaseTime - time;
        env->m_level = env->m_r * (t*t);
    }
    // SUSTAIN
    else if( time > env->m_decayTime )  
    {
        env->m_level = env->m_decayLevel;
    }
    // DECAY
    else if( time > env->m_attackTime ) 
    {
        t = (env->m_decayTime - time);
        env->m_level = env->m_d * (t*t) + env->m_decayLevel;
    }
    // ATTACK
    else  
    {
        env->m_level = env->m_a * (time * time);
    }

    return env->m_level;
}

inline f32 mixSample( Osc* osc, Env* env, f64 time )
{
    return (oscSample( osc ) * envLevel( env, time ) );
}
