#pragma once
#include "System.h"
#include <map>
#include "RenderGraph.h"
#include "Channels.h"



class RenderSystem : public System
{
	friend class Renderer;
public:
	static RenderSystem& GetSingleton();



	void AddGraph(std::shared_ptr<RenderGraph> rg);

	void LinkTechniques();
	void SubmitObjects();
	void Execute(Graphics& gfx);

	void Reset();

	void UpdateAndBindCameraBuffer();


private:
	std::map<std::string, std::shared_ptr<RenderGraph>> m_RenderGraphs;
};
