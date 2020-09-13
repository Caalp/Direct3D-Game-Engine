#include "Scene.h"
#include "Entity.h"
#include "Drawable.h"

Entity* Scene::CreateEntity(Drawable* drawable)
{
	entity = new Entity(reg, this);
	return entity;
}

void Scene::UpdateTest(float dt)
{
	auto view = (reg).view<Transformation,SolidObject>();
	for (const entt::entity e : view)
	{
		Transformation* transform = &view.get<Transformation>(e);
		transform->transform = DirectX::XMMatrixRotationRollPitchYaw(0.0f, dt, 0.0f);
	}
}

void Scene::GetEntity(uint32_t id)
{
	entt::entity a ;
	reg.each([&](entt::entity entity) { if ((uint32_t)entity == id) a = entity; });
}

Scene::~Scene()
{
	//delete entity;
}
