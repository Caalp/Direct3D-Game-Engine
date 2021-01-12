#include "VertexShader.h"

VertexShader::VertexShader(Graphics & gfx, const std::string& filename ):shaderFilename(filename)
{
	//gfx.CompileShader(filename, entryPoint, pModel, &pBlob); // compile shader in runtime
	//Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	//gfx.CompileShader(filename, entryPoint, pModel, &pBlob); // compile shader in runtime
	std::string fullPath = SHADER_DIRECTORY + filename;
	D3DReadFileToBlob(std::wstring(fullPath.begin(),fullPath.end()).c_str(), &pBlob);
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

std::string VertexShader::GetFilename() const
{
	return shaderFilename;
}
