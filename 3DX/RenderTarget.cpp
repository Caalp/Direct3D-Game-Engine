#include "RenderTarget.h"
#include "DepthStencil.h"

RenderTarget::RenderTarget(Graphics& gfx, UINT w, UINT h) : width(w),height(h)
{
	D3D11_TEXTURE2D_DESC texDesc;
	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.MipLevels = 0;
	texDesc.ArraySize = 1;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = 0;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> rtvTex;
	GetDevice(gfx)->CreateTexture2D(&texDesc, 0, rtvTex.GetAddressOf());

	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	rtvDesc.Format = texDesc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0u;

	
		
	GetDevice(gfx)->CreateRenderTargetView(rtvTex.Get(), &rtvDesc, renderTargetView.GetAddressOf());
	
}

RenderTarget::RenderTarget(Graphics& gfx, ID3D11Texture2D* texture)
{
	D3D11_TEXTURE2D_DESC textureDesc;
	texture->GetDesc(&textureDesc);
	width = textureDesc.Width;
	height = textureDesc.Height;


	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	rtvDesc.Format = textureDesc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0u;

	GetDevice(gfx)->CreateRenderTargetView(texture, &rtvDesc, renderTargetView.GetAddressOf());
}

void RenderTarget::BindAsBuffer(Graphics& gfx)
{
	assert(renderTargetView.Get() == nullptr);
	GetContext(gfx)->OMSetRenderTargets(1u, renderTargetView.GetAddressOf(), nullptr);
}

void RenderTarget::BindAsBuffer(Graphics& gfx, BufferResource* depth)
{

	// TO DO : Make sure depth variable is not null or other type than DepthStencil !!!
	GetContext(gfx)->OMSetRenderTargets(1u, renderTargetView.GetAddressOf(), dynamic_cast<DepthStencil*>(depth)->depthStencilView.Get());
}

void RenderTarget::BindAsBuffer(Graphics& gfx, DepthStencil* depth)
{
	assert(depth != nullptr);
	GetContext(gfx)->OMSetRenderTargets(1u, renderTargetView.GetAddressOf(), depth->depthStencilView.Get());
}

void RenderTarget::Clear(Graphics& gfx)
{
	float color[] = { 0.0f,0.0f,0.0f,1.0f };
	Clear(gfx, color);
}

void RenderTarget::Clear(Graphics& gfx, const float color[4])
{
	GetContext(gfx)->ClearRenderTargetView(renderTargetView.Get(), color);
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


ShaderViewRenderTarget::ShaderViewRenderTarget(Graphics& gfx, UINT width, UINT height, UINT slot) : RenderTarget(gfx,width,height),slot(slot)
{
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	renderTargetView.Get()->GetResource(resource.GetAddressOf());

	
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.TextureCube.MipLevels = -1;
	srvDesc.TextureCube.MostDetailedMip = 0;

	GetDevice(gfx)->CreateShaderResourceView(resource.Get(), &srvDesc, shaderResourceView.GetAddressOf());
}

void ShaderViewRenderTarget::BindAsBuffer(Graphics& gfx)
{
	GetContext(gfx)->PSSetShaderResources(1u, 1u, shaderResourceView.GetAddressOf());
}



BackBuffer::BackBuffer(Graphics& gfx, ID3D11Texture2D* texture) : RenderTarget(gfx,texture)
{
}

void BackBuffer::Bind(Graphics& gfx)
{
}
