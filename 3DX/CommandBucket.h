#pragma once
#include "CommandPacket.h"

template <typename T>
class CommandBucket
{
	typedef T Key;
	//typedef void* Packet;
public:
	template<typename T>
	T* AddCommand(Key key, size_t auxMemorySize)
	{
		// Create command packet with command type added to bucket
		CommandPacket commandPacket = commandPacket::Create<T>(auxMemorySize);
		keys[currentIndex] = key;
		cmdPackets[currentIndex] = commandPacket;
		
		commandPacket::StoreNextCommandPacket(commandPacket, nullptr);
		commandPacket::StoreBackendDispatchFunction(commandPacket, T::DispatchFucntion);

		return commandPacket::GetCommand<T>(commandPacket);

	}
	template<typename U, typename V>
	U* AppendCommand(V* command, size_t auxMemorySize)
	{

	}

	void SetBucketState()
	{

	}
	//CommandBucket(const Drawable* db,std::string bucketID);
	//void Sort();
	//void Flush();
	void Submit()
	{
		SetBucketState();
		for (unsigned int i = 0; i < currentIndex; i++)
		{
			CommandPacket packet = cmdPackets[i];
			do
			{
				SubmitPacket(packet);
				packet = commandPacket::LoadNextCommandPacket(packet);

			} while (packet != nullptr);
		}
	}
	void SubmitPacket(const CommandPacket packet)
	{
		const BackendDispatchFunction function = commandPacket::LoadBackendDispatchFucntion(packet);
		const void* command = commandPacket::LoadCommand(packet);
		function(command);
	}
	//void ProcessBucket(Graphics& gfx);
	


private:
	Key* keys;
	CommandPacket* cmdPackets;
	static unsigned int currentIndex;
	// Think about type of the bindable (unique_ptr) etc
	std::vector<std::unique_ptr<Bindable>> bucketBindables;
};

template<typename T>
unsigned int CommandBucket<T>::currentIndex = 0u;