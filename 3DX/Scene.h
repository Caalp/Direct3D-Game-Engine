#pragma once
#include "entt\entt.hpp"
#include <map>


// Scene shouldn't be coupled with entity. It just holds ref/ptr to entity type
// Can't manipulate entity directly, if any state change in entity, entity removes itself
// Scene can get entity return to ref/ptr
// We can say Scene->submit and drawable entity's submit themselves to render graph?
// Update routine can be only with entities need to be updated 

class Entity;

class Scene 
{
	friend class Entity;
public:


	Scene(std::string sceneName);
	~Scene();
	
	/// <summary>
	/// Create scene with given name if it is already exist return to scene
	/// </summary>
	/// <param name="sceneName">:Target scene name</param>
	/// <returns> Scene* </returns>
	static Scene* CreateScene(const std::string& sceneName);


	/// <summary>
	/// Return to entity with passed id
	/// </summary>
	/// <param name="id">entity id</param>
	/// <returns> pointer to the entity with given id</returns>
	Entity* GetEntity(uint32_t id);


	/// <summary>
	/// Add Enttity to the scene
	/// </summary>
	/// <param name="entt"></param>
	void AddEntity(Entity* const entt);


	void PrintEnttities();

	void DrawImgui();
private:
	void TraverseSceneTree(const Entity* scene);
private:
	
	std::string m_SceneName;
	static std::vector<Scene*> s_Scenes;
	std::vector<Entity*> m_Entities;
	



};

