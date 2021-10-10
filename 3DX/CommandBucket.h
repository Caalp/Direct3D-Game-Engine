#pragma once
#include "Types.h"
#include "Command.h"
#include <map>


template<typename KEY>
class CommandBucket
{
private:
	void SubmitCommand(CommandPacket commandPacket)
	{
		const command::BackendDispatchFunc func = commandpacket::LoadBackendDispatchFunction(commandPacket);
		const void* command = commandpacket::LoadCommand(commandPacket);
		func(command);
	}

public:
	typedef KEY* Key;
	std::map<KEY, CommandPacket> mCommands;
	Key p_keys;
	uint16_t m_currentIdx;

	//RenderTargetHandle m_rt;
	//DepthBufferHandle m_depth;


public:
	CommandBucket(uint16_t maxCommandSize) : m_currentIdx(0u), p_keys(new KEY[maxCommandSize]){}
	void Init()
	{
		//TORC_TEXTURE2D_DESC desc;
		//ZeroMemory(&desc, sizeof(desc));
		//desc.width = backend::m_initData.width;
		//desc.height = backend::m_initData.height;
		//desc.format = TORC_FORMAT::TORC_FORMAT_R8G8B8A8_UNORM;
		//desc.bindFlags = D3D11_BIND_RENDER_TARGET;
		//desc.usage = TORC_USAGE_DEFAULT;
		//desc.mipLevels = 1u;
		//desc.arraySize = 1u;
		//desc.sampleDesc.count = 1;
		//m_rt = backend::CreateRenderTarget(desc);
		//m_depth = backend::CreateDepthBuffer();
		//backend::BindRenderTarget(m_rt, m_depth);
	}
	template<typename T>
	T* AddCommand(backend::SortKey key, uint32_t auxMemSize);
	
	//template<typename T>
	//void AppendCommand(void* command1, void* command2)
	//{
	//	// set commands back head of the commandpacket
	//	command1 = reinterpret_cast<char*>(command1) - commandpacket::kCommandDataOffset;
	//	command2 = reinterpret_cast<char*>(command2) - commandpacket::kCommandDataOffset;

	//	// add command2 after command 1

	//	commandpacket::SetBackendDispatchFunction(command2, T::BACKEND_DISPATCH_FUNC);
	//	commandpacket::SetNextCommandPacket(command1, command2);
	//	commandpacket::SetNextCommandPacket(command2, nullptr);
	//}

	template<typename T>
	T* AppendCommand(void* command1, uint32_t auxMemSize);

	void Submit();


};





template<typename KEY>
template<typename T>
inline T* CommandBucket<KEY>::AddCommand(backend::SortKey key, uint32_t auxMemSize)
{
	void* commandPtr = commandpacket::Create<T>(auxMemSize);

	p_keys[m_currentIdx] = key.m_sortKey;
	mCommands[key.m_sortKey] = commandPtr;
	m_currentIdx++;

	commandpacket::SetBackendDispatchFunction(commandPtr, T::BACKEND_DISPATCH_FUNC);
	commandpacket::SetNextCommandPacket(commandPtr, nullptr);

	return commandpacket::GetCommand<T>(commandPtr);
}

template<typename KEY>
template<typename T>
inline T* CommandBucket<KEY>::AppendCommand(void* command1, uint32_t auxMemSize)
{
	// set commands back head of the commandpacket
	command1 = reinterpret_cast<char*>(command1) - commandpacket::kCommandDataOffset;
	//command2 = reinterpret_cast<char*>(command2) - commandpacket::kCommandDataOffset;
	void* newCommand = commandpacket::Create<T>(auxMemSize);



	commandpacket::SetBackendDispatchFunction(newCommand, T::BACKEND_DISPATCH_FUNC);
	// add command2 after command 1
	commandpacket::SetNextCommandPacket(command1, newCommand);
	commandpacket::SetNextCommandPacket(newCommand, nullptr);

	// return appended command2's command data part
	return commandpacket::GetCommand<T>(newCommand);
}

template<typename KEY>
inline void CommandBucket<KEY>::Submit()
{
	//std::cout << "[CommandBucket] Submit func called!\n";
	CommandPacket cmd_pack;
	for (auto cmd : mCommands)
	{
		cmd_pack = cmd.second;
		do
		{
			SubmitCommand(cmd_pack);
			cmd_pack = commandpacket::GetNextCommandPacket(cmd_pack);
		} while (cmd_pack != nullptr);

	}
}
