#include "PointLight.h"
#include "Technique.h"
#include "Channels.h"
#include "Entity.h"
#include "SceneRenderer.h"
#include "Events.h"
#include "DrawCallDispatch.h"
#include "Imgui/imgui.h"

PointLight::PointLight(Graphics & gfx) : __buff(gfx,2u),Sphere(gfx, "PointLight", 0.5f, 30.0f, 30.0f)
{
	
	__BufferData =
	{
		{0.3f,0.3f,0.3f,1.0f},//ambient
		{0.7f,0.7f,0.7f,1.0f},//diffuse
		{0.7f,0.7f,0.7f,1.0f},//specular
		{0.0f,0.1f,0.0f}, //attenuation
		{ 0.0f,20.0f,-10.0f}, //position
		25.0f//range
		/*{ 1.5f,14.0f,-4.5f },
		{ 0.05f,0.05f,0.05f },
		{ 1.0f,1.0f,1.0f },
		1.0f,
		1.0f,
		0.045f,
		0.0075f,*/
	};
	
	Utilize(gfx);
}

void PointLight::Bind(Graphics & gfx)
{
	
	__buff.Update(gfx, __BufferData);
	__buff.Bind(gfx);
}
void PointLight::Utilize(Graphics& gfx)
{
Technique textured_object("PointLight", channel1::defaultChannel);
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

	//evl.OnEvent<ImGuiEvent>([=](std::shared_ptr<ImGuiEvent> e) -> void {UpdatePos(__BufferData.pos, mID); });


	s1.AddBind(std::make_shared<TransformationBuffer>(gfx, mID));
	SetID(mID);
	textured_object.AddStep(s1);
}
	AppendTechnique(textured_object);
}
void PointLight::DrawLightImgui(DirectX::XMFLOAT3& pos)
{
	ImGui::Begin("PointLight");
	ImGui::SliderFloat("X", &pos.x, -30.0f, 30.0f);
	ImGui::SliderFloat("Y", &pos.y, 0.0f, 30.0f);
	ImGui::SliderFloat("Z", &pos.z, -30.0f, 30.0f);
	ImGui::End();
}
void PointLight::Update()
{
	Transformation* transform = nullptr;
	auto view = (Scene::reg).view<Transformation>();
	for (const entt::entity& e : view)
	{
		if ((uint32_t)e == GetID())
		{
			transform = &view.get<Transformation>(e);
		}

	}
	transform->transform = DirectX::XMMatrixTranslationFromVector(DirectX::XMLoadFloat3(&__BufferData.pos));
	DrawLightImgui(__BufferData.pos);

}