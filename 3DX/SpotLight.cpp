#include "SpotLight.h"
#include "Technique.h"
#include "Channels.h"
#include "Entity.h"
#include "SceneRenderer.h"

std::shared_ptr<Position> pos = std::shared_ptr<Position>(new Position);
std::shared_ptr<Transformation> trans = std::shared_ptr<Transformation>(new Transformation(DirectX::XMMatrixTranslation(pos->position.x, pos->position.y, pos->position.z)));
uint32_t mID;
SpotLight::SpotLight(Graphics& gfx) : __buff(gfx,3u), Sphere(gfx,"SpotLight",0.5f,30.0f,30.0f)
{
	__BufferData =
	{
		{0.0f,0.0f,0.0f,1.0f}, //ambient
		{0.8f,0.8f,0.8f,1.0f}, //diffuse
		{1.0f,1.0f,1.0f,1.0f}, // specular
		{1.0f,0.0f,0.010f}, // attenuation
		{pos->position.x,pos->position.y,pos->position.z}, // pos
		{0.000f,0.-0.9560,0.394}, // direction
		1000.0f, // range
		100.0f // spot

	};
	
	Utilize(gfx);
}

void SpotLight::Bind(Graphics & gfx)
{
	__BufferData.pos = { pos->position.x,pos->position.y,pos->position.z };
	__buff.Update(gfx, __BufferData);
	__buff.Bind(gfx);
}

void SpotLight::Utilize(Graphics& gfx)
{
	
	Technique textured_object("SpotLight", channel1::defaultChannel);
		{
			Step s1{ "default" };
	
			s1.AddBind(std::make_shared<PixelShader>(gfx, L"ColorBlenderPS.cso"));
			auto vs = std::make_shared<VertexShader>(gfx, L"ColorBlenderVS.cso");
			auto vsBlob = vs->GetVBlob();
			s1.AddBind(std::move(vs));
			const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
			{
				{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
				
			};
			
			s1.AddBind(std::make_shared<InputLayout>(gfx, ied, vsBlob));
	
			//s1.AddBind(std::make_shared<SamplerState>(gfx));
			s1.AddBind(std::make_shared<PSConstBuff<DirectX::XMFLOAT3>>(gfx,DirectX::XMFLOAT3{ 1.0f,0.0f,0.0f },1u));
			Entity* entt = SceneRenderer::scene.CreateEntity(this);
			entt->AddComponent<Position>(*pos);
			entt->AddComponent<Transformation>(trans->transform);
			//evl.OnEvent<KeyboardEvent>([=](std::shared_ptr<KeyboardEvent> e) {UpdatePos(e->GetEvent(), mID); });
			mID = std::move(entt->GetID());

			s1.AddBind(std::make_shared<TransformationBuffer>(gfx, mID));
	
			textured_object.AddStep(s1);
		}
		AppendTechnique(textured_object);
}

void SpotLight::DrawLightImgui()
{

	Transformation* transform = nullptr;
	auto view = (Scene::reg).view<Transformation>();
	for (const entt::entity& e : view)
	{
		if ((uint32_t)e == mID)
		{
			transform = &view.get<Transformation>(e);
		}

	}
	transform->transform = DirectX::XMMatrixTranslation(pos->position.x, pos->position.y, pos->position.z);
	ImGui::Begin("SpotLight");
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);
	ImGui::SliderFloat("X", &pos->position.x, -30.0f, 30.0f);
	ImGui::SliderFloat("Y", &pos->position.y, 0.0f, 30.0f);
	ImGui::SliderFloat("Z", &pos->position.z, -30.0f, 30.0f);
	ImGui::End();

}

//void SpotLight::Draw(Graphics & gfx)
//{
//	boxlight = new Box(gfx, __BufferData.pos.x, __BufferData.pos.y, __BufferData.pos.z);
//	boxlight->Draw(gfx);
//}
