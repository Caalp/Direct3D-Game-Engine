#pragma once
#include "Scene.h"

class Drawable;
class Entity
{
public:
	Entity() = default;
	Entity(entt::registry& reg, Scene* scene);
	template<typename T, typename... Args>
	inline void AddComponent(Args&&... args)
	{
		scene->reg.emplace<T>(entity, std::forward<Args>(args)...);
	}
	uint32_t GetID() const;
private:
	entt::entity entity;
	Scene* scene;
};