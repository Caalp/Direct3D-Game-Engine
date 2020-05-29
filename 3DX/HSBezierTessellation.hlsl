struct VertexOut
{
    float3 PosL : POSITION;
};
struct PatchTess
{
    float EdgeTess[4] : SV_TessFactor;
    float InsideTess[2] : SV_InsideTessFactor;
};

PatchTess ConstantHS(InputPatch<VertexOut, 16> patch, uint patchID : SV_PrimitiveID)
{
    PatchTess pt;
	
	// Uniform tessellation for this demo.

    pt.EdgeTess[0] = 64;
    pt.EdgeTess[1] = 64;
    pt.EdgeTess[2] = 64;
    pt.EdgeTess[3] = 64;
	
    pt.InsideTess[0] = 64;
    pt.InsideTess[1] = 64;

    return pt;
}

struct HullOut
{
    float3 PosL : POSITION;
};

// This Hull Shader part is commonly used for a coordinate basis change, 
// for example changing from a quad to a Bezier bi-cubic.
[domain("quad")]
[partitioning("integer")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(16)]
[patchconstantfunc("ConstantHS")]
[maxtessfactor(64.0f)]
HullOut main(InputPatch<VertexOut, 16> p,
           uint i : SV_OutputControlPointID,
           uint patchId : SV_PrimitiveID)
{
    HullOut hout;
	
    hout.PosL = p[i].PosL;
	
    return hout;
}
