#include "TransformBufferVar.hlsl"

struct VertexIn
{
    float3 PosL : Position;
    float3 NormalL : Normal;
    float2 texCoordinate : TexCoord;
    row_major float4x4 World : World;
    float4 Color : Color;
    uint InstanceId : SV_InstanceID;
};

struct VertexOut
{
   
    float3 PosW : Pos;
    float3 NormalW : n;
    float3 eyePos : EyePosition;
    float2 txCoord : TexCoord;
    float4 PosH : SV_POSITION;
    float4 Color : Color;
};
VertexOut main(VertexIn vin)
{
    VertexOut vout;
    vout.PosW = mul(float4(vin.PosL, 1.0f), vin.World).xyz;
    //vout.NormalW = mul(vin.NormalL, (float3x3) model);
    vout.PosH = mul(float4(vout.PosW, 1.0f), worldViewProj);
    vout.txCoord = mul(float4(vin.texCoordinate, 0.0f, 1.0f), texTransform);
    vout.eyePos = eyePos;
    vout.Color = vin.Color;
    return vout;
}