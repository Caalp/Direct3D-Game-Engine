#pragma once
#include "RenderGraph.h"
#include "BlendTransparentPass.h"
#include "MarkMirrorPass.h"
#include "MirrorReflectionPass.h"


class MirrorRenderGraph :public RenderGraph
{
public:
	MirrorRenderGraph(Graphics& gfx) : RenderGraph(gfx)
	{
		{
			auto pass = std::make_unique<MarkMirrorPass>(gfx, "markMirror");
			pass->SetSinkLinkage("depthstencil", "$.depthbuffer");
			//pass->SetSinkLinkage("rendertarget", "$.backbuffer");
			AppendPass(std::move(pass));

		}
		{
			auto pass = std::make_unique<MirrorReflectionPass>(gfx, "mirrorReflection");
			pass->SetSinkLinkage("depthstencil", "$.depthbuffer");
			//pass->SetSinkLinkage("rendertarget", "$.backbuffer");
			AppendPass(std::move(pass));

		}
		{
			auto pass = std::make_unique<BlendTransparentPass>(gfx, "blendTransparent");
			pass->SetSinkLinkage("depthstencil", "$.depthbuffer");
			//pass->SetSinkLinkage("rendertarget", "$.backbuffer");
			AppendPass(std::move(pass));

		}

	}

};