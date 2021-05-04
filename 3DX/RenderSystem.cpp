#include "RenderSystem.h"

RenderSystem& RenderSystem::GetSingleton()
{
	static RenderSystem renderSys;
	return renderSys;
}

void RenderSystem::AddGraph(std::shared_ptr<RenderGraph> rg)
{
	m_RenderGraphs[rg->Name()] = std::move(rg);
}

void RenderSystem::LinkTechniques()
{
	auto renderables = ECSFactory::GetComponents<Renderable>();

	for (auto& entt : renderables)
	{
		auto& obj = renderables.get(entt);
		for (auto& e : obj.techniques)
		{
			e.Link(*m_RenderGraphs[e.m_TargetGraphName]);
		}

	}
}

void RenderSystem::SubmitObjects()
{
	auto renderables = ECSFactory::GetComponents<Renderable>();

	for (auto& entt : renderables)
	{
		auto& obj = renderables.get(entt);
		for (auto& e : obj.techniques)
		{
			e.Submit(obj, channel1::defaultChannel);
		}

	}
}

void RenderSystem::Execute(Graphics& gfx)
{
	for (auto& graph : m_RenderGraphs)
	{
		graph.second->Execute(gfx);
	}
}

void RenderSystem::Reset()
{
	for (auto& graph : m_RenderGraphs)
	{
		graph.second->Reset();
	}
}