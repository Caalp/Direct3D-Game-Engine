#include "VertexShader.h"

VertexShader::VertexShader(Graphics & gfx, LPCWSTR filename):shaderFilename(filename)
{
	//gfx.CompileShader(filename, entryPoint, pModel, &pBlob); // compile shader in runtime
	//Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	//gfx.CompileShader(filename, entryPoint, pModel, &pBlob); // compile shader in runtime
	D3DReadFileToBlob(filename, &pBlob);
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

LPCWSTR VertexShader::GetFilename() const
{
	return shaderFilename;
}
