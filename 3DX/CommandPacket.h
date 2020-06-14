#pragma once
#include "Step.h"
#include <vector>

typedef void* CommandPacket;
namespace commandPacket
{
	static const size_t OFFSET_NEXT_COMMAND_PACKET = 0u;
	static const size_t OFFSET_BACKEND_DISPATCH_FUNCTION = OFFSET_NEXT_COMMAND_PACKET + sizeof(commandPacket);
	static const size_t OFFSET_COMMAND = OFFSET_BACKEND_DISPATCH_FUNCTION + sizeof(backendDispatchFunction);
	
	template<typename T>
	CommandPacket Create(size_t auxMemorySize)
	{
		return ::new_handler(GetSize<T>(auxMemorySize));
	}
	template <typename T>
	size_t GetSize(size_t auxMemorySize)
	{
		return OFFSET_COMMAND + sizeof(T) + auxMemorySize;
	}
};