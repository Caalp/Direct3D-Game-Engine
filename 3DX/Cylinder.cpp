#include "Cylinder.h"

Cylinder::Cylinder(Graphics& gfx, std::string name,float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, float texScale) : Drawable(name)
{
	struct Vertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT3 Normal;
		DirectX::XMFLOAT2 texCoord;
	};
	std::vector<Vertex> vertices;
	std::vector<WORD> indices;

	float dTheta = (2.0f * 3.141592653589793238f) / (float)sliceCount;
	float stackHeight = height / stackCount;
	float ringCount = (float)(stackCount + 1);
	float radiusStep = (topRadius - bottomRadius) / stackCount;
	for (int i = 0; i < ringCount; i++)
	{
		float y = -0.5f * height + i * stackHeight;
		float r = bottomRadius - i * radiusStep;
		//Check <= again
		for (UINT j = 0; j <= sliceCount; j++)
		{
			float x = cosf(dTheta * j);
			float z = sinf(dTheta * j);
			Vertex v;
			v.Pos = DirectX::XMFLOAT3(x * r, y, z * r);

			float tx = texScale * ((float)j / sliceCount);
			float ty = texScale * (1.0f - (float)i / stackCount);

			v.texCoord = DirectX::XMFLOAT2(tx, ty);
			float dr = bottomRadius - topRadius;
			DirectX::XMVECTOR tangent = { -z,0.0f,x };
			DirectX::XMVECTOR biTangent = { dr * z ,-height, dr * x };
			DirectX::XMVECTOR N = DirectX::XMVector3Normalize(DirectX::XMVector3AngleBetweenNormals(tangent, biTangent));
			DirectX::XMStoreFloat3(&v.Normal, N);
			vertices.push_back(v);
		}
	}
	float ringVertexCount = (float)(sliceCount + 1);
	for (UINT i = 0; i < stackCount; i++)
	{
		for (UINT j = 0; j < sliceCount; j++)
		{
			indices.push_back((WORD)(i * ringVertexCount + j));
			indices.push_back((WORD)((i + 1) * ringVertexCount + j));
			indices.push_back((WORD)((i + 1) * ringVertexCount + (j + 1)));

			indices.push_back((WORD)(i * ringVertexCount + j));
			indices.push_back((WORD)((i + 1) * ringVertexCount + (j + 1)));
			indices.push_back((WORD)((i)*ringVertexCount + (j + 1)));
		}
	}
	Utilize(gfx);
}

void Cylinder::Utilize(Graphics& gfx)
{}