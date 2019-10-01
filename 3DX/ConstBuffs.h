#pragma once
#include "Bindables.h"
template<typename C>
class ConstBuffs : public Bindables
{
	
public:
	void Update(Graphics& gfx, const C& cb)
	{
		D3D11_MAPPED_SUBRESOURCE MappedSource;
		GetContext(gfx)->Map(
			pConstBuffer.Get(), 0u,
			D3D11_MAP_WRITE_DISCARD, 0u,
			&MappedSource
		);
		memcpy(MappedSource.pData, &cb, sizeof(cb));
		GetContext(gfx)->Unmap(pConstBuffer.Get(), 0u);
		
	}
	
	ConstBuffs(Graphics& gfx, const C& cb)
	{
		D3D11_BUFFER_DESC bdsc{};
		bdsc.ByteWidth = sizeof(cb);
		bdsc.Usage = D3D11_USAGE_DYNAMIC;
		bdsc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bdsc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bdsc.MiscFlags = 0u;
		bdsc.StructureByteStride = 0u;

		D3D11_SUBRESOURCE_DATA InitData = {};
		InitData.pSysMem = &cb;
		GetDevice(gfx)->CreateBuffer(&bdsc, &InitData, &pConstBuffer);
	}
	ConstBuffs(Graphics& gfx)
	{
		D3D11_BUFFER_DESC bdsc{};
		bdsc.ByteWidth = sizeof(C);
		bdsc.Usage = D3D11_USAGE_DYNAMIC;
		bdsc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bdsc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bdsc.MiscFlags = 0u;
		bdsc.StructureByteStride = 0u;

		GetDevice(gfx)->CreateBuffer(&bdsc, nullptr, &pConstBuffer);
	}
protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstBuffer;
};

template <typename C>
class VSConstBuff : public ConstBuffs<C>
{
	using ConstBuffs<C>::pConstBuffer;
public:
	using ConstBuffs<C>::ConstBuffs;
	
	void Bind(Graphics& gfx) override
	{
		Bindables::GetContext(gfx)->VSSetConstantBuffers(1u, 1u,pConstBuffer.GetAddressOf());
	}
	void Bind(Graphics& gfx, UINT startSlot,UINT numofBuff) override
	{
		Bindables::GetContext(gfx)->VSSetConstantBuffers(startSlot,numofBuff, ConstBuffs<C>::pConstBuffer.GetAddressOf());
	}
};

template <typename C>
class PSConstBuff : public ConstBuffs<C>
{
	using ConstBuffs<C>::pConstBuffer;
public:
	using ConstBuffs<C>::ConstBuffs;

	void Bind(Graphics& gfx) override
	{
		Bindables::GetContext(gfx)->PSSetConstantBuffers(0u, 1u,pConstBuffer.GetAddressOf());
	}
	/*void Bind(Graphics& gfx, UINT startSlot, UINT numofBuff override
	{
		GetContext(gfx)->VSSetConstantBuffers(startSlot, numofBuff, pConstBuffer.GetAddressof());
	}*/
};