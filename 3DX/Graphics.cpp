#include "Graphics.h"
#include "DDSTextureLoader.h"
#include <sstream>
#include "DDSTextureLoader.h"
#include "Surface.h"
#include "Camera.h"
namespace wrl = Microsoft::WRL;

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib,"DirectXTK.lib")

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

Graphics::Graphics(HWND hWnd,int width,int height)
{
	DXGI_SWAP_CHAIN_DESC scd = {};
	scd.BufferDesc.Width = width;
	scd.BufferDesc.Height = height;
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

	wrl::ComPtr<ID3D11Resource> pBackBuffer ;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
	pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTarget);
	
	// depth stencil view creation
	D3D11_DEPTH_STENCIL_DESC dsd = {};
	dsd.DepthEnable = TRUE;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc = D3D11_COMPARISON_LESS;
	wrl::ComPtr<ID3D11DepthStencilState> pDSS;

	pDevice->CreateDepthStencilState(&dsd, pDSS.GetAddressOf());
	
	
	wrl::ComPtr<ID3D11Texture2D> depthTex; 
	D3D11_TEXTURE2D_DESC  depthTexDesc {};
	ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
	depthTexDesc.Width = width;
	depthTexDesc.Height = height;
	depthTexDesc.MipLevels = 1;
	depthTexDesc.ArraySize = 1;
	depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthTexDesc.SampleDesc.Count = 1;
	depthTexDesc.SampleDesc.Quality = 0;
	depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	

	pDevice->CreateTexture2D(&depthTexDesc, nullptr, depthTex.GetAddressOf());
	

	D3D11_DEPTH_STENCIL_VIEW_DESC dsv = {};
	dsv.Format =DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsv.Texture2D.MipSlice = 0u;
	pDevice->CreateDepthStencilView(depthTex.Get(), &dsv, pdsView.GetAddressOf());

	/*Microsoft::WRL::ComPtr<ID3D11BlendState> blendState;
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;

	blendDesc.RenderTarget[1].BlendEnable = false;
	pDevice->CreateBlendState(&blendDesc, blendState.GetAddressOf());
	pImmediateContext->OMSetBlendState(blendState.Get(), 0, 0xffffffff);
	*/
	
	pImmediateContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), pdsView.Get());
	pImmediateContext->OMSetDepthStencilState(pDSS.Get(), 1u);
	

	D3D11_VIEWPORT vp;
	vp.Width = (float)width;
	vp.Height = (float)height;
	vp.MinDepth = 0;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;

	pImmediateContext->RSSetViewports(1u, &vp);
	//pBackBuffer->Release();




}

void Graphics::DrawTestTriangle()
{
	HRESULT hr;
	// create vertex struct that holds vertex data
	struct Vertex
	{
		float x;
		float y;
		float r;
		float g;
		float b;
	};
	
	const Vertex vertices[] =
	{
		{ 0.0f,0.5f,1.0f,0.0f,0.0f },
		{ 0.5f,-0.5f,0.0f,1.0f,0.0f },
		{ -0.5f,-0.5f,0.0f,0.0f,1.0f },
	};
	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = sizeof(vertices);
	bd.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices;
	(pDevice->CreateBuffer(&bd, &sd, &pVertexBuffer));

	// Bind vertex buffer to pipeline
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	pImmediateContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);


	// create pixel shader
	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	wrl::ComPtr<ID3DBlob> pBlob;
	(D3DReadFileToBlob(L"PixelShader.cso", &pBlob));
	(pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader));

	// bind pixel shader
	pImmediateContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);


	// create vertex shader
	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	//CompileShader(L"VertexShader.cso", "main", "vs_5_0", &pBlob); // compile shader in runtime
	(D3DReadFileToBlob(L"VertexShader.cso", &pBlob));
	(pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader));

	// bind vertex shader
	pImmediateContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);


	// holds a defination about how to feed the vertex data laid out in to memory at stage of input assembler
	wrl::ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "Position",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		//{ "Color",0,DXGI_FORMAT_R32G32B32_FLOAT,0,8u,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};
	(pDevice->CreateInputLayout(
		ied, (UINT)std::size(ied),
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		&pInputLayout
	));

	// bind vertex layout
	pImmediateContext->IASetInputLayout(pInputLayout.Get());


	// bind render target
	pImmediateContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), nullptr);


	// Set primitive topology to triangle list (groups of 3 vertices)
	pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	// configure viewport
	D3D11_VIEWPORT vp;
	vp.Width = 800;
	vp.Height = 600;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pImmediateContext->RSSetViewports(1u, &vp);


	(pImmediateContext->Draw((UINT)std::size(vertices), 0u));

	

	

}



void Graphics::DrawCube(float angle, float x, float y)
{
	HRESULT hr;


	// create struct type that holds vertex data
	struct Vertex
	{
		float x;
		float y;
		float z;
		struct
		{
			float u;
			float v;
		}tex;
	};
	float pitch(0.5f), yaw(0.5f), roll(0.5f);

	DirectX::XMMATRIX r;
	DirectX::XMMATRIX t;

	DirectX::XMMATRIX viewMatrix_;

	DirectX::XMMATRIX projMatrix_;
	r = DirectX::XMMatrixRotationRollPitchYaw(angle, yaw, roll);
	t = DirectX::XMMatrixTranslation(x, y, 4.0f);
	D3D11_BUFFER_DESC bdsc{};
	bdsc.ByteWidth = sizeof(DirectX::XMMATRIX);
	bdsc.Usage = D3D11_USAGE_DYNAMIC;
	bdsc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bdsc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bdsc.MiscFlags = 0u;
	bdsc.StructureByteStride = 0u;

	ID3D11Buffer* worldviewM;
	ID3D11Buffer* projM;
	ID3D11Buffer* viewM;
	D3D11_SUBRESOURCE_DATA InitData = {};
	InitData.pSysMem = &r;


	float scaleX(1.0f), scaleY(1.0f), scaleZ(1.0f);
	viewMatrix_ = DirectX::XMMatrixIdentity();
	projMatrix_ = DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 10.0f);
	viewMatrix_ = DirectX::XMMatrixTranspose(viewMatrix_);
	projMatrix_ = DirectX::XMMatrixTranspose(projMatrix_);


	Vertex vertices[] =
	{

		{ -1.0f,-1.0f,-1.0,{0.0f,0.0f}},
		{ 1.0f,-1.0f,-1.0f,{1.0f,0.0f}},
		{ -1.0f,1.0f,-1.0f,{0.0f,1.0f}},
		{ 1.0f,1.0f,-1.0f,{1.0f,1.0f} },
		{ -1.0f,-1.0f,1.0f,{0.0f,0.0f}},
		{ 1.0f,-1.0f,1.0f,{1.0f,0.0f}	},
		{ -1.0f,1.0f,1.0f,{0.0f,1.0f}	},
		{ 1.0f,1.0f,1.0f,{1.0f,1.0f}	},
		/*{-1.0f,-1.0f,0.0f},
		{1.0f,-1.0f,0.0f},
		{-1.0f,1.0f,0.0f},
		{1.0f,1.0f,0.0f,},*/
	};

	/*vertices[0].tex = { 0.0f,0.0f };
	vertices[1].tex = { 1.0f,0.0f };
	vertices[2].tex = { 0.0f,1.0f };
	vertices[3].tex = { 1.0f,1.0f };*/

	// Creation of Vertexbuffer
	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC vbdesc = {};
	vbdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbdesc.Usage = D3D11_USAGE_DEFAULT;
	vbdesc.CPUAccessFlags = 0u;
	vbdesc.MiscFlags = 0u;
	vbdesc.ByteWidth = sizeof(vertices); // size of the vertices array
	vbdesc.StructureByteStride = sizeof(Vertex);
	// data for initializing a subresource 
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices; // pointer to initialization data
	hr = pDevice->CreateBuffer(&vbdesc, &sd, pVertexBuffer.GetAddressOf());

	// error check for creation of buffer here 


	const UINT stride = sizeof(Vertex); // each stride has the size of element used in buffer 
	const UINT offset = 0u; // offset number of the bytes first element in the buffer and first element will be used 
	// bind an array of vertex buffers to the input assembler 
	pImmediateContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
	ID3D11Buffer* indexBuffer_;
	WORD indices[] =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
		/*0,2,1,
		2,3,1,*/
	};
	D3D11_BUFFER_DESC indexDesc;
	ZeroMemory(&indexDesc, sizeof(indexDesc));
	indexDesc.Usage = D3D11_USAGE_DEFAULT;
	indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexDesc.ByteWidth = sizeof(indices);
	indexDesc.StructureByteStride = sizeof(unsigned short);
	indexDesc.CPUAccessFlags = 0;
	sd.pSysMem = indices;

	hr = pDevice->CreateBuffer(&indexDesc, &sd, &indexBuffer_);
	pImmediateContext->IASetIndexBuffer(indexBuffer_, DXGI_FORMAT_R16_UINT, 0);
	using namespace DirectX;




	wrl::ComPtr<ID3DBlob> pBlob;
	wrl::ComPtr<ID3D11PixelShader> pPixelShader;

	hr = CompileShader(L"ConstantColorPS.hlsl", "main", "ps_5_0", &pBlob); // compile shader in runtime
	//(D3DReadFileToBlob(L"PixelShader.cso", &pBlob));
	(pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader));
	pImmediateContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);

	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	CompileShader(L"ColorBlenderVS.hlsl", "main", "vs_5_0", &pBlob); // compile shader in runtime
	//(D3DReadFileToBlob(L"VertexShader.cso", &pBlob));
	auto bufsize = pBlob->GetBufferPointer();
	auto bb = pBlob->GetBufferSize();
	pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
	pImmediateContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);

	// bind vertex shader

	D3D11_SUBRESOURCE_DATA Init = {};

	DirectX::XMMATRIX worldMatrix_;
	// Texture Mapping Bussiness/////////////////////////////////////////////////////////////////////

	wrl::ComPtr<ID3D11ShaderResourceView> srv;
	wrl::ComPtr<ID3D11SamplerState> pSampler;
	ID3D11Texture2D* ptex;

	D3D11_TEXTURE2D_DESC tex2desc;
	Surface wall = Surface(L"kappa50.bmp");
	const int h = wall.GetHeight();
	const int w = wall.GetWidth();


	//hr = DirectX::CreateDDSTextureFromFile(pDevice.Get(),text,&restex, srv.GetAddressOf(), 0u, nullptr);
	tex2desc.Width = wall.GetWidth();
	tex2desc.Height = wall.GetHeight();
	tex2desc.MipLevels = 1;
	tex2desc.ArraySize = 1;
	tex2desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	tex2desc.SampleDesc.Quality = 0;
	tex2desc.SampleDesc.Count = 1;
	tex2desc.Usage = D3D11_USAGE_DEFAULT;
	tex2desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	tex2desc.CPUAccessFlags = 0;
	tex2desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA sd0 = {};
	sd0.pSysMem = wall.GetColorPointer();
	sd0.SysMemPitch = wall.GetWidth() * sizeof(Color);
	//
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = tex2desc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	pDevice->CreateTexture2D(&tex2desc, &sd0, &ptex);

	pDevice->CreateShaderResourceView(ptex, &srvDesc, srv.GetAddressOf());

	//

	//

	//

	D3D11_SAMPLER_DESC sampler_desc = {};
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	pDevice->CreateSamplerState(&sampler_desc, &pSampler);
	//
	pImmediateContext->PSSetSamplers(0, 1u, pSampler.GetAddressOf());
	//
	pImmediateContext->PSSetShaderResources(0u, 1u, srv.GetAddressOf());
	//
/////////////////////////////////////////////////////////////////////////////////////////////////
	worldMatrix_ = GetCamera();
	worldMatrix_ = DirectX::XMMatrixTranspose(worldMatrix_);
	Init.pSysMem = &worldMatrix_;
	hr = pDevice->CreateBuffer(&bdsc, &Init, &worldviewM);


	/*Init.pSysMem = &viewMatrix_;
	hr = pDevice->CreateBuffer(&bdsc, &Init, &viewM);

	Init.pSysMem = &projMatrix_;
	hr = pDevice->CreateBuffer(&bdsc, &Init, &projM);*/

	//pImmediateContext->UpdateSubresource(worldviewM, 0, 0, &worldMatrix_, 0, 0);
	//pImmediateContext->UpdateSubresource(prM, 0, 0, &viewMatrix_, 0, 0);
	//pImmediateContext->UpdateSubresource(viewM, 0, 0, &pj.projMatrix_, 0, 0);


	pImmediateContext->VSSetConstantBuffers(0u, 1, &worldviewM);
	//pImmediateContext->VSSetConstantBuffers(1u, 1, &viewM);
	//pImmediateContext->VSSetConstantBuffers(2u, 1, &projM);

	//
	// depth tex
	wrl::ComPtr<ID3D11Texture2D> depthTex;
	wrl::ComPtr<ID3D11DepthStencilView> dsView;
	D3D11_TEXTURE2D_DESC  depthTexDesc;
	ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
	depthTexDesc.Width = 800;
	depthTexDesc.Height = 600;
	depthTexDesc.MipLevels = 1;
	depthTexDesc.ArraySize = 1;
	depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthTexDesc.SampleDesc.Count = 1;
	depthTexDesc.SampleDesc.Quality = 0;
	depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthTexDesc.CPUAccessFlags = 0;
	depthTexDesc.MiscFlags = 0;

	hr = pDevice->CreateTexture2D(&depthTexDesc, NULL, depthTex.GetAddressOf());
	// depth stencil view creation
	D3D11_DEPTH_STENCIL_VIEW_DESC dsv;
	ZeroMemory(&dsv, sizeof(dsv));
	dsv.Format = depthTexDesc.Format;
	dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsv.Texture2D.MipSlice = 0;

	hr = pDevice->CreateDepthStencilView(depthTex.Get(), &dsv, &dsView);


	// Bind vertex buffer to pipeline
	wrl::ComPtr<ID3D11InputLayout> pInputLayout; // an input-layout holds definition of how to feed vertex data that laid out in memory
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		//{ "Color",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{"TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	hr = (pDevice->CreateInputLayout(
		ied, (UINT)std::size(ied),
		pBlob->GetBufferPointer(), // pointer to the compiled shader code
		pBlob->GetBufferSize(),
		&pInputLayout
	));
	if (FAILED(hr))
	{
		OutputDebugString("Creating InputLayout Failed!");
		exit(-1);
	}

	pImmediateContext->IASetInputLayout(pInputLayout.Get());
	pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pImmediateContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), nullptr);

	D3D11_VIEWPORT vp;
	vp.Width = 800.0f;
	vp.Height = 600.0f;
	vp.MinDepth = 0;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;

	pImmediateContext->RSSetViewports(1u, &vp);

	pImmediateContext->DrawIndexed((UINT)std::size(indices), 0u, 0u);

	//pSwapChain->Present(0, 0);



	
	
}

void Graphics::DrawIndexed(UINT count)
{
	pImmediateContext->DrawIndexed(count, 0u, 0u);
}

void Graphics::EndFrame()
{
	HRESULT hr;
	hr = pSwapChain->Present(1u, 0u);
}

void Graphics::ClearFrame(float red, float green, float blue)
{
	float color[] = { red,green,blue,1.0f };
	pImmediateContext->ClearRenderTargetView(pTarget.Get(), color);
	pImmediateContext->ClearDepthStencilView(pdsView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);
}

void Graphics::ResetRS()
{
	pImmediateContext->RSSetState(0);
}

void Graphics::ResetDSS()
{
	pImmediateContext->OMSetDepthStencilState(0, 0);
}

void Graphics::ResetBlendState()
{
	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	pImmediateContext->OMSetBlendState(0, blendFactor, 0xffffffff);
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



