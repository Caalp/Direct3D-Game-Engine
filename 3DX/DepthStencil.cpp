#include "DepthStencil.h"

DepthStencil::DepthStencil(Graphics& gfx)
	: DepthStencil(gfx, gfx.GetWidth(), gfx.GetHeight())
{}

DepthStencil::DepthStencil(Graphics& gfx, UINT width, UINT height) : width(width), height(height)
{
	// TODO: Enable support for MSAA
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

	GetDevice(gfx)->CreateTexture2D(&depthTexDesc, nullptr, depthTex.GetAddressOf());

	// Create depth Stencil View To bind texture to the device
	D3D11_DEPTH_STENCIL_VIEW_DESC dsv = {};
	dsv.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsv.Texture2D.MipSlice = 0u;
	GetDevice(gfx)->CreateDepthStencilView(depthTex.Get(), &dsv, depthStencilView.GetAddressOf());
	depthTex->Release();
}

DepthStencil::DepthStencil(Graphics& gfx, ID3D11Texture2D* texture, UINT state)
{
	D3D11_TEXTURE2D_DESC depthTexDesc;
	texture->GetDesc(&depthTexDesc);
	width = depthTexDesc.Width;
	height = depthTexDesc.Height;

	GetDevice(gfx)->CreateTexture2D(&depthTexDesc, nullptr, &texture);

	// Create depth Stencil View To bind texture to the device
	D3D11_DEPTH_STENCIL_VIEW_DESC dsv = {};
	dsv.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsv.Texture2D.MipSlice = 0u;
	GetDevice(gfx)->CreateDepthStencilView(texture, &dsv, depthStencilView.GetAddressOf());
	texture->Release();
}

void DepthStencil::BindAsBuffer(Graphics& gfx)
{ /* Set the depth State; */ }

void DepthStencil::BindAsBuffer(Graphics& gfx, BufferResource* depth)
{}

void DepthStencil::Clear(Graphics& gfx)
{
	GetContext(gfx)->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

OutputOnlyDepthBuffer::OutputOnlyDepthBuffer(Graphics& gfx) : OutputOnlyDepthBuffer(gfx, gfx.GetWidth(), gfx.GetHeight())
{}

OutputOnlyDepthBuffer::OutputOnlyDepthBuffer(Graphics& gfx, UINT width, UINT height) : DepthStencil(gfx, width, height)
{}

void OutputOnlyDepthBuffer::Bind(Graphics& gfx)
{}