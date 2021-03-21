#include "RenderTarget.h"
#include "DepthStencil.h"
#include "DirectXTK/ScreenGrab.h"
#include "DirectXTK/pch.h"
RenderTarget::RenderTarget(Graphics& gfx, UINT w, UINT h) : width(w),height(h)
{
	renderTargetView.resize(1);
	D3D11_TEXTURE2D_DESC texDesc;
	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //DXGI_FORMAT_D24_UNORM_S8_UINT;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = 0;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> rtvTex;
	GetDevice(gfx)->CreateTexture2D(&texDesc, 0, rtvTex.GetAddressOf());

	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0u;

	
		
	GetDevice(gfx)->CreateRenderTargetView(rtvTex.Get(), &rtvDesc, renderTargetView[0].GetAddressOf());
	
}

RenderTarget::RenderTarget(Graphics& gfx, ID3D11Texture2D* texture)
{
	renderTargetView.resize(1);
	D3D11_TEXTURE2D_DESC textureDesc;
	texture->GetDesc(&textureDesc);
	width = textureDesc.Width;
	height = textureDesc.Height;


	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	rtvDesc.Format = textureDesc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0u;

	GetDevice(gfx)->CreateRenderTargetView(texture, &rtvDesc, renderTargetView[0].GetAddressOf());
}

void RenderTarget::BindAsBuffer(Graphics& gfx)
{
	assert(renderTargetView[0].Get() == nullptr);
	GetContext(gfx)->OMSetRenderTargets(1u, renderTargetView[0].GetAddressOf(), nullptr);
}

void RenderTarget::BindAsBuffer(Graphics& gfx, BufferResource* depth)
{

	// TO DO : Make sure depth variable is not null or other type than DepthStencil !!!
	GetContext(gfx)->OMSetRenderTargets(1u, renderTargetView[0].GetAddressOf(), dynamic_cast<DepthStencil*>(depth)->depthStencilView.Get());
}

void RenderTarget::BindAsBuffer(Graphics& gfx, DepthStencil* depth)
{
	assert(depth != nullptr);
	GetContext(gfx)->OMSetRenderTargets(1u, renderTargetView[0].GetAddressOf(), depth->depthStencilView.Get());
}

void RenderTarget::Clear(Graphics& gfx)
{
	float color[] = { 0.0f,0.0f,0.0f,1.0f };
	Clear(gfx, color);
}

void RenderTarget::Clear(Graphics& gfx, const float color[4])
{
	GetContext(gfx)->ClearRenderTargetView(renderTargetView[0].Get(), color);
}

UINT RenderTarget::GetWidth() const
{
	return width;
}

UINT RenderTarget::GetHeight() const
{
	return height;
}

void RenderTarget::Bind(Graphics& gfx)
{
}

Microsoft::WRL::ComPtr<ID3D11RenderTargetView> RenderTarget::GetRTV(int index)
{
	return renderTargetView[index];
}


ShaderViewRenderTarget::ShaderViewRenderTarget(Graphics& gfx, UINT width, UINT height, UINT slot) : RenderTarget(gfx,width,height),slot(slot)
{
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	renderTargetView[0].Get()->GetResource(resource.GetAddressOf());

	
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.TextureCube.MipLevels = 1u;
	srvDesc.TextureCube.MostDetailedMip = 0;

	GetDevice(gfx)->CreateShaderResourceView(resource.Get(), &srvDesc, shaderResourceView.GetAddressOf());
}

void ShaderViewRenderTarget::BindAsBuffer(Graphics& gfx)
{
	GetContext(gfx)->PSSetShaderResources(1u, 1u, shaderResourceView.GetAddressOf());
}

void ShaderViewRenderTarget::BindAsBuffer(Graphics& gfx, UINT startSlot, UINT numViews)
{
	GetContext(gfx)->PSSetShaderResources(startSlot, numViews, shaderResourceView.GetAddressOf());
}

void ShaderViewRenderTarget::GetResource(ID3D11Resource** resource)
{
	this->shaderResourceView.Get()->GetResource(resource);
}

ID3D11ShaderResourceView* ShaderViewRenderTarget::GetShaderResourceView()
{
	return shaderResourceView.Get();
}



BackBuffer::BackBuffer(Graphics& gfx, ID3D11Texture2D* texture) : RenderTarget(gfx,texture)
{
}

void BackBuffer::Bind(Graphics& gfx)
{
}

//RenderTargetArray::RenderTargetArray(Graphics& gfx, UINT width, UINT Height,UINT arraySize)
//{
//	D3D11_TEXTURE2D_DESC texDesc;
//	texDesc.Width = width;
//	texDesc.Height = height;
//	texDesc.MipLevels = 0;
//	texDesc.ArraySize = arraySize;
//	texDesc.SampleDesc.Count = 1;
//	texDesc.SampleDesc.Quality = 0;
//	texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	texDesc.Usage = D3D11_USAGE_DEFAULT;
//	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
//	texDesc.CPUAccessFlags = 0;
//	texDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS | D3D11_RESOURCE_MISC_TEXTURECUBE;
//
//	Microsoft::WRL::ComPtr<ID3D11Texture2D> cubeTex;
//	GetDevice(gfx)->CreateTexture2D(&texDesc, 0, cubeTex.GetAddressOf());
//
//	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
//	rtvDesc.Format = texDesc.Format;
//	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
//	rtvDesc.Texture2DArray.ArraySize = 1;
//	rtvDesc.Texture2DArray.MipSlice = 0;
//}
