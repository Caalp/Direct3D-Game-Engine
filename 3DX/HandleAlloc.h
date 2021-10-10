#pragma once
#include "Types.h"



class HandleAlloc
{
public:
	HandleAlloc(uint16_t maxHandleCount) :m_maxHandleCount(maxHandleCount)
	{
		Reset();
	}
	uint32_t* GetHandleSection()
	{
		const uint8_t* ptr = reinterpret_cast<const uint8_t*>(this);
		// jump to the handle array part
		return (uint32_t*)&ptr[sizeof(HandleAlloc)];
	}
	uint32_t* GetIndexerSection()
	{
		// Get free list part and jump to actual handle part
		return &GetHandleSection()[m_maxHandleCount];
	}
	void Reset()
	{
		m_numHandles = 0;
		uint32_t* handle = GetHandleSection();
		for (uint16_t i = 0; i < m_maxHandleCount; i++)
		{
			handle[i] = i;
		}
	}

private:
	HandleAlloc() = default;

protected:
	uint16_t m_numHandles;
	uint16_t m_maxHandleCount;
};


template<uint16_t size>
class FixedHandleAlloc : public HandleAlloc
{
public:
	FixedHandleAlloc() : HandleAlloc(size)
	{}

	uint32_t Alloc()
	{
		uint16_t freeSlotIndex = m_numHandles;
		++m_numHandles;
		uint32_t* freePartPtr = GetHandleSection();
		uint32_t& handle = freePartPtr[freeSlotIndex];
		//increase ref_count part
		handle += 0x00010000;
		//handle  = (handle & 0xffff0000) | 
		
		uint32_t* handlePartPtr = GetIndexerSection();
		handlePartPtr[handle&0x0000ffff] = freeSlotIndex;
		return handle;

	}
	void Free(uint32_t handle)
	{

		if (!IsValid(handle))
		{
			return;
		}

		//uint16_t end = m_numHandles;
		--m_numHandles;
		uint32_t* indexerPart = GetIndexerSection();
		uint32_t* handlePart = GetHandleSection();

		// first swap indexer section values
		//std::swap(indexerPart[handle], indexerPart[m_numHandles]);
		// swap handle section values
		// value will be placed at the end of the array to be used for next alloc
		
		uint32_t idx = indexerPart[handle & 0x0000ffff];
		uint32_t& handleSlot = handlePart[idx];
		handleSlot += 0x00010000; // increase ref_count at handle
		std::swap(indexerPart[handle & 0x0000ffff], indexerPart[m_numHandles]);
		std::swap(handlePart[idx], handlePart[m_numHandles]);
		
		
	}
	bool IsValid(uint32_t handle)
	{
		uint16_t idx = GetIndexerSection()[handle&0x0000ffff];
		return idx < m_numHandles && GetHandleSection()[idx] == handle;
	}
	void print()
	{
		//std::cout << m_handles[0].idx << std::endl;
	}
private:
	uint32_t m_handles[2*size];
	
};