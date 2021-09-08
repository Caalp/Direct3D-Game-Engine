#include "TransformationSystem.h"
#include "Camera.h"
#include "CameraComponent.h"
#include "Scene.h"
#include "TransformComponent.h"


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

void TransformationSystem::Update(float dt)
{

	/*ECSFactory::GetECSFactory().GetRegistry().on_update<TransformationComponent>().connect<&freeFunc>();
	entt::observer observer{ ECSFactory::GetECSFactory().GetRegistry(), entt::collector.update<TransformationComponent>() };
*/
	TransformComponent::TransformBuffer tb;

	//if (Scene::GetRootScene() == nullptr)
	//{
	//	return;
	//}
	//auto root = Scene::GetRootScene();
	//auto& rootTransform = ECSFactory::GetComponents<CameraComponent>().get(root->GetID());
	//for (auto s : Scene::GetRootScene()->GetChildrenScenes())
	//{
	//	// Get component of the entity with given id 
	//	// Scene id is same as id of the entity
	//	
	//	auto& childTransform = ECSFactory::GetComponents<TransformationComponent>().get(s->GetID());


	//	tb.world = childrenTransform.GetMatrix();
	//	
	//	// TO DO: fix inverse transform calculation
	//	tb.worldInverseTranspose = childrenTransform.GetInverseTransform();
	//	
	//	tb.worldviewProj = childrenTransform.GetMatrix() * rootTransform.m_ViewProjXM;
	//	tb.eyePos = rootTransform.m_CamPos;
	//	//childTransform.worldInverseTranspose = childTransform.worldInverseTranspose parentTransform

	//	// Pass that transformation to children of the parent 

	//	PassDown(s, childTransform);
	//	childTransform.tBuffer->Update(tb);
	//}
	//

	auto view = ECSFactory::GetComponents<TransformComponent>();
	//auto  t = ECSFactory::GetComponents<CameraComponent, MainCamera>();

	//auto& cam = t.get<CameraComponent>(t.front());
	std::vector<char> bytes;
	

	for (auto e : view)
	{

		auto& transform = view.get<TransformComponent>(e);
		

		tb.worldInverseTranspose = transform.GetInverseTransform();
		tb.world = transform.GetMatrix();
		bytes.resize(sizeof(tb));
		memcpy(bytes.data(), &tb, sizeof(tb));
		transform.GetTransformBuffer()->Update(bytes,bytes.size());

	}	

}

void TransformationSystem::PassDown(Scene* scene, TransformComponent& parentTransform)
{

	// If there is no children then return the tranform 

	//for (auto s : scene->GetChildrenScenes())
	//{
	//	// Get component of the entity with given id 
	//	// Scene id is same as id of the entity
	//	auto& transform = ECSFactory::GetComponents<TransformationComponent>().get(s->GetID());

	//	// Pass that transformation to children of the parent 

	//	PassDown(s, transform);
	//}
}

