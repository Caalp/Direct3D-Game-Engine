#include "Plane.h"
#include "Channels.h"
#include "Texture.h"
#include "Entity.h"
#include "SceneRenderer.h"

Plane::Plane(Graphics& gfx, std::string name, UINT numRows, UINT numCols, float dx, float dt, float damping, float texScale) : Drawable(name)
{
	struct Vertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT3 Normal;
		DirectX::XMFLOAT3 Tanget;
		DirectX::XMFLOAT2 texCoord;
	};

	std::vector<Vertex> vertices;
	std::vector<WORD> indices;

	vertices.resize(numRows * numCols);
	int vertexCount = numRows * numCols;
	int triangleCount = (numRows - 1) * (numCols - 1) * 2;
	
	//timeStep = dt;
	float spatialStep = dx;

	float width = numCols * spatialStep;
	float depth = numRows * spatialStep;


	/*delete[] prevSolution;
	delete[] currSolution;
	delete[] Normals;
	delete[] TangentX;*/

	//prevSolution = new dx::XMFLOAT3[numRows*numCols];
	//currSolution = new dx::XMFLOAT3[numRows*numCols];
	//Normals = new dx::XMFLOAT3[numRows*numCols];
	//TangentX = new dx::XMFLOAT3[numRows*numCols];

	float halfWidth = 0.5f * dx * (numCols - 1);
	float halfHeight = 0.5f * dx * (numRows - 1);

	//md.vertexData.resize(numCols * numRows);
	//Generate grid vertices
	for (UINT i = 0; i < numRows; i++)
	{
		float z = halfHeight - i * dx;
		for (UINT j = 0; j < numCols; j++)
		{
			float x = -halfWidth + j * dx;

			vertices[i * numCols + j].Pos = DirectX::XMFLOAT3(x, 0.0f, z);
			//prevSolution[i*numCols + j] = DirectX::XMFLOAT3(x, 0.0f, z);
			//currSolution[i*numCols + j] = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
			//currSolution[i*numCols + j].texCoord = DirectX::XMFLOAT2(0.05f*i*dx,0.05f*j*dx);


			vertices[i * numCols + j].Normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
			vertices[i * numCols + j].Tanget = DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f);

			//vertexData[i*numCols + j].texCoord = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);

			//prevSolution[i*numCols + j].texCoord = DirectX::XMFLOAT2(0.05f*i*dx, 0.05f*j*dx);

		}
	}


	//reserve space for indices
	indices.resize(3 * triangleCount);
	//Create indices
	int k = 0;
	for (UINT i = 0; i < numRows - 1; i++)
	{
		for (UINT j = 0; j < numCols - 1; j++)
		{
			indices[k] = i * numCols + j;
			indices[k + 1] = i * numCols + j + 1;
			indices[k + 2] = (i + 1) * numCols + j;

			indices[k + 3] = (i + 1) * numCols + j;
			indices[k + 4] = i * numCols + j + 1;
			indices[k + 5] = (i + 1) * numCols + j + 1;

			k += 6;
		}
	}
	for (UINT i = 0; i < vertexCount; ++i)
	{

		//Derive tex-coords in [0,1] from position.
		vertices[i].texCoord.x = texScale * (0.5f + vertices[i].Pos.x / width);
		vertices[i].texCoord.y = texScale * (0.5f - vertices[i].Pos.z / depth);
	}
	vertexBuffer = std::make_unique<VertexBuffer>(gfx, vertices);
	primitiveTopology = std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	indexBuffer = std::make_unique<IndexBuff>(gfx, indices);
	Utilize(gfx);
}

void Plane::Utilize(Graphics& gfx)
{
	Technique mirorObject("mirror", channel1::defaultChannel);
	{
		Step s1{ "markMirror" };
		{
			s1.AddBind(std::make_shared<PixelShader>(gfx, L"PS_TextureMapping.cso"));
			auto vs = std::make_shared<VertexShader>(gfx, L"VS_TextureMapping.cso");
			auto vsBlob = vs->GetVBlob();
			s1.AddBind(std::move(vs));
			const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
			{
				{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
				//{"Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0},
				{"TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0},

			};
			s1.AddBind(std::make_shared<InputLayout>(gfx, ied, vsBlob));

			s1.AddBind(std::make_shared<SamplerState>(gfx));
			s1.AddBind(std::make_shared<Texture>(gfx, "Textures\\ice.dds"));

			Entity* entt = SceneRenderer::scene.CreateEntity(this);
			entt->AddComponent<Transformation>(DirectX::XMMatrixRotationRollPitchYaw(0.0f, -1.5708f, 1.5708f) * DirectX::XMMatrixTranslation(0.0f, 0.0f, -3.0f));
			uint32_t mID = std::move(entt->GetID());
			s1.AddBind(std::make_shared<TransformationBuffer>(gfx,mID));
			
			//DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) * DirectX::XMMatrixTranslation(posX,posY,posZ);
			mirorObject.AddStep(s1);
		}
		{
			Step s2{ "blendTransparent" };

			s2.AddBind(std::make_shared<PixelShader>(gfx, L"PhongLightingPS.cso"));
			auto vs = std::make_shared<VertexShader>(gfx, L"PhongLightingVS.cso");
			auto vsBlob = vs->GetVBlob();
			s2.AddBind(std::move(vs));
			struct MaterialConstantPS
			{

				DirectX::XMFLOAT4 amb;
				DirectX::XMFLOAT4 diff;
				DirectX::XMFLOAT4 spec;

			}matConst;

			matConst.amb = DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
			matConst.diff = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
			matConst.spec = DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 32.0f);

			s2.AddBind(std::make_shared<PSConstBuff<MaterialConstantPS>>(gfx, matConst, 1u));
			const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
			{
				{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
				{"Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0},
				{"Tangent",0,DXGI_FORMAT_R32G32B32_FLOAT,0,24u,D3D11_INPUT_PER_VERTEX_DATA,0},
				{"TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,36u,D3D11_INPUT_PER_VERTEX_DATA,0},

			};
			s2.AddBind(std::make_shared<InputLayout>(gfx, ied, vsBlob));

			s2.AddBind(std::make_shared<SamplerState>(gfx));
			s2.AddBind(std::make_shared<Texture>(gfx, "Textures\\ice.dds"));

			Entity* entt = SceneRenderer::scene.CreateEntity(this);
			entt->AddComponent<Transformation>(DirectX::XMMatrixRotationRollPitchYaw(0.0f, -1.5708f, 1.5708f)* DirectX::XMMatrixTranslation(0.0f, 0.0f, -3.0f));
			uint32_t mID = std::move(entt->GetID());
			s2.AddBind(std::make_shared<TransformationBuffer>(gfx, mID));
			
			mirorObject.AddStep(s2);
		}
	}
	AppendTechnique(mirorObject);
	Technique textured_object("floor", channel1::defaultChannel);
	{
		{
			Step s1{ "default" };

			s1.AddBind(std::make_shared<PixelShader>(gfx, L"PS_NormalMap.cso"));
			auto vs = std::make_shared<VertexShader>(gfx, L"VS_NormalMap.cso");
			auto vsBlob = vs->GetVBlob();
			s1.AddBind(std::move(vs));
			struct MaterialConstantPS
			{

				DirectX::XMFLOAT4 amb;
				DirectX::XMFLOAT4 diff;
				DirectX::XMFLOAT4 spec;

			}matConst;

			matConst.amb = DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
			matConst.diff = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			matConst.spec = DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 32.0f);

			s1.AddBind(std::make_shared<PSConstBuff<MaterialConstantPS>>(gfx, matConst, 1u));

			const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
			{
				{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
				{"Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0},
				{"Tangent",0,DXGI_FORMAT_R32G32B32_FLOAT,0,24u,D3D11_INPUT_PER_VERTEX_DATA,0},
				{"TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,36u,D3D11_INPUT_PER_VERTEX_DATA,0},

			};

			s1.AddBind(std::make_shared<InputLayout>(gfx, ied, vsBlob));

			s1.AddBind(std::make_shared<SamplerState>(gfx));
			s1.AddBind(std::make_shared<Texture>(gfx, "Textures\\floor.dds"));
			s1.AddBind(std::make_shared<Texture>(gfx, "Textures\\floor_nmap.dds",1u));
			//
			Entity* entt = SceneRenderer::scene.CreateEntity(this);
			entt->AddComponent<Transformation>(DirectX::XMMatrixTranslation(0.0f, -3.0f, -14.0f));
			uint32_t mID = std::move(entt->GetID());
			//

			s1.AddBind(std::make_shared<TransformationBuffer>(gfx, mID));
			textured_object.AddStep(s1);
		}
		
	}
	AppendTechnique(textured_object);


}

