#include "SpotLight.h"
#include "Technique.h"
#include "Channels.h"
#include "Entity.h"
#include "SceneRenderer.h"
#include "Events.h"
#include "DrawCallDispatch.h"
#include "Imgui/imgui.h"

SpotLight::SpotLight(Graphics& gfx)
	: __buff(gfx, 3u), Sphere(gfx, "SpotLight", 0.5f, 30u, 30u)
{
	__BufferData =
	{
		{0.0f,0.0f,0.0f,1.0f}, //ambient
		{0.8f,0.8f,0.8f,1.0f}, //diffuse
		{1.0f,1.0f,1.0f,1.0f}, // specular
		{1.0f,0.0f,0.010f}, // attenuation
		{0.0f,0.0f,0.0f}, // pos
		{0.000f,0. - 0.9560,0.394}, // direction
		1000.0f, // range
		100.0f // spot
	};
	Utilize(gfx);
}

void SpotLight::Bind(Graphics& gfx)
{
	__buff.Update(gfx, __BufferData);
	__buff.Bind(gfx);
}

void SpotLight::Utilize(Graphics& gfx)
{
	Technique textured_object("SpotLight", channel1::defaultChannel);
	{
		Step s1{ "default" };
		s1.AddBind(std::make_shared<DrawIndexed>(0, indexBuffer.get()->GetIndexCount()));
		s1.AddBind(std::make_shared<PixelShader>(gfx, "ColorBlenderPS.cso"));
		auto vs = std::make_shared<VertexShader>(gfx, "ColorBlenderVS.cso");
		auto vsBlob = vs->GetVBlob();
		s1.AddBind(std::move(vs));
		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		s1.AddBind(std::make_shared<InputLayout>(gfx, ied, vsBlob));
		//s1.AddBind(std::make_shared<SamplerState>(gfx));
		s1.AddBind(std::make_shared<PSConstBuff<DirectX::XMFLOAT3>>(gfx, DirectX::XMFLOAT3{ 1.0f,0.0f,0.0f }, 1u));
		Entity* entt = GetScene().CreateEntity(this);
		//entt->AddComponent<Position>(__BufferData.pos);
		entt->AddComponent<Transformation>(DirectX::XMMatrixTranslationFromVector(DirectX::XMLoadFloat3(&__BufferData.pos)));
		uint32_t mID = std::move(entt->GetID());
		//evl.OnEvent<ImGuiEvent>([=](std::shared_ptr<ImGuiEvent> e) {UpdatePos(__BufferData.pos,mID); });
		s1.AddBind(std::make_shared<TransformationBuffer>(gfx, mID));
		SetID(mID);
		textured_object.AddStep(s1);
	}
	AppendTechnique(textured_object);
}

void SpotLight::DrawLightImgui(DirectX::XMFLOAT3& pos)
{
	ImGui::Begin("SpotLight");
	ImGui::SliderFloat("X", &pos.x, -30.0f, 30.0f);
	ImGui::SliderFloat("Y", &pos.y, 0.0f, 30.0f);
	ImGui::SliderFloat("Z", &pos.z, -30.0f, 30.0f);
	ImGui::End();
}

void SpotLight::Update()
{
	Transformation* transform = nullptr;
	auto view = (Scene::reg).view<Transformation>();
	for (const entt::entity& e : view)
	{
		if ((uint32_t)e == GetID())
		{
			transform = &view.get<Transformation>(e);
			break;
		}
	}
	transform->transform = DirectX::XMMatrixTranslationFromVector(DirectX::XMLoadFloat3(&__BufferData.pos));
	DrawLightImgui(__BufferData.pos);
}