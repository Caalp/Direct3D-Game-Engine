#pragma once
#include "Bindable.h"
class RasterizerState : public Bindable
{
public:
	enum RasterizerType
	{
		Default,
		NoCull,
		CullClockwise

	};
	RasterizerState(Graphics& gfx,RasterizerType Rs = Default);
	void Bind(Graphics& gfx);
private:
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasState;
	RasterizerType rsType;



};