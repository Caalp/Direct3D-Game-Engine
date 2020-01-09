#include "PixelShader.h"

PixelShader::PixelShader(Graphics & gfx, LPCWSTR filename)
{
	
	//gfx.CompileShader(filename, entryPoint, pModel, &pBlob); // compile shader in runtime
	D3DReadFileToBlob(filename, &pBlob);

	GetDevice(gfx)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
}

void PixelShader::Bind(Graphics & gfx)
{
	GetContext(gfx)->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}
