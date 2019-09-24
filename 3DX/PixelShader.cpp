#include "PixelShader.h"

PixelShader::PixelShader(Graphics & gfx, LPCWSTR filename, LPCSTR entryPoint, LPCSTR pModel)
{
	gfx.CompileShader(filename, entryPoint, pModel, &pBlob); // compile shader in runtime

	GetDevice(gfx)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
}

void PixelShader::Bind(Graphics & gfx)
{
	GetContext(gfx)->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}
