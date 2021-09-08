#include "..\Common\TransformBufferVar.hlsl"


float4 main(float3 pos : Position) : SV_Position
{
	matrix worldViewProj = transpose(mul(mul(projXM, viewXM), model));
	//matrix worldViewProj = (mul(mul(model, viewXM), projXM));
	return  mul(float4(pos, 1.0f), worldViewProj);
	
		
}
///////////////////////////////////////////////////////////

