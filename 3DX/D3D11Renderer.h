#pragma once
#include "IRenderer.h"
#include "Backend.h"
#include "config.h"

class D3D11Renderer :public IRenderer
{
public:
	D3D11Renderer()
	{
		std::cout << "[DX11Renderer] dumb_renderer initialized!\n";
	}

	virtual void BeginFrame() override
	{

	}
	virtual void Present() override
	{
		GraphicsResources::GetSingleton().pSwapChain->Present(1u, 0u);
	}
	virtual void Init(HWND hwnd, U32 width, U32 height) override
	{
		DXGI_SWAP_CHAIN_DESC scd = {};
		scd.BufferDesc.Width = 0;
		scd.BufferDesc.Height = 0;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferDesc.RefreshRate.Numerator = 0;
		scd.BufferDesc.RefreshRate.Denominator = 0;
		scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		scd.SampleDesc.Count = 1;
		scd.SampleDesc.Quality = 0;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.BufferCount = 1;
		scd.OutputWindow = hwnd;
		scd.Windowed = TRUE;
		scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			0u,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&scd,
			&(GraphicsResources::GetSingleton().pSwapChain),
			&GraphicsResources::GetSingleton().pDevice,
			nullptr,
			&GraphicsResources::GetSingleton().pImmediateContext);

		//Microsoft::WRL::ComPtr<ID3D11Texture2D> TexBuffer;

		GraphicsResources::GetSingleton().pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &m_backBuffer);

		

		D3D11_TEXTURE2D_DESC textureDesc;
		m_backBuffer->GetDesc(&textureDesc);
		width = textureDesc.Width;
		height = textureDesc.Height;


		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
		rtvDesc.Format = textureDesc.Format;
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rtvDesc.Texture2D.MipSlice = 0u;

		GraphicsResources::GetSingleton().pDevice->CreateRenderTargetView(m_backBuffer.Get(), &rtvDesc, m_mainRT.GetAddressOf());

	}
	virtual void CreateVertexBuffer(VertexBufferHandle handle, void* data, U32 size, U32 stride) override
	{
		std::cout << "[DX11Renderer] Create vertex buffer func called!\n";
		m_vbh[handle.idx].Create(data, size, stride);
	}

	virtual void CreateIndexBuffer(IndexBufferHandle handle, void* data, U32 size, U32 stride) override
	{

		std::cout << "[DX11Renderer] Create index buffer func called!\n";
		m_ibh[handle.idx].Create(data, size, stride);
	}

	virtual void BindVertexBuffer(VertexBufferHandle handle) override
	{
		std::cout << "[DX11Renderer] BindVertexBuffer func called!\n";
		// Put check here if vb is valid
		m_vbh[handle.idx].Bind();
	}
	virtual void BindIndexBuffer(IndexBufferHandle handle)  override
	{
		std::cout << "[DX11Renderer] IndexBufferHandle func called!\n";
		// Put check here if vb is valid
		m_ibh[handle.idx].Bind();
	}
	virtual void CreateShader(ShaderHandle handle, std::string name, backend::ShaderType type) override
	{
		m_shaderMgr.Create(handle, name, type);
	}
	virtual void BindShader(ShaderHandle handle, backend::ShaderType type) override
	{
		m_shaderMgr.BindShader(handle, type);
	}
	virtual void CreateRenderTarget(RenderTargetHandle handle, D3D11_TEXTURE2D_DESC desc) override
	{
		Microsoft::WRL::ComPtr<ID3D11Texture2D> rtvTex;
		GraphicsResources::GetSingleton().pDevice->CreateTexture2D(&desc, 0, rtvTex.GetAddressOf());

		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rtvDesc.Texture2D.MipSlice = 0u;



		GraphicsResources::GetSingleton().pDevice->CreateRenderTargetView(rtvTex.Get(), &rtvDesc, m_mainRT.GetAddressOf());

	}
	virtual void BindRenderTarget(RenderTargetHandle handle) override
	{
		GraphicsResources::GetSingleton().pImmediateContext->OMSetRenderTargets(1u, m_mainRT.GetAddressOf(),m_depthStencilView.Get());
	}

	void CreateDepthBuffer(DepthBufferHandle handle, U32 width, U32 height,D3D11_TEXTURE2D_DESC desc) override
	{
		Microsoft::WRL::ComPtr<ID3D11Texture2D> depthTex;
		D3D11_TEXTURE2D_DESC  depthTexDesc{};
		ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
		depthTexDesc.Width = width;
		depthTexDesc.Height = height;
		depthTexDesc.MipLevels = 1;
		depthTexDesc.ArraySize = 1;
		depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		// This part is refers to MSAA settings
		depthTexDesc.SampleDesc.Count = 1;
		depthTexDesc.SampleDesc.Quality = 0;
		depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
		depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		GraphicsResources::GetSingleton().pDevice->CreateTexture2D(&depthTexDesc, nullptr, depthTex.GetAddressOf());

		// Create depth Stencil View To bind texture to the device
		D3D11_DEPTH_STENCIL_VIEW_DESC dsv = {};
		dsv.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsv.Texture2D.MipSlice = 0u;
		dsv.Flags = 0;
		GraphicsResources::GetSingleton().pDevice->CreateDepthStencilView(depthTex.Get(), &dsv, m_depthStencilView.GetAddressOf());
	}
	virtual void ClearDepthBuffer(DepthBufferHandle handle, U32 flags, float depthVal, U8 stencilVal) override
	{
		GraphicsResources::GetSingleton().pImmediateContext->ClearDepthStencilView(m_depthStencilView.Get(), flags, depthVal, stencilVal);
	}
private:
	
	VertexBuffer m_vbh[TORC_MAX_VERTEX_BUFFER_COUNT];
	IndexBuff m_ibh[TORC_MAX_INDEX_BUFFER_COUNT];;
	backend::ShaderManager m_shaderMgr;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_backBuffer;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_mainRT;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
};