#include "Bindable.h"

ID3D11Device* Bindable::GetDevice(Graphics & gfx)
{
	return gfx.pDevice.Get();
}

ID3D11DeviceContext * Bindable::GetContext(Graphics & gfx)
{
	return gfx.pImmediateContext.Get();
}

const std::shared_ptr<RenderTarget>& Bindable::GetTarget(Graphics & gfx)
{
	return gfx.pTarget;
}
