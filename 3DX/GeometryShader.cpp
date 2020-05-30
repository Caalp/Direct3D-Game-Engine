#include "GeometryShader.h"

GeometryShader::GeometryShader(Graphics & gfx, LPCWSTR filename)
{
	D3DReadFileToBlob(filename, pGeometryBlob.GetAddressOf());
	GetDevice(gfx)->CreateGeometryShader(pGeometryBlob->GetBufferPointer(), pGeometryBlob.Get()->GetBufferSize(), nullptr, pGeometryShader.GetAddressOf());
}

void GeometryShader::Bind(Graphics & gfx)
{
	GetContext(gfx)->GSSetShader(pGeometryShader.Get(), nullptr, 0u);
}

ID3DBlob * GeometryShader::GetGSBlob() const
{
	return pGeometryBlob.Get();
}
