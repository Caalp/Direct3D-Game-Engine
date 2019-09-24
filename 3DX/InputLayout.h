#pragma once
#include "Bindables.h"
#include <vector>
class InputLayout : public Bindables
{
public:
	InputLayout(Graphics& gfx, const std::vector< D3D11_INPUT_ELEMENT_DESC>& v,ID3DBlob* pBlob);
	void Bind(Graphics& gfx);

private:

	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;

};