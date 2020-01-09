#include "LightCalculations.hlsl"


float4 main(float3 PosW : Pos, float3 NormalW : n, float3 eyePos : EyePosition) : SV_Target
{
	
    NormalW = normalize(NormalW);

    float3 toEyeW = normalize(eyePos - PosW);

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
    float4 litColor = ambient + diffuse + spec;
    litColor.a = m_diffuse.a;

    return litColor;

}