cbuffer Clipping 
{
    bool isAlphaClip;
    float3 padding;
    
}

Texture2D tex;
SamplerState samplerState;





float4 main(float3 PosW : Pos, float3 NormalW : n, float3 eyePos : EyePosition,float2 tc : TexCoord) : SV_Target
{
    
    if(isAlphaClip)
    {
        clip(tex.Sample(samplerState,tc).a-0.1f);
    }
    return float4(tex.Sample(samplerState,tc).rgb,1.0f);
}