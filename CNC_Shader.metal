#include <metal_stdlib>

using namespace metal;

struct VertexInput
{
    float3 m_position [[attribute(0)]];
};

struct VertexOutput
{
    float4 m_position [[position]];
};

vertex VertexOutput VertexShader( VertexInput in [[stage_in]] )
{
    VertexOutput out;
    return out;
}

fragment float4 FragmentShader( const VertexOutput in [[stage_in]] )
{
    float4 color;
    return color;
}
