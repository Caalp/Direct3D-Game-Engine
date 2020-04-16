#include "TransformBufferVar.hlsl"

struct VertexOutput
{
    float3 PosW : Pos;
    float2 SizeW : Size;
};
struct GSOutput
{
    float3 PosW : Pos;
    float3 NormalW : n;
    float3 eyePos : EyePosition;
    float2 txCoord : TexCoord;
    float4 PosH : SV_POSITION;
    uint PrimID : SV_PrimitiveID;
};
cbuffer cbFixed
{

    static float2 gTexC[4] =
    {
        float2(0.0f, 1.0f),
		float2(0.0f, 0.0f),
		float2(1.0f, 1.0f),
		float2(1.0f, 0.0f)
    };
};
[maxvertexcount(4)]
void main(
	point VertexOutput vout[1], 
    uint primID : SV_PrimitiveID, 
	inout TriangleStream< GSOutput > output
)
{
    float3 up = float3(0.0f, 1.0f, 0.0f);
    float3 look = eyePos - vout[0].PosW;
    look.y = 0.0f;
    look = normalize(look);
    float3 right = cross(up, look);
    
    
    float halfWidth = 0.5f * vout[0].SizeW.x;
    float halfHeight = 0.5f * vout[0].SizeW.y;
    
    float4 v[4];
    
    v[0] = float4(vout[0].PosW + halfWidth * right - halfHeight * up, 1.0f);
    v[1] = float4(vout[0].PosW + halfWidth * right + halfHeight * up, 1.0f);
    v[2] = float4(vout[0].PosW - halfWidth * right - halfHeight * up, 1.0f);
    v[3] = float4(vout[0].PosW - halfWidth * right + halfHeight * up, 1.0f);
    
    
    GSOutput gout;
    for (int i = 0; i < 4; i++)
    {
        gout.PosW = v[i].xyz;
        gout.NormalW = look;
        gout.eyePos = eyePos;
        gout.txCoord = gTexC[i];
        gout.PosH = mul(v[i], worldViewProj);
        gout.PrimID = primID;
        
        
        
        output.Append(gout);
    }

}