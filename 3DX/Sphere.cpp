#include "Sphere.h"
#include "CyclopsUtils.h"
#include "Channels.h"

using namespace Util;

Sphere::Sphere(Graphics& gfx, std::string name, float radius, unsigned int sliceCount, unsigned int stackCount) : Drawable(name)
{
	struct Vertex
	{
		DirectX::XMFLOAT3 Pos;
		//DirectX::XMFLOAT3 Normal;
		//DirectX::XMFLOAT2 texCoord;
	};

	Vertex v;
	std::vector<Vertex> vertices;
	std::vector<WORD> indices;
	// Each slice of Sphere and each stack step in each slice
	// phi angle is 0<= phi<= pi and theta is between 0<= theta <= 2pi
	float phiStep = XM_PI / stackCount;
	float thetaStep = XM_2PI / sliceCount;
	float r = radius;
	float phi = 0.0f;
	float theta = 0.0f;
	

	// Add top pole point and calculate the normal and texCoord 
	v.Pos = DirectX::XMFLOAT3(0.0f, r, 0.0f);
	//v.Normal = normalize(v.Pos);
	//v.texCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
	// Push it to the vector
	vertices.push_back(v);

	// Skip the first stack which is between points on the second latitude lines
	// and the top pole point. For each stack(latitude lines) calculate each vertex point
	// Calculating means : completing 2pi period. After a full period increase the phi angle
	// (which is angle between y axis and rho vector) and calculate the next stacks vertices and so on.

	for (int i = 1; i <= stackCount - 1; i++)
	{
		phi = i * phiStep;
		for (int j = 0; j <= sliceCount; j++)
		{
			// Angle theta for 2pi period.
			theta = j * thetaStep;

			// Calculate the x,y,z coordinates
			// y axis is up vector and r*cos(phi) will give y coordinate
			// for x,z we should first calculate their values xz plane
			// after that with theta angle we can find x and z coordinates
			v.Pos.x = r * sinf(phi) * cosf(theta);;
			v.Pos.y = r * cosf(phi);
			v.Pos.z = r * sinf(phi) * sinf(theta);

			//v.Pos = MatHelper::normalize(v.Pos);
			//v.Normal = normalize(v.Pos);

			float du = theta / XM_2PI;
			float dv = phi / XM_PI;
			//v.texCoord.x = du;
			//v.texCoord.y = dv;

			vertices.push_back(v);
		}

	}

	// Push the bottom pole point to the vector
	v.Pos = DirectX::XMFLOAT3(0.0f, -r, 0.0f);
	//v.Normal = normalize(v.Pos);
	//v.texCoord = DirectX::XMFLOAT2(1.0f, 0.0f);
	vertices.push_back(v);

	// Calculate the triangles in first stack (between nort(top) pole point and first stack vertices
	// Triangles are created respect to the clockwise winding order
	for (int i = 1; i <= sliceCount; i++)
	{
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i);
	}

	// Create index buffer vector for body of the sphere 
	// (stack-2) because we need to avoid the portion which includes top and bottom pole part
	for (int i = 0; i < stackCount - 2; i++)
	{
		for (int j = 1; j <= sliceCount; j++)
		{

			indices.push_back((sliceCount + 1) * (i + 1) + j);
			indices.push_back(((sliceCount + 1) * i) + j);
			indices.push_back(((sliceCount + 1) * (i + 1)) + (j + 1));

			indices.push_back(((sliceCount + 1) * (i + 1)) + (j + 1));
			indices.push_back(((sliceCount + 1) * i) + j);
			indices.push_back(((sliceCount + 1) * i) + j + 1);

		}
	}

	// Fill the index buffer vector for bottom stack
	// As a last vertex bottom pole point is pushed to the vector
	// We should get its index and with substracting sliceCount visit each vertex in clockwise winding direction
	int bottomPoleIndex = vertices.size() - 1;
	for (UINT i = 0; i < sliceCount; ++i)
	{
		indices.push_back(bottomPoleIndex);
		indices.push_back((bottomPoleIndex - sliceCount) + i);
		indices.push_back((bottomPoleIndex - sliceCount) + i + 1);
	}

	vertexBuffer = std::make_unique<VertexBuffer>(gfx, vertices);
	indexBuffer = std::make_unique<IndexBuff>(gfx, indices);
	primitiveTopology = std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Utilize(gfx);
}

//void Sphere::Utilize(Graphics& gfx)
//{
//	Technique textured_object("defaultBox", channel1::defaultChannel);
//	{
//		Step s1{ "default" };
//
//		s1.AddBind(std::make_shared<PixelShader>(gfx, L"PS_TextureMapping.cso"));
//		auto vs = std::make_shared<VertexShader>(gfx, L"VS_TextureMapping.cso");
//		auto vsBlob = vs->GetVBlob();
//		s1.AddBind(std::move(vs));
//		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
//		{
//			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
//			{"Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0},
//			{"TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,24u,D3D11_INPUT_PER_VERTEX_DATA,0},
//
//		};
//
//		s1.AddBind(std::make_shared<InputLayout>(gfx, ied, vsBlob));
//
//		s1.AddBind(std::make_shared<SamplerState>(gfx));
//		//s1.AddBind(std::make_shared<Texture>(gfx, "Textures\\WireFence.dds"));
//
//		//s1.AddBind(std::make_shared<TransformationBuffer>(gfx, *this));
//
//		textured_object.AddStep(s1);
//	}
//	AppendTechnique(textured_object);
//}
