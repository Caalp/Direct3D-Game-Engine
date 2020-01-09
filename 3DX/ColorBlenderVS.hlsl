
cbuffer CBuf
{
    matrix model;
    matrix worldviewProj;
    float3 eyePos;
   
};
//Color blender

float4 main(float3 pos : POS) : SV_Position
{
		
	return mul(float4(pos, 1.0f), worldviewProj);
		
}
///////////////////////////////////////////////////////////

