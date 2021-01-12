#include "SamplerState.h"

SamplerState::SamplerState(Graphics & gfx)
{
	D3D11_SAMPLER_DESC sampler_desc = CD3D11_SAMPLER_DESC{ CD3D11_DEFAULT{} };
	sampler_desc.Filter = D3D11_FILTER_ANISOTROPIC;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.MaxAnisotropy = D3D11_REQ_MAXANISOTROPY;
	

	GetDevice(gfx)->CreateSamplerState(&sampler_desc, &pSampler);
}

void SamplerState::Bind(Graphics& gfx)
{
	GetContext(gfx)->PSSetSamplers(0, 1u, pSampler.GetAddressOf());
}
