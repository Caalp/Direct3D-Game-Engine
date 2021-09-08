//#include "TestRenderGraph.h"
//#include "DirectXTK/ScreenGrab.h"
//#include "DirectXTK/pch.h"
//#include "BlendTransparentPass.h"
//#include "MarkMirrorPass.h"
//#include "MirrorReflectionPass.h"
//#include "ResetRenderTargetPass.h"
//#include "Imgui/imgui.h"
//#include "ImguiHandler.h"
//#include "DirectXTK/D3DX11tex.h"
//#include "DirectXTK/D3DX11.h"
//#include "TextureLoader.h"
//#include <comdef.h>
//#include <iostream>
//#include "DrawOutlinePass.h"
//#include "MarkOutlinePass.h"
//#include "DynamicCubeMapPass.h"
//
//#pragma comment(lib,"DirectXTK/x86/DirectXTK.lib")
//#pragma comment(lib,"DirectXTK/x86/d3dx11d.lib")
//TestRenderGraph::TestRenderGraph(Graphics& gfx, std::string graphName) : RenderGraph(gfx,graphName)
//{
//	
//	//cam.SetCamType(Camera::CameraType::CAM_ORTO);
//	//cam.LookAt(DirectX::XMFLOAT3(-2.0f,4.0f,-1.0f), { 0.0f,0.0f,0.0f }, { 0.0f,1.0f,0.0f });
//	//cam.UpdateViewXM();
//
//
//	m_shadowMap = std::shared_ptr<ShaderResourceDS>{ new ShaderResourceDS(gfx) };
//	// Create a shader bindable render target
//	offScreenRT = std::shared_ptr<RenderTarget>{ new ShaderViewRenderTarget(gfx,gfx.GetWidth(),gfx.GetHeight()) };
//	AddGlobalSource(DirectBufferSource<RenderTarget>::Make("offScreenRT",offScreenRT));
//	AddGlobalSink(DirectBufferSink<RenderTarget>::Make("offScreenRT",offScreenRT));
//
//	AddGlobalSource(DirectBufferSource<ShaderResourceDS>::Make("shadowmap", m_shadowMap));
//	AddGlobalSink(DirectBufferSink<ShaderResourceDS>::Make("shadowmap", m_shadowMap));
//
//	
//	{
//		auto pass = std::make_unique<ClearBufferPass>("clearRT");
//		pass->SetSinkLinkage("buffer", "$.offScreenRT");
//		AppendPass(std::move(pass));
//	}
//	{
//		auto pass = std::make_unique<ClearBufferPass>("clearDS");
//		pass->SetSinkLinkage("buffer", "$.depthbuffer");
//		//pass->SetSinkLinkage("buffer", "$.shadowmap");
//		AppendPass(std::move(pass));
//	}
//	//{
//	//	auto pass = std::make_unique<DynamicCubeMapPass>(gfx,"dynamicCubeMap");
//	//	//pass->SetSinkLinkage("buffer", "$.offScreenRT");
//	//	AppendPass(std::move(pass));
//	//}
//	{
//		auto pass = std::make_unique<SkyBoxPass>(gfx, "skybox");
//		pass->SetSinkLinkage("depthstencil", "clearDS.buffer");
//		pass->SetSinkLinkage("rendertarget", "clearRT.buffer");
//		AppendPass(std::move(pass));
//	}
//	/*{
//		auto pass = std::make_unique<RasterClockwise>(gfx, "rasterclockwise");
//		pass->SetSinkLinkage("depthstencil", "clearDS.buffer");
//		pass->SetSinkLinkage("rendertarget", "clearRT.buffer");
//		AppendPass(std::move(pass));
//	}*/
//	{
//		auto pass = std::make_unique<DefaultPass>(gfx, "default");
//		pass->SetSinkLinkage("depthstencil", "clearDS.buffer");
//		pass->SetSinkLinkage("rendertarget", "clearRT.buffer");
//		//pass->SetSinkLinkage("srv", "dynamicCubeMap.dcMap");
//		/*!!! Linking only depth buffer will result with discarding RT and only binding depth !!!*/
//		// Link those render and deptstencil to existing buffers from clearRT and ClearDS
//		//pass->SetSinkLinkage("rendertarget", "clearRT.buffer");
//		//pass->SetSinkLinkage("depthstencil", "clearDS.buffer");
//		AppendPass(std::move(pass));
//		//std::cout << "Linked\n" << std::endl;
//	}
//	{
//		auto pass = std::make_unique<MarkMirrorPass>(gfx, "markMirror");
//		//pass->SetSinkLinkage("depthstencil", "clearDS.buffer");
//		//pass->SetSinkLinkage("rendertarget", "$.backbuffer");
//		AppendPass(std::move(pass));
//
//	}
//	{
//		auto pass = std::make_unique<MirrorReflectionPass>(gfx, "mirrorReflection");
//		//pass->SetSinkLinkage("depthstencil", "clearDS.buffer");
//		//pass->SetSinkLinkage("rendertarget", "$.backbuffer");
//		AppendPass(std::move(pass));
//
//	}
//	{
//		auto pass = std::make_unique<BlendTransparentPass>(gfx, "blendTransparent");
//		//pass->SetSinkLinkage("depthstencil", "clearDS.buffer");
//		//pass->SetSinkLinkage("rendertarget", "clearRT.buffer");
//		AppendPass(std::move(pass));
//
//	}
//
//	{
//		auto pass = std::make_unique<MarkOutlinePass>(gfx, "MarkOutline");
//		//pass->SetSinkLinkage("depthstencil", "$.depthbuffer");
//		//pass->SetSinkLinkage("rendertarget", "clearRT.buffer");
//		AppendPass(std::move(pass));
//	}
//	{
//		auto pass = std::make_unique<DrawOutlinePass>(gfx, "DrawOutline");
//		//pass->SetSinkLinkage("depthstencil", "$.depthbuffer");
//		//pass->SetSinkLinkage("rendertarget", "clearRT.buffer");
//		AppendPass(std::move(pass));
//	}
//	{
//		auto pass = std::make_unique<ResetRenderTargetPass>(*this, "ResetRenderTarget");
//		pass->SetSinkLinkage("depthstencil", "$.depthbuffer");
//		//pass->SetSinkLinkage("rendertarget", "clearRT.buffer");
//		AppendPass(std::move(pass));
//	}
//	
//
//	ImguiHandler& handler = ImguiHandler::GetInstance();
//	handler.BindCallback<TestRenderGraph, &TestRenderGraph::Imgui_func>(this);
//
//	//ResetRenderTarget(gfx);
//	
//}
//
//void TestRenderGraph::SaveBufferToFile(Graphics& gfx, std::string filename,std::string resourceName)
//{
//	ID3D11Resource* res = nullptr ;
//
//	const auto& a = GetGlobalSource(resourceName);
//	if (a.get() == nullptr)
//	{
//		return;
//	}
//	a->GetSource()->GetResource(&res);
//	std::string fName = "../" + filename + ".jpeg";
//	//LPCSTR filename2 = fName.c_str();
//	//offScreenRT.get()->GetResource(&res);
//	
//	//DirectX::SaveWICTextureToFile(gfx.pImmediateContext.Get(), res, GUID_ContainerFormatJpeg, std::wstring(fName.begin(), fName.end()).c_str());
//	HRESULT hr = D3DX11SaveTextureToFile(GraphicsResources::GetSingleton().pImmediateContext.Get(), res, D3DX11_IFF_JPG, fName.c_str());
//	//_com_error err(hr);
//	//LPCTSTR errMsg = err.ErrorMessage();
//	//std::cout << "ERROR: " << errMsg << std::endl;
//	//DirectX::SaveDDSTextureToFile(gfx.pImmediateContext.Get(), res, std::wstring(fName.begin(), fName.end()).c_str());
//	//Release safely 
//	if (res)
//	{
//		res->Release();
//	}
//}
//
//void TestRenderGraph::Imgui_func()
//{
//	ImGui::Begin("Viewport");
//	//ImGui::BeginChild("GameRender");
//	//ImVec2 wsize = ImGui::GetWindowSize();
//
//	ImGui::Image((void*)dynamic_cast<ShaderViewRenderTarget*>(offScreenRT.get())->GetShaderResourceView(), ImVec2(800, 450));
//	//ImGui::Image((void*)tx.srv.Get(), ImVec2(800, 600));
//
//	//ImGui::EndChild();
//	ImGui::End();
//}
