#include "LightCalculations.hlsl"
struct GSOutput
{
    float3 PosW : Pos;
    float3 NormalW : n;
    float3 eyePos : EyePosition;
    float2 txCoord : TexCoord;
    float4 PosH : SV_POSITION;
    uint PrimID : SV_PrimitiveID;
};
Texture2DArray texArray;
SamplerState samplerState;

float4 main(GSOutput pin) : SV_Target
{
	
    bool texUsed = true;
    bool alphaUsed = true;
    bool fogUsed = true;
    
    pin.NormalW = normalize(pin.NormalW);

    float3 toEyeW = normalize(pin.eyePos - pin.PosW);
    float distToEye = length(pin.eyePos - pin.PosW);
    float4 texColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
   
    if (texUsed)
    {
        float3 uvw = float3(pin.txCoord, pin.PrimID % 4);
        texColor = texArray.Sample(samplerState, uvw);
        
        if(alphaUsed)
        {
            clip(texColor.a - 0.05f);
        }
    }
 
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
    
    float4 litColor = (ambient + diffuse) * texColor + spec;
    
    if(fogUsed)
    {
        float fogLerp = saturate((distToEye - 15.0f) / 175.0f);
        float4 fogColor = float4(0.75f, 0.75f, 0.75f, 1.0f);
    
        litColor = lerp(litColor, fogColor, fogLerp);
    }
    
    
    litColor.a = texColor.a * m_diffuse.a;

    return litColor;

}