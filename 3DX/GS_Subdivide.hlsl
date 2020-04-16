#include "TransformBufferVar.hlsl"
struct VertexOut
{
	float3 PosL : Position;
    float3 NormalL : Normal;
    float2 texCoordinate : TexCoord;
};
struct GeoOut
{
    float3 PosW : Pos;
    float3 NormalW : n;
    float3 eyePos : EyePosition;
    float2 txCoord : TexCoord;
    float4 PosH : SV_POSITION;
};
void Subdivide(VertexOut inVerts[3], out VertexOut outVerts[6])
{
    VertexOut m[3];
    
    m[0].PosL = 0.5f * (inVerts[0].PosL + inVerts[1].PosL);
    m[1].PosL = 0.5f * (inVerts[1].PosL + inVerts[2].PosL);
    m[2].PosL = 0.5f * (inVerts[0].PosL + inVerts[2].PosL);
    
    m[0].PosL = normalize(m[0].PosL);
    m[1].PosL = normalize(m[1].PosL);
    m[2].PosL = normalize(m[2].PosL);
// Derive normals.
    m[0].NormalL = m[0].PosL;
    m[1].NormalL = m[1].PosL;
    m[2].NormalL = m[2].PosL;
// Interpolate texture coordinates.
    m[0].texCoordinate = 0.5f * (inVerts[0].texCoordinate + inVerts[1].texCoordinate);
    m[1].texCoordinate = 0.5f * (inVerts[1].texCoordinate + inVerts[2].texCoordinate);
    m[2].texCoordinate = 0.5f * (inVerts[2].texCoordinate + inVerts[0].texCoordinate);
    
    outVerts[0] = inVerts[0];
    outVerts[1] = m[0];
    outVerts[2] = m[2];
    outVerts[3] = m[1];
    outVerts[4] = inVerts[2];
    outVerts[5] = inVerts[1];
}
void OutputSubdivision(VertexOut v[6], inout TriangleStream<GeoOut> triStream)
{
   
    GeoOut gout[6];
    
    for (int i = 0; i < 6; i++)
    {
        gout[i].PosW = mul(float4(v[i].PosL, 1.0f), model).xyz;
        gout[i].NormalW = mul(v[i].NormalL, (float3x3)model);
        
        gout[i].PosH = mul(float4(v[i].PosL, 1.0f), worldViewProj);
        gout[i].txCoord = mul(float4(v[i].texCoordinate, 0.0f, 1.0f), texTransform);
        gout[i].eyePos = eyePos;
    }
    
    for (int j = 0; j < 5; j++)
    {
        triStream.Append(gout[j]);
        
    }
    triStream.RestartStrip();
    triStream.Append(gout[1]);
    triStream.Append(gout[5]);
    triStream.Append(gout[3]);
}
[maxvertexcount(32)]
void GS(triangle VertexOut gin[3], inout TriangleStream<GeoOut> triStream)
{
    static float time = 1.0f;
    float d = distance(eyePos, float3(0.0f, 0.0f, 0.0f));
    VertexOut v[6];
    
    
    
    if (d < 15.0f)
    {
        
        Subdivide(gin, v);
        VertexOut t0[3] = { v[0], v[1], v[2] };
        VertexOut t1[3] = { v[2], v[1], v[3] };
        VertexOut t2[3] = { v[2], v[3], v[4] };
        VertexOut t3[3] = { v[1], v[5], v[3] };
        Subdivide(t0, v);
        OutputSubdivision(v, triStream);
        triStream.RestartStrip();
        Subdivide(t1, v);
        OutputSubdivision(v, triStream);
        triStream.RestartStrip();
        Subdivide(t2, v);
        OutputSubdivision(v, triStream);
        triStream.RestartStrip();
        Subdivide(t3, v);
        OutputSubdivision(v, triStream);
    }
    
    ////if (d < 14.0f)
    ////{
    ////    Subdivide(gin, v);
    ////    VertexOut t0[3] = { v[0], v[1], v[2] };
    ////    VertexOut t1[3] = { v[2], v[1], v[3] };
    ////    VertexOut t2[3] = { v[2], v[3], v[4] };
    ////    VertexOut t3[3] = { v[1], v[5], v[3] };
    ////    Subdivide(t0, v);
    ////    VertexOut t0_0[3] = { v[0], v[1], v[2] };
    ////    VertexOut t0_1[3] = { v[2], v[1], v[3] };
    ////    VertexOut t0_2[3] = { v[2], v[3], v[4] };
    ////    VertexOut t0_3[3] = { v[1], v[5], v[3] };
    ////    Subdivide(t0_0, v);
    ////    OutputSubdivision(v, triStream);
    ////    triStream.RestartStrip();
    ////    Subdivide(t0_1, v);
    ////    OutputSubdivision(v, triStream);
    ////    triStream.RestartStrip();
    ////    Subdivide(t0_2, v);
    ////    OutputSubdivision(v, triStream);
    ////    triStream.RestartStrip();
    ////    Subdivide(t0_3, v);
    ////    OutputSubdivision(v, triStream);
    ////    triStream.RestartStrip();
        
    ////    Subdivide(t1, v);
    ////    VertexOut t1_0[3] = { v[0], v[1], v[2] };
    ////    VertexOut t1_1[3] = { v[2], v[1], v[3] };
    ////    VertexOut t1_2[3] = { v[2], v[3], v[4] };
    ////    VertexOut t1_3[3] = { v[1], v[5], v[3] };
    ////    Subdivide(t1_0, v);
    ////    OutputSubdivision(v, triStream);
    ////    triStream.RestartStrip();
    ////    Subdivide(t1_1, v);
    ////    OutputSubdivision(v, triStream);
    ////    triStream.RestartStrip();
    ////    Subdivide(t1_2, v);
    ////    OutputSubdivision(v, triStream);
    ////    triStream.RestartStrip();
    ////    Subdivide(t1_3, v);
    ////    OutputSubdivision(v, triStream);
    ////    triStream.RestartStrip();
        
    ////    Subdivide(t2, v);
    ////    VertexOut t2_0[3] = { v[0], v[1], v[2] };
    ////    VertexOut t2_1[3] = { v[2], v[1], v[3] };
    ////    VertexOut t2_2[3] = { v[2], v[3], v[4] };
    ////    VertexOut t2_3[3] = { v[1], v[5], v[3] };
        
    ////    Subdivide(t2_0, v);
    ////    OutputSubdivision(v, triStream);
    ////    triStream.RestartStrip();
    ////    Subdivide(t2_1, v);
    ////    OutputSubdivision(v, triStream);
    ////    triStream.RestartStrip();
    ////    Subdivide(t2_2, v);
    ////    OutputSubdivision(v, triStream);
    ////    triStream.RestartStrip();
    ////    Subdivide(t2_3, v);
    ////    OutputSubdivision(v, triStream);
    ////    triStream.RestartStrip();
        
    ////    Subdivide(t3, v);
    ////    VertexOut t3_0[3] = { v[0], v[1], v[2] };
    ////    VertexOut t3_1[3] = { v[2], v[1], v[3] };
    ////    VertexOut t3_2[3] = { v[2], v[3], v[4] };
    ////    VertexOut t3_3[3] = { v[1], v[5], v[3] };
    ////    Subdivide(t3_0, v);
    ////    OutputSubdivision(v, triStream);
    ////    triStream.RestartStrip();
    ////    Subdivide(t3_1, v);
    ////    OutputSubdivision(v, triStream);
    ////    triStream.RestartStrip();
    ////    Subdivide(t3_2, v);
    ////    OutputSubdivision(v, triStream);
    ////    triStream.RestartStrip();
    ////    Subdivide(t3_3, v);
    ////    OutputSubdivision(v, triStream);
        
        
    ////}
    else
    {
        
            
        Subdivide(gin, v);
        OutputSubdivision(v, triStream);
            
       
    }
    
    }