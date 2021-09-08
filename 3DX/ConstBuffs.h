#pragma once
#include "Bindable.h"
#include <vector>
#include "GraphicsResources.h"

template<typename C>
class ConstBuffs : public Bindable
{
	
public:
	/* To Do:  Break dependency to passing vector as template argument that is dumb */
	void Update(const C& cb)
	{
		D3D11_MAPPED_SUBRESOURCE MappedSource;
		GraphicsResources::GetSingleton().pImmediateContext->Map(
			pConstBuffer.Get(), 0u,
			D3D11_MAP_WRITE_DISCARD, 0u,
			&MappedSource
		);

		memcpy(MappedSource.pData, &cb, sizeof(cb));
		GraphicsResources::GetSingleton().pImmediateContext->Unmap(pConstBuffer.Get(), 0u);
		
	}
	void Update(const C& cb,UINT size)
	{
		D3D11_MAPPED_SUBRESOURCE MappedSource;
		GraphicsResources::GetSingleton().pImmediateContext->Map(
			pConstBuffer.Get(), 0u,
			D3D11_MAP_WRITE_DISCARD, 0u,
			&MappedSource
		);

		memcpy(MappedSource.pData, cb.data(), sizeof(cb[0])*size);
		GraphicsResources::GetSingleton().pImmediateContext->Unmap(pConstBuffer.Get(), 0u);

	}
	
	ConstBuffs(const C& consts, UINT slot = 0u)
		:
		slot(slot)
	{
		D3D11_BUFFER_DESC cbd;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = sizeof(consts);
		cbd.StructureByteStride = 0u;

		D3D11_SUBRESOURCE_DATA csd = {};
		csd.pSysMem = &consts;
		GraphicsResources::GetSingleton().pDevice->CreateBuffer(&cbd, &csd, &pConstBuffer);
	}
	ConstBuffs(C& consts, UINT size,UINT slot)
		:
		slot(slot)
	{
		D3D11_BUFFER_DESC cbd;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = sizeof(consts[0])*55;
		cbd.StructureByteStride = 0u;

		D3D11_SUBRESOURCE_DATA csd = {};
		csd.pSysMem = &consts[0];
		GraphicsResources::GetSingleton().pDevice->CreateBuffer(&cbd, &csd, &pConstBuffer);
	}

	
	ConstBuffs(UINT size,UINT slot = 0u)
		:slot(slot)
	{

		D3D11_BUFFER_DESC bdsc{};
		bdsc.ByteWidth = size;
		bdsc.Usage = D3D11_USAGE_DYNAMIC;
		bdsc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bdsc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bdsc.MiscFlags = 0u;
		bdsc.StructureByteStride = 0u;

		GraphicsResources::GetSingleton().pDevice->CreateBuffer(&bdsc, nullptr, &pConstBuffer);
	}

protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstBuffer;
	UINT slot;
};


template <typename C = std::vector<char>>
class VSConstBuff : public ConstBuffs<C>
{
	using ConstBuffs<C>::pConstBuffer;
public:
	using ConstBuffs<C>::ConstBuffs;
	
	void Bind(Graphics& gfx) override
	{
		GraphicsResources::GetSingleton().pImmediateContext->VSSetConstantBuffers(0u, 1u,pConstBuffer.GetAddressOf());
	}
	void Bind() override
	{
		GraphicsResources::GetSingleton().pImmediateContext->VSSetConstantBuffers(0u, 1u, pConstBuffer.GetAddressOf());
	}
	void Bind(UINT startSlot,UINT numofBuff) override
	{
		GraphicsResources::GetSingleton().pImmediateContext->VSSetConstantBuffers(startSlot,numofBuff, ConstBuffs<C>::pConstBuffer.GetAddressOf());
	}
};

template <typename C>
class PSConstBuff : public ConstBuffs<C>
{
	using ConstBuffs<C>::pConstBuffer;
	using ConstBuffs<C>::slot;
public:
	using ConstBuffs<C>::ConstBuffs;

	void Bind(Graphics& gfx) override
	{
		GraphicsResources::GetSingleton().pImmediateContext->PSSetConstantBuffers(slot, 1u,pConstBuffer.GetAddressOf());
	}
	/*void Bind(Graphics& gfx, UINT startSlot, UINT numofBuff) override
	{
		GetContext(gfx)->VSSetConstantBuffers(startSlot, numofBuff, pConstBuffer.GetAddressof());
	}*/
};