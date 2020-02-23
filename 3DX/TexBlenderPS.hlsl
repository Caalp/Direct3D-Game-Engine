Texture2D tex;
SamplerState samplerState;


float4 main(float3 PosW : Pos, float3 NormalW : n, float3 eyePos : EyePosition,float2 tc : TexCoord) : SV_Target
{
    return float4(tex.Sample(samplerState,tc).rgb,1.0f);
}