#include "ECSFactory.h"


entt::registry ECSFactory::m_Registry;

entt::entity ECSFactory::CreateEntity()
{
	return m_Registry.create();
}

bool ECSFactory::IsValid(entt::entity entt)
{
	return m_Registry.valid(entt);
}