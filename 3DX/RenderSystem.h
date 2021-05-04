#pragma once
#include "System.h"
#include <map>
#include "RenderGraph.h"
#include "Channels.h"

class RenderSystem : public System
{
public:
	static RenderSystem& GetSingleton();



	void AddGraph(std::shared_ptr<RenderGraph> rg);

	void LinkTechniques();

	void SubmitObjects();


	void Execute(Graphics& gfx);

	void Reset();


private:
	std::map<std::string, std::shared_ptr<RenderGraph>> m_RenderGraphs;
};
