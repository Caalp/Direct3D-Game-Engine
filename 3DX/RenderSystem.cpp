#include "RenderSystem.h"
#include "CameraComponent.h"
#include "RenderableComponent.h"
#include "ModelComponent.h"


RenderSystem& RenderSystem::GetSingleton()
{
	static RenderSystem renderSys;
	return renderSys;
}

void RenderSystem::AddGraph(std::shared_ptr<RenderGraph> rg)
{
	m_RenderGraphs[rg->Name()] = std::move(rg);
}

//void RenderSystem::LinkTechniques()
//{
//	auto renderables = ECSFactory::GetComponents<RenderableComponent>();
//
//	for (auto& entt : renderables)
//	{
//		auto& obj = renderables.get(entt);
//		for (auto& e : obj.techniques)
//		{
//			e.Link(*m_RenderGraphs[e.m_TargetGraphName]);
//		}
//
//	}
//}
//
void RenderSystem::SubmitObjects()
{
	//Renderer::SubmitObjects();
}

void RenderSystem::Execute(Graphics& gfx)
{

	// Update camera here
	auto cam = ECSFactory::GetComponents<CameraComponent, MainCamera>();
	auto& comp = cam.get<CameraComponent>(cam.front());
	comp.UpdateAndBindCameraBuffer();

	//Renderer::Render(gfx);

	//for (auto& graph : m_RenderGraphs)
	//{
	//	graph.second->Execute(gfx);
	//}
}
//
//void RenderSystem::Reset()
//{
//	for (auto& graph : m_RenderGraphs)
//	{
//		graph.second->Reset();
//	}
//}

void RenderSystem::UpdateAndBindCameraBuffer()
{
	auto cam = ECSFactory::GetComponents<CameraComponent, MainCamera>();
	auto& comp = cam.get<CameraComponent>(cam.front());
	comp.UpdateAndBindCameraBuffer();
}
