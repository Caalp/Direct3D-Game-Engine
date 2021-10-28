#include "SkyBox.h"
#include "Sphere.h"
#include "backend.h"
#include "buckets.h"
//#include "Channels.h"
//#include "Texture.h"
//#include "SceneRenderer.h"
//#include "Sphere.h"
//#include "DrawCallDispatch.h"
//#include "Entity.h"
//#include "Step.h"
//#include "Technique.h"
//#include "DSS.h"
//
SkyBox::SkyBox(std::string name, float radius, unsigned int sliceCount, unsigned int stackCount)
{
	m_sphere = std::make_unique<Sphere>(name,radius, sliceCount, stackCount);
	
}
void SkyBox::Init()
{
	struct modelTransformBuffer
	{
		DirectX::XMMATRIX model;
		DirectX::XMMATRIX inverseTransform;
	} modelTransform;

	modelTransform.model = DirectX::XMMatrixIdentity();
	modelTransform.inverseTransform = DirectX::XMMatrixIdentity();
	auto xm = DirectX::XMMatrixIdentity();
	auto t1 = sizeof(xm);
	auto t2 = sizeof(xm.r[1]);
	m_vsh = backend::CreateShader("VS_CubeMapping.cso", ShaderType::VertexShader);

	std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 }
	};
	backend::SortKey key;

	key.m_sortKey = TORC_STATE_DEPTH_ENABLE | TORC_STATE_DEPTH_WRITE_MASK_ALL | TORC_STATE_COMPARISON_LESS_EQUAL |
		TORC_STATE_FILL_SOLID | TORC_STATE_CULL_NONE;

	command::BindSampler* sampler = bucket::testBucket.AddCommand<command::BindSampler>(key, 0);
	sampler->Sampler = backend::CreateSampler();

	command::DrawIndexed* draw = bucket::testBucket.AppendCommand<command::DrawIndexed>(sampler, 0);
	draw->indexBuffer = backend::CreateIndexBuffer(m_sphere->indices.data(), (m_sphere->indices.size() * sizeof(U16)), sizeof(U16));
	draw->vertexBuffer = backend::CreateVertexBuffer(m_sphere->vertices.data(), m_sphere->vertices.size() * sizeof(Vertex), sizeof(Vertex));
	draw->vertexLayout = backend::CreateVertexLayout(m_vsh, ied.data(), ied.size());
	draw->texHandle = backend::CreateTexture("../Textures/snowcube1024.dds");
	draw->indexCount = m_sphere->indices.size();
	draw->baseVertexLocation = 0;
	draw->startIndexLocation = 0u;
	draw->drawInfo.cb = backend::CreateConstantBuffer(BufferType::VSConstantBuffer, &modelTransform, sizeof(modelTransform), sizeof(DirectX::XMMATRIX), 0u);
	//draw->drawInfo.
	draw->drawInfo.ps = backend::CreateShader("PS_CubeMapping.cso", ShaderType::PixelShader);
	draw->drawInfo.vs = backend::CreateShader("VS_CubeMapping.cso", ShaderType::VertexShader);
	//backend::SetState(key.m_sortKey, 0);

}
//
//void Sky::Utilize(Graphics& gfx)
//{
//
//	Technique skySphere("skySphere", channel1::defaultChannel );
//	{
//		
//		Step s1{ "skybox" };
//		
//		s1.AddBind(std::make_shared<DrawIndexed>(0, indexBuffer.get()->GetIndexCount()));
//		s1.AddBind(std::make_shared<PixelShader>(gfx, "PS_CubeMapping.cso"));
//		auto vs = std::make_shared<VertexShader>(gfx, "VS_CubeMapping.cso");
//		auto vsBlob = vs->GetVBlob();
//		s1.AddBind(std::move(vs));
//		
//		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
//		{
//			{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 }
//		
//		};
//		
//		s1.AddBind(std::make_shared<InputLayout>(gfx, ied, vsBlob));
//		
//		s1.AddBind(std::make_shared<SamplerState>(gfx));
//		s1.AddBind(std::make_shared<Texture>(gfx, "../Textures/snowcube1024.dds"));
//		
//		//Add shape as entity
//		Entity* entt = GetScene().CreateEntity(this);
//		entt->AddComponent<Transformation>(DirectX::XMMatrixIdentity());
//		uint32_t mID = std::move(entt->GetID());
//		
//		s1.AddBind(std::make_shared<TransformationBuffer>(gfx, mID));
//		
//		skySphere.AddStep(s1);
//		
//	}
//	AppendTechnique(skySphere);
//	Technique skySphere2("dynamicCubeMap", channel1::dynamicCubeMap,true);
//	{
//
//		Step s1{ "dynamicCubeMap" };
//
//		s1.AddBind(std::make_shared<DrawIndexed>(0, indexBuffer.get()->GetIndexCount()));
//		s1.AddBind(std::make_shared<PixelShader>(gfx, "PS_CubeMapping.cso"));
//		auto vs = std::make_shared<VertexShader>(gfx, "VS_CubeMapping.cso");
//		auto vsBlob = vs->GetVBlob();
//		s1.AddBind(std::move(vs));
//
//		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
//		{
//			{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 }
//
//		};
//
//		s1.AddBind(std::make_shared<InputLayout>(gfx, ied, vsBlob));
//
//		s1.AddBind(std::make_shared<SamplerState>(gfx));
//		s1.AddBind(std::make_shared<Texture>(gfx, "../Textures/snowcube1024.dds"));
//
//		//Add shape as entity
//		Entity* entt = GetScene().CreateEntity(this);
//		entt->AddComponent<Transformation>(DirectX::XMMatrixIdentity());
//		uint32_t mID = std::move(entt->GetID());
//
//		s1.AddBind(std::make_shared<TransformationBuffer>(gfx, mID));
//		s1.AddBind(std::make_unique<DSS>(gfx, DSS::DSSType::LessOrEqual));
//		s1.AddBind(std::make_unique<RasterizerState>(gfx, RasterizerState::RasterizerType::NoCull));
//		skySphere2.AddStep(s1);
//
//	}
//	AppendTechnique(skySphere2);
//}
