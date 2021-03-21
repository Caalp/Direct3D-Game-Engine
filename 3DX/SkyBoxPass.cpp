#include "SkyBoxPass.h"
#include "RasterizerState.h"
SkyBoxPass::SkyBoxPass(Graphics& gfx, std::string passName) : RenderQueuePass(passName)
{

	RegisterSink(std::make_unique<DirectBufferSink<DepthStencil>>("depthstencil", depthStencil));
	RegisterSink(std::make_unique<DirectBufferSink<RenderTarget>>("rendertarget", renderTarget));
	AddBind(std::make_unique<DSS>(gfx, DSS::DSSType::LessOrEqual));
	AddBind(std::make_unique<RasterizerState>(gfx, RasterizerState::RasterizerType::NoCull));
}

void SkyBoxPass::Execute(Graphics& gfx)
{
	mCubeMapViewport.TopLeftX = 0.0f;
	mCubeMapViewport.TopLeftY = 0.0f;
	mCubeMapViewport.Width = (float)256.0f;
	mCubeMapViewport.Height = (float)256.0f;
	mCubeMapViewport.MinDepth = 0.0f;
	mCubeMapViewport.MaxDepth = 1.0f;

	gfx.pImmediateContext->RSSetViewports(1, &mCubeMapViewport);
	RenderQueuePass::Execute(gfx);
}

void SkyBoxPass::Reset()
{
	RenderQueuePass::Reset();
}
