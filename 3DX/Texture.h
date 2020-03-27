#pragma once
#include "Bindable.h"
#include "TextureLoader.h"
class Texture : public Bindable
{
public:
	//Texture(Graphics& gfx, const class Surface& s);
	Texture(Graphics& gfx, const TextureLoader& s,unsigned int index = 0);
	void Bind(Graphics& gfx) override;
protected:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
};