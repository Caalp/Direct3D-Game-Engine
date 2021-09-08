//#pragma once
//#include "RenderQueuePass.h"
//
//
//
//class DynamicCubeMapPass : public RenderQueuePass
//{
//
//public:
//	DynamicCubeMapPass(Graphics& gfx,std::string passName) : RenderQueuePass(std::move(passName))
//	{
//		// initialize render target and depth buffer
//	/*	renderTarget = std::make_shared< RenderTargetArray>(gfx, 256u, 256u, 6u);
//		depthStencil = std::make_shared<OutputOnlyDepthBuffer>(gfx, 256u, 256u);
//
//		RegisterSource(DirectBufferSource<RenderTarget>::Make("dcMap", renderTarget));
//		BuildCameras();
//
//		ImguiHandler& handler = ImguiHandler::GetInstance();
//		handler.BindCallback<DynamicCubeMapPass, &DynamicCubeMapPass::ImguiFunc>(this);*/
//	}
//
//	void Execute(Graphics& gfx) override
//	{
//		// init viewport for cam render targets
//		//gfx.CreateViewport(256.0f, 256.0f);
//
//		for (int i = 0; i < 6; i++)
//		{
//			
//			/*gfx.SetCamera(mDynamicCubeMappingCameras[i].ViewProjXM());
//			gfx.SetView(mDynamicCubeMappingCameras[i].GetViewXM());
//			gfx.SetCameraPos(mDynamicCubeMappingCameras[i].GetPosition());
//
//			float color[] = { 0.75f, 0.75f, 0.75f,1.0f };
//			ID3D11RenderTargetView* renderTargets[1];
//			renderTargets[0] = renderTarget.get()->GetRTV(i).Get();
//
//			renderTarget->Clear(gfx, color,i);
//			depthStencil->Clear(gfx);
//
//			renderTarget->BindAsBuffer(gfx, depthStencil.get(), i);
//			RenderQueuePass::Execute(gfx);*/
//	
//		}
//		//GraphicsResources::GetSingleton().pImmediateContext->GenerateMips(dynamic_cast<RenderTargetArray*>(renderTarget.get())->GetShaderResourceView());
//
//		// recover camera 
//		//mSavedCamera.UpdateViewXM();
//		//gfx.SetCamera(mSavedCamera.ViewProjXM());
//		//gfx.SetView(mSavedCamera.GetViewXM());
//		//gfx.SetCameraPos(mSavedCamera.GetPosition());
//
//		//// reset back to original render target
//	
//		//gfx.CreateViewport(gfx.GetWidth(), gfx.GetHeight());
//	
//	}
//
//	void Reset()
//	{
//		RenderQueuePass::Reset();
//	}
//	void BuildCameras()
//	{
//		using namespace DirectX;
//		
//		XMFLOAT3 cameraPos(x, y, z);
//		XMFLOAT3 worldUp(0.0f, 1.0f, 0.0f);
//
//		XMFLOAT3 cameraTargets[6] =
//		{
//			XMFLOAT3(x + 1.0f,y,z),
//			XMFLOAT3(x - 1.0f,y,z),
//			XMFLOAT3(x,y + 1.0f,z),
//			XMFLOAT3(x,y - 1.0f,z),
//			XMFLOAT3(x,y,z + 1.0f),
//			XMFLOAT3(x,y,z - 1.0f),
//		};
//
//		XMFLOAT3 cameraUps[6] =
//		{
//			XMFLOAT3(0.0f,1.0f,0.0f),
//			XMFLOAT3(0.0f,1.0f,0.0f),
//			XMFLOAT3(0.0f,0.0f,-1.0f),
//			XMFLOAT3(0.0f,0.0f,1.0f),
//			XMFLOAT3(0.0f,1.0f,0.0f),
//			XMFLOAT3(0.0f,1.0f,0.0f),
//		};
//
//		for (int i = 0; i < 6; i++)
//		{
//			/*mDynamicCubeMappingCameras[i].LookAt(cameraPos, cameraTargets[i], cameraUps[i]);
//			mDynamicCubeMappingCameras[i].SetCameraLens(0.5f * 3.141592654f, 1.0f, 0.1f, 1000.0f);
//			mDynamicCubeMappingCameras[i].UpdateViewXM();*/
//		}
//	}
//	void ImguiFunc()
//	{
//
//
//		ImGui::Begin("DynamicCubeMapSphere");
//		ImGui::SliderFloat("X", &x, -30.0f, 30.0f);
//		ImGui::SliderFloat("Y", &y, 0.0f, 30.0f);
//		ImGui::SliderFloat("Z", &z, -30.0f, 30.0f);
//		ImGui::End();
//		BuildCameras();
//		// Really dirty shortcut take care this later
//		/*Transformation* transform = nullptr;
//		auto view = (Scene::reg).view<Transformation>();
//		for (const entt::entity& e : view)
//		{
//			if ((uint32_t)e == mID1 || (uint32_t)e == mID2 || (uint32_t)e == mID3)
//			{
//				transform = &view.get<Transformation>(e);
//				DirectX::XMFLOAT4X4 temp;
//				DirectX::XMStoreFloat4x4(&temp, transform->transform);
//				temp._41 = posX;
//				temp._42 = posY;
//				temp._43 = posZ;
//				transform->transform = DirectX::XMLoadFloat4x4(&temp);
//
//			}
//
//		}
//
//		transform = nullptr;*/
//	}
//	
//private:
//	float x{ 0.0f }, y{ 0.0f }, z{ 0.0f };
//	//Camera& mSavedCamera;
//	//Camera mDynamicCubeMappingCameras[6];
//
//};