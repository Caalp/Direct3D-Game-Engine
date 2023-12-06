#include "Sky.h"
#include "Channels.h"
#include "Texture.h"
#include "SceneRenderer.h"
#include "Sphere.h"
#include "DrawCallDispatch.h"
#include "Entity.h"
#include "Step.h"
#include "Technique.h"

Sky::Sky(Graphics& gfx, std::string name, float radius, unsigned int sliceCount, unsigned int stackCount) : Sphere(gfx, name, radius, sliceCount, stackCount)
{
	Utilize(gfx);
}

void Sky::Utilize(Graphics& gfx)
{
	Technique skySphere("skySphere", channel1::defaultChannel);
	{
		Step s1{ "skybox" };
		s1.AddBind(std::make_shared<DrawIndexed>(0, indexBuffer.get()->GetIndexCount()));
		s1.AddBind(std::make_shared<PixelShader>(gfx, "PS_CubeMapping.cso"));
		auto vs = std::make_shared<VertexShader>(gfx, "VS_CubeMapping.cso");
		auto vsBlob = vs->GetVBlob();
		s1.AddBind(std::move(vs));
		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 }

		};
		s1.AddBind(std::make_shared<InputLayout>(gfx, ied, vsBlob));
		s1.AddBind(std::make_shared<SamplerState>(gfx));
		s1.AddBind(std::make_shared<Texture>(gfx, "snowcube1024.dds"));

		//Add shape as entity
		Entity* entt = GetScene().CreateEntity(this);
		entt->AddComponent<Transformation>(DirectX::XMMatrixIdentity());
		uint32_t mID = std::move(entt->GetID());
		s1.AddBind(std::make_shared<TransformationBuffer>(gfx, mID));
		skySphere.AddStep(s1);
	}
	AppendTechnique(skySphere);
}