#pragma once
#include "Command.h"





template<typename T>
class CommandBucket
{
private:
	void SubmitCommand(CommandPacket commandPacket)
	{
		//commandPacket = (reinterpret_cast<char*>(commandPacket) - commandpacket::kCommandDataOffset);
		const command::BackendDispatchFunc func = commandpacket::LoadBackendDispatchFunction(commandPacket);
		void* command = commandpacket::LoadCommand(commandPacket);
		func(command);
	}

public:
	typedef T* Key;
	std::map<T, CommandPacket> mCommands;
	Key p_keys;
	uint16_t m_currentIdx;
public:
	CommandBucket(uint16_t maxCommandSize, RenderTarget& rt1) : m_currentIdx(0u), p_keys(new T[maxCommandSize])
	{}

	template<typename T>
	T* AddCommand(backend::SortKey key, uint32_t auxMemSize)
	{
		void* commandPtr = commandpacket::Create<T*>(auxMemSize);
		//command::DrawIndexed* di = reinterpret_cast<command::DrawIndexed*>(commandPtr);
		//di->BACKEND_DISPATCH_FUNC(0);

		// figure out how to store the key
		p_keys[m_currentIdx] = key.m_sortKey;
		//p_data = 
		mCommands[key.m_sortKey] = commandPtr;
		m_currentIdx++;

		commandpacket::SetBackendDispatchFunction(commandPtr, T::BACKEND_DISPATCH_FUNC);
		commandpacket::SetNextCommandPacket(commandPtr, nullptr);
		/*std::cout << "AddCommand function:\n";
		std::cout << "CommandPacket Address: " << commandPtr << std::endl;
		std::cout << "Command Address: " << commandpacket::LoadCommand(commandPtr) << std::endl;
		std::cout << "BackendDispatchFunction Address: " << di->BACKEND_DISPATCH_FUNC << std::endl;
		std::cout << "BackendDispatchFunction Address Retrieved(Load): " << (commandpacket::LoadBackendDispatchFunction(commandPtr)) << std::endl;
		std::cout << "BackendDispatchFunction Address Retrieved(Get): " << (commandpacket::GetBackendDispatchFunction(commandPtr)) << std::endl;*/


		/*command::BackendDispatchFunc funcPtr = commandpacket::LoadBackendDispatchFunction(commandPtr);
		funcPtr = command::DrawIndexed::BACKEND_DISPATCH_FUNC;*/

		return commandpacket::GetCommand<T>(commandPtr);
	}
	template<typename T>
	void AppendCommand(void* command1, void* command2)
	{
		// set commands back head of the commandpacket
		command1 = reinterpret_cast<char*>(command1) - commandpacket::kCommandDataOffset;
		command2 = reinterpret_cast<char*>(command2) - commandpacket::kCommandDataOffset;

		// add command2 after command 1

		commandpacket::SetBackendDispatchFunction(command2, T::BACKEND_DISPATCH_FUNC);
		commandpacket::SetNextCommandPacket(command1, command2);
		commandpacket::SetNextCommandPacket(command2, nullptr);



	}

	template<typename T>
	T* AppendCommand(void* command1, uint32_t auxMemSize)
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

	void Submit()
	{
		std::cout << "[CommandBucket] Submit func called!\n";
		/*CommandPacket cmd_pack;
		for (auto cmd : buckets::testCommandBucket->mCommands)
		{
			cmd_pack = cmd.second;
			do
			{
				SubmitCommand(cmd_pack);
				cmd_pack = commandpacket::GetNextCommandPacket(cmd_pack);
			} while (cmd_pack != nullptr);

		}*/
	}

};

