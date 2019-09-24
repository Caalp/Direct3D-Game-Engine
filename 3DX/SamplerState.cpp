#include "SamplerState.h"

SamplerState::SamplerState(Graphics & gfx)
{
	D3D11_SAMPLER_DESC sampler_desc = {};
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	GetDevice(gfx)->CreateSamplerState(&sampler_desc, &pSampler);
}

void SamplerState::Bind(Graphics& gfx)
{
	GetContext(gfx)->PSSetSamplers(0, 1u, pSampler.GetAddressOf());
}
