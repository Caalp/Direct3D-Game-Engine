#pragma once
#include <string>

struct VertexBufferHandle;
struct IndexBufferHandle;
struct ShaderHandle;
struct DepthBufferHandle;
struct RenderTargetHandle;

namespace backend
{
	enum ShaderType;
}


class IRenderer
{
public:
	virtual void BeginFrame() = 0;
	virtual void Present() = 0;
	virtual void Init(HWND hwnd, U32 width, U32 height) = 0;
	//virtual void Shutdown() = 0;
	//virtual void CreateShader(ShaderHandle shaderHandle) = 0;
	//virtual void DestroyShader(const char* VSfilename) = 0;
	//virtual void CreateGeometryShader(const char* GSfilename) = 0;
	//virtual void CreateHullShader(const char* HSfilename) = 0;
	//virtual void CreateDomainShader(const char* DSfilename) = 0;
	
	virtual void CreateVertexBuffer(VertexBufferHandle handle,void* data, U32 size, U32 stride) = 0;
	virtual void BindVertexBuffer(VertexBufferHandle handle) = 0;
	virtual void CreateIndexBuffer(IndexBufferHandle handle, void* data, U32 size, U32 stride) = 0;
	virtual void BindIndexBuffer(IndexBufferHandle handle) = 0;
	virtual void CreateShader(ShaderHandle handle, std::string name,backend::ShaderType type) = 0;
	virtual void BindShader(ShaderHandle handle, backend::ShaderType type) = 0;

	// texture desc for the render target
	virtual void CreateRenderTarget(RenderTargetHandle handle, D3D11_TEXTURE2D_DESC desc) = 0;
	virtual void BindRenderTarget(RenderTargetHandle handle) = 0;
	virtual void CreateDepthBuffer(DepthBufferHandle handle, U32 width, U32 height, D3D11_TEXTURE2D_DESC desc) = 0;
	
	virtual void ClearDepthBuffer(DepthBufferHandle handle, U32 flags = 3u,float depthVal = 1.0f, U8 stencilVal = 0u) = 0;


	
	
};

