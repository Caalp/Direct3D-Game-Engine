#pragma once
#include <string>

struct VertexBufferHandle;
struct IndexBufferHandle;
struct ShaderHandle;
struct DepthBufferHandle;
struct RenderTargetHandle;
struct ConstantBufferHandle;
struct VertexLayoutHandle;

struct TextureHandle;
struct SamplerHandle;


struct Init;
enum class ShaderType;
enum class BufferType;

class Window;
struct TORC_TEXTURE2D_DESC;
class IRenderer
{
public:
	virtual void BeginFrame() = 0;
	virtual void Present() = 0;
	virtual void InitRenderer(const Window* const wnd) = 0;
	virtual ~IRenderer() = default;
	//virtual void Shutdown() = 0;
	//virtual void CreateShader(ShaderHandle shaderHandle) = 0;
	//virtual void DestroyShader(const char* VSfilename) = 0;
	//virtual void CreateGeometryShader(const char* GSfilename) = 0;
	//virtual void CreateHullShader(const char* HSfilename) = 0;
	//virtual void CreateDomainShader(const char* DSfilename) = 0;
	
	virtual void CreateVertexBuffer(VertexBufferHandle handle,void* data, U32 size, U32 stride,U32 offset=0u) = 0;
	virtual void CreateConstantBuffer(ConstantBufferHandle handle,BufferType bufferType, void* data, U32 size, U32 stride, U32 flags) = 0;
	virtual void CreateConstantBuffer(ConstantBufferHandle handle, BufferType bufferType, U32 size, U32 stride, U32 flags) = 0;
	virtual void BindConstantBuffer(ConstantBufferHandle handle, U32 startSlot, U32 numOfBuffers) = 0;
	virtual void UpdateConstantBuffer(ConstantBufferHandle handle, void* data) = 0;
	virtual void BindVertexBuffer(VertexBufferHandle handle) = 0;
	virtual void CreateIndexBuffer(IndexBufferHandle handle, void* data, U32 size, U32 stride) = 0;
	virtual void BindIndexBuffer(IndexBufferHandle handle) = 0;
	virtual void CreateShader(ShaderHandle handle, const std::string& name,ShaderType type) = 0;
	virtual void BindShader(ShaderHandle handle) = 0;

	// texture desc for the render target
	virtual void CreateRenderTarget(RenderTargetHandle handle, TORC_TEXTURE2D_DESC desc) = 0;
	virtual void BindRenderTarget(RenderTargetHandle handle) = 0;
	virtual void BindRenderTarget(RenderTargetHandle handle,DepthBufferHandle depthHandle) = 0;
	virtual void CreateDepthBuffer(DepthBufferHandle handle, U32 width, U32 height) = 0;
	virtual void CreateDepthBuffer(DepthBufferHandle handle) = 0;
	//virtual void CreateDepthBuffer(DepthBufferHandle handle, U32 width, U32 height, D3D11_TEXTURE2D_DESC desc) = 0;
	
	virtual void ClearDepthBuffer(DepthBufferHandle handle, U32 flags = 3u,float depthVal = 1.0f, U8 stencilVal = 0u) = 0;


	virtual void CreateVertexLayout(VertexLayoutHandle handle,ShaderHandle vsHandle, void* data, U32 elemCount) = 0;
	virtual void BindVertexLayout(VertexLayoutHandle handle) = 0;
	virtual void DrawIndexed(U32 indexCount, U32 indexStartLocation, int baseVertexLocation) = 0;
	virtual void SetPrimitiveTopology() = 0;
	virtual void CreateViewport(float w, float h, float maxDepth, float minDepth, float leftX, float leftY) = 0;
	virtual void CreateTexture(TextureHandle handle, const char* path) = 0;
	virtual void BindTexture(TextureHandle handle, uint32_t slot, uint32_t numViews) = 0;
	virtual void CreateSampler(SamplerHandle handle) = 0;
	virtual void BindSampler(SamplerHandle handle) = 0;
	virtual void BindBackBufferAsRenderTarget() = 0;
	virtual void SetDepthState() = 0;
	virtual void SetRasterizerState() = 0;

};

