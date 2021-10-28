#pragma once
#include "IRenderer.h"
#include "Window.h"

#include "rrTorcDefines.h"


enum class ShaderType
{
	VertexShader,
	PixelShader

};

enum class BufferType
{
	VSConstantBuffer,
	PSConstantBuffer

};

struct RenderJob
{
	uint64_t m_state;
	uint32_t m_stencil;
	int m_depthBias;
	float m_depthBiasClamp;
	float m_slopeScaledDepthBias;


	IndexBufferHandle m_indexBufferHandle;
	VertexBufferHandle m_vertexBufferHandle;


};

struct StateTracker
{
	uint64_t currentState = 0;
	uint32_t currentStencil = 0;
	bool hasStateSet = false;
};

namespace backend
{

	static StateTracker s_states;

	
	enum RendererType
	{
		D3D11,
	};

	

	struct InitInfo
	{
		uint32_t width;
		uint32_t height;
		std::string windowName;
		bool vsync;
		RendererType renderer;
	};

	extern InitInfo m_initData;

	
	// static idx until alloc op
	static uint16_t vlh_idx = 0;
	static uint16_t cbh_idx = 0;
	static uint16_t rtv_idx = 0;

	//DEFINE_HANDLER(VertexBufferHandler)
	constexpr uint8_t k_sortKeyFullscreenLayerNumBits = 2u;
	constexpr uint8_t k_sortKeyFullscreenLayerBitShift = 64u - k_sortKeyFullscreenLayerNumBits;
	constexpr uint64_t k_sortKeyFullscreenMask = uint64_t(3u) << k_sortKeyFullscreenLayerBitShift;
	//constexpr uint8_t k_sortKeyFullscreenLayerWindowed = 1 << k_sortKeyFullscreenLayerBitShift;
	//constexpr uint8_t k_sortKeyFullscreenLayerFu = 1 << k_sortKeyFullscreenLayerBitShift;

	constexpr uint8_t k_sortKeyViewportNumBits = 3u;
	constexpr uint8_t k_sortKeyViewportBitShift = k_sortKeyFullscreenLayerBitShift - k_sortKeyViewportNumBits;
	constexpr uint64_t k_sortKeyViewportMask = uint64_t(7u) << k_sortKeyViewportBitShift;

	constexpr uint8_t k_sortKeyViewportLayerNumBits = 3u;
	constexpr uint8_t k_sortKeyViewportLayerBitShift = k_sortKeyViewportBitShift - k_sortKeyViewportLayerNumBits;
	constexpr uint64_t k_sortKeyViewportLayerMask = uint64_t(7u) << k_sortKeyViewportLayerBitShift;

	constexpr uint8_t k_sortKeyTranslucencyNumBits = 2u;
	constexpr uint8_t k_sortKeyTranslucencyBitShift = k_sortKeyViewportLayerBitShift - k_sortKeyTranslucencyNumBits;
	constexpr uint64_t k_sortKeyTranslucencyMask = uint64_t(3u) << k_sortKeyTranslucencyBitShift;

	constexpr uint8_t k_sortKeyCmdNumBits = 1u;
	constexpr uint8_t k_sortKeyCmdBitShift = k_sortKeyTranslucencyBitShift - k_sortKeyCmdNumBits;
	constexpr uint64_t k_sortKeyCmdMask = uint64_t(1u) << k_sortKeyCmdBitShift;

	constexpr uint8_t k_sortKeyDepthNumBits = 24u;
	constexpr uint8_t k_sortKeyDepthBitShift = k_sortKeyCmdBitShift - k_sortKeyDepthNumBits;
	constexpr uint64_t k_sortKeyDepthMask = uint64_t(0xfffff) << k_sortKeyDepthBitShift;

	constexpr uint8_t k_sortKeyMaterialNumBits = 29u;
	constexpr uint8_t k_sortKeyMaterialBitShift = k_sortKeyDepthBitShift - k_sortKeyMaterialNumBits;
	constexpr uint64_t k_sortKeyMaterialMask = uint64_t(0x1fffffff) << k_sortKeyMaterialBitShift;

	


	struct SortKey
	{
		struct Default
		{
			uint64_t notinuse : 30;
			uint64_t depth : 24;
			uint64_t translucency : 2;
			uint64_t viewportLayer : 3;
			uint64_t viewport : 3;
			uint64_t fullscreenLayer : 2;
		};

		struct Command
		{

		};


		uint64_t m_sortKey;
		uint64_t m_state;
		uint32_t m_stencil;


	};


	void Init(InitInfo init);
	void BeginFrame();
	void EndFrame();
	void ShutDown(); // release all the stuff we have and shut down the backend
	VertexLayoutHandle CreateVertexLayout(ShaderHandle vsHandle, void* data, U32 elemCount);
	void BindVertexLayout(VertexLayoutHandle handle);
	ConstantBufferHandle CreateConstantBuffer(BufferType bufferType, void* data, U32 size, U32 stride, U32 flags);
	ConstantBufferHandle CreateConstantBuffer(BufferType bufferType, U32 size, U32 stride, U32 flags);

	VertexBufferHandle CreateVertexBuffer(void* data, U32 size, U32 stride);

	IndexBufferHandle CreateIndexBuffer(void* data, U32 size, U32 stride);
	ShaderHandle CreateShader(std::string filename, ShaderType type);
	DepthBufferHandle CreateDepthBuffer();

	RenderTargetHandle CreateRenderTarget();
	void BindShader(ShaderHandle handle);
	void BindVertexBuffer(VertexBufferHandle handle);
	void BindIndexBuffer(IndexBufferHandle handle);
	void BindConstantBuffer(ConstantBufferHandle handle, U32 startSlot, U32 numOfBuffers);
	void UpdateConstantBuffer(ConstantBufferHandle handle, void* data);
	void CreateViewport(float w, float h, float maxDepth, float minDepth, float leftX, float leftY);
	RenderTargetHandle CreateRenderTarget(TORC_TEXTURE2D_DESC desc);
	void BindRenderTarget(RenderTargetHandle handle);
	void BindRenderTarget(RenderTargetHandle rtHandle, DepthBufferHandle depthHandle);
	
	void DrawIndexed(U32 indexCount, U32 indexStartLocation, int baseVertexLocation);
	// Reset render target and depth buffer to backbuffer's
	void BindBackBufferAsRenderTarget();
	TextureHandle CreateTexture(const char* filepath);
	void BindTexture(TextureHandle handle, uint32_t slot, uint32_t numViews);
	void BindSampler(const void* data);
	SamplerHandle CreateSampler();
	void SetState(uint64_t state, uint32_t stencil);
};
