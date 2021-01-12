#include "PixelShader.h"


PixelShader::PixelShader(Graphics & gfx, const std::string& filename)
{
	std::string fName = SHADER_DIRECTORY + filename;
	//gfx.CompileShader(filename, entryPoint, pModel, &pBlob); // compile shader in runtime
	D3DReadFileToBlob(std::wstring(fName.begin(),fName.end()).c_str(), &pBlob);

	GetDevice(gfx)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
}

void PixelShader::Bind(Graphics & gfx)
{
	GetContext(gfx)->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}
