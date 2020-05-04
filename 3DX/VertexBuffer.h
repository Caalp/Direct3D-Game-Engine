#pragma once
#include "Bindable.h"
#include <vector>
#include "xnacollision.h"

#define ReleaseCOM(x) {if(x){x->Release(); x = 0;}}
class VertexBuffer : public Bindable
{

public:
	template<typename V>
	VertexBuffer(Graphics& gfx, const std::vector<V>& v) : stride{ UINT(sizeof(V)),0u }, offset{ UINT(0u), 0u }
	{
		D3D11_BUFFER_DESC vbdesc = {};
		vbdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbdesc.Usage = D3D11_USAGE_DYNAMIC;
		vbdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vbdesc.MiscFlags = 0u;
		vbdesc.ByteWidth = sizeof(V)*v.size(); // size of the vertices array
		vbdesc.StructureByteStride = sizeof(V);
		// data for initializing a subresource 
		D3D11_SUBRESOURCE_DATA sd = {};

		sd.pSysMem = v.data(); // pointer to initialization data
		//GetDevice(gfx)->CreateBuffer(&vbdesc, &sd, &pVertexBuffer[0]);

	}
	template<typename C>
	void Update(Graphics& gfx,  const std::vector<C>& cb, int& instancedData)
	{
		DirectX::XMFLOAT4X4 temp_proj;
		DirectX::XMStoreFloat4x4(&temp_proj, gfx.GetProjection());
		
		XMMATRIX proj;
		proj._11 = temp_proj._11;
		proj._12 = temp_proj._12;
		proj._13 = temp_proj._13;
		proj._14 = temp_proj._14;

		proj._21 = temp_proj._21;
		proj._22 = temp_proj._22;
		proj._23 = temp_proj._23;
		proj._24 = temp_proj._24;

		proj._31 = temp_proj._31;
		proj._32 = temp_proj._32;
		proj._33 = temp_proj._33;
		proj._34 = temp_proj._34;

		proj._41 = temp_proj._41;
		proj._42 = temp_proj._42;
		proj._43 = temp_proj._43;
		proj._44 = temp_proj._44;



		XNA::Frustum mCamFrustum;
		XNA::ComputeFrustumFromProjection(&mCamFrustum, &proj);
		XNA::AxisAlignedBox mBox;
		XMVECTOR center{ 0.0f,0.0f,0.0f };
		XMVECTOR extends{ 0.5f,0.5f,0.5f };
		XMStoreFloat3(&mBox.Center, center);
		XMStoreFloat3(&mBox.Extents, extends);
		int mVisibleObjectCount = 0;
		DirectX::XMVECTOR detView = DirectX::XMMatrixDeterminant(gfx.GetView());
		DirectX::XMMATRIX invView = DirectX::XMMatrixInverse(&detView, gfx.GetView());

		D3D11_MAPPED_SUBRESOURCE mappedData;
		GetContext(gfx)->Map(pVertexBuffer[1], 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);

		C* dataView = reinterpret_cast<C*>(mappedData.pData);

		for (UINT i = 0; i < cb.size(); i++)
		{
			DirectX::XMMATRIX W = DirectX::XMLoadFloat4x4(&cb[i].World);
			DirectX::XMMATRIX invWorld = DirectX::XMMatrixInverse(&DirectX::XMMatrixDeterminant(W), W);

			DirectX::XMMATRIX toLocal = DirectX::XMMatrixMultiply(invView, invWorld);

			DirectX::XMVECTOR scale;
			DirectX::XMVECTOR rotQuat;
			DirectX::XMVECTOR translation;
			DirectX::XMMatrixDecompose(&scale, &rotQuat, &translation, toLocal);
			
			XNA::Frustum localspaceFrustum;
			XNA::TransformFrustum(&localspaceFrustum, &mCamFrustum, XMVectorGetX(scale), rotQuat, translation);

			if (XNA::IntersectAxisAlignedBoxFrustum(&mBox, &localspaceFrustum) != 0)
			{
				// Write the instance data to dynamic VB of the visible objects.
				dataView[mVisibleObjectCount++] = cb[i];
			}

		}
		instancedData = mVisibleObjectCount;
		GetContext(gfx)->Unmap(pVertexBuffer[1], 0);
	}
	template<typename V, typename T>
	VertexBuffer(Graphics& gfx, const std::vector<V>& v1, const std::vector<T>& v2) : stride{ UINT(sizeof(V)),UINT(sizeof(T)) }, offset{UINT(0u), UINT(0u)}
	{
		//pVertexBuffer[0] = nullptr;
		//pVertexBuffer[1] = nullptr;
		ID3D11Buffer* staticDataBuffer;
		// Create the static data with USAGE_IMMUTABLE since will be create once and 
		// will read by the GPU only
		D3D11_BUFFER_DESC vbdesc1 = {};
		vbdesc1.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbdesc1.Usage = D3D11_USAGE_IMMUTABLE; 
		vbdesc1.CPUAccessFlags = 0u;
		vbdesc1.MiscFlags = 0u;
		vbdesc1.ByteWidth = sizeof(V)*v1.size(); // size of the vertices array
		vbdesc1.StructureByteStride = sizeof(V);
		// data for initializing a subresource 
		D3D11_SUBRESOURCE_DATA sd = {};
		
		sd.pSysMem = v1.data(); // pointer to initialization data
		GetDevice(gfx)->CreateBuffer(&vbdesc1, &sd, &staticDataBuffer);

		ID3D11Buffer* instancedDataBuffer;
		D3D11_BUFFER_DESC vbdesc2 = {};
		vbdesc2.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbdesc2.Usage = D3D11_USAGE_DYNAMIC;
		vbdesc2.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vbdesc2.MiscFlags = 0u;
		vbdesc2.ByteWidth = sizeof(T)*v2.size(); // size of the vertices array
		vbdesc2.StructureByteStride = sizeof(T);
		// data for initializing a subresource 
		sd = {};
		sd.pSysMem = v2.data(); // pointer to initialization data
		GetDevice(gfx)->CreateBuffer(&vbdesc2, &sd, &instancedDataBuffer);

		pVertexBuffer[0] = staticDataBuffer;
		pVertexBuffer[1] = instancedDataBuffer;

	
		//ReleaseCOM(staticDataBuffer);
		//ReleaseCOM(instancedDataBuffer);

	}
	/*~VertexBuffer()
	{
		for (int i = 0; i < 2; i++)
			ReleaseCOM(pVertexBuffer[i]);
	}*/
	
	void Bind(Graphics& gfx)
	{
		if (stride[1] == 0)
		{
			//GetContext(gfx)->IASetVertexBuffers(0u, 1u, &pVertexBuffer[0], &stride[0], &offset[0]);
		}
		else
		{

			GetContext(gfx)->IASetVertexBuffers(0u, 2u, pVertexBuffer,stride, offset);
		}
		
	}
	
private:
	UINT stride[2] = {0,0};
	UINT offset[2] = {0,0};
	
	//mutable Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer[2];
	ID3D11Buffer* pVertexBuffer[2];
};