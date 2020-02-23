#pragma once
#include "Bindable.h"

class Texture : public Bindable
{
public:
	Texture(Graphics& gfx, const class Surface& s);
	Texture(Graphics& gfx, const class TextureLoader& s);
	void Bind(Graphics& gfx) override;
protected:

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
};