#include "TransformBufferVar.hlsl"

struct VertexIn
{
    float3 PosL : Position;
    float2 SizeL : Size;
    
};

struct VertexOut
{
   
    float3 PosW : Pos;
    float2 SizeW : Size;
};
VertexOut main(VertexIn vin)
{
    VertexOut vout;
    vout.PosW = vin.PosL;
    vout.SizeW = vin.SizeL;
    return vout;
}