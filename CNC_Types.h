#ifndef CNC_TYPES_H
#define CNC_TYPES_H

#include <simd/simd.h>

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char   u8;

typedef signed int     s32;
typedef signed short   s16;

typedef float          f32;
typedef double         f64;

typedef simd_float3     v3;
typedef simd_float4     v4;
typedef simd_float3x3   m3;
typedef simd_float4x4   m4;

#define WINDOW_WIDTH    1000
#define WINDOW_HEIGHT   600

struct VertexInput
{
    v3 m_position;
};

struct SoundBuffer
{
    u32   m_numberOfSamples;
    u32   m_numberOfChannels;
    f64   m_bufferTime;
    void* m_buffer[2];
};

#endif//CNC_TYPES_H
