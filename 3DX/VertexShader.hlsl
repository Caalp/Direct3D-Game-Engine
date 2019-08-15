cbuffer cbMatrices : register(b0)
{
	matrix g_WorldViewProj : packoffset(c0);
	matrix g_World : packoffset(c4);
};

cbuffer cbLights : register (b1)
{
	float4 g_LightDiffuse[8];
	float4 g_LightDir[8];
	float4 g_fAmbient;
	int g_nLights;
};

cbuffer cbObjectColors :register (b2)
{
	float4 g_vDiffOColor : packoffset(c0);
	float4 g_vAmbientOColor : packoffset(c1);
	bool g_bHasTexture : packoffset(c2.x);
};

struct VS_INPUT
{
	float4 vPosition : POSITION;
	float3 vNormal : NORMAL;
	float2 vTexCoord : TEXCOORD0;
};
struct VS_OUTPUT
{
	float4 vDiffuse  : COLOR0;
	float2 vTexcoord : TEXCOORD0;
	float4 vPosition : SV_POSITION;
};
VS_OUTPUT vShaderMain(VS_INPUT Input)
{
	VS_OUTPUT Output;
	float3 vNormalWorldSpace;
	float dotProduct;
	float4 dottedLightColor;
	Output.vPosition = mul(Input.vPosition, g_WorldViewProj);
	vNormalWorldSpace = mul(Input.vNormal, (float3x3)g_World);
	Output.vTexcoord = Input.vTexCoord;
	// Simple directional lighting

	float4 vTotalLightDiffuse = float4(0, 0, 0, 0);
	for (int i = 0; i < g_nLights; i++)
	{
		dotProduct = dot(vNormalWorldSpace, g_LightDir[i]);
		dotProduct = max(0, dotProduct);
		dottedLightColor = g_LightDiffuse[i] * dotProduct;
		vTotalLightDiffuse += dottedLightColor;

	}
	Output.vDiffuse.rgb = g_vDiffOColor * vTotalLightDiffuse + g_vAmbientOColor * g_fAmbient;

	Output.vDiffuse.a = 1.0f;
	return Output;



}