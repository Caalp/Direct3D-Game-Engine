#include "ModelResource.h"
#include <filesystem>
#include "Entity.h"
#include "Texture.h"

//struct Mesh
//{
//	std::vector<Vertices> m_vertices;
//	std::vector<U16> indices;
//	//std::vector<Material> m_Materials;
//	//std::string derivedNodeName; // Node which this mesh is belongs to 
//};
//struct Material
//{
//	MATERIAL_TYPE m_Type;
//	Ptr<Texture> p_Texture;
//};
//struct Vertices
//{
//	DirectX::XMFLOAT3 pos;
//	DirectX::XMFLOAT3 normal;
//	DirectX::XMFLOAT3 texCoordinates;
//	//DirectX::XMFLOAT4 weights;
//	//Byte boneIndices[4];
//};
//struct Node
//{
//	int m_ID;
//	std::string m_Name;
//	DirectX::XMMATRIX m_Transform;
//	DirectX::XMMATRIX m_ToRootTransform;
//	std::vector<Ref<Mesh>> m_Meshes;
//	std::vector<Ref<Node>> m_ChildNodes;
//};

bool ModelResource::Load(const char* filepath)
{
	
	std::filesystem::path fp(filepath);

	std::string parentPath = fp.parent_path().string() + "/";

	Assimp::Importer importer;
	const aiScene* pScene = importer.ReadFile(filepath, m_flags);


	// check if loading fails 
	// might return 0 or scene data might be incomplete or might not have root node
	if (pScene == nullptr || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || pScene->mRootNode == nullptr)
	{
		return false;
	}

	//uint32_t boneIndex = 0;
	for (int i = 0; i < pScene->mNumMeshes; i++)
	{
		m_meshes.emplace_back(std::make_shared<std::pair<TextureResource, Mesh>>());
	}



	for (size_t i = 0; i < pScene->mNumMeshes; i++)
	{
		//m_meshes[i].get()->second = Mesh();
		m_meshes[i].get()->second.ParseMesh(*pScene->mMeshes[i]);
		
		//ParseMesh(m_meshes[i].get() *pScene->mMeshes[i], pScene->mMaterials, parentPath);
	}


	//DirectX::XMMATRIX M = DirectX::XMMatrixIdentity();
	//int nextId = 0;
	//p_RootNode = ParseNode(nextId, *pScene->mRootNode, M);

	return true;
}




//#pragma region ParseMaterial
//
//	//std::string pathEntry = texIncludeDir;
//	aiString textureName;
//
//	if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_UNKNOWN))
//	{
//		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_SPECULAR, 0), textureName);
//		Material m;
//		m.m_Type = MATERIAL_TYPE::SPECULAR;
//		m.p_Texture = std::make_unique<Texture>((pathEntry + textureName.C_Str()).c_str());
//		data.m_Materials.push_back(std::move(m));
//
//		textureName.Clear();
//	}
//
//	else if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_DIFFUSE))
//	{
//		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), textureName);
//
//		Material m;
//		m.m_Type = MATERIAL_TYPE::DIFFUSE;
//		m.p_Texture = std::make_unique<Texture>((pathEntry + textureName.C_Str()).c_str());
//		data.m_Materials.push_back(std::move(m));
//
//		textureName.Clear();
//
//	}
//
//	else if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_SPECULAR) > 0)
//	{
//		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_SPECULAR, 0), textureName);
//
//		Material m;
//		m.m_Type = MATERIAL_TYPE::SPECULAR;
//		m.p_Texture = std::make_unique<Texture>((pathEntry + textureName.C_Str()).c_str());
//		data.m_Materials.push_back(std::move(m));
//
//		textureName.Clear();
//	}
//	else if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_AMBIENT) > 0)
//	{
//		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_AMBIENT, 0), textureName);
//
//		Material m;
//		m.m_Type = MATERIAL_TYPE::AMBIENT;
//		m.p_Texture = std::make_unique<Texture>((pathEntry + textureName.C_Str()).c_str());
//		data.m_Materials.push_back(std::move(m));
//
//		textureName.Clear();
//	}
//	else if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_HEIGHT) > 0)
//	{
//		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_HEIGHT, 0), textureName);
//
//		Material m;
//		m.m_Type = MATERIAL_TYPE::HEIGHT;
//		m.p_Texture = std::make_unique<Texture>((pathEntry + textureName.C_Str()).c_str());
//		data.m_Materials.push_back(std::move(m));
//
//		textureName.Clear();
//	}
//	else if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_NORMALS) > 0)
//	{
//		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_NORMALS, 0), textureName);
//
//		Material m;
//		m.m_Type = MATERIAL_TYPE::NORMAL;
//		m.p_Texture = std::make_unique<Texture>((pathEntry + textureName.C_Str()).c_str());
//		data.m_Materials.push_back(std::move(m));
//
//		textureName.Clear();
//	}
//	else if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_NONE) > 0)
//	{
//		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_NONE, 0), textureName);
//
//
//		Material m;
//		m.m_Type = MATERIAL_TYPE::NONE;
//		m.p_Texture = std::make_unique<Texture>((pathEntry + textureName.C_Str()).c_str());
//		data.m_Materials.push_back(std::move(m));
//
//		textureName.Clear();
//	}
//
//#pragma endregion 
//
//}

//Ref<Node> ModelResource::ParseNode(int& nextId, const aiNode& node, const DirectX::XMMATRIX& parentTransform)
//{
//
//	const auto transformation = DirectX::XMMatrixTranspose(DirectX::XMMATRIX(&node.mTransformation.a1));
//
//	const auto toNodeToRoot = transformation * parentTransform;
//	
//	std::vector<Ref<Mesh>> curMeshPtrs;
//	
//	curMeshPtrs.reserve(node.mNumMeshes);
//	for (size_t i = 0; i < node.mNumMeshes; i++)
//	{
//		const auto meshIdx = node.mMeshes[i];
//		//m_Meshes.at(meshIdx).derivedNodeName = node.mName.C_Str();
//
//		curMeshPtrs.emplace_back(m_meshes.at(meshIdx));
//	
//	}
//
//
//	//auto pNode = std::make_unique<Node>(nextId, node.mName.C_Str(), std::move(curMeshPtrs), transformation, toNodeToRoot);
//	auto pNode = Ref<Node>{ new Node };
//	pNode->m_ID = nextId;
//	pNode->m_Name = node.mName.C_Str();
//	pNode->m_Meshes = std::move(curMeshPtrs);
//	pNode->m_Transform = transformation;
//	pNode->m_ToRootTransform = toNodeToRoot;
//
//	
//	std::string nodeName(node.mName.C_Str());
//	if (nodeName != "" && nodes.find(nodeName) == nodes.end())
//	{
//		nodes[nodeName] = pNode;
//		nextId++;
//	}
//	
//	
//	for (size_t i = 0; i < node.mNumChildren; i++)
//	{
//		std::string childName = (*node.mChildren[i]).mName.C_Str();
//		if (childName != "")
//		{
//			pNode->m_ChildNodes.emplace_back(ParseNode(nextId, *node.mChildren[i], toNodeToRoot));
//		}
//		
//	}
//
//
//	return pNode;
//}

//void ModelResource::ParseMaterial(const aiMaterial* const* pMaterials, std::string texIncludeDir)
//{
//
//
//}
