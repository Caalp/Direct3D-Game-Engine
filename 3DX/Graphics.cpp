#include "Graphics.h"
#include "DirectXTK/DDSTextureLoader.h"
#include <sstream>
#include "Surface.h"
#include "Camera.h"
#include "RenderTarget.h"
#include "Imgui/imgui_impl_dx11.h"
#include "Imgui/imgui_impl_win32.h"
#include "DirectXTK/ScreenGrab.h"
#include "DepthStencil.h"
#include "DirectXTK/pch.h"
#include "Texture.h"
namespace wrl = Microsoft::WRL;




HRESULT Graphics::CompileShader(LPCWSTR pScrData, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** ppBlobOut)
{
	if (pScrData == nullptr || entryPoint == nullptr || shaderModel == nullptr)
	{
		OutputDebugString("Init of Arg in Shader Compilation failed!");
		return E_INVALIDARG;
	}
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	HRESULT hr = D3DCompileFromFile(pScrData, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel, D3DCOMPILE_DEBUG, 0, &shaderBlob, &errorBlob);

	if (FAILED(hr))
	{
		OutputDebugString("Compilation of Shader is FAILED");
		return E_UNEXPECTED;
	}
	*ppBlobOut = shaderBlob;
	return S_OK;
}

void Graphics::BeginFrame()
{
	if (imguiEnabled)
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}
}

void Graphics::EnableImgui()
{
	imguiEnabled = true;
}

void Graphics::DisableImgui()
{
	imguiEnabled = false;
}


Graphics::Graphics(HWND hWnd, uint32_t w, uint32_t h) : width(w),height(h)
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
	scd.SampleDesc.Quality  = 0;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	scd.OutputWindow = hWnd;
	scd.Windowed = TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	UINT creatingFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
//#if defined(_DEBUG)
//	creatingFlags |= D3D11_CREATE_DEVICE_DEBUG;
//#endif
	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		creatingFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&scd,
		&pSwapChain,
		&pDevice,
		nullptr,
		&pImmediateContext);

	wrl::ComPtr<ID3D11Texture2D> pBackBuffer ;
	wrl::ComPtr<ID3D11Texture2D> pTexBuffer ;
	
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBuffer);

	pTarget = std::shared_ptr<RenderTarget>{ new BackBuffer(*this,pBackBuffer.Get()) };
	//D3D11_TEXTURE2D_DESC texDesc;
	//texDesc.Width = width;
	//texDesc.Height = height;
	//texDesc.MipLevels = 0;
	//texDesc.ArraySize = 1;
	//texDesc.SampleDesc.Count = 1;
	//texDesc.SampleDesc.Quality = 0;
	//texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //DXGI_FORMAT_D24_UNORM_S8_UINT;
	//texDesc.Usage = D3D11_USAGE_DEFAULT;
	//texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	//texDesc.CPUAccessFlags = 0;
	//texDesc.MiscFlags = 0;

	////Microsoft::WRL::ComPtr<ID3D11Texture2D> rtvTex;
	//pDevice->CreateTexture2D(&texDesc, 0, texture.GetAddressOf());

	//pTarget2 = std::shared_ptr<RenderTarget>{ new BackBuffer(*this,texture.Get()) };
	//
	//shaderResourceViewRT = new ShaderViewRenderTarget(*this, 800u, 600u, 0u);
	/*pDevice->QueryInterface<ID3D11Debug>(&debug);
	debug->SetFeatureMask(D3D11_DEBUG_FEATURE_PRESENT_PER_RENDER_OP);*/
	

	if (imguiEnabled)
	{
		ImGui_ImplDX11_Init(this->pDevice.Get(), this->pImmediateContext.Get());
	}
		
	CreateViewport(w, h);

}

Graphics::~Graphics()
{
	if (imguiEnabled)
	{
		ImGui_ImplDX11_Shutdown();
	}
		

}



void Graphics::DrawIndexed(UINT count,uint32_t startIndexLocation, int startVertexLocation)
{
	pImmediateContext->DrawIndexed(count, startIndexLocation, startVertexLocation);
}

void Graphics::Draw(UINT vertexCount, UINT vertexStartLocation)
{
	pImmediateContext->Draw(vertexCount, vertexStartLocation);
}

void Graphics::EndFrame()
{
	HRESULT hr;
	ID3D11Resource* res;


	
	if (imguiEnabled)
	{
	
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}

	hr = pSwapChain->Present(1u, 0u);
	
}

void Graphics::ClearFrame(float red, float green, float blue)
{
	//float color[] = { red,green,blue,1.0f };
	//pImmediateContext->ClearRenderTargetView(pTarget.Get(), color);
}

std::shared_ptr<RenderTarget> Graphics::GetTarget()
{
	return pTarget;
}

bool Graphics::IsImguiEnabled() const
{
	return imguiEnabled;
}

DirectX::XMMATRIX Graphics::GetView() const
{
	return view;
}

void Graphics::SetProjection(DirectX::FXMMATRIX proj) noexcept
{
	projection = proj;
}

void Graphics::SetView(DirectX::FXMMATRIX view)
{
	this->view = view;
}

DirectX::XMMATRIX Graphics::GetProjection() const noexcept
{
	return projection;
}

void Graphics::SetCamera(DirectX::FXMMATRIX cam)
{
	this->camera = cam;
}

DirectX::XMMATRIX Graphics::GetCamera() const
{
	return camera;
}

void Graphics::SetCameraPos(const DirectX::XMFLOAT3 & pos)
{
	cameraPos = pos;
}

DirectX::XMFLOAT3 Graphics::GetCameraPos() const
{
	return cameraPos;
}

void Graphics::CreateViewport(float w, float h, float maxDepth, float minDepth, float leftX, float leftY)
{

	D3D11_VIEWPORT vp;
	vp.Width = w;
	vp.Height = h;
	vp.MinDepth = minDepth;
	vp.MaxDepth = maxDepth;
	vp.TopLeftX = leftX;
	vp.TopLeftY = leftY;

	pImmediateContext->RSSetViewports(1u, &vp);
}

const UINT& Graphics::GetWidth() const
{
	// TODO: insert return statement here
	return width;
}

const UINT& Graphics::GetHeight() const
{
	// TODO: insert return statement here
	return height;
}





Microsoft::WRL::ComPtr<ID3D11Device> Graphics::pDevice;
Microsoft::WRL::ComPtr<IDXGISwapChain> Graphics::pSwapChain;
Microsoft::WRL::ComPtr<ID3D11DeviceContext> Graphics::pImmediateContext;