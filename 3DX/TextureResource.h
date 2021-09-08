#pragma once
#include "IResource.h"
#include "Texture.h"
#include "SamplerState.h"


class aiMaterial;

class TextureResource : public IResource
{
public:

	void LoadMaterial(const aiMaterial* const* pMaterials, int materialIndex);
	void LoadNormalTexture(const char* path, U32 slot);
	void LoadDiffuseTexture(const char* path, U32 slot);
	void LoadSpecularTexture(const char* path, U32 slot);
	void SetSamplerState(Ptr<SamplerState>& samplerState);


private:
	Ptr<Texture> m_normalTexture;
	Ptr<Texture> m_diffuseTexture;
	Ptr<Texture> m_specularTexture;
	Ptr<SamplerState> m_samplerState;
};