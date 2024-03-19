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

vertex VertexOutput VertexShader( const device VertexInput* in      [[buffer(0)]],
                                  uint vertexId [[vertex_id]] )
{
    VertexOutput out = {0};
    out.m_position = float4( in[vertexId].m_position, 1.0 );
    return out;
}

fragment float4 FragmentShader( const VertexOutput in [[stage_in]] )
{
    float4 color = float4( 1.0 );
    return color;
}
