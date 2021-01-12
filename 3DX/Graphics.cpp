#include "Graphics.h"
#include "DirectXTK/DDSTextureLoader.h"
#include <sstream>
#include "Surface.h"
#include "Camera.h"
#include "RenderTarget.h"
#include "Imgui/imgui_impl_dx11.h"
#include "Imgui/imgui_impl_win32.h"
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


Graphics::Graphics(HWND hWnd)
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
	scd.Flags = 0;

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&scd,
		&pSwapChain,
		&pDevice,
		nullptr,
		&pImmediateContext);

	wrl::ComPtr<ID3D11Texture2D> pBackBuffer ;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBuffer);

	pTarget = std::shared_ptr<RenderTarget>{ new BackBuffer(*this,pBackBuffer.Get()) };
	//pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTarget);
	
	// depth stencil view creation
	/*D3D11_DEPTH_STENCIL_DESC dsd = {};
	dsd.DepthEnable = TRUE;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc = D3D11_COMPARISON_LESS;
	wrl::ComPtr<ID3D11DepthStencilState> pDSS;

	pDevice->CreateDepthStencilState(&dsd, pDSS.GetAddressOf());
	pImmediateContext->OMSetDepthStencilState(pDSS.Get(), 1u);*/
	//wrl::ComPtr<ID3D11DepthStencilView> pdsView;
	/*wrl::ComPtr<ID3D11Texture2D> depthTex;
	D3D11_TEXTURE2D_DESC  depthTexDesc;
	ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
	depthTexDesc.Width = 800;
	depthTexDesc.Height = 600;
	depthTexDesc.MipLevels = 1;
	depthTexDesc.ArraySize = 1;
	depthTexDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthTexDesc.SampleDesc.Count = 1;
	depthTexDesc.SampleDesc.Quality = 0;
	depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthTexDesc.CPUAccessFlags = 0;
	depthTexDesc.MiscFlags = 0;*/
	//pDevice->CreateTexture2D(&depthTexDesc, nullptr, depthTex.GetAddressOf());

	/*D3D11_DEPTH_STENCIL_VIEW_DESC dsv;
	ZeroMemory(&dsv, sizeof(dsv));
	dsv.Format = depthTexDesc.Format;
	dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsv.Texture2D.MipSlice = 0;*/

	
	
	//pImmediateContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), pdsView.Get());
	
	//pBackBuffer->Release();

	D3D11_VIEWPORT vp;
	vp.Width =800.0f;
	vp.Height = 600.0f;
	vp.MinDepth = 0;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;

	pImmediateContext->RSSetViewports(1u, &vp);


	//Imgui setup
	//IMGUI_CHECKVERSION();
	//ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO();
	//ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(this->pDevice.Get(), this->pImmediateContext.Get());
	//ImGui::StyleColorsDark();

}

Graphics::~Graphics()
{
	ImGui_ImplDX11_Shutdown();

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
	
	if (imguiEnabled)
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}


	
	HRESULT hr;
	hr = pSwapChain->Present(0u, 0u);
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

const UINT& Graphics::GetWidth() const
{
	// TODO: insert return statement here
	return 800u;
}

const UINT& Graphics::GetHeight() const
{
	// TODO: insert return statement here
	return 600u;
}




Microsoft::WRL::ComPtr<ID3D11Device> Graphics::pDevice;
Microsoft::WRL::ComPtr<IDXGISwapChain> Graphics::pSwapChain;
Microsoft::WRL::ComPtr<ID3D11DeviceContext> Graphics::pImmediateContext;