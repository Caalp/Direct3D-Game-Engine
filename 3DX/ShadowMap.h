#pragma once

#include "Drawable.h"

namespace wrl = Microsoft::WRL;
class ShadowMap : public Drawable
{


public:
	ShadowMap(Graphics& gfx, wrl::ComPtr<ID3D11ShaderResourceView> srv);


private:
	wrl::ComPtr<ID3D11ShaderResourceView> shaderResourceView;

};


