#pragma once
#include "BufferResource.h"
#include "Bindable.h"
#include <vector>

class DepthStencil;
// TO DO : set viewport after setting render target



class RenderTarget : public Bindable, public BufferResource
{
public:
	RenderTarget(UINT w, UINT h) : width(w),height(h)
	{

	}
	RenderTarget(Graphics& gfx, UINT width, UINT height);
	RenderTarget(Graphics& gfx, ID3D11Texture2D* texture);
	void BindAsBuffer(Graphics& gfx) override;
	void BindAsBuffer(Graphics& gfx, BufferResource* depth) override;
	void GetResource(ID3D11Resource** resource) override  { }
	// For view count new parameter can be added
	void BindAsBuffer(Graphics& gfx, DepthStencil* depth,UINT rtIndex = 0u);
	void Clear(Graphics& gfx) override;
	void Clear(Graphics& gfx,const float color[4], UINT in = 0u);
	UINT GetWidth() const;
	UINT GetHeight() const;
	void Bind(Graphics& gfx);
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRTV(int index = 0);
protected:
	UINT width;
	UINT height;
	std::vector<Microsoft::WRL::ComPtr<ID3D11RenderTargetView>> renderTargetView;
};


class ShaderViewRenderTarget : public RenderTarget
{

public:
	ShaderViewRenderTarget(UINT w, UINT h) : RenderTarget(w,h)
	{

	}
	ShaderViewRenderTarget(Graphics& gfx, UINT width, UINT Height, UINT slot=0u);

	void BindAsBuffer(Graphics& gfx) override;
	void BindAsBuffer(Graphics& gfx, UINT startSlot, UINT numViews=1u);
	void GetResource(ID3D11Resource** resource) override;
	ID3D11ShaderResourceView* GetShaderResourceView();
protected:
	UINT slot;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
};

class BackBuffer : public RenderTarget
{
public:

	BackBuffer(Graphics& gfx,ID3D11Texture2D* texture);
	void Bind(Graphics& gfx);
};

class RenderTargetArray : public RenderTarget
{
public:
	RenderTargetArray(Graphics& gfx, UINT w, UINT h, UINT arraySize) : RenderTarget(w,h)
	{
		RenderTarget::renderTargetView.resize(arraySize);
		D3D11_TEXTURE2D_DESC texDesc;
		texDesc.Width = width;
		texDesc.Height = height;
		texDesc.MipLevels = 0;
		texDesc.ArraySize = arraySize;
		texDesc.SampleDesc.Count = 1;
		texDesc.SampleDesc.Quality = 0;
		texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		texDesc.CPUAccessFlags = 0;
		texDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS | D3D11_RESOURCE_MISC_TEXTURECUBE;
		
		Microsoft::WRL::ComPtr<ID3D11Texture2D> cubeTex;
		GraphicsResources::GetSingleton().pDevice->CreateTexture2D(&texDesc, 0, cubeTex.GetAddressOf());
		
		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
		rtvDesc.Format = texDesc.Format;
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
		rtvDesc.Texture2DArray.ArraySize = 1;
		rtvDesc.Texture2DArray.MipSlice = 0;


		for (uint32_t i = 0; i < arraySize; i++)
		{
			rtvDesc.Texture2DArray.FirstArraySlice = i;
			GraphicsResources::GetSingleton().pDevice->CreateRenderTargetView(cubeTex.Get(), &rtvDesc, renderTargetView[i].GetAddressOf());
		}
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format = texDesc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
		srvDesc.TextureCube.MipLevels = -1;
		srvDesc.TextureCube.MostDetailedMip = 0;

		GraphicsResources::GetSingleton().pDevice->CreateShaderResourceView(cubeTex.Get(), &srvDesc, shaderResourceView.GetAddressOf());
	}
	ID3D11ShaderResourceView* GetShaderResourceView()
	{
		return shaderResourceView.Get();
	}
	void GetResource(ID3D11Resource** resource) override
	{
		this->shaderResourceView.Get()->GetResource(resource);
	}
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
	//std::vector<
};