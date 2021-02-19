#include "BindingPass.h"
#include "RenderTarget.h"
#include "DepthStencil.h"

BindingPass::BindingPass(std::string passName) : Pass(passName)
{
}

void BindingPass::AddBind(std::unique_ptr<Bindable> bind)
{
	binds.push_back(std::move(bind));
}

void BindingPass::BindAll(Graphics& gfx)
{
	// Bind buffers first either depth or renderTarget
	BindBufferResources(gfx);
	for (const auto& binding : binds)
	{
		binding->Bind(gfx);
	}
}

void BindingPass::BindBufferResources(Graphics& gfx)
{
	// If renderTarget is not 
	if (renderTarget)
	{
		renderTarget->BindAsBuffer(gfx, &(*depthStencil));
	}
	else if (depthStencil)
	{
		//Create and bind default depth
		//auto& a = GetSinkByName("depthbuffer");
		// only set the depth-stencil itself
		depthStencil->BindAsBuffer(gfx);
	}
}
