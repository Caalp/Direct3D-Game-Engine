#include "Entity.h"
#include "Scene.h"
#include "ECSFactory.h"


Entity::Entity(const std::string& sceneName)
{

	m_TargetScene = Scene::CreateScene(sceneName);
	mEntity = ECSFactory::CreateEntity();
	m_TargetScene->AddEntity(this);
}

size_t Entity::GetID() const
{
	return (size_t)mEntity;
}

