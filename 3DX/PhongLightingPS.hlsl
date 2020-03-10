#include "LightCalculations.hlsl"

Texture2D tex;
SamplerState samplerState;

float4 main(float3 PosW : Pos, float3 NormalW : n, float3 eyePos : EyePosition,float2 tc : TexCoord) : SV_Target
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
    ambient += A;
    diffuse += D;
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
    
    float4 litColor = (ambient + diffuse) * tex.Sample(samplerState, tc) + spec;
    
    float fogLerp = saturate((distToEye - 15.0f) / 175.0f);
    float4 fogColor = float4(0.75f, 0.75f, 0.75f, 1.0f);
    
    litColor = lerp(litColor, fogColor, fogLerp);
    litColor.a = tex.Sample(samplerState, tc).a*m_diffuse.a;

    return litColor;

}