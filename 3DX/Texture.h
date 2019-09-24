#pragma once
#include "Bindables.h"
class Texture : public Bindables
{
public:
	Texture(Graphics& gfx, const class Surface& s);
	void Bind(Graphics& gfx) override;
protected:
	Microsoft::WRL::ComPtr<ID3D11Texture2D> ptex;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
};