#include "RasterClockwise.h"
#include "additional_headers.h"
#include "DSS.h"
#include "Sink.h"
#include "Source.h"

RasterClockwise::RasterClockwise(Graphics& gfx, std::string passName) : RenderQueuePass(passName)
{
	RegisterSink(std::make_unique<DirectBufferSink<RenderTarget>>("rendertarget", renderTarget));
	RegisterSink(std::make_unique<DirectBufferSink<DepthStencil>>("depthstencil", depthStencil));
	AddBind(std::make_unique<RasterizerState>(gfx, RasterizerState::RasterizerType::CullClockwise));
}

void RasterClockwise::Execute(Graphics& gfx)
{
	RenderQueuePass::Execute(gfx);
}

void RasterClockwise::Reset()
{
	RenderQueuePass::Reset();
}