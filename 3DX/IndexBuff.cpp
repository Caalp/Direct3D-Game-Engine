#include "IndexBuff.h"

IndexBuff::IndexBuff(Graphics & gfx, std::vector<WORD>& v)
{
	D3D11_BUFFER_DESC indexDesc;
	ZeroMemory(&indexDesc, sizeof(indexDesc));
	indexDesc.Usage = D3D11_USAGE_DEFAULT;
	indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexDesc.ByteWidth = sizeof(v);
	indexDesc.StructureByteStride = sizeof(unsigned short);
	indexDesc.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = &v;

	GetDevice(gfx)->CreateBuffer(&indexDesc, &sd, indexBuffer_.GetAddressOf());
}

void IndexBuff::Bind(Graphics& gfx)
{
	GetContext(gfx)->IASetIndexBuffer(indexBuffer_.Get(), DXGI_FORMAT_R16_UINT, 0);
}
