#include "HullShader.h"

HullShader::HullShader(Graphics & gfx, LPCWSTR filename)
{
	D3DReadFileToBlob(filename, &pBlob);
	GraphicsResources::GetSingleton().pDevice->CreateHullShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pHullShader);

}

void HullShader::Bind(Graphics & gfx)
{
	GraphicsResources::GetSingleton().pImmediateContext->HSSetShader(pHullShader.Get(), nullptr, 0u);
}
