#pragma once
#include "Bindables.h"

class SamplerState : public Bindables
{
public:
	SamplerState(Graphics& gfx);
	void Bind(Graphics& gfx) override;
protected:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> pSampler;
};