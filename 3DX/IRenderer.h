#pragma once
#include <string>

struct VertexBufferHandle;
struct IndexBufferHandle;
struct ShaderHandle;

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

	
	
};

