#include "Bindables.h"

ID3D11Device* Bindables::GetDevice(Graphics & gfx)
{
	return gfx.pDevice.Get();
}

ID3D11DeviceContext * Bindables::GetContext(Graphics & gfx)
{
	return gfx.pImmediateContext.Get();
}

ID3D11RenderTargetView * Bindables::GetTarget(Graphics & gfx)
{
	return gfx.pTarget.Get();
}
