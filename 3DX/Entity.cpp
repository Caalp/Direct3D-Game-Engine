#include "Entity.h"
#include "Scene.h"
#include "ECSFactory.h"


Entity::Entity()
{
	mEntity = ECSFactory::CreateEntity();
}

Entity::Entity(Scene* scene)
{


	mEntity = ECSFactory::CreateEntity();
	//m_TargetScene->AddEntity(this);
}

Entity::~Entity()
{
	ECSFactory::m_Registry.destroy(mEntity);
	m_TargetScene = nullptr;
	printf("Entity %d destructor called\n",mEntity);
} 

size_t Entity::GetID() const
{
	return (size_t)mEntity;
}

const char* Entity::GetName() const
{

	return m_TargetScene->m_Name.c_str();
}

const char* Entity::GetFullName() const
{
	return m_TargetScene->m_FullName.c_str();
}