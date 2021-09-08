#include "..\Common\TransformBufferVar.hlsl"


cbuffer boneTransforms : register(b2)
{
	matrix bones[96];
	//matrix<float, 4, 4> [96] boneTransform;
};

struct VS_in
{
	float3 position : Position;
	//float3 normal : Normal;
	float3 tex : TexCoord;
	float4 weights : Weight;
	uint4 boneIndices : BoneIndices;
};

struct VS_out
{
	float4 PosH : SV_POSITION;
	//float3 normal : Normal;
	float3 tex : TexCoord;
	//float3 weights : Weight;
	//uint4 boneIndices : BoneIndices;
};

VS_out main(VS_in vin)
{
	
	VS_out vso;
	float3 posL = float3(0.0f, 0.0f, 0.0f);
	float weights[4] = {0.0f,0.0f,0.0f,0.0f};
	weights[0] = vin.weights.x;
	weights[1] = vin.weights.y;
	weights[2] = vin.weights.z;
	weights[3] = vin.weights.w;
	
	if (weights[0] == 0.0f && weights[1] == 0.0f && weights[2] == 0.0f && weights[3] == 0.0f)
	{
		vso.PosH = mul(float4(vin.position, 1.0f), transpose(model * viewXM * projXM));
	}
	else
	{
		
		for (int i = 0; i < 4; i++)
		{
			if (weights[i] > 0.001)
			{
				posL += weights[i] * mul(float4(vin.position, 1.0f), bones[vin.boneIndices[i]]);
			}
		
				

		}
		vso.PosH = mul(float4(posL, 1.0f), transpose(model * viewXM * projXM));
		
	}
	
		
	
	
	
		
		//vso.PosH = mul(float4(pos, 1.0f), worldViewProj);
		vso.tex = vin.tex;
	
		return vso;
	}