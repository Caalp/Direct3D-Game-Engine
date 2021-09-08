//#include "BlendTransparentPass.h"
//#include "BlendState.h"
//#include "RasterizerState.h"
//
//BlendTransparentPass::BlendTransparentPass(Graphics& gfx, std::string passName) : RenderQueuePass(passName)
//{
//	RegisterSink(std::make_unique<DirectBufferSink<DepthStencil>>("depthstencil", depthStencil));
//	//RegisterSink(std::make_unique<DirectBufferSink<RenderTarget>>("rendertarget", renderTarget));
//	AddBind(std::make_unique<DSS>(gfx, DSS::DSSType::Default));
//	AddBind(std::make_unique<RasterizerState>(gfx, RasterizerState::RasterizerType::Default));
//	AddBind(std::make_unique<BlendState>(gfx, true, BlendState::BlendType::Transparent));
//}
//
//void BlendTransparentPass::Execute(Graphics& gfx)
//{
//	RenderQueuePass::Execute(gfx);
//}
//
//void BlendTransparentPass::Reset()
//{
//	RenderQueuePass::Reset();
//}
