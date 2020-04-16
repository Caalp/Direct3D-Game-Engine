#include "Texture.h"
#include "Surface.h"
#include "D3DX11tex.h"
#include "D3DX11.h"
//Texture::Texture(Graphics & gfx, const Surface& s)
//{
//	//D3D11_TEXTURE2D_DESC tex2desc;
//	////hr = DirectX::CreateDDSTextureFromFile(pDevice.Get(),text,&restex, srv.GetAddressOf(), 0u, nullptr);
//	//tex2desc.Width = s.GetWidth();
//	//tex2desc.Height = s.GetHeight();
//	//tex2desc.MipLevels = 0;
//	//tex2desc.ArraySize = 1;
//	//tex2desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
//	//tex2desc.SampleDesc.Quality = 0;
//	//tex2desc.SampleDesc.Count = 1;
//	//tex2desc.Usage = D3D11_USAGE_DEFAULT;
//	//tex2desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
//	//tex2desc.CPUAccessFlags = 0;
//	//tex2desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
//
//	////GetDevice(gfx)->CreateTexture2D(&tex2desc, nullptr, &ptex);
//
//
//	//GetContext(gfx)->UpdateSubresource(ptex.Get(), 0u, nullptr, s.GetColorPointer(), s.GetWidth() * sizeof(Color), 0u);
//
//	///*11_SUBRESOURCE_DATA sd0 = {};
//	//sd0.pSysMem = s.GetColorPointer();
//	//sd0.SysMemPitch = s.GetWidth() * sizeof(float);*/
//
//	//
//
//	//D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
//	//srvDesc.Format = tex2desc.Format;
//	//srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
//	//srvDesc.Texture2D.MostDetailedMip = 0;
//	//srvDesc.Texture2D.MipLevels = -1;
//
//	//
//	//GetDevice(gfx)->CreateShaderResourceView(ptex.Get(), &srvDesc, &srv);
//	//GetContext(gfx)->GenerateMips(srv.Get());
//} 

Texture::Texture(Graphics & gfx, const TextureLoader& s, unsigned int index)
{
	HRESULT hr;
	unsigned int arraySize = s.filePath().size();
	ID3D11Texture2D* textureBuf;
	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	textureDesc.Width = s.GetWidth();
	textureDesc.Height = s.GetHeight();
	textureDesc.MipLevels = 0;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_STAGING;
	textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	textureDesc.MiscFlags = 0;
	GetDevice(gfx)->CreateTexture2D(&textureDesc, NULL, &textureBuf);

	GetContext(gfx)->CopyResource(textureBuf, (ID3D11Resource*)s.GetImageData(0));
	D3D11_MAPPED_SUBRESOURCE  mapResource;
	hr = GetContext(gfx)->Map(textureBuf, 0, D3D11_MAP_READ, NULL, &mapResource);

	//std::vector<ID3D11Texture2D*> srcTex(arraySize);
	//D3D11_TEXTURE2D_DESC tex2desc;
	//ZeroMemory(&tex2desc, sizeof(tex2desc));
	//
	//tex2desc.Width = s.GetWidth();
	//tex2desc.Height = s.GetHeight();
	//tex2desc.MipLevels = 0;
	//tex2desc.ArraySize = 1;
	//tex2desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	//tex2desc.SampleDesc.Quality = 0;
	//tex2desc.SampleDesc.Count = 1;
	//tex2desc.Usage = D3D11_USAGE_STAGING;
	//
	//tex2desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	


	
		/*GetDevice(gfx)->CreateTexture2D(&tex2desc, nullptr, &srcTex[0]);
		GetContext(gfx)->CopyResource(srcTex[0], (ID3D11Resource*)s.GetImageData(0));*/
		//GetContext(gfx)->UpdateSubresource(srcTex[i], 0u, nullptr, s.GetImageData(i), s.GetWidth() * sizeof(float), 0u);
	
		std::vector<ID3D11Texture2D*> srcTex(arraySize);
		for (UINT i = 0; i < arraySize; ++i)
		{
			D3DX11_IMAGE_LOAD_INFO loadInfo;

			loadInfo.Width = D3DX11_FROM_FILE;
			loadInfo.Height = D3DX11_FROM_FILE;
			loadInfo.Depth = D3DX11_FROM_FILE;
			loadInfo.FirstMipLevel = 0;
			loadInfo.MipLevels = D3DX11_FROM_FILE;
			loadInfo.Usage = D3D11_USAGE_STAGING;
			loadInfo.BindFlags = 0;
			loadInfo.CpuAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
			loadInfo.MiscFlags = 0;
			loadInfo.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			loadInfo.Filter = 1;
			loadInfo.MipFilter = 3;
			loadInfo.pSrcInfo = 0;

			D3DX11CreateTextureFromFile(GetDevice(gfx), s.filePath()[i].c_str(),
				&loadInfo, 0, (ID3D11Resource**)&srcTex[i], 0);
		}

	D3D11_TEXTURE2D_DESC texDesc;
	srcTex[0]->GetDesc(&texDesc);
	D3D11_TEXTURE2D_DESC texArrayDesc;
	texArrayDesc.Width = texDesc.Width;
	texArrayDesc.Height = texDesc.Height;
	texArrayDesc.MipLevels = texDesc.MipLevels;
	texArrayDesc.ArraySize = arraySize;
	texArrayDesc.Format = texDesc.Format;
	texArrayDesc.SampleDesc.Quality = 0;
	texArrayDesc.SampleDesc.Count = 1;
	texArrayDesc.Usage = D3D11_USAGE_DEFAULT;
	texArrayDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	texArrayDesc.CPUAccessFlags = 0;
	texArrayDesc.MiscFlags = 0;

	ID3D11Texture2D* texArrayElement;

	GetDevice(gfx)->CreateTexture2D(&texArrayDesc, nullptr, &texArrayElement);
	
		for (unsigned int texElem = 0; texElem < arraySize; texElem++)
		{
			for (unsigned int mipLevel = 0; mipLevel < texArrayDesc.MipLevels; mipLevel++)
			{
				
				D3D11_MAPPED_SUBRESOURCE tex2D;
				GetContext(gfx)->Map(srcTex[texElem], mipLevel, D3D11_MAP_READ, 0, &tex2D);

				GetContext(gfx)->UpdateSubresource(texArrayElement, 
					D3D11CalcSubresource(mipLevel,texElem,texDesc.MipLevels),0,tex2D.pData, tex2D.RowPitch, tex2D.DepthPitch);
				GetContext(gfx)->Unmap(srcTex[texElem], 0);
			}
		}
	
	
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		if (arraySize > 1)
		{
			srvDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
			srvDesc.Texture2DArray.MostDetailedMip = 0;
			srvDesc.Texture2DArray.MipLevels = texDesc.MipLevels;
			srvDesc.Texture2DArray.FirstArraySlice = 0;
			srvDesc.Texture2DArray.ArraySize = arraySize;
		}
		else
		{
			srvDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MostDetailedMip = 0;
			srvDesc.Texture2D.MipLevels = texDesc.MipLevels;
			
		}
	
	


	//GetDevice(gfx)->CreateTexture2D(&tex2desc, &sd0, &ptex);
	GetDevice(gfx)->CreateShaderResourceView(texArrayElement, &srvDesc, &srv);
	//GetContext(gfx)->GenerateMips(srv.Get());
}

void Texture::Bind(Graphics & gfx)
{
	GetContext(gfx)->PSSetShaderResources(0u, 1u, srv.GetAddressOf());
}
