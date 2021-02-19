#include "MarkMirrorPass.h"
#include "BlendState.h"
#include "RasterizerState.h"

MarkMirrorPass::MarkMirrorPass(Graphics& gfx, std::string passName) : RenderQueuePass(passName)
{
	//RegisterSink(std::make_unique<DirectBufferSink<RenderTarget>>("rendertarget", renderTarget));
	RegisterSink(std::make_unique<DirectBufferSink<DepthStencil>>("depthstencil", depthStencil));
	AddBind(std::make_unique<BlendState>(gfx, true,BlendState::BlendType::NoRenderTargetWrite));
	AddBind(std::make_unique<DSS>(gfx, DSS::DSSType::Mirror));
	AddBind(std::make_unique<RasterizerState>(gfx, RasterizerState::RasterizerType::Default));
}

void MarkMirrorPass::Execute(Graphics& gfx)
{
	//depthStencil->Clear(gfx);
	RenderQueuePass::Execute(gfx);
}

void MarkMirrorPass::Reset()
{
	RenderQueuePass::Reset();
}
