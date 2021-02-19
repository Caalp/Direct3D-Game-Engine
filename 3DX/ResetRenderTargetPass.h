#pragma once
#include "Pass.h"
#include "RenderGraph.h"
class ResetRenderTargetPass : public Pass
{
public:

	ResetRenderTargetPass(RenderGraph& rg,std::string passName);
	void Execute(Graphics& gfx) override;
	void Reset() override;
private:
	RenderGraph& rg;
};