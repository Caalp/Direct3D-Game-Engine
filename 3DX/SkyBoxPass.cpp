//#include "SkyBoxPass.h"
//#include "RasterizerState.h"
//SkyBoxPass::SkyBoxPass(Graphics& gfx, std::string passName) : RenderQueuePass(passName)
//{
//
//	RegisterSink(std::make_unique<DirectBufferSink<DepthStencil>>("depthstencil", depthStencil));
//	RegisterSink(std::make_unique<DirectBufferSink<RenderTarget>>("rendertarget", renderTarget));
//	AddBind(std::make_unique<DSS>(gfx, DSS::DSSType::LessOrEqual));
//	AddBind(std::make_unique<RasterizerState>(gfx, RasterizerState::RasterizerType::NoCull));
//}
//
//void SkyBoxPass::Execute(Graphics& gfx)
//{
//
//	RenderQueuePass::Execute(gfx);
//}
//
//void SkyBoxPass::Reset()
//{
//	RenderQueuePass::Reset();
//}
