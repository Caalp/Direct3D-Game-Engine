#include "DefaultPass.h"
#include "additional_headers.h"
#include "DSS.h"
#include "Sink.h"
#include "Source.h"

DefaultPass::DefaultPass(Graphics& gfx, std::string passName) : RenderQueuePass(passName)
{
	RegisterSink(DirectBufferSink<RenderTarget>::Make("rendertarget", renderTarget));
	RegisterSink(DirectBufferSink<DepthStencil>::Make("depthstencil", depthStencil));
	RegisterSink(DirectBufferSink<RenderTargetArray>::Make("srv", srv));
	AddBind(std::make_unique<DSS>(gfx,DSS::DSSType::Default));
	AddBind(std::make_unique<RasterizerState>(gfx, RasterizerState::RasterizerType::Default));
	AddBind(std::make_unique<BlendState>(gfx, false, BlendState::BlendType::Default));
	

}

void DefaultPass::Execute(Graphics& gfx)
{
	AddBind(std::make_unique<Texture>(gfx, srv.get()->GetShaderResourceView(), 1u));
	RenderQueuePass::Execute(gfx);
}

void DefaultPass::Reset()
{
	RenderQueuePass::Reset();
}
