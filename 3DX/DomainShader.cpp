#include "DomainShader.h"

DomainShader::DomainShader(Graphics & gfx, LPCWSTR filename)
{
	D3DReadFileToBlob(filename, &pBlob);
	GetDevice(gfx)->CreateDomainShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pDomainShader);
}

void DomainShader::Bind(Graphics & gfx)
{
	GetContext(gfx)->DSSetShader(pDomainShader.Get(), nullptr, 0u);
}
