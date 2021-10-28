#pragma once
#include "defines.h"
#include "Backend.h"



using namespace backend;
struct BufferData
{
	uint32_t mBufferType;
	ConstantBufferHandle mBufferHandle;

};

struct BackendDispatchFunction
{
	static void UpdateConstantBuffer(const void* data);
	static void CreateConstantBuffer(const void* data);
	static void DrawIndexed(const void* data);
	static void Draw(const void* data);
	static void DrawInstanced(const void* data);

};

enum Priority
{
	High = 0u,
	Low,
	Count
};


namespace command
{
	typedef void(*BackendDispatchFunc)(const void* data);



	struct DrawIndexed
	{
		static const BackendDispatchFunc BACKEND_DISPATCH_FUNC;
		RenderDrawInfo drawInfo;
		VertexLayoutHandle vertexLayout;
		IndexBufferHandle indexBuffer;
		VertexBufferHandle vertexBuffer;
		TextureHandle texHandle;

		int baseVertexLocation;
		uint32_t indexCount;
		uint32_t startIndexLocation;

	

	};


	struct Draw
	{
		static const BackendDispatchFunc BACKEND_DISPATCH_FUNC;
		VertexLayoutHandle m_vlh;
		IndexBufferHandle m_ibh;
		VertexBufferHandle m_vbh;

		uint32_t m_vertexCount;
		uint32_t m_startVertexLocation;
	};


	struct CreateConstantBuffer
	{
		static const BackendDispatchFunc BACKEND_DISPATCH_FUNC;
		uint32_t mBufferType;
		ConstantBufferHandle mBufferHandle;
	};

	struct BindSampler
	{
		static const BackendDispatchFunc BACKEND_DISPATCH_FUNC;
		SamplerHandle Sampler;

	};

	struct BindTexture
	{
		static const BackendDispatchFunc BACKEND_DISPATCH_FUNC;
		TextureHandle m_texture;
	};
	struct UpdateConstantBuffer
	{
		static const BackendDispatchFunc BACKEND_DISPATCH_FUNC;
		uint32_t mBufferType;
		ConstantBufferHandle mBufferHandle;
	};

}

// try static var initialization ??
typedef void* CommandPacket;
namespace commandpacket
{

	static const size_t kNextCommandPacketOffset = 0u;
	static const size_t kBackendDispatchFunctionOffset = kNextCommandPacketOffset + sizeof(CommandPacket);
	static const size_t kCommandDataOffset = kBackendDispatchFunctionOffset + sizeof(kBackendDispatchFunctionOffset);

	template<typename T>
	size_t GetSize(uint32_t auxMemSize)
	{
		return kCommandDataOffset + sizeof(T) + auxMemSize;
	}

	template<typename T>
	void* Create(uint32_t auxMemSize)
	{
		return ::operator new(GetSize<T>(auxMemSize));
	}

	template<typename T>
	T* GetCommand(CommandPacket commandPacket)
	{
		return reinterpret_cast<T*>(reinterpret_cast<char*>(commandPacket) + kCommandDataOffset);
	}

	CommandPacket* LoadNextCommandPacket(CommandPacket commandPacket);

	CommandPacket GetNextCommandPacket(CommandPacket commandPacket);
	void* LoadCommand(CommandPacket commandPacket);
	command::BackendDispatchFunc* GetBackendDispatchFunction(CommandPacket commandPacket);

	command::BackendDispatchFunc LoadBackendDispatchFunction(CommandPacket commandPacket);
	template<typename T>
	void* GetAuxMemoryPtr(CommandPacket commandPacket)
	{
		return reinterpret_cast<char*>(commandPacket) + kCommandDataOffset + sizeof(T);
	}
	template<typename T>
	void* GetAuxMemoryPtrFromCommandDataPtr(void* command)
	{
		return reinterpret_cast<char*>(command) + sizeof(T);
	}
	void SetBackendDispatchFunction(CommandPacket commandpacket, command::BackendDispatchFunc func);

	void SetNextCommandPacket(CommandPacket current, CommandPacket next);

	template<typename C, typename D>
	void SetAuxMemData(CommandPacket commandPacket, D data)
	{
		memcpy(*reinterpret_cast<CommandPacket*>(GetAuxMemoryPtr<C>(commandPacket)), data, sizeof(data));
		//*reinterpret_cast<CommandPacket*>(GetAuxMemoryPtr<C>(commandPacket)) = data;
	}
}

