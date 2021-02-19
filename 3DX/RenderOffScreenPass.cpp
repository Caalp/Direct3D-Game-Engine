#include "RenderOffScreenPass.h"
#include "RenderGraph.h"

RenderOffScreenPass::RenderOffScreenPass(RenderGraph& rg, const std::string passName) : BindingPass(passName)
{
	rg.AddGlobalSink(DirectBufferSink<RenderTarget>::Make("backbuffer2", rtv2));
	rg.AddGlobalSource(DirectBufferSource<RenderTarget>::Make("backbuffer2", rtv2));
}

void RenderOffScreenPass::Execute(Graphics& gfx)
{
	//rtv2->Bind()
}

void RenderOffScreenPass::Reset()
{
}
