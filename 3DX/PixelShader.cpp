#include "PixelShader.h"


PixelShader::PixelShader(const std::string& filename)
{
	std::string fName = SHADER_DIRECTORY + filename;
	//gfx.CompileShader(filename, entryPoint, pModel, &pBlob); // compile shader in runtime
	D3DReadFileToBlob(std::wstring(fName.begin(),fName.end()).c_str(), &pBlob);

	GraphicsResources::GetSingleton().pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
}

void PixelShader::Bind(Graphics & gfx)
{
	GraphicsResources::GetSingleton().pImmediateContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}
