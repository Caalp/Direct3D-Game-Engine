#include "ShadowMap.h"
#include "additional_headers.h"
#include "Channels.h"
#include "Technique.h"
#include "Entity.h"
#include "SceneRenderer.h"
#include "Components.h"
#include "DrawCallDispatch.h"

ShadowMap::ShadowMap(Graphics& gfx, wrl::ComPtr<ID3D11ShaderResourceView> srv)
{
	struct Vertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT2 TexCoord;

	};
	std::vector<Vertex> vertices;
	vertices.resize(4);


	constexpr float side = 1.0f / 2.0f;


	vertices[0].Pos = { -side,-side,-side };// 0 near side
	vertices[1].Pos = { side,-side,-side };// 1
	vertices[2].Pos = { -side,side,-side };// 2
	vertices[3].Pos = { side,side,-side };// 3
	vertices[0].TexCoord = { 0.0f,0.0f };
	vertices[1].TexCoord = { 1.0f,0.0f };
	vertices[2].TexCoord = { 0.0f,1.0f };
	vertices[3].TexCoord = { 1.0f,1.0f };

	std::vector<unsigned short> indices =
	{

			0,2,1,   
			2,3,1

	};

	vertexBuffer = std::make_unique<VertexBuffer>(gfx, vertices);
	primitiveTopology = std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	indexBuffer = std::make_unique<IndexBuff>(gfx, indices);

	Technique textured_object("shadowmap", channel1::defaultChannel);
	{
		{

			Step s1{ "ResetRenderTarget" };


			s1.AddBind(std::make_shared<PixelShader>(gfx, "PS_Textured.cso"));
			auto vs = std::make_shared<VertexShader>(gfx, "VS_Basic.cso");
			auto vsBlob = vs->GetVBlob();
			s1.AddBind(std::move(vs));
			const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
			{
				{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
				{ "TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0 }
			};

			s1.AddBind(std::make_shared<InputLayout>(gfx, ied, vsBlob));




			s1.AddBind(std::make_shared<SamplerState>(gfx));
			s1.AddBind(std::make_shared<Texture>(gfx, srv));
			Entity* entt = GetScene().CreateEntity(this);
			entt->AddComponent<Transformation>(DirectX::XMMatrixTranslation(1.0f, 1.0f, 1.0f));
			uint32_t mID = std::move(entt->GetID());
			//

			s1.AddBind(std::make_shared<DrawIndexed>(0, indexBuffer.get()->GetIndexCount()));
			s1.AddBind(std::make_shared<TransformationBuffer>(gfx, mID));
			textured_object.AddStep(s1);
		}
		
	}
	AppendTechnique(textured_object);


}
