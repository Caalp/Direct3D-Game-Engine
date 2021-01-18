
struct VSOut
{
	float4 pos : SV_POSITION;
	float3 tex : TexCoord;
	
};

Texture2D tex0 : register(t0);
Texture2D tex1 : register(t1);
Texture2D tex2 : register(t2);
Texture2D tex3 : register(t3);
Texture2D tex4 : register(t4);
Texture2D tex5 : register(t5);
SamplerState sampState;
	

float4 main(VSOut pin) : SV_Target
{
	float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);

	color = tex0.Sample(sampState, pin.tex.xy);
	clip(color.a - 0.05f);

		return color;
	}

