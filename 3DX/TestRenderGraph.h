#pragma once
#include "RenderGraph.h"
#include "ClearBufferPass.h"
#include "DefaultPass.h"
#include "SkyBoxPass.h"
#include "RasterClockwise.h"
#include "RenderTarget.h"

class TestRenderGraph : public RenderGraph
{
public:
	TestRenderGraph(Graphics& gfx,Camera& cam);
	void SaveBufferToFile(Graphics& gfx,std::string filename, std::string resourceName);
	void Imgui_func();
private:

	std::shared_ptr<RenderTarget> offScreenRT;
	std::shared_ptr<ShaderResourceDS> m_shadowMap;
};