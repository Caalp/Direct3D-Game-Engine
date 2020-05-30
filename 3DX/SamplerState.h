#pragma once
#include "Bindable.h"

class SamplerState : public Bindable
{
public:
	SamplerState(Graphics& gfx);
	void Bind(Graphics& gfx) override;
protected:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> pSampler;
};