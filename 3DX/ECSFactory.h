#pragma once
#include "entt\entt.hpp"

class ECSFactory
{
	friend class Entity;
public:

	/// <summary>
	/// Create entity and return newly created entity id
	/// </summary>
	/// <returns> entity id (size_t)</returns>
	static entt::entity CreateEntity();


	/// <summary>
	/// Get entities with passed components
	/// </summary>
	/// <typeparam name="...Args">Components</typeparam>
	/// <returns></returns>
	template<typename... Args>
	static auto GetComponents();
	
	/// <summary>
	///  Check if entity is still valid
	/// </summary>
	/// <param name="entity"> Id of the entity</param>
	/// <returns> return true if entity still valid</returns>
	static bool IsValid(entt::entity entt);



	/// <summary>
	/// Add component to given enttiy 
	/// </summary>
	/// <typeparam name="...Args">Components</typeparam>
	/// <param name="ent"></param>
	template<typename... Args>
	static void AddComponent(entt::entity ent);

	/// <summary>
	/// Remove component from entity
	/// </summary>
	/// <typeparam name="...Args">Components</typeparam>
	/// <param name="ent"></param>
	template<typename... Args>
	static void RemoveComponent(entt::entity ent);


public:
	static entt::registry m_Registry;

};

template<typename ...Args>
inline auto ECSFactory::GetComponents()
{
	return m_Registry.view<Args...>();
}

template<typename ...Args>
inline void ECSFactory::AddComponent(entt::entity ent)
{
	m_Registry.emplace<Args...>(ent);
}

template<typename ...Args>
inline void ECSFactory::RemoveComponent(entt::entity ent)
{
	m_Registry.remove<Args...>(ent);
}
