#include "DrawOutlinePass.h"

DrawOutlinePass::DrawOutlinePass(Graphics& gfx, std::string passName) : RenderQueuePass(passName)
{
	AddBind(std::make_unique<DSS>(gfx, DSS::DSSType::Write));
}

void DrawOutlinePass::Execute(Graphics& gfx)
{
	RenderQueuePass::Execute(gfx);
}

void DrawOutlinePass::Reset()
{
	RenderQueuePass::Reset();
}
