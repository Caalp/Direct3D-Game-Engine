

Texture2D tex2D;
SamplerState samplerState;


float4 main(float2 uv : TexCoord) :SV_Target
{
    return tex2D.Sample(samplerState, uv);
}