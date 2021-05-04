#include "RasterizerState.h"

RasterizerState::RasterizerState(Graphics & gfx, RasterizerType Rs):rsType(Rs)
{

	D3D11_RASTERIZER_DESC rsDesc = CD3D11_RASTERIZER_DESC(CD3D11_DEFAULT{});
	if (rsType == NoCull)
	{
		rsDesc.FillMode = D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_NONE;
		//rsDesc.FrontCounterClockwise = true;
		//rsDesc.DepthClipEnable = true;

	}
	else if (rsType == Default)
	{
		rsDesc.FillMode = D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_BACK;
	}
	else if (rsType == CullClockwise)
	{
		rsDesc.FillMode = D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_BACK;
		rsDesc.FrontCounterClockwise = true;
		rsDesc.DepthClipEnable = true;
	}
	GraphicsResources::GetSingleton().pDevice->CreateRasterizerState(&rsDesc, rasState.GetAddressOf());
}

void RasterizerState::Bind(Graphics & gfx)
{
	if (rsType == RasterizerType::Default)
	{
		GraphicsResources::GetSingleton().pImmediateContext->RSSetState(0);
	}
	else
	{
		GraphicsResources::GetSingleton().pImmediateContext->RSSetState(rasState.Get());
	}
}
