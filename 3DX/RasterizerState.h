#pragma once
#include "Bindable.h"
class RasterizerState : public Bindable
{
public:
	RasterizerState(Graphics& gfx);
	void Bind(Graphics& gfx);
private:
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasState;




};