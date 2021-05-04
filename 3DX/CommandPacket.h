//#pragma once
//#include "Step.h"
//#include <vector>
//#include "Command.h"
//#include "union_cast.h"
//
//// TO DO : Check behavior of union_cast
//
//typedef void* CommandPacket;
//namespace commandPacket
//{
//	static const size_t OFFSET_NEXT_COMMAND_PACKET = 0u;
//	static const size_t OFFSET_BACKEND_DISPATCH_FUNCTION = OFFSET_NEXT_COMMAND_PACKET + sizeof(CommandPacket);
//	static const size_t OFFSET_COMMAND = OFFSET_BACKEND_DISPATCH_FUNCTION + sizeof(BackendDispatchFunction);
//	
//	template<typename T>
//	CommandPacket Create(size_t auxMemorySize)
//	{
//		return ::operator new (GetSize<T>(auxMemorySize));
//	}
//	template <typename T>
//	size_t GetSize(size_t auxMemorySize)
//	{
//		return OFFSET_COMMAND + sizeof(T) + auxMemorySize;
//	}
//	template <typename T>
//	T* GetCommand(CommandPacket packet)
//	{
//		return (reinterpret_cast<T*>(packet) + OFFSET_COMMAND);
//	}
//
//	/*CommandPacket* GetNextCommandPacket(CommandPacket packet)
//	{
//		return union_cast<CommandPacket*>(reinterpret_cast<char*>(packet) + OFFSET_NEXT_COMMAND_PACKET);
//	}
//
//	void StoreNextCommandPacket(CommandPacket packet, CommandPacket nextPacket)
//	{
//		*commandPacket::GetNextCommandPacket(packet) = nextPacket;
//	}
//	
//	BackendDispatchFunction* GetBackendDispatchFunction(CommandPacket packet)
//	{
//		return union_cast<BackendDispatchFunction*>(reinterpret_cast<char*>(packet) + OFFSET_BACKEND_DISPATCH_FUNCTION);
//	}
//	void StoreBackendDispatchFunction(CommandPacket packet, BackendDispatchFunction bdf)
//	{
//		*commandPacket::GetBackendDispatchFunction(packet) = bdf;
//	}
//	CommandPacket* GetNextCommandPacket(CommandPacket packet)
//	{
//		return union_cast<CommandPacket*>(reinterpret_cast<char*>(packet) + OFFSET_NEXT_COMMAND_PACKET);
//	}
//	const CommandPacket LoadNextCommandPacket(const CommandPacket packet)
//	{
//		return *GetNextCommandPacket(packet);
//	}
//	const void* LoadCommand(const CommandPacket packet)
//	{
//		return reinterpret_cast<char*>(packet) + OFFSET_COMMAND;
//	}
//	BackendDispatchFunction* GetBackendDispatchFunction(CommandPacket packet)
//	{
//		return union_cast<BackendDispatchFunction*>(reinterpret_cast<char*>(packet) + OFFSET_BACKEND_DISPATCH_FUNCTION);
//	}
//	const BackendDispatchFunction LoadBackendDispatchFunction(const  CommandPacket packet)
//	{
//		return *GetBackendDispatchFunction(packet);
//	}*/
//
//};