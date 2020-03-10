#pragma once
#include "Bindable.h"

class DSS: public Bindable
{
public:
	enum DSSType
	{
		Mirror,
		DrawReflaction
	};
	DSS(Graphics& gfx, DSSType dType);
	void Bind(Graphics& gfx);
private:
	Microsoft::WRL::ComPtr< ID3D11DepthStencilState> pDSS;
};