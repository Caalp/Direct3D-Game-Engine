#include "LightCalculations.hlsl"

struct VertexOut
{
   
    float3 PosW : Pos;
    float3 NormalW : n;
    float3 eyePos : EyePosition;
    float2 txCoord : TexCoord;
    float4 PosH : SV_POSITION;
};

Texture2D diffuseMap;
TextureCube tex;
SamplerState samplerState;
// When eyepos and normal's positons are switched sphere reflects other side
float4 main(VertexOut pin) : SV_Target
{
   
    pin.NormalW = normalize(pin.NormalW);

    float3 toEyeW = normalize(pin.eyePos - pin.PosW);
    float distToEye = length(pin.eyePos - pin.PosW);
    float4 texColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
    //texColor = tex.Sample
	// Start with a sum of zero. 
    float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 spec = float4(0.0f, 0.0f, 0.0f, 0.0f);
   
    float4 A, D, S;
	//Contribution from Directional Light
    ComputeDirectionalLight(toEyeW, pin.NormalW, A, D, S);
    ambient += A;
    diffuse += D;
    spec += S;
    //Contribution from Point light
    ComputePointLight(toEyeW, pin.NormalW, pin.PosW, A, D, S);
    ambient += A;
    diffuse += D;
    spec += S;
    ComputeSpotLight(toEyeW, pin.NormalW, pin.PosW, A, D, S);
    ambient += A;
    diffuse += D;
    spec += S;
	//Final color of the pixel
    if (textureUsed)
    {
        texColor = diffuseMap.Sample(samplerState, pin.txCoord);
        if(alphaClipEnabled)
        {
            clip(texColor.a - 0.1f);
        }
    }
    
    
    float4 litColor = texColor * (ambient + diffuse) + spec;
    
    if (reflactionEnabled)
    {
        //float refactor = 0.658;
        float3 incidentVector = -toEyeW;
        float3 reflectionVector = reflect(incidentVector, pin.NormalW);
   
        float4 reflectionColor = tex.Sample(samplerState, reflectionVector);
        
        litColor += m_reflection * reflectionColor;
    }
    //float fogLerp = saturate((distToEye - 15.0f) / 175.0f);
    //float4 fogColor = float4(0.75f, 0.75f, 0.75f, 1.0f);
    
    //litColor = lerp(litColor, fogColor, fogLerp);
    litColor.a = texColor.a*m_diffuse.a;

    return litColor;

}