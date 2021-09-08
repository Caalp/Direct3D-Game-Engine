#pragma once
#include "Types.h"
#include <iostream>




class IResource
{
	friend class ResourceManager;
public:
	IResource() = default;
	virtual bool Load(const char* path) { return false; };


	// Something to work on advance this.
	template<typename T>
	T get()
	{
		//T newType;
		if (T newType = dynamic_cast<T>(this))
		{
			return newType;
		}

		return nullptr;

	}

protected:
	bool initialized = false;
	U32 m_resourceID;
	U32 m_resourceType;
};


