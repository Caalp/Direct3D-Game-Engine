struct VertexIn
{
    float3 PosL : Position;
};

struct VertexOut
{
    float3 PosL : Position;
};

VertexOut main(VertexIn vin)
{
    VertexOut vout;
	
    vout.PosL = vin.PosL;

    return vout;
}