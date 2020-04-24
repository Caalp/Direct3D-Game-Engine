#pragma once
#include "Bindable.h"
#include "TextureLoader.h"
class Texture : public Bindable
{
public:
	//Texture(Graphics& gfx, const class Surface& s);
	Texture(Graphics& gfx, const TextureLoader& s,unsigned int index = 0);
	Texture(Graphics& gfx, const char* filePath,unsigned int bufferSlot = 0u);
	void Bind(Graphics& gfx) override;
protected:
	UINT bufferSlot;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
};