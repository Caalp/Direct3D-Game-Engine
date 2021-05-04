//#include "Mesh.h"
//#include "additional_headers.h"
//#include "Imgui/imgui.h"
//#include "ImguiHandler.h"
//#include <iostream>
//#include "DynamicVertex.h"
//void  Mesh::ParseMesh(const aiMesh& mesh, const aiMaterial* const* pMaterials,std::string texIncludeDir)
//{
//	dvbuff::VertexLayout vlayout;
//	/*dvbuff::VertexLayout indices{ dvbuff::VertexLayout{}
//										.Add<dvbuff::Float>()};*/
//	dvbuff::VertexBuffer vbuff{ vlayout };
//	//dvbuff::VertexBuffer vbuff2{ indices };
//	//auto a = sizeof(mesh.mVertices);
//	if (mesh.HasPositions())
//	{
//		vlayout.Add<dvbuff::Position3D>();
//	}
//	if (mesh.HasTextureCoords(0))
//	{
//		vlayout.Add<dvbuff::TextureCoord3D>();
//	}
//	
//	if (mesh.HasNormals())
//	{
//		vlayout.Add<dvbuff::Normal>();
//	}
//	if (mesh.HasBones())
//	{
//		vlayout.Add<dvbuff::BoneIndices>();
//		vlayout.Add<dvbuff::BoneWeights>();
//	}
//	
//	//vertices.resize(mesh.mNumVertices);
//	vbuff.Resize(vlayout.GetSizeInBytes() * mesh.mNumVertices);
//	for (unsigned int i = 0; i < mesh.mNumVertices; i++)
//	{
//		if (mesh.HasPositions())
//		{
//			vbuff[i].Set<dvbuff::Position3D>(mesh.mVertices[i]);
//		}
//		auto testEl = vbuff[i].Get<dvbuff::Position3D>();
//
//
//		if (mesh.mNormals != NULL)
//		{
//			vbuff[i].Set<dvbuff::Normal>(mesh.mNormals[i]);
//		}
//		if (mesh.mTextureCoords[0] != NULL)
//		{
//
//			vbuff[i].Set<dvbuff::TextureCoord3D>(aiVector3D( mesh.mTextureCoords[0][i].x,mesh.mTextureCoords[0][i].y,mesh.mMaterialIndex ));
//		}
//		
//		/*if (mesh.mTextureCoords[0])
//		{
//			vertices.texCoordinates.x = mesh.mTextureCoords[0][i].x;
//			vertices.texCoordinates.y = mesh.mTextureCoords[0][i].y;
//			vertices.texCoordinates.z = mesh.mMaterialIndex;
//			
//		}
//		else
//		{
//			vertices.texCoordinates = DirectX::XMFLOAT3(0.0f, 0.0f, mesh.mMaterialIndex);
//		}*/
//		
//
//	}
//	
//	/*for (unsigned int i = 0; i < mesh.mNumFaces; i++)
//	{
//		aiFace face = mesh.mFaces[i];
//		for (unsigned int j = 0; j < face.mNumIndices; j++)
//			indices.push_back(face.mIndices[j]);
//
//	}
//	std::string pathEntry = texIncludeDir;
//	aiString textureName;
//
//	if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_UNKNOWN))
//	{
//		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_SPECULAR, 0), textureName);
//		textures.emplace_back(aiTextureType_SPECULAR, pathEntry + textureName.C_Str());
//		textureName.Clear();
//	}
//
//	if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_DIFFUSE))
//	{
//		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), textureName);
//		textures.emplace_back(aiTextureType_DIFFUSE, pathEntry + textureName.C_Str());
//		textureName.Clear();
//
//	}
//
//	if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_SPECULAR) > 0)
//	{
//		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_SPECULAR, 0), textureName);
//		textures.emplace_back(aiTextureType_SPECULAR, pathEntry + textureName.C_Str());
//		textureName.Clear();
//	}
//	if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_AMBIENT) > 0)
//	{
//		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_AMBIENT, 0), textureName);
//		textures.emplace_back(aiTextureType_AMBIENT, pathEntry + textureName.C_Str());
//		textureName.Clear();
//	}
//	if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_HEIGHT) > 0)
//	{
//		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_HEIGHT, 0), textureName);
//		textures.emplace_back(aiTextureType_HEIGHT, pathEntry + textureName.C_Str());
//		textureName.Clear();
//	}
//	if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_NORMALS) > 0)
//	{
//		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_NORMALS, 0), textureName);
//		textures.emplace_back(aiTextureType_NORMALS, pathEntry + textureName.C_Str());
//		textureName.Clear();
//	}
//	if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_NONE) > 0)
//	{
//		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_NONE, 0), textureName);
//		textures.emplace_back(aiTextureType_NONE, pathEntry + textureName.C_Str());
//		textureName.Clear();
//	}*/
//
//	
//
//}
//
//
