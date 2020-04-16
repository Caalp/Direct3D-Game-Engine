struct VertexIn
{
    float3 PosL : Position;
    float3 NormalL : Normal;
    float2 texCoordinate : TexCoord;
};

struct VertexOut
{
   
    float3 PosL : Position;
    float3 NormalL : Normal;
    float2 texCoordinate : TexCoord;
};
VertexOut main(VertexIn vin)
{
    VertexOut vout;
    vout.PosL = vin.PosL;
    vout.NormalL = vin.NormalL;
    vout.texCoordinate = vin.texCoordinate;
    
    return vout;
}