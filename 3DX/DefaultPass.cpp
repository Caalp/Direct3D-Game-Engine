//#include "DefaultPass.h"
//#include "additional_headers.h"
//#include "DSS.h"
//#include "Sink.h"
//#include "Source.h"
//
//DefaultPass::DefaultPass(Graphics& gfx, std::string passName) : RenderQueuePass(passName)
//{
//	//srv = std::make_shared<RenderTargetArray>(gfx, 256u, 256u, 6u);
//	RegisterSink(DirectBufferSink<RenderTarget>::Make("rendertarget", renderTarget));
//	RegisterSink(DirectBufferSink<DepthStencil>::Make("depthstencil", depthStencil));
//	//RegisterSink(DirectBufferSink<RenderTargetArray>::Make("srv", srv));
//	AddBind(std::make_unique<DSS>(gfx,DSS::DSSType::Default));
//	AddBind(std::make_unique<RasterizerState>(gfx, RasterizerState::RasterizerType::Default));
//	AddBind(std::make_unique<BlendState>(gfx, false, BlendState::BlendType::Default));
//	//AddBind(std::make_unique<Texture>(gfx, srv.get(), 1u));
//
//}
//
//void DefaultPass::Execute(Graphics& gfx)
//{
//	//AddBind(std::make_unique<Texture>(srv.get()->GetShaderResourceView(), 1u));
//	RenderQueuePass::Execute(gfx);
//	// Unbound the resource 
//	//ID3D11ShaderResourceView* const pSRV[1] = { NULL };
//	//GraphicsResources::GetSingleton().pImmediateContext->PSSetShaderResources(1, 1, pSRV);
//}
//
//void DefaultPass::Reset()
//{
//	RenderQueuePass::Reset();
//}
