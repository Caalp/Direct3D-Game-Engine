#include "Scene.h"
#include "Entity.h"
#include "Imgui/imgui.h"

std::vector<Scene*> Scene::s_Scenes;

Scene::Scene(std::string sceneName) : m_SceneName(sceneName)
{}

Scene::~Scene()
{
	//delete entity;
}

Scene* Scene::CreateScene(const std::string& sceneName)
{
	for (auto s : s_Scenes)
	{
		if (s->m_SceneName == sceneName)
		{
			return s;
		}
	}
	// Create new scene put it into scene array and return new scene
	Scene* s = new Scene(sceneName);
	s_Scenes.push_back(s);

	return s;
}




Entity* Scene::GetEntity(uint32_t id)
{
	for (auto e : m_Entities)
	{
		if (e->GetID() == id)
		{
			return e;
		}
	}
	return nullptr;

}

void Scene::AddEntity(Entity* const entt)
{
	m_Entities.push_back(entt);
}

void Scene::PrintEnttities()
{
	for (auto e : m_Entities)
	{
		printf("%d\n", e->GetID());
	}
}

void Scene::DrawImgui()
{
	if (ImGui::Begin("Scene"))
	{
		for (auto e : s_Scenes)
		{
			
		}
	}
}

void Scene::TraverseSceneTree(const Entity* scene)
{
	//if (ImGui::TreeNodeEx("", ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | (scene->getChildren().size() ? ImGuiTreeNodeFlags_None : ImGuiTreeNodeFlags_Leaf)))
	//{
	//	ImGui::SameLine();

	//	//if (ImGui::Selectable(scene->GetID))
	//	//{
	//	//	//openScene(scene.get());
	//	//}

	//	//

	//	//for (auto& child : scene->m_Entities)
	//	//{
	//	//	TraverseSceneTree(child);
	//	//}

	//	ImGui::TreePop();
	//}
	//ImGui::PopID();

	//ImGui::PopStyleColor(3);
}


