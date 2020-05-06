cbuffer cbFixed
{
	static float4 color[6] =
	{
		float4(1.0f, 0.0f, 0.0f, 1.0f),
		float4(0.0f, 1.0f, 0.0f, 1.0f),
		float4(0.0f, 0.0f, 1.0f, 1.0f),
		float4(1.0f, 0.0f, 1.0f, 1.0f),
		float4(1.0f, 1.0f, 0.0f, 1.0f),
		float4(0.0f, 1.0f, 1.0f, 1.0f)

	};
};

float4 main(uint primId : SV_PrimitiveID) : SV_Target
{
	return color[primId % 6];
}