#include "InputLayout.h"

InputLayout::InputLayout(const std::vector<D3D11_INPUT_ELEMENT_DESC>& v, ID3DBlob* pBlob)
{
	GraphicsResources::GetSingleton().pDevice->CreateInputLayout(v.data(), (UINT)v.size(),pBlob->GetBufferPointer(),// pointer to the compiled shader code
							   pBlob->GetBufferSize(),
							   &pInputLayout
	);
}

//inputlayout::inputlayout(graphics & gfx, const std::vector<d3d11_input_element_desc>& v, std::unique_ptr<d3dx11_pass_desc> passdesc, id3dblob * pblob)
//{
//
//	getdevice(gfx)->createinputlayout(v.data(), (uint)v.size(), pblob->getbufferpointer(),// pointer to the compiled shader code
//		pblob->getbuffersize(),
//		&pinputlayout
//	);
//}

void InputLayout::Bind(Graphics & gfx)
{
	GraphicsResources::GetSingleton().pImmediateContext->IASetInputLayout(pInputLayout.Get());
}
