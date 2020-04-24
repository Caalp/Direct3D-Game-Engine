#include "TransformBufferVar.hlsl"



struct VertexIn
{
    float3 PosL : POSITION;
};

struct VertexOut
{
    float4 PosH : SV_Position;
    float3 PosL : POSITION;
};

VertexOut main(VertexIn vin)
{
    VertexOut vout;
    
    vout.PosH = mul(float4(vin.PosL, 1.0f), worldViewProj).xyww;
    
    vout.PosL = vin.PosL;
    return vout;
}