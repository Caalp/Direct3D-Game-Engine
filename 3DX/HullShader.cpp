#include "HullShader.h"

HullShader::HullShader(Graphics & gfx, LPCWSTR filename)
{
	D3DReadFileToBlob(filename, &pBlob);
	GetDevice(gfx)->CreateHullShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pHullShader);

}

void HullShader::Bind(Graphics & gfx)
{
	GetContext(gfx)->HSSetShader(pHullShader.Get(), nullptr, 0u);
}
