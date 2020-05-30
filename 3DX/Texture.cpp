#include "Texture.h"
#include "Surface.h"
#include "D3DX11tex.h"
#include "D3DX11.h"

//Texture::Texture(Graphics& gfx, const char* filepath,unsigned int index)
//{
//	//bufferSlot = index;
//	//HRESULT hr;
//	//unsigned int arraySize = s.filePath().size();
//
//	//std::vector<ID3D11Texture2D*> srcTex(arraySize);
//	//for (UINT i = 0; i < arraySize; ++i)
//	//{
//	//	D3DX11_IMAGE_LOAD_INFO loadInfo;
//
//	//	loadInfo.Width = D3DX11_FROM_FILE;
//	//	loadInfo.Height = D3DX11_FROM_FILE;
//	//	loadInfo.Depth = D3DX11_FROM_FILE;
//	//	loadInfo.FirstMipLevel = 0;
//	//	loadInfo.MipLevels = D3DX11_FROM_FILE;
//	//	loadInfo.Usage = D3D11_USAGE_STAGING;
//	//	loadInfo.BindFlags = 0;
//	//	loadInfo.CpuAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
//	//	loadInfo.MiscFlags = 0;
//	//	loadInfo.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
//	//	loadInfo.Filter = 1;
//	//	loadInfo.MipFilter = 3;
//	//	loadInfo.pSrcInfo = 0;
//
//	//	D3DX11CreateTextureFromFile(GetDevice(gfx), s.filePath()[i].c_str(),
//	//		&loadInfo, 0, (ID3D11Resource**)&srcTex[i], 0);
//	//}
//
//	//D3D11_TEXTURE2D_DESC texDesc;
//	//srcTex[0]->GetDesc(&texDesc);
//	//D3D11_TEXTURE2D_DESC texArrayDesc;
//	//texArrayDesc.Width = texDesc.Width;
//	//texArrayDesc.Height = texDesc.Height;
//	//texArrayDesc.MipLevels = texDesc.MipLevels;
//	//texArrayDesc.ArraySize = arraySize;
//	//texArrayDesc.Format = texDesc.Format;
//	//texArrayDesc.SampleDesc.Quality = 0;
//	//texArrayDesc.SampleDesc.Count = 1;
//	//texArrayDesc.Usage = D3D11_USAGE_DEFAULT;
//	//texArrayDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
//	//texArrayDesc.CPUAccessFlags = 0;
//	//texArrayDesc.MiscFlags = 0;
//
//	//ID3D11Texture2D* texArrayElement;
//
//	//GetDevice(gfx)->CreateTexture2D(&texArrayDesc, nullptr, &texArrayElement);
//
//	//for (unsigned int texElem = 0; texElem < arraySize; texElem++)
//	//{
//	//	for (unsigned int mipLevel = 0; mipLevel < texArrayDesc.MipLevels; mipLevel++)
//	//	{
//
//	//		D3D11_MAPPED_SUBRESOURCE tex2D;
//	//		GetContext(gfx)->Map(srcTex[texElem], mipLevel, D3D11_MAP_READ, 0, &tex2D);
//
//	//		GetContext(gfx)->UpdateSubresource(texArrayElement,
//	//			D3D11CalcSubresource(mipLevel, texElem, texDesc.MipLevels), 0, tex2D.pData, tex2D.RowPitch, tex2D.DepthPitch);
//	//		GetContext(gfx)->Unmap(srcTex[texElem], 0);
//	//	}
//	//}
//
//
//	//D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
//	//if (arraySize > 1)
//	//{
//	//	srvDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
//	//	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
//	//	srvDesc.Texture2DArray.MostDetailedMip = 0;
//	//	srvDesc.Texture2DArray.MipLevels = texDesc.MipLevels;
//	//	srvDesc.Texture2DArray.FirstArraySlice = 0;
//	//	srvDesc.Texture2DArray.ArraySize = arraySize;
//	//}
//	//else
//	//{
//	//	srvDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
//	//	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
//	//	srvDesc.Texture2D.MostDetailedMip = 0;
//	//	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;
//
//	//}
//
//
//
//
//	////GetDevice(gfx)->CreateTexture2D(&tex2desc, &sd0, &ptex);
//	//GetDevice(gfx)->CreateShaderResourceView(texArrayElement, &srvDesc, &srv);
//	////GetContext(gfx)->GenerateMips(srv.Get());
//}

Texture::Texture(Graphics & gfx, const char * filePath, unsigned int bufferSlot)
{
	this->bufferSlot = bufferSlot;
	HRESULT hr;

	hr = D3DX11CreateShaderResourceViewFromFile(GetDevice(gfx), filePath, 0, 0, &srv, 0);
	if (FAILED(hr))
	{
		MessageBox(0, "Loading from file to SRV failed!", "ERROR", 0);
	}
}

Texture::Texture(Graphics & gfx, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> paramSrv, unsigned int bufferSlot)
{
	this->bufferSlot = bufferSlot;
	srv = paramSrv;
}



void Texture::Bind(Graphics & gfx)
{

	GetContext(gfx)->PSSetShaderResources(bufferSlot, 1u, srv.GetAddressOf());

}

