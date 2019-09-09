#include "VertexShader.h"
#include <vector>
#include<fstream>
#include <filesystem>
uintmax_t FileSize(std::string filename)
{
	std::filesystem::path p(filename);
	if (std::filesystem::exists(p) && std::filesystem::is_regular_file(p))
		return std::filesystem::file_size(p);
	return 0;
}
std::vector<uint8_t> ReadData(const std::string filename)
{
	std::vector<uint8_t> data;

	std::ifstream fs;
	fs.open(filename, std::ifstream::in | std::ifstream::binary);
	if (fs.good())
	{
		auto size = FileSize(filename);
		// TODO: check here if size is more than size_t
		data.resize(static_cast<size_t>(size));
		fs.seekg(0, std::ios::beg);
		fs.read(reinterpret_cast<char*>(&data[0]), size);
		fs.close();
	}
	return data;
}

VertexShader::VertexShader(VS_PROP ch, Graphics& gfx)
{
	
	m_pVertexLayout = nullptr;
	m_pVertexShader = nullptr;
	m_pcbVSMatrices = nullptr;
	m_pcbVSMaterial = nullptr;
	m_pcbVSLighting = nullptr;
	m_enableLights = true;

	if (ch == VS_2D)
	{

	}
}

VertexShader::~VertexShader()
{
	SAFE_RELEASE(m_pVertexLayout);
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pcbVSMatrices);
	SAFE_RELEASE(m_pcbVSMaterial);
	SAFE_RELEASE(m_pcbVSLighting);
}

HRESULT VertexShader::OnRestore(Graphics& gfx)
{
	HRESULT hr;
	SAFE_RELEASE(m_pVertexLayout);
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pcbVSMatrices);
	SAFE_RELEASE(m_pcbVSMaterial);
	SAFE_RELEASE(m_pcbVSLighting);

	// Load and compile the vertex shader. Using the lowest
	// possible profile for broadest feature level support
	ID3DBlob* pVertexShaderBuffer = nullptr;
	
	
	auto vertexShaderBytecode = gfx.CompileShader();
	if (hr)
		 
	{
		SAFE_RELEASE(pVertexShaderBuffer);
		return hr;
	}
	if (FAILED(hr = gfx.getDevice()->CreateVertexShader(
		pVertexShaderBuffer->GetBufferPointer(),
		pVertexShaderBuffer->GetBufferSize(), NULL, &m_pVertexShader)))
	{
		SAFE_RELEASE(pVertexShaderBuffer);
		return hr;
	}
	
}


