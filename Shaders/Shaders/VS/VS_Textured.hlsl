#include "..\Common\TransformBufferVar.hlsl"

struct VertexIn
{
    float3 PosL : Position;
    //float3 NormalL : Normal;
    float2 Tex : TexCoord;
    
};

struct VertexOut
{
   
    //float3 PosW : Pos;
    //float3 NormalW : n;
    //float3 eyePos : EyePosition;
    float4 PosH : SV_POSITION;
    float2 Tex : TexCoord;
};

VertexOut main(VertexIn vin)
{
    VertexOut vout;
	vout.PosH = mul(float4(vin.PosL, 1.0f), transpose(model * viewXM * projXM));
    vout.Tex = vin.Tex;
    
    return vout;

}