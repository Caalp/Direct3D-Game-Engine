//float4 main(float3 color : Color) : SV_Target
//{
//	//return float4(color,1.0f);
//}
//cbuffer CBuf : register(b0)
//{
//	float4 face_colors[6];
//};

Texture2D tex;
SamplerState sampState;

float4 main(float2 tc : TexCoord) : SV_Target
{
	return tex.Sample(sampState,tc);
}