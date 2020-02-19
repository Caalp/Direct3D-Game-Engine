#include "Texture.h"
#include "Surface.h"
#include "TextureLoader.h"
Texture::Texture(Graphics & gfx, const Surface& s)
{
	D3D11_TEXTURE2D_DESC tex2desc;
	//hr = DirectX::CreateDDSTextureFromFile(pDevice.Get(),text,&restex, srv.GetAddressOf(), 0u, nullptr);
	tex2desc.Width = s.GetWidth();
	tex2desc.Height = s.GetHeight();
	tex2desc.MipLevels = 0;
	tex2desc.ArraySize = 1;
	tex2desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	tex2desc.SampleDesc.Quality = 0;
	tex2desc.SampleDesc.Count = 1;
	tex2desc.Usage = D3D11_USAGE_DEFAULT;
	tex2desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	tex2desc.CPUAccessFlags = 0;
	tex2desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

	GetDevice(gfx)->CreateTexture2D(&tex2desc, nullptr, &ptex);


	GetContext(gfx)->UpdateSubresource(ptex.Get(), 0u, nullptr, s.GetColorPointer(), s.GetWidth() * sizeof(Color), 0u);

	/*11_SUBRESOURCE_DATA sd0 = {};
	sd0.pSysMem = s.GetColorPointer();
	sd0.SysMemPitch = s.GetWidth() * sizeof(float);*/

	

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = tex2desc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = -1;

	
	GetDevice(gfx)->CreateShaderResourceView(ptex.Get(), &srvDesc, &srv);
	GetContext(gfx)->GenerateMips(srv.Get());
}

Texture::Texture(Graphics & gfx, const TextureLoader & s)
{
	
	D3D11_TEXTURE2D_DESC tex2desc;
	//hr = DirectX::CreateDDSTextureFromFile(pDevice.Get(),text,&restex, srv.GetAddressOf(), 0u, nullptr);
	tex2desc.Width = s.GetWidth();
	tex2desc.Height = s.GetHeight();
	tex2desc.MipLevels = 0;
	tex2desc.ArraySize = 1;
	tex2desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	tex2desc.SampleDesc.Quality = 0;
	tex2desc.SampleDesc.Count = 1;
	tex2desc.Usage = D3D11_USAGE_DEFAULT;
	tex2desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	tex2desc.CPUAccessFlags = 0;
	tex2desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

	GetDevice(gfx)->CreateTexture2D(&tex2desc, nullptr, &ptex);
	/*D3D11_SUBRESOURCE_DATA sd0 = {};
	sd0.pSysMem = s.GetImageData();
	sd0.SysMemPitch = s.GetWidth()*sizeof(float);*/
	
	GetContext(gfx)->UpdateSubresource(ptex.Get(), 0u, nullptr, s.GetImageData(), s.GetWidth()*sizeof(float), 0u);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = tex2desc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = -1;

	//GetDevice(gfx)->CreateTexture2D(&tex2desc, &sd0, &ptex);
	GetDevice(gfx)->CreateShaderResourceView(ptex.Get(), &srvDesc, &srv);
	GetContext(gfx)->GenerateMips(srv.Get());
}

void Texture::Bind(Graphics & gfx)
{
	GetContext(gfx)->PSSetShaderResources(0u, 1u, srv.GetAddressOf());
}
