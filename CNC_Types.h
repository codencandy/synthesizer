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

#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   500

struct VertexInput
{
    v3 m_position;
};

#endif//CNC_TYPES_H
