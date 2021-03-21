#pragma once
#include "RenderQueuePass.h"



class DynamicCubeMapPass : public RenderQueuePass
{

public:
	DynamicCubeMapPass(Graphics& gfx,Camera& cam,std::string passName) : RenderQueuePass(std::move(passName)), mSavedCamera(cam)
	{
		// save camera states
		srv = std::make_shared< RenderTargetArray>(gfx, 256u, 256u, 6u);
		RegisterSource(DirectBufferSource<RenderTargetArray>::Make("dcMap",srv));
		BuildCameras();
		BuildSrv(gfx);
		AddBind(std::make_unique<DSS>(gfx, DSS::DSSType::LessOrEqual));
		AddBind(std::make_unique<RasterizerState>(gfx, RasterizerState::RasterizerType::NoCull));
	}

	void Execute(Graphics& gfx) override
	{
		mCubeMapViewport.TopLeftX = 0.0f;
		mCubeMapViewport.TopLeftY = 0.0f;
		mCubeMapViewport.Width = (float)256.0f;
		mCubeMapViewport.Height = (float)256.0f;
		mCubeMapViewport.MinDepth = 0.0f;
		mCubeMapViewport.MaxDepth = 1.0f;

		gfx.pImmediateContext->RSSetViewports(1, &mCubeMapViewport);
		for (int i = 0; i < 6; i++)
		{
			
			gfx.SetCamera(mDynamicCubeMappingCameras[i].ViewProjXM());
			gfx.SetView(mDynamicCubeMappingCameras[i].GetViewXM());
			gfx.SetCameraPos(mDynamicCubeMappingCameras[i].GetPosition());

			float color[] = { 0.75f, 0.75f, 0.75f,1.0f };
			ID3D11RenderTargetView* renderTargets[1];
			renderTargets[0] = srv.get()->GetRTV(i).Get();

			

			gfx.pImmediateContext->ClearRenderTargetView(srv.get()->GetRTV(i).Get(), color);
			gfx.pImmediateContext->ClearDepthStencilView(dsv.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
			gfx.pImmediateContext->OMSetRenderTargets(1, renderTargets, dsv.Get());
			RenderQueuePass::Execute(gfx);
	
		}
		gfx.pImmediateContext->GenerateMips(srv.get()->GetShaderResourceView().Get());
		// recover camera 
		mSavedCamera.UpdateViewXM();
		gfx.SetCamera(mSavedCamera.ViewProjXM());
		gfx.SetView(mSavedCamera.GetViewXM());
		gfx.SetCameraPos(mSavedCamera.GetPosition());
		mCubeMapViewport.TopLeftX = 0.0f;
		mCubeMapViewport.TopLeftY = 0.0f;
		mCubeMapViewport.Width = (float)1600.0f;
		mCubeMapViewport.Height = (float)1200.0f;
		mCubeMapViewport.MinDepth = 0.0f;
		mCubeMapViewport.MaxDepth = 1.0f;

		gfx.pImmediateContext->RSSetViewports(1, &mCubeMapViewport);
	
	}

	void Reset()
	{

	}
	void BuildCameras()
	{
		using namespace DirectX;
		float x(0.0f), y(0.0f), z(0.0f);
		XMFLOAT3 cameraPos(x, y, z);
		XMFLOAT3 worldUp(0.0f, 1.0f, 0.0f);

		XMFLOAT3 cameraTargets[6] =
		{
			XMFLOAT3(x + 1.0f,y,z),
			XMFLOAT3(x - 1.0f,y,z),
			XMFLOAT3(x,y + 1.0f,z),
			XMFLOAT3(x,y - 1.0f,z),
			XMFLOAT3(x,y,z + 1.0f),
			XMFLOAT3(x,y,z - 1.0f),
		};

		XMFLOAT3 cameraUps[6] =
		{
			XMFLOAT3(0.0f,1.0f,0.0f),
			XMFLOAT3(0.0f,1.0f,0.0f),
			XMFLOAT3(0.0f,0.0f,-1.0f),
			XMFLOAT3(0.0f,0.0f,1.0f),
			XMFLOAT3(0.0f,1.0f,0.0f),
			XMFLOAT3(0.0f,1.0f,0.0f),
		};

		for (int i = 0; i < 6; i++)
		{
			mDynamicCubeMappingCameras[i].LookAt(cameraPos, cameraTargets[i], cameraUps[i]);
			//mDynamicCubeMappingCameras[i].SetCameraLens(0.5f * 3.141592654f, 1.0f, 0.1f, 1000.0f);
			mDynamicCubeMappingCameras[i].SetCamType(Camera::CameraType::CAM_PERSPECTIVE);;
			mDynamicCubeMappingCameras[i].UpdateViewXM();
		}
	}
	void BuildSrv(Graphics& gfx)
	{
	

		D3D11_TEXTURE2D_DESC depthTexDesc;
		depthTexDesc.Width = 256u;
		depthTexDesc.Height = 256u;
		depthTexDesc.MipLevels = 1;
		depthTexDesc.ArraySize = 1;
		depthTexDesc.SampleDesc.Count = 1;
		depthTexDesc.SampleDesc.Quality = 0;
		depthTexDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
		depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthTexDesc.CPUAccessFlags = 0;
		depthTexDesc.MiscFlags = 0;

		Microsoft::WRL::ComPtr<ID3D11Texture2D> depthTex;
		gfx.pDevice->CreateTexture2D(&depthTexDesc, 0, depthTex.GetAddressOf());

		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
		dsvDesc.Format = depthTexDesc.Format;
		dsvDesc.Flags = 0;
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice = 0;

		gfx.pDevice->CreateDepthStencilView(depthTex.Get(), &dsvDesc, dsv.GetAddressOf());
		
	}

private:
	Camera& mSavedCamera;
	Camera mDynamicCubeMappingCameras[6];
	//Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mDcmRtv[6];
	std::shared_ptr<RenderTargetArray> srv;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> dsv;
	D3D11_VIEWPORT mCubeMapViewport;

};