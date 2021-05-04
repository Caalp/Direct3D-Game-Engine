#include "TransformationSystem.h"
#include "Camera.h"
#include "CameraComponent.h"


TransformationSystem& TransformationSystem::GetSingleton()
{
	static TransformationSystem transformSys;
	return transformSys;
}

void TransformationSystem::SetTranslation(size_t id, DirectX::XMFLOAT3 t)
{
}

void TransformationSystem::SetRotation(size_t id, DirectX::XMFLOAT3 r)
{
}

void TransformationSystem::SetScaling(size_t id, DirectX::XMFLOAT3 s)
{
}

void TransformationSystem::Update(Graphics& gfx, float dt)
{

	/*ECSFactory::GetECSFactory().GetRegistry().on_update<TransformationComponent>().connect<&freeFunc>();
	entt::observer observer{ ECSFactory::GetECSFactory().GetRegistry(), entt::collector.update<TransformationComponent>() };
*/

	TransformBuffer tb;

	auto view = ECSFactory::GetComponents<TransformationComponent>();
	auto  t = ECSFactory::GetComponents<CameraComponent, MainCamera>();

	auto& cam = t.get<CameraComponent>(t.front());


	for (auto e : view)
	{

		auto& transform = view.get<TransformationComponent>(e);
		

		tb.worldInverseTranspose = transform.GetInverseTransform();
		tb.world = DirectX::XMMatrixTranspose(transform.GetMatrix());
		tb.worldviewProj = DirectX::XMMatrixTranspose(transform.GetMatrix()* cam.m_ViewProjXM);
		tb.eyePos = cam.m_CamPos;
		transform.tBuffer->Update(tb);
	}

}
