#pragma once
#include "Bindable.h"
#include <vector>

class InputLayout : public Bindable
{
public:
	InputLayout(Graphics& gfx, const std::vector< D3D11_INPUT_ELEMENT_DESC>& v,ID3DBlob* pBlob);
	//InputLayout(Graphics& gfx, const std::vector< D3D11_INPUT_ELEMENT_DESC>& v, std::unique_ptr<D3DX11_PASS_DESC> passDesc,ID3DBlob* pBlob);
	void Bind(Graphics& gfx);
private:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
};