#include "DefaultPass.h"
#include "additional_headers.h"
#include "DSS.h"
#include "Sink.h"
#include "Source.h"

DefaultPass::DefaultPass(Graphics& gfx, std::string passName) : RenderQueuePass(passName)
{
	RegisterSink(std::make_unique<DirectBufferSink<RenderTarget>>("rendertarget", renderTarget));
	RegisterSink(std::make_unique<DirectBufferSink<DepthStencil>>("depthstencil", depthStencil));
	AddBind(std::make_unique<DSS>(gfx,DSS::DSSType::Default));
	AddBind(std::make_unique<RasterizerState>(gfx, RasterizerState::RasterizerType::NoCull));

}

void DefaultPass::Execute(Graphics& gfx)
{
	RenderQueuePass::Execute(gfx);
}

void DefaultPass::Reset()
{
	RenderQueuePass::Reset();
}
