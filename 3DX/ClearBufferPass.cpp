#include "ClearBufferPass.h"
#include "Sink.h"

ClearBufferPass::ClearBufferPass(const std::string passName) : BindingPass(passName)
{
	RegisterSink(DirectBufferSink<BufferResource>::Make("buffer",buffer));
	RegisterSource(DirectBufferSource<BufferResource>::Make("buffer", buffer));
	
}

void ClearBufferPass::Execute(Graphics& gfx)
{
	buffer->Clear(gfx);
}

void ClearBufferPass::Reset()
{
}
