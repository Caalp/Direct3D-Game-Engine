#pragma once
//#include "IRenderer.h"
#include "Backend.h"
#include "config.h"
#include <string>
#include "DirectXTK/D3DX11tex.h"
#include "DirectXTK/D3DX11.h"


#pragma comment(lib,"DirectXTK/x86/DirectXTK.lib")
#pragma comment(lib,"DirectXTK/x86/d3dx11d.lib")

using namespace backend;
namespace D3D11
{
	class D3D11VertexBuffer
	{
	public:
		void CreateBuffer(ID3D11Device* device,void* data, U32 size, U32 stride,U32 offset)
		{
			m_stride = stride;
			m_size = size;
			m_offset = offset;
			//--------------------------------------
			D3D11_BUFFER_DESC vbdesc = {};
			vbdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vbdesc.Usage = D3D11_USAGE_DEFAULT;
			vbdesc.CPUAccessFlags = 0u;
			vbdesc.MiscFlags = 0u;
			vbdesc.ByteWidth = size;// size of the vertices array
			vbdesc.StructureByteStride = stride;
			// data for initializing a subresource 
			D3D11_SUBRESOURCE_DATA sd = {};

			sd.pSysMem = data; // pointer to initialization data
			device->CreateBuffer(&vbdesc, &sd, &m_vertexBuffer);
		}
		void Bind(ID3D11DeviceContext* context)
		{
			context->IASetVertexBuffers(0u, 1u, m_vertexBuffer.GetAddressOf(), &m_stride, &m_offset);
		}
	private:
		U32 m_stride;
		U32 m_size;
		U32 m_offset;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
	};

	class D3D11IndexBuffer
	{
	public:
		void CreateBuffer(ID3D11Device* device, void* data, U32 size, U32 stride)
		{
			m_indexCount = size / stride;
			D3D11_BUFFER_DESC indexDesc;
			ZeroMemory(&indexDesc, sizeof(indexDesc));
			indexDesc.Usage = D3D11_USAGE_DEFAULT;
			indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			indexDesc.ByteWidth = size;
			indexDesc.StructureByteStride = stride;
			indexDesc.CPUAccessFlags = 0;
			D3D11_SUBRESOURCE_DATA sd = {};
			sd.pSysMem = data;

			device->CreateBuffer(&indexDesc, &sd, &m_indexBuffer);
		}
		void Bind(ID3D11DeviceContext* context)
		{
			context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R16_UINT,0u);
		}
	private:
		U32 m_indexCount;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
	};

	class D3D11Shader
	{
		
	public:


		Microsoft::WRL::ComPtr<ID3DBlob> GetBlob()
		{
			return m_blob;
		}
		const std::string& GetName() const
		{
			return m_shaderName;
		}
		virtual ~D3D11Shader() = default;
		virtual void CreateShader(ID3D11Device* device, const std::string& filename) {};
		virtual void Bind(ID3D11DeviceContext* context) {};
	protected:
		void ReadToBlob(const std::string& filename)
		{
			m_shaderName = filename;
			// read shader to blob
			std::string fullPath = SHADER_DIRECTORY + m_shaderName;
			D3DReadFileToBlob(std::wstring(fullPath.begin(), fullPath.end()).c_str(), &m_blob);
		}
	protected: 
		Microsoft::WRL::ComPtr<ID3DBlob> m_blob;
		std::string m_shaderName;
	};


	class D3D11VertexShader : public D3D11Shader
	{
	public:
		~D3D11VertexShader() = default;
		void CreateShader(ID3D11Device* device, const std::string& filename) override
		{
			ReadToBlob(filename);
			device->CreateVertexShader(m_blob->GetBufferPointer(), m_blob->GetBufferSize(), nullptr,m_shader.GetAddressOf());
		}
		void Bind(ID3D11DeviceContext* deviceContext) override
		{
			deviceContext->VSSetShader(m_shader.Get(), nullptr, 0u);
		}
	
	private:
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_shader;
	};

	class D3D11PixelShader : public D3D11Shader
	{
	public:
		~D3D11PixelShader() = default;
		void CreateShader(ID3D11Device* device, const std::string& filename) override
		{
			ReadToBlob(filename);
			device->CreatePixelShader(m_blob->GetBufferPointer(), m_blob->GetBufferSize(), nullptr, m_shader.GetAddressOf());
		}
		void Bind(ID3D11DeviceContext* deviceContext) override
		{
			deviceContext->PSSetShader(m_shader.Get(), nullptr, 0u);
		}
	private:
		Microsoft::WRL::ComPtr <ID3D11PixelShader> m_shader;
	};

	class D3D11ConstantBuffer
	{
	public:
		D3D11ConstantBuffer() : m_size(0u) {}
		~D3D11ConstantBuffer()
		{
			m_constantBuffer->Release();
		}
		void CreateBuffer(ID3D11Device* device,U32 size,U32 stride, U32 flags)
		{
			m_size = size;
			D3D11_BUFFER_DESC cbd;
			cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cbd.Usage = D3D11_USAGE_DYNAMIC;
			cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			cbd.MiscFlags = 0u;
			cbd.ByteWidth = size;
			cbd.StructureByteStride = stride;

			device->CreateBuffer(&cbd, 0, &m_constantBuffer);
		}
		void CreateBuffer(ID3D11Device* device,void* data, U32 size, U32 stride, U32 flags)
		{
			m_size = size;
			D3D11_BUFFER_DESC cbd;
			cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cbd.Usage = D3D11_USAGE_DYNAMIC;
			cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			cbd.MiscFlags = 0u;
			cbd.ByteWidth = size;
			cbd.StructureByteStride = stride;

			D3D11_SUBRESOURCE_DATA csd = {};
			csd.pSysMem = data;
			device->CreateBuffer(&cbd, &csd, &m_constantBuffer);
		}

		void Update(ID3D11DeviceContext* context, void* data)
		{
			D3D11_MAPPED_SUBRESOURCE MappedSource;
			context->Map(
				m_constantBuffer.Get(), 0u,
				D3D11_MAP_WRITE_DISCARD, 0u,
				&MappedSource
			);

			memcpy(MappedSource.pData, data,m_size);
			context->Unmap(m_constantBuffer.Get(), 0u);
		}
		virtual void Bind(ID3D11DeviceContext* context, U32 startSlot, U32 numOfBuffers) {};
	protected:
		U32 m_size;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;
	};


	class D3D11VertexLayout
	{
	public:
		void CreateVertexLayout(ID3D11Device* device, void* data, U32 numOfElems, ID3DBlob* vsBlob)
		{
			device->CreateInputLayout((D3D11_INPUT_ELEMENT_DESC*)data, numOfElems, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), m_vertexLayout.GetAddressOf());
		}

		void Bind(ID3D11DeviceContext* context)
		{
			context->IASetInputLayout(m_vertexLayout.Get());
		}
	private:
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_vertexLayout;
	};

	class D3D11VSConstantBuffer : public D3D11ConstantBuffer
	{
	public:
		void Bind(ID3D11DeviceContext* context, U32 startSlot, U32 numOfBuffers) override
		{
			context->VSSetConstantBuffers(startSlot, numOfBuffers, m_constantBuffer.GetAddressOf());
		};
	};

	class D3D11PSConstantBuffer : public D3D11ConstantBuffer
	{
	public:
		void Bind(ID3D11DeviceContext* context, U32 startSlot, U32 numOfBuffers) override
		{
			context->PSSetConstantBuffers(startSlot, numOfBuffers, m_constantBuffer.GetAddressOf());
		};
	};
	

}
class D3D11Renderer :public IRenderer
{
	
public:
	D3D11Renderer()
	{
		//std::cout << "[DX11Renderer] dumb_renderer initialized!\n";
		//float color[] = { 1.0f,0.5f,0.2f,1.0f };
		//pImmediateContext->ClearRenderTargetView(m_mainRT.Get(), color);
		
	}
	~D3D11Renderer()
	{
		delete[] m_shaders;
		delete[] m_constantBuffers;
	}
	void BeginFrame() override
	{
		pImmediateContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);
		//pImmediateContext->ClearDepthStencilView(m_depthBufferView[0].Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);
		float color[] = { 1.0f,0.5f,0.2f,1.0f };
		pImmediateContext->ClearRenderTargetView(m_mainRT.Get(), color);
		//pImmediateContext->ClearRenderTargetView(m_renderTargets[0].Get(), color);
	}
	void Present() override
	{
		pSwapChain->Present(1u, 0u);
	}
	void InitRenderer(const Window* const wnd) override
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
		scd.SampleDesc.Quality = 0;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.BufferCount = 1;
		scd.OutputWindow = wnd->getMainWindow();
		scd.Windowed = TRUE;
		scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			0u,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&scd,
			&(pSwapChain),
			&pDevice,
			nullptr,
			&pImmediateContext);

		//Microsoft::WRL::ComPtr<ID3D11Texture2D> TexBuffer;

		pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &m_backBuffer);

		

		D3D11_TEXTURE2D_DESC textureDesc;
		m_backBuffer->GetDesc(&textureDesc);
		/*width = textureDesc.Width;
		height = textureDesc.Height;*/


		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
		rtvDesc.Format = textureDesc.Format;
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rtvDesc.Texture2D.MipSlice = 0u;

		pDevice->CreateRenderTargetView(m_backBuffer.Get(), &rtvDesc, m_mainRT.GetAddressOf());

		Microsoft::WRL::ComPtr<ID3D11Texture2D> depthTex;
		D3D11_TEXTURE2D_DESC  depthTexDesc{};
		ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
		depthTexDesc.Width = textureDesc.Width;
		depthTexDesc.Height = textureDesc.Height;
		depthTexDesc.MipLevels = 1;
		depthTexDesc.ArraySize = 1;
		depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		// This part is refers to MSAA settings
		depthTexDesc.SampleDesc.Count = 1;
		depthTexDesc.SampleDesc.Quality = 0;
		depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
		depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		pDevice->CreateTexture2D(&depthTexDesc, nullptr, depthTex.GetAddressOf());

		// Create depth Stencil View To bind texture to the device
		D3D11_DEPTH_STENCIL_VIEW_DESC dsv = {};
		dsv.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsv.Texture2D.MipSlice = 0u;
		dsv.Flags = 0;
		pDevice->CreateDepthStencilView(depthTex.Get(), &dsv, m_depthStencilView.GetAddressOf());

	}
	void CreateViewport(float w, float h, float maxDepth, float minDepth, float leftX, float leftY) override
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
	void SetPrimitiveTopology() override
	{
		pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
	void CreateVertexBuffer(VertexBufferHandle handle, void* data, U32 size, U32 stride,U32 offset) override
	{
		//std::cout << "[DX11Renderer] Create vertex buffer func called!\n";
		m_vbh[handle.get()].CreateBuffer(pDevice.Get(),data, size, stride,offset);
	}

	void CreateIndexBuffer(IndexBufferHandle handle, void* data, U32 size, U32 stride) override
	{
		//std::cout << "[DX11Renderer] Create index buffer func called!\n";
		m_ibh[handle.get()].CreateBuffer(pDevice.Get(),data, size, stride);
	}
	void CreateConstantBuffer(ConstantBufferHandle handle, BufferType bufferType, U32 size, U32 stride, U32 flags) override
	{
		switch (bufferType)
		{
		case BufferType::VSConstantBuffer:
			m_constantBuffers[handle.get()] = new D3D11::D3D11VSConstantBuffer();
			m_constantBuffers[handle.get()]->CreateBuffer(pDevice.Get(), size, stride, flags);
			break;
		case BufferType::PSConstantBuffer:
			m_constantBuffers[handle.get()] = new D3D11::D3D11PSConstantBuffer();
			m_constantBuffers[handle.get()]->CreateBuffer(pDevice.Get(), size, stride, flags);
			break;
		default:
			break;
		}
	}
	void BindVertexBuffer(VertexBufferHandle handle) override
	{
		//std::cout << "[DX11Renderer] BindVertexBuffer func called!\n";
		// Put check here if vb is valid
		m_vbh[handle.get()].Bind(pImmediateContext.Get());
	}
	void BindIndexBuffer(IndexBufferHandle handle)  override
	{
		//std::cout << "[DX11Renderer] IndexBufferHandle func called!\n";
		// Put check here if vb is valid
		m_ibh[handle.get()].Bind(pImmediateContext.Get());
	}
	void CreateShader(ShaderHandle handle, const std::string& name, ShaderType type) override
	{
		switch (type)
		{
		case ShaderType::PixelShader:
			m_shaders[handle.get()] = new D3D11::D3D11PixelShader();
			m_shaders[handle.get()]->CreateShader(pDevice.Get(), name);
			break;
		case ShaderType::VertexShader:
			m_shaders[handle.get()] = new D3D11::D3D11VertexShader();
			m_shaders[handle.get()]->CreateShader(pDevice.Get(), name);
			break;
		
		default:
			break;
		}
	}
	void BindShader(ShaderHandle handle) override
	{
		m_shaders[handle.get()]->Bind(pImmediateContext.Get());
	}
	void CreateRenderTarget(RenderTargetHandle handle, TORC_TEXTURE2D_DESC desc) override
	{

		D3D11_TEXTURE2D_DESC textureDesc;
		ZeroMemory(&textureDesc, sizeof(D3D11_TEXTURE2D_DESC));
		textureDesc.Format = (DXGI_FORMAT)desc.format;
		textureDesc.ArraySize = desc.arraySize;
		textureDesc.Width = desc.width;
		textureDesc.Height = desc.height;
		textureDesc.MipLevels = desc.mipLevels;
		textureDesc.BindFlags = desc.bindFlags;
		textureDesc.CPUAccessFlags = desc.cpuAccessFlags;
		textureDesc.MiscFlags = desc.miscFlags;
		textureDesc.SampleDesc.Count =desc.sampleDesc.count;
		textureDesc.SampleDesc.Quality = desc.sampleDesc.quality;

		Microsoft::WRL::ComPtr<ID3D11Texture2D> rtvTex;
		pDevice->CreateTexture2D(&textureDesc, nullptr, rtvTex.GetAddressOf());

		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
		rtvDesc.Format = textureDesc.Format;
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rtvDesc.Texture2D.MipSlice = 0u;
		pDevice->CreateRenderTargetView(rtvTex.Get(), &rtvDesc, m_renderTargets[handle.get()].GetAddressOf());

	}
	void BindRenderTarget(RenderTargetHandle handle) override
	{
		pImmediateContext->OMSetRenderTargets(1u, m_mainRT.GetAddressOf(),m_depthStencilView.Get());
	}
	void BindRenderTarget(RenderTargetHandle handle, DepthBufferHandle depthHandle) override
	{

		pImmediateContext->OMSetRenderTargets(1u, m_renderTargets[handle.get()].GetAddressOf(), m_depthBufferView[depthHandle.get()].Get());

	}
	void CreateConstantBuffer(ConstantBufferHandle handle, BufferType bufferType, void* data, U32 size, U32 stride, U32 flags) override
	{
		switch (bufferType)
		{
		case BufferType::VSConstantBuffer:
			m_constantBuffers[handle.get()] = new D3D11::D3D11VSConstantBuffer();
			m_constantBuffers[handle.get()]->CreateBuffer(pDevice.Get(), data, size, stride, flags);
			break;
		case BufferType::PSConstantBuffer:
			m_constantBuffers[handle.get()] = new D3D11::D3D11PSConstantBuffer();
			m_constantBuffers[handle.get()]->CreateBuffer(pDevice.Get(), data, size, stride, flags);
			break;
		default:
			break;
		}
		
	}
	void UpdateConstantBuffer(ConstantBufferHandle handle, void* data) override
	{
		m_constantBuffers[handle.get()]->Update(pImmediateContext.Get(), data);
	}
	void BindConstantBuffer(ConstantBufferHandle handle, U32 startSlot, U32 numOfBuffers) override
	{
		m_constantBuffers[handle.get()]->Bind(pImmediateContext.Get(), startSlot, numOfBuffers);
	}
	void CreateDepthBuffer(DepthBufferHandle handle, U32 width, U32 height) override
	{
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

		pDevice->CreateTexture2D(&depthTexDesc, nullptr, depthTex.GetAddressOf());

		// Create depth Stencil View To bind texture to the device
		D3D11_DEPTH_STENCIL_VIEW_DESC dsv = {};
		dsv.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsv.Texture2D.MipSlice = 0u;
		dsv.Flags = 0;
		pDevice->CreateDepthStencilView(depthTex.Get(), &dsv, m_depthStencilView.GetAddressOf());
	}
	void CreateDepthBuffer(DepthBufferHandle handle) override
	{
		Microsoft::WRL::ComPtr<ID3D11Texture2D> depthTex;
		D3D11_TEXTURE2D_DESC  depthTexDesc{};
		ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
		depthTexDesc.Width = backend::m_initData.width;
		depthTexDesc.Height = backend::m_initData.height;
		depthTexDesc.MipLevels = 1;
		depthTexDesc.ArraySize = 1;
		depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		// This part is refers to MSAA settings
		depthTexDesc.SampleDesc.Count = 1;
		depthTexDesc.SampleDesc.Quality = 0;
		depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
		depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		pDevice->CreateTexture2D(&depthTexDesc, nullptr, depthTex.GetAddressOf());

		// Create depth Stencil View To bind texture to the device
		D3D11_DEPTH_STENCIL_VIEW_DESC dsv = {};
		dsv.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsv.Texture2D.MipSlice = 0u;
		dsv.Flags = 0;
		pDevice->CreateDepthStencilView(depthTex.Get(), &dsv, m_depthBufferView[handle.get()].GetAddressOf());
	}
	void ClearDepthBuffer(DepthBufferHandle handle, U32 flags, float depthVal, U8 stencilVal) override
	{
		pImmediateContext->ClearDepthStencilView(m_depthStencilView.Get(), flags, depthVal, stencilVal);
	}
	void CreateVertexLayout(VertexLayoutHandle handle, ShaderHandle vsHandle,void* data, U32 elemCount) override
	{
		m_vertexLayout[handle.get()].CreateVertexLayout(pDevice.Get(), data, elemCount, m_shaders[vsHandle.get()]->GetBlob().Get());
	}
	void BindVertexLayout(VertexLayoutHandle handle) override
	{
		m_vertexLayout[handle.get()].Bind(pImmediateContext.Get());
	}

	void DrawIndexed(U32 indexCount, U32 startIndexLocation, int baseVertexLocation) override
	{
		pImmediateContext->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
	}
	void CreateTexture(TextureHandle handle, const char* path) override
	{
		HRESULT hr;
		hr = D3DX11CreateShaderResourceViewFromFile(pDevice.Get(), path, 0, 0, m_shaderResourceViews[handle.get()].GetAddressOf(), 0);

		if (FAILED(hr))
		{
			MessageBox(0, "Loading from file to SRV failed!", "ERROR", 0);
		}
	}
	void BindTexture(TextureHandle handle, uint32_t slot, uint32_t numViews) override
	{
		pImmediateContext->PSSetShaderResources(slot, numViews, m_shaderResourceViews[handle.get()].GetAddressOf());
	}
	void CreateSampler(SamplerHandle handle) override
	{
		D3D11_SAMPLER_DESC samplerDesc = CD3D11_SAMPLER_DESC{ CD3D11_DEFAULT{} };
		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MaxAnisotropy = D3D11_REQ_MAXANISOTROPY;
		pDevice->CreateSamplerState(&samplerDesc, m_samplers[handle.get()].GetAddressOf());
	}
	void BindSampler(SamplerHandle handle) override
	{
		pImmediateContext->PSSetSamplers(0u, 1u, m_samplers[handle.get()].GetAddressOf());
	}
	void BindBackBufferAsRenderTarget() override
	{
		pImmediateContext->OMSetRenderTargets(1u, m_mainRT.GetAddressOf(), m_depthStencilView.Get());
	}
	void SetDepthState() override
	{
		D3D11_DEPTH_STENCIL_DESC DSSDesc = CD3D11_DEPTH_STENCIL_DESC{ CD3D11_DEFAULT{} };
		DSSDesc.DepthEnable = true;
		DSSDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		DSSDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		pDevice->CreateDepthStencilState(&DSSDesc, m_depthStencilState.GetAddressOf());
		pImmediateContext->OMSetDepthStencilState(m_depthStencilState.Get(), 1u);
	}
	void SetRasterizerState() override
	{
		D3D11_RASTERIZER_DESC rsDesc = CD3D11_RASTERIZER_DESC(CD3D11_DEFAULT{});
		rsDesc.FillMode = D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_NONE;
		pDevice->CreateRasterizerState(&rsDesc, m_rasterizerState.GetAddressOf());
		pImmediateContext->RSSetState(m_rasterizerState.Get());
	}
private:


	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pImmediateContext;
	
	D3D11::D3D11VertexBuffer m_vbh[TORC_MAX_VERTEX_BUFFER_COUNT];
	D3D11::D3D11IndexBuffer m_ibh[TORC_MAX_INDEX_BUFFER_COUNT];;
	D3D11::D3D11Shader* m_shaders[100];
	D3D11::D3D11ConstantBuffer* m_constantBuffers[100];
	D3D11::D3D11VertexLayout m_vertexLayout[100];

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargets[8];
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthBufferView[8];
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_shaderResourceViews[16];
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_samplers[16];

	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_backBuffer;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_mainRT;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;

	Microsoft::WRL::ComPtr< ID3D11DepthStencilState> m_depthStencilState;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterizerState;
};