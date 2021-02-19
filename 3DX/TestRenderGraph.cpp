#include "TestRenderGraph.h"
#include "DirectXTK/ScreenGrab.h"
#include "DirectXTK/pch.h"
#include "BlendTransparentPass.h"
#include "MarkMirrorPass.h"
#include "MirrorReflectionPass.h"
#include "ResetRenderTargetPass.h"
#include "Imgui/imgui.h"
#include "ImguiHandler.h"

TestRenderGraph::TestRenderGraph(Graphics& gfx) : RenderGraph(gfx)
{
	
	// Create a shader bindable render target
	offScreenRT = std::shared_ptr<RenderTarget>{ new ShaderViewRenderTarget(gfx,gfx.GetWidth(),gfx.GetHeight()) };
	AddGlobalSource(DirectBufferSource<RenderTarget>::Make("offScreenRT",offScreenRT));
	AddGlobalSink(DirectBufferSink<RenderTarget>::Make("offScreenRT",offScreenRT));
	
	{
		auto pass = std::make_unique<ClearBufferPass>("clearRT");
		pass->SetSinkLinkage("buffer", "$.offScreenRT");
		AppendPass(std::move(pass));
	}
	{
		auto pass = std::make_unique<ClearBufferPass>("clearDS");
		pass->SetSinkLinkage("buffer", "$.depthbuffer");
		AppendPass(std::move(pass));
	}
	{
		auto pass = std::make_unique<SkyBoxPass>(gfx, "skybox");
		pass->SetSinkLinkage("depthstencil", "clearDS.buffer");
		pass->SetSinkLinkage("rendertarget", "clearRT.buffer");
		AppendPass(std::move(pass));
	}
	{
		auto pass = std::make_unique<RasterClockwise>(gfx, "rasterclockwise");
		//pass->SetSinkLinkage("depthstencil", "clearDS.buffer");
		//pass->SetSinkLinkage("rendertarget", "clearRT.buffer");
		AppendPass(std::move(pass));
	}
	{
		auto pass = std::make_unique<DefaultPass>(gfx, "default");
		/*!!! Linking only depth buffer will result with discarding RT and only binding depth !!!*/
		// Link those render and deptstencil to existing buffers from clearRT and ClearDS
		//pass->SetSinkLinkage("rendertarget", "clearRT.buffer");
		//pass->SetSinkLinkage("depthstencil", "clearDS.buffer");
		AppendPass(std::move(pass));
	}
	{
		auto pass = std::make_unique<MarkMirrorPass>(gfx, "markMirror");
		//pass->SetSinkLinkage("depthstencil", "clearDS.buffer");
		//pass->SetSinkLinkage("rendertarget", "$.backbuffer");
		AppendPass(std::move(pass));

	}
	{
		auto pass = std::make_unique<MirrorReflectionPass>(gfx, "mirrorReflection");
		//pass->SetSinkLinkage("depthstencil", "clearDS.buffer");
		//pass->SetSinkLinkage("rendertarget", "$.backbuffer");
		AppendPass(std::move(pass));

	}
	{
		auto pass = std::make_unique<BlendTransparentPass>(gfx, "blendTransparent");
		//pass->SetSinkLinkage("depthstencil", "clearDS.buffer");
		//pass->SetSinkLinkage("rendertarget", "clearRT.buffer");
		AppendPass(std::move(pass));

	}
	{
		auto pass = std::make_unique<ResetRenderTargetPass>(*this, "ResetRenderTarget");

		AppendPass(std::move(pass));
	}

	ImguiHandler& handler = ImguiHandler::GetInstance();
	handler.BindCallback<TestRenderGraph, &TestRenderGraph::Imgui_func>(this);

	//ResetRenderTarget(gfx);
	
}

void TestRenderGraph::SaveBufferToFile(Graphics& gfx, std::string filename,std::string resourceName)
{
	ID3D11Resource* res = nullptr ;
	
	offScreenRT.get()->GetResource(&res);
	std::string fName = "../"+filename+".jpeg";
	DirectX::SaveWICTextureToFile(gfx.pImmediateContext.Get(), res, GUID_ContainerFormatJpeg, std::wstring(fName.begin(), fName.end()).c_str());
	//DirectX::SaveDDSTextureToFile(gfx.pImmediateContext.Get(), res, std::wstring(fName.begin(), fName.end()).c_str());
	//Release safely 
	if (res)
	{
		res->Release();
	}
}

void TestRenderGraph::Imgui_func()
{
	ImGui::Begin("Viewport");
	//ImGui::BeginChild("GameRender");
	//ImVec2 wsize = ImGui::GetWindowSize();

	ImGui::Image((void*)dynamic_cast<ShaderViewRenderTarget*>(offScreenRT.get())->GetShaderResourceView(), ImVec2(800, 600));
	//ImGui::Image((void*)tx.srv.Get(), ImVec2(800, 600));

	//ImGui::EndChild();
	ImGui::End();
}
