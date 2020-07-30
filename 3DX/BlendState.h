#pragma once
#include "Bindable.h"

class BlendState : public Bindable
{
public:
	enum BlendType
	{
		Default,
		Transparent,
		AlphaToCoverage,
		NoRenderTargetWrite,
		Additive
	};
	BlendState(Graphics& gfx, bool bState = false,BlendType bType = Default);
	//void ResetBlendState(Graphics& gfx);
	void Bind(Graphics& gfx);
private:
	//Microsoft::WRL::ComPtr<ID3D11RasterizerState> rastState;
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendState;
	//Microsoft::WRL::ComPtr<ID3D11BlendState> blendState1;
	bool isBlendOn = false;

};