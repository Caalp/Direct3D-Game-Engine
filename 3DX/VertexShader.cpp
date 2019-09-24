#include "VertexShader.h"

VertexShader::VertexShader(Graphics & gfx, LPCWSTR filename, LPCSTR entryPoint, LPCSTR pModel)
{
	gfx.CompileShader(filename, entryPoint, pModel, &pBlob); // compile shader in runtime
	GetDevice(gfx)->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
	
}

void VertexShader::Bind(Graphics & gfx)
{
	GetContext(gfx)->VSSetShader(pVertexShader.Get(), nullptr, 0u);
}

ID3DBlob * VertexShader::GetVBlob() const
{
	return pBlob.Get();
}
