#include "Icosahedron.h"
#include "CyclopsUtils.h"
#include "Channels.h"

using namespace Util;

Icosahedron::Icosahedron(Graphics& gfx, std::string name) : Drawable(name)
{

	
	vertices.resize(12);
	static const float  t1 = 0.525731f;
	static const float  t2 = 0.850651f;

	vertices[0].Pos = DirectX::XMFLOAT3(-t1, 0.0f, t2);
	vertices[1].Pos = DirectX::XMFLOAT3(t1, 0.0f, t2);
	vertices[2].Pos = DirectX::XMFLOAT3(-t1, 0.0f, -t2);
	vertices[3].Pos = DirectX::XMFLOAT3(t1, 0.0f, -t2);
	vertices[4].Pos = DirectX::XMFLOAT3(0.0f, t2, t1);
	vertices[5].Pos = DirectX::XMFLOAT3(0.0f, t2, -t1);
	vertices[6].Pos = DirectX::XMFLOAT3(0.0f, -t2, t1);
	vertices[7].Pos = DirectX::XMFLOAT3(0.0f, -t2, -t1);
	vertices[8].Pos = DirectX::XMFLOAT3(t2, t1, 0.0f);
	vertices[9].Pos = DirectX::XMFLOAT3(-t2, t1, 0.0f);
	vertices[10].Pos = DirectX::XMFLOAT3(t2, -t1, 0.0f);
	vertices[11].Pos = DirectX::XMFLOAT3(-t2, -t1, 0.0f);


	indices =
	{
		1,4,0,  4,9,0,  4,5,9,  8,5,4,  1,8,4,
		1,10,8, 10,3,8, 8,3,5,  3,2,5,  3,7,2,
		3,10,7, 10,6,7, 6,11,7, 6,0,11, 6,1,0,
		10,1,6, 11,0,9, 2,11,9, 5,2,9,  11,2,7
	};
	for (UINT i = 0; i <  vertices.size(); i++)
	{
		DirectX::XMVECTOR n = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&vertices[i].Pos));
		DirectX::XMStoreFloat3(&vertices[i].Normal, n);

		float theta = AngleFromXY(vertices[i].Pos.x, vertices[i].Pos.z);
		float phi = acosf(vertices[i].Pos.y / t2);
		vertices[i].texCoord.x = theta / XM_2PI;
		vertices[i].texCoord.y = phi / XM_PI;
	}
	SubDivide(gfx,1u);
	Utilize(gfx);
}

void Icosahedron::SubDivide(Graphics& gfx,unsigned int numTimesDivide)
{
	std::vector<Vertex> newVertices;
	std::vector<WORD> newIndices;
	for (int i = 0; i < numTimesDivide; i++)
	{
		//MeshData mdTemp = md;
		int triangleCount = indices.size() / 3;
		Vertex v[6];

		// Clear md data and store new vertices and indices inside it
		//md.indices.clear();
		//md.vertexData.clear();

		for (int i = 0; i < triangleCount; i++)
		{
			// Normalize the Pos XMFLOAT3 types in order to avoid distortions 
			// v[0] , v[3], v[5] is main triangle vertices and has the order of 1st, 2nd, 3rd
			// respect to the clockwise winding. Calculate mid points v[1], v[2] and v[4]

			v[0] = vertices[indices[3 * i]];
			v[0].Pos = normalize(v[0].Pos);

			v[1].Pos = normalize(0.5f * (vertices[indices[3 * i]].Pos + vertices[indices[3 * i + 1]].Pos));
			v[1].texCoord = 0.5f * (vertices[indices[3 * i]].texCoord + vertices[indices[3 * i + 1]].texCoord);
			v[1].Normal = normalize(v[1].Pos);

			v[2].Pos = normalize(0.5f * (vertices[indices[3 * i]].Pos + vertices[indices[3 * i + 2]].Pos));
			v[2].texCoord = 0.5 * (vertices[indices[3 * i]].texCoord + vertices[indices[3 * i + 2]].texCoord);
			v[2].Normal = normalize(v[2].Pos);

			v[3] = vertices[indices[3 * i + 2]];
			v[3].Pos = normalize(v[3].Pos);

			v[4].Pos = normalize(0.5f * (vertices[indices[3 * i + 1]].Pos + vertices[indices[3 * i + 2]].Pos));
			v[4].texCoord = 0.5 * (vertices[indices[3 * i + 1]].texCoord + vertices[indices[3 * i + 2]].texCoord);
			v[4].Normal = normalize(v[3].Pos);

			v[5] = vertices[indices[3 * i + 1]];
			v[5].Pos = normalize(v[5].Pos);

			//-------- triangle vertices------//
			// push vertices into vertexData inside the MeshData struct

			newVertices.push_back(v[0]);
			newVertices.push_back(v[1]);
			newVertices.push_back(v[2]);
			newVertices.push_back(v[3]);
			newVertices.push_back(v[4]);
			newVertices.push_back(v[5]);

			// according to position of the vertices inside the vector create triangles
			// respect to the clockwise winding order (front-face)
			//-------- 1st triangle indices------//
			newIndices.push_back(6 * i);
			newIndices.push_back(6 * i + 1);
			newIndices.push_back(6 * i + 2);
			//-------- 2nd triangle indices------//
			newIndices.push_back(6 * i + 1);
			newIndices.push_back(6 * i + 4);
			newIndices.push_back(6 * i + 2);
			//-------- 3rd triangle indices------//
			newIndices.push_back(6 * i + 2);
			newIndices.push_back(6 * i + 4);
			newIndices.push_back(6 * i + 3);
			//-------- 4th triangle indices------//
			newIndices.push_back(6 * i + 1);
			newIndices.push_back(6 * i + 5);
			newIndices.push_back(6 * i + 4);


		}
	}
	vertices.clear();
	indices.clear();
	vertices = std::move(newVertices);
	indices = std::move(newIndices);

	vertexBuffer = std::make_unique<VertexBuffer>(gfx, vertices);
	indexBuffer = std::make_unique<IndexBuff>(gfx, indices);
	primitiveTopology = std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Icosahedron::Utilize(Graphics& gfx)
{

	Technique textured_object("defaultBox", channel1::defaultChannel);
	{
		Step s1{ "default" };

		s1.AddBind(std::make_shared<PixelShader>(gfx, L"PS_TextureMapping.cso"));
		auto vs = std::make_shared<VertexShader>(gfx, L"VS_TextureMapping.cso");
		auto vsBlob = vs->GetVBlob();
		s1.AddBind(std::move(vs));
		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{"Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0},
			{"TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,24u,D3D11_INPUT_PER_VERTEX_DATA,0},

		};

		s1.AddBind(std::make_shared<InputLayout>(gfx, ied, vsBlob));

		s1.AddBind(std::make_shared<SamplerState>(gfx));
		//s1.AddBind(std::make_shared<Texture>(gfx, "Textures\\WireFence.dds"));

		//s1.AddBind(std::make_shared<TransformationBuffer>(gfx, *this));

		textured_object.AddStep(s1);
	}
	AppendTechnique(textured_object);
}
