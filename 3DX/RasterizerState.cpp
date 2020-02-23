#include "RasterizerState.h"

RasterizerState::RasterizerState(Graphics & gfx)
{
	D3D11_RASTERIZER_DESC wireFrame = {};
	wireFrame.FillMode = D3D11_FILL_SOLID;
	wireFrame.CullMode = D3D11_CULL_NONE;
	wireFrame.FrontCounterClockwise = false;
	wireFrame.DepthClipEnable = true;

	GetDevice(gfx)->CreateRasterizerState(&wireFrame, rasState.GetAddressOf());
}

void RasterizerState::Bind(Graphics & gfx)
{
	GetContext(gfx)->RSSetState(rasState.Get());
}
