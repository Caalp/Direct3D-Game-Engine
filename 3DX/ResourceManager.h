#pragma once
#include <vector>
#include <string>
#include "Types.h"
#include "ModelResource.h"



class IResource;
enum ResourceType;
class ResourceManager
{
public:
	enum ResourceType : U32
	{
		TypeModelResource,
		TypeMeshResource,
		TypeMaterialResource
	};
public:

	static ResourceManager& GetSingleton()
	{
		static ResourceManager rm;
		return rm;
	}
	IResource* CreateResource(std::string resName,ResourceType resourceType);
	auto GetResource(std::string resName, ResourceType resourceType);


private:
	std::map<ResourceManager::ResourceType,std::vector<std::pair<std::string,IResource*>>> m_resources;
	static U32 URID;

};
