#pragma once
#include "Bindable.h"
#include "TextureLoader.h"
#include <vector>
#include <string>
#include "BufferResource.h"


class Texture : public Bindable
{
public:
	//Texture(Graphics& gfx, const class Surface& s);
	Texture(const std::vector<std::string>& filepath, unsigned int index);
	Texture(const char* filePath, unsigned int bufferSlot = 0u);
	Texture(ID3D11ShaderResourceView* paramSrv, unsigned int bufferSlot = 0u);
	
	~Texture();
	
	void Bind(Graphics& gfx) override;
	void Bind()override;

public:
	UINT bufferSlot;
	ID3D11ShaderResourceView* srv;
};