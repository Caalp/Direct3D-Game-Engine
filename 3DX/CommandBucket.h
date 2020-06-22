#pragma once
#include "CommandPacket.h"
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
	//CommandBucket(const Drawable* db,std::string bucketID);
	void Submit(std::shared_ptr<CommandPacket> cmdPacket);
	void ProcessBucket(Graphics& gfx);
	


private:
	Key* keys;
	CommandPacket* cmdPackets;
	static unsigned int currentIndex;
};

template<typename T>
unsigned int CommandBucket<T>::currentIndex = 0u;