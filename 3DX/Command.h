#pragma once
#include "Backend.h"

struct BufferData
{
	uint32_t mBufferType;
	ConstantBufferHandle mBufferHandle;

};

struct BackendDispatchFunction
{
	static void UpdateConstantBuffer(void* data);
	static void CreateConstantBuffer(void* data);
	static void DrawIndexed(void* data);
	static void Draw(void* data);
	static void DrawInstanced(void* data);

};



namespace command
{
	typedef void(*BackendDispatchFunc)(void* data);



	struct DrawIndexed
	{
		static const BackendDispatchFunc BACKEND_DISPATCH_FUNC;
		//VertexLayoutHandle m_vlh;
		IndexBufferHandle m_ibh;
		VertexBufferHandle m_vbh;

		uint32_t m_vertexCount;
		uint32_t m_startIndexLocation;
		int m_baseVertexLocation;


	};
	const BackendDispatchFunc DrawIndexed::BACKEND_DISPATCH_FUNC = &BackendDispatchFunction::DrawIndexed;


	struct Draw
	{
		static const BackendDispatchFunc BACKEND_DISPATCH_FUNC;
		VertexLayoutHandle m_vlh;
		IndexBufferHandle m_ibh;
		VertexBufferHandle m_vbh;

		uint32_t m_vertexCount;
		uint32_t m_startVertexLocation;
	};

	const BackendDispatchFunc Draw::BACKEND_DISPATCH_FUNC = &BackendDispatchFunction::Draw;

	struct CreateConstantBuffer
	{
		static const BackendDispatchFunc BACKEND_DISPATCH_FUNC;
		uint32_t mBufferType;
		ConstantBufferHandle mBufferHandle;
	};

	const BackendDispatchFunc CreateConstantBuffer::BACKEND_DISPATCH_FUNC = &BackendDispatchFunction::CreateConstantBuffer;

	struct UpdateConstantBuffer
	{
		static const BackendDispatchFunc BACKEND_DISPATCH_FUNC;
		uint32_t mBufferType;
		ConstantBufferHandle mBufferHandle;
	};

	const BackendDispatchFunc UpdateConstantBuffer::BACKEND_DISPATCH_FUNC = &BackendDispatchFunction::UpdateConstantBuffer;
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

	CommandPacket* LoadNextCommandPacket(CommandPacket commandPacket)
	{
		return reinterpret_cast<CommandPacket*>(commandPacket) + kNextCommandPacketOffset;
	}

	CommandPacket GetNextCommandPacket(CommandPacket commandPacket)
	{
		return reinterpret_cast<CommandPacket>(*LoadNextCommandPacket(commandPacket));
	}
	void* LoadCommand(CommandPacket commandPacket)
	{
		return reinterpret_cast<char*>(commandPacket) + kCommandDataOffset;
	}
	command::BackendDispatchFunc* GetBackendDispatchFunction(CommandPacket commandPacket)
	{
		return reinterpret_cast<command::BackendDispatchFunc*>((reinterpret_cast<char*>(commandPacket) + kBackendDispatchFunctionOffset));
	}

	command::BackendDispatchFunc LoadBackendDispatchFunction(CommandPacket commandPacket)
	{
		return *GetBackendDispatchFunction(commandPacket);

	}
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
	void SetBackendDispatchFunction(CommandPacket commandpacket, command::BackendDispatchFunc func)
	{
		*GetBackendDispatchFunction(commandpacket) = func;
	}

	void SetNextCommandPacket(CommandPacket current, CommandPacket next)
	{
		*LoadNextCommandPacket(current) = next;
	}

	template<typename C, typename D>
	void SetAuxMemData(CommandPacket commandPacket, D data)
	{
		memcpy(*reinterpret_cast<CommandPacket*>(GetAuxMemoryPtr<C>(commandPacket)), data, sizeof(data));
		//*reinterpret_cast<CommandPacket*>(GetAuxMemoryPtr<C>(commandPacket)) = data;
	}
}

#pragma region BackendDispatchFunctioDefinations
void BackendDispatchFunction::DrawIndexed(void* data)
{
	//command::DrawIndexed* drawIndexData = reinterpret_cast<command::DrawIndexed*>(data);
	std::cout << "DrawIndexed Func called" << std::endl;
	// draw call to the API
	//backend::DrawIndexed(...)
}

void BackendDispatchFunction::Draw(void* data)
{
	std::cout << "Draw Func called" << std::endl;
}

void BackendDispatchFunction::CreateConstantBuffer(void* data)
{
	std::cout << "CreateConstantBuffer Func called" << std::endl;
}

void BackendDispatchFunction::UpdateConstantBuffer(void* data)
{
	command::UpdateConstantBuffer* cmd = reinterpret_cast<command::UpdateConstantBuffer*>(data);
	BufferData* bd = reinterpret_cast<BufferData*>(commandpacket::GetAuxMemoryPtrFromCommandDataPtr<command::UpdateConstantBuffer>(data));
	cmd->mBufferHandle = bd->mBufferHandle;
	cmd->mBufferType = bd->mBufferType;
	std::cout << "UpdateConstantBuffer Func mBufferType: " << cmd->mBufferType << std::endl;
	std::cout << "UpdateConstantBuffer Func mBufferHandle:" << cmd->mBufferHandle.idx << std::endl;
	std::cout << "UpdateConstantBuffer Func called" << std::endl;
}

void BackendDispatchFunction::DrawInstanced(void* data)
{

}


#pragma endregion