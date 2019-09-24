#include "InputLayout.h"

InputLayout::InputLayout(Graphics & gfx, const std::vector<D3D11_INPUT_ELEMENT_DESC>& v, ID3DBlob* pBlob)
{
	GetDevice(gfx)->CreateInputLayout(v.data(), (UINT)v.size(),pBlob->GetBufferPointer(),// pointer to the compiled shader code
							   pBlob->GetBufferSize(),
							   &pInputLayout
	);
}

void InputLayout::Bind(Graphics & gfx)
{
	GetContext(gfx)->IASetInputLayout(pInputLayout.Get());
}
