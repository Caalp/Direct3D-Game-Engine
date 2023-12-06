#pragma once
#include <vector>
#include "Sink.h"
#include "Source.h"
#include "Graphics.h"
#include "DepthStencil.h"
#include "RenderGraph.h"
#include "Pass.h"

class RenderQueuePass;
class RenderGraph
{
public:
	//void AddPass(std::unique_ptr<Pass> pass, std::string passName)
	//{
	//	for (const auto& p : passes)
	//	{
	//		if (p->GetPassName() == passName)
	//		{
	//			assert("pass is already exist");
	//		}
	//	}
	//	passes.push_back(std::move(pass));
	//}
	RenderGraph(Graphics& gfx);
	RenderQueuePass* GetRenderQueuePass(const std::string& techName);
	void AddGlobalSource(std::unique_ptr<Source> source);
	void AddGlobalSink(std::unique_ptr<Sink> sink);
	//std::vector<std::unique_ptr<Sink>>& GetSink(Pass& p) const;
	const std::unique_ptr<Pass>& GetPassByName(std::string passName) const;
	void AppendPass(std::unique_ptr<Pass> pass);
	void Execute(Graphics& gfx);
	void Reset();
private:
	std::shared_ptr<RenderTarget> backBuffer;
	std::shared_ptr<DepthStencil> depthBuffer;
private:
	std::vector<std::unique_ptr<Pass>> passes;
	std::vector<std::unique_ptr<Sink>> globalSinks;
	std::vector<std::unique_ptr<Source>> globalSources;
};