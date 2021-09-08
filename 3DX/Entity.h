#pragma once
#include "entt\entt.hpp"
#include "ECSFactory.h"



class Scene;
	
class Entity 
{
	friend class Scene;
public:

	/// <summary>
	/// Create Entity and add it to target scene
	/// </summary>
	/// <param name="sceneName"></param>
	/// <returns></returns>

	Entity();
	Entity(Scene* scene);
	~Entity();

	

	size_t GetID() const;
	
	///* Virtual Functions */
	//virtual void Update(float dt) = 0;
	
	const char* GetName() const;


	const char* GetFullName() const;

	/* Template function declarations */
	template<typename T, typename... Args>
	inline void AddComponent(Args&&... args);

	/*template<typename T>
	inline void RemoveComponent();*/
	template<typename T>
	T& GetComponent();


private:

	Scene* m_TargetScene;
	entt::entity mEntity;

};

#pragma region TemplateFuncDefinitions
template<typename T, typename ...Args>
inline void Entity::AddComponent(Args&& ...args)
{
	ECSFactory::m_Registry.emplace<T>(mEntity, std::forward<Args>(args)...);
}

template<typename T>
inline T& Entity::GetComponent()
{
	return ECSFactory::m_Registry.view<T>().get(mEntity);
}


#pragma endregion