#include "TextureResource.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

void TextureResource::LoadMaterial(const aiMaterial* const* pMaterials, int materialIndex)
{
	//std::string pathEntry = texIncludeDir;
	aiString textureName;

	if (pMaterials[materialIndex]->GetTextureCount(aiTextureType_UNKNOWN))
	{
		pMaterials[materialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_SPECULAR, 0), textureName);
		//Material m;
		//m.m_Type = MATERIAL_TYPE::SPECULAR;
		//m.p_Texture = std::make_unique<Texture>((pathEntry + textureName.C_Str()).c_str());
		//data.m_Materials.push_back(std::move(m));

		//textureName.Clear();
	}

	else if (pMaterials[materialIndex]->GetTextureCount(aiTextureType_DIFFUSE))
	{
		pMaterials[materialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), textureName);

		//Material m;
		//m.m_Type = MATERIAL_TYPE::DIFFUSE;
		//this->m_diffuseTexture = std::make_shared<Texture>((pathEntry + textureName.C_Str()).c_str());
		//data.m_Materials.push_back(std::move(m));

		//textureName.Clear();

	}

	else if (pMaterials[materialIndex]->GetTextureCount(aiTextureType_SPECULAR) > 0)
	{
		pMaterials[materialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_SPECULAR, 0), textureName);

		//Material m;
		//m.m_Type = MATERIAL_TYPE::SPECULAR;
		//m.p_Texture = std::make_unique<Texture>((pathEntry + textureName.C_Str()).c_str());
		//data.m_Materials.push_back(std::move(m));

		//textureName.Clear();
	}
	else if (pMaterials[materialIndex]->GetTextureCount(aiTextureType_AMBIENT) > 0)
	{
		pMaterials[materialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_AMBIENT, 0), textureName);

		//Material m;
		//m.m_Type = MATERIAL_TYPE::AMBIENT;
		//m.p_Texture = std::make_unique<Texture>((pathEntry + textureName.C_Str()).c_str());
		//data.m_Materials.push_back(std::move(m));

		//textureName.Clear();
	}
	else if (pMaterials[materialIndex]->GetTextureCount(aiTextureType_HEIGHT) > 0)
	{
		pMaterials[materialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_HEIGHT, 0), textureName);

		//Material m;
		//m.m_Type = MATERIAL_TYPE::HEIGHT;
		//m.p_Texture = std::make_unique<Texture>((pathEntry + textureName.C_Str()).c_str());
		//data.m_Materials.push_back(std::move(m));

		//textureName.Clear();
	}
	else if (pMaterials[materialIndex]->GetTextureCount(aiTextureType_NORMALS) > 0)
	{
		pMaterials[materialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_NORMALS, 0), textureName);

		/*	Material m;
			m.m_Type = MATERIAL_TYPE::NORMAL;
			m.p_Texture = std::make_unique<Texture>((pathEntry + textureName.C_Str()).c_str());
			data.m_Materials.push_back(std::move(m));

			textureName.Clear();*/
	}
	else if (pMaterials[materialIndex]->GetTextureCount(aiTextureType_NONE) > 0)
	{
		pMaterials[materialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_NONE, 0), textureName);


		/*Material m;
		m.m_Type = MATERIAL_TYPE::NONE;
		m.p_Texture = std::make_unique<Texture>((pathEntry + textureName.C_Str()).c_str());
		data.m_Materials.push_back(std::move(m));

		textureName.Clear();*/
	}


}
void TextureResource::LoadNormalTexture(const char* path, U32 slot)
{
	m_normalTexture = std::make_unique<Texture>(path, slot);
}
void TextureResource::LoadDiffuseTexture(const char* path, U32 slot)
{
	m_diffuseTexture = std::make_unique<Texture>(path, slot);
}
void TextureResource::LoadSpecularTexture(const char* path, U32 slot)
{
	m_specularTexture = std::make_unique<Texture>(path, slot);
}
void TextureResource::SetSamplerState(Ptr<SamplerState>& samplerState)
{
	m_samplerState = std::move(samplerState);
}



