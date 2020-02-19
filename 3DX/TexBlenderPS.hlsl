Texture2D tex;
SamplerState samplerState;

//cbuffer CBuf : register(b1)
//{
//    float4 color;
//};

float4 main(float2 tc : TexCoord) : SV_Target
{
    return tex.Sample(samplerState,tc);
}