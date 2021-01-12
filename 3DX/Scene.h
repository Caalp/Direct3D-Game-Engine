#pragma once
#include "entt\entt.hpp"
#include "Components.h"
class Graphics;
class Entity;
class Drawable;
class Scene
{
	friend class Entity;
public:

	//Scene() = default;
	Entity* CreateEntity(Drawable* drawable);
	void UpdateTest(float dt);
	void GetEntity(uint32_t id);
	void RemoveEntity(uint32_t id);
	
	~Scene();
	

public:
	static entt::registry reg;
	Entity* entity;



};

