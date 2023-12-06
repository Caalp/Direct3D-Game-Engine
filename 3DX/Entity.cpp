#include "Entity.h"
#include "Drawable.h"

Entity::Entity(entt::registry& reg, Scene* scene) : scene(scene)
{
	entity = (reg).create();
}

uint32_t Entity::GetID() const
{
	return (uint32_t)entity;
}