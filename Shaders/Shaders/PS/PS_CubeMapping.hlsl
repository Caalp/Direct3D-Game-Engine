#include "..\VS\VS_CubeMapping.hlsl"


TextureCube cubeMappingTexture;

SamplerState samplerState;
float4 main(VertexOut pin):SV_Target
{
    return cubeMappingTexture.Sample(samplerState, pin.PosL);
}