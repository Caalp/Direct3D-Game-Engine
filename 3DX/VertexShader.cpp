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
VertexShader::VertexShader()
{
	
	m_pVertexLayout = nullptr;
	m_pVertexShader = nullptr;
	m_pcbVSMatrices = nullptr;
	m_pcbVSMaterial = nullptr;
	m_pcbVSLighting = nullptr;
	m_enableLights = true;

	
}

VertexShader::~VertexShader()
{
	SAFE_RELEASE(m_pVertexLayout);
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pcbVSMatrices);
	SAFE_RELEASE(m_pcbVSMaterial);
	SAFE_RELEASE(m_pcbVSLighting);
}

HRESULT VertexShader::InitVS()
{
	HRESULT hr;
	SAFE_RELEASE(m_pVertexLayout);
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pcbVSMatrices);
	SAFE_RELEASE(m_pcbVSMaterial);
	SAFE_RELEASE(m_pcbVSLighting);

	// Load and compile the vertex shader. Using the lowest
	// possible profile for broadest feature level support
	// Creation of Vertexbuffer
	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC vbdesc = {};
	vbdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbdesc.Usage = D3D11_USAGE_DEFAULT;
	vbdesc.CPUAccessFlags = 0u;
	vbdesc.MiscFlags = 0u;
	vbdesc.ByteWidth = sizeof(vertices); // size of the vertices array
	vbdesc.StructureByteStride = sizeof(Vertex);
	// data for initializing a subresource 
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices; // pointer to initialization data
	hr = pDevice->CreateBuffer(&vbdesc, &sd, pVertexBuffer.GetAddressOf());

	// error check for creation of buffer here 


	const UINT stride = sizeof(Vertex); // each stride has the size of element used in buffer 
	const UINT offset = 0u; // offset number of the bytes first element in the buffer and first element will be used 
	// bind an array of vertex buffers to the input assembler 
	
	ID3D11Buffer* indexBuffer_;
	WORD indices[] =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
	};
	D3D11_BUFFER_DESC indexDesc;
	ZeroMemory(&indexDesc, sizeof(indexDesc));
	indexDesc.Usage = D3D11_USAGE_DEFAULT;
	indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexDesc.ByteWidth = sizeof(indices);
	indexDesc.StructureByteStride = sizeof(unsigned short);
	indexDesc.CPUAccessFlags = 0;
	sd.pSysMem = indices;

	hr = pDevice->CreateBuffer(&indexDesc, &sd, &indexBuffer_);
	pImmediateContext->IASetIndexBuffer(indexBuffer_, DXGI_FORMAT_R16_UINT, 0);
	
	wrl::ComPtr<ID3DBlob> pBlob;
	

	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	CompileShader(L"VertexShader.hlsl", "main", "vs_5_0", &pBlob); // compile shader in runtime
	
	auto bufsize = pBlob->GetBufferPointer();
	auto bb = pBlob->GetBufferSize();
	pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
	pImmediateContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);

	
	
	
	
	
}


