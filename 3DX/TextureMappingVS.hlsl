//cbuffer cbChangesEveryFrame : register(b0)
//{
//	matrix worldMatrix;
//}
//cbuffer cbNeverChanges : register(b1)
//{
//	matrix viewMatrix;
//}
//cbuffer cbChangeOnResize : register (b2)
//{
//	matrix projMatrix;
//}
cbuffer CBuf  : register(b0)
{
	matrix transform;
};


struct VSOut
{
	
	float2 tex : TexCoord;
	float4 pos : SV_POSITION;
	
};
VSOut main(float3 pos : Position,float2 tex : TexCoord)
{
	VSOut vso;

	vso.pos =  mul(float4(pos,1.0f),transform);
	vso.tex = tex;
	return vso;
}