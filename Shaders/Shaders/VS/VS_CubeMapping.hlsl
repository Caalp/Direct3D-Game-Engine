#include "..\Common\TransformBufferVar.hlsl"



struct VertexIn
{
    float3 PosL : Position;
};

struct VertexOut
{
    float4 PosH : SV_Position;
    float3 PosL : Position;
};

VertexOut main(VertexIn vin)
{
    VertexOut vout;
    
    vout.PosH = mul(float4(vin.PosL+eyePos, 1.0f), worldViewProj).xyww;
    
    vout.PosL = vin.PosL;
    return vout;
}