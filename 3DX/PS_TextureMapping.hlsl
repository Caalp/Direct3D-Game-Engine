

struct VSOut
{
    float4 pos : SV_POSITION;
    float2 tex : TexCoord;
};

Texture2D tex;
SamplerState sampState;

float4 main(VSOut pin) : SV_Target
{
	return tex.Sample(sampState,pin.tex);
}