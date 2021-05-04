#include "Bindable.h"
#include "RenderTarget.h"


const std::shared_ptr<RenderTarget>& Bindable::GetTarget(Graphics & gfx)
{
	return gfx.pTarget;
}
