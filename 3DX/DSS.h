#pragma once
#include "Bindable.h"

class DSS: public Bindable
{
public:
	enum DSSType
	{
		Mirror,
		DrawReflaction,
		NoDoubleBlend,
		NoDepthWrite
	};
	DSS(Graphics& gfx, DSSType dType);
	void Bind(Graphics& gfx);
private:
	DSSType dss;
	Microsoft::WRL::ComPtr< ID3D11DepthStencilState> pDSS;
};