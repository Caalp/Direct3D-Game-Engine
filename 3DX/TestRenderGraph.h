#pragma once
#include "RenderGraph.h"
#include "ClearBufferPass.h"
#include "DefaultPass.h"
#include "SkyBoxPass.h"
#include "RasterClockwise.h"

class TestRenderGraph : public RenderGraph
{
public:
	TestRenderGraph(Graphics& gfx) : RenderGraph(gfx)
	{
		{
			auto pass = std::make_unique<ClearBufferPass>("clearRT");
			pass->SetSinkLinkage("buffer", "$.backbuffer");
			AppendPass(std::move(pass));
		}
		{
			auto pass = std::make_unique<ClearBufferPass>("clearDS");
			pass->SetSinkLinkage("buffer", "$.depthbuffer");
			AppendPass(std::move(pass));
		}
		{
			auto pass = std::make_unique<SkyBoxPass>(gfx, "skybox");
			pass->SetSinkLinkage("depthstencil", "clearDS.buffer");
			pass->SetSinkLinkage("rendertarget", "clearRT.buffer");
			AppendPass(std::move(pass));
		}
		{
			auto pass = std::make_unique<RasterClockwise>(gfx, "rasterclockwise");
			pass->SetSinkLinkage("depthstencil", "clearDS.buffer");
			pass->SetSinkLinkage("rendertarget", "clearRT.buffer");
			AppendPass(std::move(pass));
		}
		{
			auto pass = std::make_unique<DefaultPass>(gfx, "default");
			// Link those render and deptstencil to existing buffers from clearRT and ClearDS
			pass->SetSinkLinkage("rendertarget", "clearRT.buffer");
			pass->SetSinkLinkage("depthstencil", "clearDS.buffer");
			AppendPass(std::move(pass));
		}
	}
};