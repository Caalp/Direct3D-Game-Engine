

struct VSOut
{
	float4 pos : SV_POSITION;
	float2 tex : TexCoord;
};

Texture2D tex;
SamplerState sampState;

float4 main(VSOut pin) : SV_Target
{

	float4 color =  tex.Sample(sampState,pin.tex);
	if ((color.a - 0.05f) < 0)
	{
		clip(color.a - 0.05f);
	}
	return color;
}