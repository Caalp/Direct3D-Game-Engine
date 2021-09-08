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
    
	vout.PosH = mul(float4(vin.PosL + cameraPos, 1.0f), transpose(model * viewXM * projXM)).xyww;
    
    vout.PosL = vin.PosL;
    return vout;
}