#include "MirrorReflectionPass.h"
#include "RasterizerState.h"
#include "BlendState.h"

MirrorReflectionPass::MirrorReflectionPass(Graphics& gfx, std::string passName) : RenderQueuePass(passName)
{
	RegisterSink(std::make_unique<DirectBufferSink<DepthStencil>>("depthstencil", depthStencil));
	//RegisterSink(std::make_unique<DirectBufferSink<RenderTarget>>("rendertarget", renderTarget));
	AddBind(std::make_unique<DSS>(gfx, DSS::DSSType::DrawReflaction));
	AddBind(std::make_unique<RasterizerState>(gfx, RasterizerState::RasterizerType::CullClockwise));
	AddBind(std::make_unique<BlendState>(gfx, false, BlendState::BlendType::Default));
}

void MirrorReflectionPass::Execute(Graphics& gfx)
{
	RenderQueuePass::Execute(gfx);
}

void MirrorReflectionPass::Reset()
{
	RenderQueuePass::Reset();
}
