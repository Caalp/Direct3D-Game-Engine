#include "IndexBuff.h"

IndexBuff::IndexBuff(Graphics & gfx, std::vector<WORD>& v): count((UINT)v.size())
{
	D3D11_BUFFER_DESC indexDesc;
	ZeroMemory(&indexDesc, sizeof(indexDesc));
	indexDesc.Usage = D3D11_USAGE_DEFAULT;
	indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexDesc.ByteWidth = UINT(v.size() * sizeof(unsigned short));
	indexDesc.StructureByteStride = sizeof(unsigned short);
	indexDesc.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = v.data();

	GetDevice(gfx)->CreateBuffer(&indexDesc, &sd, &indexBuffer_);
}



void IndexBuff::Bind(Graphics& gfx)
{
	GetContext(gfx)->IASetIndexBuffer(indexBuffer_.Get(), DXGI_FORMAT_R16_UINT, 0);
}

UINT IndexBuff::GetIndexCount() const
{
	return count;
}
