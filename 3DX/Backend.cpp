#include "defines.h"

#include "Backend.h"
#include "Command.h"
#include "HandleAlloc.h"
#include "D3D11Renderer.h"

#ifdef IMGUI
#include "Imgui/imgui_impl_dx11.h"
#include "Imgui/imgui_impl_win32.h"
#endif


namespace backend
{
	VertexBufferHandle m_vbh[TORC_MAX_VERTEX_BUFFER_COUNT];
	IndexBufferHandle m_ibh[TORC_MAX_INDEX_BUFFER_COUNT];
	ConstantBufferHandle m_cbh[TORC_MAX_VERTEX_BUFFER_COUNT];
	DepthBufferHandle m_dbh[TORC_MAX_INDEX_BUFFER_COUNT];
	VertexLayoutHandle m_vlh[TORC_MAX_INDEX_BUFFER_COUNT];
	RenderTargetHandle m_rth[TORC_MAX_INDEX_BUFFER_COUNT];
	TextureHandle m_th[16];
	SamplerHandle m_sh[16];


	FixedHandleAlloc<TORC_MAX_VERTEX_BUFFER_COUNT> m_vertexBufferHandle;
	FixedHandleAlloc<TORC_MAX_INDEX_BUFFER_COUNT> m_indexBufferHandle;
	FixedHandleAlloc<TORC_MAX_SHADER_COUNT> m_shaderHandle;
	FixedHandleAlloc<TORC_MAX_RENDER_TARGET_COUNT> m_renderTargetHandle;
	FixedHandleAlloc<TORC_MAX_DEPTH_BUFFER_COUNT> m_depthBufferHandle;
	FixedHandleAlloc<16> m_textureHandle;
	FixedHandleAlloc<16> m_samplerHandle;
	
	
	InitInfo m_initData;
	Window* wnd;
	IRenderer* m_renderer;
	
	void BeginFrame()
	{
#ifdef IMGUI
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
#endif
		m_renderer->BeginFrame();
	}
	void EndFrame()
	{
#ifdef IMGUI
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
#endif
		m_renderer->Present();
	}
	void ShutDown()
	{
		delete m_renderer;
		delete wnd;
	}
	void Init(InitInfo init)
	{
		
		m_initData = init;

		switch (init.renderer)
		{
		case RendererType::D3D11:
			m_renderer = new D3D11Renderer();
			break;
		default:
			break;
		}
		wnd = new Window(m_initData.width, m_initData.height, m_initData.windowName.c_str());
#ifdef IMGUI
	ImGui_ImplWin32_Init(wnd->getMainWindow());
#endif
		m_renderer->InitRenderer(wnd);
		
		RenderTargetHandle rt;
		DepthBufferHandle depth;
		depth.idx = 0;
		rt.idx = 0;
		//m_renderer->CreateDepthBuffer(depth);
		m_renderer->BindRenderTarget(rt);
		m_renderer->SetPrimitiveTopology();
		//m_renderer->SetDepthState();
		//m_renderer->SetRasterizerState();

		
	}

	VertexLayoutHandle CreateVertexLayout(ShaderHandle vsHandle, void* data, U32 elemCount)
	{
		VertexLayoutHandle handle;
		handle.idx = vlh_idx;
		m_vlh[vlh_idx] = handle;
		vlh_idx++;

		// call to the backend
		m_renderer->CreateVertexLayout(handle, vsHandle, data, elemCount);

		return handle;
	}
	void BindVertexLayout(VertexLayoutHandle handle)
	{
		m_renderer->BindVertexLayout(handle);
	}
	ConstantBufferHandle CreateConstantBuffer(BufferType bufferType, void* data, U32 size, U32 stride, U32 flags)
	{
		ConstantBufferHandle cbh;
		cbh.idx = cbh_idx;
		m_cbh[cbh_idx] = cbh;
		cbh_idx++;

		// call to the backend
		m_renderer->CreateConstantBuffer(cbh, bufferType, data, size, stride, flags);

		return cbh;
	}
	ConstantBufferHandle CreateConstantBuffer(BufferType bufferType,U32 size, U32 stride, U32 flags)
	{
		ConstantBufferHandle cbh;
		cbh.idx = cbh_idx;
		m_cbh[cbh_idx] = cbh;
		cbh_idx++;

		// call to the backend
		m_renderer->CreateConstantBuffer(cbh, bufferType, size, stride, flags);

		return cbh;
	}

	VertexBufferHandle CreateVertexBuffer(void* data, U32 size, U32 stride)
	{
		VertexBufferHandle vbh = {m_vertexBufferHandle.Alloc()};
		// call to the backend
		m_renderer->CreateVertexBuffer(vbh, data, size, stride);

		return vbh;
	}

	IndexBufferHandle CreateIndexBuffer(void* data, U32 size, U32 stride)
	{
		IndexBufferHandle ibh = {m_indexBufferHandle.Alloc()};
		// call to the backend
		m_renderer->CreateIndexBuffer(ibh, data, size, stride);

		return ibh;
	}
	ShaderHandle CreateShader(std::string filename, ShaderType type)
	{
		ShaderHandle sh = {m_shaderHandle.Alloc()};

		m_renderer->CreateShader(sh, filename, type);
		return sh;
	}
	DepthBufferHandle CreateDepthBuffer()
	{
		assert(m_renderer != nullptr);
		DepthBufferHandle dbh = { m_depthBufferHandle.Alloc() };
		m_renderer->CreateDepthBuffer(dbh);
		return dbh;
	}

	RenderTargetHandle CreateRenderTarget()
	{
		RenderTargetHandle sh;
		sh.idx = rtv_idx;
		m_rth[sh.idx] = sh;
		rtv_idx++;

		m_renderer->CreateRenderTarget(sh, {});
		return sh;
	}
	void BindShader(ShaderHandle handle)
	{
		m_renderer->BindShader(handle);
	}
	void BindVertexBuffer(VertexBufferHandle handle)
	{
		m_renderer->BindVertexBuffer(handle);
	}
	void BindIndexBuffer(IndexBufferHandle handle)
	{
		m_renderer->BindIndexBuffer(handle);
	}
	void BindConstantBuffer(ConstantBufferHandle handle, U32 startSlot, U32 numOfBuffers)
	{
		m_renderer->BindConstantBuffer(handle, startSlot, numOfBuffers);
	}
	void UpdateConstantBuffer(ConstantBufferHandle handle, void* data)
	{
		m_renderer->UpdateConstantBuffer(handle, data);
	}
	void CreateViewport(float w, float h, float maxDepth, float minDepth, float leftX, float leftY)
	{
		m_renderer->CreateViewport(w, h, maxDepth, minDepth, leftX, leftY);
	}
	RenderTargetHandle CreateRenderTarget(TORC_TEXTURE2D_DESC desc)
	{
		assert(m_renderer != nullptr);

		RenderTargetHandle rth = { m_renderTargetHandle.Alloc() };
		m_renderer->CreateRenderTarget(rth, desc);
		return rth;
	}
	void BindRenderTarget(RenderTargetHandle handle)
	{
		assert(m_renderer != nullptr);
		m_renderer->BindRenderTarget(handle);
	}
	void BindRenderTarget(RenderTargetHandle rtHandle, DepthBufferHandle depthHandle)
	{
		assert(m_renderer != nullptr);
		m_renderer->BindRenderTarget(rtHandle,depthHandle);
	}
	void DrawIndexed(U32 indexCount, U32 indexStartLocation, int baseVertexLocation)
	{
		m_renderer->DrawIndexed(indexCount, indexStartLocation, baseVertexLocation);
	}
	void BindBackBufferAsRenderTarget()
	{
		assert(m_renderer != nullptr);
		m_renderer->BindBackBufferAsRenderTarget();
	}
	void BindTexture(TextureHandle handle, uint32_t slot, uint32_t numViews)
	{
		assert(m_renderer != nullptr);
		m_renderer->BindTexture(handle, slot,numViews);
	}
	void BindSampler(const void* data)
	{
		
		assert(m_renderer != nullptr);
		const command::BindSampler* bindSampler = reinterpret_cast<const command::BindSampler*>(data);
		m_renderer->BindSampler(bindSampler->Sampler);
		
	}
	SamplerHandle CreateSampler()
	{
		assert(m_renderer != nullptr);
		SamplerHandle sh = { m_samplerHandle.Alloc() };
		m_renderer->CreateSampler(sh);
		return sh;
	}
	TextureHandle CreateTexture(const char* filepath)
	{
		assert(m_renderer != nullptr);
		TextureHandle th = { m_textureHandle.Alloc() };
		m_renderer->CreateTexture(th, filepath);
		return th;
	}

	void SetState(uint64_t state, uint32_t stencil)
	{
		m_renderer->SetState(state, stencil);
	}
}