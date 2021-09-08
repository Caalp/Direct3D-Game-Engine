#pragma once
#include <vector>
#include <DirectXMath.h>
#include <map>
#include "Types.h"
#include "TextureResource.h"
#include "Mesh.h"

enum class MATERIAL_TYPE
{
	SPECULAR,
	DIFFUSE,
	AMBIENT,
	HEIGHT,
	NORMAL,
	NONE
};
struct Vertices;


//struct Node;
//struct Mesh;
//struct Material;

/* Class for loading mesh from file and storing*/
class ModelResource : public IResource
{

public:
	ModelResource()
	{
		// Default flags
		m_flags = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_GenSmoothNormals | aiProcess_FlipUVs |
			aiProcess_MakeLeftHanded | aiProcess_FlipWindingOrder | aiProcess_LimitBoneWeights;
		
	}
	bool Load(const char* path) override;


	void SetFlag(U32 flags)
	{
		m_flags = flags;
	}
	ModelResource(const ModelResource& rhs)
	{

	}
	U32 GetMeshCount() const
	{
		return m_meshes.size();
	}
	const std::vector<Ref<std::pair<TextureResource, Mesh>>>& GetMeshes() { return m_meshes; }
private:
	/*void ParseMesh(std::pair<TextureResource, Mesh>& data,const aiMesh& mesh, const aiMaterial* const* pMaterials, std::string texIncludeDir);
	Ref<Node> ParseNode( int& nextId, const aiNode& node,const DirectX::XMMATRIX& parentTransform);
	void ParseMaterial(const aiMaterial* const* pMaterials, std::string texIncludeDir);*/


public:
	
	U32 m_flags;
	std::vector<Ref<std::pair<TextureResource,Mesh>>> m_meshes;
	//std::map<std::string,Ref<Node>> nodes;
	//Ref<Node> p_RootNode; // Ptr to the root node
};