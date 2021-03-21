#include "ResetRenderTargetPass.h"
#include "Channels.h"
#include "Imgui/imgui.h"
#include "ImguiHandler.h"
ResetRenderTargetPass::ResetRenderTargetPass(RenderGraph& rg,std::string passName) : BindingPass(passName),rg(rg)
{
	RegisterSink(std::make_unique<DirectBufferSink<DepthStencil>>("depthstencil", depthStencil));
	shaderResourceView = dynamic_cast<ShaderResourceDS*>(rg.GetGlobalSource("shadowmap")->GetSource().get())->shaderResourceView;
	//ID3D11Resource* res = nullptr;
	
	//RegisterSink(std::make_unique<DirectBufferSink<RenderTarget>>("rendertarget", renderTarget));
}

void ResetRenderTargetPass::Execute(Graphics& gfx)
{
	//shadowMap.Submit(channel1::defaultChannel);
	renderTarget = gfx.pTarget;
	BindAll(gfx);

	//ImGui::Begin("ShadowMap");
	////ImGui::BeginChild("GameRender");
	////ImVec2 wsize = ImGui::GetWindowSize();

	//ImGui::Image((void*)shaderResourceView.Get(), ImVec2(400, 300));
	////ImGui::Image((void*)tx.srv.Get(), ImVec2(800, 600));

	////ImGui::EndChild();
	//ImGui::End();
	//RenderQueuePass::Execute(gfx);
	//gfx.pImmediateContext->OMSetRenderTargets(1, rg.GetRenderTarget()->GetRTV().GetAddressOf(), 0);
}

void ResetRenderTargetPass::Reset()
{
}
