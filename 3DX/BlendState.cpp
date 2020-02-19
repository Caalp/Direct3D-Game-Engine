#include "BlendState.h"

BlendState::BlendState(Graphics & gfx)
{
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;

	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	GetDevice(gfx)->CreateBlendState(&blendDesc, blendState.GetAddressOf());
}

void BlendState::ResetBlendState(Graphics & gfx)
{
	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GetContext(gfx)->OMSetBlendState(0, blendFactor, 0xffffffff);
}

void BlendState::Bind(Graphics & gfx)
{
	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GetContext(gfx)->OMSetBlendState(blendState.Get(), blendFactor, 0xffffffff);
}
