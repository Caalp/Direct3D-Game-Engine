#pragma once
#include <vector>
#include "Sink.h"
#include "Source.h"
#include "Graphics.h"
#include "DepthStencil.h"
#include "Pass.h"
#include <map>

class RenderQueuePass;



class RenderGraph
{
	

public:

	RenderGraph(Graphics& gfx, const std::string& name);
	RenderQueuePass* GetRenderQueuePass(const std::string& techName);
	void AddGlobalSource(std::unique_ptr<Source> source);
	void AddGlobalSink(std::unique_ptr<Sink> sink);
	//std::vector<std::unique_ptr<Sink>>& GetSink(Pass& p) const;
	const std::unique_ptr<Pass>& GetPassByName(std::string passName) const;
	void AppendPass(std::unique_ptr<Pass> pass);
	void Execute(Graphics& gfx);
	void Reset();
	void SetRenderTarget(std::shared_ptr<RenderTarget> rt);
	void ResetRenderTarget(Graphics& gfx);
	void ResetDepthBuffer(Graphics& gfx);
	const std::string& Name() const;
	const std::shared_ptr<RenderTarget>& GetRenderTarget();
public:
	const std::unique_ptr<Source>& GetGlobalSource(const std::string& gSourceName);
	

private:
	std::shared_ptr<RenderTarget> backBuffer;
	std::shared_ptr<DepthStencil> depthBuffer;
private:
	std::string m_GraphName;
	std::vector<std::unique_ptr<Pass>> passes;
	std::vector<std::unique_ptr<Sink>> globalSinks;
	std::vector<std::unique_ptr<Source>> globalSources;

};