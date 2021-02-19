#include "ResetRenderTargetPass.h"

ResetRenderTargetPass::ResetRenderTargetPass(RenderGraph& rg,std::string passName) : Pass(passName),rg(rg)
{
}

void ResetRenderTargetPass::Execute(Graphics& gfx)
{
	rg.ResetRenderTarget(gfx);
}

void ResetRenderTargetPass::Reset()
{
}
