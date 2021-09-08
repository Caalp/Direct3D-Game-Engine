#include "..\Common\TransformBufferVar.hlsl"

struct VSOut
{
	float4 pos : SV_POSITION;
	float2 tex : TexCoord;
};
VSOut main(float3 pos : Position, float2 tex : TexCoord)
{
	VSOut vso;

	
	matrix worldViewProj = transpose(mul(mul(projXM, viewXM), model));
	vso.pos = mul(float4(pos, 1.0f), worldViewProj);
	vso.tex = tex;
	return vso;
}