#pragma once
#include "Bindable.h"
class BlendState : public Bindable
{
public:
	BlendState(Graphics& gfx, bool bState = false);
	//void ResetBlendState(Graphics& gfx);
	void Bind(Graphics& gfx);
private:
	//Microsoft::WRL::ComPtr<ID3D11RasterizerState> rastState;
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendState;
	//Microsoft::WRL::ComPtr<ID3D11BlendState> blendState1;
	bool isBlendOn = false;

};