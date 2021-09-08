#include "ResourceManager.h"
#include "IResource.h"
#include <utility>

U32 ResourceManager::URID = 0;

IResource* ResourceManager::CreateResource(std::string resName, ResourceType resourceType)
{
	// Check if resource is already exist
	for (auto& res : m_resources[resourceType])
	{
		if (res.first == resName)
		{
			return res.second;
		}
	}
	// If not than create and return
	switch (resourceType)
	{
	case TypeModelResource:
	{
		IResource* rs = new ModelResource;
		rs->m_resourceType = TypeModelResource;
		rs->m_resourceID = URID++;
		m_resources[resourceType].push_back(std::make_pair(resName, rs));
	}

	}


	return m_resources[resourceType][URID-1].second;
}

auto ResourceManager::GetResource(std::string resName, ResourceType resourceType)
{
	//IResource* resource;
	//for (auto& res : m_resources)
	//{
	//	if (res.first == resName)
	//	{
	//		resource = res.second;
	//	}
	//}

	//switch (resourceType) 
	//{
	//case TypeMeshResource:
	//	return dynamic_cast<MeshResource*>(resource);
	//case TypeModelResource:
	//	return dynamic_cast<ModelResource*>(resource);
	//default:
	//	return NULL;
	//}
}
