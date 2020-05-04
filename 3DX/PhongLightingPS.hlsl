#include "LightCalculations.hlsl"

Texture2D diffuseMap;
TextureCube tex;
SamplerState samplerState;

float4 main(float3 PosW : Pos, float3 NormalW : n, float3 eyePos : EyePosition,float2 tc : TexCoord,float4 Color : Color) : SV_Target
{
   
    NormalW = normalize(NormalW);

    float3 toEyeW = normalize(eyePos - PosW);
    float distToEye = length(eyePos - PosW);
    float4 texColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
    //texColor = tex.Sample
	// Start with a sum of zero. 
    float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 spec = float4(0.0f, 0.0f, 0.0f, 0.0f);
   
    float4 A, D, S;
	//Contribution from Directional Light
    ComputeDirectionalLight(toEyeW, NormalW, A, D, S);
    ambient += A * Color;
    diffuse += D * Color;
    spec += S;
    //Contribution from Point light
    ComputePointLight(toEyeW, NormalW, PosW, A, D, S);
    ambient += A;
    diffuse += D;
    spec += S;
    ComputeSpotLight(toEyeW, NormalW, PosW, A, D, S);
    ambient += A;
    diffuse += D;
    spec += S;
	//Final color of the pixel
    if (textureUsed)
    {
        texColor = diffuseMap.Sample(samplerState, tc);
        if(alphaClipEnabled)
        {
            clip(texColor.a - 0.1f);
        }
    }
    
    
    float4 litColor = texColor * (ambient + diffuse) + spec;
    
    if (reflactionEnabled)
    {
        float3 incidentVector = -toEyeW;
        float3 reflectionVector = reflect(incidentVector, NormalW);
        float4 reflectionColor = tex.Sample(samplerState, reflectionVector);
        
        litColor += m_reflection * reflectionColor;
    }
    //float fogLerp = saturate((distToEye - 15.0f) / 175.0f);
    //float4 fogColor = float4(0.75f, 0.75f, 0.75f, 1.0f);
    
    //litColor = lerp(litColor, fogColor, fogLerp);
    litColor.a = texColor.a*m_diffuse.a;

    return litColor;

}