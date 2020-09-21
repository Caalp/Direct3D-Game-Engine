//#pragma once
//#include "CommandPacket.h"
//#include <map>
//#include "Job.h"
//
//template <typename T>
//class CommandBucket
//{
//	typedef T* Key;
//public:
//	
//	CommandBucket(Graphics& gfx)
//	{
//		
//
//	}
//	
//	template<typename T>
//	T* AddCommand(UINT key, size_t auxMemorySize)
//	{
//		// Create command packet with command type added to bucket
//		CommandPacket commandPacket = commandPacket::Create<T>(auxMemorySize);
//		//keys[currentIndex] = key;
//		cmdPackets[currentIndex] = commandPacket;
//		
//		commandPacket::StoreNextCommandPacket(commandPacket, nullptr);
//		commandPacket::StoreBackendDispatchFunction(commandPacket, T::DispatchFucntion);
//
//		return commandPacket::GetCommand<T>(commandPacket);
//
//	}
//	template<typename U, typename V>
//	U* AppendCommand(V* command, size_t auxMemorySize)
//	{
//
//	}
//
//		
//		
//	//CommandBucket(const Drawable* db,std::string bucketID);
//	//void Sort();
//	//void Flush();
//	void Submit()
//	{
//		
//		for (unsigned int i = 0; i < currentIndex; i++)
//		{
//			CommandPacket packet = cmdPackets[i];
//			do
//			{
//				SubmitPacket(packet);
//				packet = commandPacket::LoadNextCommandPacket(packet);
//
//			} while (packet != nullptr);
//		}
//	}
//	void SubmitPacket(const CommandPacket packet)
//	{
//		const BackendDispatchFunction function = commandPacket::LoadBackendDispatchFunction(packet);
//		const void* command = commandPacket::LoadCommand(packet);
//		function(command);
//	}
//	/*std::vector<Pass> GetPasses() const
//	{
//		return passes;
//	}*/
//	
//	Pass* GetTargetPass(std::string targetPassName)
//	{
//		for ( const auto& p : passes)
//		{
//			if (p->GetPassName() == targetPassName)
//			{
//				return p;
//			}
//		}
//	}
//
//private:
//	Key keys;
//	CommandPacket* cmdPackets;
//	static unsigned int currentIndex;
//	
//	//std::map<std::string, Job> drawQueue;
//	// Think about type of the bindable (unique_ptr) etc
//	//std::vector<std::unique_ptr<Bindable>> bucketBindables;
//};
//
//template<typename T>
//unsigned int CommandBucket<T>::currentIndex = 0u;