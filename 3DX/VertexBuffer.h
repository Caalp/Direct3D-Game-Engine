#pragma once
#include "Bindables.h"
#include <vector>
class VertexBuffer : public Bindables
{


public:
	template<typename V>
	VertexBuffer(Graphics& gfx, const std::vector<V>& v) : stride(UINT(sizeof(V))),offset(UINT(0u))
	{
		D3D11_BUFFER_DESC vbdesc = {};
		vbdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbdesc.Usage = D3D11_USAGE_DEFAULT;
		vbdesc.CPUAccessFlags = 0u;
		vbdesc.MiscFlags = 0u;
		vbdesc.ByteWidth = sizeof(V)*v.size(); // size of the vertices array
		vbdesc.StructureByteStride = sizeof(V);
		// data for initializing a subresource 
		D3D11_SUBRESOURCE_DATA sd = {};
		
		sd.pSysMem = v.data(); // pointer to initialization data
		GetDevice(gfx)->CreateBuffer(&vbdesc, &sd, &pVertexBuffer);
		
		
	}
	void Bind(Graphics& gfx);

protected:
	UINT stride;
	UINT offset;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
};