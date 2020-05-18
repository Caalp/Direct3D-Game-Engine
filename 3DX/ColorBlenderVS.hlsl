#include "TransformBufferVar.hlsl"
struct vbuffer
{
    float3 pos : Position;
};

float4 main(vbuffer vin) : SV_Position
{
		
	return mul(float4(vin.pos, 1.0f), worldViewProj);
		
}
///////////////////////////////////////////////////////////

