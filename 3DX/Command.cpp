#include "Command.h"

namespace command
{
	const BackendDispatchFunc DrawIndexed::BACKEND_DISPATCH_FUNC = &BackendDispatchFunction::DrawIndexed;
	const BackendDispatchFunc Draw::BACKEND_DISPATCH_FUNC = &BackendDispatchFunction::Draw;
	const BackendDispatchFunc CreateConstantBuffer::BACKEND_DISPATCH_FUNC = &BackendDispatchFunction::CreateConstantBuffer;
	const BackendDispatchFunc BindSampler::BACKEND_DISPATCH_FUNC = &backend::BindSampler;
	const BackendDispatchFunc UpdateConstantBuffer::BACKEND_DISPATCH_FUNC = &BackendDispatchFunction::UpdateConstantBuffer;

}



#pragma region BackendDispatchFunctioDefinations
void BackendDispatchFunction::DrawIndexed(const void* data)
{
	const command::DrawIndexed* drawIndexData = reinterpret_cast<const command::DrawIndexed*>(data);
	backend::BindIndexBuffer(drawIndexData->indexBuffer);
	backend::BindVertexBuffer(drawIndexData->vertexBuffer);
	backend::BindVertexLayout(drawIndexData->vertexLayout);
	backend::BindConstantBuffer(drawIndexData->drawInfo.cb, 0u, 1u);
	backend::BindShader(drawIndexData->drawInfo.ps);
	backend::BindShader(drawIndexData->drawInfo.vs);
	backend::BindTexture(drawIndexData->texHandle, 0u, 1u);

	backend::DrawIndexed(drawIndexData->indexCount, drawIndexData->startIndexLocation, drawIndexData->baseVertexLocation);
}

void BackendDispatchFunction::Draw(const void* data)
{
	std::cout << "Draw Func called" << std::endl;
}

void BackendDispatchFunction::CreateConstantBuffer(const void* data)
{
	std::cout << "CreateConstantBuffer Func called" << std::endl;
}

void BackendDispatchFunction::UpdateConstantBuffer(const void* data)
{
	/*const command::UpdateConstantBuffer* cmd = const reinterpret_cast<const command::UpdateConstantBuffer*>(data);
	BufferData* bd = reinterpret_cast<BufferData*>(commandpacket::GetAuxMemoryPtrFromCommandDataPtr<command::UpdateConstantBuffer>(data));
	cmd->mBufferHandle = bd->mBufferHandle;
	cmd->mBufferType = bd->mBufferType;
	std::cout << "UpdateConstantBuffer Func mBufferType: " << cmd->mBufferType << std::endl;
	std::cout << "UpdateConstantBuffer Func mBufferHandle:" << cmd->mBufferHandle.idx << std::endl;
	std::cout << "UpdateConstantBuffer Func called" << std::endl;*/
}

void BackendDispatchFunction::DrawInstanced(const void* data)
{

}


#pragma endregion



namespace commandpacket
{
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

	void SetNextCommandPacket(CommandPacket current, CommandPacket next)
	{
		*LoadNextCommandPacket(current) = next;
	}
	void SetBackendDispatchFunction(CommandPacket commandpacket, command::BackendDispatchFunc func)
	{
		*GetBackendDispatchFunction(commandpacket) = func;
	}
}