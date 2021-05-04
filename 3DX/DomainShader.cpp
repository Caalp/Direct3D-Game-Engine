#include "DomainShader.h"

DomainShader::DomainShader(Graphics & gfx, LPCWSTR filename)
{
	D3DReadFileToBlob(filename, &pBlob);
	GraphicsResources::GetSingleton().pDevice->CreateDomainShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pDomainShader);
}

void DomainShader::Bind(Graphics & gfx)
{
	GraphicsResources::GetSingleton().pImmediateContext->DSSetShader(pDomainShader.Get(), nullptr, 0u);
}
