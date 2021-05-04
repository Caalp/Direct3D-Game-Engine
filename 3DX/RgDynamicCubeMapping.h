//#pragma once
//#include "RenderGraph.h"
//#include "Camera.h"
//
//class RgDynamicCubeMapping : public RenderGraph
//{
//public:
//	RgDynamicCubeMapping(Graphics& gfx) : RenderGraph(gfx)
//	{
//
//
//
//	}
//	void BuildCameras()
//	{
//		using namespace DirectX;
//		float x(0.0f), y(0.0f), z(0.0f);
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
//			mDynamicCubeMappingCameras[i].LookAt(cameraPos, cameraTargets[i], cameraUps[i]);
//			mDynamicCubeMappingCameras[i].SetCameraLens(0.5f * 3.141592654f, 1.0f, 0.1f, 1000.0f);
//			mDynamicCubeMappingCameras[i].UpdateViewXM();
//		}
//	}
//	void BuildSrv(Graphics& gfx)
//	{
//		D3D11_TEXTURE2D_DESC texDesc;
//		texDesc.Width = 256u;
//		texDesc.Height = 256u;
//		texDesc.MipLevels = 0;
//		texDesc.ArraySize = 6;
//		texDesc.SampleDesc.Count = 1;
//		texDesc.SampleDesc.Quality = 0;
//		texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//		texDesc.Usage = D3D11_USAGE_DEFAULT;
//		texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
//		texDesc.CPUAccessFlags = 0;
//		texDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS | D3D11_RESOURCE_MISC_TEXTURECUBE;
//
//		Microsoft::WRL::ComPtr<ID3D11Texture2D> cubeTex;
//		gfx.pDevice->CreateTexture2D(&texDesc, 0, cubeTex.GetAddressOf());
//
//		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
//		rtvDesc.Format = texDesc.Format;
//		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
//		rtvDesc.Texture2DArray.ArraySize = 1;
//		rtvDesc.Texture2DArray.MipSlice = 0;
//
//
//		for (int i = 0; i < 6; i++)
//		{
//			rtvDesc.Texture2DArray.FirstArraySlice = i;
//			gfx.pDevice->CreateRenderTargetView(cubeTex.Get(), &rtvDesc, mDcmRtv[i].GetAddressOf());
//		}
//
//
//		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
//		srvDesc.Format = texDesc.Format;
//		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
//		srvDesc.TextureCube.MipLevels = -1;
//		srvDesc.TextureCube.MostDetailedMip = 0;
//
//		gfx.pDevice->CreateShaderResourceView(cubeTex.Get(), &srvDesc, srv.GetAddressOf());
//
//		D3D11_TEXTURE2D_DESC depthTexDesc;
//		depthTexDesc.Width = 256u;
//		depthTexDesc.Height = 256u;
//		depthTexDesc.MipLevels = 1;
//		depthTexDesc.ArraySize = 1;
//		depthTexDesc.SampleDesc.Count = 1;
//		depthTexDesc.SampleDesc.Quality = 0;
//		depthTexDesc.Format = DXGI_FORMAT_D32_FLOAT;
//		depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
//		depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
//		depthTexDesc.CPUAccessFlags = 0;
//		depthTexDesc.MiscFlags = 0;
//
//		Microsoft::WRL::ComPtr<ID3D11Texture2D> depthTex;
//		gfx.pDevice->CreateTexture2D(&depthTexDesc, 0, depthTex.GetAddressOf());
//
//		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
//		dsvDesc.Format = depthTexDesc.Format;
//		dsvDesc.Flags = 0;
//		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
//		dsvDesc.Texture2D.MipSlice = 0;
//
//		gfx.pDevice->CreateDepthStencilView(depthTex.Get(), &dsvDesc, dsv.GetAddressOf());
//	}
//
//private:
//	Camera mDynamicCubeMappingCameras[6];
//	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mDcmRtv[6];
//	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
//	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> dsv;
//
//};