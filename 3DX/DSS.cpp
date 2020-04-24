#include "DSS.h"

DSS::DSS(Graphics & gfx, DSSType dType):dss(dType)
{
	D3D11_DEPTH_STENCIL_DESC DSSDesc{ 0 };
	if (dType == DSSType::Mirror)
	{
		DSSDesc.DepthEnable = true;
		DSSDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		DSSDesc.DepthFunc = D3D11_COMPARISON_LESS;
		DSSDesc.StencilEnable = true;
		DSSDesc.StencilReadMask = 0xff;
		DSSDesc.StencilWriteMask = 0xff;
		
		DSSDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		DSSDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		DSSDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
		DSSDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		DSSDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		DSSDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		DSSDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
		DSSDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	}
	else if (dType == DrawReflaction)
	{
		DSSDesc.DepthEnable = true;
		DSSDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		DSSDesc.DepthFunc = D3D11_COMPARISON_LESS;
		DSSDesc.StencilEnable = true;
		DSSDesc.StencilReadMask = 0xff;
		DSSDesc.StencilWriteMask = 0xff;

		DSSDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		DSSDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		DSSDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		DSSDesc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;

		DSSDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		DSSDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		DSSDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		DSSDesc.BackFace.StencilFunc = D3D11_COMPARISON_EQUAL;
	}
	else if (dType == NoDoubleBlend)
	{
		DSSDesc.DepthEnable = true;
		DSSDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		DSSDesc.DepthFunc = D3D11_COMPARISON_LESS;
		DSSDesc.StencilEnable = true;
		DSSDesc.StencilReadMask = 0xff;
		DSSDesc.StencilWriteMask = 0xff;

		DSSDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		DSSDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		DSSDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
		DSSDesc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;

		DSSDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		DSSDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		DSSDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
		DSSDesc.BackFace.StencilFunc = D3D11_COMPARISON_EQUAL;
	}
	else if (dType == NoDepthWrite)
	{
		DSSDesc.DepthEnable = true;
		DSSDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		DSSDesc.DepthFunc = D3D11_COMPARISON_LESS;
	}
	else if (dType == LessOrEqual)
	{
		DSSDesc.DepthEnable = true;
		DSSDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		DSSDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	}
	
	GetDevice(gfx)->CreateDepthStencilState(&DSSDesc, pDSS.GetAddressOf());
}

void DSS::Bind(Graphics & gfx)
{
	if (dss == NoDoubleBlend)
	{
		GetContext(gfx)->OMSetDepthStencilState(pDSS.Get(), 0);
	}
	else
	{
		GetContext(gfx)->OMSetDepthStencilState(pDSS.Get(), 1);

	}
}
