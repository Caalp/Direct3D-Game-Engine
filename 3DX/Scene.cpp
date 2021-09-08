#include "Scene.h"
#include "Entity.h"
#include "Imgui/imgui.h"
#include "SceneLoader.h"
#include "Camera.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "RenderableComponent.h"
#include "TestBox.h"
#include "RenderSystem.h"
#include "FileUtils.h"
#include "ResourceManager.h"
#include "ModelComponent.h"

std::vector<Scene*> Scene::s_Scenes;

Scene::Scene()
{
	
	s_Scenes.emplace_back(std::move(this));
}

Scene::~Scene()
{

	// Get index of current scene
	U32 index = 0;
	for (U32 i = 0; i < s_Scenes.size(); i++)
	{
		if (s_Scenes[i]->m_SceneID == this->m_SceneID)
		{

			index = i;
			break;
		}
	}

	// Erese item 
	s_Scenes.erase(s_Scenes.begin() + index);
	
	// Delete children of the item if any exist
	this->m_ChildScenes.clear();
}

Scene* Scene::Create()
{
	return nullptr;
}

Scene* Scene::CreateRootScene()
{
	
	
	Scene* root = new Scene;
	root->m_Name = "Root";
	root->m_FullName = "Root";
	root->p_Entity = std::make_unique<Entity>();
	root->m_SceneID = root->p_Entity.get()->GetID();

	Scene* editorCamera = new Scene((new Camera()),"EditorCamera");
	

	root->AddChild(editorCamera);
	
	return root;
}




Entity* Scene::GetEntity()
{
	return p_Entity.get();
}

const std::vector<Scene*>& Scene::GetScenes()
{
	return s_Scenes;
}



void Scene::SetEntity(Scene* scene, Entity* const entity)
{

	/* Implement here */
}

void Scene::AddChild(Scene* child)
{
	child->p_ParentScene = this;
	m_ChildScenes.emplace_back(std::move(child));
}

std::vector<Ptr<Scene>>& Scene::GetChildren()
{
	return m_ChildScenes;
}

Scene* Scene::GetRootScene()
{
	if (Scene::s_Scenes[0])
	{
		return Scene::s_Scenes[0];
	}
	
}

void Scene::SetName(const std::string& name)
{
	m_Name = std::move(name);
	
	SetFullName(name + " #" + std::to_string(m_SceneID));
}



void Scene::DrawImgui
()
{
	if (ImGui::Begin("Scene"))
	{
		TraverseSceneTree(SceneLoader::GetSingleton()->GetRootScene());
		ImGui::End();
	}
}

inline uint32_t Scene::GetID() const
{
	return m_SceneID;
}

void Scene::TraverseSceneTree(Scene* scene)
{

	static int item_current_idx = 0;
	static uint32_t uniqueID = 0;
	uniqueID++;
	if (scene)
	{
		
		ImGui::PushID(uniqueID);
		if (ImGui::TreeNodeEx("", ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | (scene->GetChildren().size() ? ImGuiTreeNodeFlags_None : ImGuiTreeNodeFlags_Leaf)))
		{
			ImGui::SameLine();
			
			if (ImGui::Selectable(scene->m_FullName.c_str(),(item_current_idx == scene->GetID())))
			{
	
				item_current_idx = scene->GetID();
				
			}
			// Clicked with right mouse button
			
			if (item_current_idx == scene->GetID())
			{
				if (ImGui::BeginPopupContextItem("item context menu"))
				{
					if (ImGui::Selectable("Add Scene"))
					{
						//??
						Scene* newScene = new Scene;
						newScene->m_Name = "NewScene";
						newScene->p_Entity = std::make_unique<Entity>();
						newScene->m_FullName = newScene->m_Name + " #"+ std::to_string(newScene->p_Entity->GetID());
						newScene->m_SceneID = newScene->p_Entity->GetID();
						ECSFactory::AddComponent<TransformComponent>((entt::entity)newScene->GetID());
						std::cout << "Number of entities created: " << ECSFactory::m_Registry.size() << std::endl;

						

						scene->AddChild(newScene);

					}
					if (ImGui::Selectable("Delete Scene"))
					{
						// if scene has a parent call erase from there to delete 
						// the scene from parent's childrens
						if (scene->p_ParentScene)
						{
							auto it = std::find_if(scene->p_ParentScene->m_ChildScenes.begin(), scene->p_ParentScene->m_ChildScenes.end()
								, [&](Ptr<Scene>& s) -> bool {
									if (s->GetID() == scene->GetID())
									{
										return true;
									}
									else
									{
										return false;
									}
								});

							scene->p_ParentScene->m_ChildScenes.erase(it);
						}
						/* TO DO: Handle deleting root itself ?? */

					}
					ImGui::EndPopup();
				}
			}
		
			for (auto& child : scene->GetChildren())
			{
				TraverseSceneTree(child.get());
			}
			
			ImGui::TreePop();
		}
		ImGui::PopID();

	}
	
	uniqueID--;
	if (ImGui::Begin("Inspector"))
	{
		
		


		if (ImGui::BeginTabBar("Inspector#left_tabs_bar", ImGuiTabBarFlags_AutoSelectNewTabs | ImGuiTabBarFlags_NoCloseWithMiddleMouseButton | ImGuiTabBarFlags_FittingPolicyMask_))
		{
			if (ECSFactory::IsValid((entt::entity)item_current_idx) && uniqueID == 0)
			{
				auto it = std::find_if(s_Scenes.begin(), s_Scenes.end(), [](Scene* s) { if (s->GetID() == item_current_idx) return true; else { return false; } });
				
				/*-------------------------------------------------------------------*/
				static char str0[128];
				memcpy(&str0, (*it)->m_Name.c_str(), (*it)->m_Name.size());
				
				ImGui::InputText("Scene Name", str0, IM_ARRAYSIZE(str0));
				if (str0 != (*it)->m_Name)
				{

					(*it)->SetName(str0);
					
				}
				std::fill_n(str0, 128, 0);

				/*-------------------------------------------------------------------*/
				{
					auto v = ECSFactory::GetComponents<TransformComponent>();
					if (v.contains((entt::entity)item_current_idx))
					{
						auto& comp = v.get((entt::entity)item_current_idx);
						comp.DrawImgui();
					}
				}

				{
					auto v = ECSFactory::GetComponents<CameraComponent>();
					if (v.contains((entt::entity)item_current_idx))
					{
						auto& comp = v.get((entt::entity)item_current_idx);
						comp.DrawImgui();
					}
				}

				{
					auto v = ECSFactory::GetComponents<RenderableComponent>();
					if (v.contains((entt::entity)item_current_idx))
					{
						auto& comp = v.get((entt::entity)item_current_idx);
						comp.DrawImgui();
					}
				}
				const char* items[] = { "Select Component", "CameraComponent","ModelComponent","AnimatedModelComponent","StaticMeshComponent"};
				static int combo_item_idx = 0;
				const char* combo_label = items[combo_item_idx];
				if (ImGui::BeginCombo("", combo_label))
				{
					for (int n = 0; n < IM_ARRAYSIZE(items); n++)
					{
						const bool is_selected = (combo_item_idx == n);
						if (ImGui::Selectable(items[n], is_selected))
							combo_item_idx = n;

						// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
						if (is_selected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}
				static std::string path;

				static ModelComponent* modelComp{nullptr};
				if (items[combo_item_idx] == "ModelComponent")
				{
					//ImGui::PushItemWidth(300);
					ImGui::InputText("", const_cast<char*>(path.c_str()), path.size());
					//ImGui::PopItemWidth();
					ImGui::SameLine();
					if (ImGui::Button("Browse"))
					{
						std::wstring temp_path = FileUtils::OpenFileDialog();
						path = std::string(temp_path.begin(),temp_path.end());
						//RenderableComponent::Load(path.c_str());
						
						
						

					}
					
					if (path!= "" && ImGui::Button("Load"))
					{
					

						//modelComp = new ModelComponent(model);
					}
				}
				
				if (ImGui::Button("Add Component"))
				{
					
					if (items[combo_item_idx] == "RenderableComponent")
					{
						
						//auto v = ECSFactory::GetComponents<RenderableComponent>();
						//auto& v2 = ECSFactory::GetComponents<TransformComponent>().get((entt::entity)item_current_idx);
						//if (!v.contains((entt::entity)item_current_idx))
						//{
						//	
						//	RenderableComponent rc;
						//
						//	TestBox::CreateBoxGeometry(rc);
						//	rc.m_TBuffer = v2.m_TBuffer;
						//	for (auto s : s_Scenes)
						//	{
						//		if (s->GetID() == item_current_idx)
						//		{
						//			s->p_Entity->AddComponent<RenderableComponent>(std::move(rc));
						//			RenderSystem::GetSingleton().LinkTechniques();
						//		}
						//	}
						//	//ECSFactory::AddComponent<RenderableComponent>((entt::entity)item_current_idx);
						
					}
					else if (items[combo_item_idx] == "ModelComponent")
					{
						Ref<ModelResource> model = std::make_shared<ModelResource>(*
							ResourceManager::GetSingleton().CreateResource(path, ResourceManager::TypeModelResource)->get<ModelResource*>());
						model->Load(path.c_str());


						modelComp = new ModelComponent(model);
							if (path != "" && modelComp != nullptr)
							{

								auto v = ECSFactory::GetComponents<ModelComponent>();
								auto& v2 = ECSFactory::GetComponents<TransformComponent>().get((entt::entity)item_current_idx);
								if (!v.contains((entt::entity)item_current_idx))
								{

									//RenderableComponent rc;

									//TestBox::CreateBoxGeometry(rc);
									//modelComp->m_TBuffer = v2.m_TBuffer;

									//for (auto s : s_Scenes)
									//{
									//	if (s->GetID() == item_current_idx)
									//	{
									//		//s->p_Entity->AddComponent<RenderableComponent>(std::move(*mc));
									//		//Renderer::LinkTechniques();
									//	}
									//}
									ECSFactory::AddComponent<RenderableComponent>((entt::entity)item_current_idx);
								}
							}
						
						
					}

					else if (items[combo_item_idx] == "StaticMeshComponent")
					{

						//if (path != "" && modelComp != nullptr)
						//{

						//	auto v = ECSFactory::GetComponents<ModelComponent>();
						//	auto& v2 = ECSFactory::GetComponents<TransformComponent>().get((entt::entity)item_current_idx);
						//	if (!v.contains((entt::entity)item_current_idx))
						//	{

						//		//RenderableComponent rc;

						//		//TestBox::CreateBoxGeometry(rc);
						//		//modelComp->m_TBuffer = v2.m_TBuffer;

						//		//for (auto s : s_Scenes)
						//		//{
						//		//	if (s->GetID() == item_current_idx)
						//		//	{
						//		//		//s->p_Entity->AddComponent<RenderableComponent>(std::move(*mc));
						//		//		//Renderer::LinkTechniques();
						//		//	}
						//		//}
						//		ECSFactory::AddComponent<RenderableComponent>((entt::entity)item_current_idx);
						//	}
						//}


					}

					else if (items[combo_item_idx] == "CameraComponent")
					{

					}
					
					
						combo_item_idx = 0;
						//delete modelComp;
						//modelComp = nullptr;
						path.clear();
				}
			}
			ImGui::EndTabBar();
		}

		ImGui::End();
	}
	
	
}

void Scene::SetFullName(const std::string& fullname)
{
	m_FullName = std::move(fullname);
}


