#include "TestCube.h"
#include "additional_headers.h"
#include "Texture.h"
#include "Surface.h"
#include "Channels.h"
#include "Technique.h"
#include "Step.h"
#include "Entity.h"
#include "SceneRenderer.h"
#include "Components.h"
#include "Events.h"
#include "App.h"


TestCube::TestCube(Graphics& gfx, float x, float y, float z) : Drawable("testCube")
{
	posX = x;
	posY = y;
	posZ = z;

	struct Vertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT2 TexCoord;

	};
	struct PixelShaderConstants
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		} face_colors[8];
	};
	const PixelShaderConstants cb2 =
	{
		{
			{ 1.0f,1.0f,1.0f },
			{ 1.0f,0.0f,0.0f },
			{ 0.0f,1.0f,0.0f },
			{ 1.0f,1.0f,0.0f },
			{ 0.0f,0.0f,1.0f },
			{ 1.0f,0.0f,1.0f },
			{ 0.0f,1.0f,1.0f },
			{ 0.0f,0.0f,0.0f },
		}
	};

	std::vector<Vertex> vertices;
	vertices.resize(24);


	constexpr float side = 1.0f / 2.0f;


	vertices[0].Pos = { -side,-side,-side };// 0 near side
	vertices[1].Pos = { side,-side,-side };// 1
	vertices[2].Pos = { -side,side,-side };// 2
	vertices[3].Pos = { side,side,-side };// 3
	vertices[4].Pos = { -side,-side,side };// 4 far side
	vertices[5].Pos = { side,-side,side };// 5
	vertices[6].Pos = { -side,side,side };// 6
	vertices[7].Pos = { side,side,side };// 7
	vertices[8].Pos = { -side,-side,-side };// 8 left side
	vertices[9].Pos = { -side,side,-side };// 9
	vertices[10].Pos = { -side,-side,side };// 10
	vertices[11].Pos = { -side,side,side };// 11
	vertices[12].Pos = { side,-side,-side };// 12 right side
	vertices[13].Pos = { side,side,-side };// 13
	vertices[14].Pos = { side,-side,side };// 14
	vertices[15].Pos = { side,side,side };// 15
	vertices[16].Pos = { -side,-side,-side };// 16 bottom side
	vertices[17].Pos = { side,-side,-side };// 17
	vertices[18].Pos = { -side,-side,side };// 18
	vertices[19].Pos = { side,-side,side };// 19
	vertices[20].Pos = { -side,side,-side };// 20 top side
	vertices[21].Pos = { side,side,-side };// 21
	vertices[22].Pos = { -side,side,side };// 22
	vertices[23].Pos = { side,side,side };// 23
	vertices[0].TexCoord = { 0.0f,0.0f };
	vertices[1].TexCoord = { 1.0f,0.0f };
	vertices[2].TexCoord = { 0.0f,1.0f };
	vertices[3].TexCoord = { 1.0f,1.0f };
	vertices[4].TexCoord = { 0.0f,0.0f };
	vertices[5].TexCoord = { 1.0f,0.0f };
	vertices[6].TexCoord = { 0.0f,1.0f };
	vertices[7].TexCoord = { 1.0f,1.0f };
	vertices[8].TexCoord = { 0.0f,0.0f };
	vertices[9].TexCoord = { 1.0f,0.0f };
	vertices[10].TexCoord = { 0.0f,1.0f };
	vertices[11].TexCoord = { 1.0f,1.0f };
	vertices[12].TexCoord = { 0.0f,0.0f };
	vertices[13].TexCoord = { 1.0f,0.0f };
	vertices[14].TexCoord = { 0.0f,1.0f };
	vertices[15].TexCoord = { 1.0f,1.0f };
	vertices[16].TexCoord = { 0.0f,0.0f };
	vertices[17].TexCoord = { 1.0f,0.0f };
	vertices[18].TexCoord = { 0.0f,1.0f };
	vertices[19].TexCoord = { 1.0f,1.0f };
	vertices[20].TexCoord = { 0.0f,0.0f };
	vertices[21].TexCoord = { 1.0f,0.0f };
	vertices[22].TexCoord = { 0.0f,1.0f };
	vertices[23].TexCoord = { 1.0f,1.0f };

	/*vertices[0].Normal = {1.0f,0.0f,0.0f };
	vertices[1].Normal = { 1.0f,0.0f,0.0f };
	vertices[2].Normal = { 1.0f,0.0f,0.0f };
	vertices[3].Normal = { 1.0f,0.0f,0.0f };
	vertices[4].Normal = { -1.0f,0.0f,0.0f };
	vertices[5].Normal = { -1.0f,0.0f,0.0f };
	vertices[6].Normal = { -1.0f,0.0f,0.0f };
	vertices[7].Normal = { -1.0f,0.0f,0.0f };
	vertices[8].Normal = { 0.0f,0.0f,-1.0f };
	vertices[9].Normal = { 0.0f,0.0f,-1.0f };
	vertices[10].Normal = { 0.0f,0.0f,-1.0f };
	vertices[11].Normal = { 0.0f,0.0f,-1.0f };
	vertices[12].Normal = { 0.0f,0.0f,1.0f };
	vertices[13].Normal = { 0.0f,0.0f,1.0f };
	vertices[14].Normal = { 0.0f,0.0f,1.0f };
	vertices[15].Normal = { 0.0f,0.0f,1.0f };
	vertices[16].Normal = { -1.0f,0.0f,0.0f };
	vertices[17].Normal = { -1.0f,0.0f,0.0f };
	vertices[18].Normal = { -1.0f,0.0f,0.0f };
	vertices[19].Normal = { -1.0f,0.0f,0.0f };
	vertices[20].Normal = { 1.0f,0.0f,0.0f };
	vertices[21].Normal = { 1.0f,0.0f,0.0f };
	vertices[22].Normal = { 1.0f,0.0f,0.0f };
	vertices[23].Normal = { 1.0f,0.0f,0.0f };
*/

	std::vector<unsigned short> indices =
	{

			0,2,1,    2,3,1,
			4,5,7,    4,7,6,
			8,10, 9,  10,11,9,
			12,13,15, 12,15,14,
			16,17,18, 18,17,19,
			20,23,21, 20,22,23

	};

	vertexBuffer = std::make_unique<VertexBuffer>(gfx, vertices);
	primitiveTopology = std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	indexBuffer = std::make_unique<IndexBuff>(gfx, indices);

	//vertexBuffer = std::make_shared<VertexBuffer>(gfx, vertices);
	//primitiveTopology = std::make_shared<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//indexBuffer = std::make_shared<IndexBuff>(gfx, indices);


	Technique textured_object("testCube", channel1::defaultChannel);
	{
		{
			Step s1{ "default" };

			s1.AddBind(std::make_shared<PixelShader>(gfx, "PS_TextureMapping.cso"));
			auto vs = std::make_shared<VertexShader>(gfx, "VS_TextureMapping.cso");
			auto vsBlob = vs->GetVBlob();
			s1.AddBind(std::move(vs));
			const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
			{
				{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
				{ "TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0 }
			};

			s1.AddBind(std::make_shared<InputLayout>(gfx, ied, vsBlob));

			s1.AddBind(std::make_shared<SamplerState>(gfx));
			s1.AddBind(std::make_shared<Texture>(gfx, "../Textures/WoodCrate01.dds"));

			Entity* entt = GetScene().CreateEntity(this);
			entt->AddComponent<Transformation>();
			entt->AddComponent<Player>();
			//entt->AddComponent<Camera>();
			// Velocity is for this case will be constant and positive actual direction will be determined by Position vector multiply velocity - or +
			entt->AddComponent<Velocity>(Vec3{10.0f,10.0f,10.0f});
			entt->AddComponent<Position>();
			entt->AddComponent<Rotation>();
			uint32_t mID= std::move(entt->GetID());
			
			GetScene().GetEntity(entt->GetID());
			//evl.OnEvent<KeyboardEvent>([=](std::shared_ptr<KeyboardEvent> e) {UpdatePos(e->GetEvent(),mID); });
			
			
			
			
			// chech valid
			//bool b = SceneRenderer::scene.reg.valid((entt::entity)mID);
			//auto version = SceneRenderer::scene.reg.version((entt::entity)mID);
			//auto curr = SceneRenderer::scene.reg.current((entt::entity)mID);
			s1.AddBind(std::make_shared<TransformationBuffer>(gfx, mID));
			delete entt;
			textured_object.AddStep(s1);
		}
		/*{
			Step s2{ "mirrorReflection" };

			s2.AddBind(std::make_shared<PixelShader>(gfx, L"PS_TextureMapping.cso"));
			auto vs = std::make_shared<VertexShader>(gfx, L"VS_TextureMapping.cso");
			auto vsBlob = vs->GetVBlob();
			s2.AddBind(std::move(vs));
			const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
			{
				{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
				{ "TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0 }
			};

			s2.AddBind(std::make_shared<InputLayout>(gfx, ied, vsBlob));

			s2.AddBind(std::make_shared<SamplerState>(gfx));
			s2.AddBind(std::make_shared<Texture>(gfx, "Textures\\WoodCrate01.dds"));

			s2.AddBind(std::make_shared<TransformationBuffer>(gfx, *this));
			DirectX::XMVECTOR mirrorPlane = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
			DirectX::XMMATRIX R = DirectX::XMMatrixReflect(mirrorPlane);

			SetTransformationXM(DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll)* DirectX::XMMatrixTranslation(x, y, z) * R);
			textured_object.AddStep(s2);
		}*/
	}
	AppendTechnique(textured_object);


}

void TestCube::UpdatePos(unsigned char key,uint32_t id)
{
	Position* pos = nullptr;
	Transformation* transform = nullptr;
	float dt = 0.5f;
	auto view = (Scene::reg).view<Position, Velocity,Transformation>();
	for (const entt::entity& e : view)
	{
		if ((uint32_t)e == id)
		{
			pos = &view.get<Position>(e);
			transform = &view.get<Transformation>(e);
			break;
		}
		
		
	}
	float v = 100.0f;
	switch (key)
	{
	case 'W':
		pos->position.z += v*dt;
		break;
	case 'S':
		pos->position.z -= v*dt;
		break;
	case 'A':
		pos->position.x -= v*dt;
		break;
	case 'D':
		pos->position.x += v*dt;
		break;
	default:
	
		break;
	}


	transform->transform = DirectX::XMMatrixTranslation(pos->position.x, pos->position.y, pos->position.z);
}
