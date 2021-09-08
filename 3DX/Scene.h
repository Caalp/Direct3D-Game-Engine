#pragma once
#include "entt\entt.hpp"
#include <map>
#include "Entity.h"
#include <string>
#include "Types.h"


class Entity;
#define SET_NAME(name) this->m_Name = name;
class Scene 
{
	friend class Entity;
public:


	Scene();
	~Scene();
	

	static Scene* Create();

	/* Create root scene with empty entity */
	static Scene* CreateRootScene();
	

	Entity* GetEntity();

	static const std::vector<Scene*>& GetScenes();

	Scene(Entity* entt, std::string name) : 
		p_Entity(std::move(entt)),
		m_SceneID((uint32_t)p_Entity->mEntity),
		m_Name(std::move(name)),
		m_FullName(this->m_Name + " #" + std::to_string(this->m_SceneID))
	{
		s_Scenes.emplace_back(std::move(this));
		p_Entity->m_TargetScene = this;
	}

	void SetEntity(Entity* entt)
	{
		m_Name = entt->GetName();
		return;
	}
	
	static void SetEntity(Scene* scene, Entity* const entity);
	void AddChild(Scene* child);
	std::vector<Ptr<Scene>>& GetChildren();
	static Scene* GetRootScene();
	void SetName(const std::string& name);

	
	void DrawImgui();
	inline uint32_t GetID() const;
private:
	void TraverseSceneTree(Scene* scene);
	void SetFullName(const std::string& fullname);
private:

	static std::vector<Scene*> s_Scenes; // All scenes stored statically here root scene stored in index 0
	std::vector<Ptr<Scene>> m_ChildScenes; // Childrens of the parent scene


	Scene* p_ParentScene = nullptr; // pointer to the parent scene and nullptr for the root scene
	Ptr<Entity> p_Entity;	// Corresponding entity for the current scene
	
	uint32_t m_SceneID; // Scene that matches with stored entities id (maybe zero for root scene)
	std::string m_Name; // Name of the entity
	std::string m_FullName; // Full scene name combination of m_Name and m_SceneID
	
	
	
	
	


};

