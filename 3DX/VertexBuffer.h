#pragma once
#include "Bindable.h"
#include <vector>
#include "DynamicVertex.h"

class VertexBuffer : public Bindable
{


public:
	// This will be deleted //
	VertexBuffer() = default;
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
		GraphicsResources::GetSingleton().pDevice->CreateBuffer(&vbdesc, &sd, &pVertexBuffer);
		
		
	}
	template<typename V>
	VertexBuffer(const std::vector<V>& v) : stride(UINT(sizeof(V))), offset(UINT(0u))
	{
		D3D11_BUFFER_DESC vbdesc = {};
		vbdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbdesc.Usage = D3D11_USAGE_DEFAULT;
		vbdesc.CPUAccessFlags = 0u;
		vbdesc.MiscFlags = 0u;
		vbdesc.ByteWidth = sizeof(V) * v.size(); // size of the vertices array
		vbdesc.StructureByteStride = sizeof(V);
		// data for initializing a subresource 
		D3D11_SUBRESOURCE_DATA sd = {};

		sd.pSysMem = v.data(); // pointer to initialization data
		GraphicsResources::GetSingleton().pDevice->CreateBuffer(&vbdesc, &sd, &pVertexBuffer);


	}
	VertexBuffer(Graphics& gfx, dvbuff::VertexBuffer& v) : stride(v.GetVertexSizeInBytes()), offset(UINT(0u))
	{
		D3D11_BUFFER_DESC vbdesc = {};
		vbdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbdesc.Usage = D3D11_USAGE_DEFAULT;
		vbdesc.CPUAccessFlags = 0u;
		vbdesc.MiscFlags = 0u;
		vbdesc.ByteWidth = v.SizeInBytes();// size of the vertices array
		vbdesc.StructureByteStride = v.GetVertexSizeInBytes();
		// data for initializing a subresource 
		D3D11_SUBRESOURCE_DATA sd = {};

		sd.pSysMem = v.Data(); // pointer to initialization data
		GraphicsResources::GetSingleton().pDevice->CreateBuffer(&vbdesc, &sd, &pVertexBuffer);


	}
	void Create(void* data, U32 size, U32 stride)
	{
		D3D11_BUFFER_DESC vbdesc = {};
		vbdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbdesc.Usage = D3D11_USAGE_DEFAULT;
		vbdesc.CPUAccessFlags = 0u;
		vbdesc.MiscFlags = 0u;
		vbdesc.ByteWidth = size;// size of the vertices array
		vbdesc.StructureByteStride = stride;
		// data for initializing a subresource 
		D3D11_SUBRESOURCE_DATA sd = {};

		sd.pSysMem = data; // pointer to initialization data
		GraphicsResources::GetSingleton().pDevice->CreateBuffer(&vbdesc, &sd, &pVertexBuffer);
	}
	void Bind(Graphics& gfx);
	void Bind() override;

protected:
	UINT stride;
	UINT offset;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
};