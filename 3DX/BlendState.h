#pragma once
#include "Bindables.h"
class BlendState : public Bindables
{
public:
	BlendState(Graphics& gfx);
	void ResetBlendState(Graphics& gfx);
	void Bind(Graphics& gfx);
private:
	//Microsoft::WRL::ComPtr<ID3D11RasterizerState> rastState;
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendState;

};