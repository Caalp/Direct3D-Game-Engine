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
		bdsc.StructureByteStride = 0u

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
		bdsc.StructureByteStride = 0u

		GetDevice(gfx)->CreateBuffer(&bdsc, nullptr, &pConstBuffer);
	}
protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstBuffer;
};

template <typename C>
class VSConstBuff : public ConstBuffs<C>
{
public:
	void Bind(Graphics& gfx) override
	{
		GetContext(gfx)->VSSetConstantBuffers(0u, 1u, pConstBuffer.GetAddressof());
	}
	void Bind(Graphics& gfx, UINT startSlot,UINT numofBuff) override
	{
		GetContext(gfx)->VSSetConstantBuffers(startSlot,numofBuff, pConstBuffer.GetAddressof());
	}
};

template <typename C>
class PSConstBuff : public ConstBuffs<C>
{
public:
	void Bind(Graphics& gfx) override
	{
		GetContext(gfx)->PSSetConstantBuffers(0u, 1u, pConstBuffer.GetAddressOf());
	}
	void Bind(Graphics& gfx, UINT startSlot, UINT numofBuff override
	{
		GetContext(gfx)->VSSetConstantBuffers(startSlot, numofBuff, pConstBuffer.GetAddressof());
	}
};