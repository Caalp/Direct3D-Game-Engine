#pragma once
#include "Bindable.h"
#include "TextureLoader.h"
#include <vector>
#include <string>



class Texture : public Bindable
{
public:
	//Texture(Graphics& gfx, const class Surface& s);
	Texture(Graphics& gfx, const std::vector<std::string>& filepath, unsigned int index);
	Texture(Graphics& gfx, const char* filePath, unsigned int bufferSlot = 0u);
	Texture(Graphics& gfx, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> paramSrv, unsigned int bufferSlot = 0u);
	void Bind(Graphics& gfx) override;

public:
	UINT bufferSlot;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
};