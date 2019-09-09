cbuffer cbChangesEveryFrame : register(b0)
{
	matrix worldMatrix;
}
cbuffer cbNeverChanges : register(b1)
{
	matrix viewMatrix;
}
cbuffer cbChangeOnResize : register (b2)
{
	matrix projMatrix;
}
//cbuffer CBuf : register (b3)
//{
//	matrix transform;
//};



//struct VS_Input
//{
//	float4 pos : Position;
//
//};
//float4 main(float3 pos : Position) : SV_POSITION
//{
//	
//	
//	return mul(float4(pos,1.0f),mul(worldMatrix,mul(viewMatrix,projMatrix)));
//	
//	
//}


//
float4 main(float3 pos : Position) : SV_Position
{
	return mul(float4(pos,1.0f),mul(worldMatrix,mul(viewMatrix,projMatrix)));
}