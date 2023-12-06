#pragma once
#include "Bindable.h"
#include "TextureLoader.h"
#include <vector>
#include <string>

#define TEXTURES_PATH "../Compiled/3DX_Build/Textures/"

class Texture : public Bindable
{
public:
	//Texture(Graphics& gfx, const class Surface& s);
	Texture(Graphics& gfx, const std::vector<std::string>& filepath, unsigned int index);
	Texture(Graphics& gfx, const char* filePath, unsigned int bufferSlot = 0u);
	Texture(Graphics& gfx, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> paramSrv, unsigned int bufferSlot = 0u);
	void Bind(Graphics& gfx) override;
protected:
	UINT bufferSlot;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
};