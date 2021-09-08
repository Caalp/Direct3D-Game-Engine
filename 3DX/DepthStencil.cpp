#include "DepthStencil.h"
#include "additional_headers.h"
#include "Channels.h"
#include "Technique.h"
#include "Entity.h"
#include "DrawCallDispatch.h"

DepthStencil::DepthStencil(Graphics& gfx) : DepthStencil(gfx,gfx.GetWidth(),gfx.GetHeight())
{
}

DepthStencil::DepthStencil(Graphics& gfx, UINT width, UINT height) : width(width),height(height)
{
	//Create default DSS state along with constructor




	// TO DO: Enable support for MSAA
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
	GraphicsResources::GetSingleton().pDevice->CreateDepthStencilView(depthTex.Get(), &dsv, depthStencilView.GetAddressOf());

	//Technique textured_object("box", channel1::defaultChannel);
	//{
	//	{

	//		Step s1{ "default" };


	//		s1.AddBind(std::make_shared<PixelShader>(gfx, "PS_TextureMapping.cso"));
	//		//auto vs = std::make_shared<VertexShader>(gfx, "VS_TextureMapping.cso");
	//		//auto vsBlob = vs->GetVBlob();
	//		s1.AddBind(std::move(vs));
	//		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	//		{
	//			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
	//			{ "TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0 }
	//		};

	//		s1.AddBind(std::make_shared<InputLayout>(gfx, ied, vsBlob));




	//		s1.AddBind(std::make_shared<SamplerState>(gfx));
	//		s1.AddBind(std::make_shared<Texture>(gfx, "../Textures/WoodCrate01.dds"));
	//		/*Entity* entt = GetScene().CreateEntity(this);
	//		entt->AddComponent<Transformation>(DirectX::XMMatrixTranslation(0.0f, -2.0f, -5.0f));
	//		uint32_t mID = std::move(entt->GetID());*/
	//		//

	//		//s1.AddBind(std::make_shared<DrawIndexed>(0, indexBuffer.get()->GetIndexCount()));
	//		//s1.AddBind(std::make_shared<TransformationBuffer>(gfx, mID));
	//		textured_object.AddStep(s1);
	//	}
	//	
	//}
	//AppendTechnique(textured_object);
	//depthTex->Release();
}

DepthStencil::DepthStencil(Graphics& gfx, UINT width, UINT height, UINT state) : width(width), height(height)
{
	//ID3D11Texture2D* depthTexture;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthTexture;
	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(D3D11_TEXTURE2D_DESC));
	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_DEPTH_STENCIL;

	GraphicsResources::GetSingleton().pDevice->CreateTexture2D(&textureDesc, nullptr, depthTexture.GetAddressOf());

	D3D11_DEPTH_STENCIL_VIEW_DESC dsv = {};
	dsv.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsv.Texture2D.MipSlice = 0u;
	dsv.Flags = 0;
	GraphicsResources::GetSingleton().pDevice->CreateDepthStencilView(depthTexture.Get(), &dsv, depthStencilView.GetAddressOf());

	D3D11_SHADER_RESOURCE_VIEW_DESC shadowSrv = {};
	shadowSrv.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	shadowSrv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shadowSrv.Texture2D.MipLevels = 1u;
	shadowSrv.Texture2D.MostDetailedMip = 0;

	GraphicsResources::GetSingleton().pDevice->CreateShaderResourceView(depthTexture.Get(), &shadowSrv, shaderResourceView.GetAddressOf());

	// TO DO: if released sometimes complains about returning nullptr !
	//depthTexture->Release();
}


DepthStencil::DepthStencil(Graphics& gfx, ID3D11Texture2D* texture, UINT state)
{

	//D3D11_TEXTURE2D_DESC depthTexDesc;
	//texture->GetDesc(&depthTexDesc);
	//width = depthTexDesc.Width;
	//height = depthTexDesc.Height;

	//GetDevice(gfx)->CreateTexture2D(&depthTexDesc, nullptr, &texture);

	//// Create depth Stencil View To bind texture to the device
	//D3D11_DEPTH_STENCIL_VIEW_DESC dsv = {};
	//dsv.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	//dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	//dsv.Texture2D.MipSlice = 0u;
	//GetDevice(gfx)->CreateDepthStencilView(texture, &dsv, depthStencilView.GetAddressOf());
	//texture->Release();
}

void DepthStencil::BindAsBuffer(Graphics& gfx)
{
	GraphicsResources::GetSingleton().pImmediateContext->OMSetRenderTargets(0, nullptr, depthStencilView.Get());
}

void DepthStencil::BindAsBuffer(Graphics& gfx, BufferResource* depth)
{
}

void DepthStencil::Clear(Graphics& gfx)
{
	GraphicsResources::GetSingleton().pImmediateContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f,0.0f);
}

OutputOnlyDepthBuffer::OutputOnlyDepthBuffer(Graphics& gfx) : OutputOnlyDepthBuffer(gfx,gfx.GetWidth(),gfx.GetHeight())
{
}

OutputOnlyDepthBuffer::OutputOnlyDepthBuffer(Graphics& gfx, UINT width, UINT height) :DepthStencil(gfx,width,height)
{
}

void OutputOnlyDepthBuffer::Bind(Graphics& gfx)
{

}

ShaderResourceDS::ShaderResourceDS(Graphics& gfx) : ShaderResourceDS(gfx,gfx.GetWidth(),gfx.GetHeight())
{
}

ShaderResourceDS::ShaderResourceDS(Graphics& gfx, UINT width, UINT height) : DepthStencil(gfx, width, height, 0)
{
}

void ShaderResourceDS::Bind(Graphics& gfx)
{
}
